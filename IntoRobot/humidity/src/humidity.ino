/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
湿度计：检测环境湿度

所需器件:
1. DHT11 温湿度传感器模块

接线说明
DHT11          核心板
VCC            3V3
GND            GND
DATA           D0

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#include <IntoRobot_DHT.h>

//湿度计应用topic定义
#define HUMIDITY_DATA_HUMIDITY    "channel/humidity_0/data/humidity"   //空气湿度

#define DHT11_PIN   D0
#define DHT_TYPE    DHT11

IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);

void setup()
{
	dht11.begin(); // 初始化
}

void loop()
{
	IntoRobot.publish(HUMIDITY_DATA_HUMIDITY, dht11.getHumidity()); //上送湿度
	delay(3000);
}
