#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BuildingBar

#include "Basic.hpp"

#include "BuildingBar_classes.hpp"
#include "BuildingBar_parameters.hpp"


namespace SDK
{

// Function BuildingBar.BuildingBar_C.Update Max HP Value
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// float                                   Max                                                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBuildingBar_C::Update_Max_HP_Value(float Max)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BuildingBar_C", "Update Max HP Value");

	Params::BuildingBar_C_Update_Max_HP_Value Parms{};

	Parms.Max = Max;

	UObject::ProcessEvent(Func, &Parms);
}


// Function BuildingBar.BuildingBar_C.Update Current HP Value
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// float                                   Current                                                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBuildingBar_C::Update_Current_HP_Value(float Current)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BuildingBar_C", "Update Current HP Value");

	Params::BuildingBar_C_Update_Current_HP_Value Parms{};

	Parms.Current = Current;

	UObject::ProcessEvent(Func, &Parms);
}


// Function BuildingBar.BuildingBar_C.Update Max Durability Value
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// float                                   Max                                                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBuildingBar_C::Update_Max_Durability_Value(float Max)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BuildingBar_C", "Update Max Durability Value");

	Params::BuildingBar_C_Update_Max_Durability_Value Parms{};

	Parms.Max = Max;

	UObject::ProcessEvent(Func, &Parms);
}


// Function BuildingBar.BuildingBar_C.Update Current Durability Value
// (Public, BlueprintCallable, BlueprintEvent)
// Parameters:
// float                                   CurrentDurability                                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBuildingBar_C::Update_Current_Durability_Value(float CurrentDurability)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BuildingBar_C", "Update Current Durability Value");

	Params::BuildingBar_C_Update_Current_Durability_Value Parms{};

	Parms.CurrentDurability = CurrentDurability;

	UObject::ProcessEvent(Func, &Parms);
}


// Function BuildingBar.BuildingBar_C.Update Durability Text
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)

void UBuildingBar_C::Update_Durability_Text()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BuildingBar_C", "Update Durability Text");

	UObject::ProcessEvent(Func, nullptr);
}


// Function BuildingBar.BuildingBar_C.Set Display Mode
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// EFortBuildingInteraction                InDisplayMode                                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBuildingBar_C::Set_Display_Mode(EFortBuildingInteraction InDisplayMode)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BuildingBar_C", "Set Display Mode");

	Params::BuildingBar_C_Set_Display_Mode Parms{};

	Parms.InDisplayMode = InDisplayMode;

	UObject::ProcessEvent(Func, &Parms);
}


// Function BuildingBar.BuildingBar_C.UpdateBuildingTrap
// (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
// Parameters:
// class ABuildingTrap*                    BuildingTrap                                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBuildingBar_C::UpdateBuildingTrap(class ABuildingTrap* BuildingTrap)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BuildingBar_C", "UpdateBuildingTrap");

	Params::BuildingBar_C_UpdateBuildingTrap Parms{};

	Parms.BuildingTrap = BuildingTrap;

	UObject::ProcessEvent(Func, &Parms);
}

}

