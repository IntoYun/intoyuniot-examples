/*
    设置时间后串口输出当前时间
*/

time_t utc_time = 1524714441; //  北京时间：2018/4/26 11:47:8

void setup()
{
    Serial.begin(115200);
    Time.zone(8);
    Time.setTime(utc_time);
}

void loop()
{
    delay(2000);
    Serial.println(Time.timeStr());
}

