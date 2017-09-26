/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
Nut光照强度计：Nut自带光传感器检测光照强度
注意：需要将Nut核心板上的LS与A0脚短接在一起。
*/

// 光照强度应用topic定义
#define ILLUMINATION_DATA_INTENSITY     "channel/illumination_0/data/intensity" //光照强度

uint16_t data = 0;
float lightIntensity = 0.0;
 
void setup()
{
   pinMode(A0,AN_INPUT);
}

void loop()
{
    data = analogRead(A0);
    
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