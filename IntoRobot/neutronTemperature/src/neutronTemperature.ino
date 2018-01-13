/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 Neutron温度计：Neutron自带的气压传感器可以检测环境温度
 */

// 温度计应用topic定义
#define TEMPERATURE_DATA_DATA    "channel/thermometer_0/data/temperature"

double temperature, pressure;

void setup()
{
    BMP280.begin();
}

void loop()
{
    BMP280.getTemperaturePressureData(temperature, pressure);
    IntoRobot.publish(TEMPERATURE_DATA_DATA, (int)temperature);
    delay(2000);
}
