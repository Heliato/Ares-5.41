#pragma once

namespace Pawn
{
	/* -------------------------------------- AFortPlayerPawnOG -------------------------------------- */
	void (*ServerReviveFromDBNOOG)(AFortPlayerPawn* PlayerPawn, AController* EventInstigator);
	/* ----------------------------------------- AFortPawnOG ----------------------------------------- */
	void (*OnDeathServerOG)(AFortPawn* Pawn, float Damage, const FGameplayTagContainer& DamageTags, const FVector& Momentum, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser, const FGameplayEffectContextHandle& EffectContext);
	void (*OnDamageServerOG)(AFortPawn* Pawn, float Damage, const FGameplayTagContainer& DamageTags, const FVector& Momentum, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser, const FGameplayEffectContextHandle& EffectContext);

	

	/* --------------------------------------- AFortPlayerPawn --------------------------------------- */

	/*
	 * Rewrite AFortPlayerPawn::ServerHandlePickup (1.8)
	 *
	 * - https://imgur.com/pKR6Nlh
	 * - https://imgur.com/Yi6yLaC
	 */
	void ServerHandlePickup(AFortPlayerPawn* PlayerPawn, AFortPickup* Pickup, float InFlyTime, const FVector& InStartDirection, bool bPlayPickupSound)
	{
		if (!Pickup || PlayerPawn->bIsDBNO)
			return;

		float FlyTime = InFlyTime / PlayerPawn->PickupSpeedMultiplier;

		Pickup->PickupLocationData.PickupGuid = PlayerPawn->LastEquippedWeaponGUID;
		Pickup->SetPickupTarget(PlayerPawn, FlyTime, InStartDirection, bPlayPickupSound);
	}

	void ServerHandlePickupWithSwap(AFortPlayerPawn* PlayerPawn, AFortPickup* Pickup, const FGuid& Swap, float InFlyTime, const FVector& InStartDirection, bool bPlayPickupSound)
	{
		if (!PlayerPawn || !Pickup)
			return;

		float FlyTime = InFlyTime / PlayerPawn->PickupSpeedMultiplier;

		Pickup->PickupLocationData.PickupGuid = PlayerPawn->LastEquippedWeaponGUID;
		Pickup->SetPickupTarget(PlayerPawn, FlyTime, InStartDirection, bPlayPickupSound);
	}

	bool CanBeRevived(AFortPlayerPawn* PlayerPawn, AController* EventInstigator)
	{
		// Soon
		return true;
	}

	void ServerReviveFromDBNO(AFortPlayerPawn* PlayerPawn, AController* EventInstigator)
	{
		AFortPlayerState* PlayerState = Cast<AFortPlayerState>(PlayerPawn->PlayerState);
		if (!PlayerState) return;

		UFortAbilitySystemComponent* AbilitySystemComponent = PlayerState->AbilitySystemComponent;

		if (CanBeRevived(PlayerPawn, EventInstigator) && AbilitySystemComponent)
		{
			AbilitySystemComponent->ClearAllAbilities();

			UFortGameData* GameData = Globals::GetGameData();
			UFortAbilitySet* DefaultAbilities = Functions::LoadAbilitySet(GameData->GenericPlayerAbilitySet);

			Abilities::GrantGameplayAbility(DefaultAbilities, AbilitySystemComponent);
			Abilities::GrantGameplayEffect(DefaultAbilities, AbilitySystemComponent);
			Abilities::GrantModifierAbilityFromPlaylist(AbilitySystemComponent);

			bool bIsReviveSelf = EventInstigator == PlayerPawn->Controller;
			TSubclassOf<UGameplayEffect> ReviveGameplayEffect{};

			if (bIsReviveSelf)
				ReviveGameplayEffect = PlayerPawn->SelfReviveGameplayEffect;
			else
				ReviveGameplayEffect = PlayerPawn->TeammateReviveGameplayEffect;

			FGameplayEffectContextHandle EffectContext{};
			AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(ReviveGameplayEffect, 0, EffectContext);

			PlayerPawn->bIsDBNO = false;
			PlayerPawn->bPlayedDying = false;

			float ReviveHealth = PlayerPawn->SetByCallerReviveHealth.GetValueAtLevel(0);

			if (ReviveHealth > 0.0f)
			{
				PlayerPawn->SetHealth(ReviveHealth);
			}

			PlayerPawn->OnRep_IsDBNO();

			AFortPlayerControllerZone* PlayerControllerZone = Cast<AFortPlayerControllerZone>(PlayerPawn->Controller);

			if (PlayerControllerZone)
			{
				PlayerControllerZone->ClientOnPawnRevived(EventInstigator);
			}

			AFortPlayerPawnAthena* PlayerPawnAthena = Cast<AFortPlayerPawnAthena>(PlayerPawn);

			if (PlayerPawnAthena)
			{
				PlayerPawnAthena->DBNORevivalStacking = 0;
			}

			// UClass* GameplayAbility = UGAB_AthenaDBNORevive_C::StaticClass(); // UGAB_PlayerDBNOResurrect_C

			//FN_LOG(LogPlayerController, Log, L"GameplayAbility %s!", GameplayAbility->GetName().c_str());

			//Abilities::ApplyGameplayAbility(GameplayAbility, AbilitySystemComponent);
		}





		FN_LOG(LogPlayerController, Log, L"[AFortPlayerPawn::ServerReviveFromDBNO] func called for %s!", EventInstigator->GetName().c_str());

		ServerReviveFromDBNOOG(PlayerPawn, EventInstigator);
	}

	//void ServerReviveFromDBNO(AFortPlayerPawnAthena* PlayerPawnAthena, AController* EventInstigator)
	//{
	//	__int64 v3; // rax
	//	__int64 v4; // rbx
	//	char* v5; // rdi
	//	__int64 v6; // rax

	//	ServerReviveFromDBNO((AFortPlayerPawn*)PlayerPawnAthena, EventInstigator);

	//	if (!PlayerPawnAthena->bIsDBNO)        // if (!PlayerPawn->bIsDBNO)
	//	{
	//		v3 = *(_QWORD*)(PlayerPawn + 0x7C0);

	//		PlayerPawnAthena->DBNORevivalStacking = 0;        // DBNORevivalStacking

	//		v4 = (*(__int64(__fastcall**)(__int64))(v3 + 16))(PlayerPawn + 0x7C0);
	//		v5 = (char*)sub_7FF61CAD94C0();
	//		if (sub_7FF6202AF070((__int64*)(v4 + 0x1330), (_DWORD*)v5 + 134, -1))
	//			(*(void(__fastcall**)(__int64, char*, _QWORD))(*(_QWORD*)v4 + 1672i64))(v4, v5 + 536, 0i64);
	//		v6 = (__int64)sub_7FF61CAD94C0();
	//		sub_7FF620359460((__int16*)v4, *(_QWORD*)(v6 + 0xA18), v4 + 0x1000);
	//	}
	//}

	void OnCapsuleBeginOverlap(AFortPlayerPawn* PlayerPawn, FFrame& Stack, void* Ret)
	{
		UPrimitiveComponent* OverlappedComp = nullptr;
		AActor* OtherActor = nullptr;
		UPrimitiveComponent* OtherComp = nullptr;
		int32 OtherBodyIndex = -1;
		bool bFromSweep = true;
		FHitResult SweepResult = FHitResult();

		Stack.StepCompiledIn(&OverlappedComp);
		Stack.StepCompiledIn(&OtherActor);
		Stack.StepCompiledIn(&OtherComp);
		Stack.StepCompiledIn(&OtherBodyIndex);
		Stack.StepCompiledIn(&bFromSweep);
		Stack.StepCompiledIn(&SweepResult);

		Stack.Code += Stack.Code != nullptr;

		AFortPlayerController* PlayerController = Cast<AFortPlayerController>(PlayerPawn->Controller);
		if (!PlayerController) return;

		AFortPickup* Pickup = Cast<AFortPickup>(OtherActor);
		if (!Pickup) return;

		float RepickupDelay = PlayerPawn->AutoPickupDropRepickupDelay.GetValueAtLevel(0);

		if (!GAutoResourceGathering)
			return;

		if (!PlayerPawn->bIsDBNO ||
			!PlayerPawn->bIsSkydiving)
		{
			if (Pickup->bPickedUp || !Pickup->bWeaponsCanBeAutoPickups)
				return;

			if (!Pickup->bServerStoppedSimulation && (Pickup->PawnWhoDroppedPickup == PlayerPawn))
				return;

			if (Pickup->PawnWhoDroppedPickup == PlayerPawn)
			{
				const float LastDropPickupTime = Pickup->LastDropPickupTime();
				const float TimeSeconds = PlayerPawn->GetWorld()->GetTimeSeconds();

				if ((TimeSeconds - LastDropPickupTime) <= RepickupDelay)
					return;
			}
			
			UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(Pickup->PrimaryPickupItemEntry.ItemDefinition);
			if (!WorldItemDefinition) return;

			int32 ItemQuantity = UFortKismetLibrary::K2_GetItemQuantityOnPlayer(PlayerController, WorldItemDefinition);

			for (int32 i = 0; i < PlayerPawn->QueuedAutoPickups.Num(); i++)
			{
				AFortPickup* QueuedAutoPickup = PlayerPawn->QueuedAutoPickups[i];
				if (!QueuedAutoPickup) continue;

				UFortWorldItemDefinition* QueuedWorldItemDefinition = Cast<UFortWorldItemDefinition>(QueuedAutoPickup->PrimaryPickupItemEntry.ItemDefinition);
				if (!QueuedWorldItemDefinition) continue;

				if (QueuedWorldItemDefinition != WorldItemDefinition)
					continue;

				ItemQuantity += QueuedAutoPickup->PrimaryPickupItemEntry.Count;
			}

			if (ItemQuantity >= WorldItemDefinition->MaxStackSize && !WorldItemDefinition->bAllowMultipleStacks)
				return;

			PlayerPawn->QueuedAutoPickups.Add(Pickup);

			float InFlyTime = Globals::GenFlyTime();
			PlayerPawn->ServerHandlePickup(Pickup, InFlyTime, FVector(), true);
		}
	}

	void OnDeathServer(AFortPawn* Pawn, float Damage, const FGameplayTagContainer& DamageTags, const FVector& Momentum, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser, const FGameplayEffectContextHandle& EffectContext)
	{
		OnDeathServerOG(Pawn, Damage, DamageTags, Momentum, HitInfo, InstigatedBy, DamageCauser, EffectContext);

		AFortPlayerControllerAthena* PlayerControllerAthena = Cast<AFortPlayerControllerAthena>(Pawn->Controller);
		if (!PlayerControllerAthena) return;

		AFortPlayerState* PlayerState = Cast<AFortPlayerState>(PlayerControllerAthena->PlayerState);
		if (!PlayerState) return;

		AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(Globals::GetGameState());
		if (!GameStateAthena) return;

		if (PlayerControllerAthena && !GameState::IsRespawningAllowed(GameStateAthena, PlayerState))
		{
			PlayerControllerAthena->ServerDropAllItems(nullptr);
			Inventory::ResetInventory(PlayerControllerAthena->WorldInventory);
		}
	}

	void MovingEmoteStopped(AFortPawn* Pawn, FFrame& Stack, void* Ret)
	{
		Stack.Code += Stack.Code != nullptr;

		Pawn->bMovingEmote = false;
	}

	void InitPawn()
	{
		AFortPlayerPawnAthena* FortPlayerPawnAthenaDefault = AFortPlayerPawnAthena::GetDefaultObj();
		UClass* FortPlayerPawnAthenaClass = AFortPlayerPawnAthena::StaticClass();

		/* --------------------------------------- AFortPlayerPawn --------------------------------------- */

		MinHook::HookVTable(FortPlayerPawnAthenaDefault, 0xD40 / 8, ServerHandlePickup, nullptr, "AFortPlayerPawn::ServerHandlePickup");
		MinHook::HookVTable(FortPlayerPawnAthenaDefault, 0xD30 / 8, ServerHandlePickupWithSwap, nullptr, "AFortPlayerPawn::ServerHandlePickupWithSwap");
		MinHook::HookVTable(FortPlayerPawnAthenaDefault, 0xCB0 / 8, ServerReviveFromDBNO, (LPVOID*)(&ServerReviveFromDBNOOG), "AFortPlayerPawn::ServerReviveFromDBNO");

		UFunction* OnCapsuleBeginOverlapFunc = FortPlayerPawnAthenaClass->GetFunction("FortPlayerPawn", "OnCapsuleBeginOverlap");
		MinHook::HookFunctionExec(OnCapsuleBeginOverlapFunc, OnCapsuleBeginOverlap, nullptr);

		/* ------------------------------------------ AFortPawn ------------------------------------------ */

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0x14B4330), OnDeathServer, (LPVOID*)(&OnDeathServerOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0x14B4330));

		UFunction* MovingEmoteStoppedFunc = FortPlayerPawnAthenaClass->GetFunction("FortPawn", "MovingEmoteStopped");
		MinHook::HookFunctionExec(MovingEmoteStoppedFunc, MovingEmoteStopped, nullptr);

		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitPawn Success!");
	}
}