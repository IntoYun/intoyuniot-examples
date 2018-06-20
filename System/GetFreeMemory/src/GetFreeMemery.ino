/*
    获取剩余动态内存
*/

void setup() {
    //用户接管三色灯控制权
    Serial.begin(115200);
}

void loop() {
    Serial.println(System.freeMemory());
    delay(5000);
}

