/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  03-30-16
************************************************************************
功能描述：
智能温控风扇：具有温湿度检测的智能风扇，可根据温度控制风扇

所需器件:
1.DHT11 温湿度传感器模块
2.风扇
3.继电器模块

接线说明:
DH11                         核心板
1.VCC                        +3.3V
2.GND                        GND
3.DATA                       D1
继电器模块
1.DC+：                      +5V
2.DC-：                      GND
3.IN：                       D0
4.NO：                       风扇的正极
5.COM：                      +5V
6.NC：                       悬空
7.触发选择端：选择跳线与high短接, 即高电平触发。
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#include <IntoRobot_DHT.h>

PRODUCT_ID(WP6KsBxqRPM9x1ab)                     //产品ID
PRODUCT_SECRET(e964ba2d7ebdfbf368ba3168aafd55cb) //产品密钥
PRODUCT_VERSION(1)                               //产品版本号

//定义数据点
#define DPID_BOOL_FAN_SWITCH     1 //风扇开关
#define DPID_BOOL_FAN_STATUS     2 //风扇状态
#define DPID_NUMBER_TEMPERATURE  3 //温度

#define DHT_TYPE                 DHT11
#define DHT11_PIN                D1
#define FAN_SWITCH_PIN           D0     // 定义风扇开关控制引脚
#define TEMPERATURE_THREHOLD     28  // 定义温度临界值


IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);

uint8_t temperature;
bool fanSwitch;
bool fanStatus;

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    // 平台下发数据点事件
    if((event == event_cloud_data) && (param == ep_cloud_data_datapoint))
    {
        if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_BOOL_FAN_SWITCH, fanSwitch))//获取风扇开关数据
        {
            if(true == fanSwitch)
            {
                digitalWrite(FAN_SWITCH_PIN,HIGH);//打开风扇 请根据实际情况设置高低电平
                IntoRobot.writeDatapoint(DPID_BOOL_FAN_STATUS, true);//写入数据风扇状态开
            }
            else
            {
                digitalWrite(FAN_SWITCH_PIN,LOW);//关闭风扇 请根据实际情况设置高低电平
                IntoRobot.writeDatapoint(DPID_BOOL_FAN_STATUS, false);//写入数据风扇状态关
            }
        }
    }
}

void setup()
{
    dht11.begin();
    pinMode(FAN_SWITCH_PIN,OUTPUT);
    digitalWrite(FAN_SWITCH_PIN, LOW);
    System.on(event_cloud_data, &system_event_callback);

    IntoRobot.defineDatapointBool(DPID_BOOL_FAN_SWITCH, DP_PERMISSION_UP_DOWN, false); //定义温度数据点
    IntoRobot.defineDatapointBool(DPID_BOOL_FAN_STATUS, DP_PERMISSION_UP_ONLY, false); //定义温度数据点
    IntoRobot.defineDatapointNumber(DPID_NUMBER_TEMPERATURE, DP_PERMISSION_UP_ONLY, 0,100,1,0); //定义温度数据点
}

void loop()
{
    temperature = dht11.getTempCelcius();
    if(temperature > TEMPERATURE_THREHOLD)
    {
        digitalWrite(FAN_SWITCH_PIN, HIGH);//打开风扇 请根据实际情况设置高低电平
        IntoRobot.writeDatapoint(DPID_BOOL_FAN_STATUS, true);//写入数据风扇状态开
        IntoRobot.writeDatapoint(DPID_BOOL_FAN_SWITCH, true);//写入数据风扇开关为开
    }
    else
    {
        digitalWrite(FAN_SWITCH_PIN, LOW);//关闭风扇 请根据实际情况设置高低电平
        IntoRobot.writeDatapoint(DPID_BOOL_FAN_STATUS, false);//写入数据风扇状态关
        IntoRobot.writeDatapoint(DPID_BOOL_FAN_SWITCH, false);//写入数据风扇开关为关
    }

    IntoRobot.writeDatapoint(DPID_NUMBER_TEMPERATURE,temperature);
    delay(3000);
}
