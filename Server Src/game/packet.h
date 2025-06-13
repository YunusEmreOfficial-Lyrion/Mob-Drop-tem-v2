//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	HEADER_CG_SHOP = 50,
	HEADER_CG_FLY_TARGETING = 51,
	HEADER_CG_USE_SKILL = 52,
	HEADER_CG_ADD_FLY_TARGETING = 53,
	HEADER_CG_SHOOT = 54,
	HEADER_CG_MYSHOP = 55,
#if defined(__MYSHOP_DECO__)
	HEADER_CG_MYSHOP_DECO_STATE = 56,
	HEADER_CG_MYSHOP_DECO_ADD = 57,
#endif
	//HEADER_CG_UNUSED = 58,


// Alt©¥na ekle

#if defined(__SEND_TARGET_INFO__)
	HEADER_CG_TARGET_INFO = 59,
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	HEADER_GC_SHOP = 38,
	HEADER_GC_SHOP_SIGN = 39,

	HEADER_GC_DUEL_START = 40,
	HEADER_GC_PVP = 41,
	HEADER_GC_EXCHANGE = 42,
	HEADER_GC_CHARACTER_POSITION = 43,

	HEADER_GC_PING = 44,
	HEADER_GC_SCRIPT = 45,
	HEADER_GC_QUEST_CONFIRM = 46,

#if defined(__EXTEND_INVEN_SYSTEM__)
	HEADER_GC_EXTEND_INVEN = 47,
	HEADER_GC_EXTEND_INVEN_ITEM_USE = 48,
#endif
#if defined(__GUILD_DRAGONLAIR_SYSTEM__)
	HEADER_GC_GUILD_DRAGONLAIR = 49,
#endif
#if defined(__CLIENT_TIMER__)
	HEADER_GC_CLIENT_TIMER = 50,
#endif
	//HEADER_GC_UNUSED = 51,
	//HEADER_GC_UNUSED = 52,
	//HEADER_GC_UNUSED = 53,
	//HEADER_GC_UNUSED = 54,
	//HEADER_GC_UNUSED = 55,
	//HEADER_GC_UNUSED = 56,
	//HEADER_GC_UNUSED = 57,


// Alt©¥na ekle

#if defined(__SEND_TARGET_INFO__)
	HEADER_GC_TARGET_INFO = 58,
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

typedef struct packet_target
{
	BYTE header;
	DWORD dwVID;
	BYTE bHPPercent;
#if defined(__VIEW_TARGET_HP__) || defined(__DEFENSE_WAVE__)
	int iMinHP;
	int iMaxHP;
	bool bAlliance;
#endif
#if defined(__ELEMENT_SYSTEM__)
	BYTE bElement[MOB_ELEMENT_MAX_NUM];
#endif
	packet_target() : dwVID(0), bHPPercent(0)
	{
#if defined(__VIEW_TARGET_HP__) || defined(__DEFENSE_WAVE__)
		iMinHP = 0;
		iMaxHP = 0;
		bAlliance = false;
#endif
#if defined(__ELEMENT_SYSTEM__)
		memset(&bElement, 0, sizeof(bElement));
#endif
	}
} TPacketGCTarget;


// Alt©¥na ekle

#if defined(__SEND_TARGET_INFO__)
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