#pragma once


namespace CheatManager
{
	/* ------------------------------------- UFortCheatManagerOG ------------------------------------- */


	/* -------------------------------------- UFortCheatManager -------------------------------------- */

	void InitCheatManager()
	{
		UFortCheatManager* FortCheatManagerDefault = UFortCheatManager::GetDefaultObj();
		UClass* FortCheatManagerClass = UFortCheatManager::StaticClass();

		/* -------------------------------------- UFortCheatManager -------------------------------------- */



		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitCheatManager Success!");
	}
}