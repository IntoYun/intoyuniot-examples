/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 酒精含量检测器：检测酒精含量

 所需器件:
 1.MQ-3酒精乙醇传感器模块

 接线说明:
 MQ-3                         核心板
 1.VIN                        5V
 2.GND                        GND
 3.AO                         A0
 4.DO                         悬空

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

//酒精含量检测器应用topic定义
#define ALCOHOLDETECT_DATA_CONCENTRATION "channel/alcoholDetect_0/data/concentration"

//传感器检测引脚
#define SENSOR_PIN    A0

int initState = 1;
int soberReading;  //没有监测到酒精的阈值，实际中监测获取
int aoVal = 0;

void setup()
{
    pinMode(SENSOR_PIN, INPUT);	//设置管脚为输入模式
    soberReading = aoVal; //没有监测到酒精的阈值，实际中监测获取
}

void loop()
{
    aoVal = analogRead(SENSOR_PIN); //读取模拟管脚数值

    // 电压每升高0.1V,实际被测气体的浓度增加约20ppm
    float ppm = (aoVal - soberReading)* 1.0 / 4096 * 3.3 * 200;
    ppm = ppm > 0 ?  ppm : 0;
    // 把获得的酒精浓度上传到云平台
    IntoRobot.publish(ALCOHOLDETECT_DATA_CONCENTRATION, ppm);
    delay(2000);
}

