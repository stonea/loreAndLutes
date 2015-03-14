/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			unitset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A unit set recognizes a whole bunch of units (of varying types) and maps them to a
				 numerical identifier. Remember it recognizes units it doesn't actually contain them!
*/
#ifndef LL_UNITSET_H_
#define LL_UNITSET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include <asfc/linkedlist.h>
	#include "scripteditem.h"
	#include "weapon.h"
	#include "armor.h"
	#include "monster.h"
	#include "scriptedunit.h"
	#include "chest.h"
	#include "guts.h"
	#include "transport.h"
	#include "player.h"
	#include "vehicleobject.h"
	#include "spawner.h"
//Realizes
	#include "gameclock.h"
	#include "terrainmap.h"
	#include "unitmap.h"
	#include "eventqueue.h"
	#include "pathnodes.h"
	#include "itemset.h"
	#include "vehicleobjectset.h"
	#include "monsterset.h"
	#include <loop/loop.h>
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_UnitSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_UnitSet
{	public:
	//Const
		static const int SEG_SCRIPTED_ITEMS = 0x0;
		static const int SEG_WEAPONS		= 0x1;
		static const int SEG_ARMORS			= 0x2;
		static const int SEG_MONSTERS		= 0x3;
		static const int SEG_SCRIPTED_UNITS	= 0x4;
		static const int SEG_BATTLE_ENEMY	= 0x5;
		static const int SEG_BATTLE_PLAYER	= 0x6;
		static const int SEG_CHESTS			= 0x7;
		static const int SEG_TRANSPORTS		= 0x8;
		static const int SEG_GUTS			= 0x9;
		static const int SEG_VEHICLES		= 0xA;
		static const int SEG_SPAWNER		= 0xB;
		static const int SEG_PLAYER			= 0xFE;
		static const int SEG_NULL			= 0xFF;
		static const int OFF_NULL			= 0xFF;
		static const int OFF_PLAYER			= 0x0;	
		static const int LAYER_DEFAULT = 3;
		static const int NOTHING_FOUND = -1;

	//- [Constuctors] -
 		LL_UnitSet();
 		MEMVAR_SETGET(SetUnitMap, UnitMap, LL_UnitMap*, mypoUnitMap);
 		MEMVAR_SETGET(SetTerrainMap, TerrainMap, LL_TerrainMap*, mypoTerrainMap);
 		MEMVAR_SETGET(SetEventQueue, EventQueue, LL_EventQueue*, mypoEventQueue);
 		MEMVAR_SETGET(SetGameClock,  GameClock, LL_GameClock*, mypoGameClock);
 		MEMVAR_SETGET(SetCLList,	 CLList,    LL_CLList*, mypoCLList);
 		MEMVAR_SETGET(SetPathNodes, PathNodes, LL_PathNodes*, mypoPathNodes);
 		MEMVAR_SETGET(SetLOOP, LOOP, LOOP_LOOP*, mypoLOOP);
 		MEMVAR_SETGET(SetItemSet, ItemSet, LL_ItemSet*, mypoItemSet);
 		MEMVAR_SETGET(SetVehicleObjectSet, VehicleObjectSet, LL_VehicleObjectSet*, mypoVehicleObjectSet);
 		MEMVAR_SETGET(SetMonsterSet, MonsterSet, LL_MonsterSet*, mypoMonsterSet);
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, myoScreen);
		MEMVAR_SETGET(SetFontPalette, FontPalette, ASFC_FontPalette*, mypoFontPalette);
		MEMVAR_SETGET(SetOnlyRunUnit, OnlyRunUnit, int, myiOnlyRunUnit);
	//- [General Unit Management] -
		void Clear();
		void RemoveUnit(int iSeg, int iOff);
		virtual void Run();
		void PlaceUnits();
	//- [File I/O] -
		void Save(ofstream &oFile);
		bool Load(ifstream &oFile, string sGraphicsDir);
		virtual void SaveRecordingInfo(ofstream &oFile);
		virtual bool LoadRecordingInfo(ifstream &oFile, string sGraphicsDir);
	//- [General Unit Manipulation] -
		virtual void ResetAnimations();
		virtual LL_Unit& Unit(int iSeg, int iOff);
		bool UnitExists(int iSeg, int iOff);
	//- [Player] -
		MEMVAR_SETGET(SetPlayer, Player, LL_Player*, mypoPlayer);
	//- [Monsters] -
		int NumMonsters();
		void AddMonster(int iX, int iY, int iL, string sGraphicsPath, int iNum);
		LL_Monster& Monster(int iOff);
		int MonsterOn(int iX, int iY);
	//- [ScriptedUnits] -
		int NumScriptedUnits();
		LL_ScriptedUnit& ScriptedUnit(int iOff);
		LL_ScriptedUnit& ScriptedUnit(string sIdentifier);
		void AddScriptedUnit(LL_ScriptedUnit &oNew);
		void AddScriptedUnit(LL_TerrainMap* poTerrainMap, LL_UnitMap* poUnitMap,
  							 LL_GameClock* poClock, LL_PathNodes* poPathNodes,
          					 LL_EventQueue* poQueue, LL_ItemSet* poItemSet, string sGraphicsFile,
          					 string sGraphicsDir, string sClass, string sIdentifier,
            				 int iX, int iY, int iL);
		bool IsScriptedUnit(string sIdentifier);
		void CallLabels(int iPlayerX, int iPlayerY);
		void CallInitLabels();
		void Ping(string sLabel);
		void PingClass(string sClass, string sLabel);
		void PingClassAndDeriv(string sClass, string sLabel);
	//- [Armor Handeling] -
		int	NumArmors();
		void AddArmor(int iX, int iY, int iL, int iNum);
		int ArmorType(int iNum);
	//- [Weapon Handeling] -
		int NumWeapons();
		void AddWeapon(int iX, int iY, int iL, int iNum);
		int WeaponType(int iNum);
	//- [ScriptedItem Handeling] -
		int NumScriptedItems();
		void AddScriptedItem(int iX, int iY, int iL, int iNum);
		int ScriptedItemType(int iNum);
	//- [Chest Handeling] -
		int NumChests();
		void AddChest(int iX, int iY, int iL);
		LL_Chest& Chest(int iNum);
	//- [Guts Handeling] -
		int NumGuts();
		void AddGuts(	int iX, int iY, int iL, ASFC_Animation& oAnimation,
  						LL_Inventory* poInventory, ASFC_Console* poConsole);
		LL_Guts& Guts(int iNum);
	//- [Transport Handeling] -
		int NumTransports();
		void AddTransport(int iX, int iY, int iL);;
		LL_Transport& Transport(int iNum);
	//- [Vehicle Objects] -
		int NumVehicles();
		void AddVehicle(int iX, int iY, int iL, string sGraphicsPath, int iNum);
		void RemoveVehicle(int iNum);
		int VehicleType(int iNum);
		LL_VehicleObject& VehicleObject(int iNum);
		int VehicleObjectNum(int iNum);
	//- [Spawner Handeling] -
		int NumSpawners();
		LL_Spawner& Spawner(int iNum);
		void AddSpawner(int iX, int iY);
		void RemoveSpawner(int iNum);
		int SpawnerAt(int iX, int iY);
		void HandleSpawners(string sGraphicsDir);
		bool OffPlayField(int iX, int iY, int iPlayerX, int iPlayerY);
		void CopySpawner(int iX, int iY, int iCopyNum);
	//- [Global script] -
		MEMVAR_SETGET(SetGlobalScript, GlobalScript, LL_ScriptedUnit*, mypoGlobalScript);
		void SetupGlobalScript(string sGraphicsDir);
		void RunGlobalScript();
	//- [Error Handeling] -
		void DisplayMessage(string sLine1, string sLine2, string sLine3, int iFont = 0);
	
 	protected:
 	//Type
 		struct LL_ItemEntry
 		{	int iX, iY, iL, iNum;
 		};
	//Const
		//Misc.
			#define LL_UnitSet__GLOBAL_CLASS_IDENTIFIER "GLSCRIPT"
			#define LL_UnitSet__GLOBAL_IDENTIFIER "GLOBAL"
 	
 	//Vars
		ASFC_Screen*						myoScreen;
		ASFC_FontPalette*					mypoFontPalette;
		ASFC_Input							myoInput;
 		LL_Player*							mypoPlayer;
 		LL_UnitMap*							mypoUnitMap;
 		LL_TerrainMap*						mypoTerrainMap;
 		LL_EventQueue* 						mypoEventQueue;
 		LL_GameClock*						mypoGameClock;
 		LL_CLList*							mypoCLList;
 		LL_PathNodes*						mypoPathNodes;
 		LL_ItemSet*							mypoItemSet;
		LL_VehicleObjectSet*				mypoVehicleObjectSet;
 		LL_MonsterSet*						mypoMonsterSet;
 		LOOP_LOOP*							mypoLOOP;
 		ASFC_LinkedList<LL_ScriptedUnit>	myloScriptedUnits;
 		ASFC_LinkedList<LL_Monster>			myloMonsters;
 		ASFC_LinkedList<LL_ItemEntry>		myloArmors;
 		ASFC_LinkedList<LL_ItemEntry>		myloWeapons;
 		ASFC_LinkedList<LL_ItemEntry>		myloScriptedItems;
 		ASFC_LinkedList<LL_Chest>			myloChests;
 		ASFC_LinkedList<LL_Guts>			myloGuts;
		ASFC_LinkedList<LL_Transport>		myloTransports;
 		ASFC_LinkedList<LL_ItemEntry>		myloVehicleObjects;
		ASFC_LinkedList<LL_Spawner>			myloSpawners;
 		LL_ScriptedUnit*					mypoGlobalScript;
		int									myiOnlyRunUnit;
};

//Now ending unitset.h
	#endif
