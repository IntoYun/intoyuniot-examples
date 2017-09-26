/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
起火报警器：检测到火焰并报警

所需器件:
1.火焰检测模块

接线说明:
火焰传感器                   核心板
1.VCC                       +3.3V
2.GND                        GND
3.DO                         D1
有源蜂鸣器模块               
1.VCC                       +3.3V
2.GND                        GND
3.I/O                        D0

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

//起火报警器应用topic定义
#define FIRE_DATA_STATUS    "channel/fire_0/data/status"

#define FireSensorINPUT      D1
#define BuzzerPIN            D0

void setup()
{
	pinMode(FireSensorINPUT, INPUT);
	pinMode(BuzzerPIN, OUTPUT);
}

void loop()
{
	if(digitalRead(FireSensorINPUT) == 0) // 输出低电平表示检测到火源
	{
		digitalWrite(BuzzerPIN,LOW);
		IntoRobot.publish(FIRE_DATA_STATUS,"1");
	}
	else                                  // 输出高电平表示未检测到火源
	{
		digitalWrite(BuzzerPIN,HIGH);
		IntoRobot.publish(FIRE_DATA_STATUS,"0");
	}
	delay(1000);
}
