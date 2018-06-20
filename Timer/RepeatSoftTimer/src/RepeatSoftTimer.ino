/*
    循环定时器
    每秒钟往串口打印一个计数值
*/

void print_every_second()
{
    static int count = 0;
    Serial.println(count++);
}

Timer timer(1000, print_every_second);

void setup()
{
    Serial.begin(115200);
    timer.start();
}

void loop()
{
}

