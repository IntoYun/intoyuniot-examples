/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 红外体温计：红外检测人体的温度

 所需器件:
 1.人体红外体温测试模块MLX90615

 接线说明:
 MLX90615         核心板
 1.VIN            +3.3V
 2.GND            GND
 3.RX             串口(Serial组)的TX
 4.TX             串口(Serial组)的RX

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 请注意核心板串口引脚区别，避免接线错误。
 */

#include <MLX90615.h>
//红外体温计应用topic定义
#define THERMOMETER_DATA_TEMPERATURE    "channel/thermometer_0/data/temperature"

MLX90615 bodyTemp;
void setup()
{
    bodyTemp.begin();
}

void loop()
{
    double temp = bodyTemp.getTemperature();
    if (temp != -1)
    {
        IntoRobot.publish(THERMOMETER_DATA_TEMPERATURE,temp);
    }
    delay(2000);
}

