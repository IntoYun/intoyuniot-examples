/*
    ReadAnalogVoltage

    读取模拟口A0模拟值，把数值转换成电压并往串口打印电压值.

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
    int sensorValue = analogRead(A0);                 //读取模拟口A0模拟值
    //把模拟值(0-4095)转换成电压值(0-3.3v)
    //其中intorobot-nut 模拟值(0-1023), 电压值(0-5.0v) 所以应修改为sensorValue * (5.0 / 1023.0).
    float voltage = sensorValue * (3.3 / 4095.0);
    Serial.println(voltage);
}
