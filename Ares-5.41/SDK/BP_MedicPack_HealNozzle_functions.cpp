#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_MedicPack_HealNozzle

#include "Basic.hpp"

#include "BP_MedicPack_HealNozzle_classes.hpp"
#include "BP_MedicPack_HealNozzle_parameters.hpp"


namespace SDK
{

// Function BP_MedicPack_HealNozzle.BP_MedicPack_HealNozzle_C.ExecuteUbergraph_BP_MedicPack_HealNozzle
// ()
// Parameters:
// int32                                   EntryPoint                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void ABP_MedicPack_HealNozzle_C::ExecuteUbergraph_BP_MedicPack_HealNozzle(int32 EntryPoint)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BP_MedicPack_HealNozzle_C", "ExecuteUbergraph_BP_MedicPack_HealNozzle");

	Params::BP_MedicPack_HealNozzle_C_ExecuteUbergraph_BP_MedicPack_HealNozzle Parms{};

	Parms.EntryPoint = EntryPoint;

	UObject::ProcessEvent(Func, &Parms);
}


// Function BP_MedicPack_HealNozzle.BP_MedicPack_HealNozzle_C.ReceiveBeginPlay
// (Event, Protected, BlueprintEvent)

void ABP_MedicPack_HealNozzle_C::ReceiveBeginPlay()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BP_MedicPack_HealNozzle_C", "ReceiveBeginPlay");

	UObject::ProcessEvent(Func, nullptr);
}


// Function BP_MedicPack_HealNozzle.BP_MedicPack_HealNozzle_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void ABP_MedicPack_HealNozzle_C::UserConstructionScript()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BP_MedicPack_HealNozzle_C", "UserConstructionScript");

	UObject::ProcessEvent(Func, nullptr);
}

}

