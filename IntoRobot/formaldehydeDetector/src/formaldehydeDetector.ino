/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  03-30-15
************************************************************************
功能描述：
甲醛测量器：检测甲醛浓度

所需器件:
1.ZP01甲醛传感器

接线说明:
ZP01                       核心板
1.VCC                        +5V
2.GND                        GND
3.A(TX)                      RX(串口Serial组)    
4.B(RX)                      TX(串口Serial组)     
说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
此模块使用串口通讯方式，请注意各核心板串口引脚。
串口通讯方式：波特率9600，模块每隔1s主动发送一次数据共9个字节。
*/

// 甲醛测量仪应用topic
#define FORMALDEHYDEDETECT_DATA_CONCENTRATION  "channel/formaldehydeDetect_0/data/concentration"

uint8_t datBuffer[9] = {0};
uint8_t datLength = 0;
float concentrationVal = 0;

void setup() 
{
    // put your setup code here, to run once.
    Serial.begin(9600);
}

void loop() 
{
    while (Serial.available()) //开始接收数据
    {
        datBuffer[datLength] = (unsigned char)Serial.read();
        if(++datLength == 9)  //接收数据完毕
        {
            datLength = 0;  //重新赋值，准备下一组数据的接收
            concentrationVal = (float)(datBuffer[4]*256 + datBuffer[5])/100;
            IntoRobot.publish(FORMALDEHYDEDETECT_DATA_CONCENTRATION,concentrationVal);
        }
    }
}