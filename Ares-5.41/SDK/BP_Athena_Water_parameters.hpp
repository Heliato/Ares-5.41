#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_Athena_Water

#include "Basic.hpp"

#include "CoreUObject_structs.hpp"
#include "Engine_structs.hpp"
#include "GameplayAbilities_structs.hpp"


namespace SDK::Params
{

// Function BP_Athena_Water.BP_Athena_Water_C.ExecuteUbergraph_BP_Athena_Water
// 0x04F8 (0x04F8 - 0x0000)
struct BP_Athena_Water_C_ExecuteUbergraph_BP_Athena_Water final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FDF[0x4];                                     // 0x0004(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<class AFortPlayerPawn*>                CallFunc_GetAllPassengers_ReturnValue;             // 0x0008(0x0010)(ZeroConstructor, ReferenceParm)
	int32                                         CallFunc_Array_Length_ReturnValue;                 // 0x0018(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FWalkableSlopeOverride                 K2Node_MakeStruct_WalkableSlopeOverride;           // 0x001C(0x0010)(IsPlainOldData, NoDestructor)
	bool                                          K2Node_CustomEvent_Bouncy;                         // 0x002C(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FE0[0x3];                                     // 0x002D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	class UPrimitiveComponent*                    K2Node_ComponentBoundEvent_HitComponent;           // 0x0030(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AActor*                                 K2Node_ComponentBoundEvent_OtherActor1;            // 0x0038(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UPrimitiveComponent*                    K2Node_ComponentBoundEvent_OtherComp1;             // 0x0040(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                K2Node_ComponentBoundEvent_NormalImpulse;          // 0x0048(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FE1[0x4];                                     // 0x0054(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	struct FHitResult                             K2Node_ComponentBoundEvent_Hit;                    // 0x0058(0x0088)(ConstParm, IsPlainOldData, NoDestructor, ContainsInstancedReference)
	TArray<class FName>                           K2Node_MakeArray_Array;                            // 0x00E0(0x0010)(ZeroConstructor, ReferenceParm)
	bool                                          CallFunc_BreakHitResult_bBlockingHit;              // 0x00F0(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          CallFunc_BreakHitResult_bInitialOverlap;           // 0x00F1(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FE2[0x2];                                     // 0x00F2(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         CallFunc_BreakHitResult_Time;                      // 0x00F4(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_BreakHitResult_Distance;                  // 0x00F8(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_BreakHitResult_Location;                  // 0x00FC(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_BreakHitResult_ImpactPoint;               // 0x0108(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_BreakHitResult_Normal;                    // 0x0114(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_BreakHitResult_ImpactNormal;              // 0x0120(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FE3[0x4];                                     // 0x012C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UPhysicalMaterial*                      CallFunc_BreakHitResult_PhysMat;                   // 0x0130(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AActor*                                 CallFunc_BreakHitResult_HitActor;                  // 0x0138(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UPrimitiveComponent*                    CallFunc_BreakHitResult_HitComponent;              // 0x0140(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class FName                                   CallFunc_BreakHitResult_HitBoneName;               // 0x0148(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         CallFunc_BreakHitResult_HitItem;                   // 0x0150(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         CallFunc_BreakHitResult_FaceIndex;                 // 0x0154(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_BreakHitResult_TraceStart;                // 0x0158(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_BreakHitResult_TraceEnd;                  // 0x0164(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_K2_GetActorLocation_ReturnValue;          // 0x0170(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FE4[0x4];                                     // 0x017C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UProjectileMovementComponent*           CallFunc_GetComponentByClass_ReturnValue;          // 0x0180(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_IsValid_ReturnValue;                      // 0x0188(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FE5[0x7];                                     // 0x0189(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class AFortAthenaVehicle*                     K2Node_DynamicCast_AsFort_Athena_Vehicle;          // 0x0190(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess;                       // 0x0198(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FE6[0x7];                                     // 0x0199(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class APlayerPawn_Athena_C*                   K2Node_DynamicCast_AsPlayer_Pawn_Athena;           // 0x01A0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess1;                      // 0x01A8(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FE7[0x3];                                     // 0x01A9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         Temp_int_Loop_Counter_Variable;                    // 0x01AC(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_Less_IntInt_ReturnValue;                  // 0x01B0(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FE8[0x3];                                     // 0x01B1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         CallFunc_Add_IntInt_ReturnValue;                   // 0x01B4(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector_NetQuantizeNormal              K2Node_MakeStruct_Vector_NetQuantizeNormal;        // 0x01B8(0x000C)(NoDestructor)
	uint8                                         Pad_3FE9[0x4];                                     // 0x01C4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UPrimitiveComponent*                    K2Node_ComponentBoundEvent_OverlappedComponent;    // 0x01C8(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AActor*                                 K2Node_ComponentBoundEvent_OtherActor;             // 0x01D0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UPrimitiveComponent*                    K2Node_ComponentBoundEvent_OtherComp;              // 0x01D8(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         K2Node_ComponentBoundEvent_OtherBodyIndex;         // 0x01E0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_ComponentBoundEvent_bFromSweep;             // 0x01E4(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FEA[0x3];                                     // 0x01E5(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FHitResult                             K2Node_ComponentBoundEvent_SweepResult;            // 0x01E8(0x0088)(ConstParm, IsPlainOldData, NoDestructor, ContainsInstancedReference)
	class AFortAthenaVehicle*                     K2Node_DynamicCast_AsFort_Athena_Vehicle1;         // 0x0270(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess2;                      // 0x0278(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FEB[0x3];                                     // 0x0279(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FVector                                CallFunc_GetActorForwardVector_ReturnValue;        // 0x027C(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_GetVelocity_ReturnValue;                  // 0x0288(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Normal_ReturnValue;                       // 0x0294(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_VSize_ReturnValue;                        // 0x02A0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_VLerp_ReturnValue;                        // 0x02A4(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_FMax_ReturnValue;                         // 0x02B0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FEC[0x4];                                     // 0x02B4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class AActor*                                 K2Node_CustomEvent_Target;                         // 0x02B8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Multiply_VectorFloat_ReturnValue;         // 0x02C0(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Multiply_VectorVector_ReturnValue;        // 0x02CC(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_Array_Contains_ReturnValue;               // 0x02D8(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FED[0x3];                                     // 0x02D9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         CallFunc_Array_LastIndex_ReturnValue;              // 0x02DC(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	TDelegate<void()>                             K2Node_CreateDelegate_OutputDelegate;              // 0x02E0(0x0010)(ZeroConstructor, NoDestructor)
	int32                                         CallFunc_Array_Length_ReturnValue1;                // 0x02F0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FEE[0x4];                                     // 0x02F4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	struct FTimerHandle                           CallFunc_K2_SetTimerDelegate_ReturnValue;          // 0x02F8(0x0008)(NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_Greater_IntInt_ReturnValue;               // 0x0300(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FEF[0x7];                                     // 0x0301(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	TDelegate<void()>                             K2Node_CreateDelegate_OutputDelegate1;             // 0x0308(0x0010)(ZeroConstructor, NoDestructor)
	struct FTimerHandle                           CallFunc_K2_SetTimerDelegate_ReturnValue1;         // 0x0318(0x0008)(NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_RandomFloatInRange_ReturnValue;           // 0x0320(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_GetActorRightVector_ReturnValue;          // 0x0324(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_GetActorForwardVector_ReturnValue1;       // 0x0330(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_RandomFloatInRange_ReturnValue1;          // 0x033C(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Multiply_VectorFloat_ReturnValue1;        // 0x0340(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Multiply_VectorFloat_ReturnValue2;        // 0x034C(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Temp_int_Loop_Counter_Variable1;                   // 0x0358(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Add_VectorVector_ReturnValue;             // 0x035C(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         CallFunc_Add_IntInt_ReturnValue1;                  // 0x0368(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Temp_int_Array_Index_Variable;                     // 0x036C(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AFortPlayerPawn*                        CallFunc_Array_Get_Item;                           // 0x0370(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AController*                            CallFunc_GetController_ReturnValue;                // 0x0378(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AFortPlayerControllerGameplay*          K2Node_DynamicCast_AsFort_Player_Controller_Gameplay; // 0x0380(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess3;                      // 0x0388(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FF0[0x3];                                     // 0x0389(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FVector                                CallFunc_MakeVector_ReturnValue;                   // 0x038C(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Add_VectorVector_ReturnValue1;            // 0x0398(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FF1[0x4];                                     // 0x03A4(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class AActor*                                 K2Node_CustomEvent_Actor;                          // 0x03A8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_K2_GetActorLocation_ReturnValue1;         // 0x03B0(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_BreakVector_X;                            // 0x03BC(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_BreakVector_Y;                            // 0x03C0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_BreakVector_Z;                            // 0x03C4(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	TArray<class AActor*>                         CallFunc_GetOverlappingActors_OverlappingActors;   // 0x03C8(0x0010)(ZeroConstructor, ReferenceParm)
	struct FVector_NetQuantize10                  K2Node_MakeStruct_Vector_NetQuantize10;            // 0x03D8(0x000C)(NoDestructor)
	int32                                         CallFunc_Array_Length_ReturnValue2;                // 0x03E4(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FGameplayCueParameters                 K2Node_MakeStruct_GameplayCueParameters;           // 0x03E8(0x00B8)(ContainsInstancedReference)
	bool                                          CallFunc_Less_IntInt_ReturnValue1;                 // 0x04A0(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FF2[0x7];                                     // 0x04A1(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class APlayerPawn_Athena_C*                   K2Node_CustomEvent_Pawn;                           // 0x04A8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_IsDedicatedServer_ReturnValue;            // 0x04B0(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FF3[0x3];                                     // 0x04B1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FVector                                CallFunc_Multiply_VectorVector_ReturnValue1;       // 0x04B4(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                CallFunc_Add_VectorVector_ReturnValue2;            // 0x04C0(0x000C)(IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FF4[0x4];                                     // 0x04CC(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class FName                                   CallFunc_GetCollisionProfileName_ReturnValue;      // 0x04D0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          CallFunc_EqualEqual_NameName_ReturnValue;          // 0x04D8(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FF5[0x3];                                     // 0x04D9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         Temp_int_Array_Index_Variable1;                    // 0x04DC(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AActor*                                 CallFunc_Array_Get_Item1;                          // 0x04E0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class APlayerPawn_Athena_C*                   K2Node_DynamicCast_AsPlayer_Pawn_Athena1;          // 0x04E8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess4;                      // 0x04F0(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          K2Node_SwitchInteger_CmpSuccess;                   // 0x04F1(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          K2Node_SwitchInteger1_CmpSuccess;                  // 0x04F2(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
};

// Function BP_Athena_Water.BP_Athena_Water_C.BouncePawn
// 0x0008 (0x0008 - 0x0000)
struct BP_Athena_Water_C_BouncePawn final
{
public:
	class APlayerPawn_Athena_C*                   Pawn;                                              // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function BP_Athena_Water.BP_Athena_Water_C.ReplicateGCVehicles
// 0x0008 (0x0008 - 0x0000)
struct BP_Athena_Water_C_ReplicateGCVehicles final
{
public:
	class AActor*                                 Actor;                                             // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function BP_Athena_Water.BP_Athena_Water_C.PlayBounceGC
// 0x0008 (0x0008 - 0x0000)
struct BP_Athena_Water_C_PlayBounceGC final
{
public:
	class AActor*                                 Target;                                            // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function BP_Athena_Water.BP_Athena_Water_C.BndEvt__Box_K2Node_ComponentBoundEvent_1_ComponentBeginOverlapSignature__DelegateSignature
// 0x00A8 (0x00A8 - 0x0000)
struct BP_Athena_Water_C_BndEvt__Box_K2Node_ComponentBoundEvent_1_ComponentBeginOverlapSignature__DelegateSignature final
{
public:
	class UPrimitiveComponent*                    OverlappedComponent;                               // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AActor*                                 OtherActor;                                        // 0x0008(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UPrimitiveComponent*                    OtherComp;                                         // 0x0010(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         OtherBodyIndex;                                    // 0x0018(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          bFromSweep;                                        // 0x001C(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_3FF6[0x3];                                     // 0x001D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FHitResult                             SweepResult;                                       // 0x0020(0x0088)(ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData, NoDestructor, ContainsInstancedReference)
};

// Function BP_Athena_Water.BP_Athena_Water_C.BndEvt__Box_K2Node_ComponentBoundEvent_0_ComponentHitSignature__DelegateSignature
// 0x00B0 (0x00B0 - 0x0000)
struct BP_Athena_Water_C_BndEvt__Box_K2Node_ComponentBoundEvent_0_ComponentHitSignature__DelegateSignature final
{
public:
	class UPrimitiveComponent*                    HitComponent;                                      // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AActor*                                 OtherActor;                                        // 0x0008(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UPrimitiveComponent*                    OtherComp;                                         // 0x0010(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                NormalImpulse;                                     // 0x0018(0x000C)(BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_3FF7[0x4];                                     // 0x0024(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	struct FHitResult                             Hit;                                               // 0x0028(0x0088)(ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData, NoDestructor, ContainsInstancedReference)
};

// Function BP_Athena_Water.BP_Athena_Water_C.SetBouncy
// 0x0001 (0x0001 - 0x0000)
struct BP_Athena_Water_C_SetBouncy final
{
public:
	bool                                          Bouncy;                                            // 0x0000(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor)
};

// Function BP_Athena_Water.BP_Athena_Water_C.UserConstructionScript
// 0x0001 (0x0001 - 0x0000)
struct BP_Athena_Water_C_UserConstructionScript final
{
public:
	bool                                          CallFunc_NotEqual_ObjectObject_ReturnValue;        // 0x0000(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
};

// Function BP_Athena_Water.BP_Athena_Water_C.OnRep_BounceLake
// 0x0001 (0x0001 - 0x0000)
struct BP_Athena_Water_C_OnRep_BounceLake final
{
public:
	bool                                          K2Node_SwitchInteger_CmpSuccess;                   // 0x0000(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
};

}

