/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  03-30-16
************************************************************************
功能描述：
智能光控灯：具有光照强度检测的智能灯，根据光强度控制灯的开关

所需器件:
1.GY-30 数字光强度光照传感器
2.LED灯泡
3.继电器模块

接线说明:
GY-30                       核心板
1.VIN                       +3.3V
2.GND                        GND
3.SDA                        I2C(Wire组)的SDA
4.SCL                        I2C(Wire组)的SCL
继电器模块
1.DC+：                      +5V
2.DC-：                      GND
3.IN：                       D0
4.NO：                       灯的正极
5.COM：                      +5V
6.NC：                       悬空
7.触发选择端：选择跳线与high短接, 即高电平触发。

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
请注意核心板的I2C引脚区别，避免接线错误。
*/

#include "project_config.h"

#include <gy30.h>

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号
PRODUCT_HARDWARE_VERSION(HARDWARE_VERSION_DEF)    // 产品硬件版本号

//定义数据点
#define DPID_BOOL_LAMP_SWITCH     1     //灯泡开关
#define DPID_BOOL_LAMP_STATUS     2     //灯泡状态
#define DPID_NUMBER_INTENSITY     3     //光强值

#define LAMP_SWITCH_PIN           D7    //定义灯泡控制引脚
#define ILLUMINATION_THRESHOLD    200   //定义光强临界值

GY30 gy30;//光照强度传感器

float lightIntensity;
bool lampSwitch;

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    // 平台下发数据点事件
    if((event == event_cloud_data) && (param == ep_cloud_data_datapoint))
    {
        if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_BOOL_LAMP_SWITCH, lampSwitch))//获取灯泡开关数据
        {
            if(true == lampSwitch)
            {
                digitalWrite(LAMP_SWITCH_PIN,LOW);//打开灯泡 请根据实际情况设置高低电平
                IntoRobot.writeDatapoint(DPID_BOOL_LAMP_STATUS, true);//写入灯泡状态开
            }
            else
            {
                digitalWrite(LAMP_SWITCH_PIN,HIGH);//关闭灯泡 请根据实际情况设置高低电平
                IntoRobot.writeDatapoint(DPID_BOOL_LAMP_STATUS, false);//写入灯泡状态关
            }
        }

    }
}

void setup()
{
    gy30.begin();
    pinMode(LAMP_SWITCH_PIN, OUTPUT);
    digitalWrite(LAMP_SWITCH_PIN, LOW);
    System.on(event_cloud_data, &system_event_callback);

    IntoRobot.defineDatapointBool(DPID_BOOL_LAMP_SWITCH, DP_PERMISSION_UP_DOWN, false); //定义灯泡数据点
    IntoRobot.defineDatapointBool(DPID_BOOL_LAMP_STATUS, DP_PERMISSION_UP_ONLY, false); //定义灯泡数据点
    IntoRobot.defineDatapointNumber(DPID_NUMBER_INTENSITY, DP_PERMISSION_UP_ONLY, 0, 10000, 2, 0); //定义光强数据点
}

void loop()
{
	float lightIntensity = gy30.Read();
    if(lightIntensity < ILLUMINATION_THRESHOLD)
    {
        digitalWrite(LAMP_SWITCH_PIN, LOW);//打开灯泡 请根据实际情况设置高低电平
        IntoRobot.writeDatapoint(DPID_BOOL_LAMP_STATUS, true);//写入数据灯泡状态开
        IntoRobot.writeDatapoint(DPID_BOOL_LAMP_SWITCH, true);//写入数据灯泡开关为开
    }
    else
    {
        digitalWrite(LAMP_SWITCH_PIN, HIGH);//关闭灯泡 请根据实际情况设置高低电平
        IntoRobot.writeDatapoint(DPID_BOOL_LAMP_STATUS, false);//写入数据灯泡状态关
        IntoRobot.writeDatapoint(DPID_BOOL_LAMP_SWITCH, false);//写入数据灯泡开关为关
    }

    IntoRobot.writeDatapoint(DPID_NUMBER_INTENSITY,lightIntensity);
    delay(3000);
}

