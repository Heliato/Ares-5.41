#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: QuestTrackerSubEntry

#include "Basic.hpp"

#include "UMG_structs.hpp"
#include "Engine_structs.hpp"
#include "FortniteUI_classes.hpp"
#include "SlateCore_structs.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass QuestTrackerSubEntry.QuestTrackerSubEntry_C
// 0x0160 (0x03B0 - 0x0250)
class UQuestTrackerSubEntry_C final : public UFortQuestTrackerSubEntry
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0250(0x0008)(Transient, DuplicateTransient)
	class UWidgetAnimation*                       CheckmarkAnimation;                                // 0x0258(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWidgetAnimation*                       CompletionRemove;                                  // 0x0260(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWidgetAnimation*                       CompletionFlash;                                   // 0x0268(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Bullet;                                            // 0x0270(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UOverlay*                               BulletOverlay;                                     // 0x0278(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 CheckMark;                                         // 0x0280(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 FlashImage;                                        // 0x0288(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       ObjectiveDescriptionText;                          // 0x0290(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Pin;                                               // 0x0298(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	struct FSlateBrush                            NonHUDBullet;                                      // 0x02A0(0x0088)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FSlateBrush                            NonHUDPin;                                         // 0x0328(0x0088)(Edit, BlueprintVisible, DisableEditOnInstance)

public:
	void ExecuteUbergraph_QuestTrackerSubEntry(int32 EntryPoint);
	void PostCompletionDelay();
	void OnCompletionFlashFInished();
	void OnPlayObjectiveCompletedAnimation();
	void OnQuestsUpdated();
	void Construct();
	void UpdateObjectiveText();
	void HideIfEmpty();
	void HandleRemoveFinished();

	float GetHeightEstimate() const;

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"QuestTrackerSubEntry_C">();
	}
	static class UQuestTrackerSubEntry_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UQuestTrackerSubEntry_C>();
	}
};

}

