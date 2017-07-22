/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  03-30-16
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

#include "IntoRobot_DHT.h"

PRODUCT_ID(WP6KsBxqRPM9x1ab)                     //产品ID
PRODUCT_SECRET(e964ba2d7ebdfbf368ba3168aafd55cb) //产品密钥
PRODUCT_VERSION(1)                               //产品版本号


//定义数据点
#define DPID_NUMBER_TEMPERATURE             1    //温度
#define DPID_NUMBER_HUMIDITY                2    //湿度

#define DHT11_PIN   D0                      //传感器引脚定义
#define DHT_TYPE    DHT11                   //传感器类型定义


IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);

float temperature;
float humidity;

void setup()
{
    dht11.begin();
    IntoRobot.defineDatapointNumber(DPID_NUMBER_TEMPERATURE, DP_PERMISSION_UP_ONLY, 0, 100, 1, 0); //定义温度数据点
    IntoRobot.defineDatapointNumber(DPID_NUMBER_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0);    //定义湿度数据点
}

void loop()
{
    temperature = dht11.getTempCelcius();
    humidity = dht11.getHumidity();

    IntoRobot.writeDatapoint(DPID_NUMBER_TEMPERATURE, temperature);
    IntoRobot.writeDatapoint(DPID_NUMBER_HUMIDITY, humidity);
    delay(3000);
}

