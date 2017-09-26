/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
按键触发器：检测是否有触摸

所需器件:
1.触摸传感器模块

接线说明:
触摸传感器                   Atom
1.VCC                        +3.3V
2.GND                        GND
3.SIG                        D0
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

// 触摸计应用topic定义
#define TOUCH_DATA_STATUS    "channel/touch_0/data/status"  // 触摸传感器的状态topic

#define TOUPIN D0 // 连接触摸传感器信号管脚

void setup()
{
	pinMode(TOUPIN, INPUT);       // 设置连接触摸传感器信号管脚的模式为输入
}

void loop()
{
    // 触摸传感器被触摸，输出的状态为高电平，未触摸时输出低电平
	int touStatus = digitalRead(TOUPIN);    // 读取触摸传感器的状态
	// 把触摸状态发送到云平台
	IntoRobot.publish(TOUCH_DATA_STATUS, touStatus); 
	delay(1000);
}
