#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: ItemInspectCycleWidget

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteUI_classes.hpp"
#include "CommonInput_structs.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass ItemInspectCycleWidget.ItemInspectCycleWidget_C
// 0x0028 (0x0288 - 0x0260)
class UItemInspectCycleWidget_C final : public UFortItemInspectCycleWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0260(0x0008)(Transient, DuplicateTransient)
	class UWidgetAnimation*                       RightPulse;                                        // 0x0268(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWidgetAnimation*                       LeftPulse;                                         // 0x0270(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UIconTextButton_C*                      LeftButton;                                        // 0x0278(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UIconTextButton_C*                      RightButton;                                       // 0x0280(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_ItemInspectCycleWidget(int32 EntryPoint);
	void BndEvt__LeftButton_K2Node_ComponentBoundEvent_135_CommonButtonClicked__DelegateSignature(class UCommonButton* Button);
	void BndEvt__RightButton_K2Node_ComponentBoundEvent_152_CommonButtonClicked__DelegateSignature(class UCommonButton* Button);
	void OnItemCycled(class UFortItem* OldItem, class UFortItem* NewItem, int32 OffsetFromPreviousItem);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"ItemInspectCycleWidget_C">();
	}
	static class UItemInspectCycleWidget_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UItemInspectCycleWidget_C>();
	}
};

}

