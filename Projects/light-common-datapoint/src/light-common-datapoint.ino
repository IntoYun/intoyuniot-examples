/*
*  产品名称：demo-common-datapoint
*  产品描述：undefined
*  说    明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。此框架包括数据点的定义和读写
*  模板版本：v1.4
*/

#include "project_config.h"

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号

#define APP_TX_DUTYCYCLE                          10000 //定义发送周期时间. 单位[ms]。

#define DPID_BOOL_STATUS                          1 //布尔型             灯状态
#define DPID_BOOL_SWITCH                          2 //布尔型             开关

#define LEDPIN                                    LED_BUILTIN      //定义灯泡控制引脚

bool dpBoolStatus;                                // 灯状态
bool dpBoolSwitch;                                // 开关

uint32_t txNextPacketTimerID;
bool isFirstSend = true;

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event) {
        case event_cloud_comm:
            switch(param) {
                case ep_cloud_comm_data:
                    /*************此处修改和添加用户控制代码*************/
                    //开关
                    if (RESULT_DATAPOINT_NEW == Cloud.readDatapoint(DPID_BOOL_SWITCH, dpBoolSwitch)) {
                        if(dpBoolSwitch) {
                            digitalWrite(LEDPIN, LOW);    // 打开灯泡
                            dpBoolStatus = true;
                        } else {
                            digitalWrite(LEDPIN, HIGH);   // 关闭灯泡
                            dpBoolStatus = false;
                        }
                        Cloud.writeDatapoint(DPID_BOOL_STATUS, dpBoolStatus);
                    }
                    Cloud.sendDatapointAll();
                    /****************************************************/
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void userInit(void)
{
    //定义数据点事件
    System.on(event_all, system_event_callback);

    //设置数据上报策略
    Cloud.datapointControl(DP_TRANSMIT_MODE_MANUAL);

    //定义产品数据点
    Cloud.defineDatapointBool(DPID_BOOL_STATUS, DP_PERMISSION_UP_ONLY, false); //灯状态
    Cloud.defineDatapointBool(DPID_BOOL_SWITCH, DP_PERMISSION_UP_DOWN, false); //开关

    /*************此处修改和添加用户初始化代码**************/
    txNextPacketTimerID = timerGetId();
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);    // 默认关闭灯泡

    /*******************************************************/
}

void userHandle(void)
{
    /*************此处修改和添加用户处理代码****************/
    if(Cloud.connected()) {
        if(isFirstSend || timerIsEnd(txNextPacketTimerID, APP_TX_DUTYCYCLE)) { //处理间隔(单位:ms)，用户可自行更改
            if(isFirstSend) {
                isFirstSend = false;
                Cloud.sendDatapointAll();
            }
            txNextPacketTimerID = timerGetId();
            //更新数据点数据（数据点具备上送属性）
        }
    }
    /*******************************************************/
}

void setup()
{
    userInit();
}

void loop()
{
    //loop 尽量不要阻塞
    userHandle();
}

