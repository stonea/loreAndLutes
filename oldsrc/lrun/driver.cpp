/*Protected under the GNU General Public License read and see copying.txt for details

   `\    /,--.\ ,--.  ,,--     /\    ||     ,. ,. __||__ ,,--  ,---             |             // , .
   ||    ||  || |__'  ||__     \/    ||     || || --,.-- ||__  `__              |            //
   ||__. ||__|| |-\\  ||--    / \/   ||___  ||_||   ||   ||--     `         \   |   /       //    '  
   ----` \____/ || \\ ''__    \_/\   `----  `---'   ||   ''__  ___/           * * *        //       ,
   ----------------------------------------------------------------------=== *  +  * ===--//    `   \ 
                                                                              * * *      //          * 
Powered By: Annex Solutions' LOOP, TextEdit, and ASFC, plus PhysFS and SDL  /   |   \   //     *      \
Written and Designed By: Andy Stone                                             |      // *           '
Much Thanks To: Eoin Coffey, Sam Latinga, ...                                   |     // 
See credits.txt for full credit (where credit is due!)                               //`   |   `  .
Protected under the GNU General Public License (see license.txt)                    //    -*-
                                                                                   //      |         ,
==================================================================================`/.           . 
Source Last Updated: MM/DD/YY                                                     /      `         `
Version GRK VV.SS.RR                                                            / `
See updates.txt for a list of changes                                           /     .        /
Visit Lore And Lutes On the Web! Visit: http://loreandlutes.sourceforge.net    /               *     .
                                                                              /       `       /
For the best lookin' source code please set your tab size to be four spaces, /    .  
and if possible size your window to have 107 characters across the screen   /    .               . 
horizontally.                                                              /           .   `         `
-------------------------------------------------------------------------*/










































/* ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			driver.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
   Description:	This is the driver program for the L&L run module. When this module is being compiled
   				into a library all code within here SHOULD be commented out. Code can go into this
				module for testing purposes (if this module is being compiled as an executable).
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initilization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Debugging objects
	#include <asfc/screen.h>
	#include "lrunstart.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Main
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
SDL_Thread* thrdExit;				

int CheckExit(void* obj)
{	SDL_Event oEvent;
	while(true)
	{	SDL_PumpEvents();
		if(SDL_PeepEvents(&oEvent, 1, SDL_PEEKEVENT, SDL_EVENTMASK(SDL_QUIT)) > 0)
        {	switch (oEvent.type)
	   	    {	case SDL_QUIT:
				{	cerr << "EXIT!!!\n";
					SDL_KillThread(thrdExit);
					return 1;
				}break;
		 		
				default:
				break;
			}
		}
	}
}

//Point of execution, program starts here
int main(int argc, char *argv[])
{	//Init the screen
		ASFC_Screen screen(640, 480, 16);//, true);
	//And run!
		LRUN_LRunStart oStarter;
//		oStarter.StartRunner(&screen, "test");


/* Create a game directory = sGameName
*/

string sGameName = "test";
string sTitle   = "test game name";
string sGameDir = "./games/" + sGameName;
LL_FileManager oManager;

ofstream oFile;

//Make the base dirs
	oManager.MakeDir("./games", sGameName);
	oManager.MakeDir(sGameDir,  "battle");
	oManager.MakeDir(sGameDir,  "documentation");
	oManager.MakeDir(sGameDir,  "graphics");
	oManager.MakeDir(sGameDir,  "maps");
	oManager.MakeDir(sGameDir,  "music");
	oManager.MakeDir(sGameDir,  "sets"); 
	
//Create the game file
	//Open it up
		string sFileName = sGameDir + "/" + sGameName + ".game";
		oFile.open(sFileName.c_str());
	//"File type" %ver%
		oFile << ".game 0 ";
	//Game title, Game name
		oFile << Qoute(sTitle) << " " << Qoute(sGameName) << "\n";
	//"Default Mapset", "Default vehicle set", "Default terrain set"
		oFile << "\"/default.mapset\" ";
		oFile << "\"/default.vehicle\" ";
		oFile << "\"/default.terrain\" ";
		oFile << "\"/default.items\" ";
		oFile << "\"/default.monsters\" ";
		oFile << "\"/default.playerset\" ";
		oFile << "\"/default.vehicleobjset\" ";
	//%Start Map% %DeathMap% %Initial Player%
		oFile << 0 << " " << 0 << " " << 0 << " ";
	//%Chance of Heal% %Amount of Heal%	
		oFile << 10 << " " << 5;
	//Copy over the battle files
		oManager.DeArchive("battle.inf", sGameDir + "/battle");
	//Copy over the default (error) graphics
		oManager.DeArchive("graphics.inf", sGameDir + "/graphics");
	//Copy over the default maps
		oManager.DeArchive("maps.inf", sGameDir + "/maps");
	//Copy over the default sets
		oManager.DeArchive("sets.inf", sGameDir + "/sets");

/*
USE THIS CODE TO ARCHIVE A TEMPLATE GAME:
==========================================
*/
/*
	#define CS__ARCHIVE_NAME "maps.inf"
	#define CS__ARCHIVE_DIR  "games/test/maps"
	LL_FileManager oManager;
	vector<LL_FileManager::LL_FileInfo> myloFiles;
	ASFC_LinkedList<string> lsFileList;
	string sFile;
	
	oManager.EnumerateFiles(CS__ARCHIVE_DIR, &myloFiles);
	
	for(int i = 0; i < myloFiles.size(); i++)
	{	if(!myloFiles[i].iFileType == LL_FileManager::FILETYPE_DIR)
	 	{	sFile = CS__ARCHIVE_DIR;
   			sFile += '/';
      		sFile += myloFiles[i].sFileName;
   			cerr << "File " << i << ": " << sFile << "\n";
	 		lsFileList.Push(sFile);
	 	}
	}
	
	oManager.Archive(lsFileList, CS__ARCHIVE_NAME);
	return 1;
	*/
}
