/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 土壤湿度检测器：土壤湿度检测

 所需器件:
 1.YL38 土壤湿度传感器

 接线说明:
 YL38                         核心板
 1.VIN                        5V
 2.GND                        GND
 3.AO                         A0
 4.DO                         悬空
 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */
#include <yl38.h>

// 土壤湿度应用topic定义
#define HUMIDITY_DATA_HUMIDITY    "channel/humidity_0/data/humidity"   //土壤湿度

#define YL38_PIN  A0

YL38 yl38 = YL38(YL38_PIN);

void setup()
{
    //初始化
    yl38.begin();
}

void loop()
{
    IntoRobot.publish(HUMIDITY_DATA_HUMIDITY,yl38.CalculateHumidity());	//上送土壤湿度
    delay(2000);
}

