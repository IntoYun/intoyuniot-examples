/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 光照强度计：检测光照强度

 所需器件:
 1.GY30 光照传感器模

 接线说明:
 GY30                         核心板
 1.VIN                        +3.3V
 2.GND                        GND
 3.SDA                        I2C(Wire组)的SDA
 4.SCL                        I2C(Wire组)的SCL

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 请注意核心板I2C引脚区别，避免接线错误
 */

#include <gy30.h>

// 光照强度应用topic定义
#define ILLUMINATION_DATA_INTENSITY     "channel/illumination_0/data/intensity" //光照强度

GY30 gy30;                //光照强度传感器

void setup()
{
    //初始化
    Wire.begin();
    delay(100);
    gy30.begin();
}

void loop()
{
    IntoRobot.publish(ILLUMINATION_DATA_INTENSITY, gy30.Read());              //上送光照强度
    delay(1000);
}

