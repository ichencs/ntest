#pragma once

#pragma region 常用颜色定义
const COLORREF g_colorBlue = RGB(153, 204, 255);
const COLORREF g_colorYellow = RGB(255, 255, 0);
const COLORREF g_colorRed = RGB(255, 0, 0);
const COLORREF g_colorWhite = RGB(255, 255, 255);
const COLORREF g_colorGreen = RGB(0, 255, 0);		//这里是草绿色
const COLORREF g_colorGray = RGB(153, 153, 153);		//灰色
#pragma endregion 常用颜色定义

class NGColorRef
{
public:
	NGColorRef();
	~NGColorRef();
};

