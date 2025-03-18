#pragma once

namespace Inventory
{
	bool (*FindItemInstancesFromDefinition)(void* InventoryOwner, UFortItemDefinition* ItemDefinition, TArray<UFortItem*>& ItemArray);
	FFortItemEntry* (*CreateItemEntry)(FFortItemEntry* ItemEntry);
	FFortItemEntry* (*CreateDefaultItemEntry)(FFortItemEntry* ItemEntry, UFortItemDefinition* ItemDefinition, int32 Count, int32 Level);
	FFortItemEntry* (*CopyItemEntry)(FFortItemEntry* PrimaryItemEntry, FFortItemEntry* ItemEntry);
	void (*PickupInitialize)(AFortPickup* Pickup, FFortItemEntry* ItemEntry, TArray<FFortItemEntry*> MultiItemEntries, bool bSplitOnPickup);
	bool (*SetStateValue)(FFortItemEntry* ItemEntry, EFortItemEntryState StateType, int32 IntValue);
	AFortPickup* (*CreateSimplePickup)(UObject* WorldContextObject, FFortItemEntry* ItemEntry, const FVector& SpawnLocation, const FRotator& SpawnRotation);
	AFortPickup* (*CreatePickupFromData)(FFortCreatePickupData* CreatePickupData);
	void (*MarkItemEntryDirty)(AFortInventory* Inventory, FFortItemEntry* ItemEntry);
	void (*AddWorldItem)(AFortInventory* Inventory, UFortWorldItem* WorldItem);
	void (*FreeItemEntry)(FFortItemEntry* ItemEntry);

	// The function is compiled in another function... We have to redo it
	int32 GetItemLevel(const FDataTableCategoryHandle& ItemLevelDataHandle)
	{
		UDataTable* DataTable = ItemLevelDataHandle.DataTable;
		AFortGameState* GameState = Globals::GetGameState();

		if (!DataTable || !GameState)
			return 0;

		if (!ItemLevelDataHandle.ColumnName.IsValid() || !ItemLevelDataHandle.RowContents.IsValid())
			return 0;

		TArray<FFortLootLevelData*> MatchingLootLevelData;

		for (auto& DataPair : DataTable->GetRowMap<FFortLootLevelData>())
		{
			if (DataPair.Second->Category != ItemLevelDataHandle.RowContents)
				continue;

			MatchingLootLevelData.Add(DataPair.Second);
		}

		if (!MatchingLootLevelData.IsValid())
		{
			int32 SelectedIndex = -1;
			int32 HighestLootLevel = 0;

			for (int32 i = 0; i < MatchingLootLevelData.Num(); ++i)
			{
				FFortLootLevelData* CurrentData = MatchingLootLevelData[i];

				if (CurrentData->LootLevel <= GameState->WorldLevel && CurrentData->LootLevel > HighestLootLevel)
				{
					HighestLootLevel = CurrentData->LootLevel;
					SelectedIndex = i;
				}
			}

			if (SelectedIndex != -1)
			{
				FFortLootLevelData* SelectedData = MatchingLootLevelData[SelectedIndex];

				const int32 MinItemLevel = SelectedData->MinItemLevel;
				const int32 MaxItemLevel = SelectedData->MaxItemLevel;

				int32 LevelRange = MaxItemLevel - MinItemLevel;

				if (LevelRange + 1 <= 0)
				{
					LevelRange = 0;
				}
				else
				{
					const int32 RandomValue = (int32)(float)((float)((float)rand() * 0.000030518509) * (float)(LevelRange + 1));

					if (RandomValue <= LevelRange)
						LevelRange = RandomValue;
				}

				return LevelRange + MinItemLevel;
			}
		}

		if (MatchingLootLevelData.Num() > 0)
			MatchingLootLevelData.Free();

		return 0;
	}

	FFortBaseWeaponStats* GetWeaponStats(UFortWeaponItemDefinition* ItemDefinition)
	{
		if (!ItemDefinition)
			return nullptr;

		if (ItemDefinition->IsA(UFortAmmoItemDefinition::StaticClass()) ||
			ItemDefinition->IsA(UFortResourceItemDefinition::StaticClass()) ||
			ItemDefinition->IsA(UFortIngredientItemDefinition::StaticClass()))
			return nullptr;

		FDataTableRowHandle* WeaponStatHandle = &ItemDefinition->WeaponStatHandle;

		if (!WeaponStatHandle)
			return nullptr;

		return Globals::GetDataTableRowFromName<FFortBaseWeaponStats>(WeaponStatHandle->DataTable, WeaponStatHandle->RowName);
	}

	void MakeItemEntry(FFortItemEntry* ItemEntry, UFortItemDefinition* ItemDefinition, int32 Count, int32 Level, int32 LoadedAmmo, float Durability)
	{
		if (!ItemEntry || !ItemDefinition)
			return;

		CreateDefaultItemEntry(ItemEntry, ItemDefinition, Count, Level);

		UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(ItemDefinition);

		if (WorldItemDefinition)
		{
			int32 ItemLevel = GetItemLevel(WorldItemDefinition->LootLevelData);

			ItemEntry->Level = (Level == -1) ? ItemLevel : Level;
			ItemEntry->Durability = (Durability == -1.0f) ? WorldItemDefinition->GetMaxDurability(ItemLevel) : Durability;

			UFortWeaponItemDefinition* WeaponItemDefinition = Cast<UFortWeaponItemDefinition>(WorldItemDefinition);

			if (WeaponItemDefinition)
			{
				FFortBaseWeaponStats* WeaponStats = GetWeaponStats(WeaponItemDefinition);

				ItemEntry->LoadedAmmo = (WeaponStats && LoadedAmmo == -1) ? WeaponStats->ClipSize : LoadedAmmo;
			}
		}
	}

	void UpdateItemEntry(FFortItemEntry* ItemEntry)
	{
		if (ItemEntry->ParentInventory.IsValid())
		{
			AFortInventory* ParentInventory = ItemEntry->ParentInventory.Get();
			MarkItemEntryDirty(ParentInventory, ItemEntry);
		}

		ItemEntry->bIsDirty = true;
	}

	void SetCount(FFortItemEntry* ItemEntry, int32 NewCount)
	{
		if (NewCount < 0)
			NewCount = 0;

		if (NewCount != ItemEntry->Count)
		{
			ItemEntry->Count = NewCount;
			UpdateItemEntry(ItemEntry);
		}
	}

	void SetLoadedAmmo(FFortItemEntry* ItemEntry, int32 NewLoadedAmmo)
	{
		if (NewLoadedAmmo < 0)
			NewLoadedAmmo = 0;

		if (NewLoadedAmmo != ItemEntry->LoadedAmmo)
		{
			ItemEntry->LoadedAmmo = NewLoadedAmmo;
			UpdateItemEntry(ItemEntry);
		}
	}

	void SetDurability(FFortItemEntry* ItemEntry, float NewDurability)
	{
		if (NewDurability != ItemEntry->Durability)
		{
			ItemEntry->Durability = NewDurability;
			UpdateItemEntry(ItemEntry);
		}
	}
	
	int32 RemoveItemCount(FFortItemEntry* ItemEntry, UFortItemDefinition* ItemDefinition, int32 CountToRemove)
	{
		if (ItemEntry->ItemDefinition != ItemDefinition)
			return 0;

		int32 ItemCount = ItemEntry->Count;

		int32 FinalCountToRemove = ItemCount;

		if (CountToRemove <= ItemCount)
			FinalCountToRemove = CountToRemove;

		int32 NewCount = ItemCount - FinalCountToRemove;

		if (NewCount == ItemCount)
			return FinalCountToRemove;

		SetCount(ItemEntry, NewCount);

		return FinalCountToRemove;
	}

	void ModifyCountItem(AFortInventory* Inventory, const FGuid& ItemGuid, int32 NewCount)
	{
		if (!Inventory)
			return;

		for (int32 i = 0; i < Inventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = Inventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &Inventory->Inventory.ItemInstances[i]->ItemEntry;

			if (ItemEntry->ItemGuid == ItemGuid)
			{
				SetCount(ItemEntry, NewCount);
				break;
			}
		}

		// I think that normally you don't need to modify the value here but for me it doesn't work idk
		for (int32 i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry* ReplicatedItemEntry = &Inventory->Inventory.ReplicatedEntries[i];

			if (ReplicatedItemEntry->ItemGuid == ItemGuid)
			{
				ReplicatedItemEntry->Count = NewCount;
				Inventory->Inventory.MarkItemDirty(*ReplicatedItemEntry);
				break;
			}
		}
	}

	void ModifyLoadedAmmoItem(AFortInventory* Inventory, const FGuid& ItemGuid, int32 NewLoadedAmmo)
	{
		if (!Inventory)
			return;

		for (int32 i = 0; i < Inventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = Inventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &Inventory->Inventory.ItemInstances[i]->ItemEntry;

			if (ItemEntry->ItemGuid == ItemGuid)
			{
				SetLoadedAmmo(ItemEntry, NewLoadedAmmo);
				break;
			}
		}

		// I think that normally you don't need to modify the value here but for me it doesn't work idk
		for (int32 i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry* ReplicatedItemEntry = &Inventory->Inventory.ReplicatedEntries[i];

			if (ReplicatedItemEntry->ItemGuid == ItemGuid)
			{
				ReplicatedItemEntry->LoadedAmmo = NewLoadedAmmo;
				Inventory->Inventory.MarkItemDirty(*ReplicatedItemEntry);
				break;
			}
		}
	}

	bool IsInventoryFull(AFortInventory* Inventory)
	{
		if (!Inventory || !Inventory->Owner)
			return false;

		// 7FF66FE971B0
		void* (*GetInterfaceAddress)(UObject* Object, UClass* InterfaceClass) = decltype(GetInterfaceAddress)(0x18471B0 + uintptr_t(GetModuleHandle(0)));
		void* InventoryOwnerInterfaceAddress = GetInterfaceAddress(Inventory->Owner, IFortInventoryOwnerInterface::StaticClass());

		// 7FF66F5C1B60
		int32 (*GetInventoryCapacity)(void* InventoryOwnerInterfaceAddress, EFortInventoryType InventoryType) = decltype(GetInventoryCapacity)(0xF71B60 + uintptr_t(GetModuleHandle(0)));
		int32 InventoryCapacity = GetInventoryCapacity(InventoryOwnerInterfaceAddress, Inventory->InventoryType);

		// 7FF66F5C21C0
		int32 (*GetInventorySize)(void* InventoryOwnerInterfaceAddress, EFortInventoryType InventoryType) = decltype(GetInventorySize)(0xF721C0 + uintptr_t(GetModuleHandle(0)));
		int32 InventorySize = GetInventorySize(InventoryOwnerInterfaceAddress, Inventory->InventoryType);

		return (InventorySize >= InventoryCapacity);
	}

	UFortWorldItem* AddItem(AFortInventory* Inventory, FFortItemEntry ItemEntry)
	{
		if (!Inventory || !Inventory->Owner)
			return nullptr;

		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(ItemEntry.ItemDefinition->CreateTemporaryItemInstanceBP(ItemEntry.Count, ItemEntry.Level));
		FFortItemEntry* WorldItemEntry = &WorldItem->ItemEntry;

		CreateItemEntry(WorldItemEntry);
		CopyItemEntry(WorldItemEntry, &ItemEntry);

		AFortPlayerController* PlayerController = Cast<AFortPlayerController>(Inventory->Owner);

		WorldItem->SetOwningControllerForTemporaryItem(PlayerController);

		AddWorldItem(Inventory, WorldItem);

		if (WorldItemEntry && PlayerController)
		{
			UFortGadgetItemDefinition* GadgetItemDefinition = Cast<UFortGadgetItemDefinition>(WorldItemEntry->ItemDefinition);

			if (GadgetItemDefinition)
			{
				// 7FF66FE971B0
				void* (*GetInterfaceAddress)(UObject* Object, UClass* InterfaceClass) = decltype(GetInterfaceAddress)(0x18471B0 + uintptr_t(GetModuleHandle(0)));
				void* InterfaceAddress = GetInterfaceAddress(PlayerController, IFortInventoryOwnerInterface::StaticClass());

				// 7FF66F5CEEE0
				bool (*ApplyGadgetData)(UFortGadgetItemDefinition* GadgetItemDefinition, void* InterfaceAddress, UFortWorldItem* WorldItem, bool bIdk) = decltype(ApplyGadgetData)(0xF7EEE0 + uintptr_t(GetModuleHandle(0)));
				ApplyGadgetData(GadgetItemDefinition, InterfaceAddress, WorldItem, true);
			}
		}

		return WorldItem;
	}

	void RemoveItem(AFortInventory* Inventory, const FGuid& ItemGuid)
	{
		if (!Inventory)
			return;

		AFortPlayerController* PlayerController = Cast<AFortPlayerController>(Inventory->Owner);

		if (!PlayerController)
			return;

		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(ItemGuid));

		if (!WorldItem)
			return;

		FFortItemEntry* WorldItemEntry = &WorldItem->ItemEntry;

		if (WorldItemEntry)
		{
			UFortGadgetItemDefinition* GadgetItemDefinition = Cast<UFortGadgetItemDefinition>(WorldItemEntry->ItemDefinition);

			if (GadgetItemDefinition)
			{
				// 7FF66FE971B0
				void* (*GetInterfaceAddress)(UObject* Object, UClass* InterfaceClass) = decltype(GetInterfaceAddress)(0x18471B0 + uintptr_t(GetModuleHandle(0)));
				void* InterfaceAddress = GetInterfaceAddress(PlayerController, IFortInventoryOwnerInterface::StaticClass());

				// 7FF66F5CF030
				void (*RemoveGadgetData)(UFortGadgetItemDefinition* GadgetItemDefinition, void* InterfaceAddress, UFortWorldItem* WorldItem) = decltype(RemoveGadgetData)(0xF7F030 + uintptr_t(GetModuleHandle(0)));
				RemoveGadgetData(GadgetItemDefinition, InterfaceAddress, WorldItem);
			}
		}

		Inventory->RecentlyRemoved.Add(WorldItem);

		for (int32 i = 0; i < Inventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = Inventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &Inventory->Inventory.ItemInstances[i]->ItemEntry;
			if (!ItemEntry) continue;

			if (ItemEntry->ItemGuid == ItemGuid)
			{
				FreeItemEntry(ItemEntry);
				Inventory->Inventory.ItemInstances.Remove(i);
				break;
			}
		}

		for (int32 i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry* ReplicatedItemEntry = &Inventory->Inventory.ReplicatedEntries[i];
			if (!ReplicatedItemEntry) continue;

			if (ReplicatedItemEntry->ItemGuid == ItemGuid)
			{
				FreeItemEntry(ReplicatedItemEntry);
				Inventory->Inventory.ReplicatedEntries.Remove(i);
				break;
			}
		}

		Inventory->Inventory.MarkArrayDirty();
		Inventory->HandleInventoryLocalUpdate();
	}

	void ResetInventory(AFortInventory* Inventory, bool bRemoveAll = true)
	{
		if (!Inventory)
			return;
	
		if (bRemoveAll)
		{
			if (Inventory->Inventory.ItemInstances.IsValid())
				Inventory->Inventory.ItemInstances.Free();

			if (Inventory->Inventory.ReplicatedEntries.IsValid())
				Inventory->Inventory.ReplicatedEntries.Free();

			Inventory->Inventory.MarkArrayDirty();
			Inventory->HandleInventoryLocalUpdate();
		}
		else
		{
			TArray<FGuid> ItemGuidToRemoves;

			for (int32 i = 0; i < Inventory->Inventory.ItemInstances.Num(); i++)
			{
				UFortWorldItem* ItemInstance = Inventory->Inventory.ItemInstances[i];
				if (!ItemInstance) continue;

				FFortItemEntry* ItemEntry = &ItemInstance->ItemEntry;
				if (!ItemEntry) continue;

				UFortWorldItemDefinition* ItemDefinition = Cast<UFortWorldItemDefinition>(ItemEntry->ItemDefinition);
				if (!ItemDefinition) continue;

				if (!ItemDefinition->bCanBeDropped)
					continue;

				ItemGuidToRemoves.Add(ItemEntry->ItemGuid);
			}

			for (int32 i = 0; i < ItemGuidToRemoves.Num(); i++)
				Inventory::RemoveItem(Inventory, ItemGuidToRemoves[i]);
		}
	}

	AFortPickup* GetClosestPickup(AFortPickup* PickupToCombine, float MaxDistance)
	{
		if (!PickupToCombine)
			return nullptr;

		UFortWorldItemDefinition* WorldItemDefinitionCombine = Cast<UFortWorldItemDefinition>(PickupToCombine->PrimaryPickupItemEntry.ItemDefinition);

		if (WorldItemDefinitionCombine)
		{
			TArray<AActor*> Actors;
			UGameplayStatics::GetAllActorsOfClass(PickupToCombine, AFortPickup::StaticClass(), &Actors);

			AFortPickup* ClosestPickup = nullptr;

			for (int32 i = 0; i < Actors.Num(); i++)
			{
				AFortPickup* Pickup = Cast<AFortPickup>(Actors[i]);
				if (!Pickup) continue;

				if (Pickup->bActorIsBeingDestroyed || Pickup->bPickedUp)
					continue;

				if (Pickup == PickupToCombine)
					continue;

				const float Distance = PickupToCombine->GetDistanceTo(Pickup);

				if (Distance > MaxDistance)
					continue;

				if (Pickup->PickupLocationData.CombineTarget)
					continue;

				FFortItemEntry* PrimaryPickupItemEntry = &Pickup->PrimaryPickupItemEntry;
				if (!PrimaryPickupItemEntry) continue;

				UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(PrimaryPickupItemEntry->ItemDefinition);
				if (!WorldItemDefinition) continue;

				if (WorldItemDefinition != WorldItemDefinitionCombine)
					continue;

				if (PrimaryPickupItemEntry->Count >= WorldItemDefinition->MaxStackSize)
					continue;

				ClosestPickup = Pickup;
				break;
			}

			if (Actors.IsValid())
				Actors.Free();

			return ClosestPickup;
		}

		return nullptr;
	}

	bool CombineNearestPickup(AFortPickup* PickupToCombine, float MaxDistance)
	{
		if (!PickupToCombine)
			return false;

		AFortPickup* ClosestPickup = Inventory::GetClosestPickup(PickupToCombine, MaxDistance);

		if (ClosestPickup)
		{
			PickupToCombine->PickupLocationData.CombineTarget = ClosestPickup;
			PickupToCombine->PickupLocationData.FlyTime = 0.25f;
			PickupToCombine->PickupLocationData.LootFinalPosition = (FVector_NetQuantize10)ClosestPickup->K2_GetActorLocation();
			PickupToCombine->PickupLocationData.LootInitialPosition = (FVector_NetQuantize10)PickupToCombine->K2_GetActorLocation();
			PickupToCombine->PickupLocationData.FinalTossRestLocation = (FVector_NetQuantize10)ClosestPickup->K2_GetActorLocation();

			PickupToCombine->OnRep_PickupLocationData();
			PickupToCombine->FlushNetDormancy();

			// Use to call a CombinePickup function with delay
			UKismetSystemLibrary::K2_SetTimer(PickupToCombine, L"OnRep_ServerImpactSoundFlash", PickupToCombine->PickupLocationData.FlyTime, false);

			return true;
		}

		return false;
	}

	AFortPickup* SpawnPickup(AFortPawn* ItemOwner, FFortItemEntry ItemEntry, FVector SpawnLocation, FVector FinalLocation, int32 OverrideMaxStackCount = 0, bool bToss = true, bool bCombinePickup = true)
	{
		FRotator SpawnRotation = FRotator({ 0, 0, 0 });

		// 7FF66F5F89D0
		void (*SetParentInventory)(FFortItemEntry* ItemEntry, AFortInventory* Inventory, bool bIsReplicatedCopy) = decltype(SetParentInventory)(0xFA89D0 + uintptr_t(GetModuleHandle(0)));
		SetParentInventory(&ItemEntry, nullptr, false);

		FFortCreatePickupData CreatePickupData = FFortCreatePickupData();
		CreatePickupData.World = Globals::GetWorld();
		CreatePickupData.ItemEntry = &ItemEntry;
		CreatePickupData.SpawnLocation = &SpawnLocation;
		CreatePickupData.SpawnRotation = &SpawnRotation;
		CreatePickupData.PlayerController = nullptr;
		CreatePickupData.OverrideClass = nullptr;
		CreatePickupData.NullptrIdk = nullptr;
		CreatePickupData.bRandomRotation = true;
		CreatePickupData.PickupSourceTypeFlags = 0;

		AFortPickup* Pickup = Inventory::CreatePickupFromData(&CreatePickupData);

		if (Pickup)
		{
			if (ItemOwner)
				Pickup->PawnWhoDroppedPickup = ItemOwner;

			Pickup->bCombinePickupsWhenTossCompletes = bCombinePickup;

			Pickup->TossPickup(FinalLocation, ItemOwner, OverrideMaxStackCount, bToss);
		}
			
		return Pickup;
	}

	TArray<FFortItemEntryStateValue>* CopyStateValues(TArray<FFortItemEntryStateValue>* PrimaryStateValues, const TArray<FFortItemEntryStateValue>* StateValues)
	{
		if (PrimaryStateValues != StateValues)
		{
			int32 OldCount = PrimaryStateValues->Num();
			int32 NewCount = StateValues->Num();

			PrimaryStateValues->SetNum(NewCount);

			if (NewCount == 0 && OldCount == 0)
				return PrimaryStateValues;

			for (int32 i = 0; i < NewCount; i++) 
			{
				(*PrimaryStateValues)[i].IntValue = (*StateValues)[i].IntValue;
				(*PrimaryStateValues)[i].NameValue = (*StateValues)[i].NameValue;
				(*PrimaryStateValues)[i].StateType = (*StateValues)[i].StateType;
			}
		}

		return PrimaryStateValues;
	}

	void AddInventoryItem(AFortPlayerController* PlayerController, FFortItemEntry ItemEntry, FGuid CurrentItemGuid = FGuid(), bool bReplaceWeapon = true)
	{
		if (!PlayerController || !PlayerController->WorldInventory || !ItemEntry.ItemDefinition)
			return;

		if (ItemEntry.Count <= 0)
			return;

		void* InventoryOwner = (void*)(__int64(PlayerController) + InventoryOwnerOffset);

		TArray<UFortItem*> ItemArray;
		bool bFoundItemInstances = FindItemInstancesFromDefinition(InventoryOwner, ItemEntry.ItemDefinition, ItemArray);

		if (bFoundItemInstances)
		{
			int32 ItemCountToAdd = ItemEntry.Count;

			for (int32 i = 0; i < ItemArray.Num(); i++)
			{
				UFortWorldItem* WorldItem = Cast<UFortWorldItem>(ItemArray[i]);
				if (!WorldItem) continue;

				UFortItemDefinition* ItemDefinition = WorldItem->ItemEntry.ItemDefinition;
				if (!ItemDefinition) continue;

				int32 CurrentCount = WorldItem->ItemEntry.Count;
				int32 MaxStackSize = ItemDefinition->MaxStackSize;

				if (CurrentCount < MaxStackSize)
				{
					int32 NewCount = UKismetMathLibrary::Min(CurrentCount + ItemCountToAdd, MaxStackSize);

					ModifyCountItem(PlayerController->WorldInventory, WorldItem->ItemEntry.ItemGuid, NewCount);

					ItemCountToAdd -= (NewCount - CurrentCount);

					if (ItemCountToAdd <= 0)
						break;
				}
			}

			if (ItemCountToAdd < 0)
				ItemCountToAdd = 0;

			ItemEntry.Count = ItemCountToAdd;
		}

		if (ItemEntry.Count <= 0)
			return;

		UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(ItemEntry.ItemDefinition);

		if (!WorldItemDefinition)
			return;
		
		if (ItemEntry.Count > WorldItemDefinition->MaxStackSize)
		{
			while (ItemEntry.Count > 0)
			{
				int32 NewCount = UKismetMathLibrary::Min(ItemEntry.Count, WorldItemDefinition->MaxStackSize);

				FFortItemEntry NewItemEntry;
				MakeItemEntry(&NewItemEntry, WorldItemDefinition, NewCount, ItemEntry.Level, ItemEntry.LoadedAmmo, ItemEntry.Durability);

				AddInventoryItem(PlayerController, NewItemEntry, CurrentItemGuid, false);

				ItemEntry.Count -= NewCount;
			}

			return;
		}

		FVector SpawnLocation = FVector({ 0, 0, 0 });
		FVector FinalLocation = FVector({ 0, 0, 0 });
		
		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (PlayerPawn)
		{
			SpawnLocation = PlayerPawn->K2_GetActorLocation();

			SpawnLocation.Z += 40.0f;

			float RandomAngle = UKismetMathLibrary::RandomFloatInRange(-60.0f, 60.0f);

			FRotator RandomRotation = PlayerPawn->K2_GetActorRotation();
			RandomRotation.Yaw += RandomAngle;

			float RandomDistance = UKismetMathLibrary::RandomFloatInRange(500.0f, 600.0f);
			FVector Direction = UKismetMathLibrary::GetForwardVector(RandomRotation);

			FinalLocation = SpawnLocation + Direction * RandomDistance;
		}

		if (WorldItemDefinition->IsA(UFortWeaponMeleeItemDefinition::StaticClass()) && !WorldItemDefinition->bCanBeDropped) // If the WorldItemDefinition is a pickaxe, replace or add
		{
			for (int32 i = 0; i < PlayerController->WorldInventory->Inventory.ItemInstances.Num(); i++)
			{
				UFortWorldItem* ItemInstance = PlayerController->WorldInventory->Inventory.ItemInstances[i];
				if (!ItemInstance) continue;

				FFortItemEntry* ItemEntry = &PlayerController->WorldInventory->Inventory.ItemInstances[i]->ItemEntry;
				if (!ItemEntry) continue;

				UFortWeaponMeleeItemDefinition* WeaponMeleeItemDefinition = Cast<UFortWeaponMeleeItemDefinition>(ItemEntry->ItemDefinition);
				if (!WeaponMeleeItemDefinition) continue;

				if (WeaponMeleeItemDefinition->bCanBeDropped)
					continue;

				RemoveItem(PlayerController->WorldInventory, ItemEntry->ItemGuid);
			}

			AddItem(PlayerController->WorldInventory, ItemEntry);
		}
		else if (IsInventoryFull(PlayerController->WorldInventory) && WorldItemDefinition->bInventorySizeLimited && PlayerPawn) // If the Inventory is full replace the current weapon and spawn pickup
		{
			if (!bReplaceWeapon)
			{
				SpawnPickup(PlayerPawn, ItemEntry, SpawnLocation, FinalLocation);
				return;
			}

			UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(CurrentItemGuid));

			if (!WorldItem)
			{
				AFortWeapon* Weapon = PlayerPawn->CurrentWeapon;

				if (Weapon)
					WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(Weapon->ItemEntryGuid));
			}

			if (!WorldItem)
			{
				SpawnPickup(PlayerPawn, ItemEntry, SpawnLocation, FinalLocation);
				return;
			}

			UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(WorldItem->ItemEntry.ItemDefinition);

			if (!WorldItemDefinition || !WorldItemDefinition->bCanBeDropped)
			{
				SpawnPickup(PlayerPawn, ItemEntry, SpawnLocation, FinalLocation);
				return;
			}

			UFortWeaponRangedItemDefinition* WeaponRangedItemDefinition = Cast<UFortWeaponRangedItemDefinition>(WorldItemDefinition);

			if (WeaponRangedItemDefinition && WeaponRangedItemDefinition->bPersistInInventoryWhenFinalStackEmpty)
			{
				int32 ItemQuantity = UFortKismetLibrary::K2_GetItemQuantityOnPlayer(PlayerController, WeaponRangedItemDefinition);

				if (ItemQuantity == 0)
				{
					SpawnPickup(PlayerPawn, ItemEntry, SpawnLocation, FinalLocation);
					return;
				}
			}

			PlayerController->ServerAttemptInventoryDrop(WorldItem->ItemEntry.ItemGuid, WorldItem->ItemEntry.Count);

			UFortWorldItem* NewWorldItem = AddItem(PlayerController->WorldInventory, ItemEntry);

			if (NewWorldItem)
			{
				AFortPlayerControllerAthena* PlayerControllerAthena = Cast<AFortPlayerControllerAthena>(PlayerController);

				if (WorldItem->ItemEntry.ItemGuid == PlayerPawn->CurrentWeapon->ItemEntryGuid && PlayerControllerAthena)
					PlayerControllerAthena->ClientEquipItem(NewWorldItem->ItemEntry.ItemGuid, true);
			}
		}
		else if (!IsInventoryFull(PlayerController->WorldInventory) && WorldItemDefinition->bInventorySizeLimited) // If the Inventory is not full just add
		{
			AddItem(PlayerController->WorldInventory, ItemEntry);
		}
		else if (!WorldItemDefinition->bInventorySizeLimited)
		{
			UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_FindExistingItemForDefinition(WorldItemDefinition, false));

			if (WorldItem && !WorldItemDefinition->bAllowMultipleStacks && PlayerPawn)
			{
				SpawnPickup(PlayerPawn, ItemEntry, SpawnLocation, FinalLocation);
				return;
			}
			else
			{
				AddItem(PlayerController->WorldInventory, ItemEntry);
			}
		}
		else
		{
			FN_LOG(LogInventory, Error, L"Zgueg au max");
		}
	}

	bool RemoveInventoryItem(AFortPlayerController* PlayerController, const FGuid& ItemGuid, int32 AmountToRemove)
	{
		UFortWorldItem* WorldItem = Cast<UFortWorldItem>(PlayerController->K2_GetInventoryItemWithGuid(ItemGuid));

		if (!WorldItem)
			return false;

		FFortItemEntry* ItemEntry = &WorldItem->ItemEntry;

		if (AmountToRemove >= ItemEntry->Count)
		{
			UFortWeaponRangedItemDefinition* WeaponRangedItemDefinition = Cast<UFortWeaponRangedItemDefinition>(ItemEntry->ItemDefinition);

			if (WeaponRangedItemDefinition && WeaponRangedItemDefinition->bPersistInInventoryWhenFinalStackEmpty)
			{
				int32 ItemQuantity = UFortKismetLibrary::K2_GetItemQuantityOnPlayer(PlayerController, WeaponRangedItemDefinition);

				if (ItemQuantity == 1)
				{
					ModifyCountItem(PlayerController->WorldInventory, ItemGuid, 0);
					return true;
				}
			}

			RemoveItem(PlayerController->WorldInventory, ItemGuid);
		}
		else if (AmountToRemove < ItemEntry->Count)
		{
			int32 NewCount = ItemEntry->Count - AmountToRemove;

			ModifyCountItem(PlayerController->WorldInventory, ItemGuid, NewCount);
		}
		else
			return false;

		return true;
	}

	bool InitWorldInventory(AFortPlayerController* PlayerController)
	{
		if (PlayerController->WorldInventory)
			return true;

		AFortInventory* WorldInventory = Util::SpawnActor<AFortInventory>(AFortInventory::StaticClass());

		if (WorldInventory)
		{
			WorldInventory->SetOwner(PlayerController);
			WorldInventory->OnRep_Owner();

			PlayerController->WorldInventory = WorldInventory;
			PlayerController->bHasInitializedWorldInventory = true;
			PlayerController->HandleWorldInventoryLocalUpdate();

			return (PlayerController->WorldInventory != nullptr);
		}

		return false;
	}

	void SetupInventory(AFortPlayerController* PlayerController, UFortWeaponMeleeItemDefinition* PickaxeItemDefinition)
	{
		if (!PlayerController)
			return;

		if (!InitWorldInventory(PlayerController))
			return;

		TArray<FItemAndCount> StartingItems = Cast<AFortGameModeAthena>(Globals::GetGameMode())->StartingItems;

		for (int32 i = 0; i < StartingItems.Num(); i++)
		{
			FItemAndCount StartingItem = StartingItems[i];

			UFortItemDefinition* ItemDefinition = StartingItem.Item;

			if (!ItemDefinition || StartingItem.Count <= 0)
				continue;

			FFortItemEntry ItemEntry;
			MakeItemEntry(&ItemEntry, ItemDefinition, StartingItem.Count, -1, -1, -1.0f);

			AddInventoryItem(PlayerController, ItemEntry);
			FreeItemEntry(&ItemEntry);
		}

		if (PickaxeItemDefinition)
		{
			FFortItemEntry ItemEntry;
			MakeItemEntry(&ItemEntry, PickaxeItemDefinition, 1, 0, 0, 0.f);

			AddInventoryItem(PlayerController, ItemEntry);
			FreeItemEntry(&ItemEntry);
		}
	}

	void InitInventory()
	{
		uintptr_t AddressFindItemInstancesFromDefinition = MinHook::FindPattern(Patterns::FindItemInstancesFromDefinition);
		uintptr_t AddressCreateItemEntry = MinHook::FindPattern(Patterns::CreateItemEntry);
		uintptr_t AddressCopyItemEntry = MinHook::FindPattern(Patterns::CopyItemEntry);
		uintptr_t AddressCreateDefaultItemEntry = MinHook::FindPattern(Patterns::CreateDefaultItemEntry);
		uintptr_t AddressPickupInitialize = MinHook::FindPattern(Patterns::PickupInitialize);
		uintptr_t AddressSetStateValue = MinHook::FindPattern(Patterns::SetStateValue);
		uintptr_t AddressCreateSimplePickup = MinHook::FindPattern(Patterns::CreateSimplePickup);
		uintptr_t AddressCreatePickupFromData = MinHook::FindPattern(Patterns::CreatePickupFromData);
		uintptr_t AddressMarkItemEntryDirty = MinHook::FindPattern(Patterns::MarkItemEntryDirty);
		uintptr_t AddressAddWorldItem = MinHook::FindPattern(Patterns::AddWorldItem);
		uintptr_t AddressFreeItemEntry = MinHook::FindPattern(Patterns::FreeItemEntry);

		FindItemInstancesFromDefinition = decltype(FindItemInstancesFromDefinition)(AddressFindItemInstancesFromDefinition);
		CreateItemEntry = decltype(CreateItemEntry)(AddressCreateItemEntry);
		CopyItemEntry = decltype(CopyItemEntry)(AddressCopyItemEntry);
		CreateDefaultItemEntry = decltype(CreateDefaultItemEntry)(AddressCreateDefaultItemEntry);
		PickupInitialize = decltype(PickupInitialize)(AddressPickupInitialize);
		SetStateValue = decltype(SetStateValue)(AddressSetStateValue);
		CreateSimplePickup = decltype(CreateSimplePickup)(AddressCreateSimplePickup);
		CreatePickupFromData = decltype(CreatePickupFromData)(AddressCreatePickupFromData);
		MarkItemEntryDirty = decltype(MarkItemEntryDirty)(AddressMarkItemEntryDirty);
		AddWorldItem = decltype(AddWorldItem)(AddressAddWorldItem);
		FreeItemEntry = decltype(FreeItemEntry)(AddressFreeItemEntry);

		FN_LOG(LogInit, Log, L"InitInventory Success!");
	}
}