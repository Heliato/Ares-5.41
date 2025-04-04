#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GCN_Tunneler_TeleportNPC

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteGame_classes.hpp"
#include "GameplayAbilities_structs.hpp"


namespace SDK
{

// BlueprintGeneratedClass GCN_Tunneler_TeleportNPC.GCN_Tunneler_TeleportNPC_C
// 0x0008 (0x0428 - 0x0420)
class AGCN_Tunneler_TeleportNPC_C final : public AFortGameplayCueNotify_Looping
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0420(0x0008)(Transient, DuplicateTransient)

public:
	void ExecuteUbergraph_GCN_Tunneler_TeleportNPC(int32 EntryPoint);
	void K2_HandleGameplayCue(class AActor* MyTarget, EGameplayCueEvent EventType, const struct FGameplayCueParameters& Parameters);
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"GCN_Tunneler_TeleportNPC_C">();
	}
	static class AGCN_Tunneler_TeleportNPC_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AGCN_Tunneler_TeleportNPC_C>();
	}
};

}

