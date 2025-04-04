#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Announcement_QuestUpdate

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "FortniteUI_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass Announcement_QuestUpdate.Announcement_QuestUpdate_C
// 0x0010 (0x0228 - 0x0218)
class UAnnouncement_QuestUpdate_C final : public UFortAnnouncementWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0218(0x0008)(Transient, DuplicateTransient)
	class UQuestUpdateEntry_C*                    QuestUpdateEntry;                                  // 0x0220(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_Announcement_QuestUpdate(int32 EntryPoint);
	void AnnouncementStopped(class AFortClientAnnouncement* Announcement);
	void UpdateWidgetData(class AFortClientAnnouncement* Announcement);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"Announcement_QuestUpdate_C">();
	}
	static class UAnnouncement_QuestUpdate_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UAnnouncement_QuestUpdate_C>();
	}
};

}

