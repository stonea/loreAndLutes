#ifndef ASFC_CONSOLE_H_
#define ASFC_CONSOLE_H_

//Aggregates
	#include "matrix.h"
	#include "input.h"
//Recognizes
	#include "font.h"
//Dependencies
	#include "utils.h"
	#include "timer.h"
		
class ASFC_Console
{	
	public:
	//- [Construction] -
		ASFC_Console();
		ASFC_Console(ASFC_Screen *screen, ASFC_Font *font, int width = 80,
			int height = 25);
		MEMVAR_SET(SetScreen, ASFC_Screen*, _screen);
		MEMVAR_GET(Screen, ASFC_Screen*, _screen);
		MEMVAR_SET(SetFont, ASFC_Font*, _font);
		MEMVAR_GET(Font, ASFC_Font*, _font);
	//- [Drawing] -
		void Draw(unsigned char alpha = 0xFF);
	//- [Outputting] -
		void Writeln(string s, int font);
		void Write(string s, int font);
		void Insert(char c, int x, int y, int font);
		void Clear();
		MEMVAR_SETGET(SetCursorX, CursorX, int, _curX);
		MEMVAR_SETGET(SetCursorY, CursorY, int, _curY);

	#include "timer.h"
		
		ASFC_Console& operator<< (string s);
		ASFC_Console& operator<< (int i);
		ASFC_Console& operator<< (double d);
	//- [Inputting] -
		string	GrabString(int font);
		string	GrabString(int font, int maxChars);
		string	GrabWord  (int font);
		string	GrabWord  (int font, int maxChars);
		char	GrabChar  (int font);
		int		GrabInt   (int font);
		double	GrabDouble(int font);
		void	Pause();
		ASFC_Console& operator>> (string &s);
		ASFC_Console& operator>> (char &c);
		ASFC_Console& operator>> (int &i);
		ASFC_Console& operator>> (double &d);
	//- [Info] -
		int FontWidth();
		int FontHeight();
		int  FontAt(int x, int y);
		char CharAt(int x, int y);
		int  LinkAt(int x, int y);
		void PixLocation(int* ptrX, int* ptrY, int x, int y);
		void CharacterAtPixel(int x, int y, int* ptrX, int* ptrY);
	//- [Font Handeling] -
		MEMVAR_SET(SetCurrentFont, int, _currentFont);
		MEMVAR_GET(CurrentFont,    int, _currentFont);
	//- [Viewports] -;
		void SetConsolePosition(int x, int y);
		void SetViewport(int x, int y);
		void SetViewportSize(int width, int height);
		void SetConsoleSize(int width, int height);
		MEMVAR_SETGET(SetTabSize, TabSize, int, _tabSize);
		MEMVAR_SET(SetWordWrap, bool, _wordWrap);
		MEMVAR_GET(IsWordWrap, bool, _wordWrap);
		MEMVAR_GET(ConsoleWidth, int, _consoleW);
		MEMVAR_GET(ConsoleHeight,int, _consoleH);
		MEMVAR_GET(ConsoleX, 	 int, _consoleX);
		MEMVAR_GET(ConsoleY,	 int, _consoleY);
		MEMVAR_GET(ViewportX,	 int, _viewX);
		MEMVAR_GET(ViewportY,	 int, _viewY);
		MEMVAR_GET(ViewWidth,    int, _viewW);
		MEMVAR_GET(ViewHeight,   int, _viewH);
	//- [Keyboard] -
		void SetKeyboardSettings(int keyDelay, int repeatRate);

	protected:
	//p- [Outputting] -p
		void MoveCursor(int chars);
		void NewLine();
		void KillLine(int line);
		void DrawCursor(int charWidth, int charHeight);
	//p- [Helper Functions] -p
		string ParseWord(string s, int &iIndex);
		bool   CharInArray(char c, const char array[]);

	//Type
		//ASFC_ConsoleData holds one piece (string) of data on a ASFC_Console object
			struct ASFC_ConsoleData
			{	//Vars			
					char c;
					int	 font;
					int	 link;
				
				//Construct
					ASFC_ConsoleData()
					{	c 	  = ' ';
						font = 0;
					}
			};
	
	//Const
		static const SDLKey KEY_LEFT 	  = SDLK_LEFT;
		static const SDLKey KEY_RIGHT 	  = SDLK_RIGHT;
		static const SDLKey KEY_DELETE	  = SDLK_DELETE;
		static const SDLKey KEY_BACKSPACE = SDLK_BACKSPACE;
		static const SDLKey KEY_TYPEABLE1 = SDLK_SPACE;
		static const SDLKey KEY_TYPEABLE2 = SDLK_z;
	//vars
		//Screen
			ASFC_Screen *_screen;
		//Fonts
			ASFC_Font *_font;
			int	_tabSize;
			int _currentFont;
		//Data
			ASFC_Matrix<ASFC_ConsoleData> _data;
		//Keyboard info
			int _keyDelay, _repeatRate;
			ASFC_Input _input;
		//Viewport
			int	 _consoleX, _consoleY, _consoleW, _consoleH;
			int	 _curX, _curY;
			int  _viewX, _viewY, _viewW, _viewH;
			bool _wordWrap;
};
#endif
