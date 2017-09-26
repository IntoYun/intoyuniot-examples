/**
  ******************************************************************************
/*
************************************************************************
* 作者:  IntoRobot Team    
* 版本:  V1.0.0
* 日期:  07-04-16
************************************************************************
功能描述：
Neutron自带传感器原始数据显示

  ******************************************************************************
  */
  
#define LED_PIN    D7

#define NEUTRON_DATA_ACCELERARTION     "channel/neutron_0/data/acceleration"
#define NEUTRON_DATA_GYROSCOPE         "channel/neutron_0/data/gyroscope"
#define NEUTRON_DATA_MAGNETOMETER      "channel/neutron_0/data/magnetometer"
#define NEUTRON_DATA_PRESSURE          "channel/neutron_0/data/pressure"
#define NEUTRON_DATA_ALTITUDE          "channel/neutron_0/data/altitude"
#define NEUTRON_DATA_ILLUMINATION      "channel/neutron_0/data/illumination"
#define NEUTRON_DATA_LOUDNESS          "channel/neutron_0/data/loudness"
#define NEUTRON_CMD_SWITCH             "channel/neutron_0/cmd/switch"

int16_t accelData[3], gyroData[3], magData[3]; //加速度、陀螺仪、磁力计值
double presureData, altitudeData; //大气压强、海拔高度值
uint16_t lightData; //光照强度值
char micData; //声音值


static void ledSwitchCb(uint8_t *payload, uint32_t len)
{
    if(payload[0] == '1')
    {
        digitalWrite(LED_PIN, HIGH);//打开
    }
    else
    {
        digitalWrite(LED_PIN, LOW);	//关闭
    }
}

void setup()
{
    pinMode(LED_PIN,OUTPUT);
    IntoRobot.subscribe(NEUTRON_CMD_SWITCH, NULL, ledSwitchCb);
    Neutron.begin();
}

void loop()
{
    //加速度、陀螺仪、磁力计
    Neutron.getAccelGyroMagData(accelData, gyroData, magData);
    
    Serial.printf("\naccel: %d %d %d\r\n", accelData[0], accelData[1], accelData[2]);
    Serial.printf("gyro:   %d %d %d\r\n", gyroData[0],  gyroData[1],  gyroData[2]);
    Serial.printf("mag:    %d %d %d\r\n", magData[0],   magData[1],   magData[2]);

    // "{x:90,y:90,z:90}"

    aJsonClass aJson;
    aJsonObject* root = aJson.createObject();
    if (root == NULL)
    {
        //return;
        Serial.printf(" root NULL! \n");
    
    }
    char *jsonString = NULL;

    aJson.addNumberToObject(root, "x", accelData[0]);
    aJson.addNumberToObject(root, "y", accelData[1]);
    aJson.addNumberToObject(root, "z", accelData[2]);
    jsonString = aJson.print(root);
    IntoRobot.publish(NEUTRON_DATA_ACCELERARTION, jsonString);
    vPortFree(jsonString);
    delay(500);

    aJson.addNumberToObject(root, "x", gyroData[0]);
    aJson.addNumberToObject(root, "y", gyroData[1]);
    aJson.addNumberToObject(root, "z", gyroData[2]);
    jsonString = aJson.print(root);
    IntoRobot.publish(NEUTRON_DATA_GYROSCOPE,jsonString);
    vPortFree(jsonString);
    delay(500);
    aJson.addNumberToObject(root, "x", magData[0]);
    aJson.addNumberToObject(root, "y", magData[1]);
    aJson.addNumberToObject(root, "z", magData[2]);
    jsonString = aJson.print(root);
    IntoRobot.publish(NEUTRON_DATA_MAGNETOMETER, jsonString);
    delay(500);
    vPortFree(jsonString);
    aJson.deleteItem(root);

    //气压、海拔
    Neutron.getPressureAltitudeData(presureData, altitudeData);
    Serial.printf("\npresure: %d\r\n", (uint32_t)presureData);
    Serial.printf("altitude: %d\r\n", (uint32_t)altitudeData);

    IntoRobot.publish(NEUTRON_DATA_PRESSURE, presureData);
    IntoRobot.publish(NEUTRON_DATA_ALTITUDE, altitudeData);
    delay(1000);
    //光照
    Neutron.getLightData(lightData);
    Serial.printf("\nlight: %d\r\n", lightData);
    IntoRobot.publish(NEUTRON_DATA_ILLUMINATION,lightData);
    delay(1000);   
    //声音
    Neutron.getMICData(micData);
    Serial.printf("\nmic: %d\r\n", micData);
    IntoRobot.publish(NEUTRON_DATA_LOUDNESS, micData);
    delay(1000);
}