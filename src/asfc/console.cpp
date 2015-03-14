//Associated Header
	#include "console.h"

//-------------------------------------------------------- [Construction] -
ASFC_Console::ASFC_Console()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
ASFC_Console::ASFC_Console(ASFC_Screen *screen, ASFC_Font *font,
	int width, int height)
	:
		_screen(screen),
		_font(font),
		_consoleX(0),
		_consoleY(0),
		_viewW(0),
		_viewH(0),
		_wordWrap(true),
		_tabSize(4),
		_keyDelay(450),
		_repeatRate(10),
		_currentFont(0),
		_curX(0),
		_curY(0)
{
	//Resize the console
		SetViewportSize(width, height);
		SetConsoleSize(width, height);	
}
//------------------------------------------------------------- [Drawing] -
void ASFC_Console::Draw(unsigned char alpha)
{
	//Vars:
		int iPixPerCharX, iPixPerCharY;
		int iPixX, iPixY;
	//Grab font metrics based on the first font (font 0)
		iPixPerCharX = _font->CharWidth();
		iPixPerCharY = _font->CharHeight();
	//Fill the console in with it's background	
		_screen->DrawFillRectangle(_consoleX, _consoleY, iPixPerCharX * _viewW + 2,
			iPixPerCharY * _viewH, COLOR_BLACK, alpha);
	//Loop through all of the characters, starting with the viewport location
		for(int iY = _viewY; (iY < _viewY + _viewH) && (iY < _consoleH); iY++)
		{	
			for(int iX = _viewX; (iX < _viewX + _viewW) && (iX < _consoleW); iX++)
			{	
				//Set iPixX, iPixY based on where this piece of data's string is supposed to output to
					iPixX = (iX - _viewX) * iPixPerCharX + _consoleX;
					iPixY = (iY - _viewY) * iPixPerCharY + _consoleY;
				//Output this piece of data (if it's legal to do so)
					if(iX <= (_viewW + _viewX) && iY <= (_viewH + _viewY))
					{
						_font->Draw(*_screen, iPixX, iPixY, _data[iX][iY].c,
							_data[iX][iY].font);
					}
			}
		}
}
//---------------------------------------------------------- [Outputting] -
void ASFC_Console::Writeln(string s, int font)
{
	//Write the string
		Write(s, font);
	//Output a new line character
		NewLine();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::Write(string s, int font)
{
	//Vars
		int		cur = 0;
		int		ti;
		string 	sWord;
		int		wordLength = s.length();
		int		i_sWordLength;
		
	//Are there still characters to output?		
		while(cur < wordLength)
		{	
			//Grab the next word to output
				sWord = ParseWord(s, cur);
				i_sWordLength = sWord.length();
			//Is word wrap on?			
				if(_wordWrap)
				{	
					//If the word is too large to fit onto this line
						if(i_sWordLength + _curX > _consoleW)
						{
							//Make a newline
								NewLine();
							//If the first char in the word is a space
								if(sWord[0] == ' ')
								{	
									//Delete out that first char
										ti    = 1;
										sWord = ParseWord(sWord, ti);
										i_sWordLength = sWord.length();
								}
						}
				}
			//Insert this word, Loop through all the chars
				for(unsigned int i = 0; i < i_sWordLength; i++)
				{	
					//Insert this char
						Insert(sWord[i], _curX, _curY, font);
				}
		}	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::Insert(char c, int x, int y, int font)
{
	//Move the cursor to position (iX, iY)
		_curX = x;
		_curY = y;
	
	//If this char is off the console
		while(_curY >= _consoleH)
		{
			//Kill the last line
				KillLine(0);
			//Decrease iY
				_curY--;
		}
		while(_curX < 0)
		{
			//Increase X
				_curX += _consoleW;
			//Decrease Y
				_curY--;
		}
	
	//Decide what to do based on c
		switch(c)
		{	//- [Newline] -
			case '\n':
			{
				//Make a new line
					NewLine();
			}break;
			
			//- [Tab] -
			case '\t':
			{	
				//Update the cursor position... THE SIZE OF A TAB!! Wha ha ha ha ha!
					MoveCursor(_tabSize);
			}break;					
			
			//- [System Bell] -
			case '\a':
			{	
				//Make a beep!
					cout << '\a';
			}break;
			
			case '\b': {}break;
			case '\e': {}break;
			case '\f': {}break;
			case '\r': {}break;
			case '\v': {}break;
			
			//- [Anything Else] -
			default:
			{	//If a normal valid char
					if(c >= ' ' && c <= '~')
					{	
						//Just insert this char, nothing special
							_data[_curX][_curY].c    = c;
							_data[_curX][_curY].font = font;								
						//Update the cursor position
							MoveCursor(1);			
						//We're Done
							return;
					}
			}break;
		};
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::Clear()
{
	//Set the cursor to (0, 0)
		_curX = 0;
		_curY = 0;
	//Loop through all the chars in the console
		for(int iY = 0; iY < _consoleH; iY++)
		{	
			for(int iX = 0; iX < _consoleW; iX++)
			{
				//Set this char to a space of font 0
					_data[iX][iY].c 	= ' ';
					_data[iX][iY].font	= 0;
			}
		}	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console& ASFC_Console::operator<< (string s)
{
	//Write this string with the current font
		Write(s, _currentFont);
	//Return self
		return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console& ASFC_Console::operator<< (int i)
{
	//Write this string with the current font
		Write(Val(i), _currentFont);
	//Return self
		return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console& ASFC_Console::operator<< (double d)
{
	//Write this string with the current font
		Write(Val(d), _currentFont);
	//Return self
		return(*this);
}
//----------------------------------------------------------- [Inputting] -
string	ASFC_Console::GrabString(int font)
{
	//Grab a string setting the max length equal to the space left
	//on the viewport
		return GrabString(font, (_viewW ) - _curX + _viewX);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string	ASFC_Console::GrabString(int font, int maxChars)
{
	//Vars
		bool shiftDown = false;
		bool done = false;
		int  key  = -1;
		int  lastKey = -2;	
		string s = "";			//Holds string inputted extracted from the user
		string ts;				//Holds a temporary string
		int	   oldX, oldY;	//Temporary vars to holds an (X, Y) local
		int charWidth, charHeight;
		ASFC_Timer timer;
		int charsPressed = 0;
		bool oldWordWrapState;

	//Reset the timer
		timer.Reset();		
	//Calculate the character width & height
		charWidth  = _font->CharWidth();
		charHeight = _font->CharHeight();
	//Draw the screen, console, and cursor
		Draw();
		_screen->DrawFillRectangle((_curX - _viewX) * charWidth + _consoleX,
			(_curY - _viewY) * charHeight + _consoleY, 2, charHeight, COLOR_WHITE, 255);
		_screen->Update();
	//While we're not done
		while(!done)
		{	
			//Reset vars
				key  = -1;
				lastKey = -2;
			//Get a key
				_input.Update();
				while(key == -1)
					key = _input.GetKey(_keyDelay, _repeatRate);
				charsPressed++;
  			//If shift is being pressed
				if(_input.GetMod() & KMOD_SHIFT)
					shiftDown = true;
				else
					shiftDown = false;
			//Set the last key to the current key
				lastKey = key;			
			//Decide what to do based on what key is down
			//- [Backspace] -
				if(key == KEY_BACKSPACE)
				{	
					//If there's a char to delete
						if(s.length() > 0)
						{
							//Save the cursor's current position
								oldX = _curX;
								oldY = _curY;
							//Move the cursor to the beginning of the string
								_curX -= s.length();
							//Draw spaces over the old string
								for(int i = 0; i < s.length(); i++)
								{	
									Insert(' ', _curX, _curY, 0);
								}							
							//Restore the cursor's old position
								_curX = oldX - s.length();
								_curY = oldY;
							//Delete this character out of the string
								s = s.substr(0, s.length() - 1);
							//Redraw this string onto the console
								oldWordWrapState = IsWordWrap();
								SetWordWrap(OFF);
								Write(s, font);
								SetWordWrap(oldWordWrapState);
						}
				}
			//- [Enter] -
				else if(key == SDLK_RETURN)
				{	//We're done!
						done = true;				
					//Loop until the user stops pressing return
						while(_input.KeyDown(SDLK_RETURN))
							_input.Update();
				}
			//- [Any typable key, if legal] -
				else if(key >= KEY_TYPEABLE1 && key <= KEY_TYPEABLE2 && s.length() < maxChars)
				{	
					//Shift + Typable Key
						if(shiftDown)
						{	
							//If its a letter Capatilize it
								if(key >= SDLK_a && key <= SDLK_z)
									key = char(key + 'A'-'a');
      						//If its a # or punction mark
    							else if(key == SDLK_BACKQUOTE) 		key = '~';
    							else if(key == SDLK_0) 				key = ')';
    							else if(key == SDLK_1) 				key = '!';
     							else if(key == SDLK_2) 				key = '@';
	      						else if(key == SDLK_3) 				key = '#';
     							else if(key == SDLK_4) 				key = '$';
     							else if(key == SDLK_5) 				key = '%';
     							else if(key == SDLK_6) 				key = '^';
      							else if(key == SDLK_7) 				key = '&';
		      					else if(key == SDLK_8) 				key = '*';
      							else if(key == SDLK_9) 				key = '(';
      							else if(key == SDLK_MINUS)		 	key = '_';
      							else if(key == SDLK_EQUALS)			key = '+';
      							else if(key == SDLK_LEFTBRACKET) 	key = '{';
		      					else if(key == SDLK_RIGHTBRACKET) 	key = '}';
      							else if(key == SDLK_BACKSLASH)		key = '|';
      							else if(key == SDLK_SEMICOLON)		key = ':';
      							else if(key == SDLK_QUOTE)			key = '\"';
      							else if(key == SDLK_COMMA)			key = '<';
		      					else if(key == SDLK_PERIOD)			key = '>';
      							else if(key == SDLK_SLASH)			key = '?';
      							else if(key == SDLK_SPACE)			key = ' ';     							
							//Recognize a shift free state
								shiftDown = false;
      					}
					//Output this char, add it to s
						Insert(key, _curX, _curY, font);
						s += key;
				}
			//Redraw
				if(charsPressed >= 3 || timer.Ellapsed(25))
				{
					Draw();
					DrawCursor(charWidth, charHeight);
					_screen->Update();
					_input.Update();
					charsPressed = 0;
					timer.Reset();
				}
		}
	//Return the string that was inputted
		return(s);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string	ASFC_Console::GrabWord(int font)
{
	//Vars
		string s;
		int dummy = 0;

	//Input data from the console
		s = GrabString(font);
	//Grab the first word in this string
		return(ParseWord(s, dummy));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string	ASFC_Console::GrabWord(int font, int maxChars)
{
	//Vars
		string s;
		int dummy = 0;

	//Input data from the console
		s = GrabString(font, maxChars);
	//Grab the first word in this string
		return(ParseWord(s, dummy));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
char ASFC_Console::GrabChar(int font)
{
	//vars
		string s;
	
	//Input data from the console
		s = GrabString(font, 1);
	//Convert this to a string and return it
		return(s[0]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	ASFC_Console::GrabInt(int font)
{
	//vars
		string s;
	
	//Input data from the console
		s = GrabString(font);
	//Convert this to a val and return that
		return(int(Val(s)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
double ASFC_Console::GrabDouble(int font)
{
	//vars
		string s;
	
	//Input data from the console
		s = GrabString(font);
	//Convert this to a val and return that
		return(Val(s));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::Pause()
{
	//Loop until we've pressed something
		do
		{
			_input.Update();
		}while(_input.GetKey(500, 500) == -1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console& ASFC_Console::operator>>(string &s)
{
	s = GrabString(_currentFont);
	return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console& ASFC_Console::operator>>(char &c)
{
	c = GrabChar(_currentFont);
	return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console& ASFC_Console::operator>> (int &i)
{
	i = GrabInt(_currentFont);
	return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console& ASFC_Console::operator>> (double &d)
{
	d = GrabDouble(_currentFont);
	return(*this);
}
//---------------------------------------------------------------- [Info] -
int ASFC_Console::FontWidth()
{
	return(_font->CharWidth());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int ASFC_Console::FontHeight()
{
	return(_font->CharHeight());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int  ASFC_Console::FontAt(int x, int y)
{
	return(_data[x][y].font);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
char ASFC_Console::CharAt(int x, int y)
{
	return(_data[x][y].c);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int  ASFC_Console::LinkAt(int x, int y)
{
	return(_data[x][y].link);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::PixLocation(int* ptrX, int* ptrY, int x, int y)
{
	//Figure out ptrY
		*ptrY = y * FontHeight() + ConsoleY() - ViewportY() * FontHeight();	
	//Figure out what piX would be if it weren't for those evil tabs
		*ptrX  = x * FontWidth() + ConsoleX() - ViewportX() * FontWidth();
	//Now loop through the string at x
		for(int i = 0; i < x; i++)
		{	
			//If there's a tab here
				if(_data[x][y].c = '\t')
				{
					//Move the piX over for the # of chars in a tab - the 1 char we already dealt with
						for(int j = 1; j < TabSize(); j++)
						{	*ptrX += FontWidth();
						}
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::CharacterAtPixel(int x, int y, int* ptrX, int* ptrY)
{
	//Conert this sucker
		(*ptrX) = (x - _consoleX) / FontWidth();
		(*ptrY) = (y - _consoleY) / FontHeight();
}
//----------------------------------------------------------- [Viewports] -
void ASFC_Console::SetConsolePosition(int x, int y)
{
	_consoleX = x;
	_consoleY = y;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::SetViewport(int x, int y)
{
	_viewX = x;
	_viewY = y;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::SetViewportSize(int width, int height)
{
	_viewX = 0;
	_viewY = 0;
	_viewW = width;
	_viewH = height;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::SetConsoleSize(int width, int height)
{
	_consoleW = width;
	_consoleH = height;
	_data.Resize(width, height);
}
//------------------------------------------------------------ [Keyboard] -
void ASFC_Console::SetKeyboardSettings(int keyDelay, int repeatRate)
{
	_keyDelay 	= keyDelay;
	_repeatRate = repeatRate;
}
//p-------------------------------------------------------- [Outputting] -p
void ASFC_Console::MoveCursor(int chars)
{
	//Increment the cusorX
		_curX += chars;

	//While the cursor X is too large
		while(_curX >= _consoleW)
		{	//Move the cursor down a line
				_curY++;
			
			//Send the carridge back *ding*
				_curX -= _consoleW;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::NewLine()
{
	//Move the cursor down a line
		_curY++;
	//Send the carridge back *ding*
		_curX = 0;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::KillLine(int line)
{
	//Remove that row out of the data matrix
		_data.RemoveRow(line);
	//Resize the data matrix back to its original size
		_data.Resize(_consoleW, _consoleH);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::DrawCursor(int charWidth,
	int charHeight)
{
	//If the cursor is within the viewport draw it
		if(_curX < _viewX + _viewW && _curY < _viewY + _viewH)
		{
			_screen->DrawFillRectangle((_curX - _viewX) * charWidth + _consoleX,
				(_curY - _viewY) * charHeight + _consoleY, 2,
				charHeight, COLOR_WHITE, 255);
		}
}
//p-------------------------------------------------- [Helper Functions] -p
string ASFC_Console::ParseWord(string s, int &iIndex)
{
	//Const
		const char SPACE_CHARS[] = {' ', '\n', '\t'};		//Holds characters that count as spaces

	//vars
		int	i_sLength = s.length();
		int iOldIndex = iIndex;
	
	//Loop while there's space chars and more chars
		while(CharInArray(s[iIndex], SPACE_CHARS) && iIndex < i_sLength)
		{	//Increment the Start index
				iIndex++;
		}
		
	//Loop while there's not a space char and more chars
		while((! CharInArray(s[iIndex], SPACE_CHARS)) && iIndex < i_sLength)
		{	//Increment the index
				iIndex++;
		}
		
	//If we're past the valid range
		if(iIndex >= i_sLength)
		{	return(s.substr(iOldIndex, i_sLength - iOldIndex));
		}	

	//Grab the string from iReturnStart to iIndex and return it		
		return(s.substr(iOldIndex, iIndex - iOldIndex));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool  ASFC_Console::CharInArray(char c, const char array[])
{
	//Vars
		int iArraySize = sizeof(array);
	
	//Loop through all the chars in the char array
		for(int i = 0; i < iArraySize; i++)
		{	//Does this char match c?				
				if(array[i] == c)
					return(true);
		}

	//If execution gets here no chars matched
		return(false);
}
