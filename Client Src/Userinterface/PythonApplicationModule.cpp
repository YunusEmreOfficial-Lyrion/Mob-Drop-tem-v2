//#####################//-/-/-/-/-/-//-/ ��Lyrion ��YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat


#if defined(ENABLE_COSTUME_SYSTEM)
	PyModule_AddIntConstant(poModule, "ENABLE_COSTUME_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_COSTUME_SYSTEM", 0);
#endif

// Alt�na ekle

#if defined(ENABLE_SEND_TARGET_INFO)
	PyModule_AddIntConstant(poModule, "ENABLE_SEND_TARGET_INFO", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_SEND_TARGET_INFO", 0);
#endif

//#####################//-/-/-/-/-/-//-/ ��Lyrion ��YunusED || Metin2House //-/-/-/-/-/-//-/#####################
