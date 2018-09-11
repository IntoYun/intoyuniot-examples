/*
*  产品名称：demo-common-custom
*  产品描述：undefined
*  说    明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。此框架包括数据点的定义和读写
*  模板版本：v1.4
*/

#include "project_config.h"

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号

#define APP_TX_DUTYCYCLE                          10000 //定义发送周期时间. 单位[ms]。

#define LEDPIN                                    LED_BUILTIN      //定义灯泡控制引脚

uint32_t txNextPacketTimerID;
bool isFirstSend = true;

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event) {
        case event_cloud_comm:
            switch(param) {
                case ep_cloud_comm_data:
                    /*************此处修改和添加用户控制代码*************/
                    //data为接收数据缓存指针，datalen为接收数据长度
                    if(datalen == 1) {
                        switch(data[0]) {
                            case 0x00:
                                digitalWrite(LEDPIN, HIGH);   // 关闭灯泡
                                break;
                            case 0x01:
                                digitalWrite(LEDPIN, LOW);    // 打开灯泡
                                break;
                            default:
                                break;
                        }
                    }
                    Cloud.sendCustomData(data, datalen);
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
                Cloud.sendCustomData("\x00", 1);
            }
            txNextPacketTimerID = timerGetId();
            //更新数据点数据（数据点具备上送属性）
        }
    }
    /*******************************************************/
}

void init_before_setup(void)
{
    System.disableFeature(SYSTEM_FEATURE_DATA_PROTOCOL_ENABLED);        //关闭数据处理
}

STARTUP( init_before_setup() );

void setup()
{
    userInit();
}

void loop()
{
    //loop 尽量不要阻塞
    userHandle();
}

