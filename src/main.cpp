#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include "Audio.h"
#include "Espradio.h"

#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC 26
#define stbt 19
#define volbt 18



String ssid = "OkrzejaWiFi";
// String password = "25422800#!@";
String password = "MorskaOkrzeja!";


// some global variables

uint8_t max_volume = 21;
uint8_t cur_station = 1;
uint8_t cur_volume = max_volume/2;

//**************************************************************************************************
//                                           S E T U P                                             *
//**************************************************************************************************
Espradio radio = Espradio(I2S_BCLK,I2S_LRC,I2S_DOUT);

void setup()
{

	Serial.begin(115200);

	WiFi.begin(ssid.c_str(), password.c_str());
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(2000);
		Serial.print("[ERROR] WiFi connection failed");
	}
	
	log_i("Connect to %s", WiFi.SSID().c_str());

	radio.get();
	
}

//**************************************************************************************************
//                                            L O O P                                              *
//**************************************************************************************************

void loop()
{
	// audio.loop();
}