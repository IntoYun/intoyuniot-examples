/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 时间:  03-30-15
************************************************************************
功能描述：
空气检测仪：检测空气温度、湿度、灰尘浓度以及光照强度

所需器件:
1. DHT11 温湿度传感器模块
2. GY30  光照传感器模块
3. GP2Y10 PM2.5灰尘传感器模块

接线说明
DHT11          核心板      
VCC            3V3       
GND            GND       
DATA           D3        

GY30                 
VCC            3V3       
GND            GND       
SDA            I2C(Wire组)的SDA        
SCL            I2C(Wire组)的SCL        

GP2Y10               
VCC	           3V3       
GND            GND       
LED            D0        
OUT            A0     

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。 
请注意核心板I2C引脚区别，避免接线错误
*/

#include <gy30.h> 
#include <IntoRobot_DHT.h>
#include <gp2y10.h>

//空气检测应用topic定义
#define AIRMONITORING_DATA_AIRTEMP              "channel/airMonitoring_0/data/airTemp"       //温度
#define AIRMONITORING_DATA_AIRHUMIDITY          "channel/airMonitoring_0/data/airHumidity"   //湿度
#define AIRMONITORING_DATA_ILLUMINATION         "channel/airMonitoring_0/data/illumination"  //光照强度
#define AIRMONITORING_DATA_CONCENTRATION        "channel/airMonitoring_0/data/concentration" //灰尘浓度

#define DHT_TYPE  DHT11
#define DHT11_PIN D3
#define GP2Y10_LED_PIN D0
#define GP2Y10_OUT_PIN A0


IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);
GP2Y10 pm25 = GP2Y10(GP2Y10_OUT_PIN,GP2Y10_LED_PIN);  
GY30 gy30;  

void setup()
{
	//初始化
	dht11.begin(); 
	pm25.begin(); 
	Wire.begin(); 
	delay(100);
	gy30.begin(); 
}

void loop()
{
	IntoRobot.publish(AIRMONITORING_DATA_AIRTEMP, dht11.getTempCelcius()); //上送温度
	IntoRobot.publish(AIRMONITORING_DATA_AIRHUMIDITY, dht11.getHumidity()); //上送湿度
	IntoRobot.publish(AIRMONITORING_DATA_ILLUMINATION, gy30.Read()); //上送光照强度
	IntoRobot.publish(AIRMONITORING_DATA_CONCENTRATION, pm25.CalculatedConcentration()); //上送PM2.5值
	delay(3000);
}
