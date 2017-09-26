/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
孵化器：孵化器是孵化禽蛋的专门设备。该设备具备灯光控制、摇蛋、控制温湿度、通风等功能。

所需器件:
1. DHT22温湿度传感器模块
2. UC1701X驱动屏
3、舵机
4. RGB LED灯条
5. 风扇
6. 加热器
7. 继电器开关模块

接线说明
LCD屏
CS        D0
RST       D1
RS        D2
SDA       D3
SCK       D4
VDD       5V
VSS       GND
LEDA      5V
注：显示屏显示孵化箱内温湿度 T为温度 H为湿度

DHT22温湿度          核心板
VCC(红色)		     3V3
GND(黑色)			 GND
DATA(黄色)           D5

陶瓷加热器
控制脚(继电器)        D6

通风风扇
控制脚(继电器)        D7

舵机
VDD(红色)			  5V
GND(灰色)             GND
DATA(黄色)            A0

RGB LED灯条
VDD(红色)             接外置电源5V
GND(白色)             GND
DATA(绿色)            A1

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/
/*该头文件引用由IntoRobot自动添加.*/
#include <IntoRobot_UC1701X.h>
#include <PID.h>
#include <IntoRobot_DHT.h>
#include <Adafruit_NeoPixel.h>

//孵化器应用topic定义
#define EGGINCUBATE_DATA_TEMPERATURE    "channel/eggIncubate_0/data/temperature" //温度
#define EGGINCUBATE_DATA_HUMIDITY       "channel/eggIncubate_0/data/humidity"    //湿度
#define EGGINCUBATE_DATA_HEATSTATUS     "channel/eggIncubate_0/data/heatStatus"  //加热状态
#define EGGINCUBATE_DATA_ROLLSTATUS     "channel/eggIncubate_0/data/rollStatus"  //翻蛋状态
#define EGGINCUBATE_DATA_FANSTATUS      "channel/eggIncubate_0/data/fanStatus"   //风扇状态
#define EGGINCUBATE_CMD_CONTROL         "channel/eggIncubate_0/cmd/control"     //控制命令

//引脚定义
#define LCD_CS_PIN          D0  //LCD屏
#define LCD_RST_PIN         D1
#define LCD_RS_PIN          D2
#define LCD_SDA_PIN         D3
#define LCD_SCK_PIN         D4
#define DHT22_PIN           D5  //温湿度传感器
#define HEAT_PIN            D6  //加热开关引脚定义
#define AIR_FUN_PIN         D7  //通风风扇开关引脚定义
#define SERVO_PIN			A0  //舵机 需PWM引脚
#define RGB_PIN             A1  //灯条数据引脚
#define RGB_COUNT           30  //灯珠数量
#define RGB_TYPE            WS2812B //灯条RGB驱动IC型号

//LCD屏
IntoRobot_UC1701X uc1701x =  IntoRobot_UC1701X(LCD_CS_PIN,LCD_RST_PIN,LCD_RS_PIN,LCD_SDA_PIN,LCD_SCK_PIN); 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(RGB_COUNT, RGB_PIN, RGB_TYPE);
IntoRobot_DHT dht(DHT22_PIN, DHT22);
Servo myservo;

char temp[256];
uint32_t  getVaueTimer;//温湿度获取定时器
uint32_t  turnEggTimer;//翻蛋定时器
uint32_t  airFunTimer; //通风定时器
char heatFlag=0;  //加热标志

//PID相关参数定义
double Setpoint, Input, Output;
int WindowSize = 20;  //周期20s
unsigned long windowStartTime;
PID myPID(&Input, &Output, &Setpoint, 55, 0, 0, DIRECT);

//温湿度定义
float   humidity;   //湿度值
float   tempcelcius;//温度值

//设置灯条亮度
void set_bright(uint8_t level)
{
	static unsigned s_level_old = 0x00;

	if(level != s_level_old)
	{
		strip.setBrightness(level);
		strip.show();
	}

	s_level_old = level;
}

//设置灯条颜色
void set_color(uint32_t c, uint8_t wait)
{
	uint16_t i;

	for (i = 0; i < strip.numPixels(); i++)
	{
		strip.setPixelColor(i, c);
	}

	strip.show();
	delay(wait);
}

//控制翻蛋动作
void turnEgg(void)
{
	static int pos = 0;	//舵机转动角度
	for (pos = 40; pos >= 0; pos -= 3)
	{
		myservo.write(pos);
		delay(200);
	}

	for (pos = 0; pos <= 80; pos += 3)
	{
		myservo.write(pos);
		delay(200);
	}

	for (pos = 80; pos >= 40; pos -= 3)
	{
		myservo.write(pos);
		delay(200);
	}
}

void  IncubatorCb(uint8_t * payload, uint32_t len)
{
	int brightnessValue;
	int rgbValue;
	uint8_t heatSwitchKey,rollSwitchKey,fanSwitchKey;

	//解析云平台下发的控制命令
    aJsonClass aJson;
	aJsonObject *root = aJson.parse((char *)payload);
	if(root == NULL)
	{
	    aJson.deleteItem(root);
		return;
	}
		
	aJsonObject *_heater = aJson.getObjectItem(root, "heater");
	if(_heater != NULL)
	{
	    heatSwitchKey = atoi(_heater->valuestring);
		//加热控制
		if(heatSwitchKey)
		{
			heatFlag=1;
			digitalWrite(HEAT_PIN, HIGH);		//打开加热器
			IntoRobot.publish(EGGINCUBATE_DATA_HEATSTATUS, "1");
		}
		else
		{
			heatFlag=0;
			digitalWrite(HEAT_PIN, LOW);		//关闭加热器
			IntoRobot.publish(EGGINCUBATE_DATA_HEATSTATUS, "0");
		}
	}
	else 
	{
	    aJsonObject *_rollover = aJson.getObjectItem(root, "rollover");
	    if(_rollover != NULL)
	    {
	        rollSwitchKey = atoi(_rollover->valuestring);
	    	//翻蛋控制
			if(rollSwitchKey)
			{
				IntoRobot.publish(EGGINCUBATE_DATA_ROLLSTATUS, "1");
				turnEgg();
				IntoRobot.publish(EGGINCUBATE_DATA_ROLLSTATUS, "0");
			}
	    }
	    else
	    {
	        aJsonObject *_ventilator = aJson.getObjectItem(root, "ventilator");
	        if(_ventilator != NULL)
	        {
	            fanSwitchKey = atoi(_ventilator->valuestring);
	        	//风扇控制
				if(fanSwitchKey)
				{
					digitalWrite(AIR_FUN_PIN, HIGH); //打开通风风扇
					IntoRobot.publish(EGGINCUBATE_DATA_FANSTATUS, "1");
				}
				else
				{
					digitalWrite(AIR_FUN_PIN, LOW);	 //关闭通风风扇
					IntoRobot.publish(EGGINCUBATE_DATA_FANSTATUS, "0");
				}
	        }
	        else
	        {
                aJsonObject *_ledBrightness = aJson.getObjectItem(root,"lightBrightness");
        		if(_ledBrightness == NULL)
        		{
        		    aJson.deleteItem(root);
        			return;
        		}
        		brightnessValue = atoi(_ledBrightness->valuestring);
	           
        		aJsonObject *_ledRgb = aJson.getObjectItem(root,"lightColor");
        		if(_ledRgb == NULL)
        		{
        		    aJson.deleteItem(root);
        			return;
        		}
        		rgbValue = atoi(_ledRgb->valuestring);

        		//灯光控制
				set_bright((25*brightnessValue)/10);
				set_color(rgbValue, 20);
	        }
	    }
	}
	aJson.deleteItem(root);	
}

void setup() 
{
// put your setup code here, to run once.
	//灯初始化
	strip.begin();
	set_bright(255);
	strip.show();
	//dht22初始化
	dht.begin();
	//控制PIN初始化
	pinMode(HEAT_PIN, OUTPUT);
	pinMode(AIR_FUN_PIN, OUTPUT);
	digitalWrite(HEAT_PIN, LOW);
	digitalWrite(AIR_FUN_PIN, LOW);
	//舵机定义
	myservo.attach(SERVO_PIN);
    //LCD屏初始化
	uc1701x.begin();
	uc1701x.setTextSize(2); //设置文本大小
    uc1701x.setTextColor(WHITE); //选择文字颜色，此屏只有一种颜色，参数为WHITE 
    uc1701x.clearDisplay();
	//温度PID控制
	windowStartTime = millis();
	Setpoint = 38;
	myPID.SetOutputLimits(0, WindowSize);
	myPID.SetSampleTime(5000);	//5秒采样时间
	myPID.SetMode(AUTOMATIC);
	//接收灯光、加热、风扇、翻蛋控制
	IntoRobot.subscribe(EGGINCUBATE_CMD_CONTROL,NULL,IncubatorCb);
	getVaueTimer=timerGetId();
	turnEggTimer=timerGetId();
}

void loop() 
{
// put your main code here, to run repeatedly.
	if (timerIsEnd(getVaueTimer,1000))
	{
		getVaueTimer=timerGetId();
		tempcelcius = dht.getTempCelcius();
		if(tempcelcius==tempcelcius) //输出不NAN
		{
		    uc1701x.clearDisplay();
		    Input=tempcelcius;
			IntoRobot.publish(EGGINCUBATE_DATA_TEMPERATURE, tempcelcius);  //上送温度数据
			humidity = dht.getHumidity();
			IntoRobot.publish(EGGINCUBATE_DATA_HUMIDITY, humidity);		   //上送湿度数据
			//LCD 数据显示
			uc1701x.setCursor(0,0); //显示温度
            uc1701x.printf("T = %.2f% C", tempcelcius);
    
	        uc1701x.setCursor(0,32); //显示湿度
	        uc1701x.printf("H = %.2f%% ", humidity);
            uc1701x.display(); //开启显示
		}
	}

	//PID温度控制
	myPID.Compute();
	if (millis() - windowStartTime > WindowSize*1000)
	{
		windowStartTime += WindowSize*1000;
	}

	if (Output*1000 < (millis() - windowStartTime))       
	{
		if(heatFlag==1)
		{
			digitalWrite(HEAT_PIN, LOW);
			IntoRobot.publish(EGGINCUBATE_DATA_HEATSTATUS, "0");
			heatFlag=0;
		}
	}
	else
	{
		if(heatFlag==0)
		{
			digitalWrite(HEAT_PIN, HIGH);
			IntoRobot.publish(EGGINCUBATE_DATA_HEATSTATUS, "1");
			heatFlag=1;
		}
	}

	//翻蛋通风定时器 6个小时一次
	if (timerIsEnd(turnEggTimer,6*60*60*1000))
	{
		turnEggTimer=timerGetId();
		IntoRobot.publish(EGGINCUBATE_DATA_ROLLSTATUS, "1");
		IntoRobot.publish(EGGINCUBATE_DATA_FANSTATUS, "1");
		digitalWrite(AIR_FUN_PIN, HIGH);	//打开通风风扇
		turnEgg();
		digitalWrite(AIR_FUN_PIN, LOW);		//关闭通风风扇
		IntoRobot.publish(EGGINCUBATE_DATA_ROLLSTATUS, "0");
		IntoRobot.publish(EGGINCUBATE_DATA_FANSTATUS, "0");
	}
}
