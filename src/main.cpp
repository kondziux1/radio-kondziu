#include <Arduino.h>
#include <Preferences.h>
#include <SPI.h>
#include <WiFi.h>
#include "Audio.h" //see my repository at github "https://github.com/schreibfaul1/ESP32-audioI2S"

#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC 26
#define stbt 19
#define volbt 18

Preferences pref;
Audio audio;

String ssid = "OkrzejaWiFi";
// String password = "25422800#!@";
String password = "MorskaOkrzeja!";

String stations[15] = {
		"servidor32-4.brlogic.com:8572/live",
		"ic1.smcdn.pl/6030-1.mp3",
		"http://10.0.0.10:8000/hee.aac",
		"http://10.0.0.10:8000/micikor.mp3",
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
String cheese = "";
//**************************************************************************************************
//                                           S E T U P                                             *
//**************************************************************************************************
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
	audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
	audio.setVolume(cur_volume); // 0...21
	audio.connecttohost(stations[cur_station].c_str());
}
//**************************************************************************************************
//                                            L O O P                                              *
//**************************************************************************************************
void loop()
{
	// audio.loop();
}

// spk - speaker commands
// -----------
// spk mute - mutes speaker
//
// #############
//
// vol - volume settings
// -----------
// vol full - sets max volume
// vol low - sets lowest volume
// vol <volume> - sets exact volume from 1 to 27 later from 1 to 100 so we can do scalling hihi :3
//
// #############
//
// radio - commands for radio player
// ------------
// get ?<position> - get url of a station at given position || if no position given list all stations
// put [url] - append at end stored stations
// set <position> [url] - changes station at given position
// rm <position> - removes a station at given position
// play [url] - force play and not add to stored stations
// playpos <position> - plays saved station

int radioplay(String url)
{
	audio.stopSong();
	audio.connecttohost(url.c_str());

	audio.loop();
}

int radiorm(int pos)
{
	stations[pos] = "";
	return 0;
}

int radioset(int pos, String url)
{
	stations[pos] = url;
	return 0;
}

int radioput(String url)
{
	for (int x = 0; x < stations->length(); x++)
	{
		if (stations[x] == "")
		{
			stations[x] = url;
			return 0;
		}
	}
}

String radioget(int pos = 0)
{
	if (pos != 0)
	{
		return stations[pos];
	}
	String formated;
	formated = "=========== STATIONS ===========\n";
	formated += "Now playing: " + stations[cur_station];
	for (int x = 0; x < stations->length(); x++)
	{
		if (stations[x] != stations[cur_station])
		{
			formated += (String(x + 1) + ") " + stations[x] + "\n");
		}
		formated += (String(x + 1) + ") " + stations[x] + " - NOW PLAYING\n");
	}
	return formated;
}

int spkmute()
{
	audio.setVolume(0);
	return 0;
}

int volchange(int volume)
{
	if (cur_volume >= max_volume)
	{
		cur_volume = max_volume;
	}
	audio.setVolume(volume);
	return 0;
}

int volminmax(bool max)
{
	if (max)
	{
		audio.setVolume(max_volume);
		return 0;
	}
	audio.setVolume(1);
}

String topcommands[] = {"spk", "vol", "radio"};
String subspk[] = {"mute"};
String subvol[] = {"full", "low"};
String subradio[] = {"put", "get", "set", "rm", "play"};

int readSerial()
{
	String cheese = Serial.readString();

	int cheeselng = 0;

	if (cheese.length() < 0)
	{
		return 1;
	}

	cheeselng = cheese.length();

	char curentchar;

	for (int x = 0; x < cheeselng; x++)
	{
	}

	return 0;
}
// function printf not supported
int sendSerial(String message, bool nl = 1)
{
	if (nl)
	{
		Serial.println("> " + message);
		return 0;
	}
	Serial.print(message);
	return 1;
}

//**************************************************************************************************
//                                           E V E N T S                                           *
//**************************************************************************************************
void audio_info(const char *info)
{
	Serial.print("audio_info: ");
	Serial.println(info);
}
