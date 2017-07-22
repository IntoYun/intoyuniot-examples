/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example


 This example connects to a WPA-encrypted Wifi network.
 Then it prints the  MAC address of the Wifi,
 the IP address obtained, and other network details.

*/

char ssid[] = "yourNetwork";     //  your network SSID (name)
char pass[] = "secretPassword";  // your network password
int status = false;     // the Wifi radio's status

void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(115200);
	while (!Serial)
	{
		; // wait for serial port to connect. Needed for Leonardo only
	}

	status = WiFi.status();
	// attempt to connect to Wifi network:
	while ( status != true)
	{
		Serial.print("Attempting to connect to open SSID: ");
		Serial.println(ssid);
		WiFi.setCredentials(ssid, pass, WPA2);
		WiFi.connect();
		status = WiFi.status();
		// wait 15 seconds for connection:
		delay(15000);
	}

	// you're connected now, so print out the data:
	Serial.print("You're connected to the network");
	printCurrentNet();
	printWifiData();

}

void loop()
{
	// check the network connection once every 10 seconds:
	delay(10000);
	printCurrentNet();
}

void printWifiData()
{
	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);
	Serial.println(ip);

	// print your MAC address:
	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print("MAC address: ");
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

void printCurrentNet()
{
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print the MAC address of the router you're attached to:
	byte bssid[6];
	WiFi.BSSID(bssid);
	Serial.print("BSSID: ");
	Serial.print(bssid[5], HEX);
	Serial.print(":");
	Serial.print(bssid[4], HEX);
	Serial.print(":");
	Serial.print(bssid[3], HEX);
	Serial.print(":");
	Serial.print(bssid[2], HEX);
	Serial.print(":");
	Serial.print(bssid[1], HEX);
	Serial.print(":");
	Serial.println(bssid[0], HEX);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.println(rssi);
}
