#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: B_Placement_Preview_Pack_MissleBattery

#include "Basic.hpp"

#include "B_Placement_Preview_Pack_MissleBattery_classes.hpp"
#include "B_Placement_Preview_Pack_MissleBattery_parameters.hpp"


namespace SDK
{

// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.ExecuteUbergraph_B_Placement_Preview_Pack_MissleBattery
// (HasDefaults)
// Parameters:
// int32                                   EntryPoint                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_Placement_Preview_Pack_MissleBattery_C::ExecuteUbergraph_B_Placement_Preview_Pack_MissleBattery(int32 EntryPoint)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "ExecuteUbergraph_B_Placement_Preview_Pack_MissleBattery");

	Params::B_Placement_Preview_Pack_MissleBattery_C_ExecuteUbergraph_B_Placement_Preview_Pack_MissleBattery Parms{};

	Parms.EntryPoint = EntryPoint;

	UObject::ProcessEvent(Func, &Parms);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.ReceiveEndPlay
// (Event, Public, BlueprintEvent)
// Parameters:
// EEndPlayReason                          EndPlayReason                                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_Placement_Preview_Pack_MissleBattery_C::ReceiveEndPlay(EEndPlayReason EndPlayReason)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "ReceiveEndPlay");

	Params::B_Placement_Preview_Pack_MissleBattery_C_ReceiveEndPlay Parms{};

	Parms.EndPlayReason = EndPlayReason;

	UObject::ProcessEvent(Func, &Parms);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.PawnSetHere
// (BlueprintCallable, BlueprintEvent)
// Parameters:
// class AFortPawn*                        Param_FortPawn                                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_Placement_Preview_Pack_MissleBattery_C::PawnSetHere(class AFortPawn* Param_FortPawn)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "PawnSetHere");

	Params::B_Placement_Preview_Pack_MissleBattery_C_PawnSetHere Parms{};

	Parms.Param_FortPawn = Param_FortPawn;

	UObject::ProcessEvent(Func, &Parms);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.OnUpdateVisuals
// (Event, Public, BlueprintEvent)
// Parameters:
// float                                   DeltaSeconds                                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// bool                                    bSafeToPlace                                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor)

void AB_Placement_Preview_Pack_MissleBattery_C::OnUpdateVisuals(float DeltaSeconds, bool bSafeToPlace)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "OnUpdateVisuals");

	Params::B_Placement_Preview_Pack_MissleBattery_C_OnUpdateVisuals Parms{};

	Parms.DeltaSeconds = DeltaSeconds;
	Parms.bSafeToPlace = bSafeToPlace;

	UObject::ProcessEvent(Func, &Parms);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void AB_Placement_Preview_Pack_MissleBattery_C::UserConstructionScript()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "UserConstructionScript");

	UObject::ProcessEvent(Func, nullptr);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.SetUpDummyProjectile
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class AFortPawn*                        PlayerPawn                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_Placement_Preview_Pack_MissleBattery_C::SetUpDummyProjectile(class AFortPawn* PlayerPawn)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "SetUpDummyProjectile");

	Params::B_Placement_Preview_Pack_MissleBattery_C_SetUpDummyProjectile Parms{};

	Parms.PlayerPawn = PlayerPawn;

	UObject::ProcessEvent(Func, &Parms);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.UpdateTrajectorySpline
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)

void AB_Placement_Preview_Pack_MissleBattery_C::UpdateTrajectorySpline()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "UpdateTrajectorySpline");

	UObject::ProcessEvent(Func, nullptr);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.SpawnLocationAndRotation
// (Public, HasOutParams, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
// Parameters:
// struct FVector                          OutLoc                                                 (Parm, OutParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// struct FRotator                         OutRot                                                 (Parm, OutParm, IsPlainOldData, NoDestructor)

void AB_Placement_Preview_Pack_MissleBattery_C::SpawnLocationAndRotation(struct FVector* OutLoc, struct FRotator* OutRot)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "SpawnLocationAndRotation");

	Params::B_Placement_Preview_Pack_MissleBattery_C_SpawnLocationAndRotation Parms{};

	UObject::ProcessEvent(Func, &Parms);

	if (OutLoc != nullptr)
		*OutLoc = std::move(Parms.OutLoc);

	if (OutRot != nullptr)
		*OutRot = std::move(Parms.OutRot);
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.CalcRocketSpeedFromPitch
// (Public, HasOutParams, BlueprintCallable, BlueprintEvent, BlueprintPure)
// Parameters:
// float                                   AimPitch                                               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// float                                   RocketSpeed                                            (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_Placement_Preview_Pack_MissleBattery_C::CalcRocketSpeedFromPitch(float AimPitch, float* RocketSpeed)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "CalcRocketSpeedFromPitch");

	Params::B_Placement_Preview_Pack_MissleBattery_C_CalcRocketSpeedFromPitch Parms{};

	Parms.AimPitch = AimPitch;

	UObject::ProcessEvent(Func, &Parms);

	if (RocketSpeed != nullptr)
		*RocketSpeed = Parms.RocketSpeed;
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.GetGadgetItem
// (Public, HasOutParams, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// class UFortItem*                        Gadget                                                 (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_Placement_Preview_Pack_MissleBattery_C::GetGadgetItem(class UFortItem** Gadget) const
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "GetGadgetItem");

	Params::B_Placement_Preview_Pack_MissleBattery_C_GetGadgetItem Parms{};

	UObject::ProcessEvent(Func, &Parms);

	if (Gadget != nullptr)
		*Gadget = Parms.Gadget;
}


// Function B_Placement_Preview_Pack_MissleBattery.B_Placement_Preview_Pack_MissleBattery_C.GetPlayerController
// (Public, HasOutParams, BlueprintCallable, BlueprintEvent, BlueprintPure, Const)
// Parameters:
// class AFortPlayerControllerZone*        Controller                                             (Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void AB_Placement_Preview_Pack_MissleBattery_C::GetPlayerController(class AFortPlayerControllerZone** Controller) const
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("B_Placement_Preview_Pack_MissleBattery_C", "GetPlayerController");

	Params::B_Placement_Preview_Pack_MissleBattery_C_GetPlayerController Parms{};

	UObject::ProcessEvent(Func, &Parms);

	if (Controller != nullptr)
		*Controller = Parms.Controller;
}

}

