#include <Arduino.h>
#include <Audio.h>
#include "Espradio.h"

Audio audio = new Audio();
String stations[];

Espradio::Espradio(uint8_t I2S_BCLK, uint8_t I2S_LRC, uint8_t I2S_DOUT){
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
}

Espradio::~Espradio(){
    
}

//**************************************************************************************************
//                                           E V E N T S                                           *
//**************************************************************************************************

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

String topcommands[] = {"spk", "vol", "radio"};
String subspk[] = {"mute"};
String subvol[] = {"full", "low"};
String subradio[] = {"put", "get", "set", "rm", "play"};

int Espradio::radioplaypos(int pos){
	return 0;
}

int Espradio::radioplay(String url)
{
	audio.stopSong();
	audio.connecttohost(url.c_str());
	// log "[INFO] Starting playing x"
	audio.loop();
	return 0;
}

int Espradio::radiorm(int pos)
{
	stations[pos] = "";
	return 0;
}

int Espradio::radioset(int pos, String url)
{
	stations[pos] = url;
	return 0;
}

int Espradio::radioput(String url)
{
	for (int x = 0; x < stations->length(); x++)
	{
		if (stations[x] == "")
		{
			stations[x] = url;
			return 0;
		}
	}
	return 1;
}

String Espradio::radioget(int pos = 0)
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

int Espradio::spkmute()
{
	audio.setVolume(0);
	return 0;
}

int Espradio::volchange(int volume)
{
	if (cur_volume >= max_volume)
	{
		cur_volume = max_volume;
	}
	audio.setVolume(volume);
	return 0;
}

int Espradio::volminmax(bool max)
{
	if (max)
	{
		audio.setVolume(max_volume);
		return 0;
	}
	audio.setVolume(1);
	return 0;
}

int Espradio::readSerial()
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

int Espradio::sendSerial(String message, bool nl = 1)
{
	if (nl)
	{
		Serial.println("> " + message);
		return 0;
	}
	Serial.print(message);
	return 1;
}