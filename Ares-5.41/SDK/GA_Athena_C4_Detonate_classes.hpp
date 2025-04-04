#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GA_Athena_C4_Detonate

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass GA_Athena_C4_Detonate.GA_Athena_C4_Detonate_C
// 0x0008 (0x0900 - 0x08F8)
class UGA_Athena_C4_Detonate_C final : public UFortGameplayAbility
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x08F8(0x0008)(Transient, DuplicateTransient)

public:
	void ExecuteUbergraph_GA_Athena_C4_Detonate(int32 EntryPoint);
	void Cancelled_0FC6F3A9476E143A48E14F9AC0AF6604(const struct FGameplayAbilityTargetDataHandle& TargetData, const struct FGameplayTag& ApplicationTag);
	void K2_ActivateAbilityFromEvent(const struct FGameplayEventData& EventData);
	void Targeted_0FC6F3A9476E143A48E14F9AC0AF6604(const struct FGameplayAbilityTargetDataHandle& TargetData, const struct FGameplayTag& ApplicationTag);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"GA_Athena_C4_Detonate_C">();
	}
	static class UGA_Athena_C4_Detonate_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UGA_Athena_C4_Detonate_C>();
	}
};

}

