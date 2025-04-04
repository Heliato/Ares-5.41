#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: B_Thrower_Flame_AOE

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "CoreUObject_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass B_Thrower_Flame_AOE.B_Thrower_Flame_AOE_C
// 0x0040 (0x05A8 - 0x0568)
class AB_Thrower_Flame_AOE_C final : public AFortAreaOfEffectCloud
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0568(0x0008)(Transient, DuplicateTransient)
	class USceneComponent*                        Scene;                                             // 0x0570(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USphereComponent*                       Sphere;                                            // 0x0578(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UParticleSystem*                        Aoe_FX_Loop;                                       // 0x0580(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             Aoe_Sound_Cue;                                     // 0x0588(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FRotator                               StopRotX;                                          // 0x0590(0x000C)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	struct FVector                                StopLocatin;                                       // 0x059C(0x000C)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_B_Thrower_Flame_AOE(int32 EntryPoint);
	void BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult);
	void GetRotation(const struct FRotator& Rotation, const struct FVector& Location);
	void ReceiveBeginPlay();
	void ReceiveDestroyed();
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"B_Thrower_Flame_AOE_C">();
	}
	static class AB_Thrower_Flame_AOE_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AB_Thrower_Flame_AOE_C>();
	}
};

}

