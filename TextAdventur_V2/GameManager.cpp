#include "GameManager.h"
#include <iostream>
#include <stdio.h>

void GameManager::OnFriendStatusChanged(PersonaStateChange_t* pCallback) //Fonction permettant de signaler un changement de statut des amis steam
{
    const char* friendName = SteamFriends()->GetFriendPersonaName(pCallback->m_ulSteamID);
    EPersonaState friendStatusEnum = SteamFriends()->GetFriendPersonaState(pCallback->m_ulSteamID);

    const char* friendStatus;
    switch (friendStatusEnum)
    {
    case k_EPersonaStateOffline:
        friendStatus = "offline";
        break;
    case k_EPersonaStateOnline:
        friendStatus = "online";
        break;
    case k_EPersonaStateBusy:
        friendStatus = "busy";
        break;
    case k_EPersonaStateAway:
        friendStatus = "away";
        break;
    case k_EPersonaStateSnooze:
        friendStatus = "set on snooze";
        break;
    case k_EPersonaStateLookingToTrade:
        friendStatus = "looking to trade";
        break;
    case k_EPersonaStateLookingToPlay:
        friendStatus = "looking to play";
        break;
    case k_EPersonaStateInvisible:
        friendStatus = "invisible";
        break;
    default:
        friendStatus = "unkown status";
        break;
    }

    std::cout << friendName << " status is now " << friendStatus << " !" << std::endl;
}

GameManager::GameManager()  //Implantation de variable gérant la boucle d'update
{
    bRunning = true;
    pSteamManager = nullptr;
}

void GameManager::SetSteamManager(SteamAPImanager* pSteamManager)
{
    this->pSteamManager = pSteamManager;
}

void GameManager::Update()
{
    while (bRunning)
    {
        if (pSteamManager != nullptr)
        {
            pSteamManager->SteamUpdate();
           // pSteamManager->GetFriends();
            //selectGame();
        }
    }
}

// Make the asynchronous request to receive the number of current players.
void GameManager::GetNumberOfCurrentPlayers()
{
    printf("Getting Number of Current Players\n");
    SteamAPICall_t hSteamAPICall = SteamUserStats()->GetNumberOfCurrentPlayers();
    m_NumberOfCurrentPlayersCallResult.Set(hSteamAPICall, this, &GameManager::OnGetNumberOfCurrentPlayers);
}

// Called when SteamUserStats()->GetNumberOfCurrentPlayers() returns asynchronously, after a call to SteamAPI_RunCallbacks().
void GameManager::OnGetNumberOfCurrentPlayers(NumberOfCurrentPlayers_t* pCallback, bool bIOFailure)
{
    if (bIOFailure || !pCallback->m_bSuccess)
    {
        printf("NumberOfCurrentPlayers_t failed!\n");
        return;
    }

    printf("Number of players currently playing: %d\n", pCallback->m_cPlayers);
}

//--------------------------------------------------------------
//Permet à l'utilisateur de créer ou de rejoindre un lobby
//--------------------------------------------------------------
void GameManager::selectGame()
{
    int choice = 0;
    char serv = 'a';
    uint64 lobbyID64;

    std::cout << " Désirez vous créer ou rejoindre un lobby? Entrez 1 pour creer, 2 pour rejoindre, 3 pour mettre à jour ";

    std::cin >> choice;

    if (choice == 1)
    {
        //int cMaxMembers = 2;
        //SteamAPICall_t CreateLobby(ELobbyType k_ELobbyTypePublic, int cMaxMembers);
        LobbyCreation();
    }
    else if (choice == 2)
    {
        //std::cout << " Recherche de lobby ";
        //FindLobbies();

        std::cout << " Entrez le lobby ID ";
        std::cin >> lobbyID64;

        join_lobby(lobbyID64);

        /*std::cout << " Désirez vous rejoindre un serveur? (Y/N) "; //Code censé mener au lancement d'un serveur
        std::cin >> serv;

        if (serv == 'Y' || serv == 'y')
        {
            ServerJoin();
        }
        else if (serv == 'N' || serv == 'n')
        {
            return;
        }*/

    }
    else if (choice == 3)       //Elément permettant d'updater manuellement lorsque la fonction se trouvait dans l'Update
    {
        std::cout << " UPDATE ";
    }
}

//--------------------------------------------------------------
//Création de lobby
//--------------------------------------------------------------
void GameManager::LobbyCreation()
{
    SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(k_ELobbyTypePublic, 2);
    m_LobbyCreatedCallResult.Set(hSteamAPICall, this, &GameManager::OnLobbyCreated);
}

void GameManager::OnLobbyCreated(LobbyCreated_t* pCallback, bool bIOFailure)
{
    if (bIOFailure || !pCallback->m_eResult)
    {
        printf(" Création de lobby échouée! \n");
        return;
    }

    printf(" Lobby créer %lld \n", pCallback->m_ulSteamIDLobby);
}

//--------------------------------------------------------------
//Recherche et jonction d'un lobby
//--------------------------------------------------------------
/*void GameManager::FindLobbies()
{
    // SteamMatchmaking()->AddRequestLobbyListFilter*() functions would be called here, before RequestLobbyList()
    SteamAPICall_t hSteamAPICall = SteamMatchmaking()->RequestLobbyList();
    m_CallResultLobbyMatchList.Set(hSteamAPICall, this, &GameManager::OnLobbyMatchList);
}

void GameManager::OnLobbyMatchList(LobbyMatchList_t* pCallback, bool bIOFailure)
{
    // lobby list has been retrieved from Steam back-end, use results
    if (bIOFailure || !pCallback->m_nLobbiesMatching)
    {
        printf(" No lobby found! \n");
        return;
    }

    printf(" Lobby list found ", pCallback->m_nLobbiesMatching);

    //int lobbyNum = 0;

    printf(" Entrez le LobbyID ", pCallback->m_nLobbiesMatching);
    //std::cin >> lobbyNum;

    for (int i = 0; i < pCallback->m_nLobbiesMatching; i++)
    {
        CSteamID LobbyID = SteamMatchmaking()->GetLobbyByIndex(i);

        if (LobbyID.IsLobby() && SteamMatchmaking()->GetNumLobbyMembers(LobbyID) > 4)
        //if (LobbyID.IsLobby())
        {
            std::cout << "Lobby number : " << i << std::endl;
            SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby(LobbyID);
            m_LobbyEnterCallResult.Set(hSteamAPICall, this, &GameManager::OnLobbyEntered);
            break;
        }
    }
}*/

//--------------------------------------------------------------
//Jonction à un lobby
//--------------------------------------------------------------

void GameManager::join_lobby(uint64 lobby_id64) {
    CSteamID lobbyID = CSteamID(lobby_id64);

    if (lobby_id64 <= 0) {
        std::cout <<  "Erreur, lobby introuvable " << lobby_id64 << " dans SteamNetwork::join_lobby";
        return;
    }

    SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby(lobbyID);
    m_LobbyEnterCallResult.Set(hSteamAPICall, this, &GameManager::OnLobbyEntered);
}

void GameManager::OnLobbyEntered(LobbyEnter_t* pCallback, bool bIOFailure)
{
    int nb = SteamMatchmaking()->GetNumLobbyMembers(pCallback->m_ulSteamIDLobby);
    for (int i = 0; i < nb; i++)
    {
        CSteamID UserID = SteamMatchmaking()->GetLobbyMemberByIndex(pCallback->m_ulSteamIDLobby, i);

        const char* userName = SteamFriends()->GetFriendPersonaName(UserID);
        std::cout << "utilisateur : " << userName << std::endl;

        const char* oldUserName = SteamFriends()->GetFriendPersonaNameHistory(UserID, 0);
        std::cout << "Ancien nom utilisateur : " << oldUserName << std::endl;
    }
}

