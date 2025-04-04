#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: AbilitiesPageTile

#include "Basic.hpp"

#include "FortniteGame_structs.hpp"
#include "FortniteUI_structs.hpp"
#include "FortniteUI_classes.hpp"
#include "Engine_structs.hpp"
#include "CoreUObject_structs.hpp"
#include "CommonInput_structs.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass AbilitiesPageTile.AbilitiesPageTile_C
// 0x0110 (0x09C8 - 0x08B8)
class UAbilitiesPageTile_C final : public UFortAbilitiesPageTileBase
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x08B8(0x0008)(Transient, DuplicateTransient)
	class UFortSZAwareImage*                      AbilityImage;                                      // 0x08C0(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       AbilityName;                                       // 0x08C8(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class USizeBox*                               SizeBoxAbilityKeybind;                             // 0x08D0(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UFortAbilityKit*                        AbilityKit;                                        // 0x08D8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UFortGadgetItemDefinition*              GadgetItemDef;                                     // 0x08E0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UFortItem*                              AbilityItem;                                       // 0x08E8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          AbilityLocked;                                     // 0x08F0(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_57DD[0x7];                                     // 0x08F1(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	struct FFortUIPerk                            AbilityUIPerk;                                     // 0x08F8(0x0098)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FLinearColor                           LockedColor;                                       // 0x0990(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           UnlockedColor;                                     // 0x09A0(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EFortBrushSize                                AbilityIconBrushSize;                              // 0x09B0(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_57DE[0x3];                                     // 0x09B1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FLinearColor                           LockedAbilityIconColor;                            // 0x09B4(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_AbilitiesPageTile(int32 EntryPoint);
	void HandleInputMethodChanged(bool bUsingGamepad);
	void Construct();
	void SetAbilityItemInfo(class UFortItem* SlottedAbilityItem);
	void UpdateKeyBinding();
	void SetAbilityPerkInfo(const struct FFortUIPerk& AbilityPerk);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"AbilitiesPageTile_C">();
	}
	static class UAbilitiesPageTile_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UAbilitiesPageTile_C>();
	}
};

}

