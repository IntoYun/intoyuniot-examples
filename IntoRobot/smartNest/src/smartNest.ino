/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 时间:  03-30-15
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 时间:  03-30-15
 ************************************************************************
 功能描述：
 鸟笼：智能鸟笼，不仅具有检测鸟是否存在功能，而且还有检测环境温湿度，
 光照强度，空气PM2.5颗粒浓度功能

 所需器件:
 1.E18-D80NK 红外光电开关 漫反射式避障传感器模块
 2.DHT11 温湿度传感器模块
 3.GY-30 数字光强度光照传感器
 4.GP2Y10 PM2.5浓度传感器模块

 接线说明：
 HC-SR501                     核心板
 1.VCC(靠近电感)              +5V
 2.GND                        GND
 3.OUT(中间)                  D0

 DH11
 1.VCC                        +3.3V
 2.GND                        GND
 3.DATA                       D3

 GY-30
 1.VCC                       +3.3V
 2.GND                        GND
 3.SDA                        I2C(Wire组)的SDA
 4.SCL                        I2C(Wire组)的SCL

 GP2Y10
 VCC	                        3V3
 GND                         GND
 LED                         D4
 OUT                         A0
 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 请注意核心板的I2C引脚区别，避免接线错误。
 */

#include <IntoRobot_DHT.h>
#include <gy30.h>
#include <gp2y10.h>

// 鸟笼应用topic定义
#define BIRDCAGE_DATA_STATE                 "channel/birdcage_0/data/status"                // 鸟笼是否有鸟
#define BIRDCAGE_DATA_TEMPERATURE           "channel/birdcage_0/data/temperature"           // 温度
#define BIRDCAGE_DATA_HUMIDITY              "channel/birdcage_0/data/humidity"              // 湿度
#define BIRDCAGE_DATA_ILLUMINATION          "channel/birdcage_0/data/illumination"          // 光照强度
#define BIRDCAGE_DATA_AIRDUSTCONCENTRATION  "channel/birdcage_0/data/airdustconcentration"  // PM2.5浓度

#define InfraredSensorINPUT   D0
#define DHT_TYPE		DHT11
#define DHT11_PIN 		D3
#define GP2Y10_LED_PIN 	D4
#define GP2Y10_OUT_PIN 	A0

GY30 gy30;
IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);
GP2Y10 pm25 = GP2Y10(GP2Y10_OUT_PIN,GP2Y10_LED_PIN);
int birdStatus = 0;
void setup()
{
    //初始化
    Wire.begin();
    delay(100);
    gy30.begin();
    dht11.begin();
    pm25.begin();
    pinMode(InfraredSensorINPUT, INPUT);
}

void loop()
{
    // 当鸟进入监测范围，InfraredSensorINPUT管脚电平为高，当鸟离开，电平管脚变为低
    if(digitalRead(InfraredSensorINPUT) == HIGH)
    {
        // 有鸟状态
        birdStatus = 1;
    }
    else
    {
        // 无鸟状态
        birdStatus = 0;
    }

    IntoRobot.publish(BIRDCAGE_DATA_STATE, birdStatus);
    IntoRobot.publish(BIRDCAGE_DATA_TEMPERATURE, dht11.getTempCelcius());	//上送温度值
    IntoRobot.publish(BIRDCAGE_DATA_HUMIDITY, dht11.getHumidity());	//上送湿度值
    IntoRobot.publish(BIRDCAGE_DATA_ILLUMINATION, gy30.Read());	//上送光照强度值
    IntoRobot.publish(BIRDCAGE_DATA_AIRDUSTCONCENTRATION, pm25.CalculatedConcentration());	//上送PM2.5浓度
    delay(2000);
}

