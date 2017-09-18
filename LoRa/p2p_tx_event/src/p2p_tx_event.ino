/*
功能描述：事件方式发送数据
SX1278_TX：SX1278发送数据
*/
#define LED    LED_BUILTIN
#define BUFFER_SIZE 10

static bool ledFlag = false;
static bool txDone = true;
uint8_t buffer[BUFFER_SIZE] = {1,2,3,4,5,6,7,8,9,0};//应用数据定义

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
                    txDone = true;
                    break;

                case ep_lora_radio_tx_fail:
                    LoRa.radioSetSleep();
                    Serial.println("tx timeout");
                    break;

                case ep_lora_radio_rx_done:
                    break;

                case ep_lora_radio_rx_timeout:
                    break;

                case ep_lora_radio_rx_error:
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
    Cloud.setProtocol(PROTOCOL_P2P);//停止运行lorawan协议
    Serial.begin(115200);
    System.on(event_lora_radio_status, &LoRaRadioEventCallback);
    LoRa.radioSetFreq(433175000);
    pinMode(LED,OUTPUT);
    Serial.println("lora p2p event tx mode");
}

void loop()
{
    if(txDone)
    {
       //发送数据
        txDone = false;
        if(buffer[0] != 255){
            buffer[0]++;
        }else{
            buffer[0] = 0;
        }
        LoRa.radioSend(buffer,BUFFER_SIZE,0);
    }
    delay(1000);
}
