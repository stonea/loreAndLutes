/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			unit.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A unit is an abstract class from which creatures and items derive. Units are contained
				 in a unit set;
*/
#ifndef LL_UNIT_H_
#define LL_UNIT_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "mapobject.h"
//Realizes
	#include "eventqueue.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Unit
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Unit : public LL_MapObject
{	public:
	//Const
		static const int NULL_SEG   = 0xFF;
		static const int NULL_OFF   = -1;
		static const int NULL_X     = -1;
		static const int NULL_Y     = -1;
		static const int NULL_LAYER = -1;

	//- [Constuctors] -
 		LL_Unit();
	//- [File I/O] -
 		virtual void SaveRecordingInfo(ofstream &oFile);
		virtual bool LoadRecordingInfo(ifstream &oFile);
	//- [Callbacks] -
		virtual void Run();
		virtual void Talk();
		virtual void Look();
		virtual bool Push();
		virtual void Search();
		virtual void Attack();
	//- [Data] -
		MEMVAR_SETGET(SetIdentifier, Identifier, string, mysIdentifier);
 		MEMVAR_SETGET(SetSeg, Seg,  Uint8, myiIdentifierSeg);
 		MEMVAR_SETGET(SetOff, Off,  int,   myiIdentifierOff);
 		MEMVAR_SET(SetX, Uint8, myiX);
		MEMVAR_GET(X, int, int(myiX));
 		MEMVAR_SET(SetY, Uint8, myiY);
		MEMVAR_GET(Y, int, int(myiY));
 		MEMVAR_SETGET(SetLayer, Layer, Uint8, myiLayer);
 		MEMVAR_SETGET(Null,   Null, bool,  myfNullify);
 		MEMVAR_SETGET(SetWeight, Weight, int, myiWeight);
 		MEMVAR_SETGET(SetEventQueue, EventQueue, LL_EventQueue*, mypoEventQueue);
 	
 	protected:
 	//Vars
 		string	mysIdentifier;
		Uint8	myiIdentifierSeg;
		int		myiIdentifierOff;
		Uint8	myiX, myiY, myiLayer;
		bool	myfNullify;
		int		myiWeight;
		LL_EventQueue* mypoEventQueue;
};

#endif
