/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example


 This example  prints the Wifi MAC address, and
 scans for available Wifi networks using the Wifi shield.
 Every ten seconds, it scans again. It doesn't actually
 connect to any network, so no encryption scheme is specified.

 */

void printMacAddress()
{
    // the MAC address of your Wifi shield
    byte mac[6];

    // print your MAC address:
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);
}

void listNetworks()
{
    WiFiAccessPoint ap[10];
    // scan for nearby networks:
    Serial.println("** Scan Networks **");
    int numSsid = WiFi.scan(ap,10);
    if (numSsid == -1)
    {
        Serial.println("Couldn't get a wifi connection");
        while (true);
    }

    // print the list of networks seen:
    Serial.print("number of available networks:");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
        Serial.print(thisNet);
        Serial.print(") ");
        Serial.print(ap[thisNet].ssid);
        Serial.print("\tSignal: ");
        Serial.print(ap[thisNet].rssi);
        Serial.print(" dBm");
    }
}


void setup()
{
    //Initialize serial and wait for port to open:
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    // check for the presence of the shield:
    if (WiFi.status() == false)
    {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
    }

    // Print WiFi MAC address:
    printMacAddress();

    // scan for existing networks:
    Serial.println("Scanning available networks...");
    listNetworks();
}

void loop()
{
    delay(10000);
    // scan for existing networks:
    Serial.println("Scanning available networks...");
    listNetworks();
}

