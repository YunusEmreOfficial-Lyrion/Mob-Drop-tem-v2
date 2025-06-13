//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

// Arat

void CInputMain::Refine(LPCHARACTER ch, const char* c_pData)
{
	
}

// Alt©¥na ekle


#if defined(__SEND_TARGET_INFO__)
void CInputMain::TargetInfo(LPCHARACTER pChar, const char* c_pszData)
{
	const TPacketCGTargetInfo* c_pData = reinterpret_cast<const TPacketCGTargetInfo*>(c_pszData);
	const LPCHARACTER pkTarget = CHARACTER_MANAGER::instance().Find(c_pData->dwVID);
	if (pChar == nullptr || pkTarget == nullptr)
		return;

	const DWORD dwVID = pkTarget->GetVID();
	const DWORD dwRaceVnum = pkTarget->GetRaceNum();

	if (pkTarget->IsMonster() || pkTarget->IsStone())
	{
		MonsterItemDropMap ItemDropMap; bool bDropMetinStone = false;
		ITEM_MANAGER::instance().GetMonsterItemDropMap(pkTarget, pChar, ItemDropMap, bDropMetinStone);

		TEMP_BUFFER TempBuffer;
		for (const MonsterItemDropMap::value_type& it : ItemDropMap)
		{
			TPacketGCTargetDropInfo DropInfoPacket;
			DropInfoPacket.dwVnum = it.first;
			DropInfoPacket.bCount = it.second;
			TempBuffer.write(&DropInfoPacket, sizeof(DropInfoPacket));
		}

		TPacketGCTargetInfo TargetInfoPacket;
		TargetInfoPacket.bHeader = HEADER_GC_TARGET_INFO;
		TargetInfoPacket.wSize = sizeof(TargetInfoPacket) + TempBuffer.size();
		TargetInfoPacket.dwRaceVnum = dwRaceVnum;
		TargetInfoPacket.dwVID = dwVID;
		TargetInfoPacket.bDropMetinStone = bDropMetinStone;

		if (TempBuffer.size())
		{
			pChar->GetDesc()->BufferedPacket(&TargetInfoPacket, sizeof(TargetInfoPacket));
			pChar->GetDesc()->Packet(TempBuffer.read_peek(), TempBuffer.size());
		}
		else
			pChar->GetDesc()->Packet(&TargetInfoPacket, sizeof(TargetInfoPacket));
	}

	pChar->ChatPacket(CHAT_TYPE_COMMAND, "RefreshMonsterDropInfo %d", pkTarget->GetRaceNum());
}
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

//  Arat

		case HEADER_CG_CLIENT_VERSION:
			Version(ch, c_pData);
			break;

#if defined(__DRAGON_SOUL_SYSTEM__)
		case HEADER_CG_DRAGON_SOUL_REFINE:
		{
			TPacketCGDragonSoulRefine* p = reinterpret_cast <TPacketCGDragonSoulRefine*>((void*)c_pData);
			switch (p->bSubType)
			{
				case DS_SUB_HEADER_CLOSE:
					ch->DragonSoul_RefineWindow_Close();
					break;

				case DS_SUB_HEADER_DO_REFINE_GRADE:
				{
					DSManager::instance().DoRefineGrade(ch, p->ItemGrid);
				}
				break;

				case DS_SUB_HEADER_DO_REFINE_STEP:
				{
					DSManager::instance().DoRefineStep(ch, p->ItemGrid);
				}
				break;

				case DS_SUB_HEADER_DO_REFINE_STRENGTH:
				{
					DSManager::instance().DoRefineStrength(ch, p->ItemGrid);
				}
				break;

#if defined(__DS_CHANGE_ATTR__)
				case DS_SUB_HEADER_DO_CHANGE_ATTR:
				{
					DSManager::instance().DoChangeAttribute(ch, p->ItemGrid);
				}
				break;
#endif
			}
		}
		break;
#endif

// Alt©¥na ekle

#if defined(__SEND_TARGET_INFO__)
		case HEADER_CG_TARGET_INFO:
			TargetInfo(ch, c_pData);
			break;
#endif

//#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################