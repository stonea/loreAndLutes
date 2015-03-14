/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			transport.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_TRANSPORT_H_
#define LL_TRANSPORT_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "unit.h"
//Dependencies
	#include "terrainmap.h"
	#include <asfc/utils.h>
	#include "inventory.h"
	#include "itemset.h"
	#include <asfc/console.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_Transport
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Transport : public LL_Unit
{	public:
	//- [Constuctors] -
 		LL_Transport();
	//- [File I/O] -
		void Save(ofstream &oFile);
		bool Load(ifstream &oFile, string sGraphicsDir);
	//- [Data] -
		MEMVAR_SETGET(SetRoomNum, RoomNum, int, myiRoomNum);
		MEMVAR_SETGET(SetTransportX,			TransportX,				int, myiTransportX);
		MEMVAR_SETGET(SetTransportY,			TransportY,				int, myiTransportY);
		MEMVAR_SETGET(SetEffect,				Effect, 				LL_BORDER_EFFECT, myiEffect);
		MEMVAR_SETGET(SetTransportIfPlayerOn,	TransportIfPlayerOn,	int, myfTransportIfPlayerOn);
		MEMVAR_SETGET(SetTransportIfTalk,		TransportIfTalk,		int, myfTransportIfTalk);
		MEMVAR_SETGET(SetTransportIfLook,		TransportIfLook,		int, myfTransportIfLook);
		MEMVAR_SETGET(SetTransportIfPush,		TransportIfPush,		int, myfTransportIfPush);
		MEMVAR_SETGET(SetTransportIfSearch,		TransportIfSearch,		int, myfTransportIfSearch);
		MEMVAR_SETGET(SetTransportIfAttack,		TransportIfAttack,		int, myfTransportIfAttack);
	//- [Callbacks] -
		void Run();
		void Talk();
		void Look();
		bool Push();
		void Search();
		void Attack();
		void Init();
		void Seen();
		void PlayerOn();

 	private:
	//Vars
		int myiRoomNum, myiTransportX, myiTransportY;
		LL_BORDER_EFFECT myiEffect;
		bool myfTransportIfPlayerOn, myfTransportIfTalk, myfTransportIfLook, myfTransportIfPush,
			 myfTransportIfSearch, myfTransportIfAttack;
};

#endif
