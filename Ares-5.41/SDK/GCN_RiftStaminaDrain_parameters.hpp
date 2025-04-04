#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GCN_RiftStaminaDrain

#include "Basic.hpp"

#include "GameplayAbilities_structs.hpp"
#include "CoreUObject_structs.hpp"


namespace SDK::Params
{

// Function GCN_RiftStaminaDrain.GCN_RiftStaminaDrain_C.UserConstructionScript
// 0x0010 (0x0010 - 0x0000)
struct GCN_RiftStaminaDrain_C_UserConstructionScript final
{
public:
	class UMaterialInstanceDynamic*               CallFunc_CreateDynamicMaterialInstance_ReturnValue; // 0x0000(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UMaterialInstanceDynamic*               CallFunc_CreateDynamicMaterialInstance_ReturnValue1; // 0x0008(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function GCN_RiftStaminaDrain.GCN_RiftStaminaDrain_C.OnWhileActiveParticleSystemActivate
// 0x0120 (0x0120 - 0x0000)
struct GCN_RiftStaminaDrain_C_OnWhileActiveParticleSystemActivate final
{
public:
	class UParticleSystemComponent*               WhileActiveParticleSysComponent;                   // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FGameplayCueParameters                 Parameters;                                        // 0x0008(0x00B8)(ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, ContainsInstancedReference)
	class AActor*                                 CallFunc_EffectContextGetEffectCauser_ReturnValue; // 0x00C0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_IsValid_ReturnValue;                      // 0x00C8(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_4D74[0x7];                                     // 0x00C9(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class AB_DtB_FloatingRift_C*                  K2Node_DynamicCast_AsB_Dt_B_Floating_Rift;         // 0x00D0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess;                       // 0x00D8(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_4D75[0x3];                                     // 0x00D9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FVector                                CallFunc_K2_GetActorLocation_ReturnValue;          // 0x00DC(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_K2_GetComponentLocation_ReturnValue;      // 0x00E8(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           CallFunc_Conv_VectorToLinearColor_ReturnValue;     // 0x00F4(0x0010)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Add_VectorVector_ReturnValue;             // 0x0104(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           CallFunc_Conv_VectorToLinearColor_ReturnValue1;    // 0x0110(0x0010)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function GCN_RiftStaminaDrain.GCN_RiftStaminaDrain_C.OnWhileActiveParticleSystemDeactivate
// 0x00C0 (0x00C0 - 0x0000)
struct GCN_RiftStaminaDrain_C_OnWhileActiveParticleSystemDeactivate final
{
public:
	class UParticleSystemComponent*               WhileActiveParticleSysComponent;                   // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FGameplayCueParameters                 Parameters;                                        // 0x0008(0x00B8)(ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, ContainsInstancedReference)
};

}

