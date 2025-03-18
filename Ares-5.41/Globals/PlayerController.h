#pragma once

namespace PlayerController
{
	/* -------------------------------- AFortPlayerControllerAthenaOG -------------------------------- */
	void (*ServerThankBusDriverOG)(AFortPlayerControllerAthena* PlayerControllerAthena);
	void (*ServerPlaceMapCursorOG)(AFortPlayerControllerAthena* PlayerControllerAthena, const FVector_NetQuantize& CursorPos);
	void (*ServerRemoveMapCursorOG)(AFortPlayerControllerAthena* PlayerControllerAthena);
	/* --------------------------------- AFortPlayerControllerZoneOG --------------------------------- */
	void (*ClientOnPawnDiedOG)(AFortPlayerControllerZone* PlayerController, const FFortPlayerDeathReport& DeathReport);
	/* ----------------------------------- AFortPlayerControllerOG ----------------------------------- */
	void (*ServerReadyToStartMatchOG)(AFortPlayerController* PlayerController);
	void (*ServerAttemptInteractOG)(AFortPlayerController* PlayerController, AActor* ReceivingActor, UPrimitiveComponent* InteractComponent, ETInteractionType InteractType, UObject* OptionalObjectData);
	void (*ServerCheatOG)(AFortPlayerController* PlayerController, const FString& Msg);
	/* ------------------------------------- PlayerControllerOG -------------------------------------- */
	void (*ServerChangeNameOG)(APlayerController* PlayerController, const FString& S);
	/* ----------------------------------------------------------------------------------------------- */



	/* --------------------------------- AFortPlayerControllerAthena --------------------------------- */

	void ServerThankBusDriver(AFortPlayerControllerAthena* PlayerControllerAthena)
	{
		ServerThankBusDriverOG(PlayerControllerAthena);
	}

	void ServerPlaceMapCursor(AFortPlayerControllerAthena* PlayerControllerAthena, const FVector_NetQuantize& CursorPos)
	{
		ServerPlaceMapCursorOG(PlayerControllerAthena, CursorPos);
	}

	void ServerRemoveMapCursor(AFortPlayerControllerAthena* PlayerControllerAthena)
	{
		ServerRemoveMapCursorOG(PlayerControllerAthena);
	}

	void ServerPlaySquadQuickChatMessage(AFortPlayerControllerAthena* PlayerControllerAthena, const FAthenaQuickChatActiveEntry& ChatEntry, const FUniqueNetIdRepl& SenderID)
	{
		AFortPlayerStateAthena* PlayerStateAthena = Cast<AFortPlayerStateAthena>(PlayerControllerAthena->PlayerState);
		if (!PlayerStateAthena) return;

		static UAthenaEmojiItemDefinition* EmojiItemDefinition = FindObjectFast<UAthenaEmojiItemDefinition>("/Game/Athena/Items/Cosmetics/Dances/Emoji/Emoji_Comm.Emoji_Comm");

		if (EmojiItemDefinition)
		{
			ETeamMemberState TeamMemberState = ETeamMemberState::None;

			switch (ChatEntry.Index)
			{
			case 0:
				TeamMemberState = ETeamMemberState::EnemySpotted;
				break;
			case 1:
				TeamMemberState = ETeamMemberState::NeedBandages;
				break;
			case 2:
				TeamMemberState = ETeamMemberState::NeedShields;
				break;
			case 3:
				TeamMemberState = ETeamMemberState::NeedMaterials;
				break;
			case 4:
				TeamMemberState = ETeamMemberState::NeedWeapon;
				break;
			default:
				TeamMemberState = ETeamMemberState::None;
				break;
			}

			PlayerStateAthena->TeamMemberState = TeamMemberState;
			PlayerStateAthena->ReplicatedTeamMemberState = TeamMemberState;
			PlayerStateAthena->OnRep_ReplicatedTeamMemberState();

			PlayerControllerAthena->ServerPlayEmoteItem(EmojiItemDefinition);
		}
	}

	/* ---------------------------------- AFortPlayerControllerZone ---------------------------------- */

	void ClientOnPawnDied(AFortPlayerControllerZone* PlayerControllerZone, const FFortPlayerDeathReport& DeathReport)
	{
		AFortPlayerPawnAthena* PlayerPawnAthena = Cast<AFortPlayerPawnAthena>(PlayerControllerZone->MyFortPawn);
		AFortPlayerStateAthena* PlayerStateAthena = Cast<AFortPlayerStateAthena>(PlayerControllerZone->PlayerState);

		if (!PlayerPawnAthena || !PlayerStateAthena)
			return;

		AFortPlayerStateAthena* KillerPlayerState = Cast<AFortPlayerStateAthena>(DeathReport.KillerPlayerState);
		AFortPlayerPawnAthena* KillerPawn = Cast<AFortPlayerPawnAthena>(DeathReport.KillerPawn);
		AActor* DamageCauser = DeathReport.DamageCauser;

		FGameplayTagContainer TagContainer = PlayerPawnAthena ? *(FGameplayTagContainer*)(__int64(PlayerPawnAthena) + 0x1188) : FGameplayTagContainer();

		float Distance = KillerPawn ? KillerPawn->GetDistanceTo(PlayerPawnAthena) : 0;

		EDeathCause DeathCause = AFortPlayerStateAthena::ToDeathCause(TagContainer, PlayerPawnAthena->bIsDBNO);

		FDeathInfo DeathInfo = FDeathInfo();
		DeathInfo.FinisherOrDowner = KillerPlayerState ? KillerPlayerState : PlayerStateAthena;
		DeathInfo.bDBNO = PlayerPawnAthena->bIsDBNO;
		DeathInfo.DeathCause = DeathCause;
		DeathInfo.Distance = (DeathCause == EDeathCause::FallDamage) ? PlayerPawnAthena->LastFallDistance : Distance;
		DeathInfo.DeathLocation = PlayerPawnAthena->K2_GetActorLocation();
		DeathInfo.bInitialized = true;

		PlayerStateAthena->PawnDeathLocation = DeathInfo.DeathLocation;

		PlayerStateAthena->DeathInfo = DeathInfo;
		PlayerStateAthena->OnRep_DeathInfo();

		if (KillerPlayerState && PlayerStateAthena != KillerPlayerState)
		{
			KillerPlayerState->KillScore++;
			KillerPlayerState->OnRep_Kills();

			KillerPlayerState->ClientReportKill(PlayerStateAthena);

#ifdef SIPHON
			AFortPlayerControllerAthena* KillerPlayerController = Cast<AFortPlayerControllerAthena>(KillerPlayerState->Owner);

			if (KillerPlayerController)
				Functions::GiveSiphonBonus(KillerPlayerController, KillerPawn);
#endif // SIPHON
		}

		AFortPlayerControllerAthena* PlayerControllerAthena = Cast<AFortPlayerControllerAthena>(PlayerControllerZone);
		AFortGameModeAthena* GameModeAthena = Cast<AFortGameModeAthena>(Globals::GetGameMode());
		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(GameModeAthena->GameState);

		if (PlayerControllerAthena && GameModeAthena && GameStateAthena)
		{
			if (!GameState::IsRespawningAllowed(GameStateAthena, PlayerStateAthena) && !PlayerPawnAthena->bIsDBNO)
			{
				FAthenaMatchTeamStats TeamStats = FAthenaMatchTeamStats();
				TeamStats.Place = GameStateAthena->PlayersLeft;
				TeamStats.TotalPlayers = GameStateAthena->TotalPlayers;

				PlayerControllerAthena->ClientSendTeamStatsForPlayer(TeamStats);

				UAthenaPlayerMatchReport* MatchReport = PlayerControllerAthena->MatchReport;

				if (MatchReport)
				{
					MatchReport->bHasMatchStats = true;
					MatchReport->bHasTeamStats = true;
					MatchReport->TeamStats = TeamStats;
					MatchReport->bHasRewards = true;
					MatchReport->EndOfMatchResults = FAthenaRewardResult();
				}

				AFortPlayerStateAthena* CorrectKillerPlayerState = (KillerPlayerState && KillerPlayerState == PlayerStateAthena) ? nullptr : KillerPlayerState;
				UFortWeaponItemDefinition* KillerWeaponItemDefinition = nullptr;

				if (DamageCauser)
				{
					AFortProjectileBase* ProjectileBase = Cast<AFortProjectileBase>(DamageCauser);
					AFortWeapon* Weapon = Cast<AFortWeapon>(DamageCauser);

					if (ProjectileBase)
					{
						AFortWeapon* ProjectileBaseWeapon = Cast<AFortWeapon>(ProjectileBase->Owner);

						if (ProjectileBaseWeapon)
							KillerWeaponItemDefinition = ProjectileBaseWeapon->WeaponData;
					}
					else if (Weapon)
						KillerWeaponItemDefinition = Weapon->WeaponData;
				}

				GameModeAthena->RemoveFromAlivePlayers(PlayerControllerAthena, CorrectKillerPlayerState, KillerPawn, KillerWeaponItemDefinition, DeathCause);

				if (GameModeAthena->bAllowSpectateAfterDeath)
				{
					APawn* PlayerToSpectate = KillerPawn;

					if (!PlayerToSpectate || PlayerToSpectate == PlayerPawnAthena)
					{
						TArray<AFortPlayerPawn*> FortPlayerPawns;
						UFortKismetLibrary::GetAllFortPlayerPawns(PlayerControllerAthena, &FortPlayerPawns);

						for (int32 i = 0; i < FortPlayerPawns.Num(); i++)
						{
							AFortPlayerPawn* FortPlayerPawn = FortPlayerPawns[i];
							if (!FortPlayerPawn) continue;

							if (PlayerPawnAthena == FortPlayerPawn)
								continue;

							PlayerToSpectate = FortPlayerPawn;
							break;
						}
					}

					TArray<FFortSpectatorAthenaItem> SpectatorArray = PlayerStateAthena->Spectators.SpectatorArray;

					for (int32 i = 0; i < SpectatorArray.Num(); i++)
					{
						FFortSpectatorAthenaItem Spectator = SpectatorArray[i];
						AFortPlayerStateAthena* SpectatorPlayerState = Spectator.PlayerState;
						if (!SpectatorPlayerState) continue;

						AFortPlayerControllerAthena* SpectatorPlayerController = Cast<AFortPlayerControllerAthena>(SpectatorPlayerState->Owner);
						if (!SpectatorPlayerController) continue;

						if (PlayerToSpectate)
						{
							SpectatorPlayerController->PlayerToSpectateOnDeath = PlayerToSpectate;
							UKismetSystemLibrary::K2_SetTimer(SpectatorPlayerController, L"SpectateOnDeath", 5.0f, false);
							break;
						}
					}

					if (PlayerToSpectate && PlayerToSpectate != PlayerPawnAthena)
					{
						PlayerControllerAthena->PlayerToSpectateOnDeath = PlayerToSpectate;
						UKismetSystemLibrary::K2_SetTimer(PlayerControllerAthena, L"SpectateOnDeath", 5.0f, false);
					}
				}
			}
		}

		ClientOnPawnDiedOG(PlayerControllerZone, DeathReport);
	}

	/* ------------------------------------ AFortPlayerController ------------------------------------ */

	void ServerReadyToStartMatch(AFortPlayerController* PlayerController)
	{
		if (!PlayerController->bReadyToStartMatch)
		{
			APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;

			if (PlayerCameraManager)
			{
				PlayerCameraManager->ViewRollMin = 0.0f;
				PlayerCameraManager->ViewRollMax = 0.0f;
			}

			AFortPlayerControllerAthena* PlayerControllerAthena = Cast<AFortPlayerControllerAthena>(PlayerController);

			if (PlayerControllerAthena)
			{
				if (!PlayerControllerAthena->MatchReport)
				{
					UAthenaPlayerMatchReport* NewMatchReport = Cast<UAthenaPlayerMatchReport>(UGameplayStatics::SpawnObject(UAthenaPlayerMatchReport::StaticClass(), PlayerControllerAthena));

					NewMatchReport->bHasMatchStats = true;
					NewMatchReport->bHasRewards = true;
					NewMatchReport->bHasTeamStats = true;

					PlayerControllerAthena->MatchReport = NewMatchReport;
				}

				if (!PlayerControllerAthena->MatchReport)
				{
					FN_LOG(LogPlayerController, Error, L"[AFortPlayerController::ServerReadyToStartMatch] Failed to spawn MatchReport for PlayerController: %s", PlayerControllerAthena->GetName().c_str());
				}
			}

			AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(Globals::GetGameState());

#ifdef CHEATS
			if (!PlayerController->CheatManager)
			{
				UCheatManager* CheatManager = (UCheatManager*)UGameplayStatics::SpawnObject(UCheatManager::StaticClass(), PlayerController);

				if (CheatManager)
				{
					PlayerController->CheatManager = CheatManager;
					PlayerController->CheatManager->ReceiveInitCheatManager();
				}
			}
#endif // CHEATS

			ServerReadyToStartMatchOG(PlayerController);
			PlayerController->bReadyToStartMatch = true;
			return;
		}

		ServerReadyToStartMatchOG(PlayerController);
	}

	void ServerCombineInventoryItems(AFortPlayerController* PlayerController, const FGuid& TargetItemGuid, const FGuid& SourceItemGuid)
	{
		UFortWorldItem* TargetWorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(TargetItemGuid));
		UFortWorldItem* SourceWorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(SourceItemGuid));

		if (!TargetWorldItem || !SourceWorldItem)
			return;

		UFortWorldItemDefinition* TargetItemDefinition = Cast<UFortWorldItemDefinition>(TargetWorldItem->ItemEntry.ItemDefinition);
		UFortWorldItemDefinition* SourceItemDefinition = Cast<UFortWorldItemDefinition>(SourceWorldItem->ItemEntry.ItemDefinition);

		if (!TargetItemDefinition || !SourceItemDefinition)
			return;

		if (TargetItemDefinition == SourceItemDefinition && TargetWorldItem->ItemEntry.Count < TargetItemDefinition->MaxStackSize)
		{
			int32 NewTargetCount = TargetWorldItem->ItemEntry.Count + SourceWorldItem->ItemEntry.Count;

			if (NewTargetCount > TargetItemDefinition->MaxStackSize)
			{
				int32 NewSourceCount = NewTargetCount - TargetItemDefinition->MaxStackSize;

				Inventory::ModifyCountItem(PlayerController->WorldInventory, SourceWorldItem->ItemEntry.ItemGuid, NewSourceCount);

				NewTargetCount = TargetItemDefinition->MaxStackSize;
			}
			else
			{
				Inventory::RemoveItem(PlayerController->WorldInventory, SourceWorldItem->ItemEntry.ItemGuid);
			}

			Inventory::ModifyCountItem(PlayerController->WorldInventory, TargetWorldItem->ItemEntry.ItemGuid, NewTargetCount);
		}
	}

	void ServerAttemptInventoryDrop(AFortPlayerController* PlayerController, const FGuid& ItemGuid, int32 Count)
	{
		if (Count < 1)
			return;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (!PlayerPawn || PlayerPawn->bIsSkydiving || PlayerPawn->bIsDBNO)
			return;

		AFortPlayerControllerAthena* PlayerControllerAthena = Cast<AFortPlayerControllerAthena>(PlayerController);

		if (PlayerControllerAthena)
		{
			if (PlayerControllerAthena->IsInAircraft())
				return;
		}

		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(ItemGuid));

		if (!WorldItem)
			return;

		UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(WorldItem->ItemEntry.ItemDefinition);

		if (!WorldItemDefinition || !WorldItemDefinition->bCanBeDropped)
			return;

		if (WorldItem->ItemEntry.Count <= 0)
		{
			UFortWeaponRangedItemDefinition* WeaponRangedItemDefinition = Cast<UFortWeaponRangedItemDefinition>(WorldItemDefinition);

			if (WeaponRangedItemDefinition && WeaponRangedItemDefinition->bPersistInInventoryWhenFinalStackEmpty)
				return;

			FN_LOG(LogPlayerController, Warning, L"[AFortPlayerController::ServerAttemptInventoryDrop] The item [%s] has a count of [%i] deletion of the item.", WorldItemDefinition->GetName().c_str(), WorldItem->ItemEntry.Count);

			PlayerController->RemoveInventoryItem(ItemGuid, Count, true, true);
			return;
		}

		if (PlayerController->RemoveInventoryItem(ItemGuid, Count, false, true))
		{
			const float LootSpawnLocationX = 0.0f;
			const float LootSpawnLocationY = 0.0f;
			const float LootSpawnLocationZ = 60.0f;

			const FVector& SpawnLocation = PlayerPawn->K2_GetActorLocation() +
				PlayerPawn->GetActorForwardVector() * LootSpawnLocationX +
				PlayerPawn->GetActorRightVector() * LootSpawnLocationY +
				PlayerPawn->GetActorUpVector() * LootSpawnLocationZ;

			FFortItemEntry NewItemEntry;
			Inventory::MakeItemEntry(&NewItemEntry, WorldItemDefinition, Count, WorldItem->ItemEntry.Level, WorldItem->ItemEntry.LoadedAmmo, WorldItem->ItemEntry.Durability);

			AFortPickup* Pickup = AFortPickup::CreatePickup(
				PlayerController->GetWorld(),
				&NewItemEntry,
				&SpawnLocation,
				nullptr,
				nullptr,
				nullptr,
				true,
				(uint32)EFortPickupSourceTypeFlag::Player);

			NewItemEntry.FreeItemEntry();

			if (Pickup)
			{
				FRotator PlayerRotation = PlayerPawn->K2_GetActorRotation();
				PlayerRotation.Yaw += UKismetMathLibrary::RandomFloatInRange(-60.0f, 60.0f);

				float RandomDistance = UKismetMathLibrary::RandomFloatInRange(500.0f, 600.0f);
				FVector FinalDirection = UKismetMathLibrary::GetForwardVector(PlayerRotation);

				FVector FinalLocation = SpawnLocation + FinalDirection * RandomDistance;

				Pickup->PawnWhoDroppedPickup = PlayerPawn;
				Pickup->bCombinePickupsWhenTossCompletes = true;
				Pickup->TossPickup(FinalLocation, PlayerPawn, 0, true);
			}

			EWorldItemDropBehavior DropBehavior = WorldItemDefinition->DropBehavior;

			switch (DropBehavior)
			{
			case EWorldItemDropBehavior::DropAsPickup:

				break;
			case EWorldItemDropBehavior::DestroyOnDrop:
				if (Pickup)
				{
					Pickup->ForceNetUpdate();
					Pickup->K2_DestroyActor();
				}
				break;
			case EWorldItemDropBehavior::DropAsPickupDestroyOnEmpty:

				break;
			default:
				break;
			}
		}
	}

	void ServerAttemptInteract(AFortPlayerController* PlayerController, AActor* ReceivingActor, UPrimitiveComponent* InteractComponent, ETInteractionType InteractType, UObject* OptionalObjectData)
	{
		if (!ReceivingActor)
			return;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (!PlayerPawn || PlayerPawn->bIsDBNO)
			return;

		ESubGame CurrentSubGame = UFortGlobals::GetCurrentSubGame();
		UFortQuestManager* QuestManager = PlayerController->GetQuestManager(CurrentSubGame);

		if (QuestManager)
		{
			FGameplayTagContainer SourceTags;
			FGameplayTagContainer ContextTags;
			QuestManager->GetSourceAndContextTags(&SourceTags, &ContextTags);

			void* GameplayTagAssetInterface = ReceivingActor->GetInterfaceAddress(IGameplayTagAssetInterface::StaticClass());

			UFortRegisteredPlayerInfo* RegisteredPlayerInfo = Cast<UFortRegisteredPlayerInfo>(QuestManager->Outer);

			// QuestManager->SendCustomStatEvent();
		}

		ABuildingItemCollectorActor* BuildingItemCollectorActor = Cast<ABuildingItemCollectorActor>(ReceivingActor);

		if (BuildingItemCollectorActor)
		{
			UFortWorldItemDefinition* ActiveInputItem = BuildingItemCollectorActor->ActiveInputItem;
			if (!ActiveInputItem) return;

			const float LootSpawnLocationX = BuildingItemCollectorActor->LootSpawnLocation.X;
			const float LootSpawnLocationY = BuildingItemCollectorActor->LootSpawnLocation.Y;
			const float LootSpawnLocationZ = BuildingItemCollectorActor->LootSpawnLocation.Z;

			const FVector& SpawnLocation = BuildingItemCollectorActor->K2_GetActorLocation() +
				BuildingItemCollectorActor->GetActorForwardVector() * LootSpawnLocationX +
				BuildingItemCollectorActor->GetActorRightVector() * LootSpawnLocationY +
				BuildingItemCollectorActor->GetActorUpVector() * LootSpawnLocationZ;

			for (int32 i = 0; i < BuildingItemCollectorActor->ItemCollections.Num(); i++)
			{
				const FColletorUnitInfo& ItemCollection = BuildingItemCollectorActor->ItemCollections[i];

				if (ItemCollection.InputItem != ActiveInputItem)
					continue;

				if (!BuildingItemCollectorActor->HasEnouphDepositItems(PlayerController, ActiveInputItem, true) && !PlayerController->bBuildFree)
					break;

				int32 DepositGoal = BuildingItemCollectorActor->GetDepositGoal(PlayerController, ActiveInputItem);

				if (PlayerController->bBuildFree)
					DepositGoal = 0;

				UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_FindExistingItemForDefinition(ActiveInputItem, false));

				if (!WorldItem && !PlayerController->bBuildFree)
					break;

				if (PlayerController->RemoveInventoryItem(WorldItem->ItemEntry.ItemGuid, DepositGoal))
				{
					TArray<FFortItemEntry> OutputItemEntry = ItemCollection.OutputItemEntry;

					for (auto& ItemEntry : OutputItemEntry)
					{
						UFortWorldItemDefinition* ItemDefinition = Cast<UFortWorldItemDefinition>(ItemEntry.ItemDefinition);
						if (!ItemDefinition) continue;

						FFortItemEntry NewItemEntry;
						Inventory::MakeItemEntry(&NewItemEntry, ItemDefinition, ItemEntry.Count, ItemEntry.Level, ItemEntry.LoadedAmmo, ItemEntry.Durability);

						AFortPickup* Pickup = AFortPickup::CreatePickup(
							PlayerController->GetWorld(),
							&NewItemEntry,
							&SpawnLocation,
							nullptr,
							nullptr,
							nullptr,
							true,
							(uint32)EFortPickupSourceTypeFlag::Tossed);

						if (Pickup)
						{
							/*FVector TossDirection = UKismetMathLibrary::GetForwardVector(BuildingItemCollectorActor->LootTossDirection);
							TossDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(TossDirection, BuildingItemCollectorActor->LootTossConeHalfAngle);
							TossDirection = SpawnLocation + TossDirection;*/

							Pickup->TossPickup(SpawnLocation, nullptr, 0, BuildingItemCollectorActor->bTossOnGround);
						}

						NewItemEntry.FreeItemEntry();
					}

					AFortPlayerStateAthena* PlayerStateAthena = Cast<AFortPlayerStateAthena>(PlayerController->PlayerState);

					if (PlayerStateAthena)
					{
						FCollectorTrackedData CollectorTrackedData = FCollectorTrackedData();
						CollectorTrackedData.Team = PlayerStateAthena->TeamIndex;
						CollectorTrackedData.Player = PlayerStateAthena;

						BuildingItemCollectorActor->TrackedInteractionData.Add(CollectorTrackedData);
					}

					Functions::VendingMachinePlayVendFX(BuildingItemCollectorActor);
					BuildingItemCollectorActor->bCurrentInteractionSuccess = true;
					return;
				}
			}

			Functions::VendingMachinePlayVendFailFX(BuildingItemCollectorActor);
			BuildingItemCollectorActor->bCurrentInteractionSuccess = false;
			return;
		}

		ServerAttemptInteractOG(PlayerController, ReceivingActor, InteractComponent, InteractType, OptionalObjectData);
	}

	/*
	 * Rewrite AFortPlayerController::CheckCreateBuildingActor (1.8)
	 *
	 * - https://imgur.com/UMJlcl7
	 * - I'm too lazy to continue but basically it checks if it's valid
	 */
	bool CheckCreateBuildingActor(AFortPlayerController* PlayerController, FBuildingClassData& BuildingClassData)
	{
		UClass* BuildingClass = BuildingClassData.BuildingClass.Get();

		if (!BuildingClass)
			return false;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (!PlayerPawn || PlayerPawn->bIsDBNO)
			return false;

		UObject* BuildingClassDefault = BuildingClass->CreateDefaultObject();

		if (!BuildingClassDefault->IsA(ABuildingActor::StaticClass()))
			return false;

		if (!Functions::IsPlayerBuildableClasse(BuildingClass))
			return false;

		ABuildingSMActor* BuildingSMActorClassDefault = Cast<ABuildingSMActor>(BuildingClassDefault);

		if (BuildingSMActorClassDefault)
		{
			if (!PlayerController->bBuildFree)
			{
				//int32 NumAvailableBuildingResources = UFortKismetLibrary::K2_GetNumAvailableBuildingResources(PlayerController, BuildingSMActorClassDefault->ResourceType); // Crash randomly
				//int32 ResourceAmount = PlayerController->GetCreateResourceAmount(BuildingClassData);

				//if (NumAvailableBuildingResources < ResourceAmount)
				//	return false;
			}
		}

		return true;
	}

	/*
	 * Rewrite AFortPlayerController::ServerCreateBuildingActor (1.8)
	 *
	 * - https://imgur.com/45hEb1e
	 */
	void ServerCreateBuildingActor(AFortPlayerController* PlayerController, FBuildingClassData BuildingClassData, const FVector_NetQuantize10& BuildLoc, const FRotator& BuildRot, bool bMirrored, float SyncKey)
	{
		if (!CheckCreateBuildingActor(PlayerController, BuildingClassData))
			return;

		UClass* BuildingClass = BuildingClassData.BuildingClass.Get();
		if (!BuildingClass) return;

		TArray<ABuildingActor*> ExistingBuildings;
		EFortStructuralGridQueryResults GridQueryResults = PlayerController->CanPlaceBuilableClassInStructuralGrid(BuildingClass, BuildLoc, BuildRot, bMirrored, &ExistingBuildings);

		if (GridQueryResults == EFortStructuralGridQueryResults::CanAdd)
		{
			for (int32 i = 0; i < ExistingBuildings.Num(); i++)
			{
				ABuildingActor* ExistingBuilding = ExistingBuildings[i];
				if (!ExistingBuilding) continue;

				ExistingBuilding->K2_DestroyActor();
			}

			ABuildingSMActor* BuildingSMActor = Util::SpawnActor<ABuildingSMActor>(BuildingClass, BuildLoc, BuildRot);
			if (!BuildingSMActor) return;

			BuildingSMActor->CurrentBuildingLevel = BuildingClassData.UpgradeLevel;

			// Fortnite does lots of other things, I don't know if it's useful?
			// https://imgur.com/a/tGBE1to

			PlayerController->PayBuildingCosts(BuildingClassData);

			BuildingSMActor->InitializeKismetSpawnedBuildingActor(BuildingSMActor, PlayerController, true);
			BuildingSMActor->bPlayerPlaced = true;

			AFortPlayerStateAthena* PlayerStateAthena = Cast<AFortPlayerStateAthena>(PlayerController->PlayerState);

			if (PlayerStateAthena)
			{
				BuildingSMActor->Team = PlayerStateAthena->TeamIndex;
				BuildingSMActor->OnRep_Team();
			}
		}

		if (ExistingBuildings.IsValid())
			ExistingBuildings.Free();
	}

	/*
	 * Rewrite AFortPlayerController::ServerRepairBuildingActor (1.8)
	 *
	 * - https://imgur.com/rbKqG3z
	 */
	void ServerRepairBuildingActor(AFortPlayerController* PlayerController, ABuildingSMActor* BuildingActorToRepair)
	{
		if (!BuildingActorToRepair ||
			!BuildingActorToRepair->GetWorld())
			return;

		AFortPlayerStateAthena* PlayerStateAthena = Cast<AFortPlayerStateAthena>(PlayerController->PlayerState);

		if (PlayerStateAthena)
		{
			if (!Functions::IsOnSameTeam(PlayerStateAthena, BuildingActorToRepair))
				return;
		}

		if (!PlayerController->bBuildFree)
		{
			int32 NumAvailableBuildingResources = UFortKismetLibrary::K2_GetNumAvailableBuildingResources(PlayerController, BuildingActorToRepair->ResourceType);
			int32 ResourceAmount = BuildingActorToRepair->GetRepairResourceAmount(PlayerController);

			if (NumAvailableBuildingResources < ResourceAmount)
				return;
		}

		int32 RepairCosts = PlayerController->PayRepairCosts(BuildingActorToRepair);
		BuildingActorToRepair->RepairBuilding(PlayerController, RepairCosts);

		// Are there any more needs?
		// https://imgur.com/5uafv8n
	}

	/*
	 * Rewrite AFortPlayerController::ServerBeginEditingBuildingActor (1.8)
	 *
	 * - https://imgur.com/A4PdpVl
	 */
	void ServerBeginEditingBuildingActor(AFortPlayerController* PlayerController, ABuildingSMActor* BuildingActorToEdit)
	{
		if (!BuildingActorToEdit)
			return;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;
		if (!PlayerPawn) return;

		if (BuildingActorToEdit->CheckBeginEditBuildingActor(PlayerController))
		{
			AFortPlayerStateZone* PlayerStateZone = Cast<AFortPlayerStateZone>(PlayerController->PlayerState);
			if (!PlayerStateZone) return;

			BuildingActorToEdit->SetEditingPlayer(PlayerStateZone);

			UFortGameData* GameData = Globals::GetGameData();
			UFortEditToolItemDefinition* EditToolItemDefinition = GameData->EditToolItem.Get();

			if (!EditToolItemDefinition)
			{
				const FString& AssetPathName = UKismetStringLibrary::Conv_NameToString(GameData->EditToolItem.ObjectID.AssetPathName);
				EditToolItemDefinition = StaticLoadObject<UFortEditToolItemDefinition>(AssetPathName.CStr());
			}

			UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_FindExistingItemForDefinition(EditToolItemDefinition, false));

			if (WorldItem && 
				EditToolItemDefinition && 
				EditToolItemDefinition->EquipWeaponDefinition(WorldItem, PlayerController))
			{
				AFortWeap_EditingTool* EditingTool = Cast<AFortWeap_EditingTool>(PlayerPawn->CurrentWeapon);

				if (EditingTool)
					EditingTool->SetEditingActor(BuildingActorToEdit);
			}
		}
	}

	/*
	 * Rewrite AFortPlayerController::ServerEditBuildingActor (1.8)
	 *
	 * - https://imgur.com/NkmbdiW
	 */
	void ServerEditBuildingActor(AFortPlayerController* PlayerController, ABuildingSMActor* BuildingActorToEdit, TSubclassOf<ABuildingSMActor> NewBuildingClass, int32 RotationIterations, bool bMirrored)
	{
		if (!BuildingActorToEdit ||
			!BuildingActorToEdit->GetWorld() ||
			BuildingActorToEdit->EditingPlayer != PlayerController->PlayerState ||
			BuildingActorToEdit->bDestroyed)
			return;

		// This security is not in the real function but it allows you not to replace everything with anything
		if (!Functions::IsPlayerBuildableClasse(NewBuildingClass.Get()))
			return;

		BuildingActorToEdit->SetEditingPlayer(nullptr);

		int32 CurrentBuildingLevel = BuildingActorToEdit->CurrentBuildingLevel;
		BuildingActorToEdit->ReplaceBuildingActor(NewBuildingClass, CurrentBuildingLevel, RotationIterations, bMirrored, PlayerController);

		// The rest of the code does stuff with quests and stats
		// And I'm too lazy to find the function on the 5.41
		// https://imgur.com/7cy0KKR
	}

	/*
	 * Rewrite AFortPlayerController::ServerEndEditingBuildingActor (1.8)
	 *
	 * - https://imgur.com/5J6ibST
	 */
	void ServerEndEditingBuildingActor(AFortPlayerController* PlayerController, ABuildingSMActor* BuildingActorToStopEditing)
	{
		if (!BuildingActorToStopEditing)
			return;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;
		if (!PlayerPawn) return;

		if (BuildingActorToStopEditing->EditingPlayer != PlayerController->PlayerState ||
			BuildingActorToStopEditing->bDestroyed)
			return;

		BuildingActorToStopEditing->SetEditingPlayer(nullptr);

		AFortWeap_EditingTool* EditingTool = Cast<AFortWeap_EditingTool>(PlayerPawn->CurrentWeapon);

		if (EditingTool)
			EditingTool->SetEditingActor(nullptr);
	}

	void ServerDropAllItems(AFortPlayerController* PlayerController, const UFortItemDefinition* IgnoreItemDef)
	{
		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;
		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!PlayerPawn || !WorldInventory)
			return;

		TArray<UFortWorldItem*> WorldItemToDrops;

		for (int32 i = 0; i < PlayerController->WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* WorldItem = PlayerController->WorldInventory->Inventory.ItemInstances[i];
			if (!WorldItem) continue;

			FFortItemEntry* ItemEntry = &WorldItem->ItemEntry;
			if (!ItemEntry) continue;

			UFortWorldItemDefinition* ItemDefinition = Cast<UFortWorldItemDefinition>(ItemEntry->ItemDefinition);
			if (!ItemDefinition) continue;

			if (!ItemDefinition->bCanBeDropped || ItemDefinition == IgnoreItemDef)
				continue;

			WorldItemToDrops.Add(WorldItem);
		}

		const float LootSpawnLocationX = 0.0f;
		const float LootSpawnLocationY = 0.0f;
		const float LootSpawnLocationZ = 70.0f;

		const FVector& SpawnLocation = PlayerPawn->K2_GetActorLocation() +
			PlayerPawn->GetActorForwardVector() * LootSpawnLocationX +
			PlayerPawn->GetActorRightVector() * LootSpawnLocationY +
			PlayerPawn->GetActorUpVector() * LootSpawnLocationZ;

		for (int32 i = 0; i < WorldItemToDrops.Num(); i++)
		{
			UFortWorldItem* WorldItemToDrop = WorldItemToDrops[i];
			if (!WorldItemToDrop) continue;

			FVector FinalLocation = SpawnLocation;
			FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();

			FinalLocation.X += RandomDirection.X * 700.0f;
			FinalLocation.Y += RandomDirection.Y * 700.0f;

			FFortItemEntry NewItemEntry;
			NewItemEntry.CopyItemEntryWithReset(&WorldItemToDrop->ItemEntry);

			if (PlayerController->RemoveInventoryItem(WorldItemToDrop->ItemEntry.ItemGuid, WorldItemToDrop->ItemEntry.Count, true, true))
			{
				AFortPickup* Pickup = AFortPickup::CreatePickup(
					PlayerController->GetWorld(), 
					&NewItemEntry, 
					&SpawnLocation,
					nullptr,
					nullptr,
					nullptr,
					true,
					(uint32)EFortPickupSourceTypeFlag::Tossed);

				if (Pickup)
				{
					Pickup->PawnWhoDroppedPickup = PlayerPawn;
					Pickup->bCombinePickupsWhenTossCompletes = true;
					Pickup->TossPickup(FinalLocation, PlayerPawn, 0, true);
				}
			}

			NewItemEntry.FreeItemEntry();
		}

		if (WorldItemToDrops.IsValid())
			WorldItemToDrops.Free();
	}

	void ServerExecuteInventoryItem(AFortPlayerController* PlayerController, const FGuid& ItemGuid)
	{
		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (!PlayerPawn || PlayerPawn->bIsDBNO)
			return;

		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(ItemGuid));
		if (!WorldItem) return;

		UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(WorldItem->ItemEntry.ItemDefinition);
		if (!WorldItemDefinition) return;

		UFortGadgetItemDefinition* GadgetItemDefinition = Cast<UFortGadgetItemDefinition>(WorldItemDefinition);

		if (GadgetItemDefinition)
		{
			WorldItemDefinition = GadgetItemDefinition->GetDecoItemDefinition();
		}

		UFortWeaponItemDefinition* WeaponItemDefinition = Cast<UFortWeaponItemDefinition>(WorldItemDefinition);
		if (!WeaponItemDefinition) return;

		UFortDecoItemDefinition* DecoItemDefinition = Cast<UFortDecoItemDefinition>(WorldItemDefinition);

		if (DecoItemDefinition)
		{
			DecoItemDefinition->EquipDecoDefinition(WorldItem, PlayerController);

			UFortContextTrapItemDefinition* ContextTrapItemDefinition = Cast<UFortContextTrapItemDefinition>(DecoItemDefinition);

			if (ContextTrapItemDefinition)
			{
				ContextTrapItemDefinition->EquipContextTrapDefinition(WorldItem, PlayerController);
			}

			return;
		}

		WeaponItemDefinition->EquipWeaponDefinition(WorldItem, PlayerController);
	}

	/*
	 * Rewrite AFortPlayerController::ServerPlayEmoteItem (1.8)
	 *
	 * - https://imgur.com/JzoSf26 
	 * - https://imgur.com/300J2E9 // not done
	 * - https://imgur.com/Z03MrUD
	 */
	void ServerPlayEmoteItem(AFortPlayerController* PlayerController, UFortMontageItemDefinitionBase* EmoteAsset)
	{
		if (!EmoteAsset)
			return;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (!PlayerPawn || PlayerPawn->bIsSkydiving || PlayerPawn->bIsDBNO)
			return;

		UFortAbilitySystemComponent* AbilitySystemComponent = PlayerPawn->AbilitySystemComponent;
		if (!AbilitySystemComponent) return;

		UFortGameplayAbility* GameplayAbility = nullptr;

		if (EmoteAsset->IsA(UAthenaSprayItemDefinition::StaticClass()))
		{
			UFortGameData* GameData = Globals::GetGameData();
			UFortGameplayAbility* SprayGameplayAbility = Functions::LoadGameplayAbility(GameData->SprayGameplayAbility);
			GameplayAbility = SprayGameplayAbility;
		}
		else if (EmoteAsset->IsA(UAthenaToyItemDefinition::StaticClass()))
		{
			UAthenaToyItemDefinition* ToyItemDefinition = Cast<UAthenaToyItemDefinition>(EmoteAsset);

			if (ToyItemDefinition)
			{
				UFortGameplayAbility* ToySpawnAbility = Functions::LoadGameplayAbility(ToyItemDefinition->ToySpawnAbility);
				GameplayAbility = ToySpawnAbility;

				UClass* ToyActorClass = Functions::LoadClass(ToyItemDefinition->ToyActorClass);

				if (ToyActorClass)
				{
					for (int32 i = 0; i < PlayerController->ActiveToyInstances.Num(); i++)
					{
						ABuildingGameplayActor* ActiveToyInstance = Cast<ABuildingGameplayActor>(PlayerController->ActiveToyInstances[i]);
						if (!ActiveToyInstance) continue;

						if (ActiveToyInstance->bActorIsBeingDestroyed)
							continue;

						if (ActiveToyInstance->IsA(ToyActorClass))
						{
							PlayerController->ActiveToyInstances.Remove(i);
							ActiveToyInstance->FlushNetDormancy();
							ActiveToyInstance->ForceNetUpdate();
							ActiveToyInstance->SilentDie();
							ActiveToyInstance->K2_DestroyActor();
						}
					}
				}
			}
		}

		if (!GameplayAbility && EmoteAsset->IsA(UAthenaDanceItemDefinition::StaticClass()))
		{
			UFortGameData* GameData = Globals::GetGameData();
			UFortGameplayAbility* EmoteGameplayAbility = Functions::LoadGameplayAbility(GameData->EmoteGameplayAbility);
			GameplayAbility = EmoteGameplayAbility;
		}

		if (GameplayAbility)
		{
			UAthenaDanceItemDefinition* DanceItemDefinition = Cast<UAthenaDanceItemDefinition>(EmoteAsset);

			if (DanceItemDefinition)
			{
				PlayerPawn->bMovingEmote = DanceItemDefinition->bMovingEmote;
				PlayerPawn->EmoteWalkSpeed = DanceItemDefinition->WalkForwardSpeed;
			}

			FGameplayAbilitySpec AbilitySpec;
			AbilitySpec.CreateDefaultAbilitySpec(GameplayAbility, GameplayAbility->GetAbilityLevel(), -1, EmoteAsset);

			FGameplayAbilitySpecHandle Handle;
			AbilitySystemComponent->GiveAbilityAndActivateOnce(&Handle, AbilitySpec);
		}
	}

	void ServerSetInventoryStateValue(AFortPlayerController* PlayerController, const FGuid& ItemGuid, const FFortItemEntryStateValue& StateValue)
	{

	}

	void ServerRemoveInventoryStateValue(AFortPlayerController* PlayerController, const FGuid& ItemGuid, EFortItemEntryState StateValueType)
	{

	}

	void ServerReturnToMainMenu(AFortPlayerController* PlayerController)
	{
		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (PlayerPawn)
		{
			PlayerController->ServerSuicide();

			if (PlayerPawn && PlayerPawn->bIsDBNO)
				PlayerController->ServerSuicide();
		}

		PlayerController->ClientTravel(L"/Game/Maps/Frontend", ETravelType::TRAVEL_Absolute, false, FGuid());
	}

	void ServerCheat(AFortPlayerController* PlayerController, const FString& Msg)
	{
		FString TempPlayerName = L"Null";

		APlayerState* TempPlayerState = PlayerController->PlayerState;

		if (TempPlayerState)
			TempPlayerName = TempPlayerState->GetPlayerName();

		FN_LOG(LogInit, Log, L"ServerCheat - Msg: %s [PlayerName: %s]", Msg.ToString().c_str(), TempPlayerName.ToString().c_str());

		//UKismetSystemLibrary::ExecuteConsoleCommand(PlayerController, Msg, PlayerController);

		//ServerCheatOG(PlayerController, Msg);
		//return;

		if (!Msg.IsValid())
			return;

		std::string Command = Msg.ToString();
		std::vector<std::string> ParsedCommand = split(Command, ' ');

		if (ParsedCommand.empty())
			return;

		std::string Action = ParsedCommand[0];
		std::transform(Action.begin(), Action.end(), Action.begin(),
			[](unsigned char c) { return std::tolower(c); });

		FString Message = L"Unknown Command";

		AFortPlayerState* PlayerState = Cast<AFortPlayerState>(PlayerController->PlayerState);
		UCheatManager* CheatManager = PlayerController->CheatManager;
		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (Action == "listplayers")
		{
			TArray<AFortPlayerController*> AllFortPlayerControllers = UFortKismetLibrary::GetAllFortPlayerControllers(PlayerController, true, false);

			int32 NumPlayers = 0;
			for (int32 i = 0; i < AllFortPlayerControllers.Num(); i++)
			{
				AFortPlayerController* FortPlayerController = AllFortPlayerControllers[i];
				if (!FortPlayerController) continue;

				if (!FortPlayerController->PlayerState)
					continue;

				NumPlayers++;

				std::string LootMessage = "[" + std::to_string(NumPlayers) + "] - PlayerName: " + FortPlayerController->PlayerState->GetPlayerName().ToString();
				FString FLootMessage = std::wstring(LootMessage.begin(), LootMessage.end()).c_str();
				PlayerController->ClientMessage(FLootMessage, FName(), 1);

				Message = L"null";
			}
		}

		else if (Action == "startaircraft")
		{
			UKismetSystemLibrary::ExecuteConsoleCommand(PlayerController, L"startaircraft", nullptr);
			Message = L"StartAirCraft command executed successfully!";
		}

#ifdef CHEATS
		else if (Action == "pausesafezone")
		{
			UKismetSystemLibrary::ExecuteConsoleCommand(PlayerController, L"pausesafezone", nullptr);
			Message = L"PauseSafeZone command executed successfully!";
		}
		else if (Action == "skipsafezone")
		{
			UKismetSystemLibrary::ExecuteConsoleCommand(PlayerController, L"skipsafezone", nullptr);
			Message = L"SkipSafeZone command executed successfully!";
		}
		else if (Action == "startsafezone")
		{
			UKismetSystemLibrary::ExecuteConsoleCommand(PlayerController, L"startsafezone", nullptr);
			Message = L"StartSafeZone command executed successfully!";
		}
		else if (Action == "skipshrinksafezone")
		{
			UKismetSystemLibrary::ExecuteConsoleCommand(PlayerController, L"skipshrinksafezone", nullptr);
			Message = L"SkipShrinkSafeZone command executed successfully!";
		}
		else if (Action == "startshrinksafezone")
		{
			UKismetSystemLibrary::ExecuteConsoleCommand(PlayerController, L"startshrinksafezone", nullptr);
			Message = L"StartShrinkSafeZone command executed successfully!";
		}
		else if (Action == "buildfree")
		{
			PlayerController->bBuildFree = PlayerController->bBuildFree ? false : true;
			Message = PlayerController->bBuildFree ? L"BuildFree on" : L"BuildFree off";
		}
		else if (Action == "infiniteammo")
		{
			PlayerController->bInfiniteAmmo = PlayerController->bInfiniteAmmo ? false : true;
			Message = PlayerController->bInfiniteAmmo ? L"InfiniteAmmo on" : L"InfiniteAmmo off";
		}
		else if (Action == "suicide" || Action == "swisspeople")
		{
			PlayerController->ServerSuicide();
		}
		else if (Action == "sethealth" && ParsedCommand.size() >= 2)
		{
			if (PlayerPawn)
			{
				try
				{
					float NewHealthVal = std::stof(ParsedCommand[1]);

					PlayerPawn->SetHealth(NewHealthVal);
					Message = L"SetHealth command executed successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					Message = L"Invalid NewHealthVal provided!";
				}
				catch (const std::out_of_range& e)
				{
					Message = L"NewHealthVal out of range!";
				}
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}
		}
		else if (Action == "setshield" && ParsedCommand.size() >= 2)
		{
			if (PlayerPawn)
			{
				try
				{
					float NewShieldVal = std::stof(ParsedCommand[1]);

					PlayerPawn->SetShield(NewShieldVal);
					Message = L"SetShield command executed successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					Message = L"Invalid NewShieldVal provided!";
				}
				catch (const std::out_of_range& e)
				{
					Message = L"NewShieldVal out of range!";
				}
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}
		}
		else if (Action == "setmaxhealth" && ParsedCommand.size() >= 2)
		{
			if (PlayerPawn)
			{
				try
				{
					float NewHealthVal = std::stof(ParsedCommand[1]);

					PlayerPawn->SetMaxHealth(NewHealthVal);
					Message = L"SetMaxHealth command executed successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					Message = L"Invalid NewHealthVal provided!";
				}
				catch (const std::out_of_range& e)
				{
					Message = L"NewHealthVal out of range!";
				}
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}
		}
		else if (Action == "setmaxshield" && ParsedCommand.size() >= 2)
		{
			if (PlayerPawn)
			{
				try
				{
					float NewShieldVal = std::stof(ParsedCommand[1]);

					PlayerPawn->SetMaxShield(NewShieldVal);
					Message = L"SetMaxShield command executed successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					Message = L"Invalid NewShieldVal provided!";
				}
				catch (const std::out_of_range& e)
				{
					Message = L"NewShieldVal out of range!";
				}
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}
		}
		else if (Action == "setsprintspeed" && ParsedCommand.size() >= 2)
		{
			if (PlayerPawn)
			{
				try
				{
					float NewSprintSpeedVal = std::stof(ParsedCommand[1]);

					PlayerPawn->MovementSet->SprintSpeed.BaseValue = NewSprintSpeedVal;
					PlayerPawn->MovementSet->SprintSpeed.CurrentValue = NewSprintSpeedVal;

					PlayerPawn->MovementSet->SprintSpeed.Minimum = NewSprintSpeedVal;
					PlayerPawn->MovementSet->SprintSpeed.Maximum = NewSprintSpeedVal;

					Message = L"SetSprintSpeed command executed successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					Message = L"Invalid NewSprintSpeedVal provided!";
				}
				catch (const std::out_of_range& e)
				{
					Message = L"NewSprintSpeedVal out of range!";
				}
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}
		}
		else if (Action == "god")
		{
			if (CheatManager)
			{
				CheatManager->God();
				Message = L"null";
			}
			else
			{
				Message = L"CheatManager not found!";
			}
		}
		else if (Action == "destroytarget")
		{
			if (CheatManager)
			{
				CheatManager->DestroyTarget();
				Message = L"Target successfully destroyed!";
			}
			else
			{
				Message = L"CheatManager not found!";
			}
		}
		else if (Action == "tp")
		{
			if (CheatManager)
			{
				CheatManager->Teleport();
				Message = L"Teleportation successful!";
			}
			else
			{
				Message = L"CheatManager not found!";
			}
		}
		else if (Action == "bugitgo" && ParsedCommand.size() >= 4)
		{
			if (CheatManager)
			{
				try
				{
					float X = std::stof(ParsedCommand[1]);
					float Y = std::stof(ParsedCommand[2]);
					float Z = std::stof(ParsedCommand[3]);

					CheatManager->BugItGo(X, Y, Z, 0.f, 0.f, 0.f);
					Message = L"BugItGo command executed successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					Message = L"Invalid coordinates provided!";
				}
				catch (const std::out_of_range& e)
				{
					Message = L"Coordinates out of range!";
				}
			}
			else
			{
				Message = L"CheatManager not found!";
			}
		}
		else if (Action == "launchpawn" && ParsedCommand.size() >= 4)
		{
			if (PlayerPawn)
			{
				try
				{
					float X = std::stof(ParsedCommand[1]);
					float Y = std::stof(ParsedCommand[2]);
					float Z = std::stof(ParsedCommand[3]);

					if (ParsedCommand.size() >= 5)
					{
						std::string PlayerName = ParsedCommand[4];

						TArray<AFortPlayerController*> AllFortPlayerControllers = UFortKismetLibrary::GetAllFortPlayerControllers(PlayerController, true, false);

						for (int32 i = 0; i < AllFortPlayerControllers.Num(); i++)
						{
							auto FortPlayerController = AllFortPlayerControllers[i];
							if (!FortPlayerController) continue;

							auto TempPlayerState = FortPlayerController->PlayerState;
							if (!TempPlayerState) continue;

							if (TempPlayerState->GetPlayerName().ToString() == PlayerName)
							{
								auto TempPlayerPawn = FortPlayerController->GetPlayerPawn();
								if (!TempPlayerPawn) break;

								TempPlayerPawn->LaunchPawn(FVector(X, Y, Z), false, false);
								Message = L"LaunchPawn command executed successfully!";
								break;
							}
						}
					}
					else
					{
						PlayerPawn->LaunchPawn(FVector(X, Y, Z), false, false);
						Message = L"LaunchPawn command executed successfully!";
					}
				}
				catch (const std::invalid_argument& e)
				{
					Message = L"Invalid coordinates provided!";
				}
				catch (const std::out_of_range& e)
				{
					Message = L"Coordinates out of range!";
				}
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}
		}
		else if (Action == "summon" && ParsedCommand.size() >= 2)
		{
			if (PlayerPawn)
			{
				std::string& ClassName = ParsedCommand[1];

				int32 AmountToSpawn = 1;

				if (ParsedCommand.size() >= 3)
				{
					bool bIsAmountToSpawnInt = std::all_of(ParsedCommand[2].begin(), ParsedCommand[2].end(), ::isdigit);

					if (bIsAmountToSpawnInt)
						AmountToSpawn = std::stoi(ParsedCommand[2]);
				}

				static TArray<UBlueprintGeneratedClass*> AllBlueprintGeneratedClass;

				if (AllBlueprintGeneratedClass.Num() <= 0)
				{
					for (int32 i = 0; i < UObject::GObjects->Num(); i++)
					{
						UObject* GObject = UObject::GObjects->GetByIndex(i);

						UBlueprintGeneratedClass* BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(GObject);
						if (!BlueprintGeneratedClass) continue;

						AllBlueprintGeneratedClass.Add(BlueprintGeneratedClass);
					}
				}

				bool bFindClass = false;
				for (int32 i = 0; i < AllBlueprintGeneratedClass.Num(); i++)
				{
					UBlueprintGeneratedClass* BlueprintGeneratedClass = AllBlueprintGeneratedClass[i];
					if (!BlueprintGeneratedClass) continue;

					FString ObjectName = UKismetStringLibrary::Conv_ObjectToString(BlueprintGeneratedClass);
					FString ObjectNameLower = UKismetStringLibrary::ToLower(ObjectName);

					FString StringClassName = std::wstring(ClassName.begin(), ClassName.end()).c_str();
					FString StringClassNameLower = UKismetStringLibrary::ToLower(StringClassName);

					if (ObjectNameLower == StringClassNameLower)
					{
						const float LootSpawnLocationX = 300;
						const float LootSpawnLocationY = 0;
						const float LootSpawnLocationZ = 0;

						FVector SpawnLocation = PlayerPawn->K2_GetActorLocation() +
							PlayerPawn->GetActorForwardVector() * LootSpawnLocationX +
							PlayerPawn->GetActorRightVector() * LootSpawnLocationY +
							PlayerPawn->GetActorUpVector() * LootSpawnLocationZ;

						for (int32 j = 0; j < AmountToSpawn; j++)
						{
							AActor* Actor = Util::SpawnActor<AActor>(BlueprintGeneratedClass, SpawnLocation);

							ABuildingContainer* BuildingContainer = Cast<ABuildingContainer>(Actor);
							ABuildingSMActor* BuildingSMActor = Cast<ABuildingSMActor>(Actor);

							if (BuildingContainer)
							{
								BuildingContainer->PostUpdate(EFortBuildingPersistentState::New);
							}
							else if (BuildingSMActor)
							{
								BuildingSMActor->PostUpdate();
							}
						}

						Message = L"Summon successful!";
						bFindClass = true;
						break;
					}
				}

				if (!bFindClass)
					Message = L"Class not found!";
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}
		}
		else if (Action == "spawnloot" && ParsedCommand.size() >= 2)
		{
			std::string& LootTierGroup = ParsedCommand[1];

			FName TierGroupName = UKismetStringLibrary::Conv_StringToName(std::wstring(LootTierGroup.begin(), LootTierGroup.end()).c_str());

			int32 WorldLevel = -1;

			if (ParsedCommand.size() >= 3)
			{
				bool bIsWorldLevelInt = std::all_of(ParsedCommand[2].begin(), ParsedCommand[2].end(), ::isdigit);

				if (bIsWorldLevelInt)
					WorldLevel = std::stoi(ParsedCommand[2]);
			}

			int32 ForcedLootTier = -1;

			if (ParsedCommand.size() >= 4)
			{
				bool bIsForcedLootTierInt = std::all_of(ParsedCommand[3].begin(), ParsedCommand[3].end(), ::isdigit);

				if (bIsForcedLootTierInt)
					ForcedLootTier = std::stoi(ParsedCommand[3]);
			}

			TArray<FFortItemEntry> LootToDrops;
			bool bSuccess = UFortKismetLibrary::PickLootDrops(PlayerController, &LootToDrops, TierGroupName, WorldLevel, ForcedLootTier);

			if (bSuccess && PlayerPawn)
			{
				const FVector& SpawnLocation = PlayerPawn->K2_GetActorLocation();

				for (auto& LootToDrop : LootToDrops)
				{
					AFortPickup* Pickup = AFortPickup::CreatePickup(
						PlayerController->GetWorld(),
						&LootToDrop,
						&SpawnLocation,
						nullptr,
						nullptr,
						nullptr,
						true,
						(uint32)EFortPickupSourceTypeFlag::Tossed);

					if (Pickup)
					{
						Pickup->TossPickup(SpawnLocation, PlayerPawn, 0, true);
						Pickup->PawnWhoDroppedPickup = PlayerPawn;
					}
				}

				Message = L"TierGroupName success spawn!";
			}
			else
			{
				if (!PlayerPawn)
				{
					Message = L"PlayerPawn not found!";
				}
				else
				{
					Message = L"Failed to find this TierGroupName!";
				}
			}

			FFortItemEntry::FreeItemEntries(&LootToDrops);
		}
		else if (Action == "spawnpickup" && ParsedCommand.size() >= 2)
		{
			std::string ItemDefinitionName = ParsedCommand[1];

			std::transform(ItemDefinitionName.begin(), ItemDefinitionName.end(), ItemDefinitionName.begin(),
				[](unsigned char c) { return std::tolower(c); });

			int32 NumberToSpawn = 1;

			if (ParsedCommand.size() >= 3)
			{
				bool bIsNumberToSpawnInt = std::all_of(ParsedCommand[2].begin(), ParsedCommand[2].end(), ::isdigit);

				if (bIsNumberToSpawnInt)
					NumberToSpawn = std::stoi(ParsedCommand[2]);
			}

			TArray<UFortItemDefinition*> AllItems = Functions::GetAllItems();

			if (PlayerPawn)
			{
				if (NumberToSpawn <= 10000 && NumberToSpawn > 0)
				{
					const FVector& SpawnLocation = PlayerPawn->K2_GetActorLocation();

					bool bItemFound = false;
					for (int32 i = 0; i < AllItems.Num(); i++)
					{
						UFortWorldItemDefinition* ItemDefinition = Cast<UFortWorldItemDefinition>(AllItems[i]);

						if (!ItemDefinition)
							continue;

						std::string ItemDefinitionName2 = ItemDefinition->GetName();

						std::transform(ItemDefinitionName2.begin(), ItemDefinitionName2.end(), ItemDefinitionName2.begin(),
							[](unsigned char c) { return std::tolower(c); });

						if (ItemDefinitionName2 != ItemDefinitionName)
							continue;

						UFortKismetLibrary::K2_SpawnPickupInWorld(PlayerController, ItemDefinition, NumberToSpawn, SpawnLocation, SpawnLocation, 0, true, true, true);
						bItemFound = true;
						break;
					}

					if (bItemFound)
					{
						Message = L"Pickup successfully spawned!";
					}
					else
					{
						Message = L"Item definition not found!";
					}
				}
				else
				{
					Message = L"Invalid number to spawn (NumberToSpawn <= 10000 && NumberToSpawn > 0)";
				}
			}
			else
			{
				Message = L"PlayerPawn not found!";
			}

			if (AllItems.IsValid())
				AllItems.Free();
		}
		else if (Action == "giveitem" && ParsedCommand.size() >= 2)
		{
			std::string ItemDefinitionName = ParsedCommand[1];

			std::transform(ItemDefinitionName.begin(), ItemDefinitionName.end(), ItemDefinitionName.begin(),
				[](unsigned char c) { return std::tolower(c); });

			int32 NumberToGive = 1;
			bool bNotifyPlayer = true;

			if (ParsedCommand.size() >= 3)
			{
				bool bIsNumberToGiveInt = std::all_of(ParsedCommand[2].begin(), ParsedCommand[2].end(), ::isdigit);

				if (bIsNumberToGiveInt)
					NumberToGive = std::stoi(ParsedCommand[2]);
			}

			if (ParsedCommand.size() >= 4)
			{
				bool bIsNotifyPlayerInt = std::all_of(ParsedCommand[3].begin(), ParsedCommand[3].end(), ::isdigit);

				if (bIsNotifyPlayerInt)
					bNotifyPlayer = std::stoi(ParsedCommand[3]);
			}

			TArray<UFortItemDefinition*> AllItems = Functions::GetAllItems();

			if (NumberToGive <= 10000 && NumberToGive > 0)
			{
				bool bItemFound = false;
				for (int32 i = 0; i < AllItems.Num(); i++)
				{
					UFortWorldItemDefinition* ItemDefinition = Cast<UFortWorldItemDefinition>(AllItems[i]);

					if (!ItemDefinition)
						continue;

					std::string ItemDefinitionName2 = ItemDefinition->GetName();

					std::transform(ItemDefinitionName2.begin(), ItemDefinitionName2.end(), ItemDefinitionName2.begin(),
						[](unsigned char c) { return std::tolower(c); });

					if (ItemDefinitionName2 != ItemDefinitionName)
						continue;

					UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, ItemDefinition, NumberToGive, bNotifyPlayer);
					bItemFound = true;
					break;
				}

				if (bItemFound)
				{
					Message = L"Item give success!";
				}
				else
				{
					Message = L"Item definition not found!";
				}
			}
			else
			{
				Message = L"Invalid number to give (NumberToGive <= 10000 && NumberToGive > 0)";
			}

			if (AllItems.IsValid())
				AllItems.Free();
		}
		else if (Action == "removeitem" && ParsedCommand.size() >= 2)
		{
			std::string ItemDefinitionName = ParsedCommand[1];

			std::transform(ItemDefinitionName.begin(), ItemDefinitionName.end(), ItemDefinitionName.begin(),
				[](unsigned char c) { return std::tolower(c); });

			int32 AmountToRemove = 1;

			if (ParsedCommand.size() >= 3)
			{
				bool bIsAmountToRemoveInt = std::all_of(ParsedCommand[2].begin(), ParsedCommand[2].end(), ::isdigit);

				if (bIsAmountToRemoveInt)
					AmountToRemove = std::stoi(ParsedCommand[2]);
			}

			TArray<UFortItemDefinition*> AllItems = Functions::GetAllItems();

			if (AmountToRemove <= 10000 && AmountToRemove > 0)
			{
				bool bItemFound = false;

				for (int32 i = 0; i < AllItems.Num(); i++)
				{
					UFortWorldItemDefinition* ItemDefinition = Cast<UFortWorldItemDefinition>(AllItems[i]);

					if (!ItemDefinition)
						continue;

					std::string ItemDefinitionName2 = ItemDefinition->GetName();

					std::transform(ItemDefinitionName2.begin(), ItemDefinitionName2.end(), ItemDefinitionName2.begin(),
						[](unsigned char c) { return std::tolower(c); });

					if (ItemDefinitionName2 != ItemDefinitionName)
						continue;

					UFortKismetLibrary::K2_RemoveItemFromPlayer(PlayerController, ItemDefinition, AmountToRemove, true);
					bItemFound = true;
					break;
				}

				if (bItemFound)
				{
					Message = L"Item remove success!";
				}
				else
				{
					Message = L"Item definition not found!";
				}
			}
			else
			{
				Message = L"Invalid number to remove (AmountToRemove <= 10000 && AmountToRemove > 0)";
			}

			if (AllItems.IsValid())
				AllItems.Free();
		}
		else if (Action == "dbno" && ParsedCommand.size() >= 2)
		{
			std::string PlayerName = ParsedCommand[1];

			TArray<AFortPlayerController*> AllFortPlayerControllers = UFortKismetLibrary::GetAllFortPlayerControllers(PlayerController, true, false);

			for (int32 i = 0; i < AllFortPlayerControllers.Num(); i++)
			{
				auto FortPlayerController = AllFortPlayerControllers[i];
				if (!FortPlayerController) continue;

				auto TempPlayerState = FortPlayerController->PlayerState;
				if (!TempPlayerState) continue;

				if (TempPlayerState->GetPlayerName().ToString() == PlayerName)
				{
					auto TempPlayerPawn = FortPlayerController->GetPlayerPawn();
					if (!TempPlayerPawn) break;

					bool bOldDBNO = TempPlayerPawn->bIsDBNO;

					TempPlayerPawn->bIsDBNO = bOldDBNO ? false : true;
					break;
				}
			}

			Message = L"dbno test!";
		}
		else if (Action == "rtx" && ParsedCommand.size() >= 1)
		{
			TArray<UFortItemDefinition*> AllItems = Functions::GetAllItems(true);

			if (AllItems.Num() > 0 && PlayerPawn)
			{
				const FVector& SpawnLocation = PlayerPawn->K2_GetActorLocation();

				for (int32 i = 0; i < AllItems.Num(); i++)
				{
					UFortWorldItemDefinition* ItemDefinition = Cast<UFortWorldItemDefinition>(AllItems[i]);

					if (!ItemDefinition)
						continue;

					if (ItemDefinition->Rarity != EFortRarity::Fine)
						continue;

					UFortKismetLibrary::K2_SpawnPickupInWorld(PlayerController, ItemDefinition, 1, SpawnLocation, SpawnLocation, 0, true, true, false);
				}

				Message = L"TEUPAIIII!";
			}
			else
			{
				if (!PlayerPawn)
				{
					Message = L"PlayerPawn not found!";
				}
				else
				{
					Message = L"No items found to spawn!";
				}
			}

			if (AllItems.IsValid())
				AllItems.Free();
		}

#endif // CHEATS

		if (Message != L"null")
			PlayerController->ClientMessage(Message, FName(), 1);
	}

	AActor* SpawnToyInstance(AFortPlayerController* PlayerController, FFrame& Stack, AActor** Ret)
	{
		TSubclassOf<AActor> ToyClass{};
		FTransform SpawnPosition = FTransform();

		Stack.StepCompiledIn(&ToyClass);
		Stack.StepCompiledIn(&SpawnPosition);

		Stack.Code += Stack.Code != nullptr;

		ABuildingGameplayActor* ToyInstance = Util::SpawnActorTransfrom<ABuildingGameplayActor>(ToyClass, SpawnPosition);

		if (ToyInstance)
		{
			ToyInstance->SetOwner(PlayerController);
			ToyInstance->OnRep_Owner();

			PlayerController->ActiveToyInstances.Add(ToyInstance);
		}

		*Ret = ToyInstance;
		return *Ret;
	}

	/* -------------------------------------- PlayerController --------------------------------------- */

	void ServerAcknowledgePossession(APlayerController* PlayerController, APawn* P)
	{
		if (!PlayerController || !P)
			return;

		if (PlayerController->AcknowledgedPawn == P)
			return;

		PlayerController->AcknowledgedPawn = P;
	}

	/*
	 *	Reimplantation of void APlayerController::ServerChangeName(APawn* P)
	 *	Call in void APlayerController::SetName(const FString& S)
	 *	Source Code: https://github.com/EpicGames/UnrealEngine/blob/4.21/Engine/Source/Runtime/Engine/Private/PlayerController.cpp#L1814
	*/
	void ServerChangeName(APlayerController* PlayerController, const FString& S)
	{
		ServerChangeNameOG(PlayerController, S);
	}

	/* --------------------------------------- InventoryOwner ---------------------------------------- */

	bool RemoveInventoryItem(void* InventoryOwner, const FGuid& ItemGuid, int32 Count, bool bForceRemoveFromQuickBars, bool bForceRemoval)
	{
		AFortPlayerController* PlayerController = AFortPlayerController::GetPlayerControllerFromInventoryOwner(InventoryOwner);
		if (!PlayerController) return false;

		if (Count == 0)
			return true;

		if (PlayerController->bInfiniteAmmo && !bForceRemoval)
			return true;

		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(ItemGuid));
		if (!WorldItem) return false;

		FFortItemEntry ItemEntry = WorldItem->ItemEntry;

		if (Count == -1)
		{
			Inventory::RemoveItem(PlayerController->WorldInventory, ItemGuid);
			return true;
		}

		if (Count >= ItemEntry.Count)
		{
			UFortWeaponRangedItemDefinition* WeaponRangedItemDefinition = Cast<UFortWeaponRangedItemDefinition>(ItemEntry.ItemDefinition);

			if (WeaponRangedItemDefinition && WeaponRangedItemDefinition->bPersistInInventoryWhenFinalStackEmpty)
			{
				int32 ItemQuantity = UFortKismetLibrary::K2_GetItemQuantityOnPlayer(PlayerController, WeaponRangedItemDefinition);

				if (ItemQuantity == 1)
				{
					Inventory::ModifyCountItem(PlayerController->WorldInventory, ItemGuid, 0);
					return true;
				}
			}

			Inventory::RemoveItem(PlayerController->WorldInventory, ItemGuid);
		}
		else if (Count < ItemEntry.Count)
		{
			int32 NewCount = ItemEntry.Count - Count;

			Inventory::ModifyCountItem(PlayerController->WorldInventory, ItemGuid, NewCount);
		}
		else
			return false;

		return true;
	}

	void ModLoadedAmmo(void* InventoryOwner, const FGuid& ItemGuid, int32 Count)
	{
		AFortPlayerController* PlayerController = AFortPlayerController::GetPlayerControllerFromInventoryOwner(InventoryOwner);
		if (!PlayerController) return;

		AFortInventory* WorldInventory = PlayerController->WorldInventory;
		if (!WorldInventory) return;

		for (int32 i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = WorldInventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &WorldInventory->Inventory.ItemInstances[i]->ItemEntry;

			if (ItemEntry->ItemGuid == ItemGuid)
			{
				ItemEntry->SetLoadedAmmo(Count);
				break;
			}
		}

		// I think that normally you don't need to modify the value here but for me it doesn't work idk
		for (int32 i = 0; i < WorldInventory->Inventory.ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry* ReplicatedItemEntry = &WorldInventory->Inventory.ReplicatedEntries[i];

			if (ReplicatedItemEntry->ItemGuid == ItemGuid)
			{
				ReplicatedItemEntry->LoadedAmmo = Count;
				WorldInventory->Inventory.MarkItemDirty(*ReplicatedItemEntry);
				break;
			}
		}
	}

	bool ModDurability(void* InventoryOwner, const FGuid& ItemGuid, float DurabilityMod, bool bForceSet)
	{
		return false;
	}

	/* ----------------------------------------------------------------------------------------------- */

	void InitPlayerController()
	{
		AFortPlayerControllerAthena* FortPlayerControllerAthenaDefault = AFortPlayerControllerAthena::GetDefaultObj();
		UClass* FortPlayerControllerAthenaClass = AFortPlayerControllerAthena::StaticClass();

		/* --------------------------------- AFortPlayerControllerAthena --------------------------------- */

		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1E88 / 8, ServerThankBusDriver, (LPVOID*)(&ServerThankBusDriverOG), "AFortPlayerControllerAthena::ServerThankBusDriver");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1DE8 / 8, ServerPlaceMapCursor, (LPVOID*)(&ServerPlaceMapCursorOG), "AFortPlayerControllerAthena::ServerPlaceMapCursor");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1DD8 / 8, ServerRemoveMapCursor, (LPVOID*)(&ServerRemoveMapCursorOG), "AFortPlayerControllerAthena::ServerRemoveMapCursor");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1EA0 / 8, ServerPlaySquadQuickChatMessage, nullptr, "AFortPlayerControllerAthena::ServerPlaySquadQuickChatMessage");

		/* ---------------------------------- AFortPlayerControllerZone ---------------------------------- */

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0x14DCFF0), ClientOnPawnDied, (LPVOID*)(&ClientOnPawnDiedOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0x14DCFF0));

		/* ------------------------------------ AFortPlayerController ------------------------------------ */

		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1278 / 8, ServerReadyToStartMatch, (LPVOID*)(&ServerReadyToStartMatchOG), "AFortPlayerController::ServerReadyToStartMatch");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1030 / 8, ServerCombineInventoryItems, nullptr, "AFortPlayerController::ServerCombineInventoryItems");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1020 / 8, ServerAttemptInventoryDrop, nullptr, "AFortPlayerController::ServerAttemptInventoryDrop");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1208 / 8, ServerAttemptInteract, (LPVOID*)(&ServerAttemptInteractOG), "AFortPlayerController::ServerAttemptInteract");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1080 / 8, ServerCreateBuildingActor, nullptr, "AFortPlayerController::ServerCreateBuildingActor");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1060 / 8, ServerRepairBuildingActor, nullptr, "AFortPlayerController::ServerRepairBuildingActor");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x10B0 / 8, ServerBeginEditingBuildingActor, nullptr, "AFortPlayerController::ServerBeginEditingBuildingActor");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1090 / 8, ServerEditBuildingActor, nullptr, "AFortPlayerController::ServerEditBuildingActor");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x10A0 / 8, ServerEndEditingBuildingActor, nullptr, "AFortPlayerController::ServerEndEditingBuildingActor");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0xD50 / 8, ServerDropAllItems, nullptr, "AFortPlayerController::ServerDropAllItems");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0xF90 / 8, ServerExecuteInventoryItem, nullptr, "AFortPlayerController::ServerExecuteInventoryItem");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0xDB0 / 8, ServerPlayEmoteItem, nullptr, "AFortPlayerController::ServerPlayEmoteItem");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0xF40 / 8, ServerSetInventoryStateValue, nullptr, "AFortPlayerController::ServerSetInventoryStateValue");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0xF30 / 8, ServerRemoveInventoryStateValue, nullptr, "AFortPlayerController::ServerRemoveInventoryStateValue");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x1258 / 8, ServerReturnToMainMenu, nullptr, "AFortPlayerController::ServerReturnToMainMenu");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0xDA0 / 8, ServerCheat, (LPVOID*)(&ServerCheatOG), "AFortPlayerController::ServerCheat");

		UFunction* SpawnToyInstanceFunc = FortPlayerControllerAthenaClass->GetFunction("FortPlayerController", "SpawnToyInstance");
		MinHook::HookFunctionExec(SpawnToyInstanceFunc, SpawnToyInstance, nullptr);

		/* -------------------------------------- PlayerController --------------------------------------- */

		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x828 / 8, ServerAcknowledgePossession, nullptr, "APlayerController::ServerAcknowledgePossession");
		MinHook::HookVTable(FortPlayerControllerAthenaDefault, 0x808 / 8, ServerChangeName, (LPVOID*)(&ServerChangeNameOG), "APlayerController::ServerChangeName");

		/* --------------------------------------- InventoryOwner ---------------------------------------- */

		UObject* InventoryOwnerDefault = (UObject*)(__int64(FortPlayerControllerAthenaDefault) + InventoryOwnerOffset);

		MinHook::HookVTable(InventoryOwnerDefault, 0x14, RemoveInventoryItem, nullptr, "RemoveInventoryItem");
		MinHook::HookVTable(InventoryOwnerDefault, 0xC, ModDurability, nullptr, "ModDurability");
		MinHook::HookVTable(InventoryOwnerDefault, 0xD, ModLoadedAmmo, nullptr, "ModLoadedAmmo");

		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitPlayerController Success!");
	}
}