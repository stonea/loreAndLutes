/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleenemy.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LL_BATTLEENEMY_H_
#define LL_BATTLEENEMY_H_
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include <lbase/monster.h>
//Realizes
	#include <asfc/screen.h>
	#include <asfc/console.h>
	#include "battleunitmap.h"
	#include "battleplayer.h"
//Dependencies
	#include "monstertemplate.h"
	#include <asfc/linkedlist.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_BattleEnemy : public LL_Monster
{	public:
	//- [Construction] -
		LL_BattleEnemy();
		MEMVAR_SETGET(SetConsole, Console, ASFC_Console*, mypoConsole);
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, mypoScreen);
		MEMVAR_SETGET(SetCorpseImage, CorpseImage, ASFC_Animation*, mypoCorpseImage);
		MEMVAR_SETGET(SetBattleUnitMap, BattleUnitMap, LL_BattleUnitMap*, mypoBattleUnitMap);
		MEMVAR_SETGET(SetBattlePlayers, BattlePlayers, ASFC_LinkedList<LL_BattlePlayer>*, mylpoBattlePlayers);
		MEMVAR_SETGET(SetMapEdgeX, MapEdgeX, int, myiMapEdgeX);
		MEMVAR_SETGET(SetMapEdgeY, MapEdgeY, int, myiMapEdgeY);
		MEMVAR_SETGET(SetStrategy, Strategy, LL_MonsterTemplate::LL_Strategy, myiStrategy);
	//- [Drawing] -
		virtual int BlitTo(ASFC_Surface &screen, const int & iX, const int & iY);
	//- [Updating] -
		MEMVAR_SETGET(SetDead, Dead, bool, myfDead);
		void Run(ASFC_Surface &oScreen);
		void Damage(int iAmount);
		
	protected:
 	//Type
		struct LL_DistanceInfo
		{	ASFC_DIRECTION iDirection;
			int iX;
			int iY;
			int iCost;
		};
 	
	//P- [Updating] -P
		void AttackTo(int iX, int iY);
		void Die();
	//P- [Calculations] -P
		int AttackValue();
		int DefenseValue();
		bool WithinRadius(int iX, int iY);
	//P- [AI] -P
		void RunAsIdiot();
		void RunAsNormal();
		void RunAsUberWimp();
		void RunAsWimp();
		void RunAsSmartWimp();
		void RunAsAerialAttacker();
		void RunAsExploiter();
		void RunAsSlacker();
		void RunAsBloodThirsty();
		void RunAsWarrior();
		void RunAsRacist();
	//P- [AI Sub Functions] -P
		bool AttackIfNextToPlayer();
		bool KeepDistance();
		int  PlayersAdjacent(int iX, int iY);
		bool AerialAttack();
		bool WithinRange(int iX, int iY);
		bool EnemyExists(int iEnemy);
		void BeaconEnemyToPlayer(int iPartyMember);
		void BeaconEnemyToExit();
		int  PlayerAssociatedToPartyMember(int iMember);
		void MoveTowardsBeacon();
		void Flee();
		void CheckFlee();
		int  PlayerWithLowestHP();
		int	 PlayerWithHighestHP();
		int  PlayerWithHighestMP();
	//Const
		static const int RNDDIR_NORTH = 0;
		static const int RNDDIR_SOUTH = 1;
		static const int RNDDIR_WEST  = 2;
		static const int RNDDIR_EAST  = 3;
		const static int BORDER_NORTH = 0;
		const static int BORDER_SOUTH = 1;
		const static int BORDER_WEST  = 2;
		const static int BORDER_EAST  = 3;

	//Vars
		LL_MonsterTemplate::LL_Strategy myiStrategy;
		bool myfDead, myfFlee;
		int myiEnemy;	//Value of party member to attack, not offset of battle player
		int myiBeaconX, myiBeaconY;
		int myiBeaconBorder;
		int myiMapEdgeX, myiMapEdgeY;
		int myiCurrentWeapon;
	//Outside info
		ASFC_LinkedList<LL_BattlePlayer>* mylpoBattlePlayers;
	//Images
		ASFC_Animation* mypoCorpseImage;
	//Interface
		LL_BattleUnitMap* mypoBattleUnitMap;
		ASFC_Screen* mypoScreen;
		ASFC_Console* mypoConsole;
};

#endif
