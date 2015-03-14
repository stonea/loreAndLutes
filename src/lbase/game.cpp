/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			game.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "game.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LL_Game
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//-------------------------------------------------------------------------------------- [Construction] -
LL_Game::LL_Game()
	:	myiCurrentMap(-2),
		myiStartMap(0),
		myiDeathMap(0),
		myiChanceOfHealInCamp(10),
  		myiAmountofHealInCamp(10)
{	//Configure sound
		//myoSound.Init();						//!!! SOUND OFF !!!!!!!!!!!!!!!!!!!
		myoSound.TurnSoundOff();
//		myoTerrainMap.SetSound(&myoSound);
//		myoBattleTerrainMap.SetSound(&myoSound);
	//Setup the data recorder
		myoDataRecorder.SetUnitSet(&myoUnitSet);
		myoDataRecorder.SetFileManager(&myoFileManager);
		myfDataRecorderOn = false;
	//Link the standard LOOP lib
		myoLOOPLibStandard.Link(&myoLOOP);
		myoClassSet.SetLOOP(&myoLOOP);
		myoBattleClassSet.SetLOOP(&myoLOOP);
		myoGlobalClassSet.SetLOOP(&myoLOOP);
	//Set up the CLList
		myoCLList.SetEventQueue(&myoEventQueue);
	//Link the terrain map and the mobility terrain map
		myoTerrainMap.SetMobilityTerrainMap(&myoMobilityTerrainMap);
		myoBattleTerrainMap.SetMobilityTerrainMap(&myoMobilityTerrainMap);
	//By default we're not in battle mode:
		myfInBattleMode = false;
}
//------------------------------------------------------------------------------------------ [File I/O] -
void LL_Game::SaveGame(string sGameName)
{	//Vars
		ofstream oFile;

	//Save the game information file
		oFile.open(myoDataRecorder.GameInfoFile().c_str());
		//%Current map%
			oFile << myiCurrentMap << " ";
		//<Save Clock Information>
			myoGameClock.SaveRecordingInfo(oFile);
		//<Save player recording info>
			myoPlayer.Save(oFile);
		//Save the flags
			oFile << mylsFlags.Length() << " ";
			for(int i = 0; i < mylsFlags.Length(); i++)
			{	oFile << Qoute(mylsFlags[i]) << " ";
				oFile << mylfFlags[i] << " ";
			}
		//We're done
			oFile.close();
	//Now save it all
		myoDataRecorder.SaveGame(sGameName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::RestoreGame(string sGameName)
{	//Vars
		ifstream oFile;
		int iMap;
		int iFlags;
	
	//Expand it all out
		myoDataRecorder.LoadGame(sGameName, GraphicsDir());
	//Load the game information file
		oFile.open(myoDataRecorder.GameInfoFile().c_str());
		//%Current map%
			oFile >> iMap;
		//<Load Clock Information>
			myoGameClock.LoadRecordingInfo(oFile, GraphicsDir());
			//Load the map
				myfDataRecorderOn = false;
				LoadMap(iMap);
				myfDataRecorderOn = true;
				LoadClasses("", mypoScreen);
		//Load the player info
			myoPlayer.Load(oFile, GraphicsDir());
		//Load the flags
			oFile >> iFlags;
			mylsFlags.Resize(iFlags);
			mylfFlags.Resize(iFlags);
			for(int i = 0; i < iFlags; i++)
			{	mylsFlags[i] = ReadString(oFile);
				oFile >> mylfFlags[i];
			}
		//We're done
			oFile.close();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::Load(string sFile, ASFC_Screen* poScreen, ASFC_FontPalette* poFontPalette)
{	//Load up the ol' Game file
		//Vars
			string 	sFileType;
			int		iVersion;
			ifstream oFile(sFile.c_str());
		//Set screen
  			mypoScreen = poScreen;
			mypoFontPalette = poFontPalette;
	//Remember the file name
		mysGlobalInfofile = sFile;
	//Setup the clock
		Clock().SetScreen(poScreen);
	//Check to make sure the file is open, if not quit out now
		if(!oFile.is_open())
		{	cerr << "ERR: File not found: " << sFile << endl;
			return false;
		}
		//Read in the header info
			oFile >> sFileType;
			oFile >> iVersion;
		//If this is a valid file continue onward
			//"Game Name\Description"
				mysGameName = ReadString(oFile);
			//"Game Dir"
				mysGameDir = ReadString(oFile);
				mysGameDir = "games/" + mysGameFile; // !!!
			//"Default Mapset", "Default vehicle set", "Default terrain set"
				sDefaultMapSet 		= ReadString(oFile);
				sDefaultVehicleSet	= ReadString(oFile);
				sDefaultTerrainSet	= ReadString(oFile);
				sDefaultItemSet		= ReadString(oFile);
				sDefaultMonsterSet	= ReadString(oFile);
				sDefaultPlayerSet	= ReadString(oFile);
				sDefaultVehicleObjectsSet = ReadString(oFile);
			//%Start Map% %DeathMap% %Initial Player%
				oFile >> myiStartMap >> myiDeathMap >> myiInitialPlayer;
			//%Chance of Heal% %Amount of Heal%
				oFile >> myiChanceOfHealInCamp >> myiAmountofHealInCamp;
	//Setup the directories
		mysDocumentationDir	= mysGameDir + LL_Game__SUB_DOCUMENTATION;
		mysGraphicsDir		= mysGameDir + LL_Game__SUB_GRAPHICS;
		mysMapsDir			= mysGameDir + LL_Game__SUB_MAPS;
		mysMusicDir			= mysGameDir + LL_Game__SUB_MUSIC;
		mysRootDir			= mysGameDir + LL_Game__SUB_ROOT;
		mysSaveDir			= mysGameDir + LL_Game__SUB_SAVE;
		mysSetsDir			= mysGameDir + LL_Game__SUB_SETS;
	//Load the map set
		if(!LoadMapSet(mysSetsDir + sDefaultMapSet)) return false;
	//Load the vehicle set
		if(!LoadVehicleSet(mysSetsDir + sDefaultVehicleSet)) return false;
	//Load the terrain set
		if(!LoadTerrainSet(mysSetsDir + sDefaultTerrainSet)) return false;
	//Load the item set
		if(!LoadItemSet(mysSetsDir + sDefaultItemSet)) return false;
	//Load the monster set
		if(!LoadMonsterSet(mysSetsDir + sDefaultMonsterSet)) return false;
	//Load the player set
		if(!LoadPlayerSet(mysSetsDir + sDefaultPlayerSet)) return false;
	//Load the vehicle objects set
		if(!LoadVehicleObjectsSet(mysSetsDir + sDefaultVehicleObjectsSet)) return false;
	//And the battle information
  		if(!LoadBattleMap()) return false;
	//Set up the mobilityterrain set map
		myoMobilityTerrainMap.Resize(TerrainSet().NumTerrains(), VehicleSet().NumVehicles());
	//Load the terrain map (for map zero)
		myiCurrentMap = 0;
		if(!LoadTerrainMap(MapSet().Map(0))) return false;
	//Load the unit map (for map zero)
		myoUnitMap.Clear();
		myoBattleUnitMap.Clear();
	//Set up the unit set
		myoUnitSet.Clear(); // /ADD\ !!!!
		myoUnitSet.SetUnitMap(&myoUnitMap);
		myoUnitSet.SetVehicleObjectSet(&myoVehicleObjectSet);
		myoUnitSet.SetTerrainMap(&myoTerrainMap);
		myoUnitSet.SetEventQueue(&myoEventQueue);
		myoUnitSet.SetGameClock(&myoGameClock);
		myoUnitSet.SetCLList(&myoCLList);
		myoUnitSet.SetPathNodes(&myoPathNodes);
		myoUnitSet.SetLOOP(&myoLOOP);
		myoUnitSet.SetItemSet(&myoItemSet);
		myoUnitSet.SetMonsterSet(&myoMonsterSet);
		myoUnitSet.SetScreen(mypoScreen);
		myoUnitSet.SetFontPalette(mypoFontPalette);
	//Set up the battle unit set
		myoBattleUnitSet.Clear(); // /ADD\ !!!!
		myoBattleUnitSet.SetVehicleObjectSet(&myoVehicleObjectSet);
		myoBattleUnitSet.SetUnitMap(&myoBattleUnitMap);
		myoBattleUnitSet.SetBattleUnitMap(&myoBattleUnitMap);
		myoBattleUnitSet.SetTerrainMap(&myoBattleTerrainMap);
		myoBattleUnitSet.SetEventQueue(&myoEventQueue);
		myoBattleUnitSet.SetGameClock(&myoGameClock);
		myoBattleUnitSet.SetCLList(&myoCLList);
		myoBattleUnitSet.SetPathNodes(&myoBattlePathNodes);
		myoBattleUnitSet.SetLOOP(&myoLOOP);
		myoBattleUnitSet.SetItemSet(&myoItemSet);
		myoBattleUnitSet.SetMonsterSet(&myoMonsterSet);
		myoBattleUnitSet.SetScreen(mypoScreen);
		myoBattleUnitSet.SetFontPalette(mypoFontPalette);
	//Setup the path nodes
		myoPathNodes.SetUnitMap(&myoUnitMap);
	//Setup the player
		myoPlayer.Inventory().Init(&myoItemSet);
		myoPlayer.SetClock(&Clock());
		myoPlayer.SetEventQueue(&myoEventQueue);
		myoPlayer.LoadAnimation("/creatures/player_n.png", GraphicsDir(), TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);	//!!!
		myoPlayer.SetTerrainMap(&myoTerrainMap);
		myoPlayer.SetUnitMap(&myoUnitMap);
		myoPlayer.SetVehicle(myoVehicleSet.Vehicle(0));
		myoPlayer.SetSeg(LL_UnitMap::SEG_PLAYER);
		myoPlayer.SetOff(LL_UnitMap::OFF_PLAYER);
		myoPlayer.SetLayer(3);	//!!!
		myoPlayer.SetItemSet(&myoItemSet);
		myoUnitSet.SetPlayer(&myoPlayer);
		myoPlayer.Place(TerrainMap().PlayerX(), TerrainMap().PlayerY());
		myoBattleUnitSet.SetPlayer(&myoPlayer);
//		myoPlayer.Place(TerrainMap().PlayerX(), TerrainMap().PlayerY());
	//Everything loaded properly so return true
		
		return(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveGlobalInfo()
{	//Vars
		ofstream oFile(mysGlobalInfofile.c_str());
	
	//".game" 0
		oFile << ".game 0";
	//"Game Name\Description"
		oFile << Qoute(mysGameName);
	//"Game Dir"
		oFile << Qoute(mysGameDir);
	//"Default Mapset", "Default vehicle set", "Default terrain set"
		oFile << Qoute(sDefaultMapSet) << " ";
		oFile << Qoute(sDefaultVehicleSet) << " ";
		oFile << Qoute(sDefaultTerrainSet) << " ";
		oFile << Qoute(sDefaultItemSet) << " ";
		oFile << Qoute(sDefaultMonsterSet) << " ";
		oFile << Qoute(sDefaultPlayerSet) << " ";
		oFile << Qoute(sDefaultVehicleObjectsSet) << " ";
	//%Start Map% %DeathMap% %Initial Player%
		oFile << myiStartMap << " " << myiDeathMap << " " << myiInitialPlayer << endl;
	//%Chance of Heal% %Amount of Heal%
		oFile << myiChanceOfHealInCamp << " " << myiAmountofHealInCamp << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadClasses(string sFile, ASFC_Screen* poScreen)
{	//If this is for battle mode
		if(myfInBattleMode)
		{	//Clear out old classes
				myoLOOP.ClearClasses();
			//Clear out all units except for the player
				myoUnitSet.Clear();
				myoBattleUnitSet.Clear();
			//Load global classes
			    myoLOOP.ReadClass(GlobalScriptFileName(), 0);
				myoLOOP.NewInstance(LL_Game__GLOBAL_CLASS_IDENTIFIER, LL_Game__GLOBAL_IDENTIFIER, SCOPE_GLOBAL);
				myoUnitSet.SetGlobalScript(&myoGlobalScript);
				myoUnitSet.SetupGlobalScript(GraphicsDir());
				myoBattleUnitSet.SetGlobalScript(&myoGlobalScript);
				LoadGlobalClassSet();

//myfInBattleMode = false;
//if(!LoadClassSet("./" + ClassSetFileName()))  return false;
//if(!LoadUnitSet("./" + UnitSetFileName()))  return false;
//myfInBattleMode = true;
				
				if(!LoadUnitSet("./" + UnitSetFileName())) return false;
				//myoBattleUnitSet.SetupGlobalScript(GraphicsDir());
				return true;
		}
	//Clear out all old classes
//		myoLOOP.ClearClasses();
	//Clear out all units except for the player
//		myoUnitSet.Clear();
	//Load the global class set
//		if(!LoadGlobalClassSet()) return false;
	//Load up the class set (first link libs)
		if(!LoadClassSet("./" + ClassSetFileName()))  return false;
	//Load the unit set (for map zero)
	//Load & Setup the map objects set
		//myoMapObjectsSet.Setup(&myoUnitMap, &myoUnitSet, &myoTerrainMap, &myoPathNodes, &myoLOOP, &myoGameClock); !!!!
		//if(!LoadMapObjectsSet("./" + MapObjectsFileName()))  return false;
	//Load recording data
		if(myfDataRecorderOn && FileExist(myoDataRecorder.File(myiCurrentMap)))
		{	myoDataRecorder.LoadInformation(myiCurrentMap, GraphicsDir());
		}
		else
		{	if(!LoadUnitSet("./" + UnitSetFileName()))  { return false; }
		}
	//Add a global script to the unit set
		//myoUnitSet.SetupGlobalScript(GraphicsDir());
		//myoBattleUnitSet.SetupGlobalScript(GraphicsDir());
	//Create an instance
//		myoLOOP.ReadClass(GlobalScriptFileName(), 0);
//		myoLOOP.NewInstance(LL_Game__GLOBAL_CLASS_IDENTIFIER, LL_Game__GLOBAL_IDENTIFIER, SCOPE_GLOBAL);
	//It worked no probs
		return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::ReloadBattleInfo()
{	//Clear out all units except for the player
		myoBattleUnitSet.Clear();
		myoBattleUnitMap.Clear();
	//Load global classes
		myoUnitSet.SetGlobalScript(&myoGlobalScript);
		myoUnitSet.SetupGlobalScript(GraphicsDir());
		if(!LoadUnitSet("./" + UnitSetFileName())) return false;
	return true;
}
//---------------------------------------------------------------------------------- [Map/Set Handeling] -
bool LL_Game::LoadVehicleSet(C_s(sFile))
{	ifstream fileSet;
	fileSet.open(sFile.c_str(), ios::binary);
	if(fileSet.is_open())
	{	myoVehicleSet.Load(fileSet);
		mysVehicleSet = sFile;
		return true;
	}
	cerr << "ERR: File not found: " << sFile << endl;
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveVehicleSet(C_s(sFile))
{	ofstream fileSet;
	fileSet.open(sFile.c_str(), ios::binary);
	myoVehicleSet.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadTerrainSet(C_s(sFile))
{	ifstream fileSet;
	fileSet.open(sFile.c_str(), ios::binary);
	if(fileSet.is_open())
	{	if(!myoTerrainSet.Load(fileSet, GraphicsDir())) return false;
		myoMobilityTerrainMap.Load(fileSet);
		mysTerrainSet = sFile;
		return true;
	}
	cerr << "ERR: File not found: " << sFile << endl;
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveTerrainSet(C_s(sFile))
{	ofstream fileSet;
	fileSet.open(sFile.c_str(), ios::binary);
	myoTerrainSet.Save(fileSet);
	myoMobilityTerrainMap.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadMapSet(C_s(sFile))
{	ifstream fileSet;
	fileSet.open(sFile.c_str(), ios::binary);
	if(fileSet.is_open())
	{	myoMapSet.Load(fileSet);
		mysMapSet = sFile;
		return true;
	}
	cerr << "ERR: File not found: " << sFile << endl;
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveMapSet(C_s(sFile))
{	ofstream fileSet;
	fileSet.open(sFile.c_str(), ios::binary);
	myoMapSet.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Loads map sFile (from the maps directory)
bool LL_Game::LoadTerrainMap(string sFile)
{	//Set the file rememberer
		mysTerrainMap = sFile;
	//Files
		ifstream fileMap;
		sFile = mysMapsDir + "/" + sFile;
  		fileMap.open(sFile.c_str(), ios::binary);
	//Check to make sure the file opened correctly
		if(fileMap.is_open())
		{	if(!myfInBattleMode)
			{	//Load the paths
					myoPathNodes.Load(fileMap);
				//Load the terrains and the map
					myoTerrainMap.Load(fileMap, MusicDir());
					myoTerrainMap.SetTerrainSet(&myoTerrainSet);
				//Set the ticks per minute
					myoGameClock.SetTicksPerMinute(myoTerrainMap.TicksPerMinute());
 			}
 			else
 			{	//Load the paths
					myoBattlePathNodes.Load(fileMap);
				//Load the terrains and the map
					myoBattleTerrainMap.Load(fileMap, MusicDir());
					myoBattleTerrainMap.SetTerrainSet(&myoTerrainSet);
				//Set the ticks per minute
					myoBattleTerrainMap.SetTicksPerMinute(myoTerrainMap.TicksPerMinute());
 			}

			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Saves map sFile
void LL_Game::SaveTerrainMap(string sFile)
{	//Set the file rememberer
		mysTerrainMap = sFile;
	//Files
		ofstream fileMap;
		sFile = mysMapsDir + "/" + sFile;
  		fileMap.open(sFile.c_str(), ios::binary);
	//Save the non battle if we're not in battle else the battle
		if(!myfInBattleMode)
		{	//Save the paths
				myoPathNodes.Save(fileMap);
			//Save the terrain map
				myoTerrainMap.Save(fileMap);
		}
		else
		{	//Save the paths
				myoBattlePathNodes.Save(fileMap);
			//Save the terrain map
				myoBattleTerrainMap.Save(fileMap);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Loads map sFile (from the maps directory)
bool LL_Game::LoadBattleMap()
{	//Files
		ifstream fileMap;
		string sFile = mysMapsDir + "/" + cGame__BATTLE_MAP;
  		fileMap.open(sFile.c_str(), ios::binary);
	//Check to make sure the file opened correctly
		if(fileMap.is_open())
		{	//Load the battls and the map
				myoBattleMap.Load(fileMap);
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Saves map sFile
void LL_Game::SaveBattleMap()
{	//Files
		ofstream fileMap;
		string sFile = mysMapsDir + "/" + cGame__BATTLE_MAP;
  		fileMap.open(sFile.c_str(), ios::binary);
	//Save the battle map
		myoBattleMap.Save(fileMap);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadMap(C_i(iMap))
{	//Vars
		bool fSuccess;
  	//Save the exit position
   		myoTerrainMap.SetExitX(myoPlayer.X());
   		myoTerrainMap.SetExitY(myoPlayer.Y());
	//If the old map is legal record data
		if(iMap >= 0 && myfDataRecorderOn)
		{	myoDataRecorder.RecordInformation(myiCurrentMap);
		}
	//Set the map
		myiCurrentMap = iMap;
	//Clear out old map info
		if(!myfInBattleMode)
		{	myoUnitMap.Clear();
//			myoUnitSet.Clear(); !!!
		}
		else
		{	myoBattleUnitMap.Clear();
///			myoBattleUnitSet.Clear(); !!!
		}
	//Load the map
		fSuccess = LoadTerrainMap(MapSet().Map(iMap));
	//If we succeeded
		if(fSuccess)
		{	//If we're loading a normal map
				if(iMap >= 0)
				{	//Load the unit map (for map zero)
						myoUnitMap.Clear();
					//Place the player
						Player().Place(TerrainMap().PlayerX(), TerrainMap().PlayerY());
					//We're done
						return true;
  				}
  			//If we're loading a battle map
				else
				{	//Load the unit map (for map zero)
						myoBattleUnitMap.Clear();
  					//Success
  						return true;
				}
		}
		cerr << "ERR: Unable to load map: " << iMap << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadClassSet(string sFile)
{	//Set the file rememberer
		mysClassSet = sFile;
	//Files
		ifstream fileSet;
  		fileSet.open(sFile.c_str());
	//Check to make sure the file loaded properly
		if(fileSet.is_open())
		{	//If we're not doing it battle map style
				if(!myfInBattleMode)
				{	//Load the terrains and the map
						myoClassSet.Load(fileSet, ClassFileName());		//Here dost lie the line of pure evil as proclaimed by the great bug of Feb '03.
  				}
  			//If we are
  				else
  				{	//Load the terrains and the map
						myoBattleClassSet.Load(fileSet, ClassFileName());
  				}
			//Close file
				fileSet.close();
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveClassSet(string sFile, LL_ClassSet* poClassSet)
{	//Set the file rememberer		
		mysClassSet = sFile;
	//Files
		ofstream fileSave;
  		fileSave.open(sFile.c_str());
	//Load the terrains and the map
		poClassSet->Save(fileSave);
	//Close file
		fileSave.close();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadGlobalClassSet()
{	//Files
		string sFile = GlobalClassSetFileName();
		ifstream fileSet;
  		fileSet.open(sFile.c_str());
	//Check to make sure the file loaded properly
		if(fileSet.is_open())
		{	//Load the terrains and the map
				myoGlobalClassSet.Clear();
				myoGlobalClassSet.Load(fileSet, GlobalClassFileName());
			//Close file
				fileSet.close();
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveGlobalClassSet()
{	//Files
		string sFile = GlobalClassSetFileName();
		ofstream fileSave;
  		fileSave.open(sFile.c_str());
	//Load the terrains and the map
		myoGlobalClassSet.Save(fileSave);
	//Close file
		fileSave.close();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadUnitSet(string sFile)
{	//Set the file rememberer
		mysUnitSet = sFile;
	//Files
		ifstream fileSet;
  		fileSet.open(sFile.c_str());
	//Check to make sure the file loaded properly
		if(fileSet.is_open())
		{	//If we're not loading the batttle map
				if(!myfInBattleMode)
				{	//Load it
						myoUnitSet.Load(fileSet, GraphicsDir());
  				}
  				else
  				{	//Load it
						myoBattleUnitSet.Load(fileSet, GraphicsDir());
				}
			//Close file
				fileSet.close();
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveUnitSet(string sFile)
{	//Set the file rememberer
		mysUnitSet = sFile;
	//Files
		ofstream fileSet;
  		fileSet.open(sFile.c_str());
	//Save the terrains and the map (normal if norm, battle if battle)
		if(!myfInBattleMode)
			myoUnitSet.Save(fileSet);
		else
			myoBattleUnitSet.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadItemSet(string sFile)
{	//Set the file rememberer
		mysItemSet = sFile;
	//Files
		ifstream fileSet;
  		fileSet.open(sFile.c_str());
	//Check to make sure the file loaded properly
		if(fileSet.is_open())
		{	//Load the terrains and the map
				myoItemSet.Load(fileSet, GraphicsDir());
			//Close file
				fileSet.close();
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveItemSet(string sFile)
{	//Set the file rememberer
		mysItemSet = sFile;
	//Files
		ofstream fileSet;
  		fileSet.open(sFile.c_str());
	//Save the terrains and the map
		myoItemSet.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadMonsterSet(string sFile)
{	//Set the file rememberer
		mysMonsterSet = sFile;
	//Files
		ifstream fileSet;
  		fileSet.open(sFile.c_str());
	//Check to make sure the file loaded properly
		if(fileSet.is_open())
		{	//Load the terrains and the map
				myoMonsterSet.Load(fileSet, GraphicsDir());
			//Close file
				fileSet.close();
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveMonsterSet(string sFile)
{	//Set the file rememberer
		mysMonsterSet = sFile;
	//Files
		ofstream fileSet;
  		fileSet.open(sFile.c_str());
	//Save the terrains and the map
		myoMonsterSet.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadPlayerSet(string sFile)
{	//Set the file rememberer
		mysPlayerSet = sFile;
	//Files
		ifstream fileSet;
	  		fileSet.open(sFile.c_str());
	//Check to make sure the file loaded properly
		if(fileSet.is_open())
		{	//Load the terrains and the map
				myoPlayerSet.Load(fileSet, GraphicsDir());
			//Close file
				fileSet.close();
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SavePlayerSet(string sFile)
{	//Set the file rememberer
		mysPlayerSet = sFile;
	//Files
		ofstream fileSet;
  		fileSet.open(sFile.c_str());
	//Save the terrains and the map
		myoPlayerSet.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::LoadVehicleObjectsSet(string sFile)
{	//Set the file rememberer
		mysVehicleObjectsSet = sFile;
	//Files
		ifstream fileSet;
  		fileSet.open(sFile.c_str());
	//Check to make sure the file loaded properly
		if(fileSet.is_open())
		{	//Load the terrains and the map
				myoVehicleObjectSet.Load(fileSet, GraphicsDir());
			//Close file
				fileSet.close();
			return true;
		}
		cerr << "ERR: File not found: " << sFile << endl;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SaveVehicleObjectsSet(string sFile)
{	//Set the file rememberer
		mysVehicleObjectsSet = sFile;
	//Files
		ofstream fileSet;
  		fileSet.open(sFile.c_str());
	//Save the terrains and the map
		myoVehicleObjectSet.Save(fileSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::NewMap(C_i(iMap))
{	//Load the default map
		//Set the file rememberer		
			mysTerrainMap = cGame__DEFAULT_MAP;
		//Files
			ifstream fileMap;
  			fileMap.open(cGame__DEFAULT_MAP, ios::binary);
		//Check to make sure the file opened correctly
			if(fileMap.is_open())
			{	//Load the paths
					myoPathNodes.Load(fileMap);
				//Load the terrains and the map
					myoTerrainMap.Load(fileMap, MusicDir());
					myoTerrainMap.SetTerrainSet(&myoTerrainSet);
			}
			else
				cerr << "ERR: Can not find default map file. Reinstall L&L: " << endl;
		//Clear out all old classes
			myoLOOP.ClearClasses();
			myoClassSet.Clear();
		//Clear out all units except for the player
			myoUnitSet.Clear();

	//Place the player
		Player().Place(TerrainMap().PlayerX(), TerrainMap().PlayerY());
	//Now set the current map #
		myiCurrentMap = iMap;
	//Set the file rememberer to what this map says its file is
		mysTerrainMap = MapSet().Map(iMap);
	//Save this new map
		SaveTerrainMap(mysTerrainMap);
	//And the classets
		SaveClassSet(ClassSetFileName(), &ClassSet());
	//And the map units set
		SaveUnitSet(UnitSetFileName());
}
//------------------------------------------------------------------------------ [Directories and files] -
//MEMVAR_GETREF(GameDir,			string, mysGameDir);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GETREF(DocumentationDir, 	string, mysDocumentationDir);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GETREF(GraphicsDir,		string, mysGraphicsDir); 
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GETREF(MapsDir,			string,	mysMapsDir);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GETREF(MusicDir, 			string, mysMusicDir);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GETREF(RootDir, 			string, mysRootDir);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GETREF(SaveDir, 			string, mysSaveDir);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GETREF(SetsDir, 			string, mysSetsDir);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Game::ClassSetFileName()
{	//ClasssSetFileName = MapsDir + "/" + + (mysTerrainMap - mysTerrainMap extension) + .classset
	//Vars
		string sMapNoExtnsn;
		int	   iExtnsnPos;
		
	//Grab mysTerrainMap - mysTerrainMap extension
		iExtnsnPos	 = mysTerrainMap.find(".map");
		sMapNoExtnsn = mysTerrainMap.substr(0, iExtnsnPos);
		
	//Now return MapDir + "/" + sMapNoExtsn + .classet
		return(mysMapsDir + '/' + sMapNoExtnsn + ".classset");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Game::ClassFileName()
{	//ClasssFileName = MapsDir + "/" + + (mysTerrainMap - mysTerrainMap extension) + .class
	//Vars
		string sMapNoExtnsn;
		int	   iExtnsnPos;
		
	//Grab mysTerrainMap - mysTerrainMap extension
		iExtnsnPos	 = mysTerrainMap.find(".map");
		sMapNoExtnsn = mysTerrainMap.substr(0, iExtnsnPos);
		
	//Now return MapDir + "/" + sMapNoExtsn + .class
		return(mysMapsDir + '/' + sMapNoExtnsn + ".class");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Game::GlobalClassSetFileName()
{	return("./" + MapsDir() + "/" + cGame__GLOBAL_CLASSSET);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Game::GlobalClassFileName()
{	return("./" + MapsDir() + "/" + cGame__GLOBAL_CLASS);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Game::GlobalScriptFileName()
{	return("./" + MapsDir() + "/" + cGame__GLOBAL_SCRIPT);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Game::UnitSetFileName()
{	//ClasssFileName = MapsDir + "/" + + (mysTerrainMap - mysTerrainMap extension) + .obj
	//Vars
		string sMapNoExtnsn;
		int	   iExtnsnPos;
	//If we're not in battle mode
		if(!myfInBattleMode)
		{	//Grab mysTerrainMap - mysTerrainMap extension
				iExtnsnPos	 = mysTerrainMap.find(".map");
				sMapNoExtnsn = mysTerrainMap.substr(0, iExtnsnPos);
			//Now return MapDir + "/" + sMapNoExtsn + .class
				return(mysMapsDir + '/' + sMapNoExtnsn + ".obj");
		}
	//If we are
		else
			return(mysMapsDir + '/' + "battle" + ".obj");
}
//---------------------------------------------------------------------------------- [Object Accessing] -
LL_PathNodes& LL_Game::PathNodes()
{	if(myfInBattleMode)
		return(myoBattlePathNodes);
	return(myoPathNodes);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_TerrainMap& LL_Game::TerrainMap()
{ 	if(myfInBattleMode)
		return(myoBattleTerrainMap);
	return(myoTerrainMap);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_ClassSet& LL_Game::ClassSet()
{	if(myfInBattleMode)
		return(myoBattleClassSet);
	return(myoClassSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_UnitMap& LL_Game::UnitMap()
{	if(myfInBattleMode)
		return(myoBattleUnitMap);
	return(myoUnitMap);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_UnitSet& LL_Game::UnitSet()
{	if(myfInBattleMode)
		return(myoBattleUnitSet);
	return(myoUnitSet);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//LL_ScriptedUnit& LL_Game::GlobalScript()
//{	return(myoUnitSet.GlobalScript());
//}
//--------------------------------------------------------------------------------------------- [Flags] -
int LL_Game::FlagPosition(string sFlagName)
{	//Capatilize the flag name
		sFlagName = UpperString(sFlagName);
	//Loop through all flags
		for(int i = 0; i < mylsFlags.Length(); i++)
		{	if(mylsFlags[i] == sFlagName)
				return i;
		}
	//Return negative if no flag was found
		return -1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::FlagExists(string sFlagName)
{	if(FlagPosition(sFlagName) < 0)
		return false;
	return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SetFlagOn(string sFlagName)
{	int iPos = FlagPosition(sFlagName);
	if(iPos >= 0)
		mylfFlags[iPos] = true;
	else
	{	mylsFlags.Resize(mylsFlags.Length() + 1);
		mylfFlags.Resize(mylsFlags.Length() + 1);
		int iPos = mylsFlags.Length() - 1;
 		mylsFlags[iPos] = UpperString(sFlagName);
   		mylfFlags[iPos] = true;
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SetFlagOff(string sFlagName)
{	int iPos = FlagPosition(sFlagName);
	if(iPos >= 0)
		mylfFlags[iPos] = false;
	else
	{	mylsFlags.Resize(mylsFlags.Length() + 1);
		mylfFlags.Resize(mylsFlags.Length() + 1);
		int iPos = mylsFlags.Length() - 1;
 		mylsFlags[iPos] = UpperString(sFlagName);
   		mylfFlags[iPos] = false;
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Game::SwitchFlag(string sFlagName)
{	int iPos = FlagPosition(sFlagName);
	if(iPos >= 0)
		mylfFlags[iPos] = !mylfFlags[iPos];
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Game::IsFlagOn(string sFlagName)
{	int iPos = FlagPosition(sFlagName);
	if(iPos >= 0)
		return(mylfFlags[iPos]);
	return false;
}
