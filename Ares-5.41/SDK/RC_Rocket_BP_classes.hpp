#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: RC_Rocket_BP

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "Engine_classes.hpp"
#include "AnimGraphRuntime_structs.hpp"


namespace SDK
{

// AnimBlueprintGeneratedClass RC_Rocket_BP.RC_Rocket_BP_C
// 0x0158 (0x04B0 - 0x0358)
class URC_Rocket_BP_C final : public UAnimInstance
{
public:
	uint8                                         Pad_3362[0x8];                                     // 0x0358(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0360(0x0008)(Transient, DuplicateTransient)
	struct FAnimNode_Root                         AnimGraphNode_Root_08FAFFB0444865FC64D0C0BFEBA059B9; // 0x0368(0x0040)()
	struct FAnimNode_SequencePlayer               AnimGraphNode_SequencePlayer_956D7C7B47E114589BA5ADB878BAB261; // 0x03A8(0x00A0)()
	struct FAnimNode_Slot                         AnimGraphNode_Slot_02FBD1D3400F785868D3B9AD8C664EA4; // 0x0448(0x0068)()

public:
	void ExecuteUbergraph_RC_Rocket_BP(int32 EntryPoint);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"RC_Rocket_BP_C">();
	}
	static class URC_Rocket_BP_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<URC_Rocket_BP_C>();
	}
};

}

