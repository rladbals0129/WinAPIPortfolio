#pragma once
#include "SingletonBase.h"
class FontManager : public SingletonBase <FontManager>
{


public:
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight,
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight,
		LPCWSTR printString, int length, COLORREF color); //Ȯ�强

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight,
		LPCWSTR* printStringArr, int length, COLORREF color);

};

