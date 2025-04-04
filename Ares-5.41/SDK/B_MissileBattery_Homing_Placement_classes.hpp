#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: B_MissileBattery_Homing_Placement

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass B_MissileBattery_Homing_Placement.B_MissileBattery_Homing_Placement_C
// 0x0008 (0x0BB0 - 0x0BA8)
class AB_MissileBattery_Homing_Placement_C final : public ABuildingProp
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0BA8(0x0008)(Transient, DuplicateTransient)

public:
	void ExecuteUbergraph_B_MissileBattery_Homing_Placement(int32 EntryPoint);
	void ReceiveBeginPlay();
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"B_MissileBattery_Homing_Placement_C">();
	}
	static class AB_MissileBattery_Homing_Placement_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AB_MissileBattery_Homing_Placement_C>();
	}
};

}

