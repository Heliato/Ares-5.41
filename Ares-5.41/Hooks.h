#pragma once

enum ENetMode
{
	NM_Standalone,
	NM_DedicatedServer,
	NM_ListenServer,
	NM_Client,
	NM_MAX,
};

namespace Hooks
{
	ABuildingTrap* (*SpawnDecoOG)(AFortDecoTool* DecoTool, UClass* Class, const FVector& Location, const FRotator& Rotation, ABuildingSMActor* AttachedActor, EBuildingAttachmentType InBuildingAttachmentType);
	void (*GetPlayerViewPoint)(APlayerController* PlayerController, FVector& out_Location, FRotator& out_Rotation);
	void (*ProcessEvent)(UObject* Object, UFunction* Function, void* Parms);
	void (*DispatchRequest)(UMcpProfileGroup* McpProfileGroup, FProfileHttpRequest* ProfileHttpRequest);
	void (*PickupCombine)(AFortPickup* Pickup);
	void (*PickupDelay)(AFortPickup* Pickup);

	uintptr_t GIsClient()
	{
		return __int64(GetModuleHandleW(0)) + 0x531F204;
	}

	uintptr_t GIsServer()
	{
		return __int64(GetModuleHandleW(0)) + 0x531F205;
	}

	ENetMode ReturnNetMode()
	{
		return ENetMode::NM_DedicatedServer;
	}

	bool LocalSpawnPlayActorHook()
	{
		FN_LOG(LogHooks, Log, L"LocalSpawnPlayActorHook!");
		return true;
	}

	bool KickPlayerHook(AFortGameSession* GameSession, AFortPlayerController* PlayerController)
	{
		return false;
	}

	__int64* ChangingGameSessionIdHook(__int64 a1, __int64 a2)
	{
		return 0;
	}

	char CollectGarbageInternalHook()
	{
		return 0;
	}

	void DispatchRequestHook(UMcpProfileGroup* McpProfileGroup, FProfileHttpRequest* ProfileHttpRequest)
	{
		*(int32*)(__int64(ProfileHttpRequest) + 0x28) = 3;

		DispatchRequest(McpProfileGroup, ProfileHttpRequest);
	}

	FVector GetPawnViewLocation(APawn* Pawn)
	{
		return Pawn->K2_GetActorLocation() + FVector(0.f, 0.f, Pawn->BaseEyeHeight);
	}

	void GetPlayerViewPointHook(APlayerController* PlayerController, FVector& out_Location, FRotator& out_Rotation)
	{
		APawn* Pawn = PlayerController->Pawn;
		ASpectatorPawn* SpectatorPawn = PlayerController->GetSpectatorPawn();

		if (Pawn)
		{
			out_Location = Pawn->K2_GetActorLocation();
			out_Rotation = PlayerController->GetControlRotation();
			return;
		}
		else if (SpectatorPawn && PlayerController->HasAuthority())
		{
			out_Location = SpectatorPawn->K2_GetActorLocation();
			out_Rotation = ((APlayerController*)SpectatorPawn->Owner)->GetControlRotation();
			return;
		}
		else if (!SpectatorPawn && !Pawn)
		{
			out_Location = PlayerController->LastSpectatorSyncLocation;
			out_Rotation = PlayerController->LastSpectatorSyncRotation;
			return;
		}

		GetPlayerViewPoint(PlayerController, out_Location, out_Rotation);
	}

	int32 CubeIndex = 561;

	bool bLogs = false;

	void ProcessEventHook(UObject* Object, UFunction* Function, void* Parms)
	{
		if (!Object || !Function)
		{
			ProcessEvent(Object, Function, Parms);
			return;
		}

		bool bCallOG = true;

		const std::string& FunctionName = Function->GetName();

		if (FunctionName.contains("ServerUpdatePhysicsParams"))
		{
			AFortAthenaVehicle* AthenaVehicle = (AFortAthenaVehicle*)Object;
			auto Params = (Params::FortAthenaVehicle_ServerUpdatePhysicsParams*)Parms;

			if (!AthenaVehicle)
				return;

			UPrimitiveComponent* RootComponent = (UPrimitiveComponent*)AthenaVehicle->RootComponent;

			if (RootComponent)
			{
				FReplicatedAthenaVehiclePhysicsState InState = Params->InState;

				// From Reboot
				InState.Rotation.X -= 2.5;
				InState.Rotation.Y /= 0.3;
				InState.Rotation.Z -= -2.0;
				InState.Rotation.W /= -1.2;

				FTransform Transform{};
				Transform.Translation = InState.Translation;
				Transform.Rotation = InState.Rotation;
				Transform.Scale3D = FVector{ 1, 1, 1 };

				RootComponent->K2_SetWorldTransform(Transform, false, nullptr, true);
				RootComponent->SetPhysicsLinearVelocity(InState.LinearVelocity, 0, FName());
				RootComponent->SetPhysicsAngularVelocity(InState.AngularVelocity, 0, FName());
			}
		}
		else if (FunctionName.contains("OnWorldReady"))
		{
			AFortGameModeAthena* GameModeAthena = Cast<AFortGameModeAthena>(Globals::GetGameMode());

			if (!GameModeAthena)
				return;

			AFortGameStateAthena* GameStateAthena = Cast<AFortGameStateAthena>(GameModeAthena->GameState);

			if (!GameStateAthena)
				return;

			if (!GameModeAthena->bWorldIsReady)
			{
				float ServerWorldTimeSeconds = UGameplayStatics::GetTimeSeconds(GameModeAthena) + GameStateAthena->ServerWorldTimeSecondsDelta;
				float Duration = 900.0f; // Seconds

				UFortPlaylistAthena* PlaylistAthena = Globals::GetPlaylist();

				if (PlaylistAthena && GameStateAthena && false)
				{
					GameStateAthena->WarmupCountdownStartTime = Duration;
					GameStateAthena->WarmupCountdownEndTime = ServerWorldTimeSeconds + Duration;

					GameModeAthena->WarmupEarlyCountdownDuration = ServerWorldTimeSeconds;
					GameModeAthena->WarmupCountdownDuration = Duration;

					for (int32 i = 0; i < PlaylistAthena->AdditionalLevels.Num(); i++)
					{
						TSoftObjectPtr<UWorld> AdditionalLevel = PlaylistAthena->AdditionalLevels[i];

						FName FoundationName = AdditionalLevel.ObjectID.AssetPathName;
						if (!FoundationName.IsValid()) continue;

						bool bSuccess = false;
						ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GameStateAthena, AdditionalLevel, FVector(), FRotator(), &bSuccess);

						if (bSuccess)
						{
							FName LevelName = AdditionalLevel.ObjectID.AssetPathName;
							if (!LevelName.IsValid()) continue;

							GameStateAthena->AdditionalPlaylistLevelsStreamed.Add(LevelName);
						}
					}

					GameStateAthena->OnRep_AdditionalPlaylistLevelsStreamed();
				}

				Functions::InitializeTreasureChests();
				Functions::InitializeAmmoBoxs();
				Functions::InitializeLlamas();
				Functions::InitializeConsumableBGAs();

				Functions::FillVendingMachines();

				FN_LOG(LogHooks, Log, L"OnWorldReady called!");
				GameModeAthena->bWorldIsReady = true;
			}
		}

		if (bLogs)
		{
			if (!FunctionName.contains("Tick") &&
				!FunctionName.contains("Visual") &&
				!FunctionName.contains("Clown Spinner") &&
				!FunctionName.contains("CustomStateChanged") &&
				!FunctionName.contains("ReceiveBeginPlay") &&
				!FunctionName.contains("OnAttachToBuilding") &&
				!FunctionName.contains("OnWorldReady") &&
				!FunctionName.contains("K2_GetActorLocation") &&
				!FunctionName.contains("ReceiveDrawHUD") &&
				!FunctionName.contains("ServerUpdateCamera") &&
				!FunctionName.contains("ServerMove") &&
				!FunctionName.contains("ContrailCheck") &&
				!FunctionName.contains("GetViewTarget") &&
				!FunctionName.contains("GetAllActorsOfClass") &&
				!FunctionName.contains("ClientAckGoodMove") &&
				!FunctionName.contains("ReadyToEndMatch") &&
				!FunctionName.contains("Check Closest Point") &&
				!FunctionName.contains("ServerTriggerCombatEvent") &&
				!FunctionName.contains("UpdateTime") &&
				!FunctionName.contains("OnUpdateMusic") &&
				!FunctionName.contains("UpdateStateEvent") &&
				!FunctionName.contains("ServerTouchActiveTime") &&
				!FunctionName.contains("OnCheckIfSurrounded") &&
				!FunctionName.contains("ServerFireAIDirectorEventBatch") &&
				!FunctionName.contains("ServerTriggerCombatEventBatch") &&
				!FunctionName.contains("UserConstructionScript") &&
				!FunctionName.contains("K2_OnReset") &&
				!FunctionName.contains("K2_OnEndViewTarget") &&
				!FunctionName.contains("K2_OnBecomeViewTarget") &&
				!FunctionName.contains("ReceiveUnpossessed") &&
				!FunctionName.contains("ClientGotoState") &&
				!FunctionName.contains("K2_OnEndViewTarget") &&
				!FunctionName.contains("K2_OnBecomeViewTarget") &&
				!FunctionName.contains("ClientSetViewTarget") &&
				!FunctionName.contains("ServerClientPawnLoaded") &&
				!FunctionName.contains("ReceiveEndPlay") &&
				!FunctionName.contains("OnPerceptionStimuliSourceEndPlay") &&
				!FunctionName.contains("HandleOnHUDElementVisibilityChanged") &&
				!FunctionName.contains("OnHUDElementVisibilityChanged") &&
				!FunctionName.contains("HandleInteractionChanged") &&
				!FunctionName.contains("BlueprintModifyCamera") &&
				!FunctionName.contains("BlueprintModifyPostProcess") &&
				!FunctionName.contains("ServerSetSpectatorLocation") &&
				!FunctionName.contains("ServerFireAIDirectorEvent") &&
				!FunctionName.contains("ServerTryActivateAbility") &&
				!FunctionName.contains("ClientActivateAbilitySucceed") &&
				!FunctionName.contains("ServerSetSpectatorLocation") &&
				!FunctionName.contains("CanJumpInternal") &&
				!FunctionName.contains("K2_OnMovementModeChanged") &&
				!FunctionName.contains("OnJumped") &&
				!FunctionName.contains("ServerModifyStat") &&
				!FunctionName.contains("OnLanded") &&
				!FunctionName.contains("ReceiveHit") &&
				!FunctionName.contains("OnWalkingOffLedge") &&
				!FunctionName.contains("ServerEndAbility") &&
				!FunctionName.contains("Execute") &&
				!FunctionName.contains("OnDamagePlayEffects") &&
				!FunctionName.contains("OnMontageStarted") &&
				!FunctionName.contains("OnNewDamageNumber") &&
				!FunctionName.contains("BP_GetTokenizedDescriptionText") &&
				!FunctionName.contains("GameplayCue_InstantDeath") &&
				!FunctionName.contains("K2_GetActorRotation") &&
				!FunctionName.contains("K2_DestroyActor") &&
				!FunctionName.contains("OnDetachFromBuilding") &&
				!FunctionName.contains("OnRep_bAlreadySearched") &&
				!FunctionName.contains("OnSetSearched") &&
				!FunctionName.contains("GetAircraft") &&
				!FunctionName.contains("BeginSpawningActorFromClass") &&
				!FunctionName.contains("BlueprintInitializeAnimation") &&
				!FunctionName.contains("BlueprintUpdateAnimation") &&
				!FunctionName.contains("BlueprintPostEvaluateAnimation") &&
				!FunctionName.contains("FinishSpawningActor") &&
				!FunctionName.contains("PawnUniqueIDSet") &&
				!FunctionName.contains("OnRep_Owner") &&
				!FunctionName.contains("OnRep_Pawn") &&
				!FunctionName.contains("Possess") &&
				!FunctionName.contains("ReceivePossessed") &&
				!FunctionName.contains("ClientRestart") &&
				!FunctionName.contains("SetControlRotation") &&
				!FunctionName.contains("ClientRetryClientRestart") &&
				!FunctionName.contains("ExecuteUbergraph_PlayerPawn_Athena_Generic") &&
				!FunctionName.contains("ExecuteUbergraph_PlayerPawn_Athena") &&
				!FunctionName.contains("ServerAcknowledgePossession") &&
				!FunctionName.contains("IsInAircraft") &&
				!FunctionName.contains("FindPlayerStart") &&
				!FunctionName.contains("SpawnDefaultPawnFor") &&
				!FunctionName.contains("MustSpectate") &&
				!FunctionName.contains("GetDefaultPawnClassForController") &&
				!FunctionName.contains("On Game Phase Change") &&
				!FunctionName.contains("ClientAdjustPosition") &&
				!FunctionName.contains("Movement Audio Crossfader__UpdateFunc") &&
				!FunctionName.contains("Holding Audio Crossfader__UpdateFunc") &&
				!FunctionName.contains("OnUpdateDirectionalLightForTimeOfDay") &&
				!FunctionName.contains("OnMontageEnded") &&
				!FunctionName.contains("ServerCancelAbility") &&
				!FunctionName.contains("K2_ActivateAbility") &&
				!FunctionName.contains("ServerHandleMissionEvent_ToggledCursorMode") &&
				!FunctionName.contains("OnBlendOut_") &&
				!FunctionName.contains("ClientEndAbility") &&
				!FunctionName.contains("OnSafeZoneStateChange") &&
				!FunctionName.contains("ClientVeryShortAdjustPosition") &&
				!FunctionName.contains("OnDayPhaseChange") &&
				!FunctionName.contains("On Day Phase Change") &&
				!FunctionName.contains("K2_OnStartCrouch") &&
				!FunctionName.contains("K2_OnEndCrouch") &&
				!FunctionName.contains("On Player Won") &&
				!FunctionName.contains("ClientFinishedInteractionInZone") &&
				!FunctionName.contains("ClientReceiveKillNotification") &&
				!FunctionName.contains("ReceiveCopyProperties") &&
				!FunctionName.contains("K2_OnLogout") &&
				!FunctionName.contains("ClientReceiveLocalizedMessage") &&
				!FunctionName.contains("ClientCancelAbility") &&
				!FunctionName.contains("ServerFinishedInteractionInZoneReport") &&
				!FunctionName.contains("FallingTimeline__UpdateFunc") &&
				!FunctionName.contains("BndEvt__InterceptCollision_K2Node_ComponentBoundEvent_5_ComponentBeginOverlapSignature__DelegateSignature") &&
				!FunctionName.contains("ReceiveActorBeginOverlap") &&
				!FunctionName.contains("Conv_StringToName") &&
				!FunctionName.contains("OnRep_GamePhase") &&
				!FunctionName.contains("K2_OnSetMatchState") &&
				!FunctionName.contains("StartPlay") &&
				!FunctionName.contains("StartMatch") &&
				!FunctionName.contains("OnAircraftEnteredDropZone") &&
				!FunctionName.contains("ServerShortTimeout") &&
				!FunctionName.contains("UpdateStateWidgetContent") &&
				!FunctionName.contains("PreConstruct") &&
				!FunctionName.contains("Construct") &&
				!FunctionName.contains("OnCurrentTextStyleChanged") &&
				!FunctionName.contains("UpdateButtonState") &&
				!FunctionName.contains("OnBangStateChanged") &&
				!FunctionName.contains("OnPlayerInfoChanged") &&
				!FunctionName.contains("Update") &&
				!FunctionName.contains("OnBeginIntro") &&
				!FunctionName.contains("HandleQuickBarChangedBP") &&
				!FunctionName.contains("HandleInventoryUpdatedEvent") &&
				!FunctionName.contains("OnActivated") &&
				!FunctionName.contains("OnBeginOutro") &&
				!FunctionName.contains("HandleActiveWidgetDeactivated") &&
				!FunctionName.contains("OnDeactivated") &&
				!FunctionName.contains("OnStateStarted") &&
				!FunctionName.contains("SetRenderTransform") &&
				!FunctionName.contains("OnAnimationFinished") &&
				!FunctionName.contains("ReadyToStartMatch") &&
				!FunctionName.contains("SetWidthOverride") &&
				!FunctionName.contains("SetHeightOverride") &&
				!FunctionName.contains("HandleMinimizeFinished") &&
				!FunctionName.contains("ServerUpdateLevelVisibility") &&
				!FunctionName.contains("OnDayPhaseChanged") &&
				!FunctionName.contains("On Game Phase Step Changed") &&
				!FunctionName.contains("SetColorAndOpacity") &&
				!FunctionName.contains("OnAnimationStarted") &&
				!FunctionName.contains("UpdateMessaging") &&
				!FunctionName.contains("ServerSendLoadoutConfig") &&
				!FunctionName.contains("CalculateBaseMagnitude") &&
				!FunctionName.contains("ClientRegisterWithParty") &&
				!FunctionName.contains("InitializeHUDForPlayer") &&
				!FunctionName.contains("ClientSetHUD") &&
				!FunctionName.contains("ClientEnableNetworkVoice") &&
				!FunctionName.contains("ClientUpdateMultipleLevelsStreamingStatus") &&
				!FunctionName.contains("ClientFlushLevelStreaming") &&
				!FunctionName.contains("ClientOnGenericPlayerInitialization") &&
				!FunctionName.contains("ClientCapBandwidth") &&
				!FunctionName.contains("K2_PostLogin") &&
				!FunctionName.contains("OnRep_bHasStartedPlaying") &&
				!FunctionName.contains("ServerChoosePart") &&
				!FunctionName.contains("SetOwner") &&
				!FunctionName.contains("OnRep_QuickBar") &&
				!FunctionName.contains("HandleStartingNewPlayer") &&
				!FunctionName.contains("ServerUpdateMultipleLevelsVisibility") &&
				!FunctionName.contains("ServerSetPartyOwner") &&
				!FunctionName.contains("PlayerCanRestart") &&
				!FunctionName.contains("ServerCreateCombatManager") &&
				!FunctionName.contains("ServerCreateAIDirectorDataManager") &&
				!FunctionName.contains("EnableSlot") &&
				!FunctionName.contains("DisableSlot") &&
				!FunctionName.contains("ServerSetShowHeroBackpack") &&
				!FunctionName.contains("ServerSetShowHeroHeadAccessories") &&
				!FunctionName.contains("ServerSetClientHasFinishedLoading") &&
				!FunctionName.contains("ServerReadyToStartMatch") &&
				!FunctionName.contains("Received_Notify") &&
				!FunctionName.contains("Received_NotifyBegin") &&
				!FunctionName.contains("AnimNotify_LeftFootStep") &&
				!FunctionName.contains("AnimNotify_RightFootStep") &&
				!FunctionName.contains("Completed_") &&
				!FunctionName.contains("InputActionHoldStopped") &&
				!FunctionName.contains("ServerCurrentMontageSetPlayRate") &&
				!FunctionName.contains("ServerSetReplicatedTargetData") &&
				!FunctionName.contains("Triggered_") &&
				!FunctionName.contains("ActorHasTag") &&
				!FunctionName.contains("RandomIntegerInRange") &&
				!FunctionName.contains("GetItemDefinitionBP") &&
				!FunctionName.contains("CreateTemporaryItemInstanceBP") &&
				!FunctionName.contains("SetOwningControllerForTemporaryItem") &&
				!FunctionName.contains("OnRep_PrimaryQuickBar") &&
				!FunctionName.contains("OnRep_SecondaryQuickBar") &&
				!FunctionName.contains("ServerSetupWeakSpotsOnBuildingActor") &&
				!FunctionName.contains("OnStartDirectionEffect") &&
				!FunctionName.contains("SetReplicates") &&
				!FunctionName.contains("ServerCurrentMontageSetNextSectionName") &&
				!FunctionName.contains("NetFadeOut") &&
				!FunctionName.contains("OnFadeOut") &&
				!FunctionName.contains("NetOnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("GameplayCue") &&
				!FunctionName.contains("ReceiveActorEndOverlap") &&
				!FunctionName.contains("PhysicsVolumeChanged") &&
				!FunctionName.contains("ServerAddItemInternal") &&
				!FunctionName.contains("FortClientPlaySound") &&
				!FunctionName.contains("OnCapsuleBeginOverlap") &&
				!FunctionName.contains("GetPlayerController") &&
				!FunctionName.contains("TossPickup") &&
				!FunctionName.contains("OnRep_PrimaryPickupItemEntry") &&
				!FunctionName.contains("ServerActivateSlotInternal") &&
				!FunctionName.contains("EquipWeaponDefinition") &&
				!FunctionName.contains("OnInitAlteration") &&
				!FunctionName.contains("OnInitCosmeticAlterations") &&
				!FunctionName.contains("K2_OnUnEquip") &&
				!FunctionName.contains("GetItemGuid") &&
				!FunctionName.contains("InternalServerSetTargeting") &&
				!FunctionName.contains("ServerReleaseInventoryItemKey") &&
				!FunctionName.contains("OnPawnMontageBlendingOut") &&
				!FunctionName.contains("OnSetTargeting") &&
				!FunctionName.contains("OnRep_DefaultMetadata") &&
				!FunctionName.contains("GetDataTableRowNames") &&
				!FunctionName.contains("GetMaxDurability") &&
				!FunctionName.contains("OnRep_PickupLocationData") &&
				!FunctionName.contains("GetControlRotation") &&
				!FunctionName.contains("OnVisibilitySetEvent") &&
				!FunctionName.contains("ShouldShowSoundIndicator") &&
				!FunctionName.contains("WaitForPawn") &&
				!FunctionName.contains("OnProjectileStopDelegate") &&
				!FunctionName.contains("Handle Parachute Audio State") &&
				!FunctionName.contains("GetDistanceTo") &&
				!FunctionName.contains("GetSpectatorPawn") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("OnHitCrack") &&
				!FunctionName.contains("EvaluateGraphExposedInputs_ExecuteUbergraph_Fortnite_M_Avg_Player_AnimBlueprint_AnimGraphNode_"))
			{
				FN_LOG(Logs, Log, L"FunctionName: [%s], Object: [%s]", Function->GetFullName().c_str(), Object->GetName().c_str());
			}
		}

		if (bCallOG)
			ProcessEvent(Object, Function, Parms);
	}

	ABuildingTrap* SpawnDeco(AFortDecoTool* DecoTool, UClass* Class, const FVector& Location, const FRotator& Rotation, ABuildingSMActor* AttachedActor, EBuildingAttachmentType InBuildingAttachmentType)
	{
		ABuildingTrap* Result = SpawnDecoOG(DecoTool, Class, Location, Rotation, AttachedActor, InBuildingAttachmentType);

		uintptr_t Offset = uintptr_t(_ReturnAddress()) - InSDKUtils::GetImageBase();
		uintptr_t IdaAddress = Offset + 0x7FF66E650000ULL;

		FN_LOG(LogMinHook, Log, L"SpawnDeco - called in Offset [0x%llx], IdaAddress [%p]", (unsigned long long)Offset, IdaAddress);

		if (Result)
		{
			// 7FF66F971DB0
			AFortPlayerController* (*GetPlayerControllerFromInstigator)(AFortDecoTool* DecoTool) = decltype(GetPlayerControllerFromInstigator)(0x1321DB0 + uintptr_t(GetModuleHandle(0)));
			AFortPlayerController* PlayerController = GetPlayerControllerFromInstigator(DecoTool);

			if (!PlayerController)
			{
				FN_LOG(LogHooks, Error, L"[AFortDecoTool::SpawnDeco] Failed to get PlayerController!");
				return Result;
			}

			AFortPlayerStateAthena* PlayerState = (AFortPlayerStateAthena*)PlayerController->PlayerState;

			if (!PlayerState)
			{
				FN_LOG(LogHooks, Error, L"[AFortDecoTool::SpawnDeco] Failed to get PlayerState!");
				return Result;
			}

			Result->bPlayerPlaced = true;
			Result->Team = PlayerState->TeamIndex;
		}

		return Result;
	}

	// 7FF66F481290
	UClass** sub_7FF66F481290Hook(__int64 a1, UClass** OutGameSessionClass)
	{
		//*OutGameSessionClass = AFortGameSessionDedicatedAthena::StaticClass();
		//*OutGameSessionClass = AFortGameSessionDedicated::StaticClass();
		*OutGameSessionClass = AFortGameSession::StaticClass();
		return OutGameSessionClass;
	}

	void InitalizePoiManager(AFortPoiManager* PoiManager)
	{
		uintptr_t Offset = uintptr_t(_ReturnAddress()) - InSDKUtils::GetImageBase();
		uintptr_t IdaAddress = Offset + 0x7FF66E650000ULL;

		FN_LOG(LogMinHook, Log, L"Function [InitalizePoiManager] successfully hooked with Offset [0x%llx], IdaAddress [%p], GameMode: [%s]", (unsigned long long)Offset, IdaAddress, PoiManager->GetName().c_str());
	}

	// 7FF66F6694B0
	void (*Restart)(AFortGameSessionDedicated* GameSession);
	void RestartHook(AFortGameSessionDedicated* GameSession)
	{
		Restart(GameSession);
	}

	void CollectGarbageHook()
	{

	}

	void InitHook()
	{
		static auto FortPickupAthenaDefault = AFortPickupAthena::GetDefaultObj();
		static auto FortPlayerPawnAthenaDefault = AFortPlayerPawnAthena::GetDefaultObj();

		uintptr_t AddressLocalSpawnPlayActor = MinHook::FindPattern(Patterns::LocalSpawnPlayActor);
		uintptr_t AddressInternalGetNetMode = MinHook::FindPattern(Patterns::InternalGetNetMode);
		uintptr_t AddressActorInternalGetNetMode = MinHook::FindPattern(Patterns::ActorInternalGetNetMode);
		uintptr_t AddressChangingGameSessionId = MinHook::FindPattern(Patterns::ChangingGameSessionId);
		uintptr_t AddressKickPlayer = MinHook::FindPattern(Patterns::KickPlayer);
		uintptr_t AddressPickupCombine = MinHook::FindPattern(Patterns::PickupCombine);
		uintptr_t AddressDispatchRequest = MinHook::FindPattern(Patterns::DispatchRequest);
		uintptr_t AddressGetPlayerViewPoint = MinHook::FindPattern(Patterns::GetPlayerViewPoint);
		uintptr_t AddressServerSpawnDeco = MinHook::FindPattern(Patterns::ServerSpawnDeco);

		MH_CreateHook((LPVOID)(AddressLocalSpawnPlayActor), LocalSpawnPlayActorHook, nullptr);
		MH_EnableHook((LPVOID)(AddressLocalSpawnPlayActor));
		MH_CreateHook((LPVOID)(AddressInternalGetNetMode), ReturnNetMode, nullptr);
		MH_EnableHook((LPVOID)(AddressInternalGetNetMode));
		MH_CreateHook((LPVOID)(AddressActorInternalGetNetMode), ReturnNetMode, nullptr);
		MH_EnableHook((LPVOID)(AddressActorInternalGetNetMode));
		MH_CreateHook((LPVOID)(AddressChangingGameSessionId), ChangingGameSessionIdHook, nullptr);
		MH_EnableHook((LPVOID)(AddressChangingGameSessionId));
		MH_CreateHook((LPVOID)(AddressKickPlayer), KickPlayerHook, nullptr);
		MH_EnableHook((LPVOID)(AddressKickPlayer));
		MH_CreateHook((LPVOID)(AddressDispatchRequest), DispatchRequestHook, (LPVOID*)(&DispatchRequest));
		MH_EnableHook((LPVOID)(AddressDispatchRequest));
		MH_CreateHook((LPVOID)(AddressGetPlayerViewPoint), GetPlayerViewPointHook, (LPVOID*)(&GetPlayerViewPoint));
		MH_EnableHook((LPVOID)(AddressGetPlayerViewPoint));
		MH_CreateHook((LPVOID)(AddressServerSpawnDeco), SpawnDeco, (LPVOID*)(&SpawnDecoOG));
		MH_EnableHook((LPVOID)(AddressServerSpawnDeco));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0xE31290), sub_7FF66F481290Hook, nullptr);
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0xE31290));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0x17C8E80), CollectGarbageHook, nullptr);
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0x17C8E80));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0xC56D70), InitalizePoiManager, nullptr);
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0xC56D70));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0x10194B0), RestartHook, (LPVOID*)(&Restart));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0x10194B0));

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + Offsets::ProcessEvent), ProcessEventHook, (LPVOID*)(&ProcessEvent));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + Offsets::ProcessEvent));

		FN_LOG(LogInit, Log, L"InitHook Success!");
	}
}