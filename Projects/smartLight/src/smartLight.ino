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

#define PRODUCT_ID_DEF                   WP6KsBxqRPM9x1ab
#define PRODUCT_SECRET_DEF               e964ba2d7ebdfbf368ba3168aafd55cb
#define SOFTWARE_VERSION_DEF             V1.0.0

PRODUCT_ID(PRODUCT_ID_DEF)     //产品ID
PRODUCT_SECRET(PRODUCT_SECRET_DEF) //产品密钥
PRODUCT_VERSION(SOFTWARE_VERSION_DEF)     //产品版本号

//定义数据点
#define DPID_BOOL_SWITCH                 1        //灯泡开关
#define DPID_BOOL_LIGHT_STATUS           2        //灯泡亮灭状态

#define LEDPIN    LED_USER    //例子灯

bool LightSwitch;
bool LightStatus;

void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    // 平台下发数据点事件
    if((event == event_cloud_data) && (param == ep_cloud_data_datapoint))
    {
        //灯泡控制
        if (RESULT_DATAPOINT_NEW == IntoRobot.readDatapoint(DPID_BOOL_SWITCH, LightSwitch))//获取灯泡开关数据
        {
            if(true == LightSwitch)
            {
                digitalWrite(LEDPIN,LOW);//打开灯泡 请根据实际情况设置高低电平
                IntoRobot.writeDatapoint(DPID_BOOL_LIGHT_STATUS, true);//写入数据灯泡状态开
            }
            else
            {
                digitalWrite(LEDPIN,HIGH);//关闭灯泡 请根据实际情况设置高低电平
                IntoRobot.writeDatapoint(DPID_BOOL_LIGHT_STATUS, false);//写入数据灯泡状态关
            }
        }
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(LEDPIN, OUTPUT);
    System.on(event_cloud_data, &system_event_callback);

    IntoRobot.defineDatapointBool(DPID_BOOL_SWITCH, DP_PERMISSION_UP_DOWN, false);        //灯泡开关
    IntoRobot.defineDatapointBool(DPID_BOOL_LIGHT_STATUS, DP_PERMISSION_UP_ONLY, false);  //灯泡亮灭状态
}

void loop()
{

}

