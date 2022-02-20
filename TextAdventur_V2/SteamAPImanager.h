#pragma once
#ifndef STEAMAPIMANAGER_H
#define STEAMAPIMANAGER_H
#include "..//Header/steam_api.h"
#include "..//Header/isteamfriends.h"
#include <direct.h>
//#include <fstream>
#include <iostream>

class SteamAPImanager
{
private:

public:
	SteamAPImanager();

	bool SteamAPIInit();
	void SteamAPIQuit();
	void GetFriends();
	void SteamUpdate();
	void ActivateOverlay();
};

#endif
