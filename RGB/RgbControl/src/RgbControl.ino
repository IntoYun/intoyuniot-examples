/*
    控制RGB三色灯
*/

void setup() {
    //用户接管三色灯控制权
    RGB.control(true);
}

void loop() {
    // 红灯亮
    RGB.color(255, 0, 0);
    delay(1000);
    // 绿灯亮
    RGB.color(0, 255, 0);
    delay(1000);
    // 蓝灯亮
    RGB.color(0, 0, 255);
    delay(1000);
    // 红灯闪烁
    RGB.blink(255, 0, 0, 100);
    delay(5000);
}

