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

	//Gestion de l'API
	bool SteamAPIInit();
	void SteamAPIQuit();

	//Recupération d'ami
	void GetFriends();
	void SteamUpdate();

	//Activation de l'overlay
	void ActivateOverlay();
};

#endif
