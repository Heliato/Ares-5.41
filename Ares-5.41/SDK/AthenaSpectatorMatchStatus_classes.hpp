#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: AthenaSpectatorMatchStatus

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteUI_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass AthenaSpectatorMatchStatus.AthenaSpectatorMatchStatus_C
// 0x0030 (0x0248 - 0x0218)
class UAthenaSpectatorMatchStatus_C final : public UAthenaMatchStatusBase
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0218(0x0008)(Transient, DuplicateTransient)
	class UAthenaGamePhaseWidget_C*               AthenaGamePhaseWidget;                             // 0x0220(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UAthenaPlayersLeftWidget_C*             AthenaPlayersLeftWidget;                           // 0x0228(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Icon;                                              // 0x0230(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       StormPhaseText;                                    // 0x0238(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       TimeElapsedText;                                   // 0x0240(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void Construct();
	void ExecuteUbergraph_AthenaSpectatorMatchStatus(int32 EntryPoint);
	void UpdateMatchTimeText(const class FText& MatchTimeText);
	void UpdateStormPhaseText(const class FText& SafeZonePhaseTxt);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"AthenaSpectatorMatchStatus_C">();
	}
	static class UAthenaSpectatorMatchStatus_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UAthenaSpectatorMatchStatus_C>();
	}
};

}

