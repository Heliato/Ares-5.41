#pragma once


namespace FortAthenaSupplyDrop
{
	/* ----------------------------------- AFortAthenaSupplyDropOG ----------------------------------- */



	/* ------------------------------------ AFortAthenaSupplyDrop ------------------------------------ */

	AFortPickup* SpawnPickup(AFortAthenaSupplyDrop* SupplyDrop, FFrame& Stack, AFortPickup** Ret)
	{
		UFortWorldItemDefinition* ItemDefinition = nullptr;
		int32 NumberToSpawn = 1;
		AFortPawn* TriggeringPawn = nullptr;
		FVector Position = FVector();
		FVector Direction = FVector();

		Stack.StepCompiledIn(&ItemDefinition);
		Stack.StepCompiledIn(&NumberToSpawn);
		Stack.StepCompiledIn(&TriggeringPawn);
		Stack.StepCompiledIn(&Position);
		Stack.StepCompiledIn(&Direction);

		Stack.Code += Stack.Code != nullptr;

		UWorld* World = GEngine->GetWorldFromContextObject(SupplyDrop, EGetWorldErrorMode::LogAndReturnNull);

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
		CreatePickupData.bRandomRotation = true;
		CreatePickupData.PickupSourceTypeFlags = 0;

		AFortPickup* Pickup = AFortPickup::CreatePickupFromData(&CreatePickupData);

		if (Pickup)
		{
			FVector FinalLocation = Position;
			FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();

			FinalLocation.X += RandomDirection.X * 700.0f;
			FinalLocation.Y += RandomDirection.Y * 700.0f;

			Pickup->bTossedFromContainer = true;
			Pickup->OnRep_TossedFromContainer();

			Pickup->TossPickup(FinalLocation, nullptr, 0, true);
		}

		ItemEntry.FreeItemEntry();

		*Ret = Pickup;
		return *Ret;
	}

	void InitFortAthenaSupplyDrop()
	{
		AFortAthenaSupplyDrop* FortAthenaSupplyDropDefault = AFortAthenaSupplyDrop::GetDefaultObj();
		UClass* FortAthenaSupplyDropClass = AFortAthenaSupplyDrop::StaticClass();

		/* ------------------------------------ AFortAthenaSupplyDrop ------------------------------------ */

		UFunction* SpawnPickupFunc = FortAthenaSupplyDropClass->GetFunction("FortAthenaSupplyDrop", "SpawnPickup");
		MinHook::HookFunctionExec(SpawnPickupFunc, SpawnPickup, nullptr);

		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"FortAthenaSupplyDrop Success!");
	}
}