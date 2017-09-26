/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 时间:  03-30-15
************************************************************************
功能描述：
PM2.5浓度检测仪：检测空气PM2.5颗粒浓度

所需器件:
1. GP2Y1010 PM2.5浓度传感器模块
2. AD模拟量采样

接线说明
GP2Y1010         核心板
VCC(红色线)	   3V3
GND(绿色线)    GND
LED(白色线)    D0
OUT(黑色线)    A0
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

#include <gp2y10.h>

//PM2.5浓度检测应用topic定义
#define GASCONCENTRATION_DATA_CONCENTRATION    "channel/gasConcentration_0/data/concentration" //PM2.5浓度

#define GP2Y10_LED_PIN D0
#define GP2Y10_OUT_PIN A0

GP2Y10 pm25 = GP2Y10(GP2Y10_OUT_PIN,GP2Y10_LED_PIN);  

void setup()
{
    //初始化
	pm25.begin(); 
}

void loop()
{
	IntoRobot.publish(GASCONCENTRATION_DATA_CONCENTRATION, pm25.CalculatedConcentration()); //上送PM2.5浓度
	delay(3000);
}
