/*
   Basic MQTT example with Authentication

   - connects to an MQTT server, providing username
   and password
   - publishes "hello world" to the topic "outTopic"
   - subscribes to the topic "inTopic"
 */

#include <PubSubClient.h>

SYSTEM_MODE(SEMI_AUTOMATIC);

// Update these with values suitable for your network.
IPAddress ip(172, 16, 0, 100);
IPAddress server(172, 16, 0, 2);

void callback(char* topic, byte* payload, unsigned int length) {
    // handle message arrived
}

TCPClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

void setup()
{
    // Note - the default maximum packet size is 128 bytes. If the
    // combined length of clientId, username and password exceed this,
    // you will need to increase the value of MQTT_MAX_PACKET_SIZE in
    // PubSubClient.h
    if (client.connect("arduinoClient", "testuser", "testpass")) {
        client.publish("outTopic","hello world");
        client.subscribe("inTopic");
    }
}

void loop()
{
    client.loop();
}
