#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: AthenaTeamCountSlot

#include "Basic.hpp"

#include "CommonUI_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass AthenaTeamCountSlot.AthenaTeamCountSlot_C
// 0x0010 (0x0220 - 0x0210)
class UAthenaTeamCountSlot_C final : public UCommonUserWidget
{
public:
	class URichTextBlock*                         TeamCount;                                         // 0x0210(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class URichTextBlock*                         TeamName;                                          // 0x0218(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void SetTeamSlotData(const struct FAthenaTeamCountSlotData& TeamSlotData);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"AthenaTeamCountSlot_C">();
	}
	static class UAthenaTeamCountSlot_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UAthenaTeamCountSlot_C>();
	}
};

}

