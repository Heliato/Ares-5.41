#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Button_Zoom

#include "Basic.hpp"

#include "CommonBacchusButton_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass Button_Zoom.Button_Zoom_C
// 0x0000 (0x03D0 - 0x03D0)
class UButton_Zoom_C final : public UCommonBacchusButton_C
{
public:
	struct FEventReply OnTouchStarted(const struct FGeometry& MyGeometry, const struct FPointerEvent& InTouchEvent);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"Button_Zoom_C">();
	}
	static class UButton_Zoom_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UButton_Zoom_C>();
	}
};

}

