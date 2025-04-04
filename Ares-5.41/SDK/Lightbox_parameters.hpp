#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Lightbox

#include "Basic.hpp"

#include "UMG_structs.hpp"


namespace SDK::Params
{

// Function Lightbox.Lightbox_C.ExecuteUbergraph_Lightbox
// 0x000C (0x000C - 0x0000)
struct Lightbox_C_ExecuteUbergraph_Lightbox final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Temp_bool_Variable;                                // 0x0004(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	ESlateVisibility                              Temp_byte_Variable;                                // 0x0005(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	ESlateVisibility                              Temp_byte_Variable1;                               // 0x0006(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_Event_IsDesignTime;                         // 0x0007(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	ESlateVisibility                              K2Node_Select_Default;                             // 0x0008(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function Lightbox.Lightbox_C.PreConstruct
// 0x0001 (0x0001 - 0x0000)
struct Lightbox_C_PreConstruct final
{
public:
	bool                                          IsDesignTime;                                      // 0x0000(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor)
};

// Function Lightbox.Lightbox_C.AddContent
// 0x0010 (0x0010 - 0x0000)
struct Lightbox_C_AddContent final
{
public:
	class UCommonUserWidget*                      Param_Content;                                     // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UPanelSlot*                             CallFunc_AddChild_ReturnValue;                     // 0x0008(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function Lightbox.Lightbox_C.RemoveContent
// 0x0001 (0x0001 - 0x0000)
struct Lightbox_C_RemoveContent final
{
public:
	bool                                          CallFunc_HasAnyChildren_ReturnValue;               // 0x0000(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
};

}

