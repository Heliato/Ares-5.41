#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: FrontendCamera_Main

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteGame_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass FrontendCamera_Main.FrontendCamera_Main_C
// 0x0010 (0x0890 - 0x0880)
class AFrontendCamera_Main_C final : public AFortCameraBase
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0880(0x0008)(Transient, DuplicateTransient)
	class UCameraComponent*                       LoginCamera_0;                                     // 0x0888(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_FrontendCamera_Main(int32 EntryPoint);
	void OnActivated();
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"FrontendCamera_Main_C">();
	}
	static class AFrontendCamera_Main_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AFrontendCamera_Main_C>();
	}
};

}

