/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 温度计：检测环境温度

 所需器件:
 1. DHT11 温湿度传感器模块

 接线说明：
 DH11                         核心板
 1.VCC                        +3.3V
 2.GND                        GND
 3.DATA                       D0

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

#include <IntoRobot_DHT.h>

//温度计应用topic定义
#define THERMOMETER_DATA_TEMPERATURE    "channel/thermometer_0/data/temperature"  //温度数据
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
    IntoRobot.publish(THERMOMETER_DATA_TEMPERATURE, dht11.getTempCelcius()); //上送温度
    delay(3000);
}

