/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
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

//温控风扇应用topic定义
#define  TEMPCTRLFAN_CMD_SWITCH          "channel/tempCtrlFan_0/cmd/switch"       //风扇开关
#define  TEMPCTRLFAN_DATA_STATUS         "channel/tempCtrlFan_0/data/status"      //风扇状态
#define  TEMPCTRLFAN_DATA_TEMPERATURE    "channel/tempCtrlFan_0/data/temperature" //温度数据

#define DHT_TYPE          DHT11
#define DHT11_PIN 		  D1
#define FAN_SWITCH_PIN    D0     // 定义风扇开关控制引脚
#define TEMPERATURE_THREHOLD 28  // 定义温度临界值

IntoRobot_DHT dht11(DHT11_PIN,DHT_TYPE);

int controlFlag = 0;

void fanSwitchCb(uint8_t *payload, uint32_t len)
{
	if(payload[0] == '1')
	{
		digitalWrite(FAN_SWITCH_PIN, HIGH);		//打开风扇
		IntoRobot.publish(TEMPCTRLFAN_DATA_STATUS,"1");
		controlFlag = 1;
	}
	else
	{
		digitalWrite(FAN_SWITCH_PIN, LOW);		//关闭风扇
		IntoRobot.publish(TEMPCTRLFAN_DATA_STATUS,"0");
		controlFlag = 0;
	}
}

void setup()
{
	//初始化
	dht11.begin();
	pinMode(FAN_SWITCH_PIN,OUTPUT);
	digitalWrite(FAN_SWITCH_PIN, LOW);
	//接收风扇开关控制
	IntoRobot.subscribe(TEMPCTRLFAN_CMD_SWITCH, NULL, fanSwitchCb);
}

void loop()
{
	float temp = dht11.getTempCelcius();
	if(!controlFlag)
	{
		if(temp > TEMPERATURE_THREHOLD)
		{
			digitalWrite(FAN_SWITCH_PIN, HIGH);			//打开风扇
			IntoRobot.publish(TEMPCTRLFAN_DATA_STATUS,"1");
		}
		else
		{
			digitalWrite(FAN_SWITCH_PIN, LOW);			//关闭风扇
			IntoRobot.publish(TEMPCTRLFAN_DATA_STATUS,"0");
		}
	}

	IntoRobot.publish(TEMPCTRLFAN_DATA_TEMPERATURE, dht11.getTempCelcius());	//上送温度
	delay(3000);
}
