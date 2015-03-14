/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			gameslist.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Starter
   | ----` |	Last Updated:
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "gameslist.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LSTART_GamesList
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//----------------------------------------------------------------------------------------- [Constructor] -
LSTART_GamesList::LSTART_GamesList()
{	myiSelectedGame = 0;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_GamesList::Setup(ASFC_Surface* poScreen, int iX, int iY, int iWidth, int iHeight)
{	myoConFont.Load("./data/gui/fonts/normal_console_font.png", 8, 14, COLOR_BLUE);
	myoFonts.Push(myoConFont);
	SetFontPalette(&myoFonts);
	SetSurface(poScreen);
	SetConsolePosition(iX, iY);
	SetViewport(0, 0);
	SetViewportSize(iWidth, iHeight);
	SetConsoleSize (iWidth, iHeight);
	PrepareList();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_GamesList::PrepareList()
{	//Get a list of all the games
		//Get a vector of all files in the games directory
			mylsGames.Resize(0);
			vector<LL_FileManager::LL_FileInfo> loFileInfo;
			vector<LL_FileManager::LL_FileInfo> loSubFileInfo;
			myoFileManager.EnumerateFiles("games", &loFileInfo);
		//Loop through removing all files that aren't directories
			for(int i = 0; i < loFileInfo.size(); i++)
				if(loFileInfo[i].iFileType != LL_FileManager::FILETYPE_DIR)
				{	loFileInfo.erase(loFileInfo.begin() + i);
					i--;
				}
		//Loop through all directories, delete if a .game file of the same name isn't found
			for(int i = 0; i < loFileInfo.size(); i++)
			{	string sSearch = "games/" + loFileInfo[i].sFileName;
   				myoFileManager.EnumerateFiles(sSearch, &loSubFileInfo);
				bool fGameFound = false;
				for(int j = 0; j < loSubFileInfo.size(); j++)
				{	string sCheck = loFileInfo[i].sFileName + ".game";
    				if(loSubFileInfo[j].sFileName == sCheck)
					{  	fGameFound = true;
					}
				}
				if(!fGameFound)
				{	loFileInfo.erase(loFileInfo.begin() + i);
					i--;
				}
				else
				{	mylsGames.Push(loFileInfo[i].sFileName);
				}
			}
}
//-------------------------------------------------------------------------------------------- [Listing] -
void LSTART_GamesList::DrawList()
{	//Vars
		int iStart;
		int iEnd;
		int iRealSelection;
		int iLoops;
	
	//Paint out all of the old stuff
		mypoSurface->DrawFillRectangle(myiConsoleX - 5, myiConsoleY - 5, myiWidth  * 8 + 8, myiHeight * 14 + 5, COLOR_BLACK, 0xFF);
	//Draw all the items
		Clear();
		//If the list can fit on one screen
			if(mylsGames.Length() < myiHeight)
			{	iStart = 0;
				iEnd = mylsGames.Length();
			}
		//If not center the selection
			else
			{	iStart = myiSelectedGame - myiHeight / 2;
				iEnd   = myiSelectedGame + myiHeight / 2;
			}
		//Draw it	
			iLoops = 0;
			for(int i = iStart; i < iEnd; i++)
			{	if(i == myiSelectedGame)
					iRealSelection = iLoops;
   				if(i >= 0 & i < mylsGames.Length())
	   			{	if(mylsGames[i].size() < myiWidth)
	       				Writeln(mylsGames[i], 0);
	       			else
	       			{	string sGame = mylsGames[i].substr(0, myiWidth - 3);
	       				sGame += "...";
	       				Writeln(sGame, 0);
	       			}
	   			}
	   			else
	   				Writeln("", 0);
	   			iLoops++;
			}
	//Draw it
		Draw(0xFF);
	//Draw the selection box
/*		mypoSurface->DrawFillRectangle(myiConsoleX, myiConsoleY + iRealSelection * 14, myiWidth * 8 - 1, 14 - 2,
  									   COLOR_WHITE, 0x33);
		mypoSurface->DrawRectangle(myiConsoleX, myiConsoleY + iRealSelection * 14 - 1, myiWidth * 8 + 1 , 14 + 2 - 2,
  								   COLOR_WHITE, 0xFF);
*/
		mypoSurface->DrawFillRectangle(myiConsoleX - 1, myiConsoleY + iRealSelection * 14, myiWidth * 8, 14 - 2,
  									   COLOR_WHITE, 0x33);
		mypoSurface->DrawRectangle(myiConsoleX - 1, myiConsoleY + iRealSelection * 14 - 1, myiWidth * 8 + 2 , 14 + 2 - 2,
  								   COLOR_WHITE, 0xFF);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_GamesList::SelectFirst()
{	myiSelectedGame = 0;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_GamesList::SelectPrev()
{	myiSelectedGame--;
	if(myiSelectedGame < 0)
 		myiSelectedGame = 0;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_GamesList::SelectNext()
{	myiSelectedGame++;
	if(myiSelectedGame >= mylsGames.Length())
		myiSelectedGame = mylsGames.Length() - 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LSTART_GamesList::Selection()
{	return(mylsGames[myiSelectedGame]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LSTART_GamesList::CurrentRow()
{	//Vars
		int iStart, iEnd, iRealSelection, iLoops;

	//If the list can fit on one screen
		if(mylsGames.Length() < myiHeight)
		{	iStart = 0;
			iEnd = mylsGames.Length();
		}
	//If not center the selection
		else
		{	iStart = myiSelectedGame - myiHeight / 2;
			iEnd   = myiSelectedGame + myiHeight / 2;
		}
	//Pretend to draw it
		iLoops = 0;
		for(int i = iStart; i < iEnd; i++)
		{	if(i == myiSelectedGame)
				iRealSelection = iLoops;
   			iLoops++;
		}
	//Return it
		return(iRealSelection);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_GamesList::AddGame(string sGameName)
{	mylsGames.Push(sGameName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LSTART_GamesList::IsGameWithName(string sGameName)
{	//Change the parameter to lower case letters
		sGameName = LowerString(sGameName);

	//Loop through all games checking to see if it has the same name
		for(int i = 0; i < mylsGames.Length(); i++)
		{	if(mylsGames[i] == sGameName)
				return true;
		}
	//If no game was found return false
		return false;
}
