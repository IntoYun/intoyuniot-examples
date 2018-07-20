/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  03-30-16
************************************************************************
功能描述：
智能灯：控制灯的开关

所需器件:
采用板子上面自带的例子灯

接线说明

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#include "project_config.h"

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号
PRODUCT_HARDWARE_VERSION(HARDWARE_VERSION_DEF)    // 产品硬件版本号

//定义数据点
#define DPID_BOOL_SWITCH                 1        //灯泡开关
#define DPID_BOOL_LIGHT_STATUS           2        //灯泡亮灭状态

#define LEDPIN    LED_USER    //例子灯

bool LightSwitch;
bool LightStatus;

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event) {
        case event_cloud_comm:
            switch(param) {
                case ep_cloud_comm_data:
                    //灯泡控制
                    if (RESULT_DATAPOINT_NEW == Cloud.readDatapoint(DPID_BOOL_SWITCH, LightSwitch)) {
                        if(true == LightSwitch) {
                            digitalWrite(LEDPIN,LOW);//打开灯泡 请根据实际情况设置高低电平
                            Cloud.writeDatapoint(DPID_BOOL_LIGHT_STATUS, true);//写入数据灯泡状态开
                        } else {
                            digitalWrite(LEDPIN,HIGH);//关闭灯泡 请根据实际情况设置高低电平
                            Cloud.writeDatapoint(DPID_BOOL_LIGHT_STATUS, false);//写入数据灯泡状态关
                        }
                    }
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(LEDPIN, OUTPUT);
    System.on(event_cloud_data, &system_event_callback);

    Cloud.defineDatapointBool(DPID_BOOL_SWITCH, DP_PERMISSION_UP_DOWN, false);        //灯泡开关
    Cloud.defineDatapointBool(DPID_BOOL_LIGHT_STATUS, DP_PERMISSION_UP_ONLY, false);  //灯泡亮灭状态
}

void loop()
{

}

