/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			eventqueue.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "eventqueue.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_EventQueue
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_EventQueue::LL_EventQueue()
{
}
//------------------------------------------------------------------------------------- [Event deleting] -
void LL_EventQueue::DeleteGosubCall()
{	//Loop through all events
		for(int i = 0; i < myoEventQueue.Length(); i++)
		{	//If this is a global call event delete it
				if(myoEventQueue[i].myiType == EVENT_GOSUB_GLOBAL)
				{	myoEventQueue.Delete(i);
    				return;
				}
		}
}
//--------------------------------------------------------------------------------------- [Event adding] -
void LL_EventQueue::String()
{	cerr << "Events: ";
	for(int i = 0; i < myoEventQueue.Length(); i++)
	{	myoEventQueue[i];
	}
	cerr << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Talk(int iSeg, int iOff,   int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_TALK;
	toEvent.myiCallingSeg = iSeg;
 	toEvent.myiCallingOff = iOff;
	toEvent.myiParam1 = iX;
 	toEvent.myiParam2 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Look(int iSeg, int iOff,   int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_LOOK;
	toEvent.myiCallingSeg = iSeg;
 	toEvent.myiCallingOff = iOff;
	toEvent.myiParam1 = iX;
 	toEvent.myiParam2 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Push(int iSeg, int iOff,   int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_PUSH;
	toEvent.myiCallingSeg = iSeg;
 	toEvent.myiCallingOff = iOff;
	toEvent.myiParam1 = iX;
 	toEvent.myiParam2 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Search(int iSeg, int iOff, int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_SEARCH;
	toEvent.myiCallingSeg = iSeg;
 	toEvent.myiCallingOff = iOff;
	toEvent.myiParam1 = iX;
 	toEvent.myiParam2 = iY;
	
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Attack(int iSeg, int iOff, int iX, int iY, int iAttack, int iTerrain)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_ATTACK;
	toEvent.myiCallingSeg = iSeg;
 	toEvent.myiCallingOff = iOff;
	toEvent.myiParam1 = iX;
 	toEvent.myiParam2 = iY;
	toEvent.myiParam3 = iAttack;
	toEvent.myiParam4 = iTerrain;
	
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Get(int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_GET;
	toEvent.myiParam1 = iX;
 	toEvent.myiParam2 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Use()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_USE;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::GoMapNorth()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_GO_MAP_NORTH;
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::GoMapSouth()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_GO_MAP_SOUTH;
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::GoMapWest()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_GO_MAP_WEST;
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::GoMapEast()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_GO_MAP_EAST;
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::GoMap(int iMap, int iEffect, int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_GO_MAP;
	toEvent.myiParam1 = iMap;
 	toEvent.myiParam2 = iEffect;
 	toEvent.myiParam3 = iX;
 	toEvent.myiParam4 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::ZStats()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_ZSTATS;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Ready()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_READY;
	
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Escape(int iNum)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_ESCAPE;
	toEvent.myiParam1 = iNum;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::QuickEscape()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_QUICK_ESCAPE;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::EscapeMonster(int iOffset)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_ESCAPE_MONSTER;
	toEvent.myiParam1 = iOffset;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::MoveTo(int iPlayerNum, int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_MOVETO;
	toEvent.myiParam1 = iPlayerNum;
	toEvent.myiParam2 = iX;
	toEvent.myiParam3 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::SelectPlayer(int iPlayerNum)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_MOVETO;
	toEvent.myiParam1 = iPlayerNum;
	
	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::PlotMonsterChest(int iMonsterNum, int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_PLOT_MONSTER_CHEST;
	toEvent.myiParam1 = iMonsterNum;
	toEvent.myiParam2 = iX;
	toEvent.myiParam3 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::PlotMonsterGuts(int iMonsterNum, int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_PLOT_MONSTER_GUTS;
	toEvent.myiParam1 = iMonsterNum;
	toEvent.myiParam2 = iX;
	toEvent.myiParam3 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::GosubGlobal(string sLabel)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_GOSUB_GLOBAL;
	toEvent.mysParam1 = sLabel;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Call(string sInstance, string sLabel, int iCallingUnitOffset)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_CALL;
	toEvent.mysParam1 = sInstance;
	toEvent.mysParam2 = sLabel;
	toEvent.myiParam1 = iCallingUnitOffset;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::CallPosition(int iX, int iY, int iCallingUnitOffset, string sInstance)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_CALL_POSITION;
	toEvent.myiParam1 = iX;
	toEvent.myiParam2 = iY;
	toEvent.myiParam3 = iCallingUnitOffset;
	toEvent.mysParam1 = sInstance;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Ping(string sLabel)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_PING;
	toEvent.mysParam1 = sLabel;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::PingClass(string sClass, string sLabel)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_PING_CLASS;
	toEvent.mysParam1 = sClass;
	toEvent.mysParam2 = sLabel;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::PingClassDeriv(string sClass, string sLabel)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_PING_CLASS_DERIV;
	toEvent.mysParam1 = sClass;
	toEvent.mysParam2 = sLabel;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Help()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_HELP;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::BoardVehicle(int iX, int iY)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_BOARD_VEHICLE;
	toEvent.myiParam1 = iX;
	toEvent.myiParam2 = iY;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::DeboardVehicle()
{	LL_Event toEvent;
	toEvent.myiType = EVENT_DEBOARD_VEHICLE;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::ReDrawMap(int iOff)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_REDRAW_MAP;
	toEvent.myiParam1 = iOff;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Lighting(bool fOn, int iOff)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_LIGHTING;
	if(fOn)	toEvent.myiParam1 = 1;
	else	toEvent.myiParam1 = 0;
	toEvent.myiParam2 = iOff;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::DoEffect(int iEffectNum, int iOff)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_DO_EFFECT;
	toEvent.myiParam1 = iEffectNum;
	toEvent.myiParam2 = iOff;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::DeEffectWithImage(int iEffectNum, int iOff, int iX, int iY, string sImage)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_DO_EFFECT_WITH_IMAGE;
	toEvent.myiParam1 = iX;
	toEvent.myiParam2 = iY;
	toEvent.myiParam3 = iEffectNum;
	toEvent.myiParam4 = iOff;
	toEvent.mysParam1 = sImage;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::SwitchUnits(int iSeg1, int iOff1, int iSeg2, int iOff2)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_SWITCH_UNITS;
	toEvent.myiParam1 = iSeg1;
	toEvent.myiParam2 = iOff1;
	toEvent.myiParam3 = iSeg2;
	toEvent.myiParam4 = iOff2;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::CallUnitsUnder(string sLabel, int iX, int iY, int iL)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_CALL_UNITS_UNDER;
	toEvent.mysParam1 = sLabel;
	toEvent.myiParam1 = iX;
	toEvent.myiParam2 = iY;
	toEvent.myiParam3 = iL;

	myoEventQueue.Push(toEvent);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Sleep(int iHours, int iChance, int iAmount)
{	LL_Event toEvent;
	toEvent.myiType = EVENT_SLEEP;
	toEvent.myiParam1 = iHours;
	toEvent.myiParam2 = iChance;
	toEvent.myiParam3 = iAmount;

	myoEventQueue.Push(toEvent);
}
//---------------------------------------------------------------------------------------------- [Queue] -
int LL_EventQueue::NumEvents()
{	return(myoEventQueue.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_EventQueue::LL_Event LL_EventQueue::GetEvent()
{	LL_Event toEvent;
	toEvent = myoEventQueue[0];
	myoEventQueue.Delete(0);
	
	return toEvent;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_EventQueue::Clear()
{	myoEventQueue.Resize(0);
}
