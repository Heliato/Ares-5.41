#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GA_BoostJumpPack_Equip

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass GA_BoostJumpPack_Equip.GA_BoostJumpPack_Equip_C
// 0x0010 (0x0908 - 0x08F8)
class UGA_BoostJumpPack_Equip_C final : public UFortGameplayAbility
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x08F8(0x0008)(Transient, DuplicateTransient)
	class AFortPlayerPawn*                        PlayerPawn;                                        // 0x0900(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_GA_BoostJumpPack_Equip(int32 EntryPoint);
	void K2_ActivateAbility();
	void IsAuthority(bool* bAuthority);

	bool K2_CanActivateAbility(const struct FGameplayAbilityActorInfo& ActorInfo, struct FGameplayTagContainer* RelevantTags) const;
	void GetPlayerController(class AFortPlayerPawn* Pawn, class AFortPlayerControllerZone** AsFort_Player_Controller_Zone) const;
	class UFortItem* GetGadgetItem(class AFortPlayerPawn* Pawn) const;

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"GA_BoostJumpPack_Equip_C">();
	}
	static class UGA_BoostJumpPack_Equip_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UGA_BoostJumpPack_Equip_C>();
	}
};

}

