#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: B_MissileBattery_Homing_Placement

#include "Basic.hpp"

#include "B_MissileBattery_Homing_Placement_classes.hpp"
#include "B_MissileBattery_Homing_Placement_parameters.hpp"


namespace SDK
{

// Function B_MissileBattery_Homing_Placement.B_MissileBattery_Homing_Placement_C.ExecuteUbergraph_B_MissileBattery_Homing_Placement
// ()
// Parameters:
// int32                                   EntryPoint                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_MissileBattery_Homing_Placement_C::ExecuteUbergraph_B_MissileBattery_Homing_Placement(int32 EntryPoint)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_MissileBattery_Homing_Placement_C", "ExecuteUbergraph_B_MissileBattery_Homing_Placement");

	Params::B_MissileBattery_Homing_Placement_C_ExecuteUbergraph_B_MissileBattery_Homing_Placement Parms{};

	Parms.EntryPoint = EntryPoint;

	UObject::ProcessEvent(Func, &Parms);
}


// Function B_MissileBattery_Homing_Placement.B_MissileBattery_Homing_Placement_C.ReceiveBeginPlay
// (Event, Protected, BlueprintEvent)

void AB_MissileBattery_Homing_Placement_C::ReceiveBeginPlay()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_MissileBattery_Homing_Placement_C", "ReceiveBeginPlay");

	UObject::ProcessEvent(Func, nullptr);
}


// Function B_MissileBattery_Homing_Placement.B_MissileBattery_Homing_Placement_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void AB_MissileBattery_Homing_Placement_C::UserConstructionScript()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_MissileBattery_Homing_Placement_C", "UserConstructionScript");

	UObject::ProcessEvent(Func, nullptr);
}

}

