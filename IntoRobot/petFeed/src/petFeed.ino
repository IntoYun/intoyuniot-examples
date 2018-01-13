/******************************

  作者  IntoRobot Team
  版本  V1.0.0
  日期  03-30-15

  功能描述：
  宠物喂食器：设想通过红外检测到宠物靠近喂食器发出声音并打开喂食器

  所需器件
  1.E18-D80NK 红外光电开关 漫反射式避障传感器模块
  2.继电器模块
  3.宠物喂食装置

  接线说明
  E18-D80NK                    核心板
  1.红色线                     +5V
  2.黑色线                     GND
  3.黄色线                     D1
  继电器模块
  1.DC+：                      +5V
  2.DC-：                      GND
  3.IN：                       D0
  4.NO：                       舵机的正极
  5.COM：                      +5V
  6.NC：                       悬空
  7.触发选择端：选择跳线与high短接, 即高电平触发。

  语音模块
  VCC                          5V
  GND                          GND
  P-E                          D2
  其余引脚不接

 ***********************************/

#define PETFEED_CMD_CONTROL      "channel/petfeeding_0/cmd/control"
#define PETFEED_DATA_FEEDSTATUS  "channel/petfeeding_0/data/feedStatus"
#define PETFEED_DATA_PATSTATUS   "channel/petfeeding_0/data/patStatus"

#define INFRARED_SENSOR_INPUT    D1  //定义红外光电传感器引脚
#define MOTORPIN                 D0  //定义马达控制引脚
#define SPEAKER                  D2  //定义语音模块播放引脚（上升沿播放）

uint8_t feedFlag;

void FeedControl(uint8_t feedVal)
{
    if(feedVal)
    {
        digitalWrite(SPEAKER,0);
        delay(100);
        digitalWrite(SPEAKER,1);

        digitalWrite(MOTORPIN,1);
        IntoRobot.publish(PETFEED_DATA_FEEDSTATUS,1);
        delay(5000);
        digitalWrite(MOTORPIN,0);
        IntoRobot.publish(PETFEED_DATA_FEEDSTATUS,0);
        feedFlag = 1;
    }
    else
    {
        digitalWrite(MOTORPIN,0);
        IntoRobot.publish(PETFEED_DATA_FEEDSTATUS,0);
    }
}

void PetFeedCb(uint8_t *payload, uint32_t len)
{
    aJsonClass aJson;
    aJsonObject *root = aJson.parse((char *)payload);
    if(root == NULL)
    {
        aJson.deleteItem(root);
        return;
    }

    aJsonObject *_feed = aJson.getObjectItem(root, "feed");
    if(_feed != NULL)
    {
        uint8_t feedSwitchKey = atoi(_feed->valuestring);
        FeedControl(feedSwitchKey);
    }
    else
    {
        aJsonObject *_photo = aJson.getObjectItem(root, "photo");
        if(_photo == NULL)
        {
            aJson.deleteItem(root);
            return;
        }
        uint8_t photoSwitchKey = atoi(_photo->valuestring);
        if(photoSwitchKey)
        {
        }
    }

    aJson.deleteItem(root);
}

void setup()
{
    pinMode(INFRARED_SENSOR_INPUT, INPUT_PULLUP);
    pinMode(MOTORPIN,OUTPUT);
    IntoRobot.subscribe(PETFEED_CMD_CONTROL,NULL,PetFeedCb);
}

void loop()
{
    if(!digitalRead(INFRARED_SENSOR_INPUT))
    {
        IntoRobot.publish(PETFEED_DATA_PATSTATUS,1);
        if(!feedFlag)
        {
            feedFlag = 1;
            digitalWrite(MOTORPIN,1);
            delay(5000);
            digitalWrite(MOTORPIN,0);
        }
    }
    else
    {
        feedFlag = 0;
        // 发送宠物未出现状态
        IntoRobot.publish(PETFEED_DATA_PATSTATUS,0);
    }

    delay(2000);
}

