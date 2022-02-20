#pragma once
#include "SteamAPImanager.h"
#include "..//Header/steam_api.h"

class GameManager
{
private:
    SteamAPImanager* pSteamManager;

    //CALLBACK
    STEAM_CALLBACK(GameManager, OnFriendStatusChanged, PersonaStateChange_t);
    //STEAM_CALLBACK(GameManager, LobbyCreation, LobbyCreated_t);

    //CALL RESULTS
    void OnGetNumberOfCurrentPlayers(NumberOfCurrentPlayers_t* pCallback, bool bIOFailure);
    CCallResult< GameManager, NumberOfCurrentPlayers_t > m_NumberOfCurrentPlayersCallResult;

    void OnLobbyCreated(LobbyCreated_t* pCallback, bool bIOFailure);
    CCallResult<GameManager, LobbyCreated_t> m_LobbyCreatedCallResult;

    /*void OnLobbyMatchList(LobbyMatchList_t* pCallback, bool bIOFailure);
    CCallResult<GameManager, LobbyMatchList_t> m_CallResultLobbyMatchList;*/

    void join_lobby(uint64 lobby_id64);
    CCallResult<GameManager, LobbyMatchList_t> m_CallResultLobbyMatchList;

    void OnLobbyEntered(LobbyEnter_t* pCallback, bool bIOFailure);
    CCallResult<GameManager, LobbyEnter_t> m_LobbyEnterCallResult;

public:
    bool bRunning;

    int member = 0;

    //Constructeurs
    GameManager();

    //Mutateurs
    void SetSteamManager(SteamAPImanager* pSteamManager);

    //Fonctions
    void Update();

    void GetNumberOfCurrentPlayers();

    void selectGame();

    void LobbyCreation();

    //void FindLobbies();

    void ServerJoin();


};
