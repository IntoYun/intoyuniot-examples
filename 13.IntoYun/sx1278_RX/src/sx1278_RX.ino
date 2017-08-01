/*
************************************************************************
* 作者:  IntoRobot Team
* 版本:  V1.0.0
* 日期:  6-20-17
************************************************************************
功能描述：
SX1278_RX：SX1278接收数据

*/

#define LED    LED_USER

static bool ledFlag = false;
uint8_t buffer[4] = {1,2,3,4};

void LoRaRadioEventCallback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event)
    {
        case event_lora_radio_status:
            switch(param)
            {
                case ep_lora_radio_tx_done:
                    LoRa.radioSetSleep();
                    break;

                case ep_lora_radio_tx_timeout:
                    LoRa.radioSetSleep();
                    break;

                case ep_lora_radio_rx_done:
                    LoRa.radioSetSleep();
                    //获取接收的数据
                    memcpy( buffer, data, datalen );
                    //调试　打印接收到的数据
                    for(uint8_t i=0; i<4;i++)
                    {
                        Serial.printf("%d ",buffer[i]);
                    }
                    Serial.printf("\r\n");
                    ledFlag = !ledFlag;
                    digitalWrite(LED,ledFlag);
                    LoRa.radioRx(0);
                    break;

                case ep_lora_radio_rx_timeout:
                    LoRa.radioSetSleep();
                    Serial.println("rx timeout");
                    LoRa.radioRx(0);
                    break;

                case ep_lora_radio_rx_error:
                    LoRa.radioSetSleep();
                    Serial.println("rx error");
                    LoRa.radioRx(0);
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
    LoRaWan.macPause();//不运行lorawan协议
    Serial.begin(115200);
    System.on(event_lora_radio_status, &LoRaRadioEventCallback);
    LoRa.radioRx(0);//设为接收模式
    pinMode(LED,OUTPUT);
}

void loop()
{

}
