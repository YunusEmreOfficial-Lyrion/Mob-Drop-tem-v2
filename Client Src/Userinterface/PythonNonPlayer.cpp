//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat


BYTE CPythonNonPlayer::GetEventTypeByVID(DWORD dwVID)
{
	CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetInstancePtr(dwVID);

	if (NULL == pInstance)
	{
		//Tracef("CPythonNonPlayer::GetEventTypeByVID - There is no Virtual Number\n");
		return ON_CLICK_EVENT_NONE;
	}

	WORD dwVnum = pInstance->GetVirtualNumber();
	return GetEventType(dwVnum);
}

const char* CPythonNonPlayer::GetMonsterName(DWORD dwVnum)
{
	const CPythonNonPlayer::TMobTable* c_pTable = GetTable(dwVnum);
	if (!c_pTable)
	{
		static const char* sc_szEmpty = "";
		return sc_szEmpty;
	}

	return c_pTable->szLocaleName;
}

DWORD CPythonNonPlayer::GetMonsterColor(DWORD dwVnum)
{
	const CPythonNonPlayer::TMobTable* c_pTable = GetTable(dwVnum);
	if (!c_pTable)
		return 0;

	return c_pTable->dwMobColor;
}

void CPythonNonPlayer::GetMatchableMobList(int iLevel, int iInterval, TMobTableList* pMobTableList)
{
	/*
	pMobTableList->clear();

	TNonPlayerDataMap::iterator itor = m_NonPlayerDataMap.begin();
	for (; itor != m_NonPlayerDataMap.end(); ++itor)
	{
		TMobTable* pMobTable = itor->second;

		int iLowerLevelLimit = iLevel - iInterval;
		int iUpperLevelLimit = iLevel + iInterval;

		if ((pMobTable->abLevelRange[0] >= iLowerLevelLimit && pMobTable->abLevelRange[0] <= iUpperLevelLimit) ||
			(pMobTable->abLevelRange[1] >= iLowerLevelLimit && pMobTable->abLevelRange[1] <= iUpperLevelLimit))
		{
			pMobTableList->push_back(pMobTable);
		}
	}
	*/
}

// Altýna ekle


#if defined(ENABLE_SEND_TARGET_INFO)
BOOL CPythonNonPlayer::SelectMobData(DWORD dwRaceVnum)
{
	CPythonNonPlayer::TMobTable* pTable = GetTable(dwRaceVnum);
	if (NULL == pTable)
		return FALSE;

	m_pSelectedMobData = pTable;
	return TRUE;
}

CPythonNonPlayer::TMobTable* CPythonNonPlayer::GetSelectedMobDataPointer()
{
	return m_pSelectedMobData;
}

// Monster Item Drop
void CPythonNonPlayer::AddItemDrop(const DWORD dwRaceVnum, const DWORD dwVnum, const WORD wCount)
{
	TMobDropItemMap::iterator it = m_MobItemDropMap.find(dwRaceVnum);
	if (it != m_MobItemDropMap.end())
	{
		TMobDropItemVec& rVec = it->second;
		const TMobDropItemVec::iterator vFind = std::find_if(rVec.begin(), rVec.end(),
			[dwVnum](const SMobItemDrop& rItem) { return rItem.dwVnum == dwVnum; });

		if (vFind != rVec.end())
			return;

		it->second.push_back({ dwVnum, wCount });
	}
	else
		m_MobItemDropMap[dwRaceVnum].push_back({ dwVnum, wCount });
}

void CPythonNonPlayer::ClearItemDrop()
{
	for (TMobDropItemMap::value_type& it : m_MobItemDropMap)
		it.second.clear();

	m_MobItemDropMap.clear();
}

CPythonNonPlayer::TMobDropItemVec* CPythonNonPlayer::GetItemDropVec(const DWORD dwVnum)
{
	TMobDropItemMap::iterator it = m_MobItemDropMap.find(dwVnum);
	if (it != m_MobItemDropMap.end())
		return &(it->second);

	return nullptr;
}
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

void CPythonNonPlayer::Clear()
{
}

// Deðiþtir

void CPythonNonPlayer::Clear()
{
#if defined(ENABLE_SEND_TARGET_INFO)
	m_pSelectedMobData = NULL;
#endif
}

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

void CPythonNonPlayer::Destroy()
{
	stl_wipe_second(m_NonPlayerDataMap);
	m_NonPlayerDataMap.clear();
}

// Deðiþtir


void CPythonNonPlayer::Destroy()
{
	stl_wipe_second(m_NonPlayerDataMap);
	m_NonPlayerDataMap.clear();

#if defined(ENABLE_SEND_TARGET_INFO)
	m_pSelectedMobData = NULL;
	m_MobItemDropMap.clear();
#endif
}

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################