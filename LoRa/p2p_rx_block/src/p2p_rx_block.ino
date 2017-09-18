/*
功能描述：阻塞方式接收
SX1278_RX：SX1278接收数据
*/
#define LED    LED_BUILTIN

#define BUFFER_SIZE   10
static bool ledFlag = false;
uint8_t buffer[BUFFER_SIZE] = {1,2,3,4,5,6,7,8,9,0};
int16_t rssiVal = 0;

void LoRaRadioEventCallback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event)
    {
        case event_lora_radio_status:
            switch(param)
            {
                case ep_lora_radio_tx_done:
                    LoRa.radioSetSleep();
                    Serial.println("tx done");
                    break;

                case ep_lora_radio_tx_fail:
                    LoRa.radioSetSleep();
                    Serial.println("tx timeout");
                    break;

                case ep_lora_radio_rx_done:
                    break;

                case ep_lora_radio_rx_timeout:
                    LoRa.radioSetSleep();
                    Serial.println("rx timeout");
                    LoRa.radioStartRx(0);
                    break;

                case ep_lora_radio_rx_error:
                    LoRa.radioSetSleep();
                    Serial.println("rx error");
                    LoRa.radioStartRx(0);
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
    Cloud.setProtocol(PROTOCOL_P2P);//不运行lorawan协议
    Serial.begin(115200);
    System.on(event_lora_radio_status, &LoRaRadioEventCallback);
    LoRa.radioSetFreq(433175000);
    LoRa.radioStartRx(0);//设为接收模式
    pinMode(LED,OUTPUT);
    Serial.println("---lora p2p block rx mode---");
}

void loop()
{
    uint16_t bufSize = LoRa.radioRx(buffer,10,&rssiVal);
    if( bufSize != 0)
    {
        //打印接收到的数据
        Serial.printf("datalen = %d\r\n",bufSize);
        for(uint8_t i=0; i<bufSize;i++)
        {
            Serial.printf("0x%x ",buffer[i]);
        }
        Serial.printf("\r\n");
        Serial.printf("rssi = %d\r\n",rssiVal);
        ledFlag = !ledFlag;
        digitalWrite(LED,ledFlag);
    }
}

