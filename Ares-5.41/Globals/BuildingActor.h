#pragma once

namespace BuildingActor
{
	/* ------------------------------------ ABuildingContainerOG ------------------------------------- */
	void (*ABuildingContainer_PostUpdateOG)(ABuildingContainer* BuildingContainer, EFortBuildingPersistentState BuildingPersistentState, __int64 a3);
	/* ------------------------------------- ABuildingSMActorOG -------------------------------------- */
	void (*ABuildingSMActor_PostUpdateOG)(ABuildingSMActor* BuildingSMActor);
	/* -------------------------------------- ABuildingActorOG --------------------------------------- */
	void (*OnDamageServerOG)(ABuildingActor* BuildingActor, float Damage, const FGameplayTagContainer& DamageTags, const FVector& Momentum, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser, const FGameplayEffectContextHandle& EffectContext);
	void (*OnDeathServerOG)(ABuildingActor* BuildingActor, float Damage, const FGameplayTagContainer& DamageTags, const FVector& Momentum, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser, const FGameplayEffectContextHandle& EffectContext);



	/* ------------------------------------- ABuildingContainer -------------------------------------- */

	/*
	 * Rewrite ABuildingContainer::PostUpdate (1.1)
	 *
	 * - https://imgur.com/fd1yviC
	 * - https://imgur.com/LgvtgEJ
	 * - https://imgur.com/xVvDs3A
	 * - https://imgur.com/SLW9Mbo
	 * - https://imgur.com/7umU78D
	 */
	void ABuildingContainer_PostUpdate(ABuildingContainer* BuildingContainer, EFortBuildingPersistentState BuildingPersistentState, __int64 a3)
	{
		// No need to call ABuildingSMActor::PostUpdate because it is already called in the OG
		// BuildingContainer->PostUpdate();
		// https://imgur.com/3aQHQSz

		if (!a3)
		{
			((ABuildingSMActor*)BuildingContainer)->PostUpdate();
		}
		else
			ABuildingContainer_PostUpdateOG(BuildingContainer, BuildingPersistentState, a3);

		if (BuildingPersistentState == EFortBuildingPersistentState::New)
		{
			float LootSpawnThreshold = 0.0f;

			bool bSpawnAllLoot = FParse::Param(FCommandLine::Get(), TEXT("SpawnAllLoot"));

			if (bSpawnAllLoot)
				LootSpawnThreshold = 1.0f;

			if (BuildingContainer->SearchLootTierGroup.IsValid())
			{
				BuildingContainer->PickLootTierGroupAthena(&BuildingContainer->SearchLootTierGroup, BuildingContainer->SearchLootTierGroup);

				FName* LootTierKey = nullptr;
				int32 ChooseLootTier = -1;
				int32 LootTier = -1;

				LootSpawnThreshold = 1.0f;

				if (BuildingContainer->SearchLootTierChosenQuotaInfo.LootTierKey.ComparisonIndex > 0 || 
					BuildingContainer->SearchLootTierChosenQuotaInfo.LootTierKey.Number > 0)
				{
					LootTierKey = &BuildingContainer->ContainerLootTierKey;
					ChooseLootTier = BuildingContainer->SearchLootTierChosenQuotaInfo.LootTier;

					BuildingContainer->ContainerLootTierKey = BuildingContainer->SearchLootTierChosenQuotaInfo.LootTierKey;

					LootTier = ChooseLootTier;
				}
				else
				{
					int32 LootLevel = UFortKismetLibrary::GetLootLevel(BuildingContainer);

					LootTierKey = &BuildingContainer->ContainerLootTierKey;

					Loots::PickLootTierKeyAndLootTierFromTierGroup(
						&BuildingContainer->ContainerLootTierKey, 
						&LootTier, 
						BuildingContainer->SearchLootTierGroup, 
						LootLevel, 
						0, 
						-1, 
						BuildingContainer->StaticGameplayTags
					);

					ChooseLootTier = LootTier;
				}

				BuildingContainer->SelectMeshSet(ChooseLootTier);

				EFortBuildingPersistentState PersistentState = EFortBuildingPersistentState::Default;

				if (!bSpawnAllLoot && 
					!BuildingContainer->bAlwaysMaintainLoot && 
					!Loots::IsLootDropPossible(*LootTierKey, L"ABuildingContainer::PostUpdate", 0))
				{
					LootTierKey = nullptr;
					PersistentState = EFortBuildingPersistentState::Searched;

					BuildingContainer->SetSearchedContainer(nullptr);

					if (!BuildingContainer->bAlwaysShowContainer)
						LootSpawnThreshold = 0.0f;
				}

				AFortWorldManager* WorldManager = Globals::GetWorldManager();

				if (BuildingContainer->bPersistToWorld && WorldManager)
				{
					// Idk what it does
					// https://imgur.com/Tpw67IX
				}

				UBlueprintGeneratedClass* FloorLootClass = FindObjectFast<UBlueprintGeneratedClass>("/Game/Athena/Environments/Blueprints/Tiered_Athena_FloorLoot_01.Tiered_Athena_FloorLoot_01_C");
				UBlueprintGeneratedClass* FloorLootWarmupClass = FindObjectFast<UBlueprintGeneratedClass>("/Game/Athena/Environments/Blueprints/Tiered_Athena_FloorLoot_Warmup.Tiered_Athena_FloorLoot_Warmup_C");

				if (BuildingContainer->IsA(FloorLootClass) || BuildingContainer->IsA(FloorLootWarmupClass))
					BuildingContainer->SpawnLoot(nullptr);
			}

			// to fix
			// https://imgur.com/lvVgqrK

			/*float v6 = 0.0f;

			int v19 = *(int*)(a3 + 0x14);
			if (v19 > 0)
			{
				if (*(int*)(a3 + 0x10) >= v19)
					*(int*)(a3 + 0x10) = 0;

				int v20 = *(int*)(a3 + 0x10);

				*(int*)(a3 + 0x10) = v20 + 1;

				v6 = *(float*)(a3 + 4i64 * v20);
			}*/

			float v6 = (float)rand() * 0.000030518509f;

			if ((float)((float)(v6 * 1.0f) + 0.0000000099999999f) > LootSpawnThreshold)
			{
				// https://imgur.com/ldBugSY
				if (BuildingContainer->bBuriedTreasure)
				{
					BuildingContainer->SetSearchedContainer(nullptr);

					if (BuildingContainer->bPersistToWorld)
					{
						// Idk what it does
						// https://imgur.com/lfVX54g
					}
				}
				else
				{
					// Idk what it does
					// https://imgur.com/TA0cs9x
				}

				BuildingContainer->ContainerLootTierKey = FName(0);
			}
		}
		else
		{
			if (BuildingContainer->ContainerLootTierKey.IsValid())
			{
				BuildingContainer->SelectMeshSet(BuildingContainer->ContainerLootTierKey);
			}
			else
			{
				int32 LootLevel = UFortKismetLibrary::GetLootLevel(BuildingContainer);
				int32 LootTier = -1;

				Loots::PickLootTierKeyAndLootTierFromTierGroup(
					&BuildingContainer->ContainerLootTierKey, 
					&LootTier, 
					BuildingContainer->SearchLootTierGroup, 
					LootLevel, 
					0, 
					-1, 
					BuildingContainer->StaticGameplayTags
				);

				BuildingContainer->SelectMeshSet(LootTier);
			}

			if (BuildingPersistentState == EFortBuildingPersistentState::Searched)
				BuildingContainer->SetSearchedContainer(nullptr);
		}

		FN_LOG(LogBuildingActor, Debug, L"ABuildingContainer::PostUpdate() on existing container Container: %s, ContainerLootTierKey: %s, AltMeshIdx: %d",
			BuildingContainer->GetName().c_str(), BuildingContainer->ContainerLootTierKey.ToString().c_str(), BuildingContainer->AltMeshIdx);
	}

	bool SpawnLoot(ABuildingContainer* BuildingContainer, AFortPlayerPawn* PlayerPawn)
	{
		if (!BuildingContainer->HasAuthority())
			return false;

		BuildingContainer->ForceNetUpdate();

		if (!BuildingContainer->bAlreadySearched)
		{
			bool bIsAthena = UFortGlobals::IsInAthena();

			const float LootSpawnLocationX = bIsAthena ? BuildingContainer->LootSpawnLocation_Athena.X : BuildingContainer->LootSpawnLocation.X;
			const float LootSpawnLocationY = bIsAthena ? BuildingContainer->LootSpawnLocation_Athena.Y : BuildingContainer->LootSpawnLocation.Y;
			const float LootSpawnLocationZ = bIsAthena ? BuildingContainer->LootSpawnLocation_Athena.Z : BuildingContainer->LootSpawnLocation.Z;

			FVector SpawnLocation = BuildingContainer->K2_GetActorLocation() +
				BuildingContainer->GetActorForwardVector() * LootSpawnLocationX +
				BuildingContainer->GetActorRightVector() * LootSpawnLocationY +
				BuildingContainer->GetActorUpVector() * LootSpawnLocationZ;

			/*FVector BaseTossDirection = UKismetMathLibrary::GetForwardVector(BuildingContainer->LootTossDirection_Athena);

			FVector FinalLocation = BuildingContainer->K2_GetActorLocation() +
				BuildingContainer->GetActorForwardVector() * BuildingContainer->LootFinalLocation.X +
				BuildingContainer->GetActorRightVector() * BuildingContainer->LootFinalLocation.Y +
				BuildingContainer->GetActorUpVector() * BuildingContainer->LootFinalLocation.Z;

			FVector TossDirection = UKismetMathLibrary::GetForwardVector(BuildingContainer->LootTossDirection_Athena);

			FVector TossLocation = BuildingContainer->K2_GetActorLocation() +
				BuildingContainer->GetActorForwardVector() * TossDirection.X +
				BuildingContainer->GetActorRightVector() * TossDirection.Y +
				BuildingContainer->GetActorUpVector() * TossDirection.Z;

			FVector RandomUnitTossDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(BaseTossDirection, BuildingContainer->LootTossConeHalfAngle_Athena);

			TossLocation.X += RandomUnitTossDirection.X * 200.0f;
			TossLocation.Y += RandomUnitTossDirection.Y * 200.0f;
			TossLocation.Z += RandomUnitTossDirection.Z * 200.0f;

			FVector FinalTossLocation = TossLocation + FVector({ LootSpawnLocationX, LootSpawnLocationY, LootSpawnLocationZ });*/

			FVector FinalTossLocation = SpawnLocation;

			UFortWorldItemDefinition* LootTestingData = BuildingContainer->LootTestingData;

			if (LootTestingData)
			{
				FFortItemEntry ItemEntry;
				Inventory::MakeItemEntry(&ItemEntry, LootTestingData, 1, -1, -1, 1.0f);

				UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(ItemEntry.ItemDefinition);

				if (WorldItemDefinition && 
					WorldItemDefinition->ItemType == EFortItemType::WeaponMelee ||
					WorldItemDefinition->ItemType == EFortItemType::WeaponRanged)
				{
					float NewDurability = 1.0f * BuildingContainer->LootedWeaponsDurabilityModifier;

					ItemEntry.SetDurability(NewDurability);
					Inventory::SetStateValue(&ItemEntry, EFortItemEntryState::DurabilityInitialized, 1);
				}

				AFortPickup* Pickup = AFortPickup::CreatePickup(
					BuildingContainer->GetWorld(),
					&ItemEntry,
					&SpawnLocation,
					nullptr,
					nullptr,
					nullptr,
					true,
					(uint32)EFortPickupSourceTypeFlag::Container);

				if (Pickup)
				{
					Pickup->TossPickup(FinalTossLocation, nullptr, 0, true);

					Pickup->bTossedFromContainer = true;
					Pickup->OnRep_TossedFromContainer();
				}

				ItemEntry.FreeItemEntry();
			}
			else if (BuildingContainer->ContainerLootTierKey.IsValid())
			{
				int32 LootLevel = UFortKismetLibrary::GetLootLevel(BuildingContainer);

				TArray<FFortItemEntry> LootToDrops;
				Loots::PickLootDrops(&LootToDrops, LootLevel, BuildingContainer->ContainerLootTierKey, 0, 0, BuildingContainer->StaticGameplayTags, true, false);

				BuildingContainer->HighestRarity = EFortRarity::Handmade;

				for (int32 i = 0; i < LootToDrops.Num(); i++)
				{
					FFortItemEntry LootToDrop = LootToDrops[i];

					UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(LootToDrop.ItemDefinition);

					if (!WorldItemDefinition)
					{
						UFortItemDefinition* ItemDefinition = LootToDrop.ItemDefinition;
						FN_LOG(LogBuildingContainer, Error, L"Attempted to spawn non-world item %s!", ItemDefinition->GetName().c_str());
						continue;
					}

					EFortRarity Rarity = WorldItemDefinition->GetRarity();
					EFortRarity HighestRarity = BuildingContainer->HighestRarity;

					if (HighestRarity < Rarity)
						BuildingContainer->HighestRarity = Rarity;

					if (WorldItemDefinition->ItemType == EFortItemType::WeaponMelee ||
						WorldItemDefinition->ItemType == EFortItemType::WeaponRanged)
					{
						float NewDurability = 1.0f * BuildingContainer->LootedWeaponsDurabilityModifier;

						LootToDrop.SetDurability(NewDurability);
						LootToDrop.SetStateValue(EFortItemEntryState::DurabilityInitialized, 1);
					}

					AFortPickup* Pickup = AFortPickup::CreatePickup(
						BuildingContainer->GetWorld(),
						&LootToDrop,
						&SpawnLocation,
						nullptr,
						nullptr,
						nullptr,
						true,
						(uint32)EFortPickupSourceTypeFlag::Container);

					if (Pickup)
					{
						Pickup->TossPickup(FinalTossLocation, nullptr, 0, true);

						Pickup->bTossedFromContainer = true;
						Pickup->OnRep_TossedFromContainer();
					}
				}

				FFortItemEntry::FreeItemEntries(&LootToDrops);
			}

			if (PlayerPawn)
			{
				AFortPlayerStateZone* PlayerStateZone = Cast<AFortPlayerStateZone>(PlayerPawn->PlayerState);

				// https://imgur.com/sN7Bk4h
				if (PlayerStateZone)
				{

				}

				float LootNoiseRange = BuildingContainer->LootNoiseRange;

				if (LootNoiseRange > 0.0f)
				{
					const FVector& NoiseLocation = BuildingContainer->K2_GetActorLocation();
					UFortAIFunctionLibrary::MakeNoiseEventAtLocation(PlayerPawn, LootNoiseRange, NoiseLocation);
				}
			}
			
			if (!BuildingContainer->bDestroyed)
			{
				BuildingContainer->SetSearchedContainer(PlayerPawn);

				AFortWorldManager* WorldManager = Globals::GetWorldManager();

				// https://imgur.com/ZEhFcUn
				if (BuildingContainer->bPersistToWorld && WorldManager)
				{

				}

				if (PlayerPawn)
				{
					AFortPlayerController* PlayerController = Cast<AFortPlayerController>(PlayerPawn->Controller);

					// https://imgur.com/tlGKgy0
					if (PlayerController)
					{

					}
				}
			}
		}

		BuildingContainer->SearchBounceData.SearchAnimationCount++;
		BuildingContainer->BounceContainer();

		return true;
	}

	/* -------------------------------------- ABuildingSMActor --------------------------------------- */

	/*
	 * Rewrite ABuildingSMActor::SelectMeshSet(FName LootTierKey) (1.1)
	 *
	 * - https://imgur.com/5hzNiB0
	 * - https://imgur.com/FMS3zQK
	 */
	void SelectMeshSet(ABuildingSMActor* BuildingSMActor, FFrame& Stack, void* Ret)
	{
		FName LootTierKey = FName(0);

		Stack.StepCompiledIn(&LootTierKey);

		Stack.Code += Stack.Code != nullptr;

		int32 LootTier = Loots::FindLootTierFromKey(LootTierKey);
		FTierMeshSets* MeshSets = nullptr;

		if (BuildingSMActor->AlternateMeshes.Num() > 0)
		{
			for (int32 i = 0; i < BuildingSMActor->AlternateMeshes.Num(); i++)
			{
				FTierMeshSets* AlternateMeshe = &BuildingSMActor->AlternateMeshes[i];
				int32 Tier = AlternateMeshe->Tier;

				if (Tier <= LootTier && (!MeshSets || MeshSets->Tier < Tier))
				{
					if (AlternateMeshe->MeshSets.Num() <= 0)
					{
						FN_LOG(LogBuildingSMActor, Warning, L"No Alternative Mesh available for Building: %s at LootTier: %d", BuildingSMActor->GetName().c_str(), Tier);
					}
					else
					{
						MeshSets = AlternateMeshe;
					}
				}
			}

			if (MeshSets)
			{
				int32 AltMeshIdx = BuildingSMActor->AltMeshIdx;

				if (AltMeshIdx != -1)
				{
					BuildingSMActor->SetMeshSet(MeshSets->MeshSets[AltMeshIdx]);
				}
			}
		}

		FN_LOG(LogBuildingSMActor, Debug, L"ABuildingSMActor::SelectMeshSet(FName LootTierKey) Building: %s, AltMeshIdx: %d", BuildingSMActor->GetName().c_str(), BuildingSMActor->AltMeshIdx);
	}


	/*
	 * Rewrite ABuildingSMActor::PostUpdate (1.1)
	 *
	 * - https://imgur.com/B3MAqOw
	 * - https://imgur.com/AbJvx6u
	 * - https://imgur.com/EyyvQGv
	 */
	void ABuildingSMActor_PostUpdate(ABuildingSMActor* BuildingSMActor)
	{
		EFortBuildingPersistentState PersistentState = EFortBuildingPersistentState::Default;
		FName LootTierKey = BuildingSMActor->DestructionLootTierKey;

		if (BuildingSMActor->DestructionLootTierKey.IsValid())
		{
			BuildingSMActor->SelectMeshSet(LootTierKey);
		}
		else
		{
			int32 LootTier = 0;
			int32 ChooseLootTier = 0;

			if (BuildingSMActor->DestructionLootTierGroup.IsValid())
			{
				LootTier = -1;

				if (BuildingSMActor->DestructionLootTierChosenQuotaInfo.LootTierKey.ComparisonIndex > 0 ||
					BuildingSMActor->DestructionLootTierChosenQuotaInfo.LootTierKey.Number > 0)
				{
					ChooseLootTier = BuildingSMActor->DestructionLootTierChosenQuotaInfo.LootTier;
					LootTierKey = BuildingSMActor->DestructionLootTierChosenQuotaInfo.LootTierKey;

					LootTier = ChooseLootTier;
				}
				else
				{
					int32 LootLevel = UFortKismetLibrary::GetLootLevel(BuildingSMActor);

					Loots::PickLootTierKeyAndLootTierFromTierGroup(
						&BuildingSMActor->DestructionLootTierKey,
						&LootTier, 
						BuildingSMActor->DestructionLootTierGroup,
						LootLevel, 
						0, 
						-1, 
						BuildingSMActor->StaticGameplayTags
					);

					ChooseLootTier = LootTier;
				}

				BuildingSMActor->SelectMeshSet(ChooseLootTier);

				if (Loots::IsLootDropPossible(LootTierKey, L"ABuildingSMActor::AttemptSpawnResources", 0))
				{
					// Idk what it does
					// https://imgur.com/bfa7h9o
				}
				else
				{
					LootTierKey = FName(0);
					PersistentState = EFortBuildingPersistentState::Searched;
				}

				if (BuildingSMActor->AltMeshIdx != -1 && BuildingSMActor->bPersistToWorld)
				{
					// Idk what it does
					// https://imgur.com/6sCJOpg
				}
			}
		}

		FN_LOG(LogBuildingSMActor, Debug, L"ABuildingSMActor::PostUpdate() Building: %s, AltMeshIdx: %d", BuildingSMActor->GetPathName().CStr(), BuildingSMActor->AltMeshIdx);

		ABuildingSMActor_PostUpdateOG(BuildingSMActor);
	}

	/* --------------------------------------- ABuildingActor ---------------------------------------- */

	/*
	 * Rewrite ABuildingSMActor::ResourceHarvesting (1.1)
	 *
	 * - PS: Idk why but in hook the real function is called only on certain actors.
	 * 
	 * - https://imgur.com/rtNXcue
	 * - https://imgur.com/bwmrN5k
	 * - https://imgur.com/2VUBSmw
	 * - https://imgur.com/xLp51BB
	 * - https://imgur.com/dBXzVy6
	 * - https://imgur.com/eqMtWQd
	 */
	void OnDamageServer(
		ABuildingActor* BuildingActor, 
		float Damage, 
		const FGameplayTagContainer& DamageTags, 
		const FVector& Momentum, 
		const FHitResult& HitInfo, 
		AController* InstigatedBy, 
		AActor* DamageCauser, 
		const FGameplayEffectContextHandle& EffectContext
	)
	{
		OnDamageServerOG(
			BuildingActor,
			Damage,
			DamageTags,
			Momentum,
			HitInfo,
			InstigatedBy,
			DamageCauser,
			EffectContext);

		ABuildingSMActor* BuildingSMActor = Cast<ABuildingSMActor>(BuildingActor);
		AFortPlayerController* PlayerController = Cast<AFortPlayerController>(InstigatedBy);
		AFortWeapon* Weapon = Cast<AFortWeapon>(DamageCauser);
		
		if (!BuildingSMActor || !PlayerController || !Weapon)
			return;

		AFortPlayerPawn* PlayerPawn = PlayerController->MyFortPawn;

		if (!Weapon->WeaponData->IsA(UFortWeaponMeleeItemDefinition::StaticClass()) || 
			!BuildingSMActor->bAllowResourceDrop ||
			!PlayerPawn)
			return;

		UFortResourceItemDefinition* ResourceItemDefinition = UFortKismetLibrary::K2_GetResourceItemDefinition(BuildingSMActor->ResourceType);

		int32 ResourceDropAmount = 0;
		float ResourceRatio = 0.0f;

		if (ResourceItemDefinition)
		{
			if (BuildingSMActor->MaxResourcesToSpawn < 0)
				BuildingSMActor->MaxResourcesToSpawn = BuildingSMActor->DetermineMaxResourcesToSpawn();

			float MaxResourcesToSpawn = BuildingSMActor->MaxResourcesToSpawn;
			float MaxHealth = BuildingSMActor->GetMaxHealth();

			ResourceRatio = MaxResourcesToSpawn / MaxHealth;
			ResourceDropAmount = (int32)(ResourceRatio * Damage);
		}

		bool bHasHealthLeft = BuildingSMActor->HasHealthLeft();
		bool bDestroyed = false;

		if (!bHasHealthLeft)
		{
			bDestroyed = true;

			int32 MinResourceCount = 0;

			if (!ResourceItemDefinition || (MinResourceCount = 1, ResourceRatio == 0.0))
				MinResourceCount = 0;

			if (ResourceDropAmount < MinResourceCount)
				ResourceDropAmount = MinResourceCount;

			if (BuildingSMActor->DestructionLootTierKey.IsValid())
			{
				int32 LootLevel = UFortKismetLibrary::GetLootLevel(BuildingSMActor);

				TArray<FFortItemEntry> LootToDrops;
				Loots::PickLootDrops(&LootToDrops, LootLevel, BuildingSMActor->DestructionLootTierKey, 0, 0, BuildingSMActor->StaticGameplayTags, true, false);

				for (int32 i = 0; i < LootToDrops.Num(); i++)
				{
					FFortItemEntry LootToDrop = LootToDrops[i];

					UFortWorldItemDefinition* WorldItemDefinition = Cast<UFortWorldItemDefinition>(LootToDrop.ItemDefinition);

					if (!WorldItemDefinition)
					{
						FN_LOG(LogBuildingSMActor, Error, L"Loot tier %s dropped entry with no item data!", BuildingSMActor->DestructionLootTierGroup.ToString().c_str());
						continue;
					}

					FVector BuildingSMActorLocation = BuildingSMActor->K2_GetActorLocation();
					FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();

					BuildingSMActorLocation.X += RandomDirection.X * 200.0f;
					BuildingSMActorLocation.Y += RandomDirection.Y * 200.0f;
					BuildingSMActorLocation.Z += RandomDirection.Z * 200.0f;

					FFortItemEntry ItemEntry;
					Inventory::MakeItemEntry(&ItemEntry, WorldItemDefinition, LootToDrop.Count, LootToDrop.Level, LootToDrop.LoadedAmmo, LootToDrop.Durability);
					Inventory::SetStateValue(&ItemEntry, EFortItemEntryState::DoNotShowSpawnParticles, 1);

					AFortPickup* Pickup = AFortPickup::CreatePickup(
						PlayerController->GetWorld(),
						&ItemEntry,
						&BuildingSMActorLocation,
						nullptr,
						nullptr,
						nullptr,
						true,
						(uint32)EFortPickupSourceTypeFlag::Destruction);

					if (Pickup)
					{
						FVector ConeDir = { 0, 0, 0 };
						FVector VectorInCone = UKismetMathLibrary::RandomUnitVectorInConeInRadians(ConeDir, 1.0f);

						float FlyTime = Globals::GenFlyTime();
						Pickup->SetPickupTarget(PlayerPawn, (FlyTime + i * 0.30000001192092896f), VectorInCone, true);
					}

					ItemEntry.FreeItemEntry();
				}
			}
		}
		
		if (ResourceDropAmount > 0)
		{
			FFortItemEntry ItemEntry;
			ItemEntry.CreateDefaultItemEntry(ResourceItemDefinition, ResourceDropAmount, 0);

			FVector BuildingSMActorLocation = BuildingSMActor->K2_GetActorLocation();
			FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();

			BuildingSMActorLocation.X += RandomDirection.X * 200.0f;
			BuildingSMActorLocation.Y += RandomDirection.Y * 200.0f;
			BuildingSMActorLocation.Z += RandomDirection.Z * 200.0f;

			Inventory::SetStateValue(&ItemEntry, EFortItemEntryState::DoNotShowSpawnParticles, 1);
			Inventory::SetStateValue(&ItemEntry, EFortItemEntryState::ShouldShowItemToast, 1);

			if (BuildingSMActor->OwnerPersistentID == -1)
			{
				// Idk what it does
				// https://imgur.com/HC3hhbt
			}

			Inventory::AddInventoryItem(PlayerController, ItemEntry);
			PlayerController->ClientReportDamagedResourceBuilding(BuildingSMActor, BuildingSMActor->ResourceType, ResourceDropAmount, bDestroyed, (Damage == 100.0f));

			ItemEntry.FreeItemEntry();
		}
	}

	void OnDeathServer(
		ABuildingActor* BuildingActor,
		float Damage,
		const FGameplayTagContainer& DamageTags,
		const FVector& Momentum,
		const FHitResult& HitInfo,
		AController* InstigatedBy,
		AActor* DamageCauser,
		const FGameplayEffectContextHandle& EffectContext
	)
	{
		OnDeathServerOG(
			BuildingActor,
			Damage,
			DamageTags,
			Momentum,
			HitInfo,
			InstigatedBy,
			DamageCauser,
			EffectContext
		);

		ABuildingContainer* BuildingContainer = Cast<ABuildingContainer>(BuildingActor);

		if (!BuildingContainer)
			return;

		/*if (!BuildingContainer->bAlreadySearched)
			BuildingContainer->SpawnLoot(nullptr);*/
	}

	void InitBuildingActor()
	{
		ABuildingContainer* BuildingContainerDefault = ABuildingContainer::GetDefaultObj();
		UClass* BuildingContainerClass = ABuildingContainer::StaticClass();

		/* ------------------------------------- ABuildingContainer -------------------------------------- */
		
		UFunction* EditorOnlyRemoveInstanceMaterialScalarParameterFunc = BuildingContainerClass->GetFunction("BuildingSMActor", "EditorOnlyRemoveInstanceMaterialScalarParameter");
		MinHook::HookFunctionExec(EditorOnlyRemoveInstanceMaterialScalarParameterFunc, SelectMeshSet, nullptr);

		MinHook::HookVTable(BuildingContainerDefault, 0xF5, ABuildingContainer_PostUpdate, (LPVOID*)(&ABuildingContainer_PostUpdateOG), "ABuildingContainer::PostUpdate");
		MinHook::HookVTable(BuildingContainerDefault, 0x1B9, SpawnLoot, nullptr, "ABuildingContainer::SpawnLoot");

		/* -------------------------------------- ABuildingSMActor --------------------------------------- */
		
		uintptr_t AddressABuildingSMActor_PostUpdate = MinHook::FindPattern(Patterns::ABuildingSMActor_PostUpdate);

		MH_CreateHook((LPVOID)(AddressABuildingSMActor_PostUpdate), ABuildingSMActor_PostUpdate, (LPVOID*)(&ABuildingSMActor_PostUpdateOG));
		MH_EnableHook((LPVOID)(AddressABuildingSMActor_PostUpdate));

		// MinHook::HookVTable(BuildingContainerDefault, 0x146, ResourceHarvesting, nullptr, "ABuildingSMActor::ResourceHarvesting");

		/* --------------------------------------- ABuildingActor ---------------------------------------- */

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0x1371CD0), OnDamageServer, (LPVOID*)(&OnDamageServerOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0x1371CD0));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0x1372290), OnDeathServer, (LPVOID*)(&OnDeathServerOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0x1372290));

		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitBuildingActor Success!");
	}
}