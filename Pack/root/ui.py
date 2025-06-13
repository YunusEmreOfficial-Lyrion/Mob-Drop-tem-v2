#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat class Window(object): icerisinde

	def SetSize(self, width, height):
		wndMgr.SetWindowSize(self.hWnd, width, height)

	def GetWidth(self):
		return wndMgr.GetWindowWidth(self.hWnd)

	def GetHeight(self):
		return wndMgr.GetWindowHeight(self.hWnd)

	def GetLocalPosition(self):
		return wndMgr.GetWindowLocalPosition(self.hWnd)

## Alt©¥na ekle


	if app.ENABLE_SEND_TARGET_INFO:
		def GetLeft(self):
			x, y = self.GetLocalPosition()
			return x

		def GetRight(self):
			return self.GetLeft() + self.GetWidth()

		def GetTop(self):
			x, y = self.GetLocalPosition()
			return y

		def GetBottom(self):
			return self.GetTop() + self.GetHeight()

#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat


class ThinBoard(Window):
	CORNER_WIDTH = 16
	CORNER_HEIGHT = 16
	LINE_WIDTH = 16
	LINE_HEIGHT = 16
	BOARD_COLOR = grp.GenerateColor(0.0, 0.0, 0.0, 0.51)

	LT = 0
	LB = 1
	RT = 2
	RB = 3
	L = 0
	R = 1
	T = 2
	B = 3

	def __init__(self, layer = "UI"):
		Window.__init__(self, layer)

		CornerFileNames = [ "d:/ymir work/ui/pattern/ThinBoard_Corner_"+dir+".tga" for dir in ["LeftTop","LeftBottom","RightTop","RightBottom"] ]
		LineFileNames = [ "d:/ymir work/ui/pattern/ThinBoard_Line_"+dir+".tga" for dir in ["Left","Right","Top","Bottom"] ]

		self.Corners = []
		for fileName in CornerFileNames:
			Corner = ExpandedImageBox()
			Corner.AddFlag("attach")
			Corner.AddFlag("not_pick")
			Corner.LoadImage(fileName)
			Corner.SetParent(self)
			Corner.SetPosition(0, 0)
			Corner.Show()
			self.Corners.append(Corner)

		self.Lines = []
		for fileName in LineFileNames:
			Line = ExpandedImageBox()
			Line.AddFlag("attach")
			Line.AddFlag("not_pick")
			Line.LoadImage(fileName)
			Line.SetParent(self)
			Line.SetPosition(0, 0)
			Line.Show()
			self.Lines.append(Line)

		Base = Bar()
		Base.SetParent(self)
		Base.AddFlag("attach")
		Base.AddFlag("not_pick")
		Base.SetPosition(self.CORNER_WIDTH, self.CORNER_HEIGHT)
		Base.SetColor(self.BOARD_COLOR)
		Base.Show()
		self.Base = Base

		self.Lines[self.L].SetPosition(0, self.CORNER_HEIGHT)
		self.Lines[self.T].SetPosition(self.CORNER_WIDTH, 0)

	def __del__(self):
		Window.__del__(self)

## Alt©¥na ekle

	if app.ENABLE_SEND_TARGET_INFO:
		def ShowCorner(self, corner):
			self.Corners[corner].Show()
			self.SetSize(self.GetWidth(), self.GetHeight())

		def HideCorners(self, corner):
			self.Corners[corner].Hide()
			self.SetSize(self.GetWidth(), self.GetHeight())

		def ShowLine(self, line):
			self.Lines[line].Show()
			self.SetSize(self.GetWidth(), self.GetHeight())

		def HideLine(self, line):
			self.Lines[line].Hide()
			self.SetSize(self.GetWidth(), self.GetHeight())

#####################//-/-/-/-/-/-//-/ ¡¸Lyrion ¡¹YunusED || Metin2House //-/-/-/-/-/-//-/#####################

## Arat

class OutlineWindow(Window):
	PATTERN_PATH = "d:/ymir work/ui/pattern/"

	def __init__(self, layer = "UI"):
		Window.__init__(self, layer)
		self.__Initialize()

	def __del__(self):
		Window.__del__(self)
		self.__Initialize()

	def __Initialize(self):
		self.pattern_x_count = 0
		self.pattern_y_count = 0
		self.left_top_img = None
		self.right_top_img = None
		self.left_bottom_img = None
		self.right_bottom_img = None
		self.top_center_img = None
		self.left_center_img = None
		self.right_center_img = None
		self.bottom_center_img = None
		self.center_img = None

	def MakeOutlineWindow(self, window_width, window_height):
		self.AddFlag("ltr")
		self.AddFlag("attach")
		self.SetWindowName("outline_window")
		self.SetSize(window_width, window_height)

		self.pattern_x_count = (window_width - 32) / 16
		self.pattern_y_count = (window_height - 32) / 16

		self.left_top_img = ImageBox()
		self.left_top_img.SetParent(self)
		self.left_top_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_left_top.tga")
		self.left_top_img.SetPosition(0, 0)
		self.left_top_img.Show()

		self.right_top_img = ImageBox()
		self.right_top_img.SetParent(self)
		self.right_top_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_right_top.tga")
		self.right_top_img.SetPosition(window_width - 16, 0)
		self.right_top_img.Show()

		self.left_bottom_img = ImageBox()
		self.left_bottom_img.SetParent(self)
		self.left_bottom_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_left_bottom.tga")
		self.left_bottom_img.SetPosition(0, window_height - 16)
		self.left_bottom_img.Show()

		self.right_bottom_img = ImageBox()
		self.right_bottom_img.SetParent(self)
		self.right_bottom_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_right_bottom.tga")
		self.right_bottom_img.SetPosition(window_width - 16, window_height - 16)
		self.right_bottom_img.Show()

		self.top_center_img = ExpandedImageBox()
		self.top_center_img.SetParent(self)
		self.top_center_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_top.tga")
		self.top_center_img.SetPosition(16, 0)
		self.top_center_img.SetRenderingRect(0.0, 0.0, self.pattern_x_count, 0.0)
		self.top_center_img.Show()

		self.left_center_img = ExpandedImageBox()
		self.left_center_img.SetParent(self)
		self.left_center_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_left.tga")
		self.left_center_img.SetPosition(0, 16)
		self.left_center_img.SetRenderingRect(0.0, 0.0, 0.0, self.pattern_y_count)
		self.left_center_img.Show()

		self.right_center_img = ExpandedImageBox()
		self.right_center_img.SetParent(self)
		self.right_center_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_right.tga")
		self.right_center_img.SetPosition(window_width - 16, 16)
		self.right_center_img.SetRenderingRect(0.0, 0.0, 0.0, self.pattern_y_count)
		self.right_center_img.Show()

		self.bottom_center_img = ExpandedImageBox()
		self.bottom_center_img.SetParent(self)
		self.bottom_center_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_bottom.tga")
		self.bottom_center_img.SetPosition(16, window_height - 16)
		self.bottom_center_img.SetRenderingRect(0.0, 0.0, self.pattern_x_count, 0.0)
		self.bottom_center_img.Show()

		self.center_img = ExpandedImageBox()
		self.center_img.SetParent(self)
		self.center_img.LoadImage(OutlineWindow.PATTERN_PATH + "border_A_center.tga")
		self.center_img.SetPosition(16, 16)
		self.center_img.SetRenderingRect(0.0, 0.0, self.pattern_x_count, self.pattern_y_count)
		self.center_img.Show()

## Alt©¥na ekle

if app.ENABLE_SEND_TARGET_INFO:
	class CheckBox(Window):
		def __init__(self):
			Window.__init__(self)

			self.checkbox_image = None
			self.check_image = None
			self.text_line = None
			self.check = False

			self.event_func = { "check" : None, "uncheck" : None, }
			self.event_args = { "check" : None, "uncheck" : None, }

			self.__BuildCheckBox()

		def __del__(self):
			Window.__del__(self)

			self.checkbox_image = None
			self.check_image = None
			self.text_line = None
			self.check = False

			self.event_func = { "check" : None, "uncheck" : None, }
			self.event_args = { "check" : None, "uncheck" : None, }

		def __BuildCheckBox(self):
			checkbox_image = ImageBox()
			checkbox_image.SetParent(self)
			checkbox_image.AddFlag("not_pick")
			checkbox_image.LoadImage("d:/ymir work/ui/game/quest/quest_checkbox.tga")
			checkbox_image.Show()
			self.checkbox_image = checkbox_image

			check_image = ImageBox()
			check_image.SetParent(self)
			check_image.AddFlag("not_pick")
			check_image.SetPosition(0, -4)
			check_image.LoadImage("d:/ymir work/ui/game/quest/quest_checked.tga")
			check_image.Hide()
			self.check_image = check_image

			text_line = TextLine()
			text_line.SetParent(self)
			text_line.SetPosition(17, -2)
			text_line.Show()
			self.text_line = text_line

			self.SetSize(self.checkbox_image.GetWidth() + self.text_line.GetTextSize()[0], self.checkbox_image.GetHeight() + self.text_line.GetTextSize()[1])

		def SetText(self, text, color = 0):
			if self.text_line:
				self.text_line.SetText(text)
				if color:
					self.text_line.SetPackedFontColor(color)

			self.SetSize(self.checkbox_image.GetWidth() + self.text_line.GetTextSize()[0], self.checkbox_image.GetHeight() + self.text_line.GetTextSize()[1])

		def SetCheckBox(self, check):
			self.check = check
			if check:
				self.check_image.Show()
			else:
				self.check_image.Hide()

		def IsChecked(self):
			return self.check

		def SetEvent(self, func, *args):
			result = self.event_func.has_key(args[0])
			if result:
				self.event_func[args[0]] = func
				self.event_args[args[0]] = args
			else:
				print("[ERROR] ui.py SetEvent, Can`t Find has_key : %s" % args[0])

		def OnMouseLeftButtonUp(self):
			if self.check != True:
				self.check = True
				self.check_image.Show()

				if self.event_func["check"]:
					apply(self.event_func["check"], self.event_args["check"])
			else:
				self.check = False
				self.check_image.Hide()

				if self.event_func["uncheck"]:
					apply(self.event_func["uncheck"], self.event_args["uncheck"])
