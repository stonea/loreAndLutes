#ifndef ASFC_FONT_H_
#define ASFC_FONT_H_

//Aggregates
	#include <string>
	#include <string>
	#include "image.h"
	using namespace std;
//Dependencies
	#include "utils.h"

class ASFC_Font
{
	public:
	//- [Construction] -
		ASFC_Font(int charWidth, int charHeight, int transR = 0, int transG = 0,
			int transB = 255, int imageBufferWidth = 512,
			int imageBufferHeight = 512);
	//- [Font loading] -
		int Load(string font);
		MEMVAR_GET(NumFonts, int, _numFonts);
	//- [Drawing] -
		void Draw(ASFC_Screen &screen, int x, int y, string s, int font = 0);
		void Draw(ASFC_Screen &screen, int x, int y, char c, int font = 0);
	//- [Font Statistics] -
		MEMVAR_GET(CharWidth,  int, _charWidth);
		MEMVAR_GET(CharHeight, int, _charHeight);
		
	private:
	//Type
		struct ASFC_Font_Info
		{
			int startElement, lastElement;
		};
	
	//Vars
		vector<ASFC_Font_Info> _fontInformation;
		ASFC_Image _fontImage;
		int _numFonts;
		int _charWidth, _charHeight;
};

#endif
