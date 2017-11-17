/*
*  产品名称：花园管家
*  产品描述：检测土壤湿度，控制浇水
*  说   明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。
*  模板版本：v1.3

引脚接法：
SHT20(温湿度传感器)
VDD    3.3V
GND    GND
SCL    D0
SDA    D1

GY30(光照传感器)
VDD    3.3V
GND    GND
SCL    D0
SDA    D1

YL38(土壤湿度传感器)
VCC    3.3V
GND    GND
AO     A0

浇水开关
switch----D2
*/

#include "IntoYunIot_SHT2x.h"
#include "gy30.h"
#include "yl38.h"

PRODUCT_ID(BysPnpkCgHPhM1ec);                     // 产品标识
PRODUCT_SECRET(745f24b07bce12ad6eb5aa6463fd2556); // 产品密钥
PRODUCT_VERSION(1);                               // 产品版本

#define DPID_NUMBER_TEMPATURE                     1  //数值型            温度
#define DPID_NUMBER_HUMIDITY                      2  //数值型            湿度
#define DPID_NUMBER_ILLUMINATION                  3  //数值型            光照强度
#define DPID_NUMBER_SOIL_HUMIDITY                 4  //数值型            土壤湿度
#define DPID_BOOL_WATER_SWITCH                    5  //布尔型            浇水开关

#define WATER_SWITCH_PIN    D2
#define SOIL_SENSOR_PIN     A0

double dpDoubleTempature = 0.00;                         // 温度
double dpDoubleHumidity = 0.00;                          // 湿度
double dpDoubleIllumination = 0.00;                      // 光照强度
int dpIntSoil_humidity = 0;                           // 土壤湿度
bool dpBoolWater_switch;                          // 浇水开关

uint32_t timerID;
GY30 gy30;
IntoYunIot_SHT2x SHT2x;
YL38 yl38 = YL38(SOIL_SENSOR_PIN);

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen) {
    if ((event == event_cloud_data) && (param == ep_cloud_data_datapoint)) {
        //浇水开关
        if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_BOOL_WATER_SWITCH, dpBoolWater_switch)) {
            //用户代码
            if(true == dpBoolWater_switch){
                digitalWrite(WATER_SWITCH_PIN, HIGH);
                dpBoolWater_switch = true;
            }else{
                digitalWrite(WATER_SWITCH_PIN, LOW);
                dpBoolWater_switch = false;
            }
        }
    }
}

void userHandle (void) {
    if(Cloud.connected() < 0)  //未连接
    {
        if(Cloud.connect(JOIN_OTAA, 400) == 0){
            LoRaWan.setMacClassType(CLASS_C);//入网成功后设置为C类
        }
    }else if (Cloud.connected() == 0){  //连接上
        if(timerIsEnd(timerID, 15000))  //处理间隔  用户可自行更改
        {
            timerID = timerGetId();
            //发送数据点 （数据点具备上送属性）
            dpDoubleTempature = SHT2x.readT();
            dpDoubleHumidity = SHT2x.readRH();
            dpDoubleIllumination = gy30.Read();
            dpIntSoil_humidity = yl38.CalculateHumidity();
            IntoRobot.writeDatapoint(DPID_NUMBER_TEMPATURE, dpDoubleTempature);
            IntoRobot.writeDatapoint(DPID_NUMBER_HUMIDITY, dpDoubleHumidity);
            IntoRobot.writeDatapoint(DPID_NUMBER_ILLUMINATION, dpDoubleIllumination);
            IntoRobot.writeDatapoint(DPID_NUMBER_SOIL_HUMIDITY, dpIntSoil_humidity);
            Cloud.sendDatapointAll(false, 120);
        }
    }
}

void userInit(void) {

    pinMode(WATER_SWITCH_PIN,OUTPUT);
    digitalWrite(WATER_SWITCH_PIN,LOW);

    System.on(event_cloud_data, system_event_callback);
    //根据网关参数具体设置
    LoRaWan.setDataRate(DR_3);
    LoRaWan.setChannelDRRange(2, DR_3, DR_3);
    LoRaWan.setChannelStatus(0, false);       //关闭通道0
    LoRaWan.setChannelStatus(1, false);       //关闭通道1

    IntoRobot.defineDatapointNumber(DPID_NUMBER_TEMPATURE, DP_PERMISSION_UP_ONLY, -100, 100, 2, 0); //温度
    IntoRobot.defineDatapointNumber(DPID_NUMBER_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 2, 0); //湿度
    IntoRobot.defineDatapointNumber(DPID_NUMBER_ILLUMINATION, DP_PERMISSION_UP_ONLY, 0, 65535, 2, 0); //光照强度
    IntoRobot.defineDatapointNumber(DPID_NUMBER_SOIL_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0); //土壤湿度
    IntoRobot.defineDatapointBool(DPID_BOOL_WATER_SWITCH, DP_PERMISSION_DOWN_ONLY, false); //浇水开关

    gy30.begin();
    yl38.begin();
    delay(100);
    timerID = timerGetId();
}

void setup(){
    userInit();
}

void loop () {
    userHandle();
}
