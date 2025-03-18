#include <Windows.h>
#include <iostream>
#include <thread>
#include <detours.h>
#include <regex>
#include <unordered_map>
#include <fstream>
#include <intrin.h>

#include "Minhook/Minhook.h"
#pragma comment(lib,"Minhook/Minhook.lib")

#include "SDK.hpp"

#include "Globals.h"
#include "MinHook.h"
#include "Patterns.h"
#include "Util.h"

#include "Functions/NewInventory.h"

#include "Functions/Loots.h"
#include "Functions/Functions.h"

#include "Functions/Abilities.h"

#include "Functions/Beacon.h"

#include "Globals/GameState.h"
#include "Globals/GameMode.h"

#include "Globals/QuestManager.h"
#include "Globals/PlayerController.h"
#include "Globals/Pawn.h"
#include "Globals/FortKismetLibrary.h"
#include "Globals/FortAthenaSupplyDrop.h"
#include "Globals/BuildingActor.h"
#include "Globals/BuildingProp.h"
#include "Globals/Pickup.h"
#include "Globals/CheatManager.h"

#include <fstream>
#include "Hooks.h"
#include "InitFunc.h"

DWORD WINAPI MainThread(LPVOID)
{
    FILE* fDummy;
    AllocConsole();
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    MH_Initialize();

    SetConsoleTitleA("Ares 5.41");
    srand(time(0));

    if (true)
    {
        APlayerController* PlayerController = Globals::GetServerPlayerController();

        if (PlayerController)
        {
            InitFunc::InitializeAll();

            UFortConsole* NewConsole = Cast<UFortConsole>(UGameplayStatics::SpawnObject(UFortConsole::StaticClass(), GEngine->GameViewport));

            if (NewConsole)
                GEngine->GameViewport->ViewportConsole = NewConsole;

            PlayerController->SwitchLevel(L"Athena_Terrain");
            //PlayerController->SwitchLevel(L"Athena_Faceoff");
            // PlayerController->SwitchLevel(L"Zone_Temperate_Forest?game=/Game/Athena/Athena_GameMode.Athena_GameMode_C");

            Hooks::InitHook();
        }

        *(bool*)Hooks::GIsClient() = false;
        *(bool*)Hooks::GIsServer() = true;

        FN_LOG(LogInitialize, Log, L"ImageBase: [%p]", InSDKUtils::GetImageBase());
        FN_LOG(LogInitialize, Log, L"Init Success!");
    }
    else
    {
        FN_LOG(LogInitialize, Log, L"Init Failed!");
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID res)
{
    if (reason == 1)
        CreateThread(0, 0, MainThread, mod, 0, 0);

    return TRUE;
}