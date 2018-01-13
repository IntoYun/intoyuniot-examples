/*
   Reconnecting MQTT example - non-blocking

   This sketch demonstrates how to keep the client connected
   using a non-blocking reconnect function. If the client loses
   its connection, it attempts to reconnect every 5 seconds
   without blocking the main loop.

 */

#include <PubSubClient.h>

SYSTEM_MODE(SEMI_AUTOMATIC);

// Update these with values suitable for your hardware/network.
IPAddress ip(172, 16, 0, 100);
IPAddress server(172, 16, 0, 2);

void callback(char* topic, byte* payload, unsigned int length) {
    // handle message arrived
}

TCPClient ethClient;
PubSubClient client(ethClient);

long lastReconnectAttempt = 0;

boolean reconnect() {
    if (client.connect("arduinoClient")) {
        // Once connected, publish an announcement...
        client.publish("outTopic","hello world");
        // ... and resubscribe
        client.subscribe("inTopic");
    }
    return client.connected();
}

void setup()
{
    client.setServer(server, 1883);
    client.setCallback(callback);

    delay(1500);
    lastReconnectAttempt = 0;
}

void loop()
{
    if (!client.connected()) {
        long now = millis();
        if (now - lastReconnectAttempt > 5000) {
            lastReconnectAttempt = now;
            // Attempt to reconnect
            if (reconnect()) {
                lastReconnectAttempt = 0;
            }
        }
    } else {
        // Client connected
        client.loop();
    }
}
