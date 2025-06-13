//#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	Set(HEADER_CG_CLIENT_VERSION, sizeof(TPacketCGClientVersion), "Version", true);
	Set(HEADER_CG_CLIENT_VERSION2, sizeof(TPacketCGClientVersion2), "Version", true);
	Set(HEADER_CG_PONG, sizeof(BYTE), "Pong", true);
	Set(HEADER_CG_MALL_CHECKOUT, sizeof(TPacketCGSafeboxCheckout), "MallCheckout", true);

	Set(HEADER_CG_SCRIPT_SELECT_ITEM, sizeof(TPacketCGScriptSelectItem), "ScriptSelectItem", true);

#if defined(__DRAGON_SOUL_SYSTEM__)
	Set(HEADER_CG_DRAGON_SOUL_REFINE, sizeof(TPacketCGDragonSoulRefine), "DragonSoulRefine", false);
#endif
	Set(HEADER_CG_STATE_CHECKER, sizeof(BYTE), "ServerStateCheck", false);

// Altına ekle

#if defined(__SEND_TARGET_INFO__)
	Set(HEADER_CG_TARGET_INFO, sizeof(TPacketCGTargetInfo), "TargetInfo", true);
#endif

//#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################
