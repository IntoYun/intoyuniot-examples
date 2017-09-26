/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  07-04-16
************************************************************************
功能描述：
Neutron气压计：Neutron自带BMP280气压传感器检测空气压强和海拔高度
*/

// 气压计应用topic定义
#define BAROMETER_DATA_PRESSURE   "channel/barometer_0/data/pressure" // 压强
#define BAROMETER_DATA_ALTITUDE   "channel/barometer_0/data/altitude" // 海拔高度

void setup()
{
    BMP280.begin();
}

void loop()
{
    double temperature, pressure, altitude;
    //float temperature, pressure, altitude;
    BMP280.getTemperaturePressureData(temperature, pressure);
    BMP280.getAltitudeData(altitude);
    IntoRobot.publish(BAROMETER_DATA_PRESSURE, (int)pressure);
	IntoRobot.publish(BAROMETER_DATA_ALTITUDE, (int)altitude);
	delay(2000);

}