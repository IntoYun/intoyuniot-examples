/*
*  产品名称：花园管家
*  产品描述：检测土壤湿度，控制浇水
*  说   明：该代码为平台根据产品内容自动生产的模板架构，您可以在此基础上开发。
*  模板版本：v1.3

引脚接法：

YL38(土壤湿度传感器)
VCC----3.3V
GND----GND
AO-----A0

浇水开关
switch----D0
*/

#include <yl38.h>

PRODUCT_ID(qWcOC68fXe7qc1ab);                     // 产品标识
PRODUCT_SECRET(d7e916d8a8a4dc4542723a73b492fe07); // 产品密钥
PRODUCT_VERSION(1);                               // 产品版本

#define DPID_NUMBER_HUMIDITY                      1  //数值型            土壤湿度
#define DPID_BOOL_SWITCH                          2  //布尔型            浇水开关

#define YL38_PIN        A0
#define WATER_SWITCH    D7

static enum eDeviceState
{
    DEVICE_STATE_IDLE,
    DEVICE_STATE_JOIN,
    DEVICE_STATE_SEND,
    DEVICE_STATE_CYCLE,
}deviceState;

int dpIntHumidity;                                // 土壤湿度
bool dpBoolSwitch;                                // 浇水开关

YL38 yl38 = YL38(YL38_PIN);

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen) {
	if ((event == event_cloud_data) && (param == ep_cloud_data_datapoint)) {
		//浇水开关
		if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_BOOL_SWITCH, dpBoolSwitch)) {
			//用户代码
            if(true == dpBoolSwitch)
            {
                digitalWrite(WATER_SWITCH,LOW);//打开开关
            }
            else
            {
                digitalWrite(WATER_SWITCH,HIGH);
            }
		}

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
                    LoRaWan.setMacClassType(CLASS_C);//入网成功后设置为C类
                    deviceState = DEVICE_STATE_SEND;
                    Serial.println("lorawan event join success");
                    break;

                case ep_lorawan_join_fail: //入网失败
                    deviceState = DEVICE_STATE_JOIN;
                    Serial.println("lorawan event join fail");
                    break;

                case ep_lorawan_send_success:
                    deviceState = DEVICE_STATE_CYCLE;
                    Serial.println("lorawan event send success");
                    break;

                case ep_lorawan_send_fail:
                    deviceState = DEVICE_STATE_CYCLE;
                    Serial.println("lorawan event send fail");
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
    switch(deviceState)
    {
        case DEVICE_STATE_JOIN:
            Cloud.connect(JOIN_OTAA,0);
            deviceState = DEVICE_STATE_IDLE;
            break;

        case DEVICE_STATE_SEND:
	        //发送数据点 （数据点具备上送属性）
	        dpIntHumidity = yl38.CalculateHumidity();
	        IntoRobot.writeDatapoint(DPID_NUMBER_HUMIDITY, dpIntHumidity);
            if(Cloud.sendDatapointAll(false,0) == -1){ //发送忙
                deviceState = DEVICE_STATE_CYCLE;
            }else{
                deviceState = DEVICE_STATE_IDLE;
            }
            break;

        case DEVICE_STATE_IDLE:
            break;

        case DEVICE_STATE_CYCLE:
            delay(60000);
            deviceState = DEVICE_STATE_SEND;
            break;

        default:
            break;
    }
}

void setup () {
    Serial.begin(115200);
    yl38.begin();
    pinMode(WATER_SWITCH,OUTPUT);
    System.on(event_lorawan_status, &lorawan_event_callback);
	System.on(event_cloud_data, system_event_callback);
	IntoRobot.defineDatapointNumber(DPID_NUMBER_HUMIDITY, DP_PERMISSION_UP_ONLY, 0, 100, 0, 0); //土壤湿度
	IntoRobot.defineDatapointBool(DPID_BOOL_SWITCH, DP_PERMISSION_DOWN_ONLY, false); //浇水开关
    //设置参数
    LoRaWan.setDataRate(DR_3);
    LoRaWan.setChannelDRRange(2,DR_3,DR_3);
    LoRaWan.setRX2Params(DR_3,434665000);
    LoRaWan.setChannelStatus(0,false);
    LoRaWan.setChannelStatus(1,false);
    //开始入网
    uint32_t joinDelay = (uint32_t)random(0,10000);
    delay(joinDelay);
    deviceState = DEVICE_STATE_JOIN;
}

void loop () {
	userHandle();
}
