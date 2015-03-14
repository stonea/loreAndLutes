/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			creature.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A creature is an abstract class from which players, monsters, and scriptedunits are
				 derived. A creature has an inventory and a vehicle. Creatures also recognize
				 a position within the map at all times. Creatures also have a calling position, each
				 turn they will attempt to move towards this position.
*/
#ifndef LL_CREATURE_H_
#define LL_CREATURE_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "unit.h"
//Aggregates
	#include "vehicle.h"
	#include "inventory.h"
	#include "route.h"
	#include "legalmovesmap.h"
//Realizes
	#include "terrainmap.h"
	#include "unitmap.h"
	#include "pathnodes.h"
	#include "gameclock.h"
	#include "cllist.h"
//Dependencies
	#include <asfc/console.h>
	#include "guimetrics.h"
	#include <asfc/utils.h>
	#include <asfc/timer.h>
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Creature
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Creature : public LL_Unit
{	public:
	//Const
		const static int NO_EQUIP = -1;
	//- [Constuctors] -
 		LL_Creature();
	//- [File I/O] -
		virtual void Save(ofstream &oFile);
		virtual void Load(ifstream &oFile);
	//- [Callbacks] -
		virtual void Run();
		virtual void Talk();
		virtual void Look();
		virtual void Search();
		virtual void Attack();
	//- [Map Handeling] -
		MEMVAR_SETGET(SetTerrainMap, TerrainMap, LL_TerrainMap*, mypoTerrainMap);
		MEMVAR_SETGET(SetUnitMap,    UnitMap,    LL_UnitMap*,    mypoUnitMap);
		MEMVAR_SETGET(SetPathNodes,	 PathNodes,	 LL_PathNodes*,	 mypoPathNodes);
		void Place(int iX, int iY, int iLayer);
	//- [Attributes Handeling] -
		MEMVAR_SETGET(SetStrength, 		Strength, 		int, myiStrength);
		MEMVAR_SETGET(SetDexterity, 	Dexterity, 		int, myiDexterity);
		MEMVAR_SETGET(SetIntelligence, 	Intelligence, 	int, myiIntelligence);
		MEMVAR_SETGET(SetMP, 			MP, 			int, myiMP);
		MEMVAR_SETGET(SetMaxMP, 		MaxMP, 			int, myiMaxMP);
		MEMVAR_SETGET(SetHP, 			HP, 			int, myiHP);
		MEMVAR_SETGET(SetMaxHP, 		MaxHP, 			int, myiMaxHP);
		MEMVAR_SETGET(SetExperience,	Experience, 	int, myiExperience);
		MEMVAR_SETGET(SetItemSet,		ItemSet,		LL_ItemSet*, mypoItemSet);
		MEMVAR_GETREF(Inventory, LL_Inventory, myoInventory);
		void AddHP(int iAmount);
	//- [Weapons & Armor] -	
		bool EquipWithWeapon(int iWeapon, ASFC_Console* poConsole, ASFC_Screen* poScreen, bool fReport = true);
		bool EquipWithArmor(int iArmor, ASFC_Console* poConsole, ASFC_Screen* poScreen, bool fReport = true);
		void UnEquipWeapon(int iWeapon);
		void UnEquipArmor(int iArmor);
		int  NumWeapons();
		int  Weapon(int iNum);
		int  NumArmors();
		int  Armor(int iNum);
		int  HoldsWeapon(int iWeaponNumber);	//Returns how many of weapon iWeaponNum this creature holds
		int	 HoldsArmor(int iArmorNumber);
	//- [Mobility Handeling] -
		MEMVAR_SETGET(SetVehicle, Vehicle, LL_Vehicle, myoVehicle);
 	//- [Running] -
 		bool CanMove(ASFC_DIRECTION iDirection);
		virtual bool Move(ASFC_DIRECTION iDirection);	//Move this critter' return true if he moved
	//- [AI] -
		void Call(int iX, int iY);
		void RandomArea(int iX, int iY, int iWidth, int iHeight);
		MEMVAR_SETGET(SetClock, Clock, LL_GameClock*, mypoClock);
		MEMVAR_SETGET(SetCLList, CLList, LL_CLList*, mypoCLList);
		void MoveFromTo(C_i4(iX1, iY1, iX2, iY2));

	protected:
	//P- [Running] -P
		void RemoveFromMap();
	//P- [Utils] -P
		void OffsetCoods(int &iX, int &iY, ASFC_DIRECTION iDirection);	//Changes X, Y to the X, Y in direction iDirection	
		int  OppositeDir(ASFC_DIRECTION iDirection);	//Returns the opposite direction of iDirection (e.g. North returns South, West returns East...)
	//P- [AI] -P
		void UpdateAI();

	//Vars
		//Maps
			LL_TerrainMap*  mypoTerrainMap;
			LL_UnitMap*     mypoUnitMap;
			LL_GameClock*	mypoClock;
		//Inventory
			LL_Inventory	  myoInventory;
		//Attributes
			int myiStrength,
				myiDexterity,
				myiIntelligence,
				myiMP, myiMaxMP,
				myiHP, myiMaxHP,
				myiExperience;
			int myiWeapon1, myiWeapon2, myiWeapon3;
			int myiArmor1, myiArmor2, myiArmor3;
			bool myfTorsoEquip, myfArmEquip, myfHand1Equip, myfHand2Equip, myfHeadEquip;
		//Mobility
			LL_Vehicle myoVehicle;
			LL_MobilityTerrainMap* mypoMobilityTerrainMap;
			int myiMapEdgeX, myiMapEdgeY;
		//AI
			LL_PathNodes* mypoPathNodes;
			LL_Route	  myoRoute;
			LL_LegalMovesMap* mytpoLegalMovesMap;
			LL_ItemSet*	mypoItemSet;
			bool myfCalling;
			int  myiCallingX, myiCallingY;
			int  myiOnStep;
			bool myfRandom;
			int  myiRandomX, myiRandomY, myiRandomWidth, myiRandomHeight;
			int  myiBlockedMoves;
			bool myfPerp;
			int  myiBlockCount;
			LL_CLList* mypoCLList;
};

//Now ending creature.h
	#endif
