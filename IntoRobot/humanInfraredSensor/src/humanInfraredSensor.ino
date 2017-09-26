/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
人体红外感应灯：检测有人并点亮灯

所需器件:
1.红外传感器模块HC-SR501
2.LED灯泡
3.继电器模块

接线说明:
HC-SR501                     核心板
1.VCC(靠近电感)              +5V
2.GND                        GND
3.OUT(中间)                  D1
4.选择模式为重复触发模式
继电器模块               
1.DC+：                      +5V
2.DC-：                      GND
3.IN：                       D0
4.NO：                       灯的正极
5.COM：                      +5V
6.NC：                       悬空
7.触发选择端：选择跳线与high短接, 即高电平触发。

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

//人体红外感应灯应用topic定义
#define HUMANDETECTOR_DATA_STATUS    "channel/humandetector_0/data/status" 

#define PIRPIN D1  // D1连接信号输入管脚
#define LEDPIN D0  // LED灯来表示有人移动的状态

void setup()
{
	pinMode(PIRPIN, INPUT);	 // 设置管脚为输入模式
	pinMode(LEDPIN, OUTPUT); // 监测到人的时候，LED会亮，人离开的时候,LED会灭
	delay(1000);
}

void loop()
{
    
	// 当有人进入监测范围，pinPin管脚电平为高，当人离开，电平管脚变为低
	if(digitalRead(PIRPIN) == HIGH)
	{
		// 把有人状态传输到云平台
		IntoRobot.publish(HUMANDETECTOR_DATA_STATUS, 1);
		while (digitalRead(PIRPIN) == HIGH)
		{
			// 点亮灯   
			digitalWrite(LEDPIN, HIGH);
			delay(500);
		}

		digitalWrite(LEDPIN, LOW);		// 人离开，熄灭LED灯
		// 把人离开状态传输到云平台
		IntoRobot.publish(HUMANDETECTOR_DATA_STATUS, 0);
	}

	delay(1000);
}
