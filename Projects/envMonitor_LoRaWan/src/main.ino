/*
 *  产品名称：环境监测
 *  产品描述：监测环境温湿度，光照强度和灰尘浓度
 *  说    明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。此框架包括数据点的定义和读写
 *  模板版本：v1.4
 *  开 发 板：Ant
 *
 *  引脚接法：
 *
 *  DHT11(温湿度传感器)
 *  VDD-----3.3V
 *  DATA----D2
 *  GND-----GND
 *
 *  GY30(光照传感器)
 *  VCC----3.3V
 *  GND----GND
 *  SCL----D0
 *  SDA----D1
 *
 *  GP2Y1051AU0f(PM2.5灰尘传感器)
 *  VDD----5V
 *  GND----GND
 *  TXD----RXD
 */

#include "project_config.h"

/*该头文件引用为载入库IntoRobot_DHT时自动添加.*/
#include <IntoRobot_DHT.h>

/*该头文件引用为载入库GY30时自动添加.*/
#include <gy30.h>

PRODUCT_ID(PRODUCT_ID_DEF)                        // 产品标识
PRODUCT_SECRET(PRODUCT_SECRET_DEF)                // 产品密钥
PRODUCT_SOFTWARE_VERSION(SOFTWARE_VERSION_DEF)    // 产品软件版本号
PRODUCT_HARDWARE_VERSION(HARDWARE_VERSION_DEF)    // 产品硬件版本号

#define DPID_DOUBLE_TEMPERATURE                   1  //数值型            环境温度
#define DPID_INT32_HUMIDITY                       2  //数值型            环境湿度
#define DPID_DOUBLE_ILLUMINATION                  3  //数值型            光照强度
#define DPID_DOUBLE_PM25                          4  //数值型            灰尘浓度

double dpDoubleTemperature;                       // 环境温度
int32_t dpInt32Humidity;                          // 环境湿度
double dpDoubleIllumination;                      // 光照强度
double dpDoublePM25;                              // 灰尘浓度

uint32_t timerID;

uint8_t datBuffer[7] = {0}; //pm2.5数据缓冲区
uint8_t datLength = 0;      //pm2.5数据长度


IntoRobot_DHT dht11(D2,DHT11);
GY30 gy30;

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event) {
        case event_cloud_comm:
            switch(param) {
                case ep_cloud_comm_data:
                    /*************此处修改和添加用户控制代码*************/
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
    if(Serial.isEnabled()) {
        Serial.end();
    }

    Serial.begin(2400);
}

double getPM25(void)
{
    while(1) {
        while (Serial.available()){//开始接收数据
            datBuffer[datLength] = (unsigned char)Serial.read();
            if(datBuffer[0] != 170) {//判断起始位
                datLength = 0;
                break;
            } else {
                if(++datLength == 7){//接收数据完毕
                    datLength = 0;
                    if((datBuffer[0] == 170) && (datBuffer[6] == 255)) {
                        return (float)(datBuffer[1]*256 + datBuffer[2])*5/1024*800;
                    } else {
                        delay(100); //重新接收数据
                    }
                }
            }
        }
    }
}

void userInit(void)
{
    //定义数据点事件
    System.on(event_cloud_data, system_event_callback);

    Serial.begin(2400);
    delay(100);
    gy30.begin();
    dht11.begin();

    //根据网关参数具体设置
    LoRaWan.setDataRate(DR_3);
    LoRaWan.setChannelStatus(0, false);               //关闭通道0 频率固定：433175000
    LoRaWan.setChannelStatus(1, false);               //关闭通道1 频率固定：433375000
    LoRaWan.setChannelStatus(2, true);                //打开通道2 频率固定：433575000
    LoRaWan.setChannelFreq(2, 433575000);             //设置通道2频率
    LoRaWan.setChannelDRRange(2, DR_3, DR_3);         //设置通道2速率范围
    LoRaWan.setChannelStatus(3, false);               //关闭通道3
    //定义产品数据点
    Cloud.defineDatapointNumber(DPID_DOUBLE_TEMPERATURE, DP_PERMISSION_UP_ONLY, -100, 100, 2, 0); //环境温度
    Cloud.defineDatapointNumber(DPID_INT32_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0); //环境湿度
    Cloud.defineDatapointNumber(DPID_DOUBLE_ILLUMINATION, DP_PERMISSION_UP_ONLY, 0, 60000, 2, 0); //光照强度
    Cloud.defineDatapointNumber(DPID_DOUBLE_PM25, DP_PERMISSION_UP_ONLY, 0, 1000, 2, 0); //灰尘浓度

    /*************此处修改和添加用户初始化代码**************/
    timerID = timerGetId();
    uint32_t joinDelay = (uint32_t)random(0,10000);
    delay(joinDelay);

    /*******************************************************/
}

void userHandle (void)
{
    /*************此处修改和添加用户处理代码****************/
    if(Cloud.connected() < 0)  { //未连接
        if(Cloud.connect(JOIN_OTAA, 400) == 0) {
            LoRaWan.setMacClassType(CLASS_C);    //入网成功后设置为A/C类
        }
    } else if(Cloud.connected() == 0) { //连接上
        if(timerIsEnd(timerID, 600000)) { //处理间隔  用户可自行更改
            timerID = timerGetId();
            //获取传感器数据
            dpDoubleTemperature = dht11.getTempCelcius();
            dpInt32Humidity = dht11.getHumidity();
            dpDoubleIllumination = gy30.Read();
            dpDoublePM25 = getPM25();
            //更新数据点数据（数据点具备上送属性）
            Cloud.writeDatapoint(DPID_DOUBLE_TEMPERATURE, dpDoubleTemperature);
            Cloud.writeDatapoint(DPID_INT32_HUMIDITY, dpInt32Humidity);
            Cloud.writeDatapoint(DPID_DOUBLE_ILLUMINATION, dpDoubleIllumination);
            Cloud.writeDatapoint(DPID_DOUBLE_PM25, dpDoublePM25);
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
