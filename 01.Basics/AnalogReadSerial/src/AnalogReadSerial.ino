/*
    AnalogReadSerial

    读取模拟口A0模拟值，并往把数值从串口输出

    以使用电位器为例, 电位器中间引脚与A0连接，两侧引脚分别连接+3.3v 和 GND(地).
*/


// setup函数, 上电后或者复位后只运行一次
void setup()
{
    // 串口初始化，波特率设置为115200
    Serial.begin(115200);
    pinMode(A0,AN_INPUT);
}

// loop函数, 循环执行
void loop()
{
    int sensorValue = analogRead(A0);  // 读取模拟口A0模拟值

    Serial.println(sensorValue);       // 打印读取的数值
    delay(1000);                       // 延时1秒钟
}
