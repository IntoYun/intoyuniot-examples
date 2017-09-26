/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
紫外线强度计：检测紫外线强度

所需器件:
1.紫外线检测传感器

接线说明:
紫外线检测传感器              核心板
1.VIN                         +3.3V
2.GND                         GND
3.OUT                         A0

说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
*/

//紫外线检测应用topic定义
#define ULTRAVIOLET_DATA_UVINTENSITY    "channel/ultraviolet_0/data/uvIntensity"
#define ULTRAVIOLET_DATA_UVINDEX        "channel/ultraviolet_0/data/uvIndex"
#define SENSOR_PIN A0 //紫外线传感器检测引脚

const uint16_t uvTable[] = {281,395,506,624,752,864,987,1093,1211,1338,1452};

//获取AD转换的平均值
uint16_t AverageAnalogRead(uint8_t pin)
{
    uint16_t sum = 0;
    for (uint8_t i = 0 ; i < 8 ; i++)
    {
        sum += analogRead(pin);
    }
    sum >>= 3;
    return sum;
}

//针对于浮点数的map函数
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    if(x<in_min) x=in_min;
    if(x>in_max) x=in_max;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//紫外线指数等级
uint8_t uvIndex(uint16_t value)
{
    uint8_t index;
    for(index = 0; index < (sizeof(uvTable) / sizeof(uint16_t)); index++)
    {
        if(value >= 1452)
        {
            return 11;
        }
        else if((value >= uvTable[index]) && (value < uvTable[index+1]))
        {
            return (index+1);
        }
    }
    return 0;
}
 
void setup() 
{
// put your setup code here, to run once.
    pinMode(SENSOR_PIN,AN_INPUT);
}

void loop() 
{
// put your main code here, to run repeatedly.
    uint16_t uvLevel = AverageAnalogRead(SENSOR_PIN);
    float outputVoltage = 3.3 * uvLevel/4095;
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);

    IntoRobot.publish(ULTRAVIOLET_DATA_UVINTENSITY, uvIntensity);
    IntoRobot.publish(ULTRAVIOLET_DATA_UVINDEX,uvIndex(analogRead(SENSOR_PIN)));
    delay(3000);
}
