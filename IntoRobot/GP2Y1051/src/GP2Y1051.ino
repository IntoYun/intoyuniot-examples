/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 时间:  03-30-15
 ************************************************************************
 功能描述：
 PM2.5浓度检测仪：检测空气PM2.5颗粒浓度

 所需器件:
 1. GP2Y1051灰尘传感器模块

 接线说明:
 GP2Y1051　　　　　核心板
 1黑色     　　　GND
 2红色     　　　5V
 6白色     　　　RX(串口)

 说明：带有“D”的为数字管脚，带有“A”的为模拟管脚，接线时请确认核心板引脚，避免接线错误。

 GP2Y1051串口通讯方式
 波特率 2400
 每10ms传感器发送一个字节数据，共7个字节，校验位 = Vout(H)+Vout(L)+Vref(H)+Vref(L)
 数据格式如下：
 起始位：0xaa
 Vout(H):
 Vout(L):
 Vref(H):
 Vref(L):
 校验位:
 结束位：0xff

 计算方法：
 输出电压Vout = ((Vout(H)*256+Vout(L))*5/1024
 浓度 = Vout * 比例系数（默认800） 建议值范围800-1000 单位ug/m³
 */

#define GAS_DATA_CONCENTRATION  "channel/gasConcentration_0/data/concentration"

uint8_t datBuffer[7] = {0};
uint8_t datLength = 0;
float concentrationVal = 0;

void setup()
{
    // put your setup code here, to run once.
    Serial.begin(2400);
}

void loop()
{
    while (Serial.available()) //开始接收数据
    {
        datBuffer[datLength] = (unsigned char)Serial.read();
        if(datBuffer[0] != 170) //判断起始位
        {
            datLength = 0;
            break;
        }
        else
        {
            if(++datLength == 7)  //接收数据完毕
            {
                datLength = 0;
                if((datBuffer[0] == 170) && (datBuffer[6] == 255))
                {
                    //重新赋值，准备下一组数据的接收
                    concentrationVal = (float)(datBuffer[1]*256 + datBuffer[2])*5/1024*800;
                    IntoRobot.publish(GAS_DATA_CONCENTRATION,concentrationVal);
                    delay(1000);
                }
            }
        }
    }
}
