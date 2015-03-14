/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS				A*ML
	By: Andy Stone

	File for ASFC_Console

	A nice little console object that can be used to output and input text.
*/

#ifndef ASFC_CONSOLE_H_
#define ASFC_CONSOLE_H_

//*********************************************************************************************************
//											Initilization
//*********************************************************************************************************
//Aggregates
	#include "linkedlist.h"
	#include "matrix.h"
	#include "input.h"

//Recognizes
	#include "fontpalette.h"
		
//*********************************************************************************************************
//												ASFC_Console
//*********************************************************************************************************
class ASFC_Console
{	public:
	//- [Construction] -
		ASFC_Console();							//Creates a new ASFC_Console object
		ASFC_Console(C_i2(iWidth, iHeight));
	//- [Drawing] -
		void Draw(int iTranslucency);		//Redraws the console onto the screen
		MEMVAR_SETGET(SetSurface, Surface, ASFC_Surface*, mypoSurface);
	//- [Outputting] -
		void Writeln(string s, int iFont);			//Outputs a string followed by a new line
		void Write(string s, int iFont);			//Outputs a string w/o a new line char
		void Insert(C_i4(c, iX, iY, iFont));		//Places a character at a specific location within the console
		void Clear();								//Clears all text out of the console

		ASFC_Console& operator<< (string s);
		ASFC_Console& operator<< (int i);
		ASFC_Console& operator<< (double d);
	//- [Inputting] -
		string	GrabString(int iFont);			//Grabs string input from the user
		string	GrabString(int iFont, int iMaxChars);	//Grabs string input from the user, iMaxChars = char limit
		string	GrabWord(int iFont);		//Grabs a word from the user
		string	GrabWord(int iFont, int iMaxChars);	//Grabs a word from the user, iMaxChars = char limit
		char	GrabChar(int iFont);		//Grabs a char from the user
		int		GrabInt(int iFont);			//Grabs an int from the user
		double	GrabDouble(int iFont);		//Grabs a double from the user
		void	Pause();					//Pauses the console until any key is pressed
		ASFC_Console& operator>> (string &s);
		ASFC_Console& operator>> (int &i);
		ASFC_Console& operator>> (double &d);
	//- [Info] -
		int  FontAt(C_i2(iX, iY));	//Extracts the handle of the font at location iX, iY
		char CharAt(C_i2(iX, iY));	//Extracts the char at location iX, iY
		int  LinkAt(C_i2(iX, iY));	//Extracts the handle of the link at location iX, iY
		void PixLocation(int* piX, int* piY, int iX, int iY);	//Changes piX and piY into the the pix location of char iX iY
		void CharacterAtPixel(int piX, int piY, int* iX, int* iY);	//Reverse of PixLocation
	//- [Font Handeling] -
		MEMVAR_SETGET(SetFontPalette, FontPalette, ASFC_FontPalette*, mypoFonts);
		MEMVAR_LINK(CurrentFont, int, myiCurrentFont);
	//- [Viewports] -
		void SetConsolePosition(int iX, int iY);		//Sets the top left corner of the console		
		void SetViewport(int iX, int iY);				//Sets the topleft corner of the viewport,
		void SetViewportSize(int iWidth, int iHeight);	//Sets the size of the viewport		
		void SetConsoleSize(int iWidth, int iHeight);	//Sets the console size (in terms of chars)
		
		MEMVAR_LINK(ViewportX, int, myiViewX);			//Viewport X position link
		MEMVAR_LINK(ViewportY, int, myiViewY);			//Viewport Y position link
  		MEMVAR_LINK(CursorX, int, myiCurX);				//Cursor X link
  		MEMVAR_LINK(CursorY, int, myiCurY);				//Cursor Y link
		MEMVAR_LINK(TabSize, int, myiTabSize);			//Sets the tab size
		MEMVAR_LINK(WordWrap, bool, myfWordWrap);		//Set\Get the word wrapping state		
		MEMVAR_LINK(AutoViewport, bool, myfAutoView);	//Sets whether the console will automatically shift the location of the	viewport when new text is added
		
		MEMVAR_GET(FontWidth, 	 int, mypoFonts->operator[](0).Width());	//Returns the font width
		MEMVAR_GET(FontHeight,	 int, mypoFonts->operator[](0).Height());	//Returns the font height
		MEMVAR_GET(ConsoleWidth, int, myiWidth);				//Returns the console width
		MEMVAR_GET(ConsoleHeight,int, myiHeight);				//Returns the console hieght
		MEMVAR_GET(ConsoleX, 	 int, myiConsoleX);				//Returns the X location of the console
		MEMVAR_GET(ConsoleY,	 int, myiConsoleY);				//Returns the Y location of the console
		MEMVAR_GET(ViewSizeX,    int, myiViewSizeX);
		MEMVAR_GET(ViewSizeY,    int, myiViewSizeY);

	//- [Keyboard] -
		void SetKeyboardSettings(C_i2(iKeyDelay, iRepeatRate));	//Sets the keyboard delay rates
	//====================================================================================================
	//====================================================================================================	
	protected:	
	//P- [Construction] -P
		void SetVarsDefaults();					//Set variables to their default values
	
	//P- [Outputting] -P
		void MoveCursor(int iChars);						//Moves the cursor iChars to the right
		void NewLine();										//Creates a newline char in the console
		void KillLine(int iLine);							//Destroys line # iLine and moves all text beyond that up a line
		void CheckCursor();									//Makes sure the curosr is on a valid position, if not move it to one
		bool ValidFont(int iFont);							//Checks if iFont is valid if not errrs
		
	//P- [Helper Functions] -P
		string ParseWord(string s, int &iIndex);			//Returns the next word in string s from char iIndex, updates iIndex too
		bool   CharInArray(char c, const char cArray[]);	//Returns true if there's a char in array cArray
	//....................................................................................................
	//Type
		//ASFC_ConsoleData holds one piece (string) of data on a ASFC_Console object
			struct ASFC_ConsoleData
			{	//Vars			
					char c;
					int	 iFont;
					int	 iLink;
				
				//Construct
					ASFC_ConsoleData()
					{	c 	  = ' ';
						iFont = 0;
					}
			};
	
	//Const
			static const SDLKey KEY_LEFT 	= SDLK_LEFT;
			static const SDLKey KEY_RIGHT 	= SDLK_RIGHT;
			static const SDLKey KEY_DELETE	= SDLK_DELETE;
			static const SDLKey KEY_BACKSPACE= SDLK_BACKSPACE;
			static const SDLKey KEY_TYPEABLE1= SDLK_SPACE;
			static const SDLKey KEY_TYPEABLE2= SDLK_z;
	
	//vars
		//Fonts
			ASFC_Surface*	  mypoSurface;
			ASFC_FontPalette* mypoFonts;			//Recognizes a font palette
			int	myiTabSize;							//Holds the console's tab size
			int myiCurrentFont;						//# that holds the current font
		//Data
			ASFC_Matrix<ASFC_ConsoleData> myloData;		//Holds the map of all the console data			
		//Keyboard info
			int myiKeyDelay;	//Holds how many mills must pass before a key starts to repeat
			int myiRepeatRate;	//Holds how many mills must pass between each key repeat
			ASFC_Input myoInput;
		//Viewport
			int	 myiConsoleX, myiConsoleY;	//Holds the top left position on the screen (in pixels) of the console
			int	 myiCurX, myiCurY;			//Holds the position of the cursor in the console
			int	 myiWidth, myiHeight;		//Holds the size of the console (in chars)
			int  myiViewX, myiViewY;		//Holds the topleft location of the viewport (in chars)
			int  myiViewSizeX, myiViewSizeY;//Holds the size of the viewport (in chars)
			bool myfAutoView;				//True if auto viewport mode is on
			bool myfWordWrap;				//True if word wrap is on*/s
};
#endif
