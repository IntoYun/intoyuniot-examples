/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-16
 ************************************************************************
 功能描述：
 Nut智能光控灯：Nut自带光照传感器，具有光照强度检测的智能灯，根据光强度控制灯的开关

 所需器件:
 １.LED灯泡
 ２.继电器模块

 接线说明:
 继电器模块
 1.DC+：                      +5V
 2.DC-：                      GND
 3.IN：                       D0
 4.NO：                       灯的正极
 5.COM：                      +5V
 6.NC：                       悬空
 7.触发选择端：选择跳线与high短接, 即高电平触发。

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 请注意核心板的I2C引脚区别，避免接线错误。
 */

//智能光控灯应用topic定义
#define OPTCTRLLAMP_CMD_SWITCH              "channel/optCtrlLamp_0/cmd/switch"        //开关命令
#define OPTCTRLLAMP_DATA_STATUS             "channel/optCtrlLamp_0/data/status"       //开关状态
#define OPTCTRLLAMP_DATA_ILLUMINATION       "channel/optCtrlLamp_0/data/illumination" //光照强度

#define LAMP_SWITCH_PIN    	   D0    //定义灯泡控制引脚
#define IlluminationThreshold  200// 定义光强临界值

uint8_t controlFlag = 0;
uint16_t lightSensorVal = 0;
float lightIntensity = 0.0;

void lightSwitchCb(uint8_t *payload, uint32_t len)
{
    if(payload[0] == '1')
    {
        digitalWrite(LAMP_SWITCH_PIN, HIGH);		//打开灯泡
        IntoRobot.publish(OPTCTRLLAMP_DATA_STATUS,"1");
        //controlFlag = 1;
    }
    else
    {
        digitalWrite(LAMP_SWITCH_PIN, LOW);		//关闭灯泡
        IntoRobot.publish(OPTCTRLLAMP_DATA_STATUS,"0");
        //controlFlag = 0;
    }
}

void setup()
{
    //初始化
    pinMode(A0,AN_INPUT);
    pinMode(LAMP_SWITCH_PIN, OUTPUT);
    //接收灯开关控制
    IntoRobot.subscribe(OPTCTRLLAMP_CMD_SWITCH, NULL, lightSwitchCb);
}

void loop()
{
    lightSensorVal = analogRead(A0);

    lightIntensity = -2.712e-08 * lightSensorVal * lightSensorVal * lightSensorVal - \
                     5.673e-05 * lightSensorVal * lightSensorVal  + 1.788 * lightSensorVal + 122.1;

    IntoRobot.publish(OPTCTRLLAMP_DATA_ILLUMINATION, lightIntensity);	//上送光照强度值

    delay(1000);
}

