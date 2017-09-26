/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  16-11-15
 ************************************************************************
 功能描述：
 雷电云：雷声与闪电效果

 所需器件:
 1. RGB LED灯条（灯条所需电流较大需单独供电，建议5V2A电源）

 接线说明：
 灯条            核心板
 VDD(红色)       接外置电源5V
 GND(白色)       GND
 DATA(绿色)      D0

说明：雷电云需用到Process类，Neutron不支持Process类，此例程只适应于Atom核心板
带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */
/*This #include statement was automatically added by the IntoRobot IDE.*/
#include <Adafruit_NeoPixel.h>

#define CLOUDLIGHT_CMD_SWITCH    "channel/cloudLight_0/cmd/switch"
#define CLOUDLIGHT_DATA_STATUS   "channel/cloudLight_0/data/status"

#define PIXEL_PIN       D0    //定义数据引脚
#define PIXEL_COUNT     12     //定义RGB LED的数量
#define PIXEL_TYPE      WS2811 //定义RGB LED的驱动类型

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void cloudLight(void)
{
    Process p;
    p.begin("madplay");
    p.addParameter("/root/2629.mp3");
    p.addParameter("&");
    p.runAsynchronously();
    if (p.running())
    {
        delay(200);
    }

    for (int i = 0; i < 6; i++)
    {
        strip.setPixelColor(i, 255, 255, 255);
    }

    strip.show();
    delay(500);
    for (int i = 0; i < 6; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    delay(200);

    for (int i = 6; i < 12; i++)
    {
        strip.setPixelColor(i, 255, 255, 255);
    }

    strip.show();
    delay(500);

    for (int i = 6; i < 12; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }

    strip.show();
    delay(200);

    for (int i = 0; i < 4; i++)
    {
        strip.setPixelColor(i, 255, 255, 255);
    }

    strip.show();
    delay(400);
    for (int i = 0; i < 4; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    delay(100);


    for (int i = 0; i < 12; i++)
    {
        strip.setPixelColor(i, 255, 255, 255);
    }

    strip.show();
    delay(600);

    for (int i = 0; i < 12; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }

    strip.show();
    delay(1000);


    for (int i = 8; i < 12; i++)
    {
        strip.setPixelColor(i, 255, 255, 255);
    }

    strip.show();
    delay(400);
    for (int i = 8; i < 12; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    delay(300);

    for (int i = 4; i < 8; i++)
    {
        strip.setPixelColor(i, 255, 255, 255);
    }

    strip.show();
    delay(500);
    for (int i = 4; i < 8; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    delay(1000);
}

void cloudCb(uint8_t *payload, uint32_t len)
{
    if(payload[0] == '1')
    {
        IntoRobot.publish(CLOUDLIGHT_DATA_STATUS,1);
        cloudLight();
        IntoRobot.publish(CLOUDLIGHT_DATA_STATUS,0);
    }
}

void setup()
{
    //初始化灯条
    strip.begin();
    strip.setBrightness(255);
    strip.show();
    IntoRobot.subscribe(CLOUDLIGHT_CMD_SWITCH, NULL, cloudCb);
}

void loop()
{
}
