#pragma once

namespace GameState
{
	/* ----------------------------------- AFortGameStateAthenaOG ------------------------------------ */
	bool (*ReadyToStartMatchOG)(AFortGameModeAthena* GameModeAthena);
	void (*HandlePostSafeZonePhaseChangedOG)(AFortGameModeAthena* GameModeAthena);
	bool (*StartAircraftPhaseOG)(AFortGameModeAthena* GameModeAthena);



	/* ------------------------------------ AFortGameStateAthena ------------------------------------- */

    bool IsOutOfSafeZone(AFortSafeZoneIndicator* SafeZoneIndicator, FVector Location)
    {
        UStaticMeshComponent* SafeZoneMesh = SafeZoneIndicator->SafeZoneMesh;
        const FVector& ComponentLocation = SafeZoneMesh->K2_GetComponentLocation();

        float v3 = ComponentLocation.Y;
        float v4 = ComponentLocation.X - Location.X;
        return std::sqrt((v3 - Location.Y) * (v3 - Location.Y) + v4 * v4) <= SafeZoneIndicator->Radius;
    }

	bool IsRespawningAllowed(AFortGameStateAthena* GameStateAthena, AFortPlayerState* PlayerState)
	{
        AFortPlayerStateAthena* PlayerStateAthena = Cast<AFortPlayerStateAthena>(PlayerState);
        if (!PlayerStateAthena) return false;

        UFortPlaylistAthena* CurrentPlaylistData = GameStateAthena->CurrentPlaylistData;
        if (!CurrentPlaylistData) return false;

        EAthenaRespawnType RespawnType = CurrentPlaylistData->RespawnType;

        if (RespawnType == EAthenaRespawnType::InfiniteRespawn)
            return true;

        if (RespawnType == EAthenaRespawnType::InfiniteRespawnExceptStorm)
        {
            if (!GameStateAthena->SafeZoneIndicator)
                return true;

            FDeathInfo DeathInfo = PlayerStateAthena->DeathInfo;

            if (!DeathInfo.bInitialized)
                return true;

            AFortSafeZoneIndicator* SafeZoneIndicator = GameStateAthena->SafeZoneIndicator;

            if (IsOutOfSafeZone(SafeZoneIndicator, DeathInfo.DeathLocation))
                return true;
        }

        return false;
    }

	void InitGameState()
	{
		AFortGameStateAthena* FortGameStateAthenaDefault = AFortGameStateAthena::GetDefaultObj();
        UClass* FortGameStateAthenaClass = AFortGameStateAthena::StaticClass();

		/* ------------------------------------ AFortGameStateAthena ------------------------------------- */
        /* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitGameState Success!");
	}
}