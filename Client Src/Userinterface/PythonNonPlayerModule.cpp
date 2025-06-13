//#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

void initNonPlayer()

// Üstüne ekle

#if defined(ENABLE_SEND_TARGET_INFO)
PyObject* nonplayerGetRaceByVID(PyObject* poSelf, PyObject* poArgs)
{
	int iVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVID))
		return Py_BuildException();

	CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetInstancePtr(iVID);
	if (NULL == pInstance)
		return Py_BuildValue("i", -1);

	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetTable(pInstance->GetVirtualNumber());
	if (NULL == pMobData)
		return Py_BuildValue("i", -1);

	return Py_BuildValue("i", pMobData->dwVnum);
}

PyObject* nonplayerSelectMob(PyObject* poSelf, PyObject* poArgs)
{
	int iVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iVnum))
		return Py_BadArgument();

	if (!CPythonNonPlayer::Instance().SelectMobData(iVnum))
		TraceError("Cannot select mob data by race %d", iVnum);

	return Py_BuildNone();
}

PyObject* nonplayerIsEnemy(PyObject* poSelf, PyObject* poArgs)
{
	const CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("b", pMobData->bType == CActorInstance::TYPE_ENEMY);
}

PyObject* nonplayerIsStone(PyObject* poSelf, PyObject* poArgs)
{
	const CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("b", pMobData->bType == CActorInstance::TYPE_STONE);
}

PyObject* nonplayerGetLevel(PyObject* poSelf, PyObject* poArgs)
{
	const CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->bLevel);
}

#if defined(__HIT_RANGE_RENEWAL__)
PyObject* nonplayerGetHitRange(PyObject* poSelf, PyObject* poArgs)
{
	const CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("f", CPythonNonPlayer::Instance().GetMonsterHitRange(pMobData->dwVnum));
}
#endif

PyObject* nonplayerGetExp(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwExp);
}

#if defined(ENABLE_CONQUEROR_LEVEL)
PyObject* nonplayerGetSungMaExp(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwSungMaExp);
}
#endif

PyObject* nonplayerGetMaxHP(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwMaxHP);
}

PyObject* nonplayerGetRegenCycle(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->bRegenCycle);
}

PyObject* nonplayerGetRegenPercent(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->bRegenPercent);
}

PyObject* nonplayerGetMinGold(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwGoldMin);
}

PyObject* nonplayerGetMaxGold(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwGoldMax);
}

PyObject* nonplayerGetAIFlag(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwAIFlag);
}

PyObject* nonplayerGetRaceFlag(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwRaceFlag);
}

PyObject* nonplayerGetImmuneFlag(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->dwImmuneFlag);
}

PyObject* nonplayerGetEnchant(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bEnchantNum;
	if (!PyTuple_GetByte(poArgs, 0, &bEnchantNum))
		return Py_BuildException();

	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	if (bEnchantNum >= CPythonNonPlayer::MOB_ENCHANTS_MAX_NUM)
		return 0;

	return Py_BuildValue("i", pMobData->cEnchants[bEnchantNum]);
}

PyObject* nonplayerGetResist(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bResistNum;
	if (!PyTuple_GetByte(poArgs, 0, &bResistNum))
		return Py_BuildException();

	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	if (bResistNum >= CPythonNonPlayer::MOB_RESISTS_MAX_NUM)
		return 0;

	return Py_BuildValue("i", pMobData->cResists[bResistNum]);
}

#if defined(ENABLE_ELEMENT_ADD)
PyObject* nonplayerGetResistDark(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->cResistDark);
}

PyObject* nonplayerGetResistIce(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->cResistIce);
}

PyObject* nonplayerGetResistEarth(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->cResistEarth);
}

PyObject* nonplayerGetElement(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bResistNum;
	if (!PyTuple_GetByte(poArgs, 0, &bResistNum))
		return Py_BuildException();

	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	if (bResistNum >= CPythonNonPlayer::MOB_ELEMENT_MAX_NUM)
		return 0;

	return Py_BuildValue("i", pMobData->cElements[bResistNum]);
}
#endif

PyObject* nonplayerGetDamage(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("ii", pMobData->dwDamageRange[0], pMobData->dwDamageRange[1]);
}

PyObject* nonplayerGetDamMultiply(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("f", pMobData->fDamMultiply);
}

PyObject* nonplayerGetST(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->bStr);
}

PyObject* nonplayerGetDX(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->bDex);
}

PyObject* nonplayerGetHT(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->bCon);
}

PyObject* nonplayerGetIQ(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNonPlayer::TMobTable* pMobData = CPythonNonPlayer::Instance().GetSelectedMobDataPointer();
	if (NULL == pMobData)
		return Py_BuildException("Cannot select mob data.");

	return Py_BuildValue("i", pMobData->bInt);
}

// Monster Drop
#include "../EterBase/Grid.h"
#include "../GameLib/ItemManager.h"
static int __CreateDropPage(CPythonNonPlayer::TMobDropItemVec* pVec, PyObject* poList)
{
	int iPageCount(0);
	CGrid Grid(CPythonNonPlayer::MAX_MOB_ITEM_DROP_GRID_SLOT_X, CPythonNonPlayer::MAX_MOB_ITEM_DROP_GRID_SLOT_Y);

	if (pVec && !pVec->empty())
	{
		for (CPythonNonPlayer::TMobDropItemVec::const_iterator it = pVec->begin(); it != pVec->end(); ++it)
		{
			const CPythonNonPlayer::SMobItemDrop& rItem = *it;
			CItemData* pItemData;
			if (!CItemManager::Instance().GetItemDataPointer(rItem.dwVnum, &pItemData))
				continue;

			const BYTE bItemSize = pItemData->GetSize();
			while (true)
			{
				const int iPos = Grid.FindBlank(1, bItemSize);
				if (iPos >= 0)
				{
					Grid.Put(iPos, 1, bItemSize);

					PyObject* pItemTuple = Py_BuildValue("iiii", iPageCount, iPos, rItem.dwVnum, rItem.wCount);
					if (pItemTuple)
					{
						PyList_Append(poList, pItemTuple);
						Py_DECREF(pItemTuple);
					}

					break;
				}
				else
				{
					Grid.Clear();
					++iPageCount;
				}
			}
		}
	}

	return iPageCount;
}

PyObject* nonplayerHasMonsterItemDrop(PyObject* poSelf, PyObject* poArgs)
{
	int iRaceVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iRaceVnum))
		return Py_BadArgument();

	CPythonNonPlayer::TMobDropItemVec* pVec = CPythonNonPlayer::Instance().GetItemDropVec(iRaceVnum);
	return Py_BuildValue("b", (pVec && !pVec->empty()));
}

PyObject* nonplayerGetMonsterItemDrop(PyObject* poSelf, PyObject* poArgs)
{
	int iRaceVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iRaceVnum))
		return Py_BadArgument();

	PyObject* poList = PyList_New(0);
	if (!poList)
		return Py_BuildException();

	CPythonNonPlayer::TMobDropItemVec* pVec = CPythonNonPlayer::Instance().GetItemDropVec(iRaceVnum);
	const int iPageCount = __CreateDropPage(pVec, poList);

	PyObject* pResult = Py_BuildValue("iO", iPageCount, poList);
	Py_DECREF(poList);

	if (!pResult)
		return Py_BuildException();

	return pResult;
}

PyObject* nonplayerGetDropMetinStone(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("b", CPythonNonPlayer::Instance().GetDropMetinStone());
}
#endif

//#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	static PyMethodDef s_methods[] =
	{
		{ "GetEventType", nonplayerGetEventType, METH_VARARGS },
		{ "GetEventTypeByVID", nonplayerGetEventTypeByVID, METH_VARARGS },
		{ "GetVnumByVID", nonplayerGetVnumByVID, METH_VARARGS },
		{ "GetLevelByVID", nonplayerGetLevelByVID, METH_VARARGS },
		{ "GetGradeByVID", nonplayerGetGradeByVID, METH_VARARGS },
		{ "GetMonsterName", nonplayerGetMonsterName, METH_VARARGS },


// Altına ekle


#if defined(ENABLE_SEND_TARGET_INFO)
		{ "GetRaceByVID", nonplayerGetRaceByVID, METH_VARARGS },
		{ "SelectMob", nonplayerSelectMob, METH_VARARGS },

		{ "IsEnemy", nonplayerIsEnemy, METH_VARARGS },
		{ "IsStone", nonplayerIsStone, METH_VARARGS },
		{ "GetLevel", nonplayerGetLevel, METH_VARARGS },
#if defined(__HIT_RANGE_RENEWAL__)
		{ "GetHitRange", nonplayerGetHitRange, METH_VARARGS },
#endif

		{ "GetAIFlag", nonplayerGetAIFlag, METH_VARARGS },
		{ "GetRaceFlag", nonplayerGetRaceFlag, METH_VARARGS },
		{ "GetImmuneFlag", nonplayerGetImmuneFlag, METH_VARARGS },
		{ "GetEnchant", nonplayerGetEnchant, METH_VARARGS },
		{ "GetResist", nonplayerGetResist, METH_VARARGS },
#if defined(ENABLE_ELEMENT_ADD)
		{ "GetResistDark", nonplayerGetResistDark, METH_VARARGS },
		{ "GetResistIce", nonplayerGetResistIce, METH_VARARGS },
		{ "GetResistEarth", nonplayerGetResistEarth, METH_VARARGS },

		{ "GetElement", nonplayerGetElement, METH_VARARGS },
#endif

		{ "GetDamage", nonplayerGetDamage, METH_VARARGS },
		{ "GetDamMultiply", nonplayerGetDamMultiply, METH_VARARGS },

		{ "GetST", nonplayerGetST, METH_VARARGS },
		{ "GetDX", nonplayerGetDX, METH_VARARGS },
		{ "GetHT", nonplayerGetHT, METH_VARARGS },
		{ "GetIQ", nonplayerGetIQ, METH_VARARGS },

		{ "GetMaxHP", nonplayerGetMaxHP, METH_VARARGS },
		{ "GetRegenCycle", nonplayerGetRegenCycle, METH_VARARGS },
		{ "GetRegenPercent", nonplayerGetRegenPercent, METH_VARARGS },

		{ "GetMinGold", nonplayerGetMinGold, METH_VARARGS },
		{ "GetMaxGold", nonplayerGetMaxGold, METH_VARARGS },

		{ "GetExp", nonplayerGetExp, METH_VARARGS },
#if defined(ENABLE_CONQUEROR_LEVEL)
		{ "GetSungMaExp", nonplayerGetSungMaExp, METH_VARARGS },
#endif

		// Monster Item Drop
		{ "HasMonsterItemDrop", nonplayerHasMonsterItemDrop, METH_VARARGS },
		{ "GetMonsterItemDrop", nonplayerGetMonsterItemDrop, METH_VARARGS },
		{ "GetDropMetinStone", nonplayerGetDropMetinStone, METH_VARARGS },
#endif

//#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

	PyModule_AddIntConstant(poModule, "RACE_FLAG_ANIMAL", CPythonNonPlayer::RACE_FLAG_ANIMAL);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_UNDEAD", CPythonNonPlayer::RACE_FLAG_UNDEAD);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_DEVIL", CPythonNonPlayer::RACE_FLAG_DEVIL);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_HUMAN", CPythonNonPlayer::RACE_FLAG_HUMAN);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ORC", CPythonNonPlayer::RACE_FLAG_ORC);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_MILGYO", CPythonNonPlayer::RACE_FLAG_MILGYO);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_INSECT", CPythonNonPlayer::RACE_FLAG_INSECT);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_DESERT", CPythonNonPlayer::RACE_FLAG_DESERT);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_TREE", CPythonNonPlayer::RACE_FLAG_TREE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_DECO", CPythonNonPlayer::RACE_FLAG_DECO);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_HIDE", CPythonNonPlayer::RACE_FLAG_HIDE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_ATT_CZ", CPythonNonPlayer::RACE_FLAG_ATT_CZ);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_AWEAKEN", CPythonNonPlayer::RACE_FLAG_AWEAKEN);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_SUNGMAHEE", CPythonNonPlayer::RACE_FLAG_SUNGMAHEE);
	PyModule_AddIntConstant(poModule, "RACE_FLAG_OUTPOST", CPythonNonPlayer::RACE_FLAG_OUTPOST);

// Altına ekle


#if defined(ENABLE_SEND_TARGET_INFO)
	PyModule_AddIntConstant(poModule, "MAX_MOB_ITEM_DROP_GRID_SLOT_X", CPythonNonPlayer::MAX_MOB_ITEM_DROP_GRID_SLOT_X);
	PyModule_AddIntConstant(poModule, "MAX_MOB_ITEM_DROP_GRID_SLOT_Y", CPythonNonPlayer::MAX_MOB_ITEM_DROP_GRID_SLOT_Y);
	PyModule_AddIntConstant(poModule, "MAX_MOB_ITEM_DROP_GRID_SIZE", CPythonNonPlayer::MAX_MOB_ITEM_DROP_GRID_SIZE);
#endif

//#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################
