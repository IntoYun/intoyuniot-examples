/*
    TCP Server
    创建一个Tcp服务器, 回显tcp客户端发送的数据。
*/

SYSTEM_MODE(MANUAL)

uint16_t serverPort = 80;

TCPServer server = TCPServer(serverPort);

void setup()
{
    Serial.begin(115200);
    while(!WiFi.ready());

    Serial.print("Local IP: ");
    Serial.print(WiFi.localIP());
    Serial.print(", Local Port: ");
    Serial.println(serverPort);
    server.begin(); // start listening for clients
    Serial.println("TCP Server listening.");        // print a message out the serial port
}

void loop()
{
    TCPClient client = server.available();   // listen for incoming clients
    if (client) {                             // if you get a client,
        Serial.println("New Client.");        // print a message out the serial port
        while (client.connected()) {          // loop while the client's connected
            while (client.available()) {      // echo all available bytes back to the client
                char c = client.read();       // read a byte, then
                Serial.write(c);              // print it out the serial monitor
                client.write(c);
            }
        }
        client.stop();
        Serial.println("Client Disconnected.");
    }
}

