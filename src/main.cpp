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

String stations[15] = {
		"servidor32-4.brlogic.com:8572/live",
		"ic1.smcdn.pl/6030-1.mp3",
		"www.surfmusic.de/m3u/100-5-das-hitradio,4529.m3u",
		"stream.1a-webradio.de/deutsch/mp3-128/vtuner-1a",
		"mp3.ffh.de/radioffh/hqlivestream.aac", //  128k aac
		"www.antenne.de/webradio/antenne.m3u",
		"listen.rusongs.ru/ru-mp3-128",
		"edge.audio.3qsdn.com/senderkw-mp3",
		"macslons-irish-pub-radio.com/media.asx"
};

// some global variables

uint8_t max_volume = 21;
uint8_t cur_station = 1;
uint8_t cur_volume = max_volume/2;

//**************************************************************************************************
//                                           S E T U P                                             *
//**************************************************************************************************
Espradio radio = new Espradio(I2S_BCLK,I2S_LRC,I2S_DOUT);

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

	radio.radioget();
}

//**************************************************************************************************
//                                            L O O P                                              *
//**************************************************************************************************

void loop()
{
	// audio.loop();
}