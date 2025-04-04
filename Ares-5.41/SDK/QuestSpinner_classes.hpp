#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: QuestSpinner

#include "Basic.hpp"

#include "UMG_classes.hpp"
#include "Engine_structs.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass QuestSpinner.QuestSpinner_C
// 0x0048 (0x0250 - 0x0208)
class UQuestSpinner_C final : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0208(0x0008)(Transient, DuplicateTransient)
	class UWidgetAnimation*                       Spin;                                              // 0x0210(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UDailyQuestWidget_C*                    PendingWidget;                                     // 0x0218(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UDailyQuestWidget_C*                    TopWidget;                                         // 0x0220(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UVerticalBox*                           VerticalBox_1;                                     // 0x0228(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UFortQuestItem*                         PendingQuestItem;                                  // 0x0230(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	TArray<class UFortQuestItem*>                 QuestItemPool;                                     // 0x0238(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int32                                         CurrentPoolIndex;                                  // 0x0248(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SpinPeriod;                                        // 0x024C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_QuestSpinner(int32 EntryPoint);
	void OnSpinComplete();
	void SetQuests(TArray<class UFortQuestItem*>& Quests, float Param_SpinPeriod);
	void BeginSpinDelayTimer();
	void OnSpinDelayTimerComplete();
	void IncrementPoolIndex(int32* NewValue);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"QuestSpinner_C">();
	}
	static class UQuestSpinner_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UQuestSpinner_C>();
	}
};

}

