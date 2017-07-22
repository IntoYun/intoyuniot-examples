/*
    闪灯程序
    点亮LED灯一秒，熄灭LED灯一秒，循环操作。

    IntoRobot模块基本上都具有一个可以控制的板载LED，不同的模块LED可能连接到不同的管脚，
    例如IntoRboot-Nut模块LED默认连接到D7管脚。程序默认定义了一个LED_BUILTIN宏, 该宏指向使用模块的LED管脚。
    如果您想知道LED管脚具体连接哪个管脚，请查看文档:http://docs.intorobot.com/hardware.
*/


// setup函数, 上电后或者复位后只运行一次
void setup()
{
    // LED_BUILTIN数字管脚设置为输出
    pinMode(LED_BUILTIN, OUTPUT);
}

// loop函数, 循环执行
void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);   // 数字管脚输出高电平(点亮LED灯)。 请注意: 部分模块LED管脚控制逻辑相反(例如输出高电平。LED灯灭)。
    delay(1000);                       // 等待1秒钟
    digitalWrite(LED_BUILTIN, LOW);    // 数字管脚输出低电平(熄灭LED灯)
    delay(1000);                       // 等待1秒钟
}
