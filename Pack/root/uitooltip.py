#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat

	def SetExchangeOwnerItem(self, slotIndex):
		itemVnum = exchange.GetItemVnumFromSelf(slotIndex)

		if 0 == itemVnum:
			return

		self.ClearToolTip()

		metinSlot = [exchange.GetItemMetinSocketFromSelf(slotIndex, i) for i in xrange(player.METIN_SOCKET_MAX_NUM)]
		attrSlot = [exchange.GetItemAttributeFromSelf(slotIndex, i) for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM)]
		refine_element = exchange.GetItemRefineElementFromSelf(slotIndex) if app.ENABLE_REFINE_ELEMENT_SYSTEM else None
		apply_random_list = [exchange.GetItemApplyRandomFromSelf(slotIndex, i) for i in xrange(player.APPLY_RANDOM_SLOT_MAX_NUM)] if app.ENABLE_APPLY_RANDOM else []
		set_value = exchange.GetItemSetValueFromSelf(slotIndex) if app.ENABLE_SET_ITEM else 0

		self.AddItemData(itemVnum, metinSlot, attrSlot, None, 0, 0, player.INVENTORY, -1, refine_element, apply_random_list, set_value)

		if app.ENABLE_CHANGE_LOOK_SYSTEM:
			self.AppendChangeLookInfoExchangeWIndow(0, slotIndex)

## Alt©¥na ekle

	if app.ENABLE_SEND_TARGET_INFO:
		def SetItemToolTipBook(self, itemVnum):
			item.SelectItem(itemVnum)

			self.ClearToolTip()

			self.SetTitle(item.GetItemName())
			self.AppendDescription(item.GetItemDescription(), 26)
			self.AppendDescription(item.GetItemSummary(), 26, self.CONDITION_COLOR)
			self.ShowToolTip()

#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat


	def AddItemData(self, itemVnum, metinSlot, attrSlot = 0, rare_attr_slot = None, flags = 0, unbindTime = 0, window_type = player.INVENTORY, slotIndex = -1, refine_element = None, apply_random_list = None, set_value = 0):
		self.itemVnum = itemVnum
		self.metinSlot = metinSlot
		self.attrSlot = attrSlot

		item.SelectItem(itemVnum)
		itemType = item.GetItemType()
		itemSubType = item.GetItemSubType()

		if not item.GetItemDescription():
			self.__CalculateToolTipWidth()

		if 50026 == itemVnum:
			if 0 != metinSlot:
				name = item.GetItemName()
				if metinSlot[0] > 0:
					name += " "
					name += localeInfo.NumberToMoneyString(metinSlot[0])
				self.SetTitle(name)
				if app.ENABLE_SOULBIND_SYSTEM:
					self.__AppendSealInformation(window_type, slotIndex) ## cyh itemseal 2013 11 11
				self.ShowToolTip()
			return

## Alt©¥na ekle

		if app.ENABLE_SEND_TARGET_INFO:
			if itemType == item.ITEM_TYPE_SKILLBOOK or itemType == item.ITEM_TYPE_SKILLFORGET:
				if metinSlot != 0 and metinSlot[0] == 0:
					self.SetItemToolTipBook(itemVnum)
					return

#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

