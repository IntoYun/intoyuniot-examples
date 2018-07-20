/*
 *  产品名称：花园管家
 *  产品描述：可远程监控环境温湿度，光照强度以及土壤湿度和实时控制浇水。
 *  说    明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。此框架包括数据点的定义和读写
 *  模板版本：v1.4
 */

#include "project_config.h"

/*该头文件引用为载入库IntoYunIot_SHT2x时自动添加.*/
#include <IntoYunIot_SHT2x.h>

/*该头文件引用为载入库GY30时自动添加.*/
#include <gy30.h>

/*该头文件引用为载入库YL38时自动添加.*/
#include <yl38.h>

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号
PRODUCT_HARDWARE_VERSION(HARDWARE_VERSION_DEF)    // 产品硬件版本号

#define DPID_DOUBLE_TEMPATURE                     1  //数值型            温度
#define DPID_DOUBLE_HUMIDITY                      2  //数值型            湿度
#define DPID_DOUBLE_ILLUMINATION                  3  //数值型            光照强度
#define DPID_INT32_SOIL_HUMIDITY                  4  //数值型            土壤湿度
#define DPID_BOOL_WATER_SWITCH                    5  //布尔型            浇水开关

#define WATER_SWITCH_PIN    D3
#define SOIL_SENSOR_PIN     A0

double dpDoubleTempature = 0.00;                  // 温度
double dpDoubleHumidity = 0.00;                   // 湿度
double dpDoubleIllumination = 0.00;               // 光照强度
int32_t dpInt32Soil_humidity = 0;                 // 土壤湿度
bool dpBoolWater_switch;                          // 浇水开关


uint32_t timerID;
GY30 gy30;
IntoYunIot_SHT2x SHT2x;
YL38 yl38 = YL38(SOIL_SENSOR_PIN);

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event) {
        case event_cloud_comm:
            switch(param) {
                case ep_cloud_comm_data:
                    /*************此处修改和添加用户控制代码*************/
                    if (RESULT_DATAPOINT_NEW == Cloud.readDatapoint(DPID_BOOL_WATER_SWITCH, dpBoolWater_switch)) {
                        //浇水开关控制实现
                        if(true == dpBoolWater_switch) {
                            digitalWrite(WATER_SWITCH_PIN, LOW);
                            dpBoolWater_switch = true;
                        } else {
                            digitalWrite(WATER_SWITCH_PIN, HIGH);
                            dpBoolWater_switch = false;
                        }
                    }

                    /*******************************************************/
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}

void SystemWakeUpHandler(void)
{
    //用户代码　唤醒后需要重新初始化外设接口
}

void userInit(void)
{
    pinMode(WATER_SWITCH_PIN,OUTPUT);
    digitalWrite(WATER_SWITCH_PIN,HIGH);

    //定义数据点事件
    System.on(event_cloud_data, system_event_callback);

    //根据网关参数具体设置
    LoRaWan.setDataRate(DR_3);
    LoRaWan.setChannelStatus(0, false);               //关闭通道0 频率固定：433175000
    LoRaWan.setChannelStatus(1, false);               //关闭通道1 频率固定：433375000
    LoRaWan.setChannelStatus(2, true);                //打开通道2 频率固定：433575000
    LoRaWan.setChannelFreq(2, 433575000);             //设置通道2频率
    LoRaWan.setChannelDRRange(2, DR_3, DR_3);         //设置通道2速率范围
    LoRaWan.setChannelStatus(3, false);               //关闭通道3
    //定义产品数据点
    Cloud.defineDatapointNumber(DPID_DOUBLE_TEMPATURE, DP_PERMISSION_UP_ONLY, -100, 100, 2, 0); //温度
    Cloud.defineDatapointNumber(DPID_DOUBLE_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 2, 0); //湿度
    Cloud.defineDatapointNumber(DPID_DOUBLE_ILLUMINATION, DP_PERMISSION_UP_ONLY, 0, 65535, 2, 0); //光照强度
    Cloud.defineDatapointNumber(DPID_INT32_SOIL_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0); //土壤湿度
    Cloud.defineDatapointBool(DPID_BOOL_WATER_SWITCH, DP_PERMISSION_DOWN_ONLY, false); //浇水开关

    /*************此处修改和添加用户初始化代码**************/
    gy30.begin();
    yl38.begin();
    delay(100);
    timerID = timerGetId();

    /*******************************************************/
}

void userHandle (void)
{
    /*************此处修改和添加用户处理代码****************/
    if(Cloud.connected() < 0) { //未连接
        if(Cloud.connect(JOIN_OTAA, 400) == 0) {
            LoRaWan.setMacClassType(CLASS_C);    //入网成功后设置为A/C类
        }
    } else if(Cloud.connected() == 0) { //连接上
        if(timerIsEnd(timerID, 600000)) { //处理间隔  用户可自行更改
            timerID = timerGetId();
            dpDoubleTempature = SHT2x.readT();
            dpDoubleHumidity = SHT2x.readRH();
            dpDoubleIllumination = gy30.Read();
            dpInt32Soil_humidity = yl38.CalculateHumidity();

            //更新数据点数据（数据点具备上送属性）
            Cloud.writeDatapoint(DPID_DOUBLE_TEMPATURE, dpDoubleTempature);
            Cloud.writeDatapoint(DPID_DOUBLE_HUMIDITY, dpDoubleHumidity);
            Cloud.writeDatapoint(DPID_DOUBLE_ILLUMINATION, dpDoubleIllumination);
            Cloud.writeDatapoint(DPID_INT32_SOIL_HUMIDITY, dpInt32Soil_humidity);
            //发送数据点数据，建议不频繁上送数据
            Cloud.sendDatapointAll(IS_SEND_CONFIRMED_DEF, 120);
        }
    }
    /*******************************************************/
}

void setup ()
{
    userInit();
}

void loop ()
{
    //loop 尽量不要阻塞
    userHandle();
}
