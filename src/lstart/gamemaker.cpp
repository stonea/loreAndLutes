/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			gamemaker.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Starter
   | ----` |	Last Updated:
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "gamemaker.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LSTART_Starter
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//----------------------------------------------------------------------------------------- [Constructor] -
LSTART_GameMaker::LSTART_GameMaker()
{	
}
//----------------------------------------------------------------------------------------------- [Maker] -
string LSTART_GameMaker::AskForGameDescription(ASFC_Console& oCon)
{	//Vars
		string sGameDescription;

	//Ask Away
		oCon.Clear();
		oCon << "================================================================================\n";
		oCon << "                      Creating a new Lore and Lutes Game\n";
		oCon << "================================================================================\n";
		sGameDescription = GrabString(oCon, "What is the full title of your game? (e.g. Lore and Lutes)");
		oCon << "\n\n";
		
	//Return it
		return(sGameDescription);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LSTART_GameMaker::AskForGameTitle(ASFC_Console& oCon, LSTART_GamesList& oList)
{	//Vars
		string sGameTitle;
		bool fValidFileName = false;

	//Ask Away until we get a valid name
		while(!fValidFileName)
		{	//Ask
				oCon << "Enter a file name for your game: (e.g. lore)\n";
				sGameTitle = GrabString(oCon, "What is the full title of your game? (e.g. Lore and Lutes)");
				sGameTitle = LowerString(sGameTitle);
				oCon.Draw(0xFF);
				
			//See if it's valid
				//Assume validity until proven false
					fValidFileName = true;
				//Check to make sure no other game has the same name
    				if(oList.IsGameWithName(sGameTitle)) fValidFileName = false;
				//Check to see if it has any bad characters
					for(int i = 0; i < sGameTitle.size() && fValidFileName; i++)
					{	if(	sGameTitle[i] == '!' || sGameTitle[i] == '@' || sGameTitle[i] == '#' || 
							sGameTitle[i] == '$' || sGameTitle[i] == '%' || sGameTitle[i] == '^' || 
							sGameTitle[i] == '&' || sGameTitle[i] == '*' || sGameTitle[i] == '(' || 
							sGameTitle[i] == ')' || sGameTitle[i] == '_' || sGameTitle[i] == '-' || 
							sGameTitle[i] == '+' || sGameTitle[i] == '=' || sGameTitle[i] == '[' || 
							sGameTitle[i] == ']' || sGameTitle[i] == '{' || sGameTitle[i] == '}' || 
							sGameTitle[i] == '\\'|| sGameTitle[i] == '|' || sGameTitle[i] == ';' || 
							sGameTitle[i] == ':' || sGameTitle[i] == '\''|| sGameTitle[i] == '\"'|| 
							sGameTitle[i] == ',' || sGameTitle[i] == '<' || sGameTitle[i] == '>' || 
							sGameTitle[i] == '.' || sGameTitle[i] == '/' || sGameTitle[i] == '?' || 
							sGameTitle[i] == '`' || sGameTitle[i] == '~')
						{	
      						fValidFileName = false;
      						oCon << "\nINVALID FILE NAME, Enter another:\n\n";
						}
					}
		}
	//Return it
		return(sGameTitle);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_GameMaker::MakeNewGame(string sDescription, string sGameName)
{	string sTitle   = sDescription;
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
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LSTART_GameMaker::GrabString(ASFC_Console& oCon, string sText)
{	oCon.Writeln(sText, 0);
	oCon.Write(">", 1);
	return(oCon.GrabString(0));
}
