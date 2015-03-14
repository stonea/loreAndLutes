/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleunitset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A unit set recognizes a whole bunch of units (of varying types) and maps them to a
				 numerical identifier. Remember it recognizes units it doesn't actually contain them!
*/
#ifndef LL_BATTLEUNITSET_H_
#define LL_BATTLEUNITSET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "unitset.h"
//Aggregates
	#include "battleplayer.h"
	#include "battleenemy.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BattleUnitSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_BattleUnitSet : public LL_UnitSet
{	public:
	//- [Constuctors] -
 		LL_BattleUnitSet();
 		MEMVAR_SETGET(SetBattleUnitMap, BattleUnitMap, LL_BattleUnitMap*, mypoBattleUnitMap);
	//- [General Unit Management] -
		virtual LL_Unit& Unit(int iSeg, int iOff);
		virtual void Run();
		virtual void ResetAnimations();
	//- [Players]-
		int NumPlayers();
		void DeletePlayer(int iNum);
		void ClearPlayers();
		LL_BattlePlayer& Player(int iNum);
		LL_BattlePlayer& PlayerMappedToPartyMember(int iNum);
		void AddPlayer( LL_TerrainMap* poTerrainMap, LL_BattleUnitMap* poUnitMap,
  						LL_GameClock* poClock, LL_EventQueue* poQueue, LL_ItemSet* poItemSet,
            			string sGraphicsDir, ASFC_Animation* pCorpseImg,
               			int iMemberNum, LL_PartyMember* poPartyMember, ASFC_Input* poInput,
         				ASFC_Console* poConsole, ASFC_Screen* poScreen, int iMapEdgeX, int iMapEdgeY,
						int iX, int iY, int iL);
		bool AnyPlayers();
		MEMVAR_GETREF(PlayerList, ASFC_LinkedList<LL_BattlePlayer>, myloBattlePlayers);
	//- [Enemies] -
		int NumEnemies();
		void ClearEnemies();
		LL_BattleEnemy& Enemy(int iNum);
		void AddEnemy(  LL_TerrainMap* poTerrainMap, LL_BattleUnitMap* poUnitMap,
  						LL_GameClock* poClock, LL_EventQueue* poQueue, LL_ItemSet* poItemSet,
            			string sGraphicsFile, string sGraphicsDir, ASFC_Animation* pCorpseImg,
               			ASFC_Console* poConsole, ASFC_Screen* poScreen, int iMonsterType,
                  		int iMapEdgeX, int iMapEdgeY, int iX, int iY, int iL);
		bool AnyEnemies();
 		
	protected:
		LL_BattleUnitMap* mypoBattleUnitMap;
		ASFC_LinkedList<LL_BattlePlayer> myloBattlePlayers;
		ASFC_LinkedList<LL_BattleEnemy>  myloBattleEnemies;
};

#endif
