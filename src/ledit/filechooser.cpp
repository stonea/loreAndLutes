/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			filechooser.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "filechooser.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_FileChooser
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_FileChooser::LEDIT_FileChooser()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LEDIT_FileChooser::~LEDIT_FileChooser()
{
}
//--------------------------------------------------------------------------------------- [File Choosing] -
string LEDIT_FileChooser::GrabFile(C_s2(sDirectory, sFileType))
{	//Set vars based on params
		mysDirectory = sDirectory;
    	mysFileType  = sFileType;
    	myiSelected  = 0;
    	myiDirsDown  = 0;
    	mysSubDirectory = "";
	//Grab a list of files
		EnumerateFiles();
	//Draw these files
		DrawFiles();
	//Reset the timer
		myoTimer.Reset();
	//If we have enough files
		if(myloFiles.size() > 0)
		{	//Handle Keys until we can handle no more!
				while(HandleKeys())
				{
				}
		}
	//If we don't have enough files return a "cancel" file
		else
			return("");

	//Return our selected directory (or nothing if we canceled)
		if(myiSelected != NO_SELECTION)
		{	//If the file  is in a sub dir
				if(myiDirsDown > 0)
				{	if(mysSubDirectory[0] == '/')
					{	mysSubDirectory.erase(mysSubDirectory.begin());
					}
					return(mysSubDirectory + "/" + myloFiles[myiSelected].sFileName);
				}
			//If we got a normal no sub dir file
			
				else
		  			return(myloFiles[myiSelected].sFileName);
		}
		else
			return("");
}
//P------------------------------------------------------------------------------------- [File Choosing] -P
//Handles keys in the GrabFile() list, return true if we should keep on lookin' for a file
bool LEDIT_FileChooser::HandleKeys()
{	//Vars
		bool fDone = false;
		bool fExitLoop = false;
		int  iKey  = -1;
		int  iLastKey = -2;

	//Loop until there's a choice or a cancel
		while(true)
		{	//Get a key
				iKey = -1;
				iLastKey = -2;
				while(iKey == -1)
				{	iKey = myoInput.GetKey(false, 350, 25);
					//- [Check mouse] -
						HandleMouse(&iKey);
				}

			fExitLoop = false;
			while(iKey != -1 && iKey != iLastKey && !fExitLoop)
			{	iLastKey = iKey;
				myoInput.Update();
 
	 			if(iKey == KEY_PREVFILE)
				{	//Move to the previous file (if possible)
						if(myiSelected > 0)
							myiSelected--;
					//Draw these files
						DrawFiles();
					//Not done yet
						return(true);
				}
			
				else if(iKey == KEY_NEXTFILE)
				{	//Move to the previous file (if possible)
						if(myiSelected < myloFiles.size()-1)
							myiSelected++;
					//Draw these files
						DrawFiles();
					//Not done yet
						return(true);
				}
				
				else if(iKey == KEY_PREVROW)
				{	//Move across left (if possible)
						if(myiSelected - NUMCOLS >= 0)
							myiSelected-= NUMCOLS;
					//Draw these files
						DrawFiles();
					//Not done yet
						return(true);
				}
				
				else if(iKey == KEY_NEXTROW)
				{	//Move to the previous file (if possible)
						if(myiSelected + NUMCOLS < myloFiles.size())
							myiSelected+= NUMCOLS;
					//Draw these files
						DrawFiles();
					//Not done yet
						return(true);
				}
				
				else if(iKey == KEY_PAGEUP)
				{	//Move to the previous file (if possible)
						if(myiSelected - (NUMCOLS * MAINCON_CHARHEIGHT) / 2 + 1 > 0)
							myiSelected -= (NUMCOLS * MAINCON_CHARHEIGHT) / 2 + 1;
						else
							myiSelected = 0;
							
					//Draw these files
						DrawFiles();
					//Not done yet
						return(true);
				}
				
				else if(iKey == KEY_PAGEDOWN)
				{	//Move to the previous file (if possible)
						if(myiSelected + (NUMCOLS * MAINCON_CHARHEIGHT) / 2 - 3 < myloFiles.size())
							myiSelected += (NUMCOLS * MAINCON_CHARHEIGHT) / 2 - 3;
						else
							myiSelected = myloFiles.size()-1;
							
					//Draw these files
						DrawFiles();
					//Not done yet
						return(true);
				}
			
				else if(iKey == KEY_CHOOSE || iKey == KEY_CHOOSE2)
				{	//If this is a file
						if(myloFiles[myiSelected].iFileType == LL_FileManager::FILETYPE_FILE)
						{	//We be done!
							return(false);
						}
	   				//If we got ourselves some fine lookin directory!
	    				if(myloFiles[myiSelected].iFileType == LL_FileManager::FILETYPE_DIR)
	    				{	//Update the current directory
	    						mysDirectory    += "/" + myloFiles[myiSelected].sFileName;
	    						mysSubDirectory += "/" + myloFiles[myiSelected].sFileName;
	    				
	    					//Re-enumerate what files we've got here
								myiSelected = 0;
	    						EnumerateFiles();
	    						
							//Add the "go back" directory
								LL_FileManager::LL_FileInfo toInfo;
	       						toInfo.iFileType = LL_FileManager::FILETYPE_GOBACKDIR;
	       						toInfo.sFileName = "..";
	       						myloFiles.push_back(toInfo);
	    						
	    					//Redraw
	    						DrawFiles();
							
							//Update our dirs down counter
								myiDirsDown++;
	    						
							//Sorry, but we've gotta keep on truckin' there pall-o
								return(true);
	    				}
					//If we got ourselves some supa' fine go back directory... ooohh.. yeah.
						if(myloFiles[myiSelected].iFileType == LL_FileManager::FILETYPE_GOBACKDIR)
						{	//Update the current directory
	    						mysDirectory 	= DirBack(mysDirectory);
	    						mysSubDirectory = DirBack(mysSubDirectory);
	    				
	    					//Re-enumerate what files we've got here
								myiSelected = 0;
	    						EnumerateFiles();
	    						
							//Update our dirs down counter
								myiDirsDown--;
	    						
							//If we can still go back
								if(myiDirsDown > 0)
								{	//Add the "go back" directory
										LL_FileManager::LL_FileInfo toInfo;
	       								toInfo.iFileType = LL_FileManager::FILETYPE_GOBACKDIR;
	       								toInfo.sFileName = "..";
	       								myloFiles.push_back(toInfo);
								}
	    						
	    					//Redraw
	    						DrawFiles();
	     
	      					//Sorry again, but we've gotta still keep on truckin' there me pall-o
								return(true);
						}
					//Reget a key
						iKey = myoInput.GetKey(false, 350, 25);
				}
				
				else if(iKey == KEY_CANCEL)
				{	//Change our selection to an invalid value (-1)
						myiSelected = NO_SELECTION;
						
					//We be done
						return(false);
				}	
			}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_FileChooser::HandleMouse(int* piKey)
{	//If the user is clicking
		if(myoInput.GetMouseButton(MOUSE_RIGHT))
		{	while(myoInput.GetMouseButton(MOUSE_RIGHT))
				myoInput.Update();
			*piKey = KEY_CANCEL;
			return;
		}

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
				mypoPainter->MainConsole().CharacterAtPixel(iMouseX, iMouseY, &iCharX, &iCharY);
			//If iCharY is > COL2_X then iCharY = 2, else iCharY = 1
				if(iCharX > COL2_X)
					iCharX = 2;
				else
					iCharX = 1;
						
			//Pretend to draw the files
			//Vars
				int iX = 0,
		  			iY = 0,
		  			iFile = 0,
		  			iLoops =0;
				string s, sFileName;
		
			//If there's more files then will fit on the screen and the cursor is past the halfway point
				if(myloFiles.size() >= 2*MAINCON_CHARHEIGHT)
				{	//If the selected file is in the first column (if it's even)
						if(myiSelected % 2 == 0)
						{	iFile = myiSelected - MAINCON_CHARHEIGHT-1;
						}
					//If the selected file is in the first column (if it's odd)
						else
							iFile = (myiSelected-1) - MAINCON_CHARHEIGHT-1;
				}
		
			//While we still have files to draw, note how I mask myloFiles.size() to a signed int, it returns unsigned!
				while(iFile < int(myloFiles.size()) && (iLoops < 2 * MAINCON_CHARHEIGHT))
				{	//If iFile is valid
						if(iFile >= 0)
						{	//Position the cursor
								if(iX == 0)
								{	mypoPainter->MainConsole().CursorX(COL1_X);
									mypoPainter->MainConsole().CursorY(iY);
								}
								else
								{	mypoPainter->MainConsole().CursorX(COL2_X);
									mypoPainter->MainConsole().CursorY(iY);
								}
							//If we got the correct position set it
								if(mypoPainter->MainConsole().CursorY() == iCharY)
								{	if
			      					(	mypoPainter->MainConsole().CursorX() == COL2_X && iCharX == 2 ||
		    							mypoPainter->MainConsole().CursorX() == COL1_X && iCharX == 1
		             				)
									{	//If this is the selected file we're done
											if(myiSelected == iFile)
												*piKey = KEY_CHOOSE;
									
							         	myiSelected = iFile;
					         			DrawFiles();
					         			
					         			//Wait for the mouse click to be done
						         			while(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
						         			{	myoInput.Update();
		         							}
										return;
									}
								}
						}
		
					//Update the file counter and the file position
						iFile++;
						iLoops++;
						iX++;
						
					//Make sure iY hasn't passed its limits
						if(iX > 1)
						{	iX = 0;
							iY++;
						}
				}//While

			//Now actually "draw" these
				mypoPainter->MainConsole().Draw(0xFF);
				mypoScreen->Update();
						
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_FileChooser::EnumerateFiles()
{	
	mypoFileManager->EnumerateFiles(mysDirectory, &myloFiles);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_FileChooser::DrawFiles()
{	//Vars
		int iX = 0,
  			iY = 0,
  			iFile = 0,
  			iLoops =0;
		string s, sFileName;

	//Clear out any old data
		mypoPainter->MainConsole().Clear();

	//If there's more files then will fit on the screen and the cursor is past the halfway point
		if(myloFiles.size() >= 2*MAINCON_CHARHEIGHT)
		{	//If the selected file is in the first column (if it's even)
				if(myiSelected % 2 == 0)
				{	iFile = myiSelected - MAINCON_CHARHEIGHT-1;
				}
			//If the selected file is in the first column (if it's odd)
				else
					iFile = (myiSelected-1) - MAINCON_CHARHEIGHT-1;
		}

	//While we still have files to draw, note how I mask myloFiles.size() to a signed int, it returns unsigned!
		while(iFile < int(myloFiles.size()) && (iLoops < 2 * MAINCON_CHARHEIGHT))
		{	//If iFile is valid
				if(iFile >= 0)
				{	//Position the cursor
						if(iX == 0)
						{	mypoPainter->MainConsole().CursorX(COL1_X);
							mypoPainter->MainConsole().CursorY(iY);
						}
						else
						{	mypoPainter->MainConsole().CursorX(COL2_X);
							mypoPainter->MainConsole().CursorY(iY);
						}
					
					//Get the file name
						sFileName = FileName(myloFiles[iFile].sFileName, COL2_X - 2);

					//If this file is a directory
						if(	myloFiles[iFile].iFileType == LL_FileManager::FILETYPE_DIR ||
      						myloFiles[iFile].iFileType == LL_FileManager::FILETYPE_GOBACKDIR)
						{	//If it's selected
								if(myiSelected == iFile)
								{	string s = ">" + sFileName + "<";
      								mypoPainter->MainConsole().Write(s, FONT_HIGHLIGHT);
								}
							//If it's not selected
								else
									mypoPainter->MainConsole().Write(sFileName, FONT_HEADING);
						}
					//If its just a file
						else
						{	//If it's selected
								if(myiSelected == iFile)
									mypoPainter->MainConsole().Write(sFileName, FONT_HIGHLIGHT);
							//If it's not selected
								else
	    							mypoPainter->MainConsole().Write(sFileName, FONT_NORMAL);
						}
						
				}//If valid file

			//Update the file counter and the file position
				iFile++;
				iLoops++;
				iX++;
				
			//Make sure iY hasn't passed its limits
				if(iX > 1)
				{	iX = 0;
					iY++;
				}
		}//While

	//Now actually "draw" these
		mypoPainter->MainConsole().Draw(0xFF);
		mypoScreen->Update();
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Makes sure sFile < iMaxChars, if its more then it shortens it and puts an ellipses (...) at the end
//iMaxChars must be > 3!!
string LEDIT_FileChooser::FileName(string sFile, C_i(iMaxChars))
{	//If the name is to long
		if(sFile.length() > iMaxChars)
		{	//Shorten it 3 less then the max chars and add an ellipses
  				sFile = sFile.substr(0, iMaxChars-3);
				sFile = sFile + "...";
		}
		
	//Return the return
		return(sFile);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Finds the previous directory in the path sDir
string LEDIT_FileChooser::DirBack(C_s(sDir))
{	//Vars
		int iSeperator = -1;
		
	//Loop for the # of chars in sDir
		for(int i = 0; i < sDir.length(); i++)
		{	//If this char is a seperator
				if(sDir[i] == '/')
				{	//Update our iSeperator value
						iSeperator = i;
				}
		}
		
	//If we didn't find any seperators return the original param
		if(iSeperator == -1)
			return(sDir);
			
	//Chop off that seperator and all after it
		return(sDir.substr(0, iSeperator));
}
