//#####################//-/-/-/-/-/-//-/ ��Lyrion ��YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	// Quest
	bool RecvScriptPacket();
	bool RecvQuestInfoPacket();
	bool RecvQuestConfirmPacket();
	bool RecvRequestMakeGuild();

	// Skill
	bool RecvSkillLevel();
	bool RecvSkillLevelNew();

	// Target
	bool RecvTargetPacket();
	bool RecvViewEquipPacket();
	bool RecvDamageInfoPacket();


// Alt�na ekle

#if defined(ENABLE_SEND_TARGET_INFO)
	bool RecvTargetInfoPacket();

public:
	bool SendTargetInfoPacket(DWORD dwVID);

protected:
#endif

//#####################//-/-/-/-/-/-//-/ ��Lyrion ��YunusED || Metin2House //-/-/-/-/-/-//-/#####################

/*

Not: Yukarda arat k�sm�nda olanlar� bulamassan�z m�sait bi yere ekleyin.
	bool RecvTargetInfoPacket();
bunun protected alt�nda oldu�una emin olun yeter di�erleri public tan�ml� zaten

*/