#include <iostream>
#include "..//Header/steam_api.h"
#include "SteamAPImanager.h"
#include "GameManager.h"

int main()
{
    setlocale(LC_ALL, "");

    //-------------------------------------------------
    //    INITIALISATION
    //-------------------------------------------------
    /*if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid)) // Replace with your App ID
    {
        return 1;
    }

    if (!SteamAPI_Init())
    {
        printf("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n");
        return 2;
    }*/

    SteamAPImanager SteamAPImanager;
    GameManager GameQuiManage;

        SteamAPImanager.SteamAPIInit();

    //{
        SteamAPImanager.SteamUpdate();

        SteamAPImanager.ActivateOverlay();

        GameQuiManage.SetSteamManager(&SteamAPImanager);

        GameQuiManage.GetNumberOfCurrentPlayers();

        GameQuiManage.selectGame();

        GameQuiManage.Update();

        //GameQuiManage.selectGame();
    //}

    SteamAPImanager.SteamAPIQuit();

    return 0;
}