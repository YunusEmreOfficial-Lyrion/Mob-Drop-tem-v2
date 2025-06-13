//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

typedef std::map<DWORD, int> ItemToSpecialGroupMap;
typedef std::map<DWORD, CDropItemGroup*> pkDropItemGroupMap;
typedef std::map<DWORD, CLevelItemGroup*> pkLevelItemGroupMap;
typedef std::map<DWORD, CMobItemGroup*> pkMobItemGroupMap;
typedef std::map<DWORD, CBuyerThiefGlovesItemGroup*> pkGloveItemGroupMap;
typedef std::map<DWORD, DWORD> EtcItemDropProbMap;
typedef std::map<DWORD, DWORD> ItemRefineFromMap;
typedef std::map<DWORD, CSpecialItemGroup*> SpecialItemGroupMap;
typedef std::map<DWORD, CSpecialAttrGroup*> SpecialAttrGroupMap;
typedef std::map<DWORD, LPITEM> ItemMap;

// Alt©¥na ekle

#if defined(__SEND_TARGET_INFO__)
typedef std::unordered_map<DWORD, BYTE> MonsterItemDropMap;
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	LPITEM Find(DWORD id);
	LPITEM FindByVID(DWORD vid);
	TItemTable* GetTable(DWORD vnum);
	bool GetVnum(const char* c_pszName, DWORD& r_dwVnum);
	bool GetVnumByOriginalName(const char* c_pszName, DWORD& r_dwVnum);

	bool GetDropPct(LPCHARACTER pkChr, LPCHARACTER pkKiller, OUT int& iDeltaPercent, OUT int& iRandRange);
	bool CreateDropItem(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM>& vec_item);

// Alt©¥na ekle

#if defined(__SEND_TARGET_INFO__)
	void GetMonsterItemDropMap(LPCHARACTER pkChr, LPCHARACTER pkKiller, MonsterItemDropMap& rItemDropMap, bool& bDropMetinStone);
	bool CreateDropItemVector(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM>& rVecItem);
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################