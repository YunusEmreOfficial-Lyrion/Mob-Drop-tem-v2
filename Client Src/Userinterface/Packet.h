//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	HEADER_CG_SHOP = 50,
	HEADER_CG_FLY_TARGETING = 51,
	HEADER_CG_USE_SKILL = 52,
	HEADER_CG_ADD_FLY_TARGETING = 53,
	HEADER_CG_SHOOT = 54,
	HEADER_CG_MYSHOP = 55,
#if defined(ENABLE_MYSHOP_DECO)
	HEADER_CG_MYSHOP_DECO = 56,
	HEADER_CG_MYSHOP_DECO_ADD = 57,
#endif
	//HEADER_CG_UNUSED = 58,

// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
	HEADER_CG_TARGET_INFO = 59,
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	HEADER_GC_PING = 44,
	HEADER_GC_SCRIPT = 45,
	HEADER_GC_QUEST_CONFIRM = 46,

#if defined(ENABLE_EXTEND_INVEN_SYSTEM)
	HEADER_GC_EXTEND_INVEN = 47,
	HEADER_GC_EXTEND_INVEN_ITEM_USE = 48,
#endif
#if defined(ENABLE_GUILD_DRAGONLAIR_SYSTEM)
	HEADER_GC_GUILD_DRAGONLAIR = 49,
#endif
#if defined(ENABLE_CLIENT_TIMER)
	HEADER_GC_CLIENT_TIMER = 50,
#endif
	//HEADER_GC_UNUSED = 51,
	//HEADER_GC_UNUSED = 52,
	//HEADER_GC_UNUSED = 53,
	//HEADER_GC_UNUSED = 54,
	//HEADER_GC_UNUSED = 55,
	//HEADER_GC_UNUSED = 56,
	//HEADER_GC_UNUSED = 57,


// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
	HEADER_GC_TARGET_INFO = 58,
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

typedef struct packet_target
{
	BYTE header;
	DWORD dwVID;
	BYTE bHPPercent;
#if defined(ENABLE_VIEW_TARGET_DECIMAL_HP) || defined(ENABLE_DEFENSE_WAVE)
	int iMinHP;
	int iMaxHP;
#if defined(ENABLE_DEFENSE_WAVE)
	bool bAlliance;
#endif
#endif
#if defined(ENABLE_ELEMENT_ADD)
	BYTE bElement[CPythonNonPlayer::MOB_ELEMENT_MAX_NUM];
#endif
} TPacketGCTarget;


// Altýna ekle


#if defined(ENABLE_SEND_TARGET_INFO)
typedef struct SPacketGCTargetDropInfo
{
	DWORD dwVnum;
	BYTE bCount;
} TPacketGCTargetDropInfo;

typedef struct SPacketGCTargetInfo
{
	BYTE bHeader;
	WORD wSize;
	DWORD dwRaceVnum;
	DWORD dwVID;
	bool bDropMetinStone;
} TPacketGCTargetInfo;

typedef struct SPacketCGTargetInfo
{
	BYTE bHeader;
	DWORD dwVID;
} TPacketCGTargetInfo;
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################