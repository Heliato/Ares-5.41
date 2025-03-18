#pragma once
#include <map>

namespace Functions
{
	bool IsPlayerBuildableClasse(UClass* BuildableClasse)
	{
		AFortGameStateAthena* GameState = Cast<AFortGameStateAthena>(Globals::GetGameState());

		if (!BuildableClasse || !GameState)
			return false;

		TArray<TSubclassOf<ABuildingActor>> BuildingActorClasses = GameState->BuildingActorClasses;

		if (BuildingActorClasses.IsValid())
		{
			for (int32 i = 0; i < BuildingActorClasses.Num(); i++)
			{
				TSubclassOf<ABuildingActor> BuildingActorClasse = BuildingActorClasses[i];
				if (!BuildingActorClasse.Get()) continue;

				if (BuildingActorClasse.Get() == BuildableClasse)
					return true;
			}
		}

		return false;
	}

	bool IsOnSameTeam(AFortPlayerStateAthena* PlayerState, ABuildingSMActor* BuildingSMActor)
	{
		if (!PlayerState || !BuildingSMActor)
			return false;

		EFortTeam PlayerTeam = PlayerState->TeamIndex;
		EFortTeam BuildingTeam = BuildingSMActor->Team;

		if (PlayerTeam == BuildingTeam)
			return true;

		if (BuildingTeam == EFortTeam::Spectator && !BuildingSMActor->bPlayerPlaced)
			return true;

		return false;
	}

	// 7FF66F3270B0
	void SetEditingPlayer(ABuildingSMActor* BuildingActor, AFortPlayerStateZone* EditingPlayer)
	{
		if (BuildingActor->HasAuthority() && (!BuildingActor->EditingPlayer || !EditingPlayer))
		{
			BuildingActor->SetNetDormancy(ENetDormancy(2 - (EditingPlayer != 0)));
			BuildingActor->ForceNetUpdate();
			BuildingActor->EditingPlayer = EditingPlayer;
		}
	}

	// 7FF66F986F80
	void SetEditingActor(AFortWeap_EditingTool* EditingTool, ABuildingSMActor* BuildingActor)
	{
		if (EditingTool->HasAuthority())
		{
			EditingTool->EditActor = BuildingActor;
			EditingTool->OnRep_EditActor();
		}
	}

	UClass* LoadClass(TSoftClassPtr<UClass> SoftClass)
	{
		UClass* Class = SoftClass.Get();

		if (!Class)
		{
			const FString& AssetPathName = UKismetStringLibrary::Conv_NameToString(SoftClass.ObjectID.AssetPathName);
			Class = StaticLoadObject<UClass>(AssetPathName.CStr());
		}

		return Class;
	}

	UFortGameplayAbility* LoadGameplayAbility(TSoftClassPtr<UClass> SoftGameplayAbility)
	{
		UClass* GameplayAbilityClass = SoftGameplayAbility.Get();

		if (!GameplayAbilityClass)
		{
			const FString& AssetPathName = UKismetStringLibrary::Conv_NameToString(SoftGameplayAbility.ObjectID.AssetPathName);
			GameplayAbilityClass = StaticLoadObject<UClass>(AssetPathName.CStr());
		}

		if (GameplayAbilityClass)
			return Cast<UFortGameplayAbility>(GameplayAbilityClass->CreateDefaultObject());

		return nullptr;
	}

	UFortAbilitySet* LoadAbilitySet(TSoftObjectPtr<UFortAbilitySet> SoftAbilitySet)
	{
		UFortAbilitySet* AbilitySet = SoftAbilitySet.Get();

		if (!AbilitySet)
		{
			const FString& AssetPathName = UKismetStringLibrary::Conv_NameToString(SoftAbilitySet.ObjectID.AssetPathName);
			AbilitySet = StaticLoadObject<UFortAbilitySet>(AssetPathName.CStr());
		}

		return AbilitySet;
	}

	UFortGameplayModifierItemDefinition* LoadGameplayModifier(TSoftObjectPtr<UFortGameplayModifierItemDefinition> SoftGameplayModifier)
	{
		UFortGameplayModifierItemDefinition* GameplayModifier = SoftGameplayModifier.Get();

		if (!GameplayModifier)
		{
			const FString& AssetPathName = UKismetStringLibrary::Conv_NameToString(SoftGameplayModifier.ObjectID.AssetPathName);
			GameplayModifier = StaticLoadObject<UFortGameplayModifierItemDefinition>(AssetPathName.CStr());
		}

		return GameplayModifier;
	}

	int GetRandomRarity(const std::map<int32, float>& RarityAndWeight) 
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::vector<float> weights;

		for (const auto& kv : RarityAndWeight) 
		{
			weights.push_back(kv.second);
		}

		std::discrete_distribution<> dist(weights.begin(), weights.end());

		return dist(gen);
	}

	void VendingMachinePlayVendFX(ABuildingItemCollectorActor* ItemCollectorActor)
	{
		if (!ItemCollectorActor)
			return;

		UFunction* PlayVendFXFunc = nullptr;

		if (PlayVendFXFunc == nullptr)
			PlayVendFXFunc = ItemCollectorActor->Class->GetFunction("B_Athena_VendingMachine_C", "PlayVendFX");

		if (PlayVendFXFunc)
			ItemCollectorActor->ProcessEvent(PlayVendFXFunc, nullptr);
	}

	void VendingMachinePlayVendFailFX(ABuildingItemCollectorActor* ItemCollectorActor)
	{
		if (!ItemCollectorActor)
			return;

		UFunction* PlayVendFailFXFunc = nullptr;

		if (PlayVendFailFXFunc == nullptr)
			PlayVendFailFXFunc = ItemCollectorActor->Class->GetFunction("B_Athena_VendingMachine_C", "PlayVendFailFX");

		if (PlayVendFailFXFunc)
			ItemCollectorActor->ProcessEvent(PlayVendFailFXFunc, nullptr);
	}

	UAthenaGliderItemDefinition* ChooseRandomGlider()
	{
		TArray<UAthenaCosmeticItemDefinition*> AllGliderItems = UFortniteAutomationBlueprintLibrary::GetAllAthenaCosmetics(EFortItemType::AthenaGlider);
		return Cast<UAthenaGliderItemDefinition>(AllGliderItems[std::rand() % AllGliderItems.Num()]);
	}

	UAthenaPickaxeItemDefinition* ChooseRandomPickaxe()
	{
		TArray<UAthenaCosmeticItemDefinition*> AllPickaxeItems = UFortniteAutomationBlueprintLibrary::GetAllAthenaCosmetics(EFortItemType::AthenaPickaxe);
		return Cast<UAthenaPickaxeItemDefinition>(AllPickaxeItems[std::rand() % AllPickaxeItems.Num()]);
	}

	UAthenaCharacterItemDefinition* ChooseRandomCharacter()
	{
		TArray<UAthenaCosmeticItemDefinition*> AllCharacterItems = UFortniteAutomationBlueprintLibrary::GetAllAthenaCosmetics(EFortItemType::AthenaCharacter);
		return Cast<UAthenaCharacterItemDefinition>(AllCharacterItems[std::rand() % AllCharacterItems.Num()]);
	}

	UAthenaBackpackItemDefinition* ChooseRandomBackpack()
	{
		TArray<UAthenaCosmeticItemDefinition*> AllBackpackItems = UFortniteAutomationBlueprintLibrary::GetAllAthenaCosmetics(EFortItemType::AthenaBackpack);
		return Cast<UAthenaBackpackItemDefinition>(AllBackpackItems[std::rand() % AllBackpackItems.Num()]);
	}

	void FillVendingMachine(ABuildingItemCollectorActor* ItemCollectorActor, std::map<int32, float> RarityAndWeight)
	{
		if (!ItemCollectorActor)
			return;

		int32 RandomRarity = GetRandomRarity(RarityAndWeight);

		if (RandomRarity == 0)
		{
			ItemCollectorActor->K2_DestroyActor();
			return;
		}

		// Get Real Rarity
		RandomRarity -= 1;

		// 0 = Common
		// 1 = UnCommon
		// 2 = Rare
		// 3 = Epic
		// 4 = Legendary

		TArray<FColletorUnitInfo> ItemCollections = ItemCollectorActor->ItemCollections;

		for (int32 i = 0; i < ItemCollections.Num(); i++)
		{
			FColletorUnitInfo& ItemCollection = ItemCollections[i];
			UFortWorldItemDefinition* InputItem = ItemCollection.InputItem;
			if (!InputItem) continue;

			int32 LootLevel = UFortKismetLibrary::GetLootLevel(ItemCollectorActor);

			TArray<FFortItemEntry> LootToDrops;
			bool bValidLoot = false;

			do
			{
				FName LootTierKey = FName(0);
				int32 LootTier = -1;

				bool bSuccess = Loots::PickLootTierKeyAndLootTierFromTierGroup(&LootTierKey, &LootTier, ItemCollectorActor->DefaultItemLootTierGroupName, LootLevel, 0, RandomRarity, ItemCollectorActor->StaticGameplayTags);
				if (!bSuccess) continue;

				Loots::PickLootDrops(&LootToDrops, LootLevel, LootTierKey, 0, 0, ItemCollectorActor->StaticGameplayTags, false, false);

				bValidLoot = true;
				if (LootToDrops.Num() > 0)
				{
					UFortWorldItemDefinition* LootToDropDefinition = Cast<UFortWorldItemDefinition>(LootToDrops[0].ItemDefinition);

					for (const FColletorUnitInfo& OtherItemCollection : ItemCollections)
					{
						if (OtherItemCollection.OutputItem == LootToDropDefinition)
						{
							bValidLoot = false;
							break;
						}
					}
				}

			} while (!bValidLoot);

			if (ItemCollections[i].OutputItemEntry.Num() > 0)
				ItemCollections[i].OutputItemEntry.Free();

			for (auto& LootToDrop : LootToDrops)
				ItemCollections[i].OutputItemEntry.Add(LootToDrop);

			if (ItemCollections[i].OutputItemEntry.IsValidIndex(0))
				ItemCollections[i].OutputItem = Cast<UFortWorldItemDefinition>(ItemCollections[i].OutputItemEntry[0].ItemDefinition);
		}

		ItemCollectorActor->StartingGoalLevel = RandomRarity;
	}

	void FillVendingMachines()
	{
		AFortGameStateAthena* GameState = Cast<AFortGameStateAthena>(Globals::GetGameState());

		if (GameState && GameState->MapInfo)
		{
			AFortAthenaMapInfo* MapInfo = GameState->MapInfo;

			TArray<AActor*> VendingMachines;
			UGameplayStatics::GetAllActorsOfClass(MapInfo, MapInfo->VendingMachineClass, &VendingMachines);

			FScalableFloat VendingMachineRarityCount = MapInfo->VendingMachineRarityCount;

			std::map<int32, float> RarityAndWeight;

			// 0 = Destroy - RarityCount: 1.00, Value: 1.00
			// 1 = Common - RarityCount: 0.25, Value: 1.00
			// 2 = UnCommon - RarityCount: 0.75, Value: 1.00
			// 3 = Rare - RarityCount: 0.75, Value: 1.00
			// 4 = Epic - RarityCount: 0.70, Value: 1.00
			// 5 = Legendary - RarityCount: 0.30, Value: 1.00

			for (int32 i = 0; i < 6; i++)
			{
				float RarityCount = MapInfo->VendingMachineRarityCount.GetValueAtLevel(i);
				RarityAndWeight[i] = RarityCount;
			}

			for (int32 i = 0; i < VendingMachines.Num(); i++)
			{
				ABuildingItemCollectorActor* VendingMachine = Cast<ABuildingItemCollectorActor>(VendingMachines[i]);
				if (!VendingMachine) continue;

				FillVendingMachine(VendingMachine, RarityAndWeight);
			}

			if (VendingMachines.Num() > 0)
				VendingMachines.Free();
		}
	}

	ABuildingGameplayActorConsumable* SpawnGameplayActorConsumable(ABGAConsumableSpawner* ConsumableSpawner, UBGAConsumableWrapperItemDefinition* ConsumableWrapperItemDefinition)
	{
		if (!ConsumableSpawner || !ConsumableWrapperItemDefinition)
			return nullptr;

		UClass* ConsumableClass = ConsumableWrapperItemDefinition->ConsumableClass.Get();

		if (!ConsumableClass)
		{
			const FString& AssetPathName = UKismetStringLibrary::Conv_NameToString(ConsumableWrapperItemDefinition->ConsumableClass.ObjectID.AssetPathName);
			ConsumableClass = StaticLoadObject<UClass>(AssetPathName.CStr());
		}

		if (!ConsumableClass)
			return nullptr;

		FVector SpawnLocation = ConsumableSpawner->K2_GetActorLocation();

		UBlueprintGeneratedClass* BGA_RiftPortal_Athena_Spawner = FindObjectFast<UBlueprintGeneratedClass>("/Game/Athena/Items/ForagedItems/Rift/BGA_RiftPortal_Athena_Spawner.BGA_RiftPortal_Athena_Spawner_C");

		if (!BGA_RiftPortal_Athena_Spawner)
			BGA_RiftPortal_Athena_Spawner = StaticLoadObject<UBlueprintGeneratedClass>(L"/Game/Athena/Items/ForagedItems/Rift/BGA_RiftPortal_Athena_Spawner.BGA_RiftPortal_Athena_Spawner_C");

		if (ConsumableClass != BGA_RiftPortal_Athena_Spawner)
		{
			FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();

			SpawnLocation.X += RandomDirection.X * 500.0f;
			SpawnLocation.Y += RandomDirection.Y * 500.0f;

			const FVector& End = SpawnLocation - FVector({ 0, 0, 1000 });

			FHitResult HitResult;
			bool bHit = UKismetSystemLibrary::LineTraceSingle(
				ConsumableSpawner,
				SpawnLocation,
				End,
				ETraceTypeQuery::TraceTypeQuery1,
				false,
				TArray<AActor*>(),
				EDrawDebugTrace::ForDuration,
				&HitResult,
				true,
				FLinearColor(),
				FLinearColor(),
				0.0f);

			if (bHit)
				SpawnLocation = HitResult.Location;
		}

		FTransform SpawnTransform = UKismetMathLibrary::MakeTransform(SpawnLocation, ConsumableSpawner->K2_GetActorRotation(), FVector({ 1, 1, 1 }));

		ABuildingGameplayActorConsumable* GameplayActorConsumable = Util::SpawnActorTransfrom<ABuildingGameplayActorConsumable>(ConsumableClass, SpawnTransform);

		if (GameplayActorConsumable)
			UGameplayStatics::FinishSpawningActor(GameplayActorConsumable, SpawnTransform);

		return GameplayActorConsumable;
	}

	void InitializeTreasureChests()
	{
		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(Globals::GetGameState());
		bool bSpawnAllLoot = FParse::Param(FCommandLine::Get(), TEXT("SpawnAllLoot"));

		if (GameStateAthena && GameStateAthena->MapInfo && !bSpawnAllLoot)
		{
			AFortAthenaMapInfo* MapInfo = GameStateAthena->MapInfo;

			float TreasureChestMinSpawnPercent = MapInfo->TreasureChestMinSpawnPercent.GetValueAtLevel(0); // 50%
			float TreasureChestMaxSpawnPercent = MapInfo->TreasureChestMaxSpawnPercent.GetValueAtLevel(0); // 70%

			TArray<AActor*> TreasureChests;
			UGameplayStatics::GetAllActorsOfClass(MapInfo, MapInfo->TreasureChestClass, &TreasureChests);

			int32 TotalTreasureChests = TreasureChests.Num();
			int32 MinTreasureChestsToKeep = std::floor(TotalTreasureChests * (TreasureChestMinSpawnPercent / 100.0f));
			int32 MaxTreasureChestsToKeep = std::floor(TotalTreasureChests * (TreasureChestMaxSpawnPercent / 100.0f));

			int32 NumTreasureChestsToKeep = UKismetMathLibrary::RandomIntegerInRange(MinTreasureChestsToKeep, MaxTreasureChestsToKeep);

			for (int32 i = TotalTreasureChests - 1; i >= NumTreasureChestsToKeep; --i)
			{
				int32 IndexToDestroy = UKismetMathLibrary::RandomIntegerInRange(0, i);

				TreasureChests[IndexToDestroy]->K2_DestroyActor();
				TreasureChests.Remove(IndexToDestroy);
			}

			if (TreasureChests.Num() > 0)
				TreasureChests.Free();
		}
	}

	void InitializeAmmoBoxs()
	{
		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(Globals::GetGameState());
		bool bSpawnAllLoot = FParse::Param(FCommandLine::Get(), TEXT("SpawnAllLoot"));

		if (GameStateAthena && GameStateAthena->MapInfo && !bSpawnAllLoot)
		{
			AFortAthenaMapInfo* MapInfo = GameStateAthena->MapInfo;

			float AmmoBoxMinSpawnPercent = MapInfo->AmmoBoxMinSpawnPercent.GetValueAtLevel(0); // 65%
			float AmmoBoxMaxSpawnPercent = MapInfo->AmmoBoxMaxSpawnPercent.GetValueAtLevel(0); // 80%

			TArray<AActor*> AmmoBoxs;
			UGameplayStatics::GetAllActorsOfClass(MapInfo, MapInfo->AmmoBoxClass, &AmmoBoxs);

			int32 TotalAmmoBoxs = AmmoBoxs.Num();
			int32 MinAmmoBoxsToKeep = std::floor(TotalAmmoBoxs * (AmmoBoxMinSpawnPercent / 100.0f));
			int32 MaxAmmoBoxsToKeep = std::floor(TotalAmmoBoxs * (AmmoBoxMaxSpawnPercent / 100.0f));

			int32 NumAmmoBoxsToKeep = UKismetMathLibrary::RandomIntegerInRange(MinAmmoBoxsToKeep, MaxAmmoBoxsToKeep);

			for (int32 i = TotalAmmoBoxs - 1; i >= NumAmmoBoxsToKeep; --i)
			{
				int32 IndexToDestroy = UKismetMathLibrary::RandomIntegerInRange(0, i);

				AmmoBoxs[IndexToDestroy]->K2_DestroyActor();
				AmmoBoxs.Remove(IndexToDestroy);
			}

			if (AmmoBoxs.Num() > 0)
				AmmoBoxs.Free();
		}
	}

	void InitializeLlamas()
	{
		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(Globals::GetGameState());
		AFortGameModeAthena* GameModeAthena = Cast<AFortGameModeAthena>(Globals::GetGameMode());

		if (GameStateAthena && GameModeAthena && GameStateAthena->MapInfo)
		{
			AFortAthenaMapInfo* MapInfo = GameStateAthena->MapInfo;

			float LlamaQuantityMin = MapInfo->LlamaQuantityMin.GetValueAtLevel(0); // 3
			float LlamaQuantityMax = MapInfo->LlamaQuantityMax.GetValueAtLevel(0); // 3

			int32 LlamaQuantityToSpawn = UKismetMathLibrary::RandomIntegerInRange(LlamaQuantityMin, LlamaQuantityMax);

			float SupplyDropMinPlacementHeight = MapInfo->SupplyDropMinPlacementHeight.GetValueAtLevel(0);
			float SupplyDropMaxPlacementHeight = MapInfo->SupplyDropMaxPlacementHeight.GetValueAtLevel(0);

			float SafeZoneStartingRadius = MapInfo->SafeZoneStartingRadius.GetValueAtLevel(0);

			FVector SafeZoneLocation = GameModeAthena->SafeZoneLocations[0];
			SafeZoneLocation.Z = 15000;

			for (int32 i = 0; i < LlamaQuantityToSpawn; i++)
			{
				FVector SpawnLocation = FVector(0, 0, 0);
				MapInfo->PickSupplyDropLocation(&SpawnLocation, &SafeZoneLocation, SafeZoneStartingRadius);

				if (SpawnLocation.IsZero())
					continue;

				FRotator SpawnRotation = FRotator(0, 0, 0);
				SpawnRotation.Yaw = (float)rand() * 0.010986663f;

				MapInfo->SpawnSupplyDrop(&SpawnLocation, &SpawnRotation, MapInfo->LlamaClass, SupplyDropMaxPlacementHeight, SupplyDropMinPlacementHeight);
			}
		}
	}

	void InitializeConsumableBGAs()
	{
		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(Globals::GetGameState());

		if (GameStateAthena)
		{
			UBlueprintGeneratedClass* GameplayActorConsumableClass = StaticLoadObject<UBlueprintGeneratedClass>(L"/Game/Athena/BuildingActors/ConsumableBGAs/Spawner/BP_BGACSpawner.BP_BGACSpawner_C");

			TArray<AActor*> Actors;
			UGameplayStatics::GetAllActorsOfClass(GameStateAthena, GameplayActorConsumableClass, &Actors);

			for (int32 i = 0; i < Actors.Num(); i++)
			{
				ABGAConsumableSpawner* ConsumableSpawner = Cast<ABGAConsumableSpawner>(Actors[i]);
				if (!ConsumableSpawner) continue;

				int32 LootLevel = UFortKismetLibrary::GetLootLevel(GameStateAthena);

				TArray<FFortItemEntry> LootToDrops;
				UFortKismetLibrary::PickLootDrops(GameStateAthena, &LootToDrops, ConsumableSpawner->SpawnLootTierGroup, LootLevel, -1);

				FVector SpawnerLocation = ConsumableSpawner->K2_GetActorLocation();

				for (int32 j = 0; j < LootToDrops.Num(); j++)
				{
					FFortItemEntry LootToDrop = LootToDrops[j];

					UBGAConsumableWrapperItemDefinition* ConsumableWrapperItemDefinition = Cast<UBGAConsumableWrapperItemDefinition>(LootToDrop.ItemDefinition);
					if (!ConsumableWrapperItemDefinition) continue;

					ABuildingGameplayActorConsumable* GameplayActorConsumable = SpawnGameplayActorConsumable(ConsumableSpawner, ConsumableWrapperItemDefinition);

					FVector ConsumableLocation = GameplayActorConsumable->K2_GetActorLocation();

					FN_LOG(LogFunctions, Debug, L"[%i/%i] - GameplayActorConsumable: %s, ConsumableLocation: [X: %.2f, Y: %.2f, Z: %.2f]",
						(j + 1), LootToDrops.Num(), GameplayActorConsumable->GetFullName().c_str(), ConsumableLocation.X, ConsumableLocation.Y, ConsumableLocation.Z);

					ConsumableSpawner->ConsumablesToSpawn.Add(LootToDrop);
				}
			}
		}
	}

	void SetPlaylistData(AFortGameModeAthena* GameModeAthena, UFortPlaylistAthena* PlaylistAthena)
	{
		if (!GameModeAthena || !PlaylistAthena)
			return;

		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(GameModeAthena->GameState);

		if (GameStateAthena)
		{
			GameModeAthena->SetCurrentPlaylistId(PlaylistAthena->PlaylistId);

			GameStateAthena->CurrentPlaylistData = PlaylistAthena;
			GameStateAthena->OnRep_CurrentPlaylistData();

			GameStateAthena->AirCraftBehavior = PlaylistAthena->AirCraftBehavior;
			GameStateAthena->bIsLargeTeamGame = PlaylistAthena->bIsLargeTeamGame;
			GameStateAthena->TeamCount = PlaylistAthena->MaxTeamCount;
			GameStateAthena->TeamSize = PlaylistAthena->MaxTeamSize;

			UFortZoneTheme* ZoneTheme = GameStateAthena->ZoneTheme;

			if (ZoneTheme)
			{
				ZoneTheme->PlaylistId = PlaylistAthena->PlaylistId;
				ZoneTheme->TeamSize = PlaylistAthena->MaxTeamSize;
				ZoneTheme->TeamCount = PlaylistAthena->MaxTeamCount;
				ZoneTheme->MaxPartySize = PlaylistAthena->MaxSocialPartySize;
				ZoneTheme->MaxPlayers = PlaylistAthena->MaxPlayers;
			}

			GameModeAthena->GameContextTags.GameplayTags.Clear();

			GameModeAthena->AISettings = PlaylistAthena->AISettings;
			GameModeAthena->WarmupRequiredPlayerCount = 1;

			AFortGameSession* GameSession = GameModeAthena->FortGameSession;

			if (GameSession)
			{
				GameSession->MaxPlayers = 100;//PlaylistAthena->MaxPlayers;
				GameSession->MaxPartySize = PlaylistAthena->MaxSocialPartySize;

				GameSession->SessionName = UKismetStringLibrary::Conv_StringToName(L"Ares-5.41-Session");
			}
		}
	}

	bool HasGameplayTags(TArray<FGameplayTag> GameplayTags, FName TagNameRequired)
	{
		const FString& TagNameRequiredString = UKismetStringLibrary::Conv_NameToString(TagNameRequired);
		const FString& TagNameRequiredLower = UKismetStringLibrary::ToLower(TagNameRequiredString);

		for (int32 j = 0; j < GameplayTags.Num(); j++)
		{
			FGameplayTag GameplayTag = GameplayTags[j];

			FName TagName = GameplayTag.TagName;
			if (!TagName.IsValid()) continue;

			const FString& TagNameString = UKismetStringLibrary::Conv_NameToString(TagName);
			const FString& TagNameLower = UKismetStringLibrary::ToLower(TagNameString);

			if (TagNameLower == TagNameRequiredLower)
				return true;
		}

		return false;
	}

	TArray<UFortItemDefinition*> PickOnlyAthena(TArray<UFortItemDefinition*> AllItems)
	{
		static TArray<UFortItemDefinition*> AllAthenaItems;

		if (AllAthenaItems.Num() > 0)
			return AllAthenaItems;

		for (int32 i = 0; i < AllItems.Num(); i++)
		{
			UFortItemDefinition* ItemDefinition = AllItems[i];

			if (!ItemDefinition)
				continue;

			const FString& PathName = UKismetSystemLibrary::GetPathName(ItemDefinition);

			if (!PathName.ToString().contains("/Game/Athena/Items"))
				continue;

			AllAthenaItems.Add(ItemDefinition);
		}

		return AllAthenaItems;
	}

	TArray<UFortItemDefinition*> GetAllItems(bool bOnlyAthena = false)
	{
		static TArray<UFortItemDefinition*> AllItems;

		if (AllItems.Num() > 0)
			return bOnlyAthena ? PickOnlyAthena(AllItems) : AllItems;

		for (int32 i = 0; i < UObject::GObjects->Num(); i++)
		{
			UObject* GObject = UObject::GObjects->GetByIndex(i);

			if (!GObject)
				continue;

			if (GObject->IsA(UFortItemDefinition::StaticClass()))
			{
				UFortItemDefinition* ItemDefinition = Cast<UFortItemDefinition>(GObject);
				if (!ItemDefinition) continue;

				AllItems.Add(ItemDefinition);
			}
		}

		return bOnlyAthena ? PickOnlyAthena(AllItems) : AllItems;
	}

	TArray<UFortWorldItemDefinition*> GetAllItemsWithClass(bool bOnlyAthena, UClass* Class)
	{
		TArray<UFortItemDefinition*> AllItems = GetAllItems(bOnlyAthena);
		TArray<UFortWorldItemDefinition*> AllItemsWithClass;

		for (int32 i = 0; i < AllItems.Num(); i++)
		{
			UFortItemDefinition* ItemDefinition = AllItems[i];

			if (!ItemDefinition)
				continue;

			if (ItemDefinition->IsA(Class))
			{
				UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(ItemDefinition);
				if (!WorldItemDefinition) continue;

				AllItemsWithClass.Add(WorldItemDefinition);
			}
		}

		return AllItemsWithClass;
	}

	TArray<UFortWeaponItemDefinition*> GetAllItemsWithTag(const FName& TagNameRequired, TArray<UFortWorldItemDefinition*> BlackListWorldItemDefinitions, TArray<EFortRarity> BlackListRaritys, TArray<EFortItemType> BlackListItemTypes)
	{
		TArray<UFortItemDefinition*> AllItems = GetAllItems(true);
		TArray<UFortWeaponItemDefinition*> AllItemsWithTag;

		if (!TagNameRequired.IsValid())
			return AllItemsWithTag;

		for (int32 i = 0; i < AllItems.Num(); i++)
		{
			UFortWeaponItemDefinition* WeaponRangedItemDefinition = Cast<UFortWeaponItemDefinition>(AllItems[i]);
			if (!WeaponRangedItemDefinition) continue;

			bool bBlacklistItem = false;
			for (int32 j = 0; j < BlackListWorldItemDefinitions.Num(); j++)
			{
				UFortWorldItemDefinition* BlackListWorldItemDefinition = BlackListWorldItemDefinitions[j];
				if (!BlackListWorldItemDefinition) continue;

				if (BlackListWorldItemDefinition == WeaponRangedItemDefinition)
				{
					bBlacklistItem = true;
					break;
				}
			}

			if (bBlacklistItem)
				continue;

			bool bBlackListRariry = false;
			for (int32 j = 0; j < BlackListRaritys.Num(); j++)
			{
				EFortRarity BlackListRarity = BlackListRaritys[j];

				if (BlackListRarity == WeaponRangedItemDefinition->Rarity)
				{
					bBlackListRariry = true;
					break;
				}
			}

			if (bBlackListRariry)
				continue;

			bool bBlackListItemType = false;
			for (int32 j = 0; j < BlackListItemTypes.Num(); j++)
			{
				EFortItemType BlackListItemType = BlackListItemTypes[j];

				if (BlackListItemType == WeaponRangedItemDefinition->ItemType)
				{
					bBlackListItemType = true;
					break;
				}
			}

			if (bBlackListItemType)
				continue;

			TArray<FGameplayTag> GameplayTags = WeaponRangedItemDefinition->GameplayTags.GameplayTags;

			const FString& TagNameRequiredString = UKismetStringLibrary::Conv_NameToString(TagNameRequired);
			const FString& TagNameRequiredLower = UKismetStringLibrary::ToLower(TagNameRequiredString);

			bool bFindTagName = false;
			for (int32 j = 0; j < GameplayTags.Num(); j++)
			{
				FGameplayTag GameplayTag = GameplayTags[j];

				FName TagName = GameplayTag.TagName;
				if (!TagName.IsValid()) continue;

				const FString& TagNameString = UKismetStringLibrary::Conv_NameToString(TagName);
				const FString& TagNameLower = UKismetStringLibrary::ToLower(TagNameString);

				if (TagNameLower == TagNameRequiredLower)
				{
					bFindTagName = true;
					break;
				}
			}

			if (!bFindTagName)
				continue;

			AllItemsWithTag.Add(WeaponRangedItemDefinition);
		}

		return AllItemsWithTag;
	}

	UFortWeaponItemDefinition* ChooseRandomItemWithFilter(const FName& TagNameRequired, TArray<UFortWorldItemDefinition*> BlackListWorldItemDefinitions = {}, TArray<EFortRarity> BlackListRarity = {}, TArray<EFortItemType> BlackListItemTypes = {})
	{
		TArray<UFortWeaponItemDefinition*> AllItemsWithTag = GetAllItemsWithTag(TagNameRequired, BlackListWorldItemDefinitions, BlackListRarity, BlackListItemTypes);
		return AllItemsWithTag[std::rand() % AllItemsWithTag.Num()];
	}

#ifdef SIPHON
	void ApplySiphonEffect(AFortPlayerState* PlayerState)
	{
		if (PlayerState)
		{
			UFortAbilitySystemComponent* AbilitySystemComponent = PlayerState->AbilitySystemComponent;

			if (AbilitySystemComponent)
			{
				FGameplayTag GameplayTag = FGameplayTag();
				GameplayTag.TagName = UKismetStringLibrary::Conv_StringToName(L"GameplayCue.Shield.PotionConsumed");

				AbilitySystemComponent->NetMulticast_InvokeGameplayCueAdded(GameplayTag, FPredictionKey(), FGameplayEffectContextHandle());
				AbilitySystemComponent->NetMulticast_InvokeGameplayCueExecuted(GameplayTag, FPredictionKey(), FGameplayEffectContextHandle());
			}
		}
	}

	void GiveSiphonBonus(AFortPlayerController* PlayerController, AFortPawn* Pawn, bool bGiveBuildingResource = true, bool bHealPlayer = true)
	{
		if (PlayerController)
		{
			if (bGiveBuildingResource)
			{
				UFortKismetLibrary::K2_GiveBuildingResource(PlayerController, EFortResourceType::Wood, 50);
				UFortKismetLibrary::K2_GiveBuildingResource(PlayerController, EFortResourceType::Stone, 50);
				UFortKismetLibrary::K2_GiveBuildingResource(PlayerController, EFortResourceType::Metal, 50);
			}

			if (bHealPlayer && Pawn)
			{
				float MaxHealth = Pawn->GetMaxHealth();
				float MaxShield = Pawn->GetMaxShield();

				float Health = Pawn->GetHealth();
				float Shield = Pawn->GetShield();

				float SiphonAmount = 50.0f;
				float RemainingSiphonAmount = SiphonAmount;

				if (Health < MaxHealth)
				{
					float NewHealth = std::clamp(Health + SiphonAmount, 0.0f, MaxHealth);

					Pawn->SetHealth(NewHealth);

					RemainingSiphonAmount -= (NewHealth - Health);
				}

				if (RemainingSiphonAmount > 0.0f)
				{
					float NewShield = std::clamp(Shield + RemainingSiphonAmount, 0.0f, MaxShield);

					Pawn->SetShield(NewShield);
				}
			}

			AFortPlayerState* PlayerState = Cast<AFortPlayerState>(PlayerController->PlayerState);

			if (PlayerState)
			{
				ApplySiphonEffect(PlayerState);
			}
		}
	}
#endif // SIPHON

#ifdef LATEGAME
	void GiveLateGameInventory(AFortPlayerController* PlayerController)
	{
		UFortKismetLibrary::K2_GiveBuildingResource(PlayerController, EFortResourceType::Wood, 500);
		UFortKismetLibrary::K2_GiveBuildingResource(PlayerController, EFortResourceType::Stone, 300);
		UFortKismetLibrary::K2_GiveBuildingResource(PlayerController, EFortResourceType::Metal, 150);

		// Give All Ammos
		{
			TArray<UFortWorldItemDefinition*> AllAmmoItems = Functions::GetAllItemsWithClass(true, UFortAmmoItemDefinition::StaticClass());

			for (int32 i = 0; i < AllAmmoItems.Num(); i++)
			{
				UFortAmmoItemDefinition* AmmoItemDefinition = Cast<UFortAmmoItemDefinition>(AllAmmoItems[i]);
				if (!AmmoItemDefinition) continue;

				if (!AmmoItemDefinition->bCanBeDropped)
					continue;

				UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, AmmoItemDefinition, ((AmmoItemDefinition->MaxStackSize / 4) + 1), false);
			}
		}

		// Assault Weapon
		{
			const FName& TagNameRequired = UKismetStringLibrary::Conv_StringToName(L"Weapon.Ranged.Assault");

			TArray<EFortRarity> BlackListRarity;
			BlackListRarity.Add(EFortRarity::Handmade);
			BlackListRarity.Add(EFortRarity::Ordinary);

			UFortWeaponItemDefinition* RandomItemWithTag = Functions::ChooseRandomItemWithFilter(TagNameRequired, {}, BlackListRarity);

			if (RandomItemWithTag)
				UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, RandomItemWithTag, RandomItemWithTag->MaxStackSize, false);

			if (BlackListRarity.IsValid())
				BlackListRarity.Free();
		}

		// Shotgun Weapon
		{
			const FName& TagNameRequired = UKismetStringLibrary::Conv_StringToName(L"Weapon.Ranged.Shotgun");

			TArray<EFortRarity> BlackListRarity;
			BlackListRarity.Add(EFortRarity::Handmade);
			BlackListRarity.Add(EFortRarity::Ordinary);

			UFortWeaponItemDefinition* RandomItemWithTag = Functions::ChooseRandomItemWithFilter(TagNameRequired, {}, BlackListRarity);

			if (RandomItemWithTag)
				UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, RandomItemWithTag, RandomItemWithTag->MaxStackSize, false);

			if (BlackListRarity.IsValid())
				BlackListRarity.Free();
		}

		// Smg Weapon
		{
			const FName& TagNameRequired = UKismetStringLibrary::Conv_StringToName(L"Weapon.Ranged.Smg");

			TArray<EFortRarity> BlackListRarity;
			BlackListRarity.Add(EFortRarity::Handmade);
			BlackListRarity.Add(EFortRarity::Ordinary);

			UFortWeaponItemDefinition* RandomItemWithTag = Functions::ChooseRandomItemWithFilter(TagNameRequired, {}, BlackListRarity);

			if (RandomItemWithTag)
				UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, RandomItemWithTag, RandomItemWithTag->MaxStackSize, false);

			if (BlackListRarity.IsValid())
				BlackListRarity.Free();
		}

		// Heal Weapon
		{
			const FName& TagNameRequired = UKismetStringLibrary::Conv_StringToName(L"Athena.ItemAction.Consume");

			TArray<EFortRarity> BlackListRarity;
			BlackListRarity.Add(EFortRarity::Quality);
			BlackListRarity.Add(EFortRarity::Fine);

			UFortWeaponItemDefinition* RandomItemWithTag = Functions::ChooseRandomItemWithFilter(TagNameRequired, {}, BlackListRarity);

			if (RandomItemWithTag)
				UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, RandomItemWithTag, RandomItemWithTag->MaxStackSize, false);

			if (BlackListRarity.IsValid())
				BlackListRarity.Free();
		}

		// Rota/Sniper Weapon
		{
			const FName& TagNameRequired = UKismetStringLibrary::Conv_StringToName(L"Weapon.Ranged.Sniper"); // UKismetMathLibrary::RandomBool() ? UKismetStringLibrary::Conv_StringToName(L"Weapon.Ranged.Sniper") : UKismetStringLibrary::Conv_StringToName(L"Weapon.Ranged.Heavy.Grenade");
			UFortWeaponItemDefinition* RandomItemWithTag = Functions::ChooseRandomItemWithFilter(TagNameRequired);

			if (RandomItemWithTag)
				UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, RandomItemWithTag, RandomItemWithTag->MaxStackSize, false);
		}

		// Trap
		{
			const FName& TagNameRequired = UKismetStringLibrary::Conv_StringToName(L"Bacchus.Place.Trap.Damage");
			UFortWeaponItemDefinition* RandomItemWithTag = Functions::ChooseRandomItemWithFilter(TagNameRequired);

			if (RandomItemWithTag)
				UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, RandomItemWithTag, 3, false);
		}
	}

	void StartSafeZone(AFortGameModeAthena* GameModeAthena)
	{
		if (!GameModeAthena)
			return;

		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(GameModeAthena->GameState);

		if (GameStateAthena)
		{
			// 7FF66F254FC0
			bool (*StartSafeZonesPhase)(AFortGameModeAthena* GameModeAthena, bool a2) = decltype(StartSafeZonesPhase)(0xC04FC0 + uintptr_t(GetModuleHandle(0)));

			// 7FF66F254C70
			bool (*sub_7FF66F254C70)(AFortGameModeAthena* GameModeAthena, bool a2, bool a3) = decltype(sub_7FF66F254C70)(0xC04C70 + uintptr_t(GetModuleHandle(0)));
			sub_7FF66F254C70(GameModeAthena, true, true);

			GameStateAthena->SafeZonesStartTime = 0.0f;
		}
	}

	void InitLateGameSafeZone(AFortGameModeAthena* GameModeAthena)
	{
		if (!GameModeAthena)
			return;

		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(GameModeAthena->GameState);

		if (GameStateAthena)
		{
			StartSafeZone(GameModeAthena);
		}
	}
#endif // LATEGAME

	void InitFunctions()
	{
		FN_LOG(LogInit, Log, L"InitFunctions Success!");
	}
}