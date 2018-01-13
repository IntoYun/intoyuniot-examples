/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 声控灯：单击掌开灯， 双（多）击掌关灯

 所需器件:
 1.声音传感器模块
 2.LED灯泡

 接线说明:
 声音传感器模块               核心板
 1.VCC                        +3.3V
 2.GND                        GND
 3.OUT                        D1
 继电器模块
 1.DC+：                      +5V
 2.DC-：                      GND
 3.IN：                       D0
 4.NO：                       灯的正极
 5.COM：                      +5V
 6.NC：                       悬空
 7.触发选择端：选择跳线与high短接, 即高电平触发。
 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

//声控灯应用topic定义
#define SOUND_DATA_STATUS    "channel/sound_0/data/status"

#define LEDPIN               D0
#define SoundSensorINPUT     D1

unsigned char state = 0;
uint32_t timeLast = 0;
uint32_t timeNow = 0;

void setup()
{
    pinMode(LEDPIN, OUTPUT);
    pinMode(SoundSensorINPUT, INPUT_PULLUP);
    attachInterrupt(SoundSensorINPUT, soundDetectCb, FALLING);	//D0口为外部中断，当有下降沿触发的时候调用soundDetectCb函数
}

void loop()
{
    IntoRobot.publish(SOUND_DATA_STATUS,state);
    digitalWrite(LEDPIN,state);
    delay(1000);
}

void soundDetectCb()//声音检测回调函数
{
    timeNow = timerGetId();

    if((timeNow - timeLast) > 3200)  // 3.5s
    {
        timeLast = timeNow;
    }
    uint32_t delta = timeNow - timeLast;

    if((timeNow - timeLast) < 300)   // 0.2s
    {
        state = 1;
    }
    else if((timeNow - timeLast) < 3000) // 3s
    {
        state = 0;
    }
}
