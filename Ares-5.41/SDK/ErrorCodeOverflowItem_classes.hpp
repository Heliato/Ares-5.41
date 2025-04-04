#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: ErrorCodeOverflowItem

#include "Basic.hpp"

#include "UMG_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass ErrorCodeOverflowItem.ErrorCodeOverflowItem_C
// 0x0008 (0x0210 - 0x0208)
class UErrorCodeOverflowItem_C final : public UUserWidget
{
public:
	class UTextBlock*                             TextBlock_332;                                     // 0x0208(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void SetErrorCodeDisplay(const class FString& ErrorCode);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"ErrorCodeOverflowItem_C">();
	}
	static class UErrorCodeOverflowItem_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UErrorCodeOverflowItem_C>();
	}
};

}

