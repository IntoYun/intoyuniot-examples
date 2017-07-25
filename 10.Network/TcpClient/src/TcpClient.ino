TCPClient client;
byte server[] = {202,108,22,5}; // baidu

void setup()
{
    // Make sure your SerialUSB Terminal app is closed before powering your Core
    // Now open your SerialUSB Terminal, and hit any key to continue!
    Serial.begin(115200);
    while(!Serial.available());

    Serial.println("connecting...");

    if (client.connect(server, 80))
    {
        Serial.println("connected");
        client.println("GET /search?q=unicorn HTTP/1.0");
        client.println("Host: www.baidu.com");
        client.println("Content-Length: 0");
        client.println();
    }
    else
    {
        Serial.println("connection failed");
    }
}

void loop()
{
    if (client.available())
    {
        char c = client.read();
        Serial.print(c);
    }

    if (!client.connected())
    {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();
        for(;;);
    }
}
