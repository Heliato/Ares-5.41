#pragma once


namespace QuestManager
{
	/* ------------------------------------- UFortQuestManagerOG ------------------------------------- */
	void (*SendCustomStatEventOG)(UFortQuestManager* QuestManager, const FDataTableRowHandle& ObjectiveStat, int32 Count, bool bForceFlush);
	void (*SendStatEventWithTagsOG)(UFortAwardManager* AwardManager, EFortQuestObjectiveStatEvent ObjectiveStatEvent, UObject* TargetObject, __int64 a4, __int64 a5, FGameplayTagContainer SourceTags, FGameplayTagContainer ContextTag);



	/* -------------------------------------- UFortQuestManager -------------------------------------- */

	void SendCustomStatEvent(UFortQuestManager* QuestManager, const FDataTableRowHandle& ObjectiveStatHandle, int32 Count, bool bForceFlush)
	{
		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendCustomStatEvent] QuestManager: %s", QuestManager->GetName().c_str());
		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendCustomStatEvent] Outer: %s", QuestManager->Outer->GetName().c_str());
		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendCustomStatEvent] ObjectiveStatHandle.DataTable: %s", ObjectiveStatHandle.DataTable->GetName().c_str());
		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendCustomStatEvent] ObjectiveStatHandle.RowName: %s", ObjectiveStatHandle.RowName.ToString().c_str());
		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendCustomStatEvent] Count: %i", Count);
		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendCustomStatEvent] bForceFlush: %i", bForceFlush);
		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendCustomStatEvent] called!");

		return SendCustomStatEventOG(QuestManager, ObjectiveStatHandle, Count, bForceFlush);

		for (int32 i = 0; i < QuestManager->CurrentQuests.Num(); i++)
		{
			UFortQuestItem* CurrentQuest = QuestManager->CurrentQuests[i];
			if (!CurrentQuest) continue;
			
			UFortQuestObjectiveInfo* ObjectiveInfo = CurrentQuest->GetObjectiveInfo(ObjectiveStatHandle);
			if (!ObjectiveInfo) continue;

			AFortPlayerController* OwningController = CurrentQuest->GetOwningController();
			if (!OwningController) continue;

			FFortQuestObjectiveCompletion ObjectiveCompletion;
			ObjectiveCompletion.StatName = UKismetStringLibrary::Conv_NameToString(ObjectiveInfo->BackendName);
			ObjectiveCompletion.Count = Count;

			QuestManager->PendingChanges.Add(ObjectiveCompletion);
			
			void (*UpdateStatsForSingleMatchQuests)(UFortQuestManager* QuestManager) = decltype(UpdateStatsForSingleMatchQuests)(0x125bfd0 + uintptr_t(GetModuleHandle(0)));
			UpdateStatsForSingleMatchQuests(QuestManager);

			/*__int64 (*ProcessPendingStatEvents)(UFortQuestManager* QuestManager) = decltype(ProcessPendingStatEvents)(0x124fe60 + uintptr_t(GetModuleHandle(0)));
			ProcessPendingStatEvents(QuestManager);*/

			break;

			/*CurrentQuest->HasCompletedObjectiveWithName();
			CurrentQuest->HasCompletedObjective();
			CurrentQuest->HasCompletedQuest();*/

			/*for (int32 j = 0; j < CurrentQuest->Objectives.Num(); j++)
			{
				UFortQuestObjectiveInfo* Objective = CurrentQuest->Objectives[j];
				if (!Objective) continue;

				Objective->BackendName;
				Objective->AchievedCount;
				Objective->StatEvent;
				Objective->ItemEvent;
			}*/
		}

		SendCustomStatEventOG(QuestManager, ObjectiveStatHandle, Count, bForceFlush);
	}

	void SendStatEventWithTags(UFortAwardManager* AwardManager, EFortQuestObjectiveStatEvent ObjectiveStatEvent, UObject* TargetObject, __int64 a4, __int64 a5, FGameplayTagContainer SourceTags, FGameplayTagContainer ContextTag)
	{
		FN_LOG(LogQuestManager, Log, L"[UFortAwardManager::SendStatEventWithTags] AwardManager: %s", AwardManager->GetName().c_str());
		FN_LOG(LogQuestManager, Log, L"[UFortAwardManager::SendStatEventWithTags] ObjectiveStatEvent: %i", ObjectiveStatEvent);
		FN_LOG(LogQuestManager, Log, L"[UFortAwardManager::SendStatEventWithTags] TargetObject: %s", TargetObject->GetName().c_str());
		FN_LOG(LogQuestManager, Log, L"[UFortAwardManager::SendStatEventWithTags] a4: %i", a4);
		FN_LOG(LogQuestManager, Log, L"[UFortAwardManager::SendStatEventWithTags] a5: %i", a5);

		FN_LOG(LogGameMode, Log, L"SourceTags.GameplayTags.Num(): %i", SourceTags.GameplayTags.Num());
		FN_LOG(LogGameMode, Log, L"ContextTag.GameplayTags.Num(): %i", ContextTag.GameplayTags.Num());

		for (int32 i = 0; i < SourceTags.GameplayTags.Num(); i++)
		{
			FGameplayTag GameplayTag = SourceTags.GameplayTags[i];

			FN_LOG(LogGameMode, Log, L"%i - SourceTags GameplayTag: %s", i, UKismetStringLibrary::Conv_NameToString(GameplayTag.TagName).ToString().c_str());
		}

		for (int32 i = 0; i < ContextTag.GameplayTags.Num(); i++)
		{
			FGameplayTag GameplayTag = ContextTag.GameplayTags[i];

			FN_LOG(LogGameMode, Log, L"%i - ContextTag GameplayTag: %s", i, UKismetStringLibrary::Conv_NameToString(GameplayTag.TagName).ToString().c_str());
		}

		/*if (QuestManager->PendingChanges.Num() > 0) 
		{
			for (int i = 0; i < QuestManager->CurrentQuests.Num(); i++)
			{
				auto Quest = QuestManager->CurrentQuests[i];
				if (!Quest) continue;

				for (int x = 0; x < Quest->Objectives.Num(); x++)
				{
					auto Objective = Quest->Objectives[x];
					if (!Objective) continue;

					for (int y = 0; y < QuestManager->PendingChanges.Num(); y++)
					{
						auto Change = QuestManager->PendingChanges[y];
						if (Change.StatName.ToString() != Objective->BackendName.ToString()) continue;

						if (Objective->AchievedCount != Change.Count && Objective->AchievedCount < Objective->RequiredCount)
							Objective->AchievedCount = Change.Count;

						Objective->DisplayDynamicQuestUpdate();
					}
				}
			}
		}*/

		FN_LOG(LogQuestManager, Log, L"[UFortQuestManager::SendStatEventWithTags] called!");

		SendStatEventWithTagsOG(AwardManager, ObjectiveStatEvent, TargetObject, a4, a5, SourceTags, ContextTag);
	}

	void InitQuestManager()
	{
		UFortQuestManager* FortQuestManagerDefault = UFortQuestManager::GetDefaultObj();
		UClass* FortQuestManagerClass = UFortQuestManager::StaticClass();

		/* -------------------------------------- UFortQuestManager -------------------------------------- */

		MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0x1255040), SendCustomStatEvent, (LPVOID*)(&SendCustomStatEventOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0x1255040));
		/*MH_CreateHook((LPVOID)(InSDKUtils::GetImageBase() + 0xcaa4c0), SendStatEventWithTags, (LPVOID*)(&SendStatEventWithTagsOG));
		MH_EnableHook((LPVOID)(InSDKUtils::GetImageBase() + 0xcaa4c0));*/

		/* ----------------------------------------------------------------------------------------------- */

		FN_LOG(LogInit, Log, L"InitQuestManager Success!");
	}
}