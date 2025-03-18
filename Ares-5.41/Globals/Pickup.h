#pragma once

namespace Pickup
{
	/* ----------------------------------------- AFortPickupOG --------------------------------------- */

	bool (*PickupAddInventoryOwnerInterfaceOG)(AFortPickup* Pickup, void* InventoryOwner);
	void (*TossPickupOG)(AFortPickup* Pickup, const FVector& FinalLocation, class AFortPawn* ItemOwner, int32 OverrideMaxStackCount, bool bToss);
	void (*OnServerStopCallbackOG)(AFortPickup* Pickup, const FHitResult& Hit);



	/* ------------------------------------------ AFortPickup ---------------------------------------- */

	bool PickupAddInventoryOwnerInterface(AFortPickup* Pickup, void* InventoryOwner)
	{
		PickupAddInventoryOwnerInterfaceOG(Pickup, InventoryOwner);

		if (!Pickup || !InventoryOwner)
			return false;

		AFortPlayerController* PlayerController = AFortPlayerController::GetPlayerControllerFromInventoryOwner(InventoryOwner);
		if (!PlayerController) return false;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;
		if (!PlayerPawn) return false;

		for (int32 i = 0; i < PlayerPawn->QueuedAutoPickups.Num(); i++)
		{
			AFortPickup* QueuedAutoPickup = PlayerPawn->QueuedAutoPickups[i];
			if (!QueuedAutoPickup) continue;

			if (QueuedAutoPickup == Pickup)
			{
				PlayerPawn->QueuedAutoPickups.Remove(i);
				break;
			}
		}

		Inventory::AddInventoryItem(PlayerController, Pickup->PrimaryPickupItemEntry, Pickup->PickupLocationData.PickupGuid);

		return true;
	}

	void TossPickup(AFortPickup* Pickup, const FVector& FinalLocation, class AFortPawn* ItemOwner, int32 OverrideMaxStackCount, bool bToss)
	{
		TossPickupOG(Pickup, FinalLocation, ItemOwner, OverrideMaxStackCount, bToss);

		if (Pickup->bTossedFromContainer)
			return;

		Inventory::CombineNearestPickup(Pickup, 300.0f);
	}

	void OnServerStopCallback(AFortPickup* Pickup, const FHitResult& Hit)
	{
		OnServerStopCallbackOG(Pickup, Hit);

		if (Pickup->bActorIsBeingDestroyed || !Pickup->bCombinePickupsWhenTossCompletes)
			return;

		Inventory::CombineNearestPickup(Pickup, 400.0f);
	}

	void CombinePickup(AFortPickup* Pickup, FFrame& Stack, void* Ret)
	{
		Stack.Code += Stack.Code != nullptr;

		if (Pickup->bActorIsBeingDestroyed)
			return;

		AFortPickup* CombineTarget = Pickup->PickupLocationData.CombineTarget;

		if (!CombineTarget || CombineTarget->bActorIsBeingDestroyed)
			return;

		UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(CombineTarget->PrimaryPickupItemEntry.ItemDefinition);
		if (!WorldItemDefinition) return;

		int32 NewCount = Pickup->PrimaryPickupItemEntry.Count + CombineTarget->PrimaryPickupItemEntry.Count;
		int32 CountToRemove = UKismetMathLibrary::Max(0, NewCount - WorldItemDefinition->MaxStackSize);
		NewCount = UKismetMathLibrary::Min(NewCount, WorldItemDefinition->MaxStackSize);

		CombineTarget->PrimaryPickupItemEntry.SetCount(NewCount);
		CombineTarget->FlushNetDormancy();

		if (CountToRemove > 0)
		{
			FFortItemEntry ItemEntry;
			Inventory::MakeItemEntry(&ItemEntry, WorldItemDefinition, CountToRemove, Pickup->PrimaryPickupItemEntry.Level, Pickup->PrimaryPickupItemEntry.LoadedAmmo, Pickup->PrimaryPickupItemEntry.Durability);

			const FVector& SpawnLocation = CombineTarget->K2_GetActorLocation();

			AFortPickup* NewPickup = AFortPickup::CreatePickup(
				Pickup->GetWorld(),
				&ItemEntry,
				&SpawnLocation,
				nullptr,
				nullptr,
				nullptr,
				true,
				(uint32)EFortPickupSourceTypeFlag::Other);

			if (NewPickup)
			{
				NewPickup->TossPickup(SpawnLocation, nullptr, 0, true);
			}

			ItemEntry.FreeItemEntry();
		}

		Pickup->K2_DestroyActor();
	}

	void InitPickup()
	{
		AFortPickupAthena* FortPickupAthenaDefault = AFortPickupAthena::GetDefaultObj();
		UClass* FortPickupAthenaClass = AFortPickupAthena::StaticClass();

		/* ------------------------------------------ AFortPickup ---------------------------------------- */

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0xFA11C0), PickupAddInventoryOwnerInterface, (LPVOID*)(&PickupAddInventoryOwnerInterfaceOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0xFA11C0));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0xFABF80), TossPickup, (LPVOID*)(&TossPickupOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0xFABF80));

		MinHook::HookVTable(FortPickupAthenaDefault, 0x630 / 8, OnServerStopCallback, (LPVOID*)(&OnServerStopCallbackOG), "AFortPickup::OnServerStopCallback");

		UFunction* OnRep_ServerImpactSoundFlashFunc = FortPickupAthenaClass->GetFunction("FortPickup", "OnRep_ServerImpactSoundFlash");
		MinHook::HookFunctionExec(OnRep_ServerImpactSoundFlashFunc, CombinePickup, nullptr);

		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitPawn Success!");
	}
}