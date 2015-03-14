//Associated header
	#include "font.h"

//-------------------------------------------------------- [Construction] -
ASFC_Font::ASFC_Font(int charWidth, int charHeight, int transR,
	int transG, int transB, int imageBufferWidth,
	int imageBufferHeight)
	:
		_numFonts(0),
		_fontImage(32, transR, transG, transB, imageBufferWidth, imageBufferHeight,
			charWidth, charHeight),
		_charWidth(charWidth),
		_charHeight(charHeight)
{
}
//-------------------------------------------------------- [Font loading] -
int ASFC_Font::Load(string font)
{
	//Vars
		ASFC_Font_Info *newFontInfo;
		
	//Create a new font info structure;
		_fontInformation.resize(_fontInformation.size() + 1);
		newFontInfo = &_fontInformation[_fontInformation.size() - 1];
		newFontInfo->startElement = (_numFonts == 0) ? 0 : 
			_fontInformation[_numFonts - 1].lastElement;
	//Load the font
		newFontInfo->lastElement = _fontImage.Load(font);
	//Increment our font counter
		_numFonts++;
}
//------------------------------------------------------------- [Drawing] -
void ASFC_Font::Draw(ASFC_Screen &screen, int x, int y, string s, int font)
{
	//Loop through all of the characters of the string		
		for(int i = 0; i < s.length(); i++)
		{	
			//Draw a char
				_fontImage.Draw(screen, x + i * _charWidth, y,
					s[i] - ' ' + _fontInformation[font].startElement);
		}

}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Font::Draw(ASFC_Screen &screen, int x, int y, char c, int font)
{
	int image = (int)c;
	
	image -= ' ';
	_fontImage.Draw(screen, x, y, _fontInformation[font].startElement + image);
}