/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
花园管家：检测花园环境温湿度、光照强度、土壤湿度，同时可以控制浇水

所需器件:
1. DHT11 温湿度传感器模块
2. YL38 土壤湿度检测传感器模块
3. GY30 光照传感器模块
4. 电磁阀

接线说明
YL38            核心板
+               VIN
-               GND
S               A0

DHT11
VCC             3V3
GND             GND
DATA            D0

GY30
VCC             3V3
GND             GND
SDA             I2C(Wire组)的SDA引脚
SCL             I2C(Wire组)的SCL引脚
AD0与GND在模块上短接在一起

继电器模块
DC+             5V0
DC-             GND
IN              D3

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
请注意核心板的I2C引脚区别，避免接线错误。
*/

#include <gy30.h>
#include <IntoRobot_DHT.h>
#include <yl38.h>

// 花盆监护应用topic定义
#define FLOWERPOT_DATA_AIRTEMP          "channel/flowerPot_0/data/airTemp"      //空气温度
#define FLOWERPOT_DATA_AIRHUMIDITY      "channel/flowerPot_0/data/airHumidity"  //空气湿度
#define FLOWERPOT_DATA_SOILHUMIDITY     "channel/flowerPot_0/data/soilHumidity" //土壤湿度
#define FLOWERPOT_DATA_ILLUMINATION     "channel/flowerPot_0/data/illumination" //光照强度
#define FLOWERPOT_CMD_WATERING          "channel/flowerPot_0/cmd/control"      //浇水开关
#define FLOWERPOT_DATA_STATUS           "channel/flowerPot_0/data/status"       //浇水状态

#define  WATERING_SWITCH_PIN    D3 //浇水开关引脚
#define  DHT_TYPE   DHT11
#define  DHT11_PIN  D0
#define  YL38_PIN   A0

IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE); //温湿度传感器
YL38 yl38 = YL38(YL38_PIN);     //土壤湿度传感器
GY30 gy30;                //光照强度传感器

uint8_t   wateringDelay;  //浇水时间
uint8_t   wateringFlag;   //浇水标志
uint32_t  wateringTimer;  //浇水定时器

//花盆浇水回调
void flowerPotWateringCb(uint8_t *payload, uint32_t len)
{
	uint8_t wateringStatus;
    aJsonClass aJson;
	aJsonObject *root = aJson.parse((char *)payload);
	if(root == NULL)
	{
	    aJson.deleteItem(root);
		return;
	}
	
	aJsonObject *_waterCmd = aJson.getObjectItem(root, "watering");
	if(_waterCmd == NULL)
	{
		aJson.deleteItem(root);
		return;    
	}
	
	aJsonObject *_waterStatus = aJson.getObjectItem(_waterCmd, "status");
	if(_waterStatus == NULL)
	{
	  	aJson.deleteItem(root);
		return;  
	}
	wateringStatus = _waterStatus->valueint;

	aJsonObject *_waterTime = aJson.getObjectItem(_waterCmd, "time");
	if(_waterTime == NULL)
	{
	  	aJson.deleteItem(root);
		return;  
	}
	wateringDelay = _waterTime->valueint;
	aJson.deleteItem(root);

	if(wateringStatus)
	{
		digitalWrite(WATERING_SWITCH_PIN, HIGH); //打开浇水
		IntoRobot.publish(FLOWERPOT_DATA_STATUS,"1");
		if(wateringDelay != 0)
		{
			wateringFlag = 1;
			wateringTimer = timerGetId();
		}
		else
		{
			wateringFlag = 0;
		}
	}
	else
	{
		digitalWrite(WATERING_SWITCH_PIN, LOW); //关闭浇水
		IntoRobot.publish(FLOWERPOT_DATA_STATUS,"0");
		wateringFlag = 0;
	}
}

void setup()
{
    //初始化
	yl38.begin();
	dht11.begin();
	Wire.begin();
	delay(100);
	gy30.begin();
	pinMode(WATERING_SWITCH_PIN, OUTPUT);
	//接受浇水指令
	IntoRobot.subscribe(FLOWERPOT_CMD_WATERING, NULL, flowerPotWateringCb);
}

void loop()
{
	IntoRobot.publish(FLOWERPOT_DATA_AIRTEMP, dht11.getTempCelcius());      //上送温度
	IntoRobot.publish(FLOWERPOT_DATA_AIRHUMIDITY, dht11.getHumidity());      //上送湿度
	IntoRobot.publish(FLOWERPOT_DATA_ILLUMINATION, gy30.Read());              //上送光照强度
	IntoRobot.publish(FLOWERPOT_DATA_SOILHUMIDITY, yl38.CalculateHumidity()); //上送土壤湿度

	if(wateringFlag && (timerIsEnd(wateringTimer,wateringDelay*60000)))
	{
		digitalWrite(WATERING_SWITCH_PIN, LOW); //花盆浇水时间到，关闭浇水
		IntoRobot.publish(FLOWERPOT_DATA_STATUS,"0");
		wateringFlag = 0;
	}

	delay(2000);
}
