/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 温湿度计：检测环境温度和湿度

 所需器件:
 1.DHT11 温湿度传感器模块

 接线说明：
 DH11                         核心板
 1.VCC                        +3.3V
 2.GND                        GND
 3.DATA                       D0

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

#include <IntoRobot_DHT.h>

//温湿度计应用topic定义
#define HUMITURE_DATA_TEMPERATURE    "channel/humiture_0/data/temperature"   //空气温度
#define HUMITURE_DATA_HUMIDITY       "channel/humiture_0/data/humidity"      //空气湿度
#define DHT11_PIN   D0
#define DHT_TYPE    DHT11

IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);

void setup()
{
    //初始化
    dht11.begin();
}

void loop()
{
    IntoRobot.publish(HUMITURE_DATA_TEMPERATURE, dht11.getTempCelcius()); //上送温度值
    IntoRobot.publish(HUMITURE_DATA_HUMIDITY, dht11.getHumidity());        //上送湿度值
    delay(1000);
}

