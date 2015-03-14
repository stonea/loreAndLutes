/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS				A*ML
	By: Andy Stone

	File for ASFC_Console

	A nice little console object that can be used to output and input text.
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header
	#include "console.h"
	#include "font.h"
	#include "input.h"
	#include "timer.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												ASFC_Console
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//--------------------------------------------------------------------------------------- [Construction] -
//Creates a new ASFC_Console object
ASFC_Console::ASFC_Console()
{	//Set variables to their defaults
		SetVarsDefaults();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Console::ASFC_Console(C_i2(iWidth, iHeight))
{	//Set vars to their defaults
		SetVarsDefaults();
	
	//Resize the ASFC_Console
		SetConsoleSize(iWidth, iHeight);
		SetViewportSize(iWidth, iHeight);
}
//-------------------------------------------------------------------------------------------- [Drawing] -
//Redraws the console onto the screen
void ASFC_Console::Draw(int iTranslucency = 255)
{	//Vars
		int iPixPerCharX, iPixPerCharY;		//Holds the size of the base character
		int iPixX, iPixY;					//Holds a location on the screen
	
	//Grab font metrics based on the first font (font 0)
		iPixPerCharX = mypoFonts->operator[](0).Width();
		iPixPerCharY = mypoFonts->operator[](0).Height();
	
	//Fill the console in with it's background	
		mypoSurface->DrawFillRectangle(myiConsoleX, myiConsoleY, iPixPerCharX * myiViewSizeX + 2,
									   iPixPerCharY * myiViewSizeY, COLOR_BLACK, iTranslucency);
	//Loop through all of the characters, starting with the viewport location
		for(int iY = myiViewY; (iY < myiViewY + myiViewSizeY) && (iY < myiHeight); iY++)
		{	for(int iX = myiViewX; (iX < myiViewX + myiViewSizeX) && (iX < myiWidth); iX++)
			{	//Set iPixX, iPixY based on where this piece of data's string is supposed to output to
					iPixX = (iX - myiViewX) * iPixPerCharX + myiConsoleX;
					iPixY = (iY - myiViewY) * iPixPerCharY + myiConsoleY;
				
				//Output this piece of data (if it's legal to do so)
					if(iX <= (myiViewSizeX + myiViewX) && iY <= (myiViewSizeY + myiViewY))
					{	mypoFonts->operator[](myloData[iX][iY].iFont).WriteTo(*mypoSurface, iPixX, iPixY, myloData[iX][iY].c);
					}
			}
		}
}
//----------------------------------------------------------------------------------------- [Outputting] -
//Outputs a string followed by a new line
void ASFC_Console::Writeln(string s, int iFont)
{	//Check the font
		if(ValidFont(iFont))
		{	//Write the string
				Write(s, iFont);
			//Output a new line character
				NewLine();
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Outputs a string w/o a new line char
void ASFC_Console::Write(string s, int iFont)
{	//Vars
		int				iCur	= 0;	//Everything right of this position in s needs to be outputted
		int				ti;				//Temporary (dummy) int
		string  		sWord;			//Holds a word that will be outtputed
		int				iWordLength = s.length();
		int				i_sWordLength;
		
	//Check the font
		if(!ValidFont(iFont))
			return;

	//Are there still characters to output?		
		while(iCur < iWordLength)
		{	//Grab the next word to output
				sWord = ParseWord(s, iCur);
				i_sWordLength = sWord.length();
			//Is word wrap on?			
				if(myfWordWrap)
				{	//If the word is too large to fit onto this line
						if(i_sWordLength + myiCurX > myiWidth)
						{	//Make a newline
								NewLine();
							//If the first char in the word is a space
								if(sWord[0] == ' ')
								{	//Delete out that first char
										ti    = 1;
										sWord = ParseWord(sWord, ti);
										i_sWordLength = sWord.length();
								}
						}
			}

			//Insert this word, Loop through all the chars
				for(unsigned int i = 0; i < i_sWordLength; i++)
				{	//Insert this char
						Insert(sWord[i], myiCurX, myiCurY, iFont);
				}
		}	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Places a character at a specific location within the console
void ASFC_Console::Insert(C_i4(c, iX, iY, iFont))
{	//Check the font
		if(!ValidFont(iFont))
			return;

	//Move the cursor to position (iX, iY)
		myiCurX = iX;
		myiCurY = iY;
	
	//If this char is off the console
		while(myiCurY >= myiHeight)
		{	//Kill the last line
				KillLine(0);
			
			//Decrease iY
				myiCurY--;
		}
	
	//Decide what to do based on c
		switch(c)
		{	//- [Newline] -
			case '\n':
			{	//Make a new line
					NewLine();				
			}break;
			
			//- [Tab] -
			case '\t':
			{	//Update the cursor position... THE SIZE OF A TAB!! Wha ha ha ha ha!
					MoveCursor(myiTabSize);
			}break;					
			
			//- [System Bell] -
			case '\a':
			{	//Make a beep!
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
					{	//Just insert this char, nothing special
							myloData[iX][iY].c 	   = c;
							myloData[iX][iY].iFont = iFont;
								
						//Update the cursor position
							MoveCursor(1);
						
						//We're Done
							return;
					}
			}break;
		};
		
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Clears all text out of the console
void ASFC_Console::Clear()
{	//Set the cursor to (0, 0)
		myiCurX = 0;
		myiCurY = 0;
	
	//Loop through all the chars in the console
		for(int iY = 0; iY < myiHeight; iY++)
		{	for(int iX = 0; iX < myiWidth; iX++)
			{	//Set this char to a space of font 0
					myloData[iX][iY].c 	   = ' ';
					myloData[iX][iY].iFont  = 0;
			}
		}	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
ASFC_Console& ASFC_Console::operator<< (string s)
{	//Write this string with the current font
		Write(s, myiCurrentFont);
	
	//Return self
		return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
ASFC_Console& ASFC_Console::operator<< (int i)
{	//Output this integer:
		Write(Val(i), myiCurrentFont);
	
	//Return self
		return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
ASFC_Console& ASFC_Console::operator<< (double d)
{	//Output this double':
		Write(Val(d), myiCurrentFont);
	
	//Return self
		return(*this);
}
//------------------------------------------------------------------------------------------ [Inputting] -
//Grabs string input from the user
string	ASFC_Console::GrabString(int iFont)
{	//Grab a string with a maximum chars of what's left on the console
		return(GrabString(iFont, myiWidth - myiCurX));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Grabs string input from the user, iMaxChars = char limit
string	ASFC_Console::GrabString(int iFont, int iMaxChars)
{	//Vars
		bool myfShiftDown = false;
		bool fDone = false;
		int  iKey  = -1;
		int  iLastKey = -2;	
		string s = "";			//Holds string inputted extracted from the user
		string ts;				//Holds a temporary string
		int	   tiOldX, tiOldY;	//Temporary vars to holds an (X, Y) local
		
	//Redraw
		Draw();
	//Draw the cursor!
		int iPixPerCharX = mypoFonts->operator[](0).Width();
		int iPixPerCharY = mypoFonts->operator[](0).Height();				
		mypoSurface->DrawFillRectangle((myiCurX - myiViewX) * iPixPerCharX + myiConsoleX,
			(myiCurY - myiViewY) * iPixPerCharY + myiConsoleY, 2, FontHeight(), COLOR_WHITE, 255);
	//Update
		mypoSurface->Update();
		myoInput.Update();

	//While we're not done
		while(!fDone)
		{	//Reset vars
				iKey  = -1;
				iLastKey = -2;	
  
  			//If shift is being pressed
				myoInput.Update();
				if(myoInput.KeyDown(SDLK_LSHIFT) || myoInput.KeyDown(SDLK_RSHIFT))
			  	{	myfShiftDown = true;
			  	}
				else
				{	//If its been 20 mills since shift was last pressed cancel it
						myfShiftDown = false;
				}
				
			//Get a key
				while(iKey == -1)
					iKey = myoInput.GetKey(false, 250, 0);

				while(iKey != -1 && iKey != iLastKey)
				{	iLastKey = iKey;
				
					//If shift is being pressed
						myoInput.Update();
						if(myoInput.KeyDown(SDLK_LSHIFT) || myoInput.KeyDown(SDLK_RSHIFT))
			  				myfShiftDown = true;
						else
							myfShiftDown = false;

		
					//Decide what to do based on what key is down
					//- [Backspace] -
						if(iKey == KEY_BACKSPACE)
						{	//If there's a char to delete
								if(s.length() > 0)
								{	//Save the cursor's current position
										tiOldX = myiCurX; tiOldY = myiCurY;
									//Move the cursor to the beginnig of the string
										myiCurX -= s.length();
							
									//Draw spaces over the old string
										for(unsigned int i = 0; i < s.length(); i++)
										{	Insert(' ', myiCurX, myiCurY, 0);
										}
										
									//Restore the cursor's old position
										myiCurX = tiOldX;	myiCurY = tiOldY;
									//Move the cursor to the beginnig of the string
										myiCurX -= s.length();
									
									//Delete this character out of the string
										s = s.substr(0, s.length() - 1);
									
									//Redraw this string onto the console
										Write(s, iFont);
								}
						}
					//- [Enter] -
						else if(iKey == SDLK_RETURN)
						{	//We're done!
								fDone = true;
								
							//Loop until the user stops pressing return
								while(myoInput.KeyDown(SDLK_RETURN)) {myoInput.Update();}
						}
					//- [Any typable key, if legal] -
						else if(iKey >= KEY_TYPEABLE1 && iKey <= KEY_TYPEABLE2 && s.length() < iMaxChars)
						{	//Shift + Typable Key
								if(myfShiftDown)
								{	//If its a letter Capatilize it
										if(iKey >= SDLK_a && iKey <= SDLK_z)
											iKey = char(iKey + 'A'-'a');
		      						//If its a # or punction mark
      									else if(iKey == SDLK_BACKQUOTE) iKey = '~';
      									else if(iKey == SDLK_0) iKey = ')';
      									else if(iKey == SDLK_1) iKey = '!';
      									else if(iKey == SDLK_2) iKey = '@';
		      							else if(iKey == SDLK_3) iKey = '#';
      									else if(iKey == SDLK_4) iKey = '$';
      									else if(iKey == SDLK_5) iKey = '%';
      									else if(iKey == SDLK_6) iKey = '^';
      									else if(iKey == SDLK_7) iKey = '&';
		      							else if(iKey == SDLK_8) iKey = '*';
      									else if(iKey == SDLK_9) iKey = '(';
      									else if(iKey == SDLK_MINUS)		 	iKey = '_';
      									else if(iKey == SDLK_EQUALS)		iKey = '+';
      									else if(iKey == SDLK_LEFTBRACKET) 	iKey = '{';
		      							else if(iKey == SDLK_RIGHTBRACKET) 	iKey = '}';
      									else if(iKey == SDLK_BACKSLASH)		iKey = '|';
      									else if(iKey == SDLK_SEMICOLON)		iKey = ':';
      									else if(iKey == SDLK_QUOTE)			iKey = '\"';
      									else if(iKey == SDLK_COMMA)			iKey = '<';
		      							else if(iKey == SDLK_PERIOD)		iKey = '>';
      									else if(iKey == SDLK_SLASH)			iKey = '?';
      									else if(iKey == SDLK_SPACE)			iKey = ' ';
      							
									//Recognize a shift free state
										myfShiftDown = false;

									//Output this char
										Insert(iKey, myiCurX, myiCurY, iFont);
									
									//Add it to s
										s += iKey;
      							}
 								//Just a typable key
 									else
									{	//Output this char
										Insert(iKey, myiCurX, myiCurY, iFont);
											
										//Add it to s
											s += iKey;
									}
						}
					iKey = myoInput.GetKey(false, 250, 0);
				}
				
				//Redraw
					Draw();
				//Draw the cursor!
					int iPixPerCharX = mypoFonts->operator[](0).Width();
					int iPixPerCharY = mypoFonts->operator[](0).Height();				
					mypoSurface->DrawFillRectangle((myiCurX - myiViewX) * iPixPerCharX + myiConsoleX,
 					  (myiCurY - myiViewY) * iPixPerCharY + myiConsoleY, 2, FontHeight(), COLOR_WHITE, 255);
				//Update
					mypoSurface->Update();
					myoInput.Update();
		}
		
	//Wait for enter to be depressed, it's a sad key now :-(
		while(myoInput.KeyDown(SDLK_RETURN))
			myoInput.Update();

	//Return the string that was inputted
		return(s);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Grabs a word from the user
string	ASFC_Console::GrabWord(int iFont)
{	//Vars
		string s;	//String data extracted from the console
		int iDummy = 0;
	
	//Input data from the console
		s = GrabString(iFont);
	
	//Grab the first word in this string
		return(ParseWord(s, iDummy));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Grabs a word from the user, iMaxChars = char limit
string	ASFC_Console::GrabWord(int iFont, int iMaxChars)
{	//Vars
		string s;	//String data extracted from the console
		int iDummy = 0;
	
	//Input data from the console
		s = GrabString(iFont, iMaxChars);
	
	//Grab the first word in this string
		return(ParseWord(s, iDummy));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Grabs a char from the user
char	ASFC_Console::GrabChar(int iFont)
{	//vars
		string s;
	
	//Input data from the console
		s = GrabString(iFont, 1);
	
	//Convert this to a string and return it
		return(s[0]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Grabs an int from the user
int		ASFC_Console::GrabInt(int iFont)
{	//vars
		string s;
	
	//Input data from the console
		s = GrabString(iFont);
	
	//Convert this to a val and return that
		return(int(Val(s)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Grabs a double from the user
double	ASFC_Console::GrabDouble(int iFont)
{	//vars
		string s;
	
	//Input data from the console
		s = GrabString(iFont);
	
	//Convert this to a val and return that
		return(Val(s));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Pauses the console until any key is pressed
void	ASFC_Console::Pause()
{	//Loop until we've pressed enter		
		while(myoInput.GetKey(false, 500, 500) == -1){}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
ASFC_Console& ASFC_Console::operator>> (string &s)
{	//Grab a string
		s = GrabString(myiCurrentFont);
	
	//Return self
		return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
ASFC_Console& ASFC_Console::operator>> (int &i)
{	//Grab an int
		i = GrabInt(myiCurrentFont);

	//Return self
		return(*this);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
ASFC_Console& ASFC_Console::operator>> (double &d)
{	//Grab a double
		d = GrabDouble(myiCurrentFont);
	
	//Return self
		return(*this);
}
//----------------------------------------------------------------------------------------------- [Info] -
//Extracts the handle of the font at location iX, iY
int  ASFC_Console::FontAt(C_i2(iX, iY))
{	return(myloData[iX][iY].iFont);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Extracts the char at location iX, iY
char ASFC_Console::CharAt(C_i2(iX, iY))
{	return(myloData[iX][iY].c);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Changes piX and piY into the the pix location of char iX iY
void ASFC_Console::PixLocation(int* piX, int* piY, int iX, int iY)
{	//Figure out piY
		*piY = iY * FontHeight() + ConsoleY() - ViewportY() * FontHeight();
		
	//Figure out what piX would be if it weren't for those evil tabs
		*piX = iX * FontWidth() + ConsoleX() - ViewportX() * FontWidth();

	//Now loop through the string at iX
		for(int i = 0; i < iX; i++)
		{	//If there's a tab here
				if(myloData[i][iY].c = '\t')
				{	//Move the piX over for the # of chars in a tab - the 1 char we already dealt with
						for(int j = 1; j < TabSize(); j++)
						{	*piX += FontWidth();
						}
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Console::CharacterAtPixel(int piX, int piY, int* iX, int* iY)
{	//Grab the # of pixels per character
		int	iPixPerCharX = mypoFonts->operator[](0).Width();
		int	iPixPerCharY = mypoFonts->operator[](0).Height();
	
	//Conert this sucker
		(*iX) = (piX - myiConsoleX) / iPixPerCharX;
		(*iY) = (piY - myiConsoleY) / iPixPerCharY;
}
//------------------------------------------------------------------------------------- [Font Handeling] -
//------------------------------------------------------------------------------------------ [Viewports] -		
//Sets the top left corner of the console
void ASFC_Console::SetConsolePosition(int iX, int iY)
{	//Okay, now set it
		myiConsoleX = iX;
		myiConsoleY = iY;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Sets the topleft corner of the viewport,
void ASFC_Console::SetViewport(int iX, int iY)
{	//Make sure it's legal to change here
		if(iX >= 0 && iX <= myiWidth && iY >= 0 && iY <= myiHeight)
		{	myiViewX = iX;
			myiViewY = iY;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Sets the size of the viewport		
void ASFC_Console::SetViewportSize(int iWidth, int iHeight)
{	myiViewSizeX	= iWidth;
	myiViewSizeY	= iHeight;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Sets the console size (in terms of chars)
void ASFC_Console::SetConsoleSize(int iWidth, int iHeight)
{	//Alright map params to mem vars
		myiWidth	=	iWidth;
		myiHeight	=	iHeight;
	
	//Move the cursor to the topleft corner
		myiCurX = 0;
		myiCurY = 0;
	
	//And resize the character matrix
		myloData.Resize(iWidth, iHeight);
}
//------------------------------------------------------------------------------------------- [Keyboard] -
//Sets the keyboard delay rates
void ASFC_Console::SetKeyboardSettings(C_i2(iKeyDelay, iRepeatRate))
{	myiKeyDelay 	= iKeyDelay;
	myiRepeatRate	= iRepeatRate;
}
//P------------------------------------------------------------------------------------- [Construction] -P
//Set variables to their default values
void ASFC_Console::SetVarsDefaults()
{	//Set variables to their defaults
		SetConsolePosition(0, 0);
		SetConsoleSize(80, 25);
		SetViewportSize(80, 25);
		SetViewport(0, 0);
		WordWrap(ON);
		TabSize(4);
		AutoViewport(ON);
		SetKeyboardSettings(250, 10);
		CurrentFont(0);
}
//P--------------------------------------------------------------------------------------- [Outputting] -P
//Moves the cursor iChars to the right
void ASFC_Console::MoveCursor(int iChars)
{	//Increment the cusorX
		myiCurX += iChars;

	//While the cursor X is too large
		while(myiCurX > myiWidth)
		{	//Move the cursor down a line
				myiCurY++;
			
			//Send the carridge back *ding*
				myiCurX -= myiWidth;
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... P
//Creates a newline char in the console
void ASFC_Console::NewLine()
{	//Move the cursor down a line
		myiCurY++;
	
	//Send the carridge back *ding*
		myiCurX = 0;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... P
//Destroys line # iLine and moves all text beyond that up a line
void ASFC_Console::KillLine(int iLine)
{	//Remove that row out of the data matrix
		myloData.RemoveRow(iLine);
	
	//Resize the data matrix back to its original size
		myloData.Resize(myiWidth, myiHeight);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... P
//Makes sure the curosr is on a valid position, if not move it to one
void ASFC_Console::CheckCursor()
{	//Make sure cursor X & cursor Y are positive
		if(myiCurX < 0) myiCurX = 0;
		if(myiCurY < 0) myiCurY = 0;
			
	
	//While the cursor X is too large
		while(myiCurX > myiWidth)
		{	//Move the cursor down a line
				myiCurY++;
			
			//Send the carridge back *ding*
				myiCurX -= myiWidth;
		}
		
	//While the cursor Y is too large
		while(myiCurY >= myiHeight)
		{	//Decrease the cursor Y
				myiCurY--;
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... P
//Checks if iFont is valid if not errrs
bool ASFC_Console::ValidFont(int iFont)
{	if(iFont < 0 || iFont >= mypoFonts->Length())
	{	cerr << "ERR In ASFC_Console::ValidFont(int iFont), invalid font!\n";
		return false;
	}
	return true;
}
//P--------------------------------------------------------------------------------- [Helper Functions] -P
//Returns the next word in string s from char iIndex
string ASFC_Console::ParseWord(string s, int &iIndex)
{	//Const
		const char SPACE_CHARS[] = {' ', '\n', '\t'};		//Holds characters that count as spaces

	//vars
		int	i_sLength = s.length();
		int iOldIndex = iIndex;
	
	//Loop while there's space chars and more chars
		while(CharInArray(s[iIndex], SPACE_CHARS)     && iIndex < i_sLength)
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
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... P
//Returns true if there's a char in array cArray
bool ASFC_Console::CharInArray(char c, const char cArray[])
{	//Vars
		int iArraySize = sizeof(cArray);
	
	//Loop through all the chars in the char array
		for(int i = 0; i < iArraySize; i++)
		{	//Does this char match c?				
				if(cArray[i] == c)
					return(true);
		}

	//If execution gets here no chars matched
		return(false);
}
