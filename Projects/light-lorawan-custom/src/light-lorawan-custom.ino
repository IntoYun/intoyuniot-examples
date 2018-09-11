
/*
*  产品名称：demo-lorawan-custom
*  产品描述：undefined
*  说    明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。此框架包括数据点的定义和读写
*  模板版本：v1.4
*/

#include "project_config.h"

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号

#define APP_RUN_DELAY_RND                         5000 //开机随机启动时间. 单位[ms]. 防止设备同时上电同时入网。
#define APP_TX_DUTYCYCLE_BASE                     60000 //定义发送周期时间. 单位[ms]。
#define APP_TX_DUTYCYCLE_RND                      6000 //定义发送时间调整随机范围. 单位[ms]。
#define APP_TX_DUTYCYCLE                          APP_TX_DUTYCYCLE_BASE + random(-APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND) //定义发送周期时间. 单位[ms]。

#define LEDPIN                                    LED_BUILTIN      //定义灯泡控制引脚

uint32_t txNextPacketTimerID;
uint32_t txDutyCycleTime; // 发送周期变量
uint32_t isTxConfirmed = APP_CONFIRMED_MSG_ON; //指示设备发送非确认包或者确认包
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
                            case 0:
                                digitalWrite(LEDPIN, HIGH);   // 关闭灯泡
                                break;
                            case 1:
                                digitalWrite(LEDPIN, LOW);    // 打开灯泡
                                break;
                            default:
                                break;
                        }
                    }
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

    //根据网关参数具体设置
    LoRaWan.setChannelStatus(0, false);               //关闭通道0 频率固定：433175000
    LoRaWan.setChannelStatus(1, false);               //关闭通道1 频率固定：433375000
    LoRaWan.setChannelStatus(2, true);                //打开通道2 频率固定：433575000
    LoRaWan.setChannelFreq(2, 433575000);             //设置通道2频率
    LoRaWan.setChannelDRRange(2, DR_3, DR_3);         //设置通道2速率范围
    LoRaWan.setChannelStatus(3, false);               //关闭通道3
    LoRaWan.setDutyCyclePrescaler(1);                 //设置占空比

    /*************此处修改和添加用户初始化代码**************/
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);    // 默认关闭灯泡

    delay(random(0, APP_RUN_DELAY_RND)); //随机延时，防止设备同时上电同时接入网络
    /*******************************************************/
}

void userHandle(void)
{
    /*************此处修改和添加用户处理代码****************/
    if(Cloud.connected() < 0) { //未连接
        if(Cloud.connect(JOIN_OTAA, 400) == 0) {
            LoRaWan.setMacClassType(CLASS_C);    //入网成功后设置为C类
            txNextPacketTimerID = timerGetId();
        }
    } else if(Cloud.connected() == 0) { //连接上
        txDutyCycleTime = APP_TX_DUTYCYCLE;
        if(timerIsEnd(txNextPacketTimerID, txDutyCycleTime)) { //处理间隔(单位: ms) 用户可自行更改
            if(isFirstSend) {
                isFirstSend = false;
                Cloud.sendCustomData("0x00", 1);
            }
            txNextPacketTimerID = timerGetId();
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

