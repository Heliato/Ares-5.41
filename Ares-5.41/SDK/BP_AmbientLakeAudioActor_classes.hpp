#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_AmbientLakeAudioActor

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "Engine_classes.hpp"
#include "CoreUObject_structs.hpp"


namespace SDK
{

// BlueprintGeneratedClass BP_AmbientLakeAudioActor.BP_AmbientLakeAudioActor_C
// 0x02D0 (0x05F8 - 0x0328)
class ABP_AmbientLakeAudioActor_C final : public AActor
{
public:
	class UAudioComponent*                        WaterLoopAudio;                                    // 0x0328(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        DefaultSceneRoot;                                  // 0x0330(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)
	struct FSoundAttenuationSettings              AttenuationOverride;                               // 0x0338(0x02A8)(Edit, BlueprintVisible, DisableEditOnInstance)
	struct FVector                                AttenuationExtents;                                // 0x05E0(0x000C)(Edit, BlueprintVisible, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         FalloffDistance;                                   // 0x05EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase*                             Sound;                                             // 0x05F0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BP_AmbientLakeAudioActor_C">();
	}
	static class ABP_AmbientLakeAudioActor_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<ABP_AmbientLakeAudioActor_C>();
	}
};

}

