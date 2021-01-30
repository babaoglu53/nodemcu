#define WIFI_NAME ""
#define WIFI_PASSWORD ""
#define DEVICE_ID 2
#define DEVICE_NAME "relay_project"
#define TOKEN "~905304_23t3FtUCBzHqKYwxqwINikWy"
#define RELAY_PIN 0

#include <ESP8266WiFi.h>
#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>


RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

inline void setRelay_control(boolean state)
{
  remoteMe.getVariables()->setBoolean("relay_control", state);
}

void onRelay_controlChange(boolean state) 
{
  digitalWrite(RELAY_PIN, state?HIGH:LOW);
}

void setup() {
  
  pinMode(RELAY_PIN, OUTPUT);

  Serial.begin(9600);
  
	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  Serial.println("CONNECTING..."); 
  
	while (WiFi.status() != WL_CONNECTED)
	{
    Serial.print(".");
		delay(100);
	}

  Serial.println("WIFI CONNECTED...");

	remoteMe.getVariables()->observeBoolean("relay_control" ,onRelay_controlChange);

	remoteMe.setConnector(new RemoteMeSocketConnector());
	remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);

  Serial.println("RELAY CONNECTED...");
  
  digitalWrite(RELAY_PIN, LOW);
}


void loop()
{
	remoteMe.loop();
}
