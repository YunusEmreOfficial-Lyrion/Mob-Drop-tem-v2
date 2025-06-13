#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## İmportlardan sonra ekle  class TargetBoard(ui.ThinBoard): Bundan önce

if app.ENABLE_SEND_TARGET_INFO:
	import item
	import uiToolTip

	def IS_SET(flag, bit):
		return (flag & bit) != 0

	class TargetDetailsThinBoard(ui.ThinBoard):
		BOARD_WIDTH = 280
		BOARD_HEIGHT = 0

		RACE_FLAG_NAME_DICT = {
			nonplayer.RACE_FLAG_ANIMAL : localeInfo.TARGET_INFO_RACE_ANIMAL,
			nonplayer.RACE_FLAG_UNDEAD : localeInfo.TARGET_INFO_RACE_UNDEAD,
			nonplayer.RACE_FLAG_DEVIL : localeInfo.TARGET_INFO_RACE_DEVIL,
			nonplayer.RACE_FLAG_HUMAN : localeInfo.TARGET_INFO_RACE_HUMAN,
			nonplayer.RACE_FLAG_ORC : localeInfo.TARGET_INFO_RACE_ORC,
			nonplayer.RACE_FLAG_MILGYO : localeInfo.TARGET_INFO_RACE_MILGYO,
			nonplayer.RACE_FLAG_INSECT : localeInfo.TARGET_INFO_RACE_INSECT,
			nonplayer.RACE_FLAG_DESERT : localeInfo.TARGET_INFO_RACE_DESERT,
			nonplayer.RACE_FLAG_TREE : localeInfo.TARGET_INFO_RACE_TREE,
			nonplayer.RACE_FLAG_ATT_CZ : localeInfo.TARGET_INFO_RACE_ATT_CZ,
			nonplayer.RACE_FLAG_AWEAKEN : localeInfo.TARGET_INFO_RACE_AWEAKEN,
			nonplayer.RACE_FLAG_SUNGMAHEE : localeInfo.TARGET_INFO_RACE_SUNGMAHEE,
			nonplayer.RACE_FLAG_OUTPOST : localeInfo.TARGET_INFO_RACE_OUTPOST,
		}

		if app.ENABLE_ELEMENT_ADD:
			ELEMENT_ENCHANT_NAME_DICT = {
				0 : [ "d:/ymir work/ui/game/12zi/element/elect.sub", localeInfo.TARGET_INFO_ELEMENT_ELECT ],
				1 : [ "d:/ymir work/ui/game/12zi/element/fire.sub", localeInfo.TARGET_INFO_ELEMENT_FIRE ],
				2 : [ "d:/ymir work/ui/game/12zi/element/ice.sub", localeInfo.TARGET_INFO_ELEMENT_ICE ],
				3 : [ "d:/ymir work/ui/game/12zi/element/wind.sub", localeInfo.TARGET_INFO_ELEMENT_WIND ],
				4 : [ "d:/ymir work/ui/game/12zi/element/earth.sub", localeInfo.TARGET_INFO_ELEMENT_EARTH ],
				5 : [ "d:/ymir work/ui/game/12zi/element/dark.sub", localeInfo.TARGET_INFO_ELEMENT_DARK ],
			}

		PERCENT_BY_DELTA_LEVEL = [
			1, 5, 10, 20, 30, 50, 70, 80, 85, 90,
			92, 94, 96, 98, 100, 100, 105, 110, 115, 120,
			125, 130, 135, 140, 145, 150, 155, 160, 165, 170,
			180
		]

		QUESTION_BUTTON_ELEMENT = 0
		QUESTION_BUTTON_ATTR = 1
		QUESTION_BUTTON_REWARD = 2

		ELEMENT_TOOLTIP_LIST = [
			localeInfo.TARGET_INFO_ELEMENT_TOOLTIP_LIST1,
			localeInfo.TARGET_INFO_ELEMENT_TOOLTIP_LIST2
		]

		ATTR_TOOLTIP_LIST = [
			localeInfo.TARGET_INFO_ATTR_TOOLTIP_LIST1,
			localeInfo.TARGET_INFO_ATTR_TOOLTIP_LIST2
		]

		REWARD_TOOLTIP_LIST = [
			localeInfo.TARGET_INFO_REWARD_TOOLTIP_LIST1,
			localeInfo.TARGET_INFO_REWARD_TOOLTIP_LIST2,
			localeInfo.TARGET_INFO_REWARD_TOOLTIP_LIST3
		]

		THINBOARD_BAR_GAP = 3
		THINBOARD_BAR_COLOR = 0x66111111
		THINBOARD_BAR_TITLE_COLOR = 0xfffff571
		THINBOARD_BAR_TEXT_COLOR = 0xffFFFFE0

		def __init__(self, parent):
			ui.ThinBoard.__init__(self)

			self.SetSize(self.BOARD_WIDTH, 0)
			self.HideCorners(self.LT)
			self.HideCorners(self.RT)
			self.HideLine(self.T)

			self.parent = parent
			self.race_vnum = 0
			self.attr_page = 0
			self.attr_page_dict = {}
			self.attr_show_null_value = False
			self.attr_show_color = True

			self.children_list = []
			self.height = 0
			self.tooltip = uiToolTip.ToolTip()
			self.help_tooltip_height_dict = {}
			self.item_drop_window = MobItemDropWindow()

			self.has_attr = False
			if app.ENABLE_ELEMENT_ADD:
				self.has_element = False
			self.has_reward = True

			self.__LoadWindow()

		def __del__(self):
			ui.ThinBoard.__del__(self)
			self.attr_page_dict = {}
			self.children_list = []
			self.help_tooltip_height_dict = {}
			del self.tooltip
			del self.item_drop_window

		def __LoadWindow(self):
			self.SetWindowName("TargetDetailsThinBoard")
			self.SetPosition(0, 34)
			self.SetWindowHorizontalAlignCenter()
			self.SetSize(self.BOARD_WIDTH, self.BOARD_HEIGHT)

			self.__AppendSeperator()

		def __AppendHeight(self, height):
			self.height += height
			self.SetSize(self.BOARD_WIDTH, self.height)

		def __AppendSpace(self, height = 0):
			self.__AppendHeight(height if height else 5)

		def __AppendChild(self, child, height):
			self.children_list.append(child)
			self.__AppendHeight(height)

		def __AppendSeperator(self, space = 25):
			image = ui.ImageBox()
			image.SetParent(self)
			image.AddFlag("not_pick")
			image.LoadImage("d:/ymir work/ui/pattern/seperator.tga")
			image.SetPosition(0, self.height + image.GetTop() - 10)
			image.SetWindowHorizontalAlignCenter()
			image.Show()
			self.__AppendChild(image, space)

		def __AutoAppendTitleLine(self, text):
			text_line = self.__AutoAppendTextLine(text)
			text_line.SetPackedFontColor(0xfffff2cc)

		def __AutoAppendTextLine(self, text, font_color = 0, outline_color = 0):
			text_line = ui.TextLine()
			text_line.SetParent(self)
			text_line.SetPosition(0, self.height)
			text_line.SetWindowHorizontalAlignCenter()
			text_line.SetHorizontalAlignCenter()
			text_line.SetText(text)
			if font_color != 0:
				text_line.SetPackedFontColor(font_color)
			text_line.SetOutline(True)
			if outline_color != 0:
				text_line.SetOutline(outline_color)
			text_line.Show()
			self.__AppendChild(text_line, 17)
			return text_line

		def __AutoAppendTextValueLine(self, text, value, font_color = 0, outline_color = 0):
			if value != 0 or self.attr_show_null_value:
				if self.attr_show_color:
					if value > 0:
						self.__AutoAppendTextLine(text % value, 0xFFFF6F61, outline_color)
					elif value < 0:
						self.__AutoAppendTextLine(text % value, 0xFF98FB98, outline_color)
					else:
						self.__AutoAppendTextLine(text % value, font_color, outline_color)
				else:
					self.__AutoAppendTextLine(text % value, font_color, outline_color)

			return value

		def __AppendHorizontalLine(self, line_size = 0):
			draw_line = True
			if draw_line != True:
				line = ui.ImageBox()
				line.SetParent(self)
				line.LoadImage("d:/ymir work/ui/quest_re/quest_list_line_01.tga")
				line.SetDiffuseColor(3.0, 0.3, 0.3, 1.0)
				line.SetPosition(0, self.height)
				line.SetWindowHorizontalAlignCenter()
				line.Show()
				self.__AppendChild(line, 0)
			else:
				if line_size == 0:
					line_size = self.GetWidth() - 50

				for i in xrange(2):
					line = ui.Line()
					line.SetParent(self)
					line.SetSize(line_size, 0)
					line.SetColor(0x66c7c7c7 if 0 == i else 0xff000000)
					line.SetPosition((self.GetWidth() / 2) - (line_size / 2), self.height + 2 + i)
					line.Show()

					self.__AppendChild(line, 0)

			self.__AppendHeight(7)

		def __AppendCheckBox(self, text, check_func, uncheck_func, check):
			checkbox = ui.CheckBox()
			checkbox.SetParent(self)
			checkbox.SetCheckBox(check)
			checkbox.SetText(text, 0xfffffff1)
			checkbox.SetPosition(0, self.height + 5)
			checkbox.SetWindowHorizontalAlignCenter()
			if check_func and uncheck_func:
				checkbox.SetEvent(ui.__mem_func__(check_func), "check")
				checkbox.SetEvent(ui.__mem_func__(uncheck_func), "uncheck")
			checkbox.Show()
			self.__AppendChild(checkbox, 13)
			self.__AppendHeight(5)

		def __AppendArrows(self, prev_func, next_func):
			prev_button = ui.Button()
			prev_button.SetParent(self)
			prev_button.SetPosition(25, self.height + 5)
			prev_button.SetUpVisual("d:/ymir work/ui/public/public_intro_btn/prev_btn_01.sub")
			prev_button.SetOverVisual("d:/ymir work/ui/public/public_intro_btn/prev_btn_02.sub")
			prev_button.SetDownVisual("d:/ymir work/ui/public/public_intro_btn/prev_btn_01.sub")
			if prev_func:
				prev_button.SetEvent(ui.__mem_func__(prev_func))
			prev_button.Show()

			next_button = ui.Button()
			next_button.SetParent(self)
			next_button.SetPosition(self.GetWidth() - 45, self.height + 5)
			next_button.SetUpVisual("d:/ymir work/ui/public/public_intro_btn/next_btn_01.sub")
			next_button.SetOverVisual("d:/ymir work/ui/public/public_intro_btn/next_btn_02.sub")
			next_button.SetDownVisual("d:/ymir work/ui/public/public_intro_btn/next_btn_01.sub")
			if next_func:
				next_button.SetEvent(ui.__mem_func__(next_func))
			next_button.Show()

			self.__AppendChild(prev_button, 0)
			self.__AppendChild(next_button, 0)
			self.__AppendHeight(5)

		def __OnImageMouseEvent(self, event_type, arg = None):
			self.tooltip.ClearToolTip()

			if "mouse_over_in" == event_type and arg:
				self.tooltip.SetThinBoardSize(app.GetTextLength(str(arg)))

				self.tooltip.color = ui.Bar()
				self.tooltip.color.SetParent(self.tooltip)
				self.tooltip.color.SetColor(self.THINBOARD_BAR_COLOR)
				self.tooltip.color.SetPosition(0, 0)
				self.tooltip.color.SetWindowHorizontalAlignCenter()
				self.tooltip.color.SetWindowVerticalAlignCenter()
				self.tooltip.color.Show()

				self.tooltip.AutoAppendTextLine(arg, self.THINBOARD_BAR_TEXT_COLOR)
				self.tooltip.AlignHorizonalCenter()
				self.tooltip.ShowToolTip()

				self.tooltip.color.SetSize(self.tooltip.GetWidth() - self.THINBOARD_BAR_GAP, self.tooltip.GetHeight() - self.THINBOARD_BAR_GAP)

			elif "mouse_over_out" == event_type:
				self.tooltip.Hide()

		def __AutoAppendInlineImage(self, element_dict):
			image_scale = 0.5
			image_gap = 5

			inline_window = ui.Window()
			inline_window.SetParent(self)

			for i, (key, dict) in enumerate(element_dict.items()):
				image = ui.ImageBox()
				image.SetParent(inline_window)
				image.LoadImage(dict["image_path"])

				inline_window.SetSize((image.GetWidth() * image_scale + image_gap) * len(element_dict), (image.GetHeight() * image_scale + image_gap))

				image.SetScale(image_scale, image_scale)
				image.SetPosition((image_gap / 2) + (image.GetWidth() * image_scale + image_gap) * i, (image_gap / 2))
				image.SetEvent(ui.__mem_func__(self.__OnImageMouseEvent), "mouse_over_in", dict["locale_text"] % dict["value"])
				image.SetEvent(ui.__mem_func__(self.__OnImageMouseEvent), "mouse_over_out")
				image.Show()

				self.__AppendChild(image, 0)

			inline_window.SetPosition(0, self.height)
			inline_window.SetWindowHorizontalAlignCenter()
			inline_window.Show()

			self.__AppendChild(inline_window, 0)
			self.__AppendHeight(28)

		def __CalculateValueLvDelta(self, player_level, victim_level, exp):
			percent_lv_delta = self.PERCENT_BY_DELTA_LEVEL[min(max(0, (victim_level + 15) - player_level), len(self.PERCENT_BY_DELTA_LEVEL) - 1)]
			return (exp * percent_lv_delta) / 100

		def __AppendDefaultDetails(self):
			## Race
			race_name_list = [value for key, value in self.RACE_FLAG_NAME_DICT.items() if IS_SET(nonplayer.GetRaceFlag(), key)]
			race_name = ", ".join(race_name_list)
			if race_name_list:
				self.__AutoAppendTextLine(localeInfo.TARGET_INFO_RACE % race_name)
			else:
				if nonplayer.IsStone():
					self.__AutoAppendTextLine(localeInfo.TARGET_INFO_RACE % localeInfo.TARGET_INFO_RACE_METIN)
				else:
					self.__AutoAppendTextLine(localeInfo.TARGET_INFO_RACE % localeInfo.TARGET_INFO_RACE_UNKNOWN)

			max_hp = nonplayer.GetMaxHP()
			regen_pct = nonplayer.GetRegenPercent()
			regen_cycle = nonplayer.GetRegenCycle()
			regen_hp_value = max(1, max_hp * regen_pct / 100)

			## Health
			self.__AutoAppendTextLine(localeInfo.TARGET_INFO_MAX_HP % localeInfo.NumberToDecimal(max_hp))

			## Health Regeneration
			self.__AutoAppendTextLine(localeInfo.TARGET_INFO_HP_REGEN % (regen_pct, regen_hp_value, regen_cycle))
			self.__AppendSpace()

			if chr.IsGameMaster(player.GetMainCharacterIndex()):
				## Hit Range
				self.__AutoAppendTextLine("Hit Range: {}".format(nonplayer.GetHitRange()))
				self.__AppendSpace()

		if app.ENABLE_ELEMENT_ADD:
			def __AppendElementDetails(self):
				element_dict = {}
				for key, list in self.ELEMENT_ENCHANT_NAME_DICT.items():
					value = nonplayer.GetElement(key)
					if value != 0:
						element_dict.update({ key : { "value" : value, "image_path" : list[0], "locale_text" : list[1] }})

				if not element_dict:
					self.has_element = False
					return

				self.__AppendHorizontalLine()
				self.__AppendQuestion(self.QUESTION_BUTTON_ELEMENT)
				self.__AutoAppendTitleLine(localeInfo.TARGET_INFO_ELEMENT_TITLE)

				self.__AutoAppendInlineImage(element_dict)

				self.has_element = True

		def __OnCheckShowAttrNullValue(self):
			self.attr_show_null_value = True
			self.Refresh()

		def __OnUnCheckShowAttrNullValue(self):
			self.attr_show_null_value = False
			self.Refresh()

		def __OnCheckShowAttrColor(self):
			self.attr_show_color = True
			self.Refresh()

		def __OnUnCheckShowAttrColor(self):
			self.attr_show_color = False
			self.Refresh()

		def __AppendAttrDetails(self):
			if nonplayer.IsStone():
				return

			attr_dict = {
				0 : [ ## Weapon Resistances
					(localeInfo.TARGET_INFO_RESIST_FIST, nonplayer.GetResist(nonplayer.MOB_RESIST_FIST)),
					(localeInfo.TARGET_INFO_RESIST_SWORD, nonplayer.GetResist(nonplayer.MOB_RESIST_SWORD)),
					(localeInfo.TARGET_INFO_RESIST_TWOHAND, nonplayer.GetResist(nonplayer.MOB_RESIST_TWOHAND)),
					(localeInfo.TARGET_INFO_RESIST_DAGGER, nonplayer.GetResist(nonplayer.MOB_RESIST_DAGGER)),
					(localeInfo.TARGET_INFO_RESIST_BOW, nonplayer.GetResist(nonplayer.MOB_RESIST_BOW)),
					(localeInfo.TARGET_INFO_RESIST_BELL, nonplayer.GetResist(nonplayer.MOB_RESIST_BELL)),
					(localeInfo.TARGET_INFO_RESIST_FAN, nonplayer.GetResist(nonplayer.MOB_RESIST_FAN)),
				],
				1 : [ ## Elemental Resistances
					(localeInfo.TARGET_INFO_RESIST_FIRE, nonplayer.GetResist(nonplayer.MOB_RESIST_FIRE)),
				],
				2 : [ ## Resistances (Others)
					(localeInfo.TARGET_INFO_RESIST_POISON, nonplayer.GetResist(nonplayer.MOB_RESIST_POISON)),
					(localeInfo.TARGET_INFO_RESIST_BLEEDING, nonplayer.GetResist(nonplayer.MOB_RESIST_BLEEDING)),
				],
				3 : [ ## Enchantments
					(localeInfo.TARGET_INFO_ENCHANT_SLOW, nonplayer.GetEnchant(nonplayer.MOB_ENCHANT_SLOW)),
					(localeInfo.TARGET_INFO_ENCHANT_STUN, nonplayer.GetEnchant(nonplayer.MOB_ENCHANT_STUN)),
					(localeInfo.TARGET_INFO_ENCHANT_POISON, nonplayer.GetEnchant(nonplayer.MOB_ENCHANT_POISON)),
					(localeInfo.TARGET_INFO_ENCHANT_CRITICAL, nonplayer.GetEnchant(nonplayer.MOB_ENCHANT_CRITICAL)),
					(localeInfo.TARGET_INFO_ENCHANT_PENETRATE, nonplayer.GetEnchant(nonplayer.MOB_ENCHANT_PENETRATE)),
				],
			}
			if not app.DISABLE_WOLFMAN_CREATION:
				attr_dict[0].append((localeInfo.TARGET_INFO_RESIST_CLAW, nonplayer.GetResist(nonplayer.MOB_RESIST_CLAW)))
			if app.ENABLE_ELEMENT_ADD:
				attr_dict[1].append((localeInfo.TARGET_INFO_RESIST_EARTH, nonplayer.GetResistEarth()))
			attr_dict[1].append((localeInfo.TARGET_INFO_RESIST_WIND, nonplayer.GetResist(nonplayer.MOB_RESIST_WIND)))
			if app.ENABLE_ELEMENT_ADD:
				attr_dict[1].append((localeInfo.TARGET_INFO_RESIST_ICE, nonplayer.GetResistIce()))
			attr_dict[1].append((localeInfo.TARGET_INFO_RESIST_ELECT, nonplayer.GetResist(nonplayer.MOB_RESIST_ELECT)))
			attr_dict[1].append((localeInfo.TARGET_INFO_RESIST_MAGIC, nonplayer.GetResist(nonplayer.MOB_RESIST_MAGIC)))
			if app.ENABLE_ELEMENT_ADD:
				attr_dict[1].append((localeInfo.TARGET_INFO_RESIST_DARK, nonplayer.GetResistDark()))

			self.attr_page_dict = {}
			i = 0
			for key, list in attr_dict.items():
				for tuple in list:
					if tuple[1] != 0:
						self.attr_page_dict[i] = key
						i += 1
						break

			if i == 0:
				self.has_attr = False
				return

			self.__AppendHorizontalLine()
			self.__AppendQuestion(self.QUESTION_BUTTON_ATTR)

			self.__AppendCheckBox(localeInfo.TARGET_INFO_CHECKBOX_SHOW_ATTR_NULL_VALUE, self.__OnCheckShowAttrNullValue, self.__OnUnCheckShowAttrNullValue, self.attr_show_null_value)
			self.__AppendCheckBox(localeInfo.TARGET_INFO_CHECKBOX_SHOW_ATTR_COLOR, self.__OnCheckShowAttrColor, self.__OnUnCheckShowAttrColor, self.attr_show_color)

			self.__AppendSeperator(20)
			self.__AppendArrows(self.__OnClickPrevResistDetails, self.__OnClickNextResistDetails)

			if self.attr_page in self.attr_page_dict:
				page = self.attr_page_dict[self.attr_page]
				if page in attr_dict:
					if page == 0:
						self.__AutoAppendTitleLine(localeInfo.TARGET_INFO_RESIST_WEAPON_TITLE)
					elif page == 1:
						self.__AutoAppendTitleLine(localeInfo.TARGET_INFO_RESIST_ELEMENT_TITLE)
					elif page == 2:
						self.__AutoAppendTitleLine(localeInfo.TARGET_INFO_RESIST_TITLE)
					elif page == 3:
						self.__AutoAppendTitleLine(localeInfo.TARGET_INFO_RESIST_ELEMENT_TITLE)

					for tuple in attr_dict[page]:
						self.__AutoAppendTextValueLine(tuple[0], tuple[1])

			self.has_attr = True

		def __CreateGameTypeToolTip(self, title, desc_list):
			tooltip = uiToolTip.ToolTip()
			tooltip.ClearToolTip()
			tooltip.AppendSpace(5)

			tooltip.color = ui.Bar()
			tooltip.color.SetParent(tooltip)
			tooltip.color.SetColor(self.THINBOARD_BAR_COLOR)
			tooltip.color.SetPosition(0, 0)
			tooltip.color.SetWindowHorizontalAlignCenter()
			tooltip.color.SetWindowVerticalAlignCenter()
			tooltip.color.Show()

			tooltip.AutoAppendTextLine(title, self.THINBOARD_BAR_TITLE_COLOR)
			for desc in desc_list:
				tooltip.AutoAppendTextLine(desc, self.THINBOARD_BAR_TEXT_COLOR)
			tooltip.AlignHorizonalCenter()

			tooltip.color.SetSize(tooltip.GetWidth() - self.THINBOARD_BAR_GAP, tooltip.GetHeight() - self.THINBOARD_BAR_GAP)

			return tooltip

		def __AppendQuestion(self, key):
			self.help_tooltip_height_dict[key] = self.height

		def __AutoAppendQuestion(self, key, title, desc_list):
			if key not in self.help_tooltip_height_dict:
				return

			button = ui.Button()
			button.SetParent(self)
			button.SetUpVisual("d:/ymir work/ui/pattern/q_mark_01.tga")
			button.SetOverVisual("d:/ymir work/ui/pattern/q_mark_02.tga")
			button.SetDownVisual("d:/ymir work/ui/pattern/q_mark_01.tga")
			if localeInfo.IsARABIC():
				button.SetPosition(self.GetWidth() - button.GetWidth() - 24 , self.help_tooltip_height_dict[key] - 13)
			else:
				button.SetPosition(24 , self.help_tooltip_height_dict[key] - 13)

			tooltip = self.__CreateGameTypeToolTip(title, desc_list)
			button.SetToolTipWindow(tooltip)
			button.Show()

			self.__AppendChild(button, 0)
			self.__AppendChild(tooltip, 0)

		def __AppendRewardDetails(self):
			self.__AppendHorizontalLine()
			self.__AppendQuestion(self.QUESTION_BUTTON_REWARD)

			my_level = player.GetStatus(player.LEVEL)
			level = nonplayer.GetLevel()

			## Experience
			self.__AutoAppendTextLine(localeInfo.TARGET_INFO_EXP % localeInfo.NumberToDecimal(self.__CalculateValueLvDelta(my_level, level, nonplayer.GetExp())))
			if app.ENABLE_CONQUEROR_LEVEL:
				conqueror_level = player.GetStatus(player.POINT_CONQUEROR_LEVEL)
				if conqueror_level > 0:
					self.__AutoAppendTextLine(localeInfo.TARGET_INFO_SUNGMA_EXP % localeInfo.NumberToDecimal(self.__CalculateValueLvDelta(my_level, level, nonplayer.GetSungMaExp())), 0xFFBFD9FF, 0xFF0066FF)

			## Gold
			self.__AutoAppendTextLine(localeInfo.TARGET_INFO_GOLD_MIN_MAX % (localeInfo.NumberToMoneyString(nonplayer.GetMinGold()), localeInfo.NumberToMoneyString(nonplayer.GetMaxGold())))

			self.__AppendSpace()

			## Metin Stone Drop
			if nonplayer.GetDropMetinStone():
				self.__AutoAppendTextLine(localeInfo.TARGET_INFO_METIN_STONE_DROP)
				self.__AppendSpace()

			## Mob Item Drop Button
			button = ui.Button()
			button.SetParent(self)
			button.SetDisableVisual("d:/ymir work/ui/game/treasure_hunt/event/reward_list/reward_off_btn_default.sub")
			button.SetUpVisual("d:/ymir work/ui/game/treasure_hunt/event/reward_list/reward_on_btn_default.sub")
			button.SetOverVisual("d:/ymir work/ui/game/treasure_hunt/event/reward_list/reward_on_btn_over.sub")
			button.SetDownVisual("d:/ymir work/ui/game/treasure_hunt/event/reward_list/reward_on_btn_down.sub")
			button.SetPosition(0, self.height)
			button.SetWindowHorizontalAlignCenter()
			button.SetEvent(ui.__mem_func__(self.__OnClickMobItemDropButton), -1)
			if nonplayer.HasMonsterItemDrop(self.race_vnum):
				button.SetOverEvent(ui.__mem_func__(self.__OnImageMouseEvent), "mouse_over_in", localeInfo.TARGET_INFO_ITEM_DROP)
				button.Enable()
			else:
				button.Disable()
				button.SetOverEvent(ui.__mem_func__(self.__OnImageMouseEvent), "mouse_over_in", localeInfo.TARGET_INFO_NO_ITEM_DROP)
			button.SetOverOutEvent(ui.__mem_func__(self.__OnImageMouseEvent), "mouse_over_out")
			button.Show()

			self.__AppendChild(button, button.GetHeight() + 5)

		def __OnClickMobItemDropButton(self):
			if self.item_drop_window:
				self.item_drop_window.Open(self.race_vnum)

		def __OnClickPrevResistDetails(self):
			self.attr_page -= 1
			if self.attr_page < 0:
				self.attr_page = len(self.attr_page_dict) - 1

			self.Refresh()

		def __OnClickNextResistDetails(self):
			self.attr_page += 1
			if self.attr_page > len(self.attr_page_dict) - 1:
				self.attr_page = 0

			self.Refresh()

		def __ShowDetails(self):
			if self.race_vnum == 0:
				return False

			nonplayer.SelectMob(self.race_vnum)

			self.__AppendDefaultDetails()
			if not nonplayer.IsStone():
				if app.ENABLE_ELEMENT_ADD:
					self.__AppendElementDetails()
				self.__AppendAttrDetails()
			self.__AppendRewardDetails()

			return True

		def __ClearChildren(self):
			self.children_list = []
			self.height = 0

		def Refresh(self):
			self.__ClearChildren()

			self.has_attr = False
			if app.ENABLE_ELEMENT_ADD:
				self.has_element = False
			self.has_reward = True

			self.__AppendSeperator()
			if self.__ShowDetails():
				self.__AppendSeperator(16)

			if self.has_reward:
				self.__AutoAppendQuestion(self.QUESTION_BUTTON_REWARD, localeInfo.TARGET_INFO_REWARD_TOOLTIP_TITLE, self.REWARD_TOOLTIP_LIST)

			if self.has_attr:
				self.__AutoAppendQuestion(self.QUESTION_BUTTON_ATTR, localeInfo.TARGET_INFO_ATTR_TOOLTIP_TITLE, self.ATTR_TOOLTIP_LIST)

			if app.ENABLE_ELEMENT_ADD:
				if self.has_element:
					self.__AutoAppendQuestion(self.QUESTION_BUTTON_ELEMENT, localeInfo.TARGET_INFO_ELEMENT_TOOLTIP_TITLE, self.ELEMENT_TOOLTIP_LIST)

		def Open(self, race_vnum):
			self.race_vnum = race_vnum

			self.SetTop()
			self.Show()

			self.Refresh()

		def Close(self):
			if self.tooltip:
				self.tooltip.Hide()

			self.Hide()

		def OnPressEscapeKey(self):
			self.Close()
			return True

	class MobItemDropWindow(ui.BoardWithTitleBar):
		BOARD_WIDTH = 200
		BOARD_HEIGHT = 355

		def __init__(self):
			ui.BoardWithTitleBar.__init__(self)
			self.isLoaded = False

			self.race_vnum = 0
			self.page_count = 0
			self.page = 0
			self.drop_dict = {}
			self.tooltip_item = uiToolTip.ItemToolTip()

			self.__LoadWindow()

		def __del__(self):
			ui.BoardWithTitleBar.__del__(self)
			self.drop_dict = {}
			del self.tooltip_item
			self.slot_window = None
			self.prev_button = None
			self.next_button = None

		def __LoadWindow(self):
			self.SetWindowName("MobItemDropWindow")
			self.AddFlag("movable")
			self.AddFlag("float")

			self.SetSize(self.BOARD_WIDTH, self.BOARD_HEIGHT)
			self.SetCenterPosition()
			self.SetCloseEvent(ui.__mem_func__(self.Close))
			self.SetTitleName(localeInfo.TARGET_INFO_ITEM_DROP)

			window = ui.OutlineWindow()
			window.SetParent(self)
			window.SetPosition(0, 32)
			window.SetWindowHorizontalAlignCenter()
			window.MakeOutlineWindow(self.GetWidth() - 20, self.GetHeight() - 45)
			window.Show()
			self.window = window

			slot_window = ui.GridSlotWindow()
			slot_window.SetParent(self.window)
			slot_window.SetWindowHorizontalAlignCenter()
			slot_window.SetPosition(0, 10)
			slot_window.ArrangeSlot(0, nonplayer.MAX_MOB_ITEM_DROP_GRID_SLOT_X, nonplayer.MAX_MOB_ITEM_DROP_GRID_SLOT_Y, 32, 32, 0, 0)
			slot_window.SetSlotBaseImage("d:/ymir work/ui/public/Slot_Base.sub", 1.0, 1.0, 1.0, 1.0)
			slot_window.RefreshSlot()
			slot_window.SetOverInItemEvent(ui.__mem_func__(self.__OnOverInSlot))
			slot_window.SetOverOutItemEvent(ui.__mem_func__(self.__OnOverOutSlot))
			slot_window.Show()
			self.slot_window = slot_window

			prev_button = ui.Button()
			prev_button.SetParent(self.window)
			prev_button.SetPosition(-40, 30)
			prev_button.SetWindowHorizontalAlignCenter()
			prev_button.SetWindowVerticalAlignBottom()
			prev_button.SetUpVisual("d:/ymir work/ui/public/public_intro_btn/prev_btn_01.sub")
			prev_button.SetOverVisual("d:/ymir work/ui/public/public_intro_btn/prev_btn_02.sub")
			prev_button.SetDownVisual("d:/ymir work/ui/public/public_intro_btn/prev_btn_01.sub")
			prev_button.SetEvent(ui.__mem_func__(self.__SetPage), -1)
			prev_button.Show()
			self.prev_button = prev_button

			next_button = ui.Button()
			next_button.SetParent(self.window)
			next_button.SetPosition(40, 30)
			next_button.SetWindowHorizontalAlignCenter()
			next_button.SetWindowVerticalAlignBottom()
			next_button.SetUpVisual("d:/ymir work/ui/public/public_intro_btn/next_btn_01.sub")
			next_button.SetOverVisual("d:/ymir work/ui/public/public_intro_btn/next_btn_02.sub")
			next_button.SetDownVisual("d:/ymir work/ui/public/public_intro_btn/next_btn_01.sub")
			next_button.SetEvent(ui.__mem_func__(self.__SetPage), +1)
			next_button.Show()
			self.next_button = next_button

			page_window = ui.ThinBoardCircle()
			page_window.SetParent(self.window)
			page_window.SetSize(30, 20)
			page_window.SetPosition(0, 32)
			page_window.SetWindowHorizontalAlignCenter()
			page_window.SetWindowVerticalAlignBottom()
			page_window.Show()
			self.page_window = page_window

			page_text = ui.TextLine()
			page_text.SetParent(self.page_window)
			page_text.SetPosition(0, 3)
			page_text.SetWindowHorizontalAlignCenter()
			page_text.SetHorizontalAlignCenter()
			page_text.SetText("1")
			page_text.Show()
			self.page_text = page_text

		def __OnOverInSlot(self, slot_num):
			if self.tooltip_item and self.page in self.drop_dict:
				if slot_num in self.drop_dict[self.page]:
					data = self.drop_dict[self.page][slot_num]
					self.tooltip_item.SetItemToolTip(data[0])

		def __OnOverOutSlot(self):
			if self.tooltip_item:
				self.tooltip_item.HideToolTip()

		def __RefreshItems(self):
			for i in range(nonplayer.MAX_MOB_ITEM_DROP_GRID_SIZE):
				self.slot_window.ClearSlot(i)

			if self.page in self.drop_dict:
				for pos in self.drop_dict[self.page]:
					data = self.drop_dict[self.page][pos]
					self.slot_window.SetItemSlot(pos, data[0], data[1])

			self.slot_window.RefreshSlot()

		def __SetPage(self, page):
			next_page = page + self.page
			if 0 <= next_page <= self.page_count:
				self.page = next_page
				self.page_text.SetText(str(self.page + 1))
				self.__RefreshItems()

		def Refresh(self):
			self.page = 0
			(self.page_count, drop_list) = nonplayer.GetMonsterItemDrop(self.race_vnum)

			self.drop_dict.clear()
			for i in range(self.page_count + 1):
				self.drop_dict[i] = dict()

			for page, pos, vnum, count in drop_list:
				self.drop_dict[page][pos] = (vnum, count)

			self.__SetPage(0)

		def Open(self, race_vnum):
			if self.isLoaded == False:
				self.isLoaded = True
				self.__LoadWindow()

			self.race_vnum = race_vnum

			self.SetTitleName(nonplayer.GetMonsterName(self.race_vnum))
			self.SetCenterPosition()
			self.SetTop()
			self.Show()

			if app.ENABLE_MOUSE_WHEEL_TOP_WINDOW:
				wndMgr.SetWheelTopWindow(self.hWnd)

			self.Refresh()

		def Close(self):
			if app.ENABLE_MOUSE_WHEEL_TOP_WINDOW:
				wndMgr.ClearWheelTopWindow(self.hWnd)

			self.__OnOverOutSlot()
			self.Hide()

		def OnPressEscapeKey(self):
			self.Close()
			return True

		if app.ENABLE_MOUSE_WHEEL_TOP_WINDOW:
			def OnMouseWheelButtonUp(self):
				self.__SetPage(-1)
				return True

			def OnMouseWheelButtonDown(self):
				self.__SetPage(+1)
				return True
#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat class TargetBoard(ui.ThinBoard): içerisinde

		name = ui.TextLine()
		name.SetParent(self)
		name.SetDefaultFontName()
		name.SetOutline()
		name.Show()
		self.name = name

		hpGauge = ui.Gauge()
		hpGauge.SetParent(self)
		hpGauge.MakeGauge(130, "red")
		hpGauge.Hide()
		self.hpGauge = hpGauge

		if app.ENABLE_VIEW_TARGET_DECIMAL_HP:
			hpDecimal = ui.TextLine()
			hpDecimal.SetParent(hpGauge)
			hpDecimal.SetDefaultFontName()
			hpDecimal.SetPosition(5, 5)
			hpDecimal.SetOutline()
			hpDecimal.Hide()
			self.hpDecimal = hpDecimal

## Altına ekle

		if app.ENABLE_SEND_TARGET_INFO:
			target_details_button = ui.Button()
			target_details_button.SetParent(self)
			target_details_button.SetUpVisual("d:/ymir work/ui/pattern/q_mark_01.tga")
			target_details_button.SetOverVisual("d:/ymir work/ui/pattern/q_mark_02.tga")
			target_details_button.SetDownVisual("d:/ymir work/ui/pattern/q_mark_01.tga")
			target_details_button.SetEvent(ui.__mem_func__(self.__OnClickTargetDetailsButton))
			target_details_button.Hide()
			self.target_details_button = target_details_button

			target_details_thinboard = TargetDetailsThinBoard(self)
			target_details_thinboard.Hide()
			self.target_details_thinboard = target_details_thinboard

#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat hemen altında

	def __del__(self):
		ui.ThinBoard.__del__(self)

		print "===================================================== DESTROYED TARGET BOARD"

	def __Initialize(self):
		self.nameString = ""
		self.nameLength = 0
		self.vid = 0

## Altına ekle

		if app.ENABLE_SEND_TARGET_INFO:
			self.race_vnum = 0


#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat hemen altında

	def Destroy(self):
		self.__Initialize()

		self.name = None
		self.hpGauge = None
		if app.ENABLE_VIEW_TARGET_DECIMAL_HP:
			self.hpDecimal = None

## Altına ekle

		if app.ENABLE_SEND_TARGET_INFO:
			self.target_details_button = None
			del self.target_details_thinboard

#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat

	def Destroy(self):
		self.__Initialize()

		self.name = None
		self.hpGauge = None
		if app.ENABLE_VIEW_TARGET_DECIMAL_HP:
			self.hpDecimal = None

		if app.ENABLE_SEND_TARGET_INFO:
			self.target_details_button = None
			del self.target_details_thinboard

		self.closeButton = None
		self.buttonDict = None
		self.showingButtonList = None

		if app.ENABLE_ELEMENT_ADD:
			self.element_enchants_dict = {}
			self.elementImgList = None

## Altına ekle

	if app.ENABLE_SEND_TARGET_INFO:
		def RefreshMonsterInfoBoard(self):
			if self.target_details_thinboard.IsShow():
				self.target_details_thinboard.Refresh()

		def __OnClickTargetDetailsButton(self):
			if not self.target_details_thinboard:
				return

			net.RequestTargetInfo(player.GetTargetVID())

			if self.target_details_thinboard.IsShow():
				self.target_details_thinboard.Close()

				if app.ENABLE_ELEMENT_ADD:
					self.ShowElementImg(self.element_enchants_dict)
			else:
				self.target_details_thinboard.Open(self.race_vnum)

				if app.ENABLE_ELEMENT_ADD:
					self.__HideAllElementImg()

#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat

	def Close(self): 
		self.__Initialize()
		self.Hide()

## Değiştir

	def Close(self): 
		self.__Initialize()

		if app.ENABLE_SEND_TARGET_INFO:
			if self.target_details_thinboard:
				self.target_details_thinboard.Close()

		self.Hide()

#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat

	def ResetTargetBoard(self):
		for btn in self.buttonDict.values():
			btn.Hide()

		self.__Initialize()

		self.name.SetPosition(0, 13)
		self.name.SetHorizontalAlignCenter()
		self.name.SetWindowHorizontalAlignCenter()

		self.hpGauge.Hide()
		if app.ENABLE_VIEW_TARGET_DECIMAL_HP:
			self.hpDecimal.Hide()


## Altına ekle 		self.SetSize(250, 40) den öncesine

		if app.ENABLE_SEND_TARGET_INFO:
			self.target_details_button.Hide()
			if self.target_details_thinboard:
				self.target_details_thinboard.Close()

#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat

	def SetEnemyVID(self, vid):
		self.SetTargetVID(vid)


## Altına ekle

		if app.ENABLE_SEND_TARGET_INFO:
			race_vnum = nonplayer.GetRaceByVID(vid)

#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat

		nameFront = ""
		if -1 != level:
			nameFront += "Lv." + str(level) + " "
		if self.GRADE_NAME.has_key(grade):
			nameFront += "(" + self.GRADE_NAME[grade] + ") "

		self.SetTargetName(nameFront + name)

## Altına ekle

		if app.ENABLE_SEND_TARGET_INFO:
			if race_vnum >= 101:
				self.race_vnum = race_vnum

				(text_width, text_height) = self.name.GetTextSize()

				self.target_details_button.SetPosition(text_width + 25, 12)
				self.target_details_button.SetWindowHorizontalAlignLeft()
				self.target_details_button.Show()

#####################//-/-/-/-/-/-//-/ 「Lyrion 」YunusED || Metin2House //-/-/-/-/-/-//-/#####################

