//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat


void CPythonNetworkStream::ServerCommand(char* c_szCommand)
{
	// #0000811: [M2EU] ??? ?? ?? 
	if (strcmpi(c_szCommand, "ConsoleEnable") == 0)
		return;

	if (m_apoPhaseWnd[PHASE_WINDOW_GAME])
	{
		bool isTrue;
		if (PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME],
			"BINARY_ServerCommand_Run",
			Py_BuildValue("(s)", c_szCommand),
			&isTrue
		))
		{
			if (isTrue)
				return;
		}
	}
	else if (m_poSerCommandParserWnd)
	{
		bool isTrue;
		if (PyCallClassMemberFunc(m_poSerCommandParserWnd,
			"BINARY_ServerCommand_Run",
			Py_BuildValue("(s)", c_szCommand),
			&isTrue
		))
		{
			if (isTrue)
				return;
		}
	}

	CTokenVector TokenVector;
	if (!SplitToken(c_szCommand, &TokenVector))
		return;

	if (TokenVector.empty())
		return;

	const char* szCmd = TokenVector[0].c_str();

#if defined(ENABLE_EVENT_BANNER)
	// NOTE : Instead of creating an additional packet to enable events, we will just
	// take advantage of the command packet and filter the existing events, making it
	// easier to control. However, this code below is subject to change in the future
	// to its own packet.
	BYTE bInGameEventType = CPythonInGameEventSystemManager::Instance().GetInGameEventType(szCmd);
	if (bInGameEventType != CPythonInGameEventSystemManager::INGAME_EVENT_TYPE_NONE)
	{
		if (2 != TokenVector.size())
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %d", c_szCommand, TokenVector.size());
			return;
		}

		int iFlag = atoi(TokenVector[1].c_str());
		CPythonInGameEventSystemManager::Instance().SetInGameEventEnable(bInGameEventType, iFlag);
		return;
	}
#endif

	if (!strcmpi(szCmd, "quit"))
	{
		PostQuitMessage(0);
	}
	else if (!strcmpi(szCmd, "BettingMoney"))
	{
		if (2 != TokenVector.size())
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		// UINT uMoney = atoi(TokenVector[1].c_str());
	}


// Altýna ekle

#if defined(ENABLE_SEND_TARGET_INFO)
	else if (!strcmpi(szCmd, "RefreshMonsterDropInfo"))
	{
		if (TokenVector.size() != 2)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		const DWORD dwRace = atoi(TokenVector[1].c_str());
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_RefreshTargetMonsterDropInfo", Py_BuildValue("(i)", dwRace));
	}
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################
