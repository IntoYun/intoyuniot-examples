/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  6-20-17
************************************************************************
功能描述：
SX1278_TX：SX1278发送数据

*/

#define LED    LED_USER

static bool ledFlag = false;
uint8_t buffer[4] = {1,2,3,4};//应用数据定义

//用户处理接收发送完数据等处理
void LoRaRadioEventCallback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event)
    {
        case event_lora_radio_status:
            switch(param)
            {
                case ep_lora_radio_tx_done:
                    LoRa.radioSetSleep();
                    ledFlag = !ledFlag;
                    digitalWrite(LED,ledFlag);
                    Serial.println("tx done");
                    break;

                case ep_lora_radio_tx_timeout:
                    LoRa.radioSetSleep();
                    Serial.println("tx timeout");
                    break;

                case ep_lora_radio_rx_done:
                    LoRa.radioSetSleep();
                    break;

                case ep_lora_radio_rx_timeout:
                    LoRa.radioSetSleep();
                    break;

                case ep_lora_radio_rx_error:
                    LoRa.radioSetSleep();
                    break;

                case ep_lora_radio_cad_done:
                    if((*data) == 1)//已检测到CAD
                    {
                    }
                    else
                    {
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

}

void setup()
{
    LoRaWan.macPause();//停止运行lorawan协议
    Serial.begin(115200);
    System.on(event_lora_radio_status, &LoRaRadioEventCallback);
    pinMode(LED,OUTPUT);
}

void loop()
{
    //只发送数据
    if(buffer[0] != 255)
    {
        buffer[0]++;
    }
    else
    {
        buffer[0] = 0;
    }
    LoRa.radioSend(buffer,4);
    delay(1000);
}
