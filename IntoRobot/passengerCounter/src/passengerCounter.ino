/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 客流统计器：统计经过的人数

 所需器件:
 1.E18-D80NK 红外光电开关 漫反射式避障传感器模块

 接线说明:
 E18-D80NK                    核心板
 1.VDD-红色线                 5V
 2.GND-黑色线                 GND
 3.DATA-黄色线                D0

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

//客流统计器应用topic定义
#define PASSENGERCOUNT_DATA_POPULATION    "channel/passengerCount_0/data/population"

#define InfraredSensorINPUT   D0

volatile int32_t populationNow = 0;
uint32_t populationBefore = 0;
void countISR(void);

void setup()
{
    pinMode(InfraredSensorINPUT, INPUT_PULLUP);
    attachInterrupt(InfraredSensorINPUT, countISR, FALLING);
    IntoRobot.publish(PASSENGERCOUNT_DATA_POPULATION, 0);
}

void loop()
{
    if (populationNow != populationBefore)
    {
        populationBefore = populationNow;
        IntoRobot.publish(PASSENGERCOUNT_DATA_POPULATION, populationNow);
    }
    delay(1000);
}

void countISR(void)
{
    populationNow++;
}

