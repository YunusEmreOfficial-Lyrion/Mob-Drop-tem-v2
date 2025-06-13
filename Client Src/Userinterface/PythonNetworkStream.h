//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

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


// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
	bool RecvTargetInfoPacket();

public:
	bool SendTargetInfoPacket(DWORD dwVID);

protected:
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

/*

Not: Yukarda arat kýsmýnda olanlarý bulamassanýz müsait bi yere ekleyin.
	bool RecvTargetInfoPacket();
bunun protected altýnda olduðuna emin olun yeter diðerleri public tanýmlý zaten

*/