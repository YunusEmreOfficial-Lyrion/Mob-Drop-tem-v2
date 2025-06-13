//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

bool ITEM_MANAGER::GetDropPct(LPCHARACTER pkChr, LPCHARACTER pkKiller, OUT int& iDeltaPercent, OUT int& iRandRange)
{
	if (NULL == pkChr || NULL == pkKiller)
		return false;

	BYTE bRank = pkChr->GetMobRank();
	int iLevel = pkKiller->GetLevel();

	iDeltaPercent = 100;

	if (!pkChr->IsStone() && pkChr->GetMobRank() >= MOB_RANK_BOSS)
		iDeltaPercent = PERCENT_LVDELTA_BOSS(pkKiller->GetLevel(), pkChr->GetLevel());
	else
		iDeltaPercent = PERCENT_LVDELTA(pkKiller->GetLevel(), pkChr->GetLevel());

	// LEVEL_105_DROP_RATE
	if (iLevel >= 105)
		iDeltaPercent = PERCENT_LVDELTA_BOSS(105, pkChr->GetLevel());
	// END_LEVEL_105_DROP_RATE

	if (1 == number(1, 50000))
		iDeltaPercent += 1000;
	else if (1 == number(1, 10000))
		iDeltaPercent += 500;

	sys_log(3, "CreateDropItem for level: %d rank: %u pct: %d", iLevel, bRank, iDeltaPercent);
	iDeltaPercent = iDeltaPercent * CHARACTER_MANAGER::instance().GetMobItemRate(pkKiller) / 100;

	int iDropBonus = CPrivManager::instance().GetPriv(pkKiller, PRIV_ITEM_DROP);

	// ADD_PREMIUM
	if (pkKiller->GetPremiumRemainSeconds(PREMIUM_ITEM) > 0)
	{
		iDropBonus += 50;
		iDeltaPercent += (iDeltaPercent * 50) / 100;
	}

	if (pkKiller->GetPoint(POINT_MALL_ITEMBONUS) > 0)
	{
		iDropBonus += MIN(100, pkKiller->GetPoint(POINT_MALL_ITEMBONUS));
		iDeltaPercent += iDeltaPercent * pkKiller->GetPoint(POINT_MALL_ITEMBONUS) / 100;
	}
	// END_OF_ADD_PREMIUM

	// NOTE: Thief's Gloves now work like special rings.
	/*
	if (pkKiller->IsEquipUniqueGroup(UNIQUE_GROUP_DOUBLE_ITEM))
	{
		iDropBonus += 50;
		iDeltaPercent += (iDeltaPercent * 50) / 100;
	}
	*/

	if (pkKiller->GetPoint(POINT_ITEM_DROP_BONUS) > 0)
	{
		iDropBonus += MIN(100, pkKiller->GetPoint(POINT_ITEM_DROP_BONUS));
		iDeltaPercent += iDeltaPercent * pkKiller->GetPoint(POINT_ITEM_DROP_BONUS) / 100;
	}

	iRandRange = 4000000;
	iRandRange = iRandRange * 100 / (100 + iDropBonus);

	return true;
}


// Alt©¥na ekle


#if defined(__SEND_TARGET_INFO__)
void ITEM_MANAGER::GetMonsterItemDropMap(LPCHARACTER pkChr, LPCHARACTER pkKiller, MonsterItemDropMap& rItemDropMap, bool& bDropMetinStone)
{
	if (pkChr->IsPolymorphed() || pkChr->IsPC())
		return;

	int iLevel = pkKiller->GetLevel();
	BYTE bRank = pkChr->GetMobRank();

	bool bShowCommonDrop = true;
	bool bShowDropItemGroup = true;
	bool bShowMobItemGroup = true;
	bool bShowLevelItemGroup = true;
	bool bShowGloveItemGroup = true;
	bool bShowEtcItemDrop = true;
	bool bShowDropMetinStone = true;

	//////////////////////////////////////////////////////////////////////////////////////////////
	// CommonDropItem (common_drop_item.txt)
	if (bShowCommonDrop)
	{
		std::vector<CItemDropInfo>::iterator it = g_vec_pkCommonDropItem[bRank].begin();
		while (it != g_vec_pkCommonDropItem[bRank].end())
		{
			const CItemDropInfo& c_rInfo = *(it++);
			if (iLevel < c_rInfo.m_iLevelStart || iLevel > c_rInfo.m_iLevelEnd)
				continue;

			DWORD dwVnum = c_rInfo.m_dwVnum;
			TItemTable* table = GetTable(dwVnum);
			if (!table)
				continue;

			MonsterItemDropMap::iterator it = rItemDropMap.find(dwVnum);
			if (it == rItemDropMap.end())
				rItemDropMap.insert(std::make_pair(dwVnum, 1));
		}
	}
	// CommonDropItem
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	// DropItemGroup
	if (bShowDropItemGroup)
	{
		pkDropItemGroupMap::const_iterator it = m_map_pkDropItemGroup.find(pkChr->GetRaceNum());
		if (it != m_map_pkDropItemGroup.end())
		{
			DropItemGroupInfoVector v = it->second->GetVector();
			for (DWORD i = 0; i < v.size(); ++i)
			{
				DWORD dwVnum = v[i].dwVnum;
				MonsterItemDropMap::iterator it = rItemDropMap.find(dwVnum);
				if (it == rItemDropMap.end())
					rItemDropMap.insert(std::make_pair(dwVnum, v[i].iCount));
			}
		}
	}
	// DropItemGroup
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	// MobItemGroup
	if (bShowMobItemGroup)
	{
		pkMobItemGroupMap::const_iterator it = m_map_pkMobItemGroup.find(pkChr->GetRaceNum());
		if (it != m_map_pkMobItemGroup.end())
		{
			CMobItemGroup* pGroup = it->second;
			if (pGroup && !pGroup->IsEmpty())
			{
				const SMobItemGroupInfo& info = pGroup->GetOne();
				DWORD dwVnum = info.dwItemVnum;
				MonsterItemDropMap::iterator it = rItemDropMap.find(dwVnum);
				if (it == rItemDropMap.end())
					rItemDropMap.insert(std::make_pair(dwVnum, info.iCount));
			}
		}
	}
	// MobItemGroup
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	// LevelItemGroup (mob_drop_item.txt) type(limit)
	if (bShowLevelItemGroup)
	{
		pkLevelItemGroupMap::const_iterator it = m_map_pkLevelItemGroup.find(pkChr->GetRaceNum());
		if (it != m_map_pkLevelItemGroup.end())
		{
			if (it->second->GetLevelLimit() <= static_cast<DWORD>(iLevel))
			{
				LevelItemGroupInfoVector v = it->second->GetVector();
				for (DWORD i = 0; i < v.size(); i++)
				{
					DWORD dwVnum = v[i].dwVNum;
					MonsterItemDropMap::iterator it = rItemDropMap.find(dwVnum);
					if (it == rItemDropMap.end())
						rItemDropMap.insert(std::make_pair(dwVnum, v[i].iCount));
				}
			}
		}
	}
	// LevelItemGroup
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	// GloveItemGroup (mob_drop_item.txt) type(thiefgloves) - Drops only if you are using gloves.
	if (bShowGloveItemGroup)
	{
		if (pkKiller->GetPremiumRemainSeconds(PREMIUM_ITEM) > 0 ||
			pkKiller->IsEquipUniqueGroup(UNIQUE_GROUP_DOUBLE_ITEM))
		{
			pkGloveItemGroupMap::const_iterator it = m_map_pkGloveItemGroup.find(pkChr->GetRaceNum());
			if (it != m_map_pkGloveItemGroup.end())
			{
				ItemThiefGroupInfoVector v = it->second->GetVector();
				for (DWORD i = 0; i < v.size(); ++i)
				{
					DWORD dwVnum = v[i].dwVnum;
					MonsterItemDropMap::iterator it = rItemDropMap.find(dwVnum);
					if (it == rItemDropMap.end())
						rItemDropMap.insert(std::make_pair(dwVnum, v[i].iCount));
				}
			}
		}
	}
	// GloveItemGroup
	//////////////////////////////////////////////////////////////////////////////////////////////

	if (bShowEtcItemDrop && pkChr->GetMobDropItemVnum())
	{
		EtcItemDropProbMap::const_iterator it = m_map_dwEtcItemDropProb.find(pkChr->GetMobDropItemVnum());
		if (it != m_map_dwEtcItemDropProb.end())
		{
			MonsterItemDropMap::iterator it = rItemDropMap.find(pkChr->GetMobDropItemVnum());
			if (it == rItemDropMap.end())
				rItemDropMap.insert(std::make_pair(pkChr->GetMobDropItemVnum(), 1));
		}
	}

	if (bShowDropMetinStone && pkChr->IsStone())
	{
		const DWORD dwMetinStoneVnum = pkChr->GetDropMetinStoneVnum();
		if (dwMetinStoneVnum)
		{
			MonsterItemDropMap::iterator it = rItemDropMap.find(dwMetinStoneVnum);
			if (it == rItemDropMap.end())
			{
				//rItemDropMap.insert(std::make_pair(pkChr->GetDropMetinStoneVnum(), 1));
				bDropMetinStone = true;
			}
		}
	}
}

bool ITEM_MANAGER::CreateDropItemVector(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM>& vec_item)
{
	if (pkChr->IsPolymorphed() || pkChr->IsPC())
	{
		return false;
	}

	int iLevel = pkKiller->GetLevel();

	BYTE bRank = pkChr->GetMobRank();
	LPITEM item = NULL;

	std::vector<CItemDropInfo>::iterator it = g_vec_pkCommonDropItem[bRank].begin();

	while (it != g_vec_pkCommonDropItem[bRank].end())
	{
		const CItemDropInfo& c_rInfo = *(it++);

		if (iLevel < c_rInfo.m_iLevelStart || iLevel > c_rInfo.m_iLevelEnd)
			continue;

		TItemTable* table = GetTable(c_rInfo.m_dwVnum);

		if (!table)
			continue;

		item = NULL;

		if (table->bType == ITEM_POLYMORPH)
		{
			if (c_rInfo.m_dwVnum == pkChr->GetPolymorphItemVnum())
			{
				item = CreateItem(c_rInfo.m_dwVnum, 1, 0, true);

				if (item)
					item->SetSocket(0, pkChr->GetRaceNum());
			}
		}
		else
			item = CreateItem(c_rInfo.m_dwVnum, 1, 0, true);

		if (item) vec_item.push_back(item);
	}

	// Drop Item Group
	{
		pkDropItemGroupMap::const_iterator it = m_map_pkDropItemGroup.find(pkChr->GetRaceNum());

		if (it != m_map_pkDropItemGroup.end())
		{
			DropItemGroupInfoVector v = it->second->GetVector();

			for (DWORD i = 0; i < v.size(); ++i)
			{
				item = CreateItem(v[i].dwVnum, v[i].iCount, 0, true);

				if (item)
				{
					if (item->GetType() == ITEM_POLYMORPH)
					{
						if (item->GetVnum() == pkChr->GetPolymorphItemVnum())
						{
							item->SetSocket(0, pkChr->GetRaceNum());
						}
					}

					vec_item.push_back(item);
				}
			}
		}
	}

	// MobDropItem Group
	{
		pkMobItemGroupMap::const_iterator it = m_map_pkMobItemGroup.find(pkChr->GetRaceNum());

		if (it != m_map_pkMobItemGroup.end())
		{
			CMobItemGroup* pGroup = it->second;

			// MOB_DROP_ITEM_BUG_FIX
			if (pGroup && !pGroup->IsEmpty())
			{
				const SMobItemGroupInfo& info = pGroup->GetOne();
				item = CreateItem(info.dwItemVnum, info.iCount, 0, true, info.iRarePct);

				if (item) vec_item.push_back(item);
			}
			// END_OF_MOB_DROP_ITEM_BUG_FIX
		}
	}

	// Level Item Group
	{
		pkLevelItemGroupMap::const_iterator it = m_map_pkLevelItemGroup.find(pkChr->GetRaceNum());

		if (it != m_map_pkLevelItemGroup.end())
		{
			if (it->second->GetLevelLimit() <= (DWORD)iLevel)
			{
				LevelItemGroupInfoVector v = it->second->GetVector();

				for (DWORD i = 0; i < v.size(); i++)
				{
					DWORD dwVnum = v[i].dwVNum;
					item = CreateItem(dwVnum, v[i].iCount, 0, true);
					if (item) vec_item.push_back(item);
				}
			}
		}
	}

	// BuyerTheifGloves Item Group
	{
		if (pkKiller->GetPremiumRemainSeconds(PREMIUM_ITEM) > 0 ||
			pkKiller->IsEquipUniqueGroup(UNIQUE_GROUP_DOUBLE_ITEM))
		{
			pkGloveItemGroupMap::const_iterator it = m_map_pkGloveItemGroup.find(pkChr->GetRaceNum());

			if (it != m_map_pkGloveItemGroup.end())
			{
				ItemThiefGroupInfoVector v = it->second->GetVector();

				for (DWORD i = 0; i < v.size(); ++i)
				{
					DWORD dwVnum = v[i].dwVnum;
					item = CreateItem(dwVnum, v[i].iCount, 0, true);
					if (item) vec_item.push_back(item);
				}
			}
		}
	}

	if (pkChr->GetMobDropItemVnum())
	{
		EtcItemDropProbMap::const_iterator it = m_map_dwEtcItemDropProb.find(pkChr->GetMobDropItemVnum());

		if (it != m_map_dwEtcItemDropProb.end())
		{
			item = CreateItem(pkChr->GetMobDropItemVnum(), 1, 0, true);
			if (item) vec_item.push_back(item);
		}
	}

	if (pkChr->IsStone())
	{
		if (pkChr->GetDropMetinStoneVnum())
		{
			item = CreateItem(pkChr->GetDropMetinStoneVnum(), 1, 0, true);
			if (item) vec_item.push_back(item);
		}
	}

	return vec_item.size();
}
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################
