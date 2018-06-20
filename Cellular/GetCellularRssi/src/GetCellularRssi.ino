/*
    获取移动网络信号强度
*/

CellularSignal sig;

void setup() {
}

void loop() {
    sig = Cellular.RSSI();
    Serial.println(sig);
    delay(3000);
}

