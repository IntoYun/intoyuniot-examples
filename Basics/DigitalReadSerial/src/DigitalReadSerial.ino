/*
    DigitalReadSerial

    读取数字口D0状态值，并把结果往串口输出
*/

int pushButton = D0;

// setup函数, 上电后或者复位后只运行一次
void setup()
{
    // 串口初始化，波特率设置为115200
    Serial.begin(115200);
    // pushButton 数字口设置成输入
    pinMode(pushButton, INPUT);
}

// loop函数, 循环执行
void loop()
{
    int buttonState = digitalRead(pushButton);   // 读取pushButton数字口状态

    Serial.println(buttonState);                 // 往串口打印状态值
    delay(1000);                                 // 延时1秒钟
}
