#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GCN_Carmine_Jump_Liftoff

#include "Basic.hpp"

#include "GCN_Carmine_Jump_Liftoff_classes.hpp"
#include "GCN_Carmine_Jump_Liftoff_parameters.hpp"


namespace SDK
{

// Function GCN_Carmine_Jump_Liftoff.GCN_Carmine_Jump_Liftoff_C.OnStartParticleSystemSpawned
// (Event, Public, HasOutParams, HasDefaults, BlueprintCallable, BlueprintEvent, Const)
// Parameters:
// class UParticleSystemComponent*         SpawnedParticleSysComponent                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// struct FGameplayCueParameters           Parameters                                             (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, ContainsInstancedReference)

void UGCN_Carmine_Jump_Liftoff_C::OnStartParticleSystemSpawned(class UParticleSystemComponent* SpawnedParticleSysComponent, const struct FGameplayCueParameters& Parameters) const
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("GCN_Carmine_Jump_Liftoff_C", "OnStartParticleSystemSpawned");

	Params::GCN_Carmine_Jump_Liftoff_C_OnStartParticleSystemSpawned Parms{};

	Parms.SpawnedParticleSysComponent = SpawnedParticleSysComponent;
	Parms.Parameters = std::move(Parameters);

	UObject::ProcessEvent(Func, &Parms);
}

}

