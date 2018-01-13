/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 智能风扇：控制风扇开关

 所需器件:
 1.风扇
 2.继电器模块

 接线说明:

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

//智能风扇应用topic定义
#define    SMARTFAN_CMD_SWITCH    "channel/smartFan_0/cmd/switch"    //开关命令
#define    SMARTFAN_DATA_STATUS   "channel/smartFan_0/data/status"   //开关状态

#define    SMART_FAN_SWITCH_PIN    D0 //定义风扇开关引脚

void smartFanCb(uint8_t *payload, uint32_t len)
{
    if(payload[0] == '1')
    {
        digitalWrite(SMART_FAN_SWITCH_PIN, HIGH); //打开风扇
        IntoRobot.publish(SMARTFAN_DATA_STATUS,"1");
    }
    else
    {
        digitalWrite(SMART_FAN_SWITCH_PIN, LOW);//关闭风扇
        IntoRobot.publish(SMARTFAN_DATA_STATUS,"0");
    }
}

void setup()
{
    //初始化
    pinMode(SMART_FAN_SWITCH_PIN,OUTPUT);
    //接收风扇开关命令
    IntoRobot.subscribe(SMARTFAN_CMD_SWITCH, NULL, smartFanCb);
}

void loop()
{
}

