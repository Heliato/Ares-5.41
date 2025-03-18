#pragma once

namespace Inventory
{
	bool (*GetItemInstancesIdk)(void* idk, UFortWorldItemDefinition* ItemDefinition, TArray<UFortWorldItem*>* OutWorldItems);
	UFortWorldItem* (*GetItemInstanceIdk)(void* idk, const FGuid& ItemGuid);
	FFortItemEntry* (*CreateItemEntry)(FFortItemEntry* ItemEntry);
	FFortItemEntry* (*CreateDefaultItemEntry)(FFortItemEntry* ItemEntry, UFortWorldItemDefinition* ItemDefinition, int32 Count, int32 Level);
	FFortItemEntry* (*CopyItemEntry)(FFortItemEntry* PrimaryItemEntry, FFortItemEntry* ItemEntry);
	void (*PickupInitialize)(AFortPickup* Pickup, FFortItemEntry* ItemEntry, TArray<FFortItemEntry*> MultiItemEntries, bool bSplitOnPickup);
	bool (*SetStateValue)(FFortItemEntry* ItemEntry, const EFortItemEntryState& StateType, int32 IntValue);
	AFortPickup* (*CreatePickup)(__int64 a1);
	AFortPickup* (*CreateSimplePickup)(UObject* WorldContextObject, FFortItemEntry* ItemEntry, const FVector& SpawnLocation, const FRotator& SpawnRotation);

	void UpdateInventory(AFortInventory* WorldInventory)
	{
		if (!WorldInventory)
			return;

		WorldInventory->HandleInventoryLocalUpdate();
		WorldInventory->Inventory.MarkArrayDirty();
	}

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

		// The function is compiled in another function... We have to redo it
		return Globals::GetDataTableRowFromName<FFortBaseWeaponStats>(WeaponStatHandle->DataTable, WeaponStatHandle->RowName);
	}

	AFortPickup* GetClosestPickup(UFortItemDefinition* ItemDefinition, FVector Location, float MaxDistance)
	{
		if (!ItemDefinition || Location.IsZero())
			return nullptr;

		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(Globals::GetWorld(), AFortPickup::StaticClass(), &Actors);

		AFortPickup* ClosestPickup = nullptr;

		for (AActor* Actor : Actors)
		{
			AFortPickup* Pickup = (AFortPickup*)Actor;
			if (!Pickup) continue;

			if (!Pickup->HasAuthority() || Pickup->bPickedUp)
				continue;

			float Distance = sqrtf((Location - Pickup->K2_GetActorLocation()).SizeSquared());

			if (Distance > MaxDistance || Distance <= 0.f)
				continue;

			FFortItemEntry* PrimaryPickupItemEntry = &Pickup->PrimaryPickupItemEntry;
			if (!PrimaryPickupItemEntry) continue;

			UFortItemDefinition* ClosestItemDefinition = PrimaryPickupItemEntry->ItemDefinition;
			if (!ClosestItemDefinition) continue;

			if (ClosestItemDefinition != ItemDefinition)
				continue;

			if (PrimaryPickupItemEntry->Count >= ItemDefinition->MaxStackSize)
				continue;

			ClosestPickup = Pickup;
			break;
		}

		if (Actors.Num() > 0)
			Actors.Free();

		return ClosestPickup;
	}

	void MakeItemEntry(FFortItemEntry* ItemEntry, UFortWorldItemDefinition* ItemDefinition, int32 Count, int32 Level, int32 LoadedAmmo, float Durability)
	{
		if (!ItemEntry || !ItemDefinition)
			return;

		FFortBaseWeaponStats* WeaponStats = GetWeaponStats((UFortWeaponItemDefinition*)ItemDefinition);
		int32 ItemLevel = GetItemLevel(ItemDefinition->LootLevelData);

		CreateDefaultItemEntry(ItemEntry, ItemDefinition, Count, (Level == -1) ? ItemLevel : Level);

		ItemEntry->Durability = (Durability == 0.f) ?  ItemDefinition->GetMaxDurability(ItemLevel) : Durability;
		ItemEntry->LoadedAmmo = (WeaponStats && LoadedAmmo == -1) ? WeaponStats->ClipSize : LoadedAmmo;
	}

	bool GetItemInstances(AFortPlayerController* PlayerController, UFortWorldItemDefinition* WorldItemDefinition, TArray<UFortWorldItem*>* OutWorldItems)
	{
		if (!PlayerController || !WorldItemDefinition)
			return false;

		auto idk = (void*)(__int64(PlayerController) + IdkOffset);

		if (!idk)
			return false;

		bool bSuccess = GetItemInstancesIdk(idk, WorldItemDefinition, OutWorldItems);

		return bSuccess;
	}

	UFortWorldItem* GetItemInstance(AFortPlayerController* PlayerController, const FGuid& ItemGuid, bool bVerifMaxStackSize = false)
	{
		if (!PlayerController)
			return nullptr;

		auto idk = (void*)(__int64(PlayerController) + IdkOffset);

		if (!idk)
			return nullptr;

		UFortWorldItem* ItemInstance = GetItemInstanceIdk(idk, ItemGuid);

		if (ItemInstance)
		{
			UFortItemDefinition* ItemDefinition = ItemInstance->GetItemDefinitionBP();

			if (!ItemDefinition)
				return nullptr;

			if (ItemInstance->ItemEntry.Count >= ItemDefinition->MaxStackSize && bVerifMaxStackSize)
				return nullptr;
		}

		return ItemInstance;
	}

	UFortWorldItem* GetItemInstance(AFortPlayerController* PlayerController, UFortWorldItemDefinition* WorldItemDefinition, bool bVerifMaxStackSize = false)
	{
		if (!PlayerController || !WorldItemDefinition)
			return nullptr;

		TArray<UFortWorldItem*> WorldItems;
		bool bSuccess = GetItemInstances(PlayerController, WorldItemDefinition, &WorldItems);

		if (bSuccess)
		{
			for (int32 i = 0; i < WorldItems.Num(); i++)
			{
				UFortWorldItem* ItemInstance = WorldItems[i];

				if (!ItemInstance)
					continue;

				UFortItemDefinition* ItemDefinition = ItemInstance->GetItemDefinitionBP();

				if (!ItemDefinition)
					continue;

				if (ItemInstance->ItemEntry.Count >= ItemDefinition->MaxStackSize && bVerifMaxStackSize)
					continue;

				return ItemInstance;
			}
		}

		return nullptr;
	}

	void ModifyCountItem(AFortPlayerController* PlayerController, const FGuid& ItemGuid, int32 NewCount)
	{
		if (!PlayerController)
			return;

		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!WorldInventory)
			return;

		for (int32 i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = WorldInventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &WorldInventory->Inventory.ItemInstances[i]->ItemEntry;

			if (ItemEntry->ItemGuid == ItemGuid)
			{
				ItemEntry->Count = NewCount;
				WorldInventory->Inventory.MarkItemDirty(WorldInventory->Inventory.ItemInstances[i]->ItemEntry);
				break;
			}
		}

		for (int32 i = 0; i < WorldInventory->Inventory.ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry* ReplicatedItemEntry = &WorldInventory->Inventory.ReplicatedEntries[i];

			if (ReplicatedItemEntry->ItemGuid == ItemGuid)
			{
				ReplicatedItemEntry->Count = NewCount;
				WorldInventory->Inventory.MarkItemDirty(WorldInventory->Inventory.ReplicatedEntries[i]);
				break;
			}
		}
	}

	AFortPickupAthena* SpawnPickup(AFortPawn* ItemOwner, FFortItemEntry* ItemEntry, const FVector& Position, bool bToss, bool bCopyGuid = false, const FGuid& OldGuid = FGuid())
	{
		if (!ItemEntry)
			return nullptr;

		if (ItemEntry->Count <= 0)
			return nullptr;

		AFortPickupAthena* Pickup = Util::SpawnActor<AFortPickupAthena>(AFortPickupAthena::StaticClass(), Position);

		if (!Pickup)
		{
			FN_LOG(LogInventory, Error, "[Inventory::SpawnPickup] failed to spawn Pickup!");
			return nullptr;
		}

		if (ItemOwner)
			Pickup->PawnWhoDroppedPickup = ItemOwner;

		TArray<FFortItemEntry*> MultiItemEntries{};
		PickupInitialize(Pickup, ItemEntry, MultiItemEntries, false);

		if (bCopyGuid)
			ItemEntry->ItemGuid = OldGuid;

		Pickup->bRandomRotation = true;

		/*AFortPickup* ClosestPickup = GetClosestPickup(ItemEntry->ItemDefinition, Position, 300.f);

		if (ClosestPickup)
		{
			FFortPickupLocationData* PickupLocationData = &Pickup->PickupLocationData;

			if (PickupLocationData)
			{
				PickupLocationData->CombineTarget = ClosestPickup;
				PickupLocationData->FlyTime = 0.5f;
				PickupLocationData->LootFinalPosition = (FVector_NetQuantize10)Position;
				PickupLocationData->LootInitialPosition = (FVector_NetQuantize10)Pickup->K2_GetActorLocation();
				PickupLocationData->FinalTossRestLocation = (FVector_NetQuantize10)ClosestPickup->K2_GetActorLocation();
				Pickup->OnRep_PickupLocationData();

				Pickup->ForceNetUpdate();
			}
		}
		else*/
		{
			Pickup->TossPickup(Position, ItemOwner, 0, bToss);
		}

		return Pickup;
	}

	bool IsInventoryFull(AFortPlayerController* PlayerController)
	{
		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!WorldInventory)
			return false;

		int32 TotalItems = 0;

		for (int32 i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = WorldInventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			if (!ItemInstance->GetItemDefinitionBP()->IsA(UFortWeaponRangedItemDefinition::StaticClass()) &&
				!ItemInstance->GetItemDefinitionBP()->IsA(UFortGadgetItemDefinition::StaticClass()))
				continue;

			TotalItems++;
		}

		return (TotalItems >= 5);
	}

	void RemoveItemFromInventory(AFortPlayerController* PlayerController, const FGuid& ItemGuid)
	{
		if (!PlayerController)
			return;

		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!WorldInventory)
			return;

		for (int32 i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = WorldInventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry ItemEntry = WorldInventory->Inventory.ItemInstances[i]->ItemEntry;

			if (ItemEntry.ItemGuid == ItemGuid)
			{
				WorldInventory->Inventory.ItemInstances.Remove(i);
				break;
			}
		}

		for (int32 i = 0; i < WorldInventory->Inventory.ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry ReplicatedItemEntry = WorldInventory->Inventory.ReplicatedEntries[i];

			if (ReplicatedItemEntry.ItemGuid == ItemGuid)
			{
				WorldInventory->Inventory.ReplicatedEntries.Remove(i);
				break;
			}
		}
	}

	bool RemoveInventoryItem(AFortPlayerController* PlayerController, const FGuid& ItemGuid, int32 AmountToRemove)
	{
		UFortWorldItem* ItemInstance = Inventory::GetItemInstance(PlayerController, ItemGuid);

		if (!ItemInstance)
		{
			FN_LOG(LogInventory, Error, "[Inventory::RemoveInventoryItem] Failed to get ItemInstance!");
			return false;
		}

		FFortItemEntry ItemEntry = ItemInstance->ItemEntry;

		if (AmountToRemove >= ItemEntry.Count)
		{
			/*UFortItemDefinition* ItemDefinition = ItemInstance->GetItemDefinitionBP();

			if (ItemDefinition && ItemDefinition->IsA(UFortWeaponRangedItemDefinition::StaticClass()))
			{
				UFortWeaponRangedItemDefinition* WeaponRangedItemDefinition = (UFortWeaponRangedItemDefinition*)ItemDefinition;

				if (WeaponRangedItemDefinition->bPersistInInventoryWhenFinalStackEmpty && ((ItemEntry.Count - AmountToRemove) == 0))
				{
					Inventory::ModifyCountItem(PlayerController, ItemGuid, 0);
					return true;
				}
			}*/

			Inventory::RemoveItemFromInventory(PlayerController, ItemGuid);
		}
		else if (AmountToRemove < ItemEntry.Count)
		{
			int32 NewCount = ItemEntry.Count - AmountToRemove;

			Inventory::ModifyCountItem(PlayerController, ItemGuid, NewCount);
		}
		else
			return false;

		return true;
	}

	void RemoveAllItemsFromInventory(AFortPlayerController* PlayerController, bool bRemoveCantBeDropped = false)
	{
		if (!PlayerController)
			return;

		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!WorldInventory)
			return;

		TArray<FGuid> ItemGuidToRemove;

		for (int32 i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = WorldInventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &ItemInstance->ItemEntry;
			if (!ItemEntry) continue;

			UFortWorldItemDefinition* ItemDefinition = (UFortWorldItemDefinition*)ItemInstance->GetItemDefinitionBP();
			if (!ItemDefinition) continue;

			if (!ItemDefinition->bCanBeDropped && !bRemoveCantBeDropped)
				continue;

			ItemGuidToRemove.Add(ItemEntry->ItemGuid);
		}

		for (FGuid& ItemGuid : ItemGuidToRemove)
		{
			RemoveItemFromInventory(PlayerController, ItemGuid);
		}

		if (ItemGuidToRemove.Num() > 0)
			ItemGuidToRemove.Free();
	}

	void ModifyLoadedAmmoItem(AFortPlayerController* PlayerController, const FGuid& ItemGuid, int32 NewLoadedAmmo)
	{
		if (!PlayerController)
			return;

		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!WorldInventory)
			return;

		for (int32 i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = WorldInventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &WorldInventory->Inventory.ItemInstances[i]->ItemEntry;

			if (ItemEntry->ItemGuid == ItemGuid)
			{
				UFortItemDefinition* ItemDefinition = ItemEntry->ItemDefinition;

				// For Grappler
				/*if (ItemDefinition && ItemDefinition->IsA(UFortWeaponItemDefinition::StaticClass()))
				{
					UFortWeaponItemDefinition* WeaponItemDefinition = (UFortWeaponItemDefinition*)ItemDefinition;

					if (WeaponItemDefinition->bUsesCustomAmmoType && NewLoadedAmmo <= 0)
					{
						Inventory::RemoveItemFromInventory(PlayerController, ItemGuid);
						return;
					}
				}*/

				ItemEntry->LoadedAmmo = NewLoadedAmmo;
				WorldInventory->Inventory.MarkItemDirty(WorldInventory->Inventory.ItemInstances[i]->ItemEntry);
				break;
			}
		}

		for (int32 i = 0; i < WorldInventory->Inventory.ReplicatedEntries.Num(); i++)
		{
			FFortItemEntry* ReplicatedItemEntry = &WorldInventory->Inventory.ReplicatedEntries[i];

			if (ReplicatedItemEntry->ItemGuid == ItemGuid)
			{
				ReplicatedItemEntry->LoadedAmmo = NewLoadedAmmo;
				WorldInventory->Inventory.MarkItemDirty(WorldInventory->Inventory.ReplicatedEntries[i]);
				break;
			}
		}
	}

	void DropAllItemsFromInventory(AFortPlayerController* PlayerController, bool bRemoveCantBeDropped = false)
	{
		if (!PlayerController)
			return;

		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!WorldInventory || !PlayerController->MyFortPawn)
			return;

		for (int32 i = 0; i < WorldInventory->Inventory.ItemInstances.Num(); i++)
		{
			UFortWorldItem* ItemInstance = WorldInventory->Inventory.ItemInstances[i];
			if (!ItemInstance) continue;

			FFortItemEntry* ItemEntry = &ItemInstance->ItemEntry;
			if (!ItemEntry) continue;

			UFortWorldItemDefinition* ItemDefinition = (UFortWorldItemDefinition*)ItemInstance->GetItemDefinitionBP();
			if (!ItemDefinition) continue;

			if (!ItemDefinition->bCanBeDropped)
				continue;

			Inventory::SpawnPickup(PlayerController->MyFortPawn, ItemEntry, PlayerController->MyFortPawn->K2_GetActorLocation(), true, true, ItemInstance->ItemEntry.ItemGuid);
		}

		RemoveAllItemsFromInventory(PlayerController, bRemoveCantBeDropped);
	}

	UFortWorldItem* AddItem(AFortPlayerController* PlayerController, FFortItemEntry* ItemEntry, bool bCopyGuid = false, const FGuid& OldGuid = FGuid())
	{
		if (!PlayerController || !ItemEntry)
		{
			FN_LOG(LogInventory, Error, "[Inventory::AddItem] failed to get PlayerController/ItemEntry!");
			return nullptr;
		}

		if (ItemEntry->Count <= 0)
			return nullptr;

		UFortItemDefinition* ItemDefinition = ItemEntry->ItemDefinition;

		if (!ItemDefinition)
		{
			FN_LOG(LogInventory, Error, "[Inventory::AddItem] failed to get ItemDefinition!");
			return nullptr;
		}

		AFortInventory* WorldInventory = PlayerController->WorldInventory;

		if (!WorldInventory)
		{
			FN_LOG(LogInventory, Error, "[Inventory::AddItem] failed to get WorldInventory!");
			return nullptr;
		}

		UFortWorldItem* ItemInstance = (UFortWorldItem*)ItemDefinition->CreateTemporaryItemInstanceBP(ItemEntry->Count, ItemEntry->Level);

		if (!ItemInstance)
		{
			FN_LOG(LogInventory, Error, "[Inventory::AddItem] failed to create ItemInstance!");
			return nullptr;
		}

		FFortItemEntry* InstanceItemEntry = &ItemInstance->ItemEntry;
		CreateItemEntry(InstanceItemEntry);
		CopyItemEntry(InstanceItemEntry, ItemEntry);

		if (bCopyGuid)
			InstanceItemEntry->ItemGuid = OldGuid;

		WorldInventory->Inventory.ReplicatedEntries.Add(*InstanceItemEntry);
		WorldInventory->Inventory.ItemInstances.Add(ItemInstance);

		WorldInventory->Inventory.MarkItemDirty(*InstanceItemEntry);

		return ItemInstance;
	}

	void AddInventoryItem(AFortPlayerController* PlayerController, FFortItemEntry* ItemEntry, FGuid CurrentWeaponGuid = FGuid())
	{
		if (!PlayerController || !ItemEntry)
		{
			FN_LOG(LogInventory, Error, "[Inventory::AddInventoryItem] failed to get PlayerController/ItemDefinition/ItemEntry!");
			return;
		}

		UFortWorldItemDefinition* ItemDefinition = (UFortWorldItemDefinition*)ItemEntry->ItemDefinition;

		if (!ItemDefinition)
		{
			FN_LOG(LogInventory, Error, "[Inventory::AddInventoryItem] failed to get ItemDefinition!");
			return;
		}

		AFortPlayerPawn* Pawn = PlayerController->MyFortPawn;

		bool bInventoryFull = IsInventoryFull(PlayerController);

		UFortWorldItem* ItemInstance = GetItemInstance(PlayerController, ItemDefinition, true);

		const FGuid& OldItemGuid = ItemEntry->ItemGuid;

		int32 CountToRemove = 0;
		bool bSuccess = false;
		bool bSkip = false;

		Skip:

		if (!bSkip)
		{
			if (ItemInstance)
			{
				int32 NewCount = ItemInstance->ItemEntry.Count + ItemEntry->Count;

				if (NewCount > ItemDefinition->MaxStackSize)
				{
					CountToRemove = NewCount - ItemDefinition->MaxStackSize;
					NewCount = ItemDefinition->MaxStackSize;
				}

				ModifyCountItem(PlayerController, ItemInstance->GetItemGuid(), NewCount);
				bSuccess = true;
			}
			else
			{
				if ((ItemDefinition->IsA(UFortWeaponRangedItemDefinition::StaticClass()) || ItemDefinition->IsA(UFortGadgetItemDefinition::StaticClass())) && bInventoryFull)
				{
					UFortWorldItem* CurrentItemInstance = GetItemInstance(PlayerController, CurrentWeaponGuid);

					if (!CurrentItemInstance && Pawn)
					{
						AFortWeapon* CurrentWeapon = Pawn->CurrentWeapon;

						if (CurrentWeapon)
							CurrentItemInstance = Inventory::GetItemInstance(PlayerController, CurrentWeapon->ItemEntryGuid);
					}

					if (!CurrentItemInstance)
					{
						CountToRemove = ItemEntry->Count;
						bSkip = true;
						goto Skip;
					}

					UFortWorldItemDefinition* CurrentItemDefinition = (UFortWorldItemDefinition*)CurrentItemInstance->GetItemDefinitionBP();

					if (!CurrentItemDefinition)
					{
						CountToRemove = ItemEntry->Count;
						bSkip = true;
						goto Skip;
					}

					if (!CurrentItemDefinition->bCanBeDropped)
					{
						CountToRemove = ItemEntry->Count;
						bSkip = true;
						goto Skip;
					}

					PlayerController->ServerAttemptInventoryDrop(CurrentItemInstance->GetItemGuid(), CurrentItemInstance->GetNumInStack());

					// ItemInstance = AddItem(PlayerController, ItemEntry, true, OldItemGuid);
					ItemInstance = AddItem(PlayerController, ItemEntry, false, OldItemGuid);

					if (ItemInstance && Pawn)
					{
						if (CurrentItemInstance->GetItemGuid() == Pawn->CurrentWeapon->ItemEntryGuid)
							((AFortPlayerControllerAthena*)PlayerController)->ClientEquipItem((FGuid&)ItemInstance->GetItemGuid(), true);
					}

					bSuccess = true;
				}

				if (!bSuccess)
				{
					ItemInstance = GetItemInstance(PlayerController, ItemDefinition);

					if (ItemInstance)
					{
						if (ItemDefinition->bAllowMultipleStacks)
						{
							// ItemInstance = AddItem(PlayerController, ItemEntry, true, OldItemGuid);
							ItemInstance = AddItem(PlayerController, ItemEntry, false, OldItemGuid);
							bSuccess = true;
						}
						else
						{
							CountToRemove = ItemEntry->Count;
							bSuccess = true;
						}
					}
					else
					{
						// ItemInstance = AddItem(PlayerController, ItemEntry, true, OldItemGuid);
						ItemInstance = AddItem(PlayerController, ItemEntry, false, OldItemGuid);
						bSuccess = true;
					}
				}
			}
		}

		if (ItemInstance && bSuccess)
		{
			int32 NewCount = ItemInstance->ItemEntry.Count;

			if (NewCount > ItemDefinition->MaxStackSize)
			{
				CountToRemove = NewCount - ItemDefinition->MaxStackSize;
				NewCount = ItemDefinition->MaxStackSize;

				ModifyCountItem(PlayerController, ItemInstance->GetItemGuid(), NewCount);
			}

			UpdateInventory(PlayerController->WorldInventory);
		}

		if (CountToRemove > 0 && Pawn)
		{
			FFortItemEntry NewItemEntry;
			MakeItemEntry(&NewItemEntry, ItemDefinition, CountToRemove, ItemEntry->Durability, ItemEntry->Level, ItemEntry->LoadedAmmo);
			SpawnPickup(Pawn, &NewItemEntry, Pawn->K2_GetActorLocation(), true);
		}
	}

	void SetupInventory(AFortPlayerController* PlayerController, UFortWeaponMeleeItemDefinition* PickaxeDefinition)
	{
		TArray<FItemAndCount> StartingItems = Cast<AFortGameModeAthena>(Globals::GetGameMode())->StartingItems;

		for (int32 i = 0; i < StartingItems.Num(); i++)
		{
			FItemAndCount StartingItem = StartingItems[i];

			UFortWorldItemDefinition* ItemDefinition = (UFortWorldItemDefinition*)StartingItem.Item;

			if (!ItemDefinition || StartingItem.Count <= 0)
				continue;

			FFortItemEntry ItemEntry;
			MakeItemEntry(&ItemEntry, ItemDefinition, StartingItem.Count, -1, -1, 0.f);
			SetStateValue(&ItemEntry, EFortItemEntryState::ShouldShowItemToast, 1);
			AddInventoryItem(PlayerController, &ItemEntry);
		}

		if (PickaxeDefinition)
		{
			FFortItemEntry ItemEntry;
			MakeItemEntry(&ItemEntry, PickaxeDefinition, 1, 0, 0, 0.f);
			AddInventoryItem(PlayerController, &ItemEntry);
		}

		UpdateInventory(PlayerController->WorldInventory);
	}

	void InitInventory()
	{
		uintptr_t AddressGetItemInstances = MinHook::FindPattern(Patterns::GetItemInstances);
		uintptr_t AddressGetItemInstance = MinHook::FindPattern(Patterns::GetItemInstance);
		uintptr_t AddressCreateItemEntry = MinHook::FindPattern(Patterns::CreateItemEntry);
		uintptr_t AddressCopyItemEntry = MinHook::FindPattern(Patterns::CopyItemEntry);
		uintptr_t AddressCreateDefaultItemEntry = MinHook::FindPattern(Patterns::CreateDefaultItemEntry);
		uintptr_t AddressPickupInitialize = MinHook::FindPattern(Patterns::PickupInitialize);
		uintptr_t AddressSetStateValue = MinHook::FindPattern(Patterns::SetStateValue);
		uintptr_t AddressCreatePickup = MinHook::FindPattern(Patterns::CreatePickup);
		uintptr_t AddressCreateSimplePickup = MinHook::FindPattern(Patterns::CreateSimplePickup);

		GetItemInstancesIdk = decltype(GetItemInstancesIdk)(AddressGetItemInstances);
		GetItemInstanceIdk = decltype(GetItemInstanceIdk)(AddressGetItemInstance);
		CreateItemEntry = decltype(CreateItemEntry)(AddressCreateItemEntry);
		CopyItemEntry = decltype(CopyItemEntry)(AddressCopyItemEntry);
		CreateDefaultItemEntry = decltype(CreateDefaultItemEntry)(AddressCreateDefaultItemEntry);
		PickupInitialize = decltype(PickupInitialize)(AddressPickupInitialize);
		SetStateValue = decltype(SetStateValue)(AddressSetStateValue);
		CreatePickup = decltype(CreatePickup)(AddressCreatePickup);
		CreateSimplePickup = decltype(CreateSimplePickup)(AddressCreateSimplePickup);

		FN_LOG(LogInit, Log, "InitInventory Success!");
	}
}