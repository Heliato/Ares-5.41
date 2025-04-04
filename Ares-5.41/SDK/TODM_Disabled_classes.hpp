#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: TODM_Disabled

#include "Basic.hpp"

#include "MASTER_TODM_classes.hpp"
#include "Engine_structs.hpp"
#include "CoreUObject_structs.hpp"


namespace SDK
{

// BlueprintGeneratedClass TODM_Disabled.TODM_Disabled_C
// 0x0180 (0x0F10 - 0x0D90)
class ATODM_Disabled_C final : public AMASTER_TODM_C
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame_TODM_Disabled_C;                    // 0x0D90(0x0008)(Transient, DuplicateTransient)
	float                                         WindSpeed_0;                                       // 0x0D98(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         RandomWeatherWaitTime_0;                           // 0x0D9C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CurrentAmountOfRandomWeatherTimeLeft_0;            // 0x0DA0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         NewWeatherLerpAmount_0;                            // 0x0DA4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         WindStrength_0;                                    // 0x0DA8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         FutureWindStrength_0;                              // 0x0DAC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         FutureWindSpeed_0;                                 // 0x0DB0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          bPickNewWindConditions_0;                          // 0x0DB4(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_5F1F[0x3];                                     // 0x0DB5(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LightningStrength_0;                               // 0x0DB8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         ThreatCloudStormAmount_0;                          // 0x0DBC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          UseRainWithStorms_0;                               // 0x0DC0(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          Play_a_Particle_Effect_Near_the_players_Feet_0;    // 0x0DC1(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          WindEffects_Should_be_Active_0;                    // 0x0DC2(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_5F20[0x5];                                     // 0x0DC3(0x0005)(Fixing Size After Last Property [ Dumper-7 ])
	class UParticleSystemComponent*               Storm_Foot_Particle_Outdoor_0;                     // 0x0DC8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystem*                        Storm_Foot_Particle_While_on_Terrain_0;            // 0x0DD0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               Storm_Foot_Particle_Indoor_0;                      // 0x0DD8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystem*                        Storm_Foot_Particle_While_NOT_on_Terrain_0;        // 0x0DE0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         Storm_Wind_Strength_0;                             // 0x0DE8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Generate_Foliage_Wind_Gusts_0;                     // 0x0DEC(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor)
	uint8                                         Pad_5F21[0x3];                                     // 0x0DED(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FTimerHandle                           LightningStrikeTimerHandle_0;                      // 0x0DF0(0x0008)(Edit, BlueprintVisible, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           PreviousDirectionalLightColor_0;                   // 0x0DF8(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           Lightning_Flash_Color_0;                           // 0x0E08(0x0010)(Edit, BlueprintVisible, IsPlainOldData, NoDestructor, ExposeOnSpawn, HasGetValueTypeHash)
	float                                         Lightning_Flash_Timeline_Min_0;                    // 0x0E18(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         Lightning_Flash_Timeline_Max_0;                    // 0x0E1C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UParticleSystemComponent*               ShootingStarParticleSystem_0;                      // 0x0E20(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Spawn_Shooting_Stars_0;                            // 0x0E28(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor)
	uint8                                         Pad_5F22[0x3];                                     // 0x0E29(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FLinearColor                           SkyboxFogMorningColor_0;                           // 0x0E2C(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           SkyboxFogMorningLitColor_0;                        // 0x0E3C(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogMorningDistance_0;                        // 0x0E4C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogMorningDiffuseAmount_0;                   // 0x0E50(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogMorningEmissiveAmount_0;                  // 0x0E54(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogMorningLitLength_0;                       // 0x0E58(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogMorningLitRotation_0;                     // 0x0E5C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogMorningLitOffset_0;                       // 0x0E60(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           SkyboxFogDayColor_0;                               // 0x0E64(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           SkyboxFogDayLitColor_0;                            // 0x0E74(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogDayDistance_0;                            // 0x0E84(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogDayDiffuseAmount_0;                       // 0x0E88(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogDayEmissiveAmount_0;                      // 0x0E8C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogDayLitLength_0;                           // 0x0E90(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogDayLitRotation_0;                         // 0x0E94(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogDayLitOffset_0;                           // 0x0E98(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           SkyboxFogEveningColor_0;                           // 0x0E9C(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           SkyboxFogEveningLitColor_0;                        // 0x0EAC(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogEveningDistance_0;                        // 0x0EBC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogEveningDiffuseAmount_0;                   // 0x0EC0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogEveningEmissiveAmount_0;                  // 0x0EC4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogEveningLitLength_0;                       // 0x0EC8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogEveningLitRotation_0;                     // 0x0ECC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogEveningLitOffset_0;                       // 0x0ED0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           SkyboxFogNightColor_0;                             // 0x0ED4(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           SkyboxFogNightLitColor_0;                          // 0x0EE4(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogNightDistance_0;                          // 0x0EF4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogNightDiffuseAmount_0;                     // 0x0EF8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogNightEmissiveAmount_0;                    // 0x0EFC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogNightLitLength_0;                         // 0x0F00(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogNightLitRotation_0;                       // 0x0F04(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         SkyboxFogNightLitOffset_0;                         // 0x0F08(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_TODM_Disabled(int32 EntryPoint);
	void ReceiveBeginPlay();
	void DisableLightAndFog(bool Enable);
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"TODM_Disabled_C">();
	}
	static class ATODM_Disabled_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<ATODM_Disabled_C>();
	}
};

}

