#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: B_Assault_Surgical_Thermal_Athena

#include "Basic.hpp"


namespace SDK::Params
{

// Function B_Assault_Surgical_Thermal_Athena.B_Assault_Surgical_Thermal_Athena_C.ExecuteUbergraph_B_Assault_Surgical_Thermal_Athena
// 0x0040 (0x0040 - 0x0000)
struct B_Assault_Surgical_Thermal_Athena_C_ExecuteUbergraph_B_Assault_Surgical_Thermal_Athena final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_IsDedicatedServer_ReturnValue;            // 0x0004(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          K2Node_Event_bNewIsTargeting;                      // 0x0005(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          CallFunc_IsMobilePlatform_ReturnValue;             // 0x0006(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          Temp_bool_Has_Been_Initd_Variable;                 // 0x0007(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	float                                         CallFunc_Divide_FloatFloat_ReturnValue;            // 0x0008(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_4CCE[0x4];                                     // 0x000C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class APawn*                                  CallFunc_GetInstigator_ReturnValue;                // 0x0010(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Temp_bool_IsClosed_Variable;                       // 0x0018(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_4CCF[0x7];                                     // 0x0019(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class AFortPawn*                              K2Node_DynamicCast_AsFort_Pawn;                    // 0x0020(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess;                       // 0x0028(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_4CD0[0x7];                                     // 0x0029(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class APlayerController*                      CallFunc_GetLocalViewingPlayerController_ReturnValue; // 0x0030(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_IsValid_ReturnValue;                      // 0x0038(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
};

// Function B_Assault_Surgical_Thermal_Athena.B_Assault_Surgical_Thermal_Athena_C.OnSetTargeting
// 0x0001 (0x0001 - 0x0000)
struct B_Assault_Surgical_Thermal_Athena_C_OnSetTargeting final
{
public:
	bool                                          bNewIsTargeting;                                   // 0x0000(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor)
};

}

