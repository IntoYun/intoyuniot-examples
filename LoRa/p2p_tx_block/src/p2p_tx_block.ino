/*
功能描述：阻塞方式发送数据
SX1278_TX：SX1278发送数据
*/
#define LED    LED_BUILTIN
#define BUFFER_SIZE 10

static bool ledFlag = false;
uint8_t buffer[BUFFER_SIZE] = {1,2,3,4,5,6,7,8,9,0};//应用数据定义

void init_before_setup(void)
{
    System.disableFeature(SYSTEM_FEATURE_LORAMAC_RUN_ENABLED); //不运行lorawan协议
    System.disableFeature(SYSTEM_FEATURE_CONFIG_SAVE_ENABLED); //设备模式不保存
}

STARTUP( init_before_setup() );

//用户处理接收发送完数据等处理
void LoRaRadioEventCallback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    switch(event) {
        case event_lora_radio_status:
            switch(param) {
                case ep_lora_radio_tx_done:
                    LoRa.radioSetSleep();
                    break;

                case ep_lora_radio_tx_fail:
                    LoRa.radioSetSleep();
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
    Serial.println("lora p2p block tx mode");
}

void loop()
{
    //发送数据
    if(buffer[0] != 255) {
        buffer[0]++;
    } else {
        buffer[0] = 0;
    }

    ledFlag = !ledFlag;
    digitalWrite(LED,ledFlag);

    if(LoRa.radioSend(buffer,BUFFER_SIZE,3000) == 0) {
        Serial.println("radio send ok");
    } else {
        Serial.println("radio send fail");
    }
    ledFlag = !ledFlag;
    digitalWrite(LED,ledFlag);
    delay(1000);
}

