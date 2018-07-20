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

#include "project_config.h"

#include "IntoRobot_DHT.h"

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号
PRODUCT_HARDWARE_VERSION(HARDWARE_VERSION_DEF)    // 产品硬件版本号

#define DPID_NUMBER_TEMPERATURE                   1  //数值型            温度
#define DPID_NUMBER_HUMIDITY                      2  //数值型            湿度

#define DHT11_PIN   D0                           //传感器引脚定义
#define DHT_TYPE    DHT11                        //传感器类型定义


IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);

double dpDoubleTemperature;                      // 温度
int dpIntHumidity;                               // 湿度

void userHandle (void) {
    dpDoubleTemperature = dht11.getTempCelcius();
    dpIntHumidity = dht11.getHumidity();
    //发送数据点 （数据点具备上送属性）
    Cloud.writeDatapoint(DPID_NUMBER_TEMPERATURE, dpDoubleTemperature);
    Cloud.writeDatapoint(DPID_NUMBER_HUMIDITY, dpIntHumidity);
    //处理间隔，用户可以根据自己需求更改
    delay(3000);
}

void setup()
{
    dht11.begin();
    Cloud.defineDatapointNumber(DPID_NUMBER_TEMPERATURE, DP_PERMISSION_UP_ONLY, 0, 100, 1, 0); //温度
    Cloud.defineDatapointNumber(DPID_NUMBER_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0);    //湿度
}

void loop()
{
    userHandle();
}

