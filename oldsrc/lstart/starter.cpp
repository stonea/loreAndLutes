/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			starter.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Starter
   | ----` |	Last Updated:
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "starter.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LSTART_Starter
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LSTART_Starter::LSTART_Starter(ASFC_Screen* poScreen)
{	myiState = STATE_NOTHING;
	mypoScreen = poScreen;
	myimgBackground.LoadImage("background.png");
	myoDescriptionViewer.Setup(&myimgBackground, DESCRIPTION_X, DESCRIPTION_Y, DESCRIPTION_W, DESCRIPTION_H);
	myoGamesList.Setup(&myimgBackground, GAMES_MENU_X, GAMES_MENU_Y, GAMES_MENU_W, GAMES_MENU_H);
	mysGame = myoGamesList.Selection();
	
	out.open("out.txt");
	
	//Set up the console
		myoConFont.Load("./data/gui/fonts/normal_console_font.png", 8, 14, COLOR_BLUE);
		myoFonts.Push(myoConFont);
		myoConFont.Load("./data/gui/fonts/bold_console_font.png", 8, 14, COLOR_BLUE);
		myoFonts.Push(myoConFont);
		myoConsole.SetFontPalette(&myoFonts);
		myoConsole.SetSurface(poScreen);
		myoConsole.SetConsolePosition(0, 0);
		myoConsole.SetViewport(0, 0);
		myoConsole.SetViewportSize(poScreen->GetWidth() / 8, poScreen->GetHeight() / 14);
		myoConsole.SetConsoleSize (poScreen->GetWidth() / 8, poScreen->GetHeight() / 14);
}
//--------------------------------------------------------------------------------------------- [Starter] -
void LSTART_Starter::Run()
{	//Vars
		bool fExit = false;
		LEDIT_MapEditor::LEDIT_TestInformation oTestInfo;

	//While we're not ready to exit the starter
		while(!fExit)
		{	//Default the state to nothing
				myiState = STATE_NOTHING;
   			//While we're in a state of nothingness
				while(myiState == STATE_NOTHING)
				{	//ReDraw
						Draw();
		  			//Check keys
	 					CheckKeys();
				}
			//Check the current state
				switch(myiState)
				{	case STATE_EDIT:
					{	oTestInfo = myoEditor.StartEditor(mypoScreen, mysGame);
						while(oTestInfo.fTest)
						{	myoRunner.StartRunner(mypoScreen, mysGame, oTestInfo.iMap, oTestInfo.iX, oTestInfo.iY);
							oTestInfo = myoEditor.StartEditor(mypoScreen, mysGame, oTestInfo.iMap, oTestInfo.iX, oTestInfo.iY);
						}
					}break;
					
					case STATE_PLAY:
     				{	myoRunner.StartRunner(mypoScreen, mysGame);
	     					//fExit = true;
          			}break;
          			
          			case STATE_NEW:
          			{	string sGameDescription = myoGameMaker.AskForGameDescription(myoConsole);
          				mypoScreen->Update();
	          			string sGameTitle       = myoGameMaker.AskForGameTitle(myoConsole, myoGamesList);
	          			mypoScreen->Update();
	          			myoGameMaker.MakeNewGame(sGameDescription, sGameTitle);
	          			
	          			oTestInfo = myoEditor.StartEditor(mypoScreen, mysGame);
						while(oTestInfo.fTest)
						{	myoRunner.StartRunner(mypoScreen, mysGame, oTestInfo.iMap, oTestInfo.iX, oTestInfo.iY);
							oTestInfo = myoEditor.StartEditor(mypoScreen, mysGame);
						}
						
	          			myoGamesList.AddGame(sGameTitle);
						myoGamesList.SelectFirst();
						mysGame = myoGamesList.Selection();
	          			//ReDraw
							Draw();
          			}break;
          			
          			case STATE_EXIT:
     				{	fExit = true;
          			}break;
          			
					default: break;
				}
		}
}
//P------------------------------------------------------------------------------------------- [Starter] -P
void LSTART_Starter::CheckKeys()
{	//Vars
		bool fDone = false;
		int  iKey  = -1;
		int  iLastKey = -2;

	//Get a key
		while(iKey == -1)
		{	iKey = myoInput.GetKey(false, 250, 5);
			HandleMouse();
		}

		while(iKey != -1 && iKey != iLastKey)
		{	iLastKey = iKey;
			HandleMouse();
			//Decide what to do based on what key is down
			//- [Play] -
				if(iKey == KEY_PLAY)
				{	myiState = STATE_PLAY;
    				fDone = true;
					ASFC_Surface imgTmp;
    				imgTmp.LoadImage("startgame.png"),
    				imgTmp.BlitTo(*mypoScreen, 10, 10);
    				mypoScreen->Update();
				}
			//- [Edit] -
				else if(iKey == KEY_EDIT)
				{	myiState = STATE_EDIT;
    				fDone = true;
    				ASFC_Surface imgTmp;
    				imgTmp.LoadImage("starteditor.png"),
    				imgTmp.BlitTo(*mypoScreen, 10, 10);
    				mypoScreen->Update();
				}
			//- [New] -
				else if(iKey == KEY_NEW)
				{	myiState = STATE_NEW;
					fDone = true;
				}
			//- [Quit] -
				else if(iKey == KEY_QUIT || iKey == KEY_QUIT2)
				{	myiState = STATE_EXIT;
    				fDone = true;
				}
			//- [Prev] -
				else if(iKey == KEY_PREV)
				{	myoGamesList.SelectPrev();
					mysGame = myoGamesList.Selection();
					Draw();
					fDone = true;
				}
			//- [Next] -
				else if(iKey == KEY_NEXT)
				{	myoGamesList.SelectNext();
					mysGame = myoGamesList.Selection();
					Draw();
					fDone = true;
				}
			//Reget a key
				iKey = myoInput.GetKey(false, 250, 0);			
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_Starter::Draw()
{	//Draw the text
		myoDescriptionViewer.ViewDescription(mysGame);
	//Load and draw the logo
		myimgLogo.LoadImage("./games/" + mysGame + "/logo.png");
		myimgLogo.BlitTo(myimgBackground, LOGO_X, LOGO_Y);
	//Clear out the
	//Draw the games list
		myoGamesList.DrawList();
	//Draw the background
		myimgBackground.BlitTo(*mypoScreen, 0, 0);
	//Flip the back buffer
		mypoScreen->Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LSTART_Starter::HandleMouse()
{	//Vars
		int iMouseX, iMouseY, iMouseX2, iMouseY2, iRow, iRow2, iCurrentRow, iMoveDown;

	//If the user is clicking
		myoInput.Update();
		if(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
		{	//Get the position
				iMouseX = myoInput.GetMouseX();
				iMouseY = myoInput.GetMouseY();
				
			//If this position is within the games list
				if( iMouseX >= GAMES_MENU_X && iMouseY >= GAMES_MENU_Y && iMouseX <= GAMES_MENU_X + GAMES_MENU_W * 8 &&
					iMouseY <= GAMES_MENU_Y + GAMES_MENU_H * 14)
				{	//Translate this into a row
						iRow = (iMouseY - GAMES_MENU_Y) / 14;
					//Wait for the click to be released
						while(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
							myoInput.Update();
					//Translate this into a row
						myoInput.Update();
						iMouseX2 = myoInput.GetMouseX();
						iMouseY2 = myoInput.GetMouseY();
						iRow2 = (iMouseY2 - GAMES_MENU_Y) / 14;
					//If we're at a different row forget about it
						if(iRow2 != iRow)
							return 0;
					//If the X is off the screen forget about it
						if(!(iMouseX2 >= GAMES_MENU_X && iMouseX2 <= GAMES_MENU_X + GAMES_MENU_W * 8))
							return 0;
					//Find the difference from the real row and the clicked one
						iMoveDown = iRow - myoGamesList.CurrentRow();
					//Now fix it
						if(iMoveDown < 0)
						{	for(int i = 0; i > iMoveDown; i--)
								myoGamesList.SelectPrev();
						}
						if(iMoveDown > 0)
						{	for(int i = 0; i < iMoveDown; i++)
								myoGamesList.SelectNext();
						}
					//Redraw
						mysGame = myoGamesList.Selection();
						Draw();
				}
		}

	return 0;
}
