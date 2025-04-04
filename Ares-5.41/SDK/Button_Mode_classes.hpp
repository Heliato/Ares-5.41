#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Button_Mode

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "CommonBacchusButton_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass Button_Mode.Button_Mode_C
// 0x0008 (0x03D8 - 0x03D0)
class UButton_Mode_C final : public UCommonBacchusButton_C
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame_Button_Mode_C;                      // 0x03D0(0x0008)(Transient, DuplicateTransient)

public:
	void ExecuteUbergraph_Button_Mode(int32 EntryPoint);
	void Construct();
	void OnBuildModeChanged_Event_0(bool bEntering);
	struct FEventReply OnTouchStarted(const struct FGeometry& MyGeometry, const struct FPointerEvent& InTouchEvent);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"Button_Mode_C">();
	}
	static class UButton_Mode_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UButton_Mode_C>();
	}
};

}

