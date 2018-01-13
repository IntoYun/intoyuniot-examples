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
 2. LCD12864屏
 3、舵机
 4. RGB LED灯条
 5. 风扇
 6. 加热器
 7. 继电器开关模块

 接线说明
 DHT22温湿度          核心板
 VCC					  3V3
 GND					  GND
 DATA                  D3

 LCD12864屏
 PIN1                  GND
 PIN2                  5V
 RS(CS)                D0
 RW(SID)               D2
 EN(CLK)               D1
 PIN15 PSB             GND

 舵机
 VDD					  5V
 GND					  GND
 DATA                  A0

 RGB LED灯条
 VDD                   5V
 GND                   GND
 DATA                  D4

 加热器
 控制脚                D5

 加热风扇
 控制脚                D6

 通风风扇
 控制脚                D7

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。

 */
#include <Adafruit_NeoPixel.h>
#include <LCD12864RSPI.h>
#include <Adafruit_DHT.h>
#include <PID.h>

#include "intorobot_bmp.h"    //开机LCD屏显示的图片

//孵化器应用topic定义
#define EGGINCUBATE_DATA_TEMPERATURE        "channel/eggIncubate_0/data/temperature" //温度
#define EGGINCUBATE_DATA_HUMIDITY           "channel/eggIncubate_0/data/humidity"    //湿度

#define EGGINCUBATE_DATA_HEATSTATUS         "channel/eggIncubate_0/data/heatStatus"  //加热状态
#define EGGINCUBATE_DATA_ROLLSTATUS         "channel/eggIncubate_0/data/rollStatus"  //翻蛋状态
#define EGGINCUBATE_DATA_FANSTATUS          "channel/eggIncubate_0/data/fanStatus"   //风扇状态

#define EGGINCUBATE_CMD_HEATSWITCH          "channel/eggIncubate_0/cmd/heatSwitch"   //加热开关
#define EGGINCUBATE_CMD_ROLLSWITCH          "channel/eggIncubate_0/cmd/rollSwitch"   //翻蛋开关
#define EGGINCUBATE_CMD_FANSWITCH           "channel/eggIncubate_0/cmd/fanSwitch"    //风扇开关
#define EGGINCUBATE_CMD_LIGHTMODE           "channel/eggIncubate_0/cmd/lightMode"    //灯条控制

#define LCD_RS_CS           D0
#define LCD_RW_SID          D2
#define LCD_EN_CLK          D1
#define DHT22_PIN           D3
#define RGB_PIN             D4
#define HEAT_PIN            D5  //加热开关引脚定义
#define HEAT_FUN_PIN        D6  //加热风扇开关引脚定义
#define AIR_FUN_PIN         D7  //通风风扇开关引脚定义

#define SERVO_PIN			A0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, RGB_PIN, WS2811);
LCD12864RSPI LCDA(LCD_RS_CS, LCD_RW_SID, LCD_EN_CLK);
Adafruit_DHT dht(DHT22_PIN, DHT22);
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

//灯条控制回调 {"brightness":1,"rgb":9291264}
void neopixelControlCb(uint8_t *payload, uint32_t len)
{
    int brightnessValue;
    int rgbValue;

    if(jsonGetValue(payload,"brightness",brightnessValue))
    {
        set_bright((25*brightnessValue)/10);
    }

    if(jsonGetValue(payload,"rgb",rgbValue))
    {
        set_color(rgbValue, 20);
    }
}

//加热器控制回调
void heatSwitchCb(uint8_t * payload, uint32_t len)
{
    if(payload[0] == '1')
    {
        heatFlag=1;
        digitalWrite(HEAT_PIN, HIGH);		//打开加热器
        digitalWrite(HEAT_FUN_PIN, HIGH);   //打开加热器风扇
        IntoRobot.publish(EGGINCUBATE_DATA_HEATSTATUS, "1");
    }
    else
    {
        heatFlag=0;
        digitalWrite(HEAT_PIN, LOW);		//关闭加热器
        digitalWrite(HEAT_FUN_PIN, LOW);	//关闭加热器风扇
        IntoRobot.publish(EGGINCUBATE_DATA_HEATSTATUS, "0");
    }
}

//通风风扇控制回调
void funSwitchCb(uint8_t * payload, uint32_t len)
{
    if(payload[0] == '1')
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

//翻蛋控制回调
void turnEggSwitchCb(uint8_t * payload, uint32_t len)
{
    if(payload[0] == '1')
    {
        IntoRobot.publish(EGGINCUBATE_DATA_ROLLSTATUS, "1");
        turnEgg();
        IntoRobot.publish(EGGINCUBATE_DATA_ROLLSTATUS, "0");
    }
}

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

void setup()
{
    //灯初始化
    strip.begin();
    set_bright(255);
    strip.show();
    //dht22初始化
    dht.begin();
    //控制PIN初始化
    pinMode(HEAT_PIN, OUTPUT);
    pinMode(HEAT_FUN_PIN, OUTPUT);
    pinMode(AIR_FUN_PIN, OUTPUT);
    digitalWrite(HEAT_PIN, LOW);
    digitalWrite(HEAT_FUN_PIN, LOW);
    digitalWrite(AIR_FUN_PIN, LOW);
    //舵机定义
    myservo.attach(SERVO_PIN);
    //初始化屏 LCD 128*64
    LCDA.Initialise();
    delay(100);
    //开机显示图片
    LCDA.DrawFullScreen(logo);
    delay(1000);
    LCDA.Clear();
    delay(100);
    memset(temp, 0, sizeof(temp));
    strcpy(temp, "    incubator    ");
    LCDA.DisplayString(0, 0, (uint8_t *)temp, strlen(temp));
    delay(100);
    //温度PID控制
    windowStartTime = millis();
    Setpoint = 38;
    myPID.SetOutputLimits(0, WindowSize);
    myPID.SetSampleTime(5000);	//5秒采样时间
    myPID.SetMode(AUTOMATIC);
    //接收灯光、加热、风扇、翻蛋控制
    IntoRobot.subscribe(EGGINCUBATE_CMD_LIGHTMODE, NULL, neopixelControlCb);
    IntoRobot.subscribe(EGGINCUBATE_CMD_HEATSWITCH, NULL, heatSwitchCb);
    IntoRobot.subscribe(EGGINCUBATE_CMD_FANSWITCH, NULL, funSwitchCb);
    IntoRobot.subscribe(EGGINCUBATE_CMD_ROLLSWITCH, NULL, turnEggSwitchCb);
    getVaueTimer=timerGetId();
    turnEggTimer=timerGetId();
}

void loop()
{
    if (timerIsEnd(getVaueTimer,1000))
    {
        getVaueTimer=timerGetId();
        tempcelcius = dht.getTempCelcius();
        if(tempcelcius==tempcelcius) //输出不NAN
        {
            Input=tempcelcius;
            IntoRobot.publish(EGGINCUBATE_DATA_TEMPERATURE, tempcelcius);  //上送温度数据
            humidity = dht.getHumidity();
            IntoRobot.publish(EGGINCUBATE_DATA_HUMIDITY, humidity);		   //上送湿度数据
            //LCD 数据显示
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "    T=%.2fc    ", tempcelcius);
            LCDA.DisplayString(1, 0, (uint8_t *)temp, strlen(temp));
            delay(100);
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "    H=%.2f%%    ", humidity);
            LCDA.DisplayString(2, 0, (uint8_t *)temp, strlen(temp));
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
            digitalWrite(HEAT_FUN_PIN, LOW);
            IntoRobot.publish(EGGINCUBATE_DATA_HEATSTATUS, "0");
            heatFlag=0;
        }
    }
    else
    {
        if(heatFlag==0)
        {
            digitalWrite(HEAT_PIN, HIGH);
            digitalWrite(HEAT_FUN_PIN, HIGH);
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

