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

        SteamAPImanager.SteamAPIInit(); //Initialisation de l'APi

    //{
        SteamAPImanager.SteamUpdate(); //Updatede l'API

        SteamAPImanager.ActivateOverlay(); //Activation de l'overlay et de l'interface

        GameQuiManage.SetSteamManager(&SteamAPImanager); 

        GameQuiManage.GetNumberOfCurrentPlayers(); //Récupération du nombre de joueur sur l'application

        GameQuiManage.selectGame(); //Choix de créer ou rejoindre un lobby

        GameQuiManage.Update();
    //}

    SteamAPImanager.SteamAPIQuit(); // Fin de l'élimination d l'API

    return 0;
}