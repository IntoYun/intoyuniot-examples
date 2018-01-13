/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  05-11-16
 ************************************************************************
 功能描述：
 检测鱼缸水温，控制其恒温、增氧、水泵、喂食、灯光。

 所需器件:
 抽水泵
 恒温器
 喂食器
 增氧器

 接线说明:
 DS18B20传感器               核心板
 1.VCC                       +3.3V
 2.GND                       GND
 3.DATA                      D0

 RGB灯条模块(所需电流较大，外置电源供电)
 1.VCC                       接外置电源5V
 2.GND                       GND
 3.DATA                      D1

 恒温器                       D2
 抽水泵                       D3
 喂食器                       D4
 增氧器                       D5
 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */
/*该头文件引用由IntoRobot自动添加.*/
#include <Dallas_Temperature.h>
#include <OneWire.h>
#include <Adafruit_NeoPixel.h>

//智能鱼缸topic定义
#define FISHTANK_DATA_TEMPERATURE    "channel/fishTank_0/data/temperature"
#define FISHTANK_CMD_CONTROL         "channel/fishTank_0/cmd/control"
#define FISHTANK_DATA_OXYSTATUS      "channel/fishTank_0/data/oxyStatus"

//引脚定义
#define ONE_WIRE_BUS  D0 //DS18B20 温度传感器
#define RGB_PIN       D1
#define TEMP_PIN      D2 //恒温开关
#define PUMP_PIN      D3 //水泵开关
#define FEED_PIN      D4 //喂食开关
#define O2_PIN        D5 //增氧开关

uint32_t oxyStartTime; //增氧开始时间
uint8_t incOxyTime;
uint8_t incOxyFlag;


// 设置oneWire线连接
OneWire oneWire(ONE_WIRE_BUS);
// 把oneWire线赋给温度传感器
Dallas_Temperature ds18b20(&oneWire);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, RGB_PIN, WS2812B); // RGB灯条

//设置灯条亮度
void set_bright(uint8_t level)
{
    static unsigned s_level_old = 0x00;

    if(level != s_level_old)
    {
        strip.setBrightness(level);
        strip.show();
    }

    s_level_old = level;
}

//设置灯条颜色
void set_color(uint32_t c, uint8_t wait)
{
    uint16_t i;

    for (i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
    }

    strip.show();
    delay(wait);
}

//灯条控制
void neopixelControl(uint8_t brightness, uint32_t rgb)
{
    set_bright((25*brightness)/10);
    set_color(rgb, 20);
}

//增氧控制
void IncOxyControl(uint8_t oxySwitch)
{
    digitalWrite(O2_PIN,oxySwitch);
    IntoRobot.publish(FISHTANK_DATA_OXYSTATUS,oxySwitch);

    if(oxySwitch) //增氧开关
    {
        if(incOxyTime != 0)
        {
            incOxyFlag = 1;
            oxyStartTime = timerGetId();
        }
        else
        {
            incOxyFlag = 0;
        }
    }
    else
    {
        incOxyFlag = 0;
    }
}

void FishTankCb(uint8_t *payload, uint32_t len)
{
    aJsonClass aJson;
    aJsonObject *root = aJson.parse((char *)payload);
    if(root == NULL)
    {
        aJson.deleteItem(root);
        return;
    }

    aJsonObject *_thermostat = aJson.getObjectItem(root, "thermostat");
    if(_thermostat != NULL)
    {
        uint8_t thermostatSwitchKey = atoi(_thermostat->valuestring);
        digitalWrite(TEMP_PIN, thermostatSwitchKey); //恒温开关

        aJsonObject *pumpSwitch = aJson.getObjectItem(root, "pump");
        if(pumpSwitch ==NULL)
        {
            aJson.deleteItem(root);
            return;
        }
        uint8_t pumpSwitchKey = atoi(pumpSwitch->valuestring);
        digitalWrite(PUMP_PIN, pumpSwitchKey); //水泵开关

        aJsonObject *ledBrightness = aJson.getObjectItem(root,"lightBrightness");
        if(ledBrightness == NULL)
        {
            aJson.deleteItem(root);
            return;
        }
        uint8_t ledBrightnessValue = atoi(ledBrightness->valuestring);

        aJsonObject *ledRgb = aJson.getObjectItem(root,"lightColor");
        if(ledRgb == NULL)
        {
            aJson.deleteItem(root);
            return;
        }
        uint32_t rgbValue = atoi(ledRgb->valuestring);

        neopixelControl(ledBrightnessValue,rgbValue); //灯光控制
    }
    else
    {
        aJsonObject *feed = aJson.getObjectItem(root, "feed");

        if(feed != NULL)
        {
            uint8_t feedSwitchKey = atoi(feed->valuestring);
            digitalWrite(FEED_PIN, feedSwitchKey); //喂食开关
        }
        else
        {
            aJsonObject *oxy = aJson.getObjectItem(root, "oxy");
            if(oxy == NULL)
            {
                aJson.deleteItem(root);
                return;
            }

            aJsonObject *oxystatus = aJson.getObjectItem(oxy,"status");
            if(oxystatus == NULL)
            {
                aJson.deleteItem(root);
                return;
            }
            uint8_t oxySwitchKey = oxystatus->valueint;

            aJsonObject *oxyTime = aJson.getObjectItem(oxy,"time");
            if(oxyTime == NULL)
            {
                aJson.deleteItem(root);
                return;
            }
            incOxyTime = oxyTime->valueint;
            IncOxyControl(oxySwitchKey);
        }
    }
    aJson.deleteItem(root);
}

void setup()
{
    oneWire.begin();
    ds18b20.begin();
    //灯条初始化
    strip.begin();
    set_bright(255);
    strip.show();
    IntoRobot.subscribe(FISHTANK_CMD_CONTROL, NULL, FishTankCb);
}

void loop()
{
    ds18b20.requestTemperatures();
    float waterTemp = ds18b20.getTempCByIndex(0);
    if(waterTemp != -127.00)
    {
        IntoRobot.publish(FISHTANK_DATA_TEMPERATURE,waterTemp); //上送温度
    }

    if(incOxyFlag && (timerIsEnd(oxyStartTime,incOxyTime*60000)))//增氧定时
    {
        digitalWrite(O2_PIN,0);
        IntoRobot.publish(FISHTANK_DATA_OXYSTATUS,0);
        incOxyFlag = 0;
    }

    delay(3000);
}

