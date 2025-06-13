//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	void ItemGive(LPCHARACTER ch, const char* c_pData);
	void Hack(LPCHARACTER ch, const char* c_pData);
	int MyShop(LPCHARACTER ch, const char* c_pData, size_t uiBytes);

#if defined(__MYSHOP_DECO__)
	void MyShopDecoState(LPCHARACTER ch, const char* c_pData);
	void MyShopDecoAdd(LPCHARACTER ch, const char* c_pData);
#endif

	void Refine(LPCHARACTER ch, const char* c_pData);

#if defined(__CUBE_RENEWAL__)
	// Cube
	void Cube(const LPCHARACTER pChar, const char* pData);
#endif

// Alt©¥na ekle

#if defined(__SEND_TARGET_INFO__)
	void TargetInfo(LPCHARACTER pChar, const char* c_pszData);
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################