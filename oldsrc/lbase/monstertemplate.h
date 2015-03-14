/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monstertemplate.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef MONSTERTEMPLATE_H_
	#define MONSTERTEMPLATE_H_

//Aggregates
	#include "chest.h"
//Dependencies
	#include <asfc/utils.h>
	#include "monster.h"
	#include "vehicle.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_MonsterTemplate
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_MonsterTemplate
{	public:
	//Type
		enum LL_Strategy
		{	STRATEGY_IDIOT = 0,
			STRATEGY_NORMAL,
			STRATEGY_UBER_WIMP,
			STRATEGY_WIMP,
			STRATEGY_SMART_WIMP,
			STRATEGY_AERIAL_ATTACKER,
			STRATEGY_EXPLOITER,
			STRATEGY_SLACKER,
			STRATEGY_BLOODTHIRSTY,
			STRATEGY_WARRIOR,
			STRATEGY_NUM_STRATGIES
		};

	//- [Constuctors] -
 		LL_MonsterTemplate();
	//- [File I/O] -
		void 	Save(ofstream &oFile);
		void	Load(ifstream &oFile, string sGraphicsDir);
	//- [Object Maker] -
		void MakeMonster(string sGraphicsPath, LL_Monster* poMonster);
		LL_Strategy PickStrategy();
	//- [Friends] -
		void AddFriend(int iMonsterCode, int iChance);
		void DeleteFriend(int iNum);
		int  Friend(int iNum);
		int  FriendChance(int iNum);
		void SetFriend(int iNum, int iTo);
		void SetFriendChance(int iNum, int iTo);
		int  NumFriends();
		int  PickMonster(int iSelfCode);
		int  NumMonstersToPlace();
	//- [Attributes Handeling] -
		MEMVAR_SETGET(SetIdentifier,	Identifier,		string, mysIdentifier);
		MEMVAR_SETGET(SetImage,			Image,			string, mysImage);
		MEMVAR_SETGET(SetCustomImage,	CustomImage,	bool, myfCustomImage);
		MEMVAR_SETGET(SetRarity,		Rarity,			int, myiRarity);
		MEMVAR_SETGET(SetStrength, 		Strength, 		int, myiStrength);
		MEMVAR_SETGET(SetDexterity, 	Dexterity, 		int, myiDexterity);
		MEMVAR_SETGET(SetIntelligence, 	Intelligence, 	int, myiIntelligence);
		MEMVAR_SETGET(SetMP, 			MP, 			int, myiMP);
		MEMVAR_SETGET(SetMaxMP, 		MaxMP, 			int, myiMaxMP);
		MEMVAR_SETGET(SetHP, 			HP, 			int, myiHP);
		MEMVAR_SETGET(SetMaxHP, 		MaxHP, 			int, myiMaxHP);
		MEMVAR_SETGET(SetExperience,	Experience, 	int, myiExperience);
		MEMVAR_SETGET(SetVehicleCode,	VehicleCode,	int, myiVehicleCode);
		MEMVAR_SETGET(SetWeapon1,		Weapon1,		int, myiWeapon1);
		MEMVAR_SETGET(SetWeapon2,		Weapon2,		int, myiWeapon2);
		MEMVAR_SETGET(SetArmor1,		Armor1,			int, myiArmor1);
		MEMVAR_SETGET(SetArmor2,		Armor2,			int, myiArmor2);
		MEMVAR_GETREF(Strategies, 		ASFC_LinkedList<LL_Strategy>, myliStratgies);
		MEMVAR_SETGET(SetChanceOfChest,	ChanceOfChest,	int, myiChanceOfChest);
		MEMVAR_SETGET(SetChanceOfFood,	ChanceOfFood,	int, myiChanceOfFood);
		MEMVAR_SETGET(SetMaxFood,		MaxFood,		int, myiMaxFood);
		MEMVAR_SETGET(SetPartyMin,		PartyMin,		int, myiPartyMin);
		MEMVAR_SETGET(SetPartyMax,		PartyMax,		int, myiPartyMax);
		MEMVAR_GETREF(DeathChest, 		LL_Chest, myoDeathChest);

 	private:
 	//Vars
		//Image
			string mysImage;
			bool myfCustomImage;
		//Attributes and Mobility
			string mysIdentifier;
	 		int myiRarity;
			int myiStrength,
				myiDexterity,
				myiIntelligence,
				myiMP, myiMaxMP,
				myiHP, myiMaxHP,
				myiExperience;
			int myiVehicleCode;
			int myiWeapon1, myiWeapon2;
			int myiArmor1, myiArmor2;
			ASFC_LinkedList<LL_Strategy> myliStratgies;
			ASFC_LinkedList<int> myliFriends;
			ASFC_LinkedList<int> myliFriendChance;
			int myiPartyMin, myiPartyMax;
		//Inventory (of death!)
			int myiChanceOfChest;
			int myiChanceOfFood;
			int myiMaxFood;
			LL_Chest myoDeathChest;
};

//Now ending monstertemplate.h
	#endif
