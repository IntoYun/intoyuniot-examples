

TCPServer server = TCPServer(5555);
TCPClient client,client_bak;

char c;

void setup()
{
  // start listening for clients
  server.begin();
  Serial.begin(115200);
}
void loop()
{
    if (client.connected()) {
        // echo all available bytes back to the client
        while (client.available()) {
            server.write(client.read());
        }
    } else {
        // if no client is yet connected, check for a new connection
        client = server.available();
    }
}
