#pragma once

namespace GameMode
{
	/* ------------------------------------ AFortGameModeAthenaOG ------------------------------------ */
	bool (*ReadyToStartMatchOG)(AFortGameModeAthena* GameModeAthena);
	void (*HandlePostSafeZonePhaseChangedOG)(AFortGameModeAthena* GameModeAthena);
	bool (*StartAircraftPhaseOG)(AFortGameModeAthena* GameModeAthena);


	/* ------------------------------------- AFortGameModeAthena ------------------------------------- */

	bool ReadyToStartMatch(AFortGameModeAthena* GameModeAthena)
	{
		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(GameModeAthena->GameState);

		if (GameStateAthena && !GameStateAthena->bPlaylistDataIsLoaded)
		{
			FURL URL;
			URL.Port = 7777;
			Beacon::ListenServer(GameModeAthena->GetWorld(), URL);

			AOnlineBeacon;

			int32 PlaylistId = 2; // Solo
			// int32 PlaylistId = 10; // Duo
			// int32 PlaylistId = 9; // Squad
			// int32 PlaylistId = 35; // Playground 
			// int32 PlaylistId = 50; // 50VS50
			// int32 PlaylistId = 140; // Bling Solo 
			// int32 PlaylistId = 44; // Close Solo
			// int32 PlaylistId = 185; // Soaring Solo

			UFortPlaylistAthena* PlaylistAthena = GameModeAthena->PlaylistManager->GetPlaylistByPlaylistId(PlaylistId);

			if (PlaylistAthena)
			{
				/*PlaylistAthena->MaxPlayers = 16;
				PlaylistAthena->MaxTeamCount = 16;
				PlaylistAthena->MaxTeamSize = 4;
				PlaylistAthena->MaxSocialPartySize = 4;
				PlaylistAthena->MaxSquadSize = 4;*/

				Functions::SetPlaylistData(GameModeAthena, PlaylistAthena);

				FGameplayTagContainer GameplayTagContainer = PlaylistAthena->GameplayTagContainer;

				TArray<FGameplayTag> GameplayTags = GameplayTagContainer.GameplayTags;
				TArray<FGameplayTag> ParentTags = GameplayTagContainer.ParentTags;

				FN_LOG(LogGameMode, Log, L"GameplayTags.Num(): %i", GameplayTags.Num());
				FN_LOG(LogGameMode, Log, L"ParentTags.Num(): %i", ParentTags.Num());

				for (int32 i = 0; i < GameplayTags.Num(); i++)
				{
					FGameplayTag GameplayTag = GameplayTags[i];

					FN_LOG(LogGameMode, Log, L"%i - GameplayTag: %s", i, UKismetStringLibrary::Conv_NameToString(GameplayTag.TagName).ToString().c_str());
				}

				for (int32 i = 0; i < ParentTags.Num(); i++)
				{
					FGameplayTag ParentTag = ParentTags[i];

					FN_LOG(LogGameMode, Log, L"%i - ParentTag: %s", i, UKismetStringLibrary::Conv_NameToString(ParentTag.TagName).ToString().c_str());
				}

				FN_LOG(LogGameMode, Log, L"[AGameMode::ReadyToStartMatch] AISettings: %s", GameModeAthena->AISettings->GetName().c_str());
				FN_LOG(LogGameMode, Log, L"[AGameMode::ReadyToStartMatch] AIDirector: %s", GameModeAthena->AIDirector->GetName().c_str());
				FN_LOG(LogGameMode, Log, L"[AGameMode::ReadyToStartMatch] AIGoalManager: %s", GameModeAthena->AIGoalManager->GetName().c_str());
				FN_LOG(LogGameMode, Log, L"[AGameMode::ReadyToStartMatch] PlaylistAthena: %s", PlaylistAthena->GetName().c_str());
				FN_LOG(LogGameMode, Log, L"[AGameMode::ReadyToStartMatch] Choose Playlist Finish!");

				GameStateAthena->bPlaylistDataIsLoaded = true;
			}
		}

		return ReadyToStartMatchOG(GameModeAthena);
	}

	AFortPlayerPawn* SpawnDefaultPawnFor(AFortGameModeAthena* GameModeAthena, AController* NewPlayer, AActor* StartSpot)
	{
		if (!NewPlayer || !StartSpot)
			return nullptr;

		AFortPlayerControllerAthena* PlayerControllerAthena = Cast<AFortPlayerControllerAthena>(NewPlayer);
		AFortPlayerStateAthena* PlayerStateAthena = Cast<AFortPlayerStateAthena>(NewPlayer->PlayerState);

		if (!PlayerControllerAthena || !PlayerStateAthena)
			return nullptr;

		AFortPlayerPawn* PlayerPawn = GameModeAthena->SpawnDefaultPawnFor(PlayerControllerAthena, StartSpot);
		
		if (!PlayerPawn)
			return nullptr;

		UFortAbilitySystemComponent* AbilitySystemComponent = PlayerStateAthena->AbilitySystemComponent;

		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->ClearAllAbilities();

			UFortGameData* GameData = Globals::GetGameData();
			UFortAbilitySet* DefaultAbilities = Functions::LoadAbilitySet(GameData->GenericPlayerAbilitySet);

			Abilities::GrantGameplayAbility(DefaultAbilities, AbilitySystemComponent);
			Abilities::GrantGameplayEffect(DefaultAbilities, AbilitySystemComponent);
			Abilities::GrantModifierAbilityFromPlaylist(AbilitySystemComponent);
		}

		PlayerStateAthena->ApplyCharacterCustomization(PlayerPawn);

		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(Globals::GetGameState());
		if (!GameStateAthena) return nullptr;

		bool bIsRespawningAllowed = GameState::IsRespawningAllowed(GameStateAthena, PlayerStateAthena);

		if ((bIsRespawningAllowed && GameStateAthena->GamePhase <= EAthenaGamePhase::Aircraft) || !bIsRespawningAllowed)
		{
			UFortWeaponMeleeItemDefinition* PickaxeItemDefinition = nullptr;

			if (PlayerControllerAthena)
			{
				UAthenaPickaxeItemDefinition* AthenaPickaxeItemDefinition = PlayerControllerAthena->CustomizationLoadout.Pickaxe;

				if (AthenaPickaxeItemDefinition)
					PickaxeItemDefinition = AthenaPickaxeItemDefinition->WeaponDefinition;

				if (!PickaxeItemDefinition)
				{
					UFortGameData* GameData = Globals::GetGameData();
					UAthenaPickaxeItemDefinition* DefaultPickaxeSkin = GameData->DefaultPickaxeSkin;

					if (DefaultPickaxeSkin)
						PickaxeItemDefinition = DefaultPickaxeSkin->WeaponDefinition;
				}
			}

			Inventory::SetupInventory(PlayerControllerAthena, PickaxeItemDefinition);
		}
		
#ifdef AUTORELOADWEAPON
		if (bIsRespawningAllowed && GameStateAthena->GamePhase >= EAthenaGamePhase::Warmup)
		{
			for (int32 i = 0; i < PlayerControllerAthena->WorldInventory->Inventory.ItemInstances.Num(); i++)
			{
				UFortWorldItem* ItemInstance = PlayerControllerAthena->WorldInventory->Inventory.ItemInstances[i];
				if (!ItemInstance) continue;

				UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(ItemInstance->ItemEntry.ItemDefinition);

				if (WorldItemDefinition)
				{
					UFortWeaponItemDefinition* WeaponItemDefinition = Cast<UFortWeaponItemDefinition>(WorldItemDefinition);

					if (WeaponItemDefinition)
					{
						FFortBaseWeaponStats* WeaponStats = Inventory::GetWeaponStats(WeaponItemDefinition);
						if (!WeaponStats) continue;

						PlayerControllerAthena->ModLoadedAmmo(ItemInstance->ItemEntry.ItemGuid, WeaponStats->ClipSize);
					}
				}
			}
		}
#endif // AUTORELOADWEAPON

		/*UFortPlaylistAthena* CurrentPlaylistData = GameStateAthena->CurrentPlaylistData;

		if (CurrentPlaylistData)
		{
			int32 SquadIdNum = 0;
			for (int32 i = 0; i < GameStateAthena->Teams.Num(); i++)
			{
				AFortTeamInfo* TeamInfo = GameStateAthena->Teams[i];
				if (!TeamInfo) continue;

				if (TeamInfo->Team != PlayerStateAthena->TeamIndex)
					continue;

				for (int32 j = 0; j < TeamInfo->TeamMembers.Num(); j++)
				{
					AController* TeamMember = TeamInfo->TeamMembers[j];
					if (!TeamMember) continue;

					AFortPlayerStateAthena* TeamMemberPlayerState = Cast<AFortPlayerStateAthena>(TeamMember->PlayerState);
					if (!TeamMemberPlayerState) continue;

					if (TeamMemberPlayerState->SquadId == uint8(PlayerStateAthena->TeamIndex))
						SquadIdNum++;
				}
			}

			if (SquadIdNum < CurrentPlaylistData->MaxSquadSize && (PlayerStateAthena->SquadId < CurrentPlaylistData->MaxSquads || CurrentPlaylistData->MaxSquads == -1))
			{
				PlayerStateAthena->SquadId = uint8(PlayerStateAthena->TeamIndex);
				PlayerStateAthena->OnRep_SquadId();
			}
		}*/

		PlayerStateAthena->SquadId = uint8(PlayerStateAthena->TeamIndex);
		PlayerStateAthena->OnRep_SquadId();

		uintptr_t Offset = uintptr_t(_ReturnAddress()) - InSDKUtils::GetImageBase();
		uintptr_t IdaAddress = Offset + 0x7FF66E650000ULL;

		FN_LOG(LogMinHook, Log, L"Function [SpawnDefaultPawnFor] successfully hooked with Offset [0x%llx], IdaAddress [%p]", (unsigned long long)Offset, IdaAddress);

		return PlayerPawn;
	}

	void HandlePostSafeZonePhaseChanged(AFortGameModeAthena* GameModeAthena)
	{
		FN_LOG(LogGameMode, Log, L"[AFortGameModeAthena::HandlePostSafeZonePhaseChanged] GameModeAthena: %s", GameModeAthena->GetName().c_str());
		FN_LOG(LogGameMode, Log, L"[AFortGameModeAthena::HandlePostSafeZonePhaseChanged] called!");

		HandlePostSafeZonePhaseChangedOG(GameModeAthena);
	}

	bool StartAircraftPhase(AFortGameModeAthena* GameModeAthena)
	{
		TArray<AFortPlayerController*> AllFortPlayerController = UFortKismetLibrary::GetAllFortPlayerControllers(GameModeAthena, true, true);

		for (int32 i = 0; i < AllFortPlayerController.Num(); i++)
		{
			AFortPlayerController* PlayerController = AllFortPlayerController[i];
			if (!PlayerController) continue;

			Inventory::ResetInventory(PlayerController->WorldInventory);
		}

		return StartAircraftPhaseOG(GameModeAthena);
	}

	EFortTeam PickTeam(AFortGameModeAthena* GameModeAthena, EFortTeam PreferredTeam, AFortPlayerControllerAthena* PlayerControllerAthena)
	{
		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(GameModeAthena->GameState);
		if (!GameStateAthena) return EFortTeam::HumanPvP_Team101;

		UFortPlaylistAthena* PlaylistAthena = GameStateAthena->CurrentPlaylistData;
		if (!GameStateAthena) return EFortTeam::HumanPvP_Team101;

		int32 MaxTeamCount = PlaylistAthena->MaxTeamCount;
		int32 MaxTeamSize = PlaylistAthena->MaxTeamSize;

		EFortTeam ChooseTeam = EFortTeam::HumanPvP_Team101;

		FN_LOG(LogGameMode, Log, L"GameStateAthena->Teams.Num(): %i", GameStateAthena->Teams.Num());

		if (PlaylistAthena->bIsLargeTeamGame || PlaylistAthena->bAllowTeamSwitching)
		{
			int32 MinimumPlayers = INT32_MAX;

			for (int32 i = 0; i < GameStateAthena->Teams.Num(); i++)
			{
				AFortTeamInfo* TeamInfo = GameStateAthena->Teams[i];
				if (!TeamInfo) continue;

				if (i >= MaxTeamCount) break;

				int32 TeamMembersSize = TeamInfo->TeamMembers.Num();

				if (TeamMembersSize < MinimumPlayers && TeamMembersSize < MaxTeamSize)
				{
					MinimumPlayers = TeamMembersSize;
					ChooseTeam = TeamInfo->Team;
				}
			}

			FN_LOG(LogGameMode, Log, L"[AFortGameModeAthena::PickTeam] Large Team Mode: ChosenTeam: %i with %i members", ChooseTeam, MinimumPlayers);
		}
		else
		{
			for (int32 i = 0; i < GameStateAthena->Teams.Num(); i++)
			{
				AFortTeamInfo* TeamInfo = GameStateAthena->Teams[i];
				if (!TeamInfo) continue;

				if (i > MaxTeamCount)
					break;

				int32 TeamMembersSize = TeamInfo->TeamMembers.Num();

				if (TeamMembersSize >= MaxTeamSize)
					continue;

				FN_LOG(LogGameMode, Log, L"[AFortGameModeAthena::PickTeam] Normal Team Mode: ChosenTeam: %i with %i members", TeamInfo->Team, TeamMembersSize);

				ChooseTeam = TeamInfo->Team;
				break;
			}
		}

		return ChooseTeam;
	}


	void InitGameMode()
	{
		AFortGameModeAthena* FortGameModeAthenaDefault = AFortGameModeAthena::GetDefaultObj();
		UClass* FortGameModeAthenaClass = AFortGameModeAthena::StaticClass();

		/* ------------------------------------- AFortGameModeAthena ------------------------------------- */

		MinHook::HookVTable(FortGameModeAthenaDefault, 0x7D8 / 8, ReadyToStartMatch, (LPVOID*)(&ReadyToStartMatchOG), "AFortGameModeAthena::ReadyToStartMatch");
		MinHook::HookVTable(FortGameModeAthenaDefault, 0x610 / 8, SpawnDefaultPawnFor, nullptr, "AFortGameModeAthena::SpawnDefaultPawnFor");

		uintptr_t PatternHandlePostSafeZonePhaseChanged = MinHook::FindPattern(Patterns::HandlePostSafeZonePhaseChanged);
		uintptr_t PatternStartAircraftPhase = MinHook::FindPattern(Patterns::StartAircraftPhase);
		uintptr_t PatternPickTeam = MinHook::FindPattern(Patterns::PickTeam);

		MH_CreateHook((LPVOID)(PatternHandlePostSafeZonePhaseChanged), HandlePostSafeZonePhaseChanged, (LPVOID*)(&HandlePostSafeZonePhaseChangedOG));
		MH_EnableHook((LPVOID)(PatternHandlePostSafeZonePhaseChanged));

		MH_CreateHook((LPVOID)(PatternStartAircraftPhase), StartAircraftPhase, (LPVOID*)(&StartAircraftPhaseOG));
		MH_EnableHook((LPVOID)(PatternStartAircraftPhase));

		MH_CreateHook((LPVOID)(PatternPickTeam), PickTeam, nullptr);
		MH_EnableHook((LPVOID)(PatternPickTeam));

		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitGameMode Success!");
	}
}