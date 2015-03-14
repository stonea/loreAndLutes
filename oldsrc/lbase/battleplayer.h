/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleplayer.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LL_BATTLEPLAYER_H_
#define LL_BATTLEPLAYER_H_
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "creature.h"
//Aggregates
	#include <asfc/timer.h>
//Realizes
	#include <asfc/input.h>
	#include <asfc/console.h>
	#include <asfc/screen.h>
	#include "battleunitmap.h"
	#include "partymember.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_BattlePlayer : public LL_Creature
{	public:
	//- [Construction] -
		LL_BattlePlayer();
		MEMVAR_SETGET(SetInput, Input, ASFC_Input*, mypoInput);
		MEMVAR_SETGET(SetConsole, Console, ASFC_Console*, mypoConsole);
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, mypoScreen);
		MEMVAR_SETGET(SetBattleUnitMap, BattleUnitMap, LL_BattleUnitMap*, mypoBattleUnitMap);
		MEMVAR_SETGET(SetMember, Member, LL_PartyMember*, mypoMember);
		MEMVAR_SETGET(SetCorpseImage, CorpseImage, ASFC_Animation*, mypoCorpseImage);
	//- [Position] -
		MEMVAR_SETGET(SetMemberNum, MemberNum, int, myiMemberNum);
		MEMVAR_SETGET(SetEscaped, Escaped, bool, myfEscaped);
		MEMVAR_SETGET(SetMapEdgeX, MapEdgeX, int, myiMapEdgeX);
		MEMVAR_SETGET(SetMapEdgeY, MapEdgeY, int, myiMapEdgeY);
		MEMVAR_SETGET(SetLastDirection, LastDirection, int, myiLastDirection);
	//- [Drawing] -
		virtual int BlitTo(ASFC_Surface &screen, const int & iX, const int & iY);
		void Reset();
	//- [Updating] -
		bool Run(ASFC_Surface &oScreen, int iRegisterNum);
		void UpdateState();
		void Damage(int iAmount);
		
	protected:
	//P- [Updating] -
		ASFC_DIRECTION PromptDirection();
		void GrabLocation(int* piX, int* piY);
		void AttackTo(int iX, int iY);
		void OffsetCoods(int &iX, int &iY, ASFC_DIRECTION iDirection);
	//P- [Calculations] -P
		int AttackValue(int iDistance);
		int DefenseValue();
		bool WithinRadius(int iX, int iY);
	//P- [Basic Actions] -P
		bool TalkTo(ASFC_DIRECTION iDirection);
 		bool LookTo(ASFC_DIRECTION iDirection);
 		bool PushTo(ASFC_DIRECTION iDirection);
 		bool SearchTo(ASFC_DIRECTION iDirection);
		bool GetTo(ASFC_DIRECTION iDirection);
	//Vars
		//Location
			int myiMemberNum;
			bool myfEscaped;
			int myiMapEdgeX, myiMapEdgeY;
			int myiLastDirection;
 		//Images
			ASFC_Animation* mypoCorpseImage;
		//Interface
			ASFC_Screen* mypoScreen;
			ASFC_Input* mypoInput;
			ASFC_Timer myoTimer;
			ASFC_Console* mypoConsole;
			LL_BattleUnitMap* mypoBattleUnitMap;
			bool myfBoxDown;
			int myiBoxColor;
			int myiCurX, myiCurY;
			LL_PartyMember* mypoMember;
			int myiCurrentWeapon;
			bool myfOnTurn;

	//Const
		static const int BOX_DELAY = 30;
		static const int BOX_DOWN_STEP = 25;
		static const int TRANS_DOWN_STEP = 5;
		static const int TRANS_HIGHEST = 150;
		static const SDLKey KEY_MOVE_NORTH = SDLK_UP;
		static const SDLKey KEY_MOVE_SOUTH = SDLK_DOWN;
		static const SDLKey KEY_MOVE_WEST  = SDLK_LEFT;
		static const SDLKey KEY_MOVE_EAST  = SDLK_RIGHT;
		static const SDLKey KEY_PASS  	   = SDLK_SPACE;
		static const SDLKey KEY_TALK  	   = SDLK_t;
		static const SDLKey KEY_LOOK  	   = SDLK_l;
		static const SDLKey KEY_PUSH  	   = SDLK_p;
		static const SDLKey KEY_SEARCH 	   = SDLK_s;
		static const SDLKey KEY_ATTACK	   = SDLK_a;
		static const SDLKey KEY_GET		   = SDLK_g;
		static const SDLKey KEY_USE		   = SDLK_u;
		static const SDLKey KEY_ZSTATS	   = SDLK_z;
		static const SDLKey KEY_QUIT	   = SDLK_ESCAPE;
		static const SDLKey KEY_CHOOSE	   = SDLK_RETURN;
		static const SDLKey KEY_CHOOSE2	   = SDLK_SPACE;
		static const SDLKey KEY_SET_PLAYER_1 = SDLK_1;
		static const SDLKey KEY_SET_PLAYER_2 = SDLK_2;
		static const SDLKey KEY_SET_PLAYER_3 = SDLK_3;
		static const SDLKey KEY_SET_PLAYER_4 = SDLK_4;
		static const SDLKey KEY_SET_PLAYER_5 = SDLK_5;
		static const SDLKey KEY_SET_PLAYER_6 = SDLK_6;
		static const SDLKey KEY_SET_PLAYER_7 = SDLK_7;
		static const SDLKey KEY_SET_PLAYER_8 = SDLK_8;
		static const SDLKey KEY_SET_PLAYER_9 = SDLK_9;
};

#endif
