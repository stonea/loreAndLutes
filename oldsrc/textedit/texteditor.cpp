/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS
	By: Andy Stone

	File for: TE_TextEditor
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "texteditor.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												TE_TextEditor
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
TE_TextEditor::TE_TextEditor()	
{	myfConsoleSet		= false;
	myiRowAtTopOfScreen	= 0;
	myiProtectedMin		= -1;
	myiProtectedMax		= -1;
	myfProtectData		= false;
	myiState			= STATE_GOOD;
	myiFont				= 0;
	myfShiftDown		= false;
	myoTimer.Reset();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_TextEditor::SetConsole(ASFC_Console* pConsole)
{	//Set the console and the flag that says we set it
		mypoConsole 	= pConsole;
		myfConsoleSet 	= true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_TextEditor::SetDefaults()
{	myiRowAtTopOfScreen	= 0;
	myiProtectedMin		= -1;
	myiProtectedMax		= -1;
	myfProtectData		= false;
	myiState			= STATE_GOOD;
	myiFont				= 0;
	myfShiftDown		= false;
	myoTimer.Reset();
	mypoText->MoveCursor(0, 0);
	CheckCursorPosition();
	
	//Make sure we have atleast 1 line
		if(mypoText->NumRows() < 1)
		{	AddRow();
		}
}
//-------------------------------------------------------------------------------------- [Text Editting] -
void TE_TextEditor::EditText(TE_Text* poTextToEdit)
{	//Map params to the appropriate vars
		mypoText = poTextToEdit;
		mypoText->SetMaximumNumColumns(mypoConsole->ConsoleWidth());

	//Set defaults
		SetDefaults();

	//Now really (no really!) edit the text
		EditText();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_TextEditor::EditText(TE_Text* poTextToEdit, int* piProtectedMinRow, int* piProtectedMaxRow)
{	//Map params to the appropriate vars
		mypoText 		= poTextToEdit;
		mypoText->SetMaximumNumColumns(mypoConsole->ConsoleWidth());
	//Set defaults
		SetDefaults();
	//Set the protected region
		myiProtectedMin = *piProtectedMinRow;
		myiProtectedMax = *piProtectedMaxRow;
		myfProtectData 	= true;

	//Set the cursor to border with the protected area
		mypoText->MoveCursor(0, myiProtectedMin);
		myiRowAtTopOfScreen = myiProtectedMin;

	//Now really (no really!) edit the text
		EditText();
		
	//Now update the min and max rows
		*piProtectedMinRow = myiProtectedMin;
		*piProtectedMaxRow = myiProtectedMax;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_TextEditor::EditText(TE_Text* poTextToEdit, int* piProtectedMinRow, int* piProtectedMaxRow,
							 int iCur)
{	//Map params to the appropriate vars
		mypoText 		= poTextToEdit;
		mypoText->SetMaximumNumColumns(mypoConsole->ConsoleWidth());
	//Set defaults
		SetDefaults();
	//Set the protected region
		myiProtectedMin = *piProtectedMinRow;
		myiProtectedMax = *piProtectedMaxRow;
		myfProtectData 	= true;

	//Set the cursor to border with the protected area
		mypoText->MoveCursor(0, iCur);
		myiRowAtTopOfScreen = iCur - mypoConsole->ConsoleHeight() / 2;
		if(myiRowAtTopOfScreen < *piProtectedMinRow)
			myiRowAtTopOfScreen = *piProtectedMinRow;

	//Now really (no really!) edit the text
		EditText();
		
	//Now update the min and max rows
		*piProtectedMinRow = myiProtectedMin;
		*piProtectedMaxRow = myiProtectedMax;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_TextEditor::ViewText(TE_Text* poTextToEdit)
{	//Map params to the appropriate vars
		mypoText 		= poTextToEdit;
		mypoText->SetMaximumNumColumns(mypoConsole->ConsoleWidth());

	//Set defaults
		SetDefaults();
		myiState = STATE_GOOD;
		
	//Draw everything important for the edit
		DrawText();
		mypoConsole->Surface()->Update();

	//If we're ready for launch
		if(EditorReady())
		{	//Keep on a-updatin till we're told to quit!
				while(myiState != STATE_EXIT)
    				UpdateTextViewer();
		}
}
//P----------------------------------------------------------------------------------------- [Updating] -P
void TE_TextEditor::EditText()
{	//Draw everything important for the edit
		DrawText();
		DrawCursor();
		mypoConsole->Surface()->Update();

	//Set the state to good
		myiState = STATE_GOOD;

	//If we're ready for launch
		if(EditorReady())
		{	//Keep on a-updatin till we're told to quit!
				while(myiState != STATE_EXIT)
					UpdateTextEdit();
		}
		
	//Reset the console state
		mypoConsole->ViewportX(0);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::UpdateTextEdit()
{	//Handle keys, and then draw the text and cursor, and of course update the double buffer!
		HandleKeys();
		CheckCursorPosition();
		DrawText();
		DrawCursor();
		mypoConsole->Surface()->Update();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::UpdateTextViewer()
{	//Handle viewing keys, and then draw the text and cursor, and of course update the double buffer!
		HandleViewingKeys();
		CheckCursorPosition();
		DrawText();
		mypoConsole->Surface()->Update();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::DrawText()
{	//Vars
		int iRowAtBottomOfScreen;
		
	//Reset the console
		mypoConsole->Clear();
		
	//Calculamate the bottom row to draw if we have protected data make sure it doesn't exceed the max row
		iRowAtBottomOfScreen     = myiRowAtTopOfScreen + mypoConsole->ConsoleHeight();
		if(iRowAtBottomOfScreen  > myiProtectedMax+1 && myfProtectData)
			iRowAtBottomOfScreen = myiProtectedMax+1;

	//Loop through all rows visible on the console
		for(int i = myiRowAtTopOfScreen; i < iRowAtBottomOfScreen; i++)
		{	//Draw this line (yay!)
				mypoConsole->Writeln(mypoText->GetData(i), myiFont);
		}
		
	//Set the viewport x
		if(mypoText->CursorColumn() > mypoConsole->ViewportX() + mypoConsole->ViewSizeX())
		{	mypoConsole->ViewportX(mypoText->CursorColumn() - mypoConsole->ViewSizeX());
		}
		if(mypoText->CursorColumn() < mypoConsole->ViewportX())
		{	mypoConsole->ViewportX(mypoText->CursorColumn());
		}

	//Draw the console
		mypoConsole->Draw(0xFF);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::DrawCursor()
{	//Vars
		int iPixX, iPixY;
		string s;
		
	//Translate the cursor position into a pixel location
		iPixX = mypoText->CursorColumn() * mypoConsole->FontWidth() + mypoConsole->ConsoleX() -
  				mypoConsole->ViewportX() * mypoConsole->FontWidth();
		iPixY = mypoText->CursorRow()	* mypoConsole->FontHeight() + mypoConsole->ConsoleY() - 
  				myiRowAtTopOfScreen 	* mypoConsole->FontHeight();
  				
	//Grab the row of data where the cursor is and check for tabs
		s = mypoText->GetData(mypoText->CursorRow());
		for(int i = 0; i < mypoText->CursorColumn(); i++)
		{	//If there's a tab adjust the cursor x to go past it
	  			if(s[i] == '\t')
				{	iPixX += (mypoConsole->TabSize()-1) * mypoConsole->FontWidth();
				}
		}

	//Draw the cursor here
		mypoConsole->Surface()->DrawFillRectangle(iPixX, iPixY, 2, 14, COLOR_WHITE, 255);
}

//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::HandleKeys()
{	//Vars
		bool fDone = false;
		int  iKey  = -1;
		int  iLastKey = -2;

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
		{	iKey = myoInput.GetKey(false, 250, 5);
			HandleMouse();
		}

		while(iKey != -1 && iKey != iLastKey)
		{	iLastKey = iKey;
			HandleMouse();
		
			//If shift is being pressed
				myoInput.Update();
				if(myoInput.KeyDown(SDLK_LSHIFT) || myoInput.KeyDown(SDLK_RSHIFT))
			  		myfShiftDown = true;
				else
					myfShiftDown = false;

		
			//Decide what to do based on what key is down
			//- [Escape] -
				if(iKey == KEY_EXIT)
				{	//Wait for escape to be upressed, you know Happy! (um not depressed)
						while(myoInput.KeyDown(KEY_EXIT))
						{	myoInput.Update();
						}
    				//Set the viewport x
						mypoConsole->ViewportX(0);
    				
    				myiState = STATE_EXIT;
					fDone = true;
				}
			//- [Left] -
				else if(iKey == KEY_LEFT)
				{	//Move the cursor one char to the left (-1 chars right)
	   					mypoText->MoveCursor(-1);
					fDone = true;
				}
			//- [Right] -
				else if(iKey == KEY_RIGHT)
				{	//Move the cursor one char to the right
	    				mypoText->MoveCursor(1);
					fDone = true;
				}
			//- [Up] -
				else if(iKey == KEY_UP)
				{	//Move the cursor up
						MoveUpARow();	    		 					
					fDone = true;
				}
			//- [Down] -
				else if(iKey == KEY_DOWN)
				{	//Move the cursor down
						MoveDownARow();
	 				fDone = true;
				}
			//- [Delete] -
				else if(iKey == KEY_DELETE)
				{	//Sing a song, kill a char
						mypoText->Delete();
					fDone = true;
				}
			//- [Backspace] -
				else if(iKey == KEY_BACKSPACE)
				{	//Sing a song, kill a char
						mypoText->BackSpace();
					fDone = true;
				}
			//- [Home] -
				else if(iKey == KEY_HOME)
				{	mypoText->MoveCursor(0, mypoText->CursorRow());
					fDone = true;
				}
			//- [End] -
				else if(iKey == KEY_END)
				{	mypoText->MoveCursor(mypoText->GetData(mypoText->CursorRow()).length(),
										 mypoText->CursorRow());
					fDone = true;
				}
			//- [KEY_PAGEUP] -
				else if(iKey == KEY_PAGEUP)
				{	//Move up a page
						for(int i = 0; i < mypoConsole->ConsoleHeight()-1; i++)
							MoveUpARow();
					fDone = true;
				}
			//- [KEY_PAGEDOWN] -
				else if(iKey == KEY_PAGEDOWN)
				{	//Move down a page
						for(int i = 0; i < mypoConsole->ConsoleHeight()-1; i++)
							MoveDownARow();
					fDone = true;
				}
			//- [New row] -
				else if(iKey ==	KEY_NEWROW)
				{	AddRow();
					fDone = true;
				}
			//- [Any typable key] -
				else if(iKey >= KEY_TYPEABLE1 && iKey <= KEY_TYPEABLE2)
				{	//Cntrl + Typable Key
						if(myoInput.KeyDown(SDLK_LCTRL) || myoInput.KeyDown(SDLK_RCTRL))
						{	if(iKey == KEY_REMOVEROW)
							{	DeleteRow();
								fDone = true;
							}							
						}
    				//Shift + Typable Key
						else if(myfShiftDown)
						{	//If its a letter Capatilize it
								if(iKey >= SDLK_a && iKey <= SDLK_z)
									mypoText->Insert(char(iKey + 'A'-'a'));
      						//If its a # or punction mark
      							else if(iKey == SDLK_BACKQUOTE) mypoText->Insert('~');
      							else if(iKey == SDLK_0) mypoText->Insert(')');
      							else if(iKey == SDLK_1) mypoText->Insert('!');
      							else if(iKey == SDLK_2) mypoText->Insert('@');
      							else if(iKey == SDLK_3) mypoText->Insert('#');
      							else if(iKey == SDLK_4) mypoText->Insert('$');
      							else if(iKey == SDLK_5) mypoText->Insert('%');
      							else if(iKey == SDLK_6) mypoText->Insert('^');
      							else if(iKey == SDLK_7) mypoText->Insert('&');
      							else if(iKey == SDLK_8) mypoText->Insert('*');
      							else if(iKey == SDLK_9) mypoText->Insert('(');
      							else if(iKey == SDLK_MINUS)		 	mypoText->Insert('_');
      							else if(iKey == SDLK_EQUALS)		mypoText->Insert('+');
      							else if(iKey == SDLK_LEFTBRACKET) 	mypoText->Insert('{');
      							else if(iKey == SDLK_RIGHTBRACKET) 	mypoText->Insert('}');
      							else if(iKey == SDLK_BACKSLASH)		mypoText->Insert('|');
      							else if(iKey == SDLK_SEMICOLON)		mypoText->Insert(':');
      							else if(iKey == SDLK_QUOTE)			mypoText->Insert('\"');
      							else if(iKey == SDLK_COMMA)			mypoText->Insert('<');
      							else if(iKey == SDLK_PERIOD)		mypoText->Insert('>');
      							else if(iKey == SDLK_SLASH)			mypoText->Insert('?');
      							else if(iKey == SDLK_SPACE)			mypoText->Insert(' ');
      							
							//Recognize a shift free state
								myfShiftDown = false;
      					}
 						//Just a typable key
 							else
								mypoText->Insert(char(iKey));
				}
			CheckCursorPosition();
			iKey = myoInput.GetKey(false, 250, 0);			
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::HandleMouse()
{	//If the mouse is down
	if(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
	{	//Translate the cursor position
			int iMouseX = myoInput.GetMouseX();
			int iMouseY = myoInput.GetMouseY();
			int iCharX, iCharY;
			mypoConsole->CharacterAtPixel(iMouseX, iMouseY, &iCharX, &iCharY);
			mypoText->MoveCursor(mypoConsole->ViewportX() + iCharX, myiRowAtTopOfScreen + iCharY);
		//Redraw
			CheckCursorPosition();
			DrawText();
			DrawCursor();
			mypoConsole->Surface()->Update();
		//Wait for the button to be released
			while(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
				myoInput.Update();
	}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::HandleViewingKeys()
{	//Vars
		bool fDone = false;
		int  iKey  = -1;
		int  iLastKey = -2;

	//Get a key
		while(iKey == -1)
			iKey = myoInput.GetKey(false, 250, 0);

		while(iKey != -1 && iKey != iLastKey)
		{	iLastKey = iKey;
		
			//Decide what to do based on what key is down
			//- [Escape] -
				if(iKey == KEY_EXIT)
				{	//Wait for escape to be upressed, you know Happy! (um not depressed)
						while(myoInput.KeyDown(KEY_EXIT))
						{	myoInput.Update();
						}
						
	    				myiState = STATE_EXIT;
						fDone = true;
				}
			//- [Up] -
				else if(iKey == KEY_UP)
				{	//Move the cursor up
						MoveUpARow();
						myiRowAtTopOfScreen--;
						CheckCursorPosition();
					fDone = true;
				}
			//- [Down] -
				else if(iKey == KEY_DOWN)
				{	//Move the cursor down
						MoveDownARow();
						myiRowAtTopOfScreen++;
						CheckCursorPosition();
	 				fDone = true;
				}
			//- [KEY_PAGEUP] -
				else if(iKey == KEY_PAGEUP)
				{	//Move up a page
						myiRowAtTopOfScreen = myiRowAtTopOfScreen - mypoConsole->ConsoleHeight()-1;
						mypoText->MoveCursor(mypoText->CursorColumn(), myiRowAtTopOfScreen);
						CheckCursorPosition();
					fDone = true;
				}
			//- [KEY_PAGEDOWN] -
				else if(iKey == KEY_PAGEDOWN)
				{	//Move down a page
						myiRowAtTopOfScreen = myiRowAtTopOfScreen + mypoConsole->ConsoleHeight()-1;
						mypoText->MoveCursor(mypoText->CursorColumn(), myiRowAtTopOfScreen);
						CheckCursorPosition();
					fDone = true;
				}
			CheckCursorPosition();
			iKey = myoInput.GetKey(false, 250, 0);			
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::MoveDownARow()
{	mypoText->MoveCursor(mypoText->CursorColumn(), mypoText->CursorRow()+1);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::MoveUpARow()
{	mypoText->MoveCursor(mypoText->CursorColumn(), mypoText->CursorRow()-1);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::CheckCursorPosition()
{	//If the cursor is off the screen (too high up)
		while(mypoText->CursorRow() < myiRowAtTopOfScreen)
		{	//Set the cursor to be in the screen
  			myiRowAtTopOfScreen = mypoText->CursorRow();
		}
	//If the cursor is off the screen (too far down)
		while(mypoText->CursorRow() >= myiRowAtTopOfScreen + mypoConsole->ConsoleHeight())
		{	//Set the cursor to be in the screen
				myiRowAtTopOfScreen = mypoText->CursorRow() - mypoConsole->ConsoleHeight()+1;
		}
		
	//If we have range protection on
		if(myfProtectData)
		{	//If we're up to far (screen wise)
				if(myiRowAtTopOfScreen < myiProtectedMin)
				{	myiRowAtTopOfScreen = myiProtectedMin;
				}
			//If we're up to far (cursor wise)
				while(mypoText->CursorRow() < myiProtectedMin)
				{	mypoText->MoveCursor(mypoText->CursorColumn(), mypoText->CursorRow()+1);
				}
  			//If we're down to far
				while(mypoText->CursorRow() > myiProtectedMax)
				{	mypoText->MoveCursor(mypoText->CursorColumn(), mypoText->CursorRow()-1);
				}
		}
	//If we have no range protection on
		else
		{	//If we're up to far (screen wise)
				if(myiRowAtTopOfScreen < 0)
				{	myiRowAtTopOfScreen = 0;
				}
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::AddRow()
{	//Add a row after the cursor
		mypoText->AddRow(mypoText->CursorColumn(), mypoText->CursorRow());
	//Expand our protected area a row too
		myiProtectedMax++;
	//Move down a row
		MoveDownARow();
	//Go home
		mypoText->MoveCursor(0, mypoText->CursorRow());
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void TE_TextEditor::DeleteRow()
{	//If this is the last row to delete
		if(mypoText->NumRows() - NumUnprotectedRows() <= 1)
		{	//Set this row to include nada, nothing, absolutely nothing
				mypoText->SetData(mypoText->CursorRow(), "");
		}
		else
		{	//If we've got plenty of space to kill
				//Delete this row
					mypoText->DeleteRow(mypoText->CursorRow());
				//De-expand our protected area a row too
					myiProtectedMax--;		
		}
		
	//Go home, check the cursor
		CheckCursorPosition();
		mypoText->MoveCursor(0, mypoText->CursorRow());
}

//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int	 TE_TextEditor::NumUnprotectedRows()
{	//If we have no protection return 0
		if(!myfProtectData)
			return(0);
	//Else if our data is protected return the rows before + the rows after the unprotected area
		return(myiProtectedMin + (mypoText->NumRows() - myiProtectedMax));
}

//P---------------------------------------------------------------------------------------- [Debugging] -P
bool TE_TextEditor::EditorReady()
{	//If we haven't set the console err and return false
		if(!myfConsoleSet)
		{	cout << "Poor and misguided user, you can't use this \n";
			cout << "editor until thou hast initilized everything. \n";
			cout << "Didst thou SetConsole?\n";;
			
			return(false);
		}
	//Otherwise we're all set and ready
		return(true);
}
