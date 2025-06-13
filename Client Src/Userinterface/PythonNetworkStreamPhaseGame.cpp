//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

			case HEADER_GC_HYBRIDCRYPT_SDB:
				RecvHybridCryptSDBPacket();
				return;

#if defined(__IMPROVED_PACKET_ENCRYPTION__)
			case HEADER_GC_KEY_AGREEMENT:
				RecvKeyAgreementPacket();
				return;

			case HEADER_GC_KEY_AGREEMENT_COMPLETED:
				RecvKeyAgreementCompletedPacket();
				return;
#endif

			case HEADER_GC_SPECIFIC_EFFECT:
				ret = RecvSpecificEffect();
				break;

#if defined(ENABLE_DRAGON_SOUL_SYSTEM)
			case HEADER_GC_DRAGON_SOUL_REFINE:
				ret = RecvDragonSoulRefine();
				break;
#endif

// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
			case HEADER_GC_TARGET_INFO:
				ret = RecvTargetInfoPacket();
				break;
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat


void CPythonNetworkStream::SetGamePhase()
{
	if ("Game" != m_strPhase)
		m_phaseLeaveFunc.Run();

	Tracen("");
	Tracen("## Network - Game Phase ##");
	Tracen("");

	m_strPhase = "Game";

	m_dwChangingPhaseTime = ELTimer_GetMSec();
	m_phaseProcessFunc.Set(this, &CPythonNetworkStream::GamePhase);
	m_phaseLeaveFunc.Set(this, &CPythonNetworkStream::__LeaveGamePhase);

	// Main Character ??O

	IAbstractPlayer& rkPlayer = IAbstractPlayer::GetSingleton();
	rkPlayer.SetMainCharacterIndex(GetMainActorVID());

	__RefreshStatus();
}

// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
bool CPythonNetworkStream::SendTargetInfoPacket(DWORD dwVID)
{
	TPacketCGTargetInfo TargetInfoPacket;
	TargetInfoPacket.bHeader = HEADER_CG_TARGET_INFO;
	TargetInfoPacket.dwVID = dwVID;

	if (!Send(sizeof(TargetInfoPacket), &TargetInfoPacket))
		return false;

	return SendSequence();
}
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

bool CPythonNetworkStream::RecvTargetPacket()
{
	TPacketGCTarget TargetPacket;

	if (!Recv(sizeof(TPacketGCTarget), &TargetPacket))
	{
		Tracen("Recv Target Packet Error");
		return false;
	}

#if defined(ENABLE_DEFENSE_WAVE)
	if (TargetPacket.bAlliance)
	{
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetHPAllianceTargetBoard",
			Py_BuildValue("(iii)", TargetPacket.dwVID, TargetPacket.iMinHP, TargetPacket.iMaxHP));
		return true;
	}
#endif

	CInstanceBase* pInstPlayer = CPythonCharacterManager::Instance().GetMainInstancePtr();
	CInstanceBase* pInstTarget = CPythonCharacterManager::Instance().GetInstancePtr(TargetPacket.dwVID);
	if (pInstPlayer && pInstTarget)
	{
		if (!pInstTarget->IsDead())
		{
#if defined(ENABLE_VIEW_TARGET_PLAYER_HP)
			if (pInstTarget->IsBuilding())
#else
			if (pInstTarget->IsPC() || pInstTarget->IsBuilding())
#endif
			{
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "CloseTargetBoardIfDifferent", Py_BuildValue("(i)", TargetPacket.dwVID));
			}
			else if (pInstPlayer->CanViewTargetHP(*pInstTarget))
			{
#if defined(ENABLE_VIEW_TARGET_DECIMAL_HP)
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetHPTargetBoard", Py_BuildValue("(iiii)", TargetPacket.dwVID, TargetPacket.bHPPercent, TargetPacket.iMinHP, TargetPacket.iMaxHP));
#else
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetHPTargetBoard", Py_BuildValue("(ii)", TargetPacket.dwVID, TargetPacket.bHPPercent));
#endif

#if defined(ENABLE_ELEMENT_ADD)
				PyObject* poDict = PyDict_New();
				for (BYTE bElementIndex = 0; bElementIndex < CPythonNonPlayer::MOB_ELEMENT_MAX_NUM; ++bElementIndex)
				{
					PyDict_SetItem(poDict,
						Py_BuildValue("i", bElementIndex),
						Py_BuildValue("i", TargetPacket.bElement[bElementIndex]));
				}
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "ShowTargetElementEnchant", Py_BuildValue("(O)", poDict));
				Py_DECREF(poDict);
#endif
			}
			else
			{
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "CloseTargetBoard", Py_BuildValue("()"));
			}

			m_pInstTarget = pInstTarget;
		}
	}
	else
	{
		CPythonPlayer::Instance().SetTarget(0);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "CloseTargetBoard", Py_BuildValue("()"));
	}

	return true;
}

// Altýna ekle


#if defined(ENABLE_SEND_TARGET_INFO)
bool CPythonNetworkStream::RecvTargetInfoPacket()
{
	TPacketGCTargetInfo TargetInfoPacket;
	if (!Recv(sizeof(TPacketGCTargetInfo), &TargetInfoPacket))
	{
		Tracen("Recv TargetInfo Packet Error");
		return false;
	}

	CPythonNonPlayer::Instance().ClearItemDrop();

	CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetInstancePtr(TargetInfoPacket.dwVID);
	if (pInstance && (pInstance->IsEnemy() || pInstance->IsStone() && !pInstance->IsDead()))
	{
		UINT uiPacketSize = (TargetInfoPacket.wSize - sizeof(TPacketGCTargetInfo));
		for (; uiPacketSize > 0; uiPacketSize -= sizeof(TPacketGCTargetDropInfo))
		{
			TPacketGCTargetDropInfo TargetDropInfoPacket;
			if (!Recv(sizeof(TargetDropInfoPacket), &TargetDropInfoPacket))
				return false;

			CPythonNonPlayer::Instance().AddItemDrop(
				TargetInfoPacket.dwRaceVnum,
				TargetDropInfoPacket.dwVnum,
				TargetDropInfoPacket.bCount
			);
		}

		CPythonNonPlayer::Instance().SetDropMetinStone(TargetInfoPacket.bDropMetinStone);
	}
	else
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "CloseTargetBoard", Py_BuildValue("()"));

	return true;
}
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################
