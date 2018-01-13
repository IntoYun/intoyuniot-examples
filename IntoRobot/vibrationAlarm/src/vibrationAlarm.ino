/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 震动报警器：检测到震动并报警

 所需器件:
 1.震动传感器SW-420


 接线说明:
 震动传感器                   核心板
 1.VCC                       +3.3V
 2.GND                        GND
 3.DO                         D1
 有源蜂鸣器模块               Atom
 1.VCC                       +3.3V
 2.GND                        GND
 3.I/O                        D0
 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 */

//震动报警器应用topic定义
#define SHAKE_DATA_STATUS    "channel/shake_0/data/status"

#define ShakeSensorINPUT   D1
#define BuzzerPIN  D0
unsigned char state = 0;

void setup()
{
    pinMode(ShakeSensorINPUT, INPUT);
    pinMode(BuzzerPIN, OUTPUT);
    attachInterrupt(ShakeSensorINPUT, shakeCb, RISING);	//D0口为外部中断0，当有上升沿触发的时候调用shake函数
}

void loop()
{
    if(state!=0)
    {
        IntoRobot.publish(SHAKE_DATA_STATUS,"1");
        digitalWrite(BuzzerPIN,LOW);
        delay(2000);
        digitalWrite(BuzzerPIN,HIGH);
        IntoRobot.publish(SHAKE_DATA_STATUS,"0");
        state = 0;
    }
}

void shakeCb()//数字输入传感器下降沿触发中断服务函数
{
    state = 1;
}
