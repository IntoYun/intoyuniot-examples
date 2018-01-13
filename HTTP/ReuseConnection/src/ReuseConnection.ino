/**
 * reuseConnection.ino
 *
 *  Created on: 22.11.2015
 *
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#define USE_SERIAL Serial

HTTPClient http;

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

    // allow reuse (if server supports it)
    http.setReuse(true);
}

void loop() {
    // wait for WiFi connection
    if( WiFi.ready() ) {

        http.begin("http://192.168.1.12/test.html");
        //http.begin("192.168.1.12", 80, "/test.html");

        int httpCode = http.GET();
        if(httpCode > 0) {
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                http.writeToStream(&USE_SERIAL);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(1000);
}
