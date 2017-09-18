/*
   Fade

   该示例展示如何通过函数analogWrite()让LED实现调光效果.

   analogWrite()用于产生PWM, 所以如果您要修改管脚，您需要确保管脚具备产生PWM功能.
   如果你想或者哪些管脚具备PWM功能，请查看文档:http://docs.intorobot.com/hardware.
 */

int led = D0;          // LED灯管脚
int brightness = 0;    // LED灯亮度
int fadeAmount = 5;    // LED灯亮度每次变化值

// setup函数, 上电后或者复位后只运行一次
void setup()
{
    // LED管脚设置为输出
    pinMode(led, OUTPUT);
}

// loop函数, 循环执行
void loop()
{
    // 设置LED灯亮度
    analogWrite(led, brightness);

    // 改变LED灯亮度
    brightness = brightness + fadeAmount;

    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount ;
    }
    // 等待30默秒, 可以看到调光效果
    delay(30);
}
