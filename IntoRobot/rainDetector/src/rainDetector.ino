/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 雨水检测器：检测是否有雨水

 所需器件:
 1.雨水检测传感器

 接线说明:
 雨水检测传感器               核心板
 1.VCC                       +3.3V
 2.GND                        GND
 3.AO                         悬空
 4.DO                         D0

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

//雨水检测器应用topic定义
#define RAIN_DATA_STATUS    "channel/rain_0/data/status"

#define RainSensorINPUT   D0

void setup()
{
    pinMode(RainSensorINPUT, INPUT);
}

void loop()
{
    if(digitalRead(RainSensorINPUT)==0)     //检测到雨水
    {
        IntoRobot.publish(RAIN_DATA_STATUS,"1");
    }
    else  //未检测到雨水
    {
        IntoRobot.publish(RAIN_DATA_STATUS,"0");
    }
    delay(1000);
}

