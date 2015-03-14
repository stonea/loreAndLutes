/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			game.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: Contains all of the game objects (maps, sets, all of those goodies.)
*/
#ifndef LL_GAME_H_
#define LL_GAME_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include "terrainmap.h"
	#include "unitmap.h"
	#include "classset.h"
	#include "mapset.h"
	#include "unitset.h"
	#include "itemset.h"
	#include "monsterset.h"
	#include "playerset.h"
	#include "terrainset.h"
	#include "player.h"
	#include "vehicleset.h"
	#include "pathnodes.h"
	#include "mobilityterrainmap.h"
	#include "gameclock.h"
	#include "eventqueue.h"
	#include "battlemap.h"
	#include "battleunitmap.h"
	#include "battleunitset.h"
	#include "vehicleobjectset.h"
	#include <loop/loop.h>
	#include <loop/looplib_standard.h>
	#include "filemanager.h"
	#include "datarecorder.h"
	#include "cllist.h"
//Dependencies
	#include <asfc/screen.h>
	#include <asfc/fontpalette.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												 Prototype
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Game
{	public:
	//- [Construction] -
		LL_Game();
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, mypoScreen);
		MEMVAR_SETGET(SetFontPalette, FontPalette, ASFC_FontPalette*, mypoFontPalette);
	//- [Map/Set Handeling] -
		bool LoadVehicleSet(C_s(sFile));
		void SaveVehicleSet(C_s(sFile));
		bool LoadTerrainSet(C_s(sFile));
		void SaveTerrainSet(C_s(sFile));
		bool LoadMapSet(C_s(sFile));
		void SaveMapSet(C_s(sFile));
		bool LoadTerrainMap(string sFile);
		void SaveTerrainMap(string sFile);
		bool LoadBattleMap();
		void SaveBattleMap();
		bool LoadClassSet(string sFile);
		void SaveClassSet(string sFile, LL_ClassSet* poClassSet);
		bool LoadGlobalClassSet();
		void SaveGlobalClassSet();
		bool LoadUnitSet(string sFile);
		void SaveUnitSet(string sFile);
		bool LoadItemSet(string sFile);
		void SaveItemSet(string sFile);
		bool LoadMonsterSet(string sFile);
		void SaveMonsterSet(string sFile);
		bool LoadPlayerSet(string sFile);
		void SavePlayerSet(string sFile);
		bool LoadVehicleObjectsSet(string sFile);
		void SaveVehicleObjectsSet(string sFile);
		bool LoadMap(C_i(iMap));
		void NewMap(C_i(iMap));
		bool LoadItems(string sFile);
		void SaveItems(string sFile);
		MEMVAR_GET(CurrentMap, int, myiCurrentMap);
	//- [Directories and files] -
		MEMVAR_GETREF(GameDir,			string, mysGameDir);
		MEMVAR_GETREF(DocumentationDir, string, mysDocumentationDir);
		MEMVAR_GETREF(GraphicsDir,		string, mysGraphicsDir); 
		MEMVAR_GETREF(MapsDir,			string,	mysMapsDir);
		MEMVAR_GETREF(MusicDir, 		string, mysMusicDir);
		MEMVAR_GETREF(RootDir, 			string, mysRootDir);
		MEMVAR_GETREF(SaveDir, 			string, mysSaveDir);
		MEMVAR_GETREF(SetsDir, 			string, mysSetsDir);
		string ClassSetFileName();
		string ClassFileName();
		string GlobalClassSetFileName();
		string GlobalClassFileName();
		string GlobalScriptFileName();
		string UnitSetFileName();
		MEMVAR_GET(VehicleSetFile,		string, mysVehicleSet);
		MEMVAR_GET(TerrainSetFile,		string, mysTerrainSet);
		MEMVAR_GET(MapSetFile,			string, mysMapSet);
		MEMVAR_GET(TerrainMapFile,		string, mysTerrainMap);
		MEMVAR_GET(UnitSetFile,			string, mysUnitSet);
		MEMVAR_GET(ItemSetFile,			string, mysItemSet);
		MEMVAR_GET(MonsterSetFile,		string, mysMonsterSet);
		MEMVAR_GET(PlayerSetFile,		string, mysPlayerSet);
		MEMVAR_GET(VehicleObjectsSetFile, string, mysVehicleObjectsSet);
		MEMVAR_GET(GlobalInfofile,		string, mysGlobalInfofile);
		MEMVAR_GETREF(GlobalScript, 	LL_ScriptedUnit, myoGlobalScript);
	//- [File I/O] -
		void SaveGame(string sGameName);
		void RestoreGame(string sGameName);
		bool Load(string sFile, ASFC_Screen* poScreen, ASFC_FontPalette* poFontPalette);
		void SaveGlobalInfo();
		bool LoadClasses(string sFile, ASFC_Screen* poScreen);
		bool ReloadBattleInfo();
		MEMVAR_SETGET(SetGameFile, GameFile, string, mysGameFile);
	//- [Object Accessing] -
		MEMVAR_GETREF(BattleTerrainMap,		LL_TerrainMap,			myoBattleTerrainMap);
		MEMVAR_GETREF(GlobalClassSet,		LL_ClassSet,			myoGlobalClassSet);
		MEMVAR_GETREF(MapSet,				LL_MapSet,				myoMapSet);
		MEMVAR_GETREF(ItemSet,				LL_ItemSet,				myoItemSet);
		MEMVAR_GETREF(MonsterSet,			LL_MonsterSet,			myoMonsterSet);
		MEMVAR_GETREF(PlayerSet,			LL_PlayerSet,			myoPlayerSet);
		MEMVAR_GETREF(TerrainSet,			LL_TerrainSet,			myoTerrainSet);
		MEMVAR_GETREF(MobilityTerrainMap,	LL_MobilityTerrainMap,	myoMobilityTerrainMap);
		MEMVAR_GETREF(Player,				LL_Player,				myoPlayer);
		MEMVAR_GETREF(VehicleSet,			LL_VehicleSet,			myoVehicleSet);
		MEMVAR_GETREF(LOOP,					LOOP_LOOP,				myoLOOP);
		MEMVAR_GETREF(LOOPLibStandard,		LOOP_LOOPLib_Standard,	myoLOOPLibStandard);
		MEMVAR_GETREF(Clock,				LL_GameClock,			myoGameClock);
		MEMVAR_GETREF(EventQueue,			LL_EventQueue,			myoEventQueue);
		MEMVAR_GETREF(CLList,				LL_CLList,				myoCLList);
		MEMVAR_GETREF(BattleMap,			LL_BattleMap,			myoBattleMap);
		MEMVAR_SETGET(SetInBattleMode,		InBattleMode,			bool, myfInBattleMode);
		MEMVAR_SETGET(SetRecorderOn,		RecorderOn,				bool, myfDataRecorderOn);
		LL_TerrainMap& TerrainMap();
		LL_UnitMap& UnitMap();
		LL_ClassSet& ClassSet();
		LL_UnitSet& UnitSet();
		LL_PathNodes& PathNodes();
//		LL_ScriptedUnit& GlobalScript();
		MEMVAR_GETREF(Sound,			ASFC_Sound,			 myoSound);
		MEMVAR_GETREF(BattleUnitMap, 	LL_BattleUnitMap,	 myoBattleUnitMap);
		MEMVAR_GETREF(BattleUnitSet, 	LL_BattleUnitSet,	 myoBattleUnitSet);
		MEMVAR_GETREF(VehicleObjectSet,	LL_VehicleObjectSet, myoVehicleObjectSet);
  		MEMVAR_GETREF(FileManager,		LL_FileManager,		 myoFileManager);
		MEMVAR_GETREF(DataRecorder,		LL_DataRecorder,	 myoDataRecorder);
	//- [Global Information] -
		MEMVAR_SETGET(SetStartMap, 			StartMap,			int,	myiStartMap);
		MEMVAR_SETGET(SetDeathMap, 			DeathMap,			int,	myiDeathMap);
		MEMVAR_SETGET(SetInitialPlayer,		InitialPlayer,		int,	myiInitialPlayer);
		MEMVAR_SETGET(SetChanceOfHealInCamp, ChanceOfHealInCamp, int,	myiChanceOfHealInCamp);
  		MEMVAR_SETGET(SetAmountOfHealInCamp, AmountOfHealInCamp, int,	myiAmountofHealInCamp);
	//- [Flags] -
		int  FlagPosition(string sFlagName);
		bool FlagExists(string sFlagName);
		void SetFlagOn(string sFlagName);
		void SetFlagOff(string sFlagName);
		void SwitchFlag(string sFlagName);
		bool IsFlagOn(string sFlagName);
		MEMVAR_GETREF(FlagStrings,		ASFC_LinkedList<string>, mylsFlags);
		MEMVAR_GETREF(Flags,			ASFC_LinkedList<bool>,	 mylfFlags);

	protected:
	//Const
		//Default sub directories
			#define LL_Game__SUB_DOCUMENTATION 	"/documentation"
			#define LL_Game__SUB_GRAPHICS		"/graphics"
			#define LL_Game__SUB_MAPS			"/maps"
			#define LL_Game__SUB_MUSIC		 	"/music"
			#define LL_Game__SUB_ROOT			"/root"
			#define LL_Game__SUB_SAVE			"/save"
			#define LL_Game__SUB_SETS			"/sets"
		//Default files
			#define cGame__DEFAULT_MAP 		"./data/defaults/default.map"
			#define cGame__GLOBAL_CLASSSET	"global.classset"
			#define cGame__GLOBAL_CLASS		"global.class"
			#define cGame__GLOBAL_SCRIPT	"glscript.class"
			#define cGame__BATTLE_MAP		"battle.info"
		//Misc.
			#define LL_Game__GLOBAL_CLASS_IDENTIFIER "GLSCRIPT"
			#define LL_Game__GLOBAL_IDENTIFIER "GLOBAL"
	//Vars
		//Game objects
			LL_TerrainMap			myoTerrainMap;
			LL_UnitMap				myoUnitMap;
			LL_ClassSet				myoClassSet;
			LL_ClassSet				myoGlobalClassSet;
			LL_MapSet				myoMapSet;
			LL_UnitSet				myoUnitSet;
			LL_ItemSet				myoItemSet;
			LL_MonsterSet			myoMonsterSet;
   			LL_PlayerSet			myoPlayerSet;
			LL_TerrainSet			myoTerrainSet;
			LL_MobilityTerrainMap	myoMobilityTerrainMap;
			LL_Player				myoPlayer;
			LL_VehicleSet			myoVehicleSet;
			LOOP_LOOP				myoLOOP;
			LOOP_LOOPLib_Standard 	myoLOOPLibStandard;
			LL_PathNodes			myoPathNodes;
			LL_GameClock			myoGameClock;
			LL_EventQueue			myoEventQueue;
			LL_CLList				myoCLList;
			int						myiCurrentMap;
			ASFC_Screen*			mypoScreen;
			ASFC_FontPalette*		mypoFontPalette;
			LL_ScriptedUnit			myoGlobalScript;
			LL_FileManager			myoFileManager;
   			LL_DataRecorder			myoDataRecorder;
			bool					myfDataRecorderOn;
			ASFC_Sound				myoSound;
		//Battle objects
			LL_BattleMap			myoBattleMap;
			LL_PathNodes			myoBattlePathNodes;
			LL_TerrainMap			myoBattleTerrainMap;
			LL_ClassSet				myoBattleClassSet;
			LL_BattleUnitMap		myoBattleUnitMap;
			LL_BattleUnitSet		myoBattleUnitSet;
			LL_VehicleObjectSet		myoVehicleObjectSet;
			bool					myfInBattleMode;
		//Global Information
			int	myiStartMap;
			int myiDeathMap;
			int myiInitialPlayer;
			string mysGlobalInfofile;
			string	sDefaultMapSet,
					sDefaultVehicleSet,
					sDefaultTerrainSet,
					sDefaultItemSet,
					sDefaultMonsterSet,
     				sDefaultPlayerSet,
					sDefaultVehicleObjectsSet;
			int myiChanceOfHealInCamp, myiAmountofHealInCamp;
		//Directories and files
			string	mysGameName;
			string	mysGameDir,
					mysDocumentationDir,
					mysGraphicsDir,
					mysMapsDir,
					mysMusicDir,
					mysRootDir,
					mysSaveDir,
					mysSetsDir;
			string	mysVehicleSet,
					mysTerrainSet,
					mysMapSet,
					mysTerrainMap,
					mysClassSet,
					mysUnitSet,
					mysItemSet,
     				mysMonsterSet,
     				mysPlayerSet,
					mysVehicleObjectsSet;
			string  mysGameFile;
		//Flags
			ASFC_LinkedList<string> mylsFlags;
			ASFC_LinkedList<bool>   mylfFlags;
};

#endif
