/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 Neutron照强度计：Neutron自带光传感器检测光照强度

 */

// 光照强度应用topic定义
#define ILLUMINATION_DATA_INTENSITY     "channel/illumination_0/data/intensity" //光照强度

void setup()
{
    lightSensor.begin();
}

void loop()
{
    uint16_t data = 0;
    lightSensor.getLightData(data);

    float lightIntensity = 0.0;
    if (data == 0)
    {
        lightIntensity = 0.0;
    }
    else
    {
        lightIntensity = -2.712e-08 * data * data * data - \
                         5.673e-05 * data * data  + 1.788 * data + 122.1;
    }

    IntoRobot.publish(ILLUMINATION_DATA_INTENSITY,(int)lightIntensity);  //上送光照强度
    delay(2000);
}
