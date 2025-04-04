#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SmallLevelUpReward

#include "Basic.hpp"

#include "UMG_structs.hpp"
#include "UMG_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass SmallLevelUpReward.SmallLevelUpReward_C
// 0x0018 (0x0220 - 0x0208)
class USmallLevelUpReward_C final : public UUserWidget
{
public:
	class UCommonTextBlock*                       MiniReward1CountTB;                                // 0x0208(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 MiniReward1Image;                                  // 0x0210(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UHorizontalBox*                         RewardContainer;                                   // 0x0218(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void SetupReward(bool HasReward, const struct FFortItemInstanceQuantityPair& RewardItem, int32 LevelRewarded);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"SmallLevelUpReward_C">();
	}
	static class USmallLevelUpReward_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<USmallLevelUpReward_C>();
	}
};

}

