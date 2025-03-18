#pragma once

namespace FortKismetLibrary
{
	/* ------------------------------------- UFortKismetLibraryOG ------------------------------------ */



	/* -------------------------------------- UFortKismetLibrary ------------------------------------- */

	AFortAIDirector* GetAIDirector(UFortKismetLibrary* KismetLibrary, FFrame& Stack, AFortAIDirector** Ret)
	{
		UObject* WorldContextObject = nullptr;

		Stack.StepCompiledIn(&WorldContextObject);

		Stack.Code += Stack.Code != nullptr;

		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

		if (World)
		{
			AFortGameModeZone* GameModeZone = Cast<AFortGameModeZone>(World->AuthorityGameMode);

			if (GameModeZone)
			{
				*Ret = GameModeZone->AIDirector;
				return *Ret;
			}
		}

		*Ret = nullptr;
		return *Ret;
	}

	AFortAIGoalManager* GetAIGoalManager(UFortKismetLibrary* KismetLibrary, FFrame& Stack, AFortAIGoalManager** Ret)
	{
		UObject* WorldContextObject = nullptr;

		Stack.StepCompiledIn(&WorldContextObject);

		Stack.Code += Stack.Code != nullptr;

		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

		if (World)
		{
			AFortGameModeZone* GameModeZone = Cast<AFortGameModeZone>(World->AuthorityGameMode);

			if (GameModeZone)
			{
				*Ret = GameModeZone->AIGoalManager;
				return *Ret;
			}
		}

		*Ret = nullptr;
		return *Ret;
	}

	/*
	 * Rewrite UFortKismetLibrary::PickLootDrops (1.1)
	 *
	 * - https://imgur.com/6xCTrE9
	 */
	bool PickLootDrops(UFortKismetLibrary* KismetLibrary, FFrame& Stack, bool* Ret)
	{
		UObject* WorldContextObject = nullptr;
		TArray<FFortItemEntry> OutLootToDrop = {};
		FName TierGroupName = FName(0);
		int32 WorldLevel = -1;
		int32 ForcedLootTier = -1;

		Stack.StepCompiledIn(&WorldContextObject);
		TArray<FFortItemEntry>& LootToDrops = Stack.StepCompiledInRef<TArray<FFortItemEntry>>(&OutLootToDrop);
		Stack.StepCompiledIn(&TierGroupName);
		Stack.StepCompiledIn(&WorldLevel);
		Stack.StepCompiledIn(&ForcedLootTier);

		Stack.Code += Stack.Code != nullptr;

		FFortItemEntry::FreeItemEntries(&OutLootToDrop);

		FName LootTierKey = FName(0);
		int32 LootTier = -1;

		bool bResult = Loots::PickLootTierKeyAndLootTierFromTierGroup(&LootTierKey, &LootTier, TierGroupName, WorldLevel, 0, ForcedLootTier, FGameplayTagContainer());

		if (bResult)
		{
			*Ret = Loots::PickLootDrops(&LootToDrops, WorldLevel, LootTierKey, 0, 0, FGameplayTagContainer(), false, false);
			return *Ret;
		}

		*Ret = false;
		return *Ret;
	}

	AFortPickup* K2_SpawnPickupInWorld(UFortKismetLibrary* KismetLibrary, FFrame& Stack, AFortPickup** Ret)
	{
		UObject* WorldContextObject = nullptr;
		UFortWorldItemDefinition* ItemDefinition = nullptr;
		int32 NumberToSpawn = 1;
		FVector Position = FVector();
		FVector Direction = FVector();
		int32 OverrideMaxStackCount = 0;
		bool bToss = true;
		bool bRandomRotation = true;
		bool bBlockedFromAutoPickup = false;

		Stack.StepCompiledIn(&WorldContextObject);
		Stack.StepCompiledIn(&ItemDefinition);
		Stack.StepCompiledIn(&NumberToSpawn);
		Stack.StepCompiledIn(&Position);
		Stack.StepCompiledIn(&Direction);
		Stack.StepCompiledIn(&OverrideMaxStackCount);
		Stack.StepCompiledIn(&bToss);
		Stack.StepCompiledIn(&bRandomRotation);
		Stack.StepCompiledIn(&bBlockedFromAutoPickup);

		Stack.Code += Stack.Code != nullptr;

		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

		if (!World || !ItemDefinition || (NumberToSpawn < 1))
		{
			*Ret = nullptr;
			return *Ret;
		}

		FFortItemEntry ItemEntry;
		Inventory::MakeItemEntry(&ItemEntry, ItemDefinition, NumberToSpawn, -1, -1, -1.0f);

		FFortCreatePickupData CreatePickupData = FFortCreatePickupData();
		CreatePickupData.World = World;
		CreatePickupData.ItemEntry = &ItemEntry;
		CreatePickupData.SpawnLocation = &Position;
		CreatePickupData.SpawnRotation = nullptr;
		CreatePickupData.PlayerController = nullptr;
		CreatePickupData.OverrideClass = nullptr;
		CreatePickupData.NullptrIdk = nullptr;
		CreatePickupData.bRandomRotation = bRandomRotation;
		CreatePickupData.PickupSourceTypeFlags = 0;

		AFortPickup* Pickup = AFortPickup::CreatePickupFromData(&CreatePickupData);

		if (Pickup)
		{
			Pickup->TossPickup(Direction, nullptr, OverrideMaxStackCount, bToss);
			Pickup->bWeaponsCanBeAutoPickups = !bBlockedFromAutoPickup;
		}

		ItemEntry.FreeItemEntry();

		*Ret = Pickup;
		return *Ret;
	}

	void GiveItemToInventoryOwner(UFortKismetLibrary* KismetLibrary, FFrame& Stack, void* Ret)
	{
		TScriptInterface<class IFortInventoryOwnerInterface> InventoryOwner;
		class UFortWorldItemDefinition* ItemDefinition = nullptr;
		int32 NumberToGive = 1;
		bool bNotifyPlayer = true;

		Stack.StepCompiledIn(&InventoryOwner);
		Stack.StepCompiledIn(&ItemDefinition);
		Stack.StepCompiledIn(&NumberToGive);
		Stack.StepCompiledIn(&bNotifyPlayer);

		Stack.Code += Stack.Code != nullptr;

		AFortPlayerController* PlayerController = AFortPlayerController::GetPlayerControllerFromInventoryOwner(InventoryOwner.GetInterface());

		if (!PlayerController || !ItemDefinition)
			return;

		UWorld* World = GEngine->GetWorldFromContextObject(PlayerController, EGetWorldErrorMode::LogAndReturnNull);

		if (!World)
			return;

		FFortItemEntry ItemEntry;
		Inventory::MakeItemEntry(&ItemEntry, ItemDefinition, NumberToGive, -1, -1, -1.0f);

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (bNotifyPlayer && PlayerPawn)
		{
			const FVector& SpawnLocation = PlayerPawn->K2_GetActorLocation();

			int32 MaxStackSize = ItemDefinition->MaxStackSize;
			int32 RemainingToGive = NumberToGive;
			int32 PickupIndex = 0;

			while (RemainingToGive > 0)
			{
				int32 StackSize = UKismetMathLibrary::Min(RemainingToGive, MaxStackSize);
				Inventory::MakeItemEntry(&ItemEntry, ItemDefinition, StackSize, -1, -1, -1.0f);
				AFortPickup* Pickup = AFortPickup::CreatePickup(World, &ItemEntry, &SpawnLocation);

				if (Pickup)
				{
					const FVector& StartDirection = FVector({ 0, 0, 0 });
					float FlyTime = Globals::GenFlyTime();
					Pickup->SetPickupTarget(PlayerPawn, (FlyTime + PickupIndex * 0.30000001192092896f), StartDirection);
				}

				RemainingToGive -= StackSize;
				PickupIndex++;
			}
		}
		else
		{
			Inventory::SetStateValue(&ItemEntry, EFortItemEntryState::ShouldShowItemToast, 1);
			Inventory::AddInventoryItem(PlayerController, ItemEntry);
		}

		ItemEntry.FreeItemEntry();
	}

	void K2_GiveBuildingResource(UFortKismetLibrary* KismetLibrary, FFrame& Stack, void* Ret)
	{
		AFortPlayerController* Controller = nullptr;
		EFortResourceType ResourceType = EFortResourceType::Wood;
		int32 ResourceAmount = 1;

		Stack.StepCompiledIn(&Controller);
		Stack.StepCompiledIn(&ResourceType);
		Stack.StepCompiledIn(&ResourceAmount);

		Stack.Code += Stack.Code != nullptr;

		UFortResourceItemDefinition* ResourceItemDefinition = UFortKismetLibrary::K2_GetResourceItemDefinition(ResourceType);

		if (!Controller || !ResourceItemDefinition)
			return;

		UFortKismetLibrary::K2_GiveItemToPlayer(Controller, ResourceItemDefinition, ResourceAmount, false);
	}

	void K2_GiveItemToAllPlayers(UFortKismetLibrary* KismetLibrary, FFrame& Stack, void* Ret)
	{
		UObject* WorldContextObject = nullptr;
		UFortWorldItemDefinition* ItemDefinition = nullptr;
		int32 NumberToGive = 1;
		bool bNotifyPlayer = true;

		Stack.StepCompiledIn(&WorldContextObject);
		Stack.StepCompiledIn(&ItemDefinition);
		Stack.StepCompiledIn(&NumberToGive);
		Stack.StepCompiledIn(&bNotifyPlayer);

		Stack.Code += Stack.Code != nullptr;

		TArray<AFortPlayerController*> AllFortPlayerControllers = UFortKismetLibrary::GetAllFortPlayerControllers(WorldContextObject, true, false);

		for (int32 i = 0; i < AllFortPlayerControllers.Num(); i++)
		{
			AFortPlayerController* PlayerController = AllFortPlayerControllers[i];
			if (!PlayerController) return;

			UFortKismetLibrary::K2_GiveItemToPlayer(PlayerController, ItemDefinition, NumberToGive, bNotifyPlayer);
		}
	}

	void K2_GiveItemToPlayer(UFortKismetLibrary* KismetLibrary, FFrame& Stack, void* Ret)
	{
		AFortPlayerController* PlayerController = nullptr;
		UFortWorldItemDefinition* ItemDefinition = nullptr;
		int32 NumberToGive = 1;
		bool bNotifyPlayer = true;

		Stack.StepCompiledIn(&PlayerController);
		Stack.StepCompiledIn(&ItemDefinition);
		Stack.StepCompiledIn(&NumberToGive);
		Stack.StepCompiledIn(&bNotifyPlayer);	

		Stack.Code += Stack.Code != nullptr;

		if (!PlayerController || !ItemDefinition)
			return;

		UWorld* World = GEngine->GetWorldFromContextObject(PlayerController, EGetWorldErrorMode::LogAndReturnNull);

		if (!World)
			return;

		FFortItemEntry ItemEntry;
		Inventory::MakeItemEntry(&ItemEntry, ItemDefinition, NumberToGive, -1, -1, -1.0f);

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (bNotifyPlayer && PlayerPawn)
		{
			const FVector& SpawnLocation = PlayerPawn->K2_GetActorLocation();

			int32 MaxStackSize = ItemDefinition->MaxStackSize;
			int32 RemainingToGive = NumberToGive;
			int32 PickupIndex = 0;

			while (RemainingToGive > 0)
			{
				int32 StackSize = UKismetMathLibrary::Min(RemainingToGive, MaxStackSize);
				Inventory::MakeItemEntry(&ItemEntry, ItemDefinition, StackSize, -1, -1, -1.0f);
				AFortPickup* Pickup = AFortPickup::CreatePickup(World, &ItemEntry, &SpawnLocation);

				if (Pickup)
				{
					const FVector& StartDirection = FVector({ 0, 0, 0 });
					float FlyTime = Globals::GenFlyTime();
					Pickup->SetPickupTarget(PlayerPawn, (FlyTime + PickupIndex * 0.30000001192092896f), StartDirection);
				}

				RemainingToGive -= StackSize;
				PickupIndex++;
			}
		}
		else
		{
			Inventory::SetStateValue(&ItemEntry, EFortItemEntryState::ShouldShowItemToast, 1);
			Inventory::AddInventoryItem(PlayerController, ItemEntry);
		}

		ItemEntry.FreeItemEntry();
	}

	void K2_RemoveItemFromAllPlayers(UFortKismetLibrary* KismetLibrary, FFrame& Stack, void* Ret)
	{
		UObject* WorldContextObject = nullptr;
		UFortWorldItemDefinition* ItemDefinition = nullptr;
		int32 AmountToRemove = 1;

		Stack.StepCompiledIn(&WorldContextObject);
		Stack.StepCompiledIn(&ItemDefinition);
		Stack.StepCompiledIn(&AmountToRemove);

		Stack.Code += Stack.Code != nullptr;

		TArray<AFortPlayerController*> AllFortPlayerControllers = UFortKismetLibrary::GetAllFortPlayerControllers(WorldContextObject, true, false);

		for (int32 i = 0; i < AllFortPlayerControllers.Num(); i++)
		{
			AFortPlayerController* PlayerController = AllFortPlayerControllers[i];
			if (!PlayerController) return;

			UFortKismetLibrary::K2_RemoveItemFromPlayer(PlayerController, ItemDefinition, AmountToRemove, false);
		}
	}

	int32 K2_RemoveItemFromPlayer(AFortPlayerController* PlayerController, UFortWorldItemDefinition* ItemDefinition, int32 AmountToRemove, bool bForceRemoval)
	{
		if (!PlayerController || !ItemDefinition)
			return 0;

		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_FindExistingItemForDefinition(ItemDefinition, false));

		if (WorldItem)
		{
			int32 ItemCount = WorldItem->ItemEntry.Count;
			int32 FinalCount = ItemCount - AmountToRemove;

			if (FinalCount < 0)
				FinalCount = 0;

			PlayerController->RemoveInventoryItem(WorldItem->ItemEntry.ItemGuid, AmountToRemove, false, bForceRemoval);

			return FinalCount;
		}

		return 0;
	}
	int32 K2_RemoveItemFromPlayerByGuid(AFortPlayerController* PlayerController, const FGuid& ItemGuid, int32 AmountToRemove, bool bForceRemoval)
	{
		if (!PlayerController)
			return 0;

		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(ItemGuid));

		if (WorldItem)
		{
			int32 ItemCount = WorldItem->ItemEntry.Count;
			int32 FinalCount = ItemCount - AmountToRemove;

			if (FinalCount < 0)
				FinalCount = 0;

			PlayerController->RemoveInventoryItem(WorldItem->ItemEntry.ItemGuid, AmountToRemove, false, bForceRemoval);

			return FinalCount;
		}

		return 0;
	}

	void InitFortKismetLibrary()
	{
		UFortKismetLibrary* FortKismetLibraryDefault = UFortKismetLibrary::GetDefaultObj();
		UClass* FortKismetLibraryClass = UFortKismetLibrary::StaticClass();

		/* -------------------------------------- UFortKismetLibrary ------------------------------------- */

		UFunction* GetAIDirectorFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "GetAIDirector");
		MinHook::HookFunctionExec(GetAIDirectorFunc, GetAIDirector, nullptr);

		UFunction* GetAIGoalManagerFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "GetAIGoalManager");
		MinHook::HookFunctionExec(GetAIGoalManagerFunc, GetAIGoalManager, nullptr);

		UFunction* PickLootDropsFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "PickLootDrops");
		MinHook::HookFunctionExec(PickLootDropsFunc, PickLootDrops, nullptr);

		UFunction* K2_SpawnPickupInWorldFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "K2_SpawnPickupInWorld");
		MinHook::HookFunctionExec(K2_SpawnPickupInWorldFunc, K2_SpawnPickupInWorld, nullptr);

		UFunction* GiveItemToInventoryOwnerFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "GiveItemToInventoryOwner");
		MinHook::HookFunctionExec(GiveItemToInventoryOwnerFunc, GiveItemToInventoryOwner, nullptr);

		UFunction* K2_GiveBuildingResourceFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "K2_GiveBuildingResource");
		MinHook::HookFunctionExec(K2_GiveBuildingResourceFunc, K2_GiveBuildingResource, nullptr);

		UFunction* K2_GiveItemToAllPlayersFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "K2_GiveItemToAllPlayers");
		MinHook::HookFunctionExec(K2_GiveItemToAllPlayersFunc, K2_GiveItemToAllPlayers, nullptr);

		UFunction* K2_GiveItemToPlayerFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "K2_GiveItemToPlayer");
		MinHook::HookFunctionExec(K2_GiveItemToPlayerFunc, K2_GiveItemToPlayer, nullptr);

		UFunction* K2_RemoveItemFromAllPlayersFunc = FortKismetLibraryClass->GetFunction("FortKismetLibrary", "K2_RemoveItemFromAllPlayers");
		MinHook::HookFunctionExec(K2_RemoveItemFromAllPlayersFunc, K2_RemoveItemFromAllPlayers, nullptr);

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0xEBE880), K2_RemoveItemFromPlayer, nullptr);
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0xEBE880));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0xEBE8A0), K2_RemoveItemFromPlayerByGuid, nullptr);
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0xEBE8A0));

		FN_LOG(LogInit, Log, L"InitFortKismetLibrary Success!");
	}
}