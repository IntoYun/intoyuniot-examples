/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
水温计：检测水温

所需器件:
1.传感器模块DS18B20


接线说明:
DS18B20                      核心板
1.VCC（红色）                +3.3V
2.GND（黑色或灰色）           GND
3.DATA      				   D0
注意：DS18B20的DATA线一般为蓝色或黄色，需接一个1K-4.7K的上拉电阻）
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#include <OneWire.h>
#include <Dallas_Temperature.h>

//水温计应用topic定义
#define THERMOMETER_DATA_TEMPERATURE    "channel/thermometer_0/data/temperature"

// 数据线接到Atom板上的D0管脚
#define ONE_WIRE_BUS D0

// 设置oneWire线连接
OneWire oneWire(ONE_WIRE_BUS);

// 把oneWire线赋给温度传感器
Dallas_Temperature sensors(&oneWire);

void setup(void)
{
	// 设置管脚模式为输入
	oneWire.begin();
	// 启动传感器
	sensors.begin();
}

void loop(void)
{
	// 调用sensors.requestTemperatures() 发出获取温度的请求
	// 这里会请求所有连接上的设备
	sensors.requestTemperatures();
	// 取第一个设备的温度，如果温度显示是-127，说明值是不正确的
	float temp = sensors.getTempCByIndex(0);
	if(temp != -127.00)
	{
		// 把测量的温度数据传输到云平台
		IntoRobot.publish(THERMOMETER_DATA_TEMPERATURE, temp);
	}
	delay(1000);
}
