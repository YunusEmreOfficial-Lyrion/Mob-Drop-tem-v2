//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

		Set(HEADER_GC_LOVER_INFO, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCLoverInfo), STATIC_SIZE_PACKET));
		Set(HEADER_GC_LOVE_POINT_UPDATE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCLovePointUpdate), STATIC_SIZE_PACKET));

		Set(HEADER_GC_DIG_MOTION, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDigMotion), STATIC_SIZE_PACKET));
		Set(HEADER_GC_DAMAGE_INFO, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDamageInfo), STATIC_SIZE_PACKET));

		Set(HEADER_GC_HYBRIDCRYPT_KEYS, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCHybridCryptKeys), DYNAMIC_SIZE_PACKET));
		Set(HEADER_GC_HYBRIDCRYPT_SDB, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCHybridSDB), DYNAMIC_SIZE_PACKET));
		Set(HEADER_GC_SPECIFIC_EFFECT, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCSpecificEffect), STATIC_SIZE_PACKET));

#if defined(ENABLE_DRAGON_SOUL_SYSTEM)
		Set(HEADER_GC_DRAGON_SOUL_REFINE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));
#endif
#if defined(ENABLE_GEM_SYSTEM)
		Set(HEADER_GC_GEM_SHOP, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCGemShop), DYNAMIC_SIZE_PACKET));
		Set(HEADER_GC_GEM_SHOP_PROCESS, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCGemShopProcess), STATIC_SIZE_PACKET));
#endif

// Alt©¥na ekle cavu?.

#if defined(ENABLE_SEND_TARGET_INFO)
		Set(HEADER_GC_TARGET_INFO, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCTargetInfo), DYNAMIC_SIZE_PACKET));
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################
