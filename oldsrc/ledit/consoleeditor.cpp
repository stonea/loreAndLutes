/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			consoleeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	09/20/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "consoleeditor.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_ConsoleEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ConsoleEditor::LEDIT_ConsoleEditor()
{	//Reset
		Reset(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Resets the state of the console editor
void LEDIT_ConsoleEditor::Reset(bool fResetCursor)
{	//Reset our selected option and option counting vars
		if(fResetCursor)
			myiSelected = 0;
		myiNumOptions	= 0;
		
	//Resize the information object to contain no data
		myoInfo.resize(0);
}			
//------------------------------------------------------------------------------------------- [Writting] -
//Writes a heading (unselectable portion of text) of sHeading
void LEDIT_ConsoleEditor::Heading(const string sHeading)
{	//Vars
		LEDIT_ConsoleEditInfo toEditInfo;

	//Form this into an edit info object
		toEditInfo.s 		= sHeading;
		toEditInfo.iType 	= CONSOLE_EDIT_TYPE_HEADING;

	//Push this edit info onto the console info object
		myoInfo.push_back(toEditInfo);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Writes the option sOption
void LEDIT_ConsoleEditor::Option(const string sOption)
{	//Vars
		LEDIT_ConsoleEditInfo toEditInfo;

	//Form this into an edit info object
		toEditInfo.s 		= sOption;
		toEditInfo.iType 	= CONSOLE_EDIT_TYPE_OPTION;

	//Push this edit info onto the console info object
		myoInfo.push_back(toEditInfo);
		
	//Update our # of options count
		myiNumOptions++;
}
//------------------------------------------------------------------------------------------- [Editting] -
//Sits waiting for a user to select an option, returns the selected option
int LEDIT_ConsoleEditor::GrabOption()
{	//Set up a chooser list including return and space
		ASFC_LinkedList<int> lChoosers;
  		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
	//Grab an option ignore the key
		int iDummyKey;
		return(GrabOption(&iDummyKey, lChoosers));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Grabs an option and returns the key used to select it
int LEDIT_ConsoleEditor::GrabOption(int* piKey, ASFC_LinkedList<int> lChoosers)
{	//Vars
		bool fDone = false;
		bool fExitLoop = false;
		int  iKey  = -1;
		int  iLastKey = -2;

	//Check and make sure the cursor is on a valid option, if not set to the first option (0)
		if(myiSelected >= myiNumOptions)
			myiSelected	= 0;
	//Draw all of our options
		Draw();
	//Loop until there's a choice or a cancel
		while(true)
		{	//Get a key
				iKey = -1;
				iLastKey = -2;
				while(iKey == -1)
				{	iKey = myoInput.GetKey(false, 350, 25);
					//- [Check mouse] -
						int iHndlMouse = HandleMouse(&iKey, lChoosers);
						if(iHndlMouse >= 0)
						{	*piKey = KEY_CHOOSE;
							return(iHndlMouse);
						}
				}
		
				fExitLoop = false;
				while(iKey != -1 && iKey != iLastKey && !fExitLoop)
				{	iLastKey = iKey;
					//Decide what to do based on what key is down
						//- [Check mouse] -
							int iHndlMouse = HandleMouse(&iKey, lChoosers);
							if(iHndlMouse >= 0)
								return(iHndlMouse);
						//- [Choose] -
							for(int i = 0; i < lChoosers.Length(); i++)
							{	if(iKey == SDLKey(lChoosers[i]))
								{	//Wait until that key is released
										while(myoInput.KeyDown(SDLKey(lChoosers[i])))
		   								{myoInput.Update();}
		   								
									//Set the choosing key
										*piKey = lChoosers[i];
										
									//Return with the chosen option
										return(myiSelected);
								}
							}
						//- [Cancel] -
							if(iKey == KEY_CANCEL)
							{	//Wait until that key is released
									while(myoInput.KeyDown(KEY_CANCEL)) {myoInput.Update();}
		 			
		   						//Return our cancel option
									return(CONSOLEEDIT_NONE);
							}
						//- [Previous] -
							else if(iKey == KEY_PREVIOUS)
							{	//If we can choose a previous option, choose it
									if(myiSelected > 0)
										myiSelected--;
								//Redraw
									Draw();
								//Reset the timer
									myoTimer.Reset();
								//Exit the loop
									fExitLoop = true;
							}
						//- [Next] -
							else if(iKey == KEY_NEXT)
							{	//If we can choose the next option, choose it
									if(myiSelected+1 < myiNumOptions)
										myiSelected++;
								//Redraw
									Draw();
								//Reset the timer
									myoTimer.Reset();
								//Exit the loop
									fExitLoop = true;
							}
						//- [Page up] -
							else if(iKey == KEY_PG_UP)
							{	//Go up five options
									myiSelected -= 5;
       							//If we can choose a previous option, choose it
									if(myiSelected < 0)
										myiSelected = 0;
								//Redraw
									Draw();
								//Reset the timer
									myoTimer.Reset();
								//Exit the loop
									fExitLoop = true;
							}
						//- [Page down] -
							else if(iKey == KEY_PG_DN)
							{	//Go down five options
									myiSelected += 5;
   								//If we can choose the next option, choose it
									if(myiSelected >= myiNumOptions)
										myiSelected = myiNumOptions - 1;
								//Redraw
									Draw();
								//Reset the timer
									myoTimer.Reset();
								//Exit the loop
									fExitLoop = true;
							}
					//Reget a key
						iKey = myoInput.GetKey(false, 350, 25);
				}
		}
/*
	//Check and make sure the cursor is on a valid option, if not set to the first option (0)
		if(myiSelected >= myiNumOptions)
			myiSelected	= 0;

	//Draw all of our options
		Draw();
		
	//Reset the timer
		myoTimer.Reset();

	//Loop until a return is forced (e.g. forever)
		while(1 == 1)
		{	//Update our input info
				myoInput.Update();
			
    		//Decide what to do based on what key is down (if enough time has passed since the last press
    			if(myoTimer.Ellapsed(DELAY))
    			{	//- [Check mouse] -
						int iHndlMouse = HandleMouse(piKey, lChoosers);
						if(iHndlMouse >= 0)
							return(iHndlMouse);
					//- [Choose] -
    					for(int i = 0; i < lChoosers.Length(); i++)
    					{	if(myoInput.KeyDown(SDLKey(lChoosers[i])))
							{	//Wait until that key is released
									while(myoInput.KeyDown(SDLKey(lChoosers[i])))
       								{myoInput.Update();}
       								
								//Set the choosing key
									*piKey = lChoosers[i];
									
								//Return with the chosen option
									return(myiSelected);
							}
						}
					//- [Cancel] -
						if(myoInput.KeyDown(KEY_CANCEL))
						{	//Wait until that key is released
								while(myoInput.KeyDown(KEY_CANCEL)) {myoInput.Update();}
     			
       						//Return our cancel option
								return(CONSOLEEDIT_NONE);
						}
					//- [Previous] -
						else if(myoInput.KeyDown(KEY_PREVIOUS))
						{	//If we can choose a previous option, choose it
								if(myiSelected > 0)
									myiSelected--;
							//Redraw
								Draw();
							//Reset the timer
								myoTimer.Reset();
						}
					//- [Next] -
						else if(myoInput.KeyDown(KEY_NEXT))
						{	//If we can choose the next option, choose it
								if(myiSelected+1 < myiNumOptions)
									myiSelected++;
							//Redraw
								Draw();
							//Reset the timer
								myoTimer.Reset();
						}
				}
		}
*/
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LEDIT_ConsoleEditor::HandleMouse(int* piKey, ASFC_LinkedList<int> lChoosers)
{	//If the user wants to exit
		if(myoInput.GetMouseButton(MOUSE_RIGHT))
		{	while(myoInput.GetMouseButton(MOUSE_RIGHT))
				myoInput.Update();
			*piKey = KEY_CANCEL;
			return -1;
		}

	//If the user is clicking
		if(myoInput.GetMouseButton(MOUSE_LEFT))
		{	//Pretend to draw
				//Vars
					int iOptionsCount = 0;
					int iFirstInfoToDraw= 0;
					int iLastInfoToDraw = 0;
					int iCharX, iCharY;

			//Get the position
				int iMouseX = myoInput.GetMouseX();
				int iMouseY = myoInput.GetMouseY();

			//Clear out any old info off the console
				mypoPainter->MainConsole().Clear();
	
			//If there are more pieces of info then will fit on the screen
				if(myoInfo.size() >= mypoPainter->MainConsole().ConsoleHeight())
				{	//Set it so the range of the first and last infos so that the cursor is in mid screen
						iFirstInfoToDraw = myiSelected - mypoPainter->MainConsole().ConsoleHeight()/2;
						iLastInfoToDraw  = myiSelected + mypoPainter->MainConsole().ConsoleHeight()/2;
				
					//Count the # of options from 0 to iFirstInfoToDraw
						if(iFirstInfoToDraw > 0)
						{	for(int i = 0; i < iFirstInfoToDraw; i++)
							{	if(myoInfo[i].iType == CONSOLE_EDIT_TYPE_OPTION)
			     					iOptionsCount++;
							}
						}
				}
			//If this info fits perfectly
				else
				{	//Set first to first and last to last
						iFirstInfoToDraw = 0;
						iLastInfoToDraw = myoInfo.size();
				}
		
			//Loop through all of the pieces of information we've got
				for(int i = iFirstInfoToDraw; i < iLastInfoToDraw; i++)
				{	//If this piece of info is "okay" to draw
						if(i >= 0 && i < myoInfo.size())
						{	//If this is a header
								if(myoInfo[i].iType == CONSOLE_EDIT_TYPE_HEADING)
								{	//Output this info in the header text
										mypoPainter->MainConsole().Writeln(myoInfo[i].s, FONT_HEADING);
								}
							//If this is an option
								else if(myoInfo[i].iType == CONSOLE_EDIT_TYPE_OPTION)
								{	//If this is the selected option
										if(iOptionsCount == myiSelected)
										{	//Draw this info in the selected text
												mypoPainter->MainConsole().Writeln(myoInfo[i].s, FONT_HIGHLIGHT);
											//If we're clicking on this line select it
												mypoPainter->MainConsole().CharacterAtPixel
												(	iMouseX, iMouseY, &iCharX, &iCharY
												);
												iCharY++;
												if(iCharY == mypoPainter->MainConsole().CursorY())
												{	myiSelected = iOptionsCount;
													Draw();
													
													//Wait for a mouse release
														while(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
															myoInput.Update();
													*piKey = lChoosers[0];
													return myiSelected;
												}
										}
									//If this is an unselected option
										else
										{	//Draw this info in the unselected text
												mypoPainter->MainConsole().Writeln(myoInfo[i].s, FONT_NORMAL);
											//If we're clicking on this line select it
												mypoPainter->MainConsole().CharacterAtPixel
												(	iMouseX, iMouseY, &iCharX, &iCharY
												);
												iCharY++;
												if(iCharY == mypoPainter->MainConsole().CursorY())
												{	myiSelected = iOptionsCount;
													Draw();
										
													//Wait for a mouse release
														while(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
															myoInput.Update();
										
													return -1;
												}
										}
									//Increment our count
										iOptionsCount++;
								}
						}
					//If this info is evil, evil!
						else
						{	mypoPainter->MainConsole().Writeln("", FONT_NORMAL);
						}
				}
		}

	return -1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LEDIT_ConsoleEditor::YesNo(bool f)
{	if(f)
		return "Yes";
	return "No";
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Returns the # of options
int LEDIT_ConsoleEditor::NumOptions()
{	//Return the # o' options
		return(myiNumOptions);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
int LEDIT_ConsoleEditor::GrabInt(string sText, int iMin, int iMax)
{	//Vars
		int ti = iMin -1;	//Set ti to an illegal value by default

	//Loop until we get a legal value
		while(ti < iMin || ti > iMax)
		{	mypoPainter->MainConsole().Clear();
			mypoPainter->MainConsole().Writeln(sText, FONT_NORMAL);
			mypoPainter->MainConsole().Write(">", FONT_HEADING);
			ti = mypoPainter->MainConsole().GrabInt(FONT_HIGHLIGHT);
		}
	
	//Return ti
		return(ti);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
int LEDIT_ConsoleEditor::GrabIntWithoutAClear(string sText, int iMin, int iMax)
{	//Vars
		int ti = iMin -1;	//Set ti to an illegal value by default

	//Loop until we get a legal value
		while(ti < iMin || ti > iMax)
		{	mypoPainter->MainConsole().Writeln(sText, FONT_NORMAL);
			mypoPainter->MainConsole().Write(">", FONT_HEADING);
			ti = mypoPainter->MainConsole().GrabInt(FONT_HIGHLIGHT);
		}
	
	//Return ti
		return(ti);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
string LEDIT_ConsoleEditor::GrabString(string sText)
{	mypoPainter->MainConsole().Clear();
	mypoPainter->MainConsole().Writeln(sText, FONT_NORMAL);
	mypoPainter->MainConsole().Write(">", FONT_HEADING);
	return(mypoPainter->MainConsole().GrabString(FONT_HIGHLIGHT));
}
//P------------------------------------------------------------------------------------------ [Drawing] -P
void LEDIT_ConsoleEditor::DrawInit()
{	//Just draw a big ol' black rectangle over the map area
		mypoScreen->DrawFillRectangle(PLAYFIELD_X, PLAYFIELD_Y, PLAYFIELD_X2 - PLAYFIELD_X,
 	 								  PLAYFIELD_Y2 - PLAYFIELD_Y, COLOR_BLACK, 255);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ConsoleEditor::Draw()
{	//Vars
		int iOptionsCount = 0;	//# of options outputted so far
		int iFirstInfoToDraw= 0;//The first piece of info that should be drawn on the screenn
		int iLastInfoToDraw = 0;//The last peice of info that should be drawn on the screen
		
	//If there are more pieces of info then will fit on the screen
		if(myoInfo.size() >= mypoPainter->MainConsole().ConsoleHeight())
		{	//Set it so the range of the first and last infos so that the cursor is in mid screen
				iFirstInfoToDraw = myiSelected - mypoPainter->MainConsole().ConsoleHeight()/2;
				iLastInfoToDraw  = myiSelected + mypoPainter->MainConsole().ConsoleHeight()/2;
				
			//Count the # of options from 0 to iFirstInfoToDraw
				if(iFirstInfoToDraw > 0)
				{	for(int i = 0; i < iFirstInfoToDraw; i++)
					{	if(myoInfo[i].iType == CONSOLE_EDIT_TYPE_OPTION)
	     					iOptionsCount++;
					}
				}
		}
	//If this info fits perfectly
		else
		{	//Set first to first and last to last
				iFirstInfoToDraw = 0;
				iLastInfoToDraw = myoInfo.size();
		}
		
	//Clear out any old info off the console
		mypoPainter->MainConsole().Clear();

	//Loop through all of the pieces of information we've got
		for(int i = iFirstInfoToDraw; i < iLastInfoToDraw; i++)
		{	//If this piece of info is "okay" to draw
				if(i >= 0 && i < myoInfo.size())
				{	//If this is a header
						if(myoInfo[i].iType == CONSOLE_EDIT_TYPE_HEADING)
						{	//Output this info in the header text
								mypoPainter->MainConsole().Writeln(myoInfo[i].s, FONT_HEADING);
						}
				
					//If this is an option
						else if(myoInfo[i].iType == CONSOLE_EDIT_TYPE_OPTION)
						{	//If this is the selected option
								if(iOptionsCount == myiSelected)
								{	//Draw this info in the selected text
										mypoPainter->MainConsole().Writeln(myoInfo[i].s, FONT_HIGHLIGHT);
								}
				
							//If this is an unselected option
								else
								{	//Draw this info in the unselected text
										mypoPainter->MainConsole().Writeln(myoInfo[i].s, FONT_NORMAL);
								}
								
							//Increment our count
								iOptionsCount++;
						}
				}
			//If this info is evil, evil!
				else
				{	mypoPainter->MainConsole().Writeln("", FONT_NORMAL);
				}
		}
		
	//Now actually "draw" this info
		mypoPainter->MainConsole().Draw(0xFF);
		mypoPainter->TalkConsole().Draw(0xFF);
		mypoScreen->Update();
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ConsoleEditor::DrawQuickKeys()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole() << "Up:     Move up\n";
	mypoPainter->TalkConsole() << "Down:   Move down\n";
	mypoPainter->TalkConsole() << "Enter:  Change Value\n";
	mypoPainter->TalkConsole() << "Escape: Exit\n";
}
