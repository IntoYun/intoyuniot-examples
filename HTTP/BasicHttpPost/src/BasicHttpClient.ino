/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#define USE_SERIAL Serial

void setup() {
    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
}

void loop() {
    // wait for WiFi connection
    if( WiFi.ready() ) {

        HTTPClient http;
        String payload;

        USE_SERIAL.print("[HTTP] begin...\n");

        http.begin("192.168.1.12", 80, "/v1/device?act=register");
        http.setUserAgent("User-Agent: Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.101 Safari/537.36");
        int httpCode = http.POST(payload);

        if(httpCode > 0) {
            payload = http.getString();
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            USE_SERIAL.print(payload);
        } else {
            USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    delay(10000);
}
