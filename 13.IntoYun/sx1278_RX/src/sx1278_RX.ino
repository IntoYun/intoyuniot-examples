/*
************************************************************************
* 作者:  IntoRobot Team 
* 版本:  V1.0.0
* 日期:  6-20-17
************************************************************************
功能描述：
SX1278_RX：SX1278接收数据

*/

#define LED           D5

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
                    LoRaWan.radioSetSleep();
                    break;

                case ep_lora_radio_tx_timeout:
                    LoRaWan.radioSetSleep();
                    break;

                case ep_lora_radio_rx_done:
                    LoRaWan.radioSetSleep();
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
                    LoRaWan.radioRx(0);
                    break;

                case ep_lora_radio_rx_timeout:
                    LoRaWan.radioSetSleep();
                    Serial.println("rx timeout");
                    LoRaWan.radioRx(0);
                    break;

                case ep_lora_radio_rx_error:
                    LoRaWan.radioSetSleep();
                    Serial.println("rx error");
                    LoRaWan.radioRx(0);
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

void init_before_setup(void)
{
    System.disableFeature(SYSTEM_FEATURE_LORAMAC_ENABLED);
}

STARTUP( init_before_setup() );


void setup()
{
    Serial.begin(115200);
    LoRaWan.loramacPause();//不运行lorawan协议
    System.on(event_lora_radio_status, &LoRaRadioEventCallback);
    LoRaWan.radioSetFreq(470000000);
    LoRaWan.radioRx(0);//设为接收模式
    pinMode(LED,OUTPUT);
}

void loop()
{

}

