/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 甲醛测量器：检测甲醛浓度

 所需器件:
 1.KQM2801A甲醛传感器
 2.采用串口通讯方式

 注意:
 模块上电后需预热3分钟

 接线说明:
 传感器                       核心板
 1.VCC                        +5V
 2.GND                        GND
 3.A(TX)                      RX(串口Serial组)
 4.B(RX)                      TX(串口Serial组)
 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。
 此模块使用串口通讯方式，请注意各核心板串口引脚。
 串口通讯方式：波特率9600，模块每隔1s主动发送一次数据共4个字节。
 */

// 甲醛测量仪应用topic
#define FORMALDEHYDEDETECT_DATA_CONCENTRATION  "channel/formaldehydeDetect_0/data/concentration"

uint8_t datBuffer[4] = {0};
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
        if(datBuffer[0] != 0x5F) //判断起始位
        {
            datLength = 0;
            break;
        }
        else
        {
            if(++datLength == 4)  //接收数据完毕
            {
                datLength = 0;
                if((datBuffer[0] == 0x5F) && (datBuffer[1] == 0xFF) && (datBuffer[2] == 0xFF))
                {
                    //预热阶段
                    IntoRobot.publish(FORMALDEHYDEDETECT_DATA_CONCENTRATION,0);
                    delay(1000);
                }
                else if((datBuffer[0] == 0x5F) && (((datBuffer[0]+datBuffer[1] +  datBuffer[2])  & 0xff) == datBuffer[3]))
                {
                    //重新赋值，准备下一组数据的接收
                    concentrationVal = (float)(datBuffer[1]*256 + datBuffer[2])/10;
                    IntoRobot.publish(FORMALDEHYDEDETECT_DATA_CONCENTRATION,concentrationVal);
                    delay(1000);
                }
            }
        }
    }
}

