/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			player.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A player is a creature that moves based on user input. Its the player!
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef PLAYER_H_
	#define PLAYER_H_
//Parent
	#include "creature.h"
//Aggregates
	#include <asfc/input.h>
	#include "partymember.h"
//Realizes
	#include <asfc/console.h>
	#include <asfc/surface.h>
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Player
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Player : public LL_Creature
{	public:
	//Type
		//Update values specify what the L&L engine should do next
		enum LL_UPDATE
		{	UPDATE_OKAY = 0,
			UPDATE_GO_DONE,
			UPDATE_QUIT,
			UPDATE_GO_MAP_NORTH,
			UPDATE_GO_MAP_SOUTH,
			UPDATE_GO_MAP_WEST,
			UPDATE_GO_MAP_EAST
		};

	//- [Constuctors] -
 		LL_Player();
	//- [File I/O] -
		virtual void Save(ofstream &oFile);
		virtual void Load(ifstream &oFile, string sGraphicsDir);
	//- [Callbacks] -
		virtual void Run();
		void Talk();
		void Look();
		bool Push();
		void Search();
		void Attack();
	//- [Input] -
		MEMVAR_SET(SetConsole, ASFC_Console*, mypoCon);
		MEMVAR_SET(SetScreen,  ASFC_Surface*, mypoScreen);
		MEMVAR_SETGET(SetInput, Input, ASFC_Input*, mypoInput);
		MEMVAR_SETGET(SetVehicleObject, VehicleObject, int, myiVehicleObject);
	//- [Updates] -
		MEMVAR_SETGET(SetUpdateValue, UpdateValue, LL_UPDATE, myiUpdateValue);
	//- [Misc.] -
		void Place(C_i2(iX, iY));
		MEMVAR_SETGET(SetLockedMember, LockedMember, int, myiLockedMember);
	//- [Running] -
		virtual bool Move(ASFC_DIRECTION iDirection);
		void ChangeVehicle(int iVehicle);
	//- [Party Members] -
		MEMVAR_GETREF(PartyMembers, ASFC_LinkedList<LL_PartyMember>, myloPartyMembers);
	//- [Torch Handeling] -
		MEMVAR_SETGET(SetTorchTurns, TorchTurns, int, myiTorchTurns);
 	
 	protected:
 	//P- [Running] -P
 		void MoveViewports(ASFC_DIRECTION iDirection);	//Moves various viewports so we focus on the player
 		ASFC_DIRECTION  PromptDirection();				//Returns a direction based on what key is down
 		bool TalkTo(ASFC_DIRECTION iDirection);			//Talks to the unit in iDirection
 		bool LookTo(ASFC_DIRECTION iDirection);			//Looks to the unit or terrain in iDirection
 		bool PushTo(ASFC_DIRECTION iDirection);
 		bool SearchTo(ASFC_DIRECTION iDirection);
 		bool AttackTo(ASFC_DIRECTION iDirection);
 		bool GetTo(ASFC_DIRECTION iDirection);
		bool ClimbTo(ASFC_DIRECTION iDirection);
 	//Vars
 		ASFC_Input*		mypoInput;
 		ASFC_Console*	mypoCon;
		ASFC_Surface*	mypoScreen;
 		LL_UPDATE myiUpdateValue;
 		ASFC_LinkedList<LL_PartyMember> myloPartyMembers;
 		int myiLockedMember;
		int myiVehicleObject;
		int myiTorchTurns;
	//Const	
		static const int TORCH_LENGTH = 150;
		static const SDLKey KEY_MOVE_NORTH = SDLK_UP;
		static const SDLKey KEY_MOVE_SOUTH = SDLK_DOWN;
		static const SDLKey KEY_MOVE_WEST  = SDLK_LEFT;
		static const SDLKey KEY_MOVE_EAST  = SDLK_RIGHT;
		static const SDLKey KEY_PASS  	   = SDLK_SPACE;
		static const SDLKey KEY_BOARD	   = SDLK_b;
		static const SDLKey KEY_EXIT	   = SDLK_x;
		static const SDLKey KEY_IGNITE	   = SDLK_i;
		static const SDLKey KEY_TALK  	   = SDLK_t;
		static const SDLKey KEY_LOOK  	   = SDLK_l;
		static const SDLKey KEY_PUSH  	   = SDLK_p;
		static const SDLKey KEY_SEARCH 	   = SDLK_s;
		static const SDLKey KEY_ATTACK	   = SDLK_a;
		static const SDLKey KEY_GET		   = SDLK_g;
		static const SDLKey KEY_USE		   = SDLK_u;
		static const SDLKey KEY_CLIMB	   = SDLK_k;
		static const SDLKey KEY_ZSTATS	   = SDLK_z;
		static const SDLKey KEY_READY	   = SDLK_r;
		static const SDLKey KEY_HELP	   = SDLK_h;
		static const SDLKey KEY_HELP2	   = SDLK_F1;
		static const SDLKey KEY_QUIT	   = SDLK_ESCAPE;
		static const SDLKey KEY_ONKEY_W	   = SDLK_w;
		static const SDLKey KEY_ONKEY_E	   = SDLK_e;
		static const SDLKey KEY_ONKEY_Y	   = SDLK_y;
		static const SDLKey KEY_ONKEY_O	   = SDLK_o;
		static const SDLKey KEY_ONKEY_D	   = SDLK_d;
		static const SDLKey KEY_ONKEY_F	   = SDLK_f;
		static const SDLKey KEY_ONKEY_J	   = SDLK_j;
		static const SDLKey KEY_ONKEY_C	   = SDLK_c;
		static const SDLKey KEY_ONKEY_V	   = SDLK_v;
		static const SDLKey KEY_ONKEY_N	   = SDLK_n;
		static const SDLKey KEY_ONKEY_M	   = SDLK_m;
};

//Now ending player.h
	#endif
