/*
    获取剩余动态内存
*/

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println(System.freeMemory());
    delay(5000);
}

