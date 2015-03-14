/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battle.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LRUN_BATTLE_H_
#define LRUN_BATTLE_H_
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Realizes
	#include <lbase/game.h>
	#include <asfc/effects.h>
	#include <asfc/screen.h>
	#include <lbase/painter.h>
	#include <lbase/zstats.h>
	#include <lbase/looplib_lore.h>
	#include <lbase/looplib_lorelinker.h>
//Dependencies
	#include <lbase/guimetrics.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LRUN_Battle
{	public:
	//- [Construction] -
		LRUN_Battle();
		void Setup(	LL_Game* poGame, LL_LOOPLib_LoreLinker* poLOOPLibLinker,
					LL_LOOPLib_Lore* poLOOPLib, LL_Painter* poPaint, ASFC_Screen* poScreen,
     				ASFC_Effects* poEffects, ASFC_Input* poInput, LL_ZStats* poZStats);
	//- [Attack] -
		bool Attack(int iMonster, int iBattleMap, int iMonsterSeg, int iMonsterOff, int* piDir);
		
	protected:
	//P- [Engine] -P
		void Run();
		void UpdateQueue();
		void PlayerAttack(int iPlayer, int iX, int iY, int iAmount);
		void EnemyAttack(int iPlayer, int iX, int iY, int iAmount);
	//P- [Setup] -P
		void PlaceParty();
		void PlaceEnemies();
	//P- [Graphics] -P
		void Draw();
		void DrawHit(int iX, int iY);
		void PerformEffect(LL_BORDER_EFFECT iEffect);

	//Const
		#define LRUN__DEAD_IMAGE	"/battle/dead.png"
		#define LRUN__HIT_IMAGE		"/battle/hit.png"
		const static int FREE_SPACE = -1;
		const static int ANIMATION_DELAY = 200;
		const static int EXIT_DELAY = 10;
		const static int ENEMY_DELAY = 25;
	//Vars
		//Game objects
			LL_Game*		mypoGame;
			LL_Painter* 	mypoPaint;
			ASFC_Screen*	mypoScreen;
			ASFC_Effects*	mypoEffects;
			ASFC_Input*		mypoInput;
			LL_ZStats*		mypoZStats;
			ASFC_Timer		myoTimer;
			ASFC_Animation 	myoDeadImage, myoHitImage;
			LL_LOOPLib_LoreLinker* mypoLOOPLibLinker;
			LL_LOOPLib_Lore* 	   mypoLOOPLib;
			int myiRunning;
		//Battle objects
			ASFC_Matrix<bool> lLight;
			int myiMapEdgeX, myiMapEdgeY;
			int myiRunningPlayer;
			int* mypiExitDir;
		//Display objects
			int myiViewX, myiViewY;
		//Misc.
			int myiBattleMap;
			int myiMonster;
			int myiNumMonsters;
			int myiMonsterSeg, myiMonsterOff;
};

#endif
