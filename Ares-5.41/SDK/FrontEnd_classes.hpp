#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Frontend

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass Frontend.FrontEnd_C
// 0x0010 (0x0350 - 0x0340)
class AFrontEnd_C final : public AFortLevelScriptActor
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0340(0x0008)(Transient, DuplicateTransient)
	class AHBOnboardingFlow_C*                    HBOnboardingFlow_ExecuteUbergraph_Frontend_RefProperty; // 0x0348(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_FrontEnd(int32 EntryPoint);
	void EnableTutorial();
	void OnMatchStarted();
	void ReceiveBeginPlay();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"FrontEnd_C">();
	}
	static class AFrontEnd_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AFrontEnd_C>();
	}
};

}

