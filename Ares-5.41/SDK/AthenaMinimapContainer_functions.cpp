#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: AthenaMinimapContainer

#include "Basic.hpp"

#include "AthenaMinimapContainer_classes.hpp"
#include "AthenaMinimapContainer_parameters.hpp"


namespace SDK
{

// Function AthenaMinimapContainer.AthenaMinimapContainer_C.BndEvt__MapButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// (BlueprintEvent)

void UAthenaMinimapContainer_C::BndEvt__MapButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("AthenaMinimapContainer_C", "BndEvt__MapButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UObject::ProcessEvent(Func, nullptr);
}


// Function AthenaMinimapContainer.AthenaMinimapContainer_C.ExecuteUbergraph_AthenaMinimapContainer
// ()
// Parameters:
// int32                                   EntryPoint                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UAthenaMinimapContainer_C::ExecuteUbergraph_AthenaMinimapContainer(int32 EntryPoint)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("AthenaMinimapContainer_C", "ExecuteUbergraph_AthenaMinimapContainer");

	Params::AthenaMinimapContainer_C_ExecuteUbergraph_AthenaMinimapContainer Parms{};

	Parms.EntryPoint = EntryPoint;

	UObject::ProcessEvent(Func, &Parms);
}

}

