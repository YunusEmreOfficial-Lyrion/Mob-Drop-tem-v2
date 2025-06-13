//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	BYTE GetMonsterScalePercent(DWORD dwVnum);
	float GetMonsterHitRange(DWORD dwVnum);

	// Function for outer
	void GetMatchableMobList(int iLevel, int iInterval, TMobTableList* pMobTableList);

protected:
	TNonPlayerDataMap m_NonPlayerDataMap;

// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
public:
	enum EMonsterItemDrop
	{
		MAX_MOB_ITEM_DROP_GRID_SLOT_X = 5,
		MAX_MOB_ITEM_DROP_GRID_SLOT_Y = 8,
		MAX_MOB_ITEM_DROP_GRID_SIZE = MAX_MOB_ITEM_DROP_GRID_SLOT_X * MAX_MOB_ITEM_DROP_GRID_SLOT_Y,
	};

	struct SMobItemDrop
	{
		DWORD dwVnum;
		WORD wCount;
	};

	using TMobDropItemVec = std::vector<SMobItemDrop>;
	using TMobDropItemMap = std::unordered_map<DWORD, TMobDropItemVec>;

public:
	BOOL SelectMobData(DWORD dwRaceVnum);
	TMobTable* GetSelectedMobDataPointer();

	void AddItemDrop(const DWORD dwRaceVnum, const DWORD dwVnum, const WORD wCount);
	void ClearItemDrop();

	TMobDropItemVec* GetItemDropVec(const DWORD dwVnum);

	void SetDropMetinStone(bool bDropMetinStone) { m_bDropMetinStone = bDropMetinStone; }
	bool GetDropMetinStone() const { return m_bDropMetinStone; }

protected:
	TMobTable* m_pSelectedMobData;
	TMobDropItemMap m_MobItemDropMap;
	bool m_bDropMetinStone;
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################
