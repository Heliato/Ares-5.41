#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SmallStatWidget

#include "Basic.hpp"

#include "FortniteUI_structs.hpp"


namespace SDK::Params
{

// Function SmallStatWidget.SmallStatWidget_C.ExecuteUbergraph_SmallStatWidget
// 0x00D8 (0x00D8 - 0x0000)
struct SmallStatWidget_C_ExecuteUbergraph_SmallStatWidget final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_53F5[0x4];                                     // 0x0004(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UAthenaBaseStatView*                    CallFunc_GetBaseStatView_ReturnValue;              // 0x0008(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FFortUIStatStyle                       CallFunc_GetStatStyle_ReturnValue;                 // 0x0010(0x00C0)(ConstParm)
	float                                         CallFunc_GetStat_ReturnValue;                      // 0x00D0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

}

