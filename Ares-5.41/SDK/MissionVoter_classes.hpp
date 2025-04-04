#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: MissionVoter

#include "Basic.hpp"

#include "UMG_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass MissionVoter.MissionVoter_C
// 0x0018 (0x0220 - 0x0208)
class UMissionVoter_C final : public UUserWidget
{
public:
	class UPlayerBanner_C*                        PlayerBanner;                                      // 0x0208(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCommonTextBlock*                       PlayerName;                                        // 0x0210(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 VoteMinusDecision;                                 // 0x0218(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void SetVoterData(const struct FVoter& Voter);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"MissionVoter_C">();
	}
	static class UMissionVoter_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UMissionVoter_C>();
	}
};

}

