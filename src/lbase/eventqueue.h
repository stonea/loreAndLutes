/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			eventqueue.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: An event queue is a list of events that the LL_Run engine should execute.
*/
#ifndef LL_EVENTQUEUE_H_
#define LL_EVENTQUEUE_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include <asfc/linkedlist.h>
	#include <string>
//Dependencies
	#include <iostream>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_EventQueue
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_EventQueue
{	public:
	//Type
		enum EVENT_TYPE
		{	EVENT_TALK = 1,		//iP1 = X Location, iP2 = Y Location
			EVENT_LOOK,		//iP1 = X Location, iP2 = Y Location
			EVENT_PUSH,		//iP1 = X Location, iP2 = Y Location
			EVENT_SEARCH,	//iP1 = X Location, iP2 = Y Location
			EVENT_ATTACK,	//In OM: iP1 = X Location, iP2 = y Location, iP3 = Monster Number
							//In BM: iP1 = X Location, iP2 = Y Location, iP3 = Attack Value
			EVENT_GET,		//iP1 = X Location, iP2 = Y Location
			EVENT_USE,
			EVENT_GO_MAP_NORTH,
			EVENT_GO_MAP_SOUTH,
			EVENT_GO_MAP_WEST,
			EVENT_GO_MAP_EAST,
			EVENT_GO_MAP,	//iP1 = Map #, iP2 = Effect, iP3 = X-Local, iP4 = Y-Local
			EVENT_ZSTATS,
			EVENT_READY,
			EVENT_ESCAPE,	//iP1 = Player#
			EVENT_QUICK_ESCAPE,
			EVENT_ESCAPE_MONSTER,
			EVENT_MOVETO,	//iP1 = Player#, iP2 = X Local, iP3 = Y Local
			EVENT_SELECT_PLAYER,//iP1 = Player #
			EVENT_PLOT_MONSTER_CHEST, //iP1 = MonsterTemplateNum, iP2 = X, iP3 = Y
			EVENT_PLOT_MONSTER_GUTS, //iP1 = MonsterTemplateNum, iP2 = X, iP3 = Y
			EVENT_GOSUB_GLOBAL,  	//iSP1 = Call what
			EVENT_CALL,   			//iSP1 = Instance, iSP2 = Label, iP1 = Calling unit offset
			EVENT_CALL_POSITION,	//iP1  = iX, iP2 = iY, iP3 = Calling Unit Offset, sS1 = Label
			EVENT_PING,				//iSP1 = Label
			EVENT_PING_CLASS,		//iSP1 = Class, iSP2 = Label
			EVENT_PING_CLASS_DERIV,	//iSP1 = Class, iSP2 = Label
			EVENT_HELP,
			EVENT_BOARD_VEHICLE,	//iP1 = X, iP2 = Y
			EVENT_DEBOARD_VEHICLE,
			EVENT_REDRAW_MAP,
			EVENT_LIGHTING,				//iP1 = 0 for off else on
			EVENT_DO_EFFECT,			//iP1 = Effect #, iP2 = Offset
			EVENT_DO_EFFECT_WITH_IMAGE,	//iP1 = X, iP2 = Y, iP3 = Effect#, iP4 = Offset; sP1 = String
			EVENT_SWITCH_UNITS,			//iP1 = Unit1Seg, iP2 = Unit1Off, iP3 = Unit2Seg, iP3 = Unit2Off, 
			EVENT_CALL_UNITS_UNDER,		//iSP1 = Label, iP1 = X, iP2 = Y, iP3 = L
			EVENT_SLEEP					//iP1 = Hours, iP2 = Chance of heal\hour, iP3 = Heal amount
		};
		struct LL_Event
		{	EVENT_TYPE	myiType;
			int			myiCallingSeg, myiCallingOff;
			int			myiParam1, myiParam2, myiParam3, myiParam4;
			string		mysParam1, mysParam2;
		};

	//- [Constuctors] -
 		LL_EventQueue();
	//- [Event deleting] -
		void DeleteGosubCall();
	//- [Event adding] -
		void String();
		void Talk(int iSeg, int iOff,   int iX, int iY);
		void Look(int iSeg, int iOff,   int iX, int iY);
		void Push(int iSeg, int iOff,   int iX, int iY);
		void Search(int iSeg, int iOff, int iX, int iY);
		void Attack(int iSeg, int iOff, int iX, int iY, int iAttack = -1, int iTerrain = -1);
		void Get(int iX, int iY);
		void Use();
		void GoMapNorth();
		void GoMapSouth();
		void GoMapWest();
		void GoMapEast();
		void GoMap(int iMap, int iEffect, int iX, int iY);
		void ZStats();
		void Ready();
		void Escape(int iNum);
		void QuickEscape();
		void EscapeMonster(int iOffset);
		void MoveTo(int iPlayerNum, int iX, int iY);
		void SelectPlayer(int iPlayerNum);
		void PlotMonsterChest(int iMonsterNum, int iX, int iY);
		void PlotMonsterGuts(int iMonsterNum, int iX, int iY);
		void GosubGlobal(string sLabel);
		void Call(string sInstance, string sLabel, int iCallingUnitOffset);
		void CallPosition(int iX, int iY, int iCallingUnitOffset, string sInstance);
		void Ping(string sLabel);
		void PingClass(string sClass, string sLabel);
		void PingClassDeriv(string sClass, string sLabel);
		void Help();
		void BoardVehicle(int iX, int iY);
		void DeboardVehicle();
		void ReDrawMap(int iOff);
		void Lighting(bool fOn, int iOff);
		void DoEffect(int iEffectNum, int iOff);
		void DeEffectWithImage(int iEffectNum, int iOff, int iX, int iY, string sImage);
		void SwitchUnits(int iSeg1, int iOff1, int iSeg2, int iOff2);
		void CallUnitsUnder(string sLabel, int iX, int iY, int iL);
		void Sleep(int iHours, int iChance, int iAmount);
	//- [Queue] -
		int NumEvents();
		LL_Event GetEvent();
		void Clear();
		
	private:
	//Vars
		ASFC_LinkedList<LL_Event> myoEventQueue;
};

#endif
