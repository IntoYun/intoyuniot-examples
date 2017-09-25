/*
*  产品名称：环境监测
*  产品描述：监测环境温湿度，光照强度和PM2,.5
*  说   明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。
*  模板版本：v1.3

引脚接法：

DHT11(温湿度传感器)
VDD-----3.3V
DATA----D2
GND-----GND

GY30(光照传感器)
VCC----3.3V
GND----GND
SCL----D0
SDA----D1

GP2Y1051AU0f(灰尘传感器)
VDD----5V
GND----GND
TXD----RXD
*/

#include <gy30.h>
#include <IntoRobot_DHT.h>

PRODUCT_ID(eykXmRE76yutf1b9);                     // 产品标识
PRODUCT_SECRET(e88d8e51e3f4f1b09ce7ea1ec8fc9c5b); // 产品密钥
PRODUCT_VERSION(1);                               // 产品版本

#define DPID_NUMBER_TEMPERATURE                   1  //数值型            环境温度
#define DPID_NUMBER_HUMIDITY                      2  //数值型            环境湿度
#define DPID_NUMBER_ILLUMINATION                  3  //数值型            光照强度
#define DPID_NUMBER_PM25                          4  //数值型            灰尘浓度

double dpDoubleTemperature;                       // 环境温度
int dpIntHumidity;                                // 环境湿度
double dpDoubleIllumination;                      // 光照强度
double dpDoublePM25;                              // 灰尘浓度

static enum eDeviceState
{
    DEVICE_STATE_IDLE,
    DEVICE_STATE_JOIN,
    DEVICE_STATE_SEND,
    DEVICE_STATE_SLEEP,
}deviceState;

uint8_t datBuffer[7] = {0}; //pm2.5数据缓冲区
uint8_t datLength = 0;      //pm2.5数据长度


IntoRobot_DHT dht11(PB13,DHT11);
GY30 gy30;

static void SystemWakeUpHandler(void)
{
    if(Serial.isEnabled()){
        Serial.end();
    }

    if(Serial1.isEnabled()){
        Serial1.end();
    }
    Serial1.begin(115200);
    Serial.begin(2400);
    Serial1.println("System Wakeup!!!");
    if(Cloud.connected() == 0){
        deviceState = DEVICE_STATE_SEND;
    }else{
        deviceState = DEVICE_STATE_JOIN;
    }
}

double getPM25(void)
{
    while(1){
        while (Serial.available()){//开始接收数据
            datBuffer[datLength] = (unsigned char)Serial.read();
            if(datBuffer[0] != 170){//判断起始位
                datLength = 0;
                break;
            }else{
                if(++datLength == 7){//接收数据完毕
                    datLength = 0;
                    if((datBuffer[0] == 170) && (datBuffer[6] == 255)){
                        return (float)(datBuffer[1]*256 + datBuffer[2])*5/1024*800;
                    }else{
                        delay(100); //重新接收数据
                    }
                }
            }
        } 
    }
}

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen) {
	if ((event == event_cloud_data) && (param == ep_cloud_data_datapoint)) {
	}
}

void lorawan_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event)
    {
        case event_lorawan_status:
            switch(param)
            {
                case ep_lorawan_join_success: //入网成功
                    deviceState = DEVICE_STATE_SEND;
                    Serial1.println("lorawan event joined ok");
                    break;

                case ep_lorawan_join_fail: //入网失败
                    deviceState = DEVICE_STATE_JOIN;
                    Serial1.println("lorawan event joined fail");
                    break;

                case ep_lorawan_send_success:
                    deviceState = DEVICE_STATE_SLEEP;
                    Serial1.println("lorawan event send success");
                    break;

                case ep_lorawan_send_fail:
                    deviceState = DEVICE_STATE_SLEEP;
                    Serial1.println("lorawan event send fail");
                    break;

                default:
                    break;
            }
            break;

            default:
                break;
    }
}

void userHandle (void) {
    switch(deviceState){
        case DEVICE_STATE_JOIN:
            IntoYun.connect(JOIN_OTAA,0); //开始入网
            deviceState = DEVICE_STATE_IDLE;
            break;

        case DEVICE_STATE_SEND:
            //获取传感器数据
            dpDoubleTemperature = dht11.getTempCelcius();
            dpIntHumidity = dht11.getHumidity();
            dpDoubleIllumination = gy30.Read();
            dpDoublePM25 = getPM25();
	        //发送数据点 （数据点具备上送属性）
	        IntoRobot.writeDatapoint(DPID_NUMBER_TEMPERATURE, dpDoubleTemperature);
	        IntoRobot.writeDatapoint(DPID_NUMBER_HUMIDITY, dpIntHumidity);
	        IntoRobot.writeDatapoint(DPID_NUMBER_ILLUMINATION, dpDoubleIllumination);
	        IntoRobot.writeDatapoint(DPID_NUMBER_PM25, dpDoublePM25);
	        Cloud.sendDatapointAll(false,0);
            deviceState = DEVICE_STATE_IDLE;
            break;

        case DEVICE_STATE_IDLE:
            break;

        case DEVICE_STATE_SLEEP:
            System.sleep(SystemWakeUpHandler,60); //休眠60s
            break;

        default:
            break;
    }
}

void setup () {
    Serial.begin(2400);
    Serial1.begin(115200);
    delay(100);
    gy30.begin();
    dht11.begin();
    Serial1.println("environment monitor");
    System.on(event_cloud_data, system_event_callback);//设置回调
    System.on(event_lorawan_status, &lorawan_event_callback);
    //数据点定义
    IntoRobot.defineDatapointNumber(DPID_NUMBER_TEMPERATURE, DP_PERMISSION_UP_ONLY, -100, 100, 2, 0); //环境温度
    IntoRobot.defineDatapointNumber(DPID_NUMBER_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0); //环境湿度
    IntoRobot.defineDatapointNumber(DPID_NUMBER_ILLUMINATION, DP_PERMISSION_UP_ONLY, 0, 60000, 2, 0); //光照强度
    IntoRobot.defineDatapointNumber(DPID_NUMBER_PM25, DP_PERMISSION_UP_ONLY, 0, 1000, 2, 0); //灰尘浓度

    //设置参数
    LoRaWan.setDataRate(DR_3);
    LoRaWan.setChannelDRRange(2,DR_3,DR_3);
    LoRaWan.setRX2Params(DR_3,434665000);
    LoRaWan.setChannelStatus(0,false);
    LoRaWan.setChannelStatus(1,false);

    uint32_t joinDelay = (uint32_t)random(0,10000);
    delay(joinDelay);
    deviceState = DEVICE_STATE_JOIN;
}

void loop () {
    userHandle();
}
