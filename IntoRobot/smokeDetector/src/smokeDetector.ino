/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
烟雾检测器：获取烟雾报警信息

所需器件:
1.MQ2 烟雾传感器模块

接线说明：
MQ2                          核心板
1.VCC                        +5V
2.GND                        GND
3.DO                         悬空
4.AO                         A0
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#include <mq2.h>

//烟雾报警应用topic定义
#define SMOKEDETECTOR_DATA_STATUS    "channel/smokedetector_0/data/status"  //烟雾状态  
#define SMOKE_ALARM_CONCENTRATION    2000    //设定烟雾浓度报警值 范围是0-4095
#define MQ2_PIN A0

MQ2 mq2 = MQ2(MQ2_PIN);

void setup()
{
    //初始化
	mq2.begin(); 
}

void loop()
{
	if(mq2.Read() >= SMOKE_ALARM_CONCENTRATION) //烟雾浓度达到报警值
	{
		IntoRobot.publish(SMOKEDETECTOR_DATA_STATUS,"1");
	}
	else
	{
		IntoRobot.publish(SMOKEDETECTOR_DATA_STATUS,"0");
	}

	delay(3000);
}
