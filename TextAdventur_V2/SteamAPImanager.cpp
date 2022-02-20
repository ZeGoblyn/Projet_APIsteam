#include <iostream>
#include "SteamAPImanager.h"

SteamAPImanager::SteamAPImanager()
//Constructeur
{}

bool SteamAPImanager::SteamAPIInit()
//BUT : Initialisation de l'API Steam
{
	if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid))
	{
		//return EXIT_FAILURE;
		printf_s("Erreur lors du rechargement de l'api steam.");
		return false;
	}

	// Initialize SteamAPI, if this fails we bail out since we depend on Steam for lots of stuff.
	// This will also load the in-game steam overlay dll into your process.  
	if (!SteamAPI_Init())
	{
		printf_s("Erreur lors de l'initialisation de l'api steam.");
		return false;
	}

	// Ensure that the user has logged into Steam.
	if (!SteamUser()->BLoggedOn())
	{
		printf_s("Fatal Error Steam user must be logged in to play this game (SteamUser()->BLoggedOn() returned false).\n");
		return false;
	}

	if (!SteamInput()->Init(false))
	{
		printf_s("Fatal Error SteamInput()->Init failed.\n");
		return false;
	}


	//Test du Steamworks Interfaces pour afficher le nom de l'utilisateur.
	const char* name = SteamFriends()->GetPersonaName();
	printf_s(name);

	return true;
}

void SteamAPImanager::SteamAPIQuit()
//BUT : Fermeture de l'API Steam
{
	SteamAPI_Shutdown();

}

void SteamAPImanager::SteamUpdate()	//Implantation de la gestion de Callback
{
	SteamAPI_RunCallbacks();
}

void SteamAPImanager::ActivateOverlay()
{
	//printf_s("Activate overlay\n");
	SteamFriends()->ActivateGameOverlay("friends"); //Activation des fonctions d'Overlay
}

void SteamAPImanager::GetFriends()	
{
	int nFriends = SteamFriends()->GetFriendCount(k_EFriendFlagAll);

	if (nFriends == -1)
	{
		std::cout << "GetFriendCount returned -1, the current user is not logged in." << std::endl;
		// We always recommend resetting to 0 just in case you were to do something like allocate
		// an array with this value, or loop over it in a way that doesn't take into the -1 into account.
		nFriends = 0;
	}

	for (int i = 0; i < nFriends; i++)
	{
		CSteamID friendSteamID = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagImmediate);
		const char* friendName = SteamFriends()->GetFriendPersonaName(friendSteamID);
		SteamFriends()->RequestUserInformation(friendSteamID, true);
	}
}