/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			scriptedunit.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A creature who is controlled through a LOOP class.
*/
#ifndef LL_SCRIPTEDUNIT_H_
#define LL_SCRIPTEDUNIT_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "creature.h"
//Realizes
	#include <loop/loop.h>
	#include "looplib_loreinfo.h"
//Aggregates
	#include "dailyroutine.h"
	#include <asfc/input.h>
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_ScriptedUnit
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_ScriptedUnit : public LL_Creature
{	public:
	//- [Constuctors] -
 		LL_ScriptedUnit();
//		LL_ScriptedUnit(LL_ScriptedUnit oCopy);
//		LL_ScriptedUnit& LL_ScriptedUnit::operator=(LL_ScriptedUnit oCopy);
 		MEMVAR_SETGET(SetLOOP, 		LOOP, 		LOOP_LOOP*, 			mypoLOOP);
 		MEMVAR_SETGET(SetLibInfo,	LibInfo,	LL_LOOPLib_LoreInfo*,	mypoLibInfo);
		
	//- [File I/O] -
		void 	Save(ofstream &oFile);
		void	Load(ifstream &oFile, string sGraphicsDir);
		virtual void SaveRecordingInfo(ofstream &oFile);
		virtual bool LoadRecordingInfo(ifstream &oFile, string sGraphicsDir);
		virtual bool LoadRecordingInfoVars(ifstream &oFile, string sGraphicsDir);
	//- [Callbacks] -
		void Run();
		void Talk();
		void Look();
		bool Push();
		void Search();
		void Attack();
		void Init();
		void Gosub(string sLabel);
		void Seen();
		void PlayerOn();
	//- [LOOP Script Linking] -
		MEMVAR_SETGET(SetClass,		 Class,			string, mysClass);
	//- [Default Variable Adding\Setting] -
		void SetDefaultString(string sIdentifier, string	sValue);
		void SetDefaultInt   (string sIdentifier, int		iValue);
		void SetDefaultFloat (string sIdentifier, double	dValue);
		string DefaultString(string sIdentifier);
		int    DefaultInt   (string sIdentifier);
		double DefaultFloat (string sIdentifier);
		MEMVAR_GETREF(DefaultStrings,		ASFC_LinkedList<string>, mylsDefaultStrings);
		MEMVAR_GETREF(DefaultStringsValues,	ASFC_LinkedList<string>, mylsDefaultStringsValues);
		MEMVAR_GETREF(DefaultInts,			ASFC_LinkedList<string>, mylsDefaultInts);
		MEMVAR_GETREF(DefaultIntsValues,	ASFC_LinkedList<int>, 	 myliDefaultIntsValues);
		MEMVAR_GETREF(DefaultFloats,		ASFC_LinkedList<string>, mylsDefaultFloats);
		MEMVAR_GETREF(DefaultFloatsValues,	ASFC_LinkedList<double>, myldDefaultFloatsValues);
	//- [Route AI] -
		MEMVAR_GETREF(DailyRoutine, LL_DailyRoutine, myoDailyRoutine);
	//- [Ops] -
		LL_ScriptedUnit& operator=(LL_ScriptedUnit oRHS);
	
 	protected:
	//P- [LOOP Script Linking] -P
 		void ReadyForLOOP();
		void SetDefaults();
	//P- [Route AI] -P
		void UpdateRoutineAI();
	
 	//Const
 		#define LL_ScriptedUnit__LABEL_TALK "TALK"	//String constant holding label to call when the player "talks" to this unit
 		#define LL_ScriptedUnit__LABEL_LOOK "LOOK"
 		#define LL_ScriptedUnit__LABEL_PUSH "PUSH"
 		#define LL_ScriptedUnit__LABEL_SEARCH "SEARCH"
 		#define LL_ScriptedUnit__LABEL_ATTACK "ATTACk"
 		#define LL_ScriptedUnit__LABEL_INIT   "INIT"
 		#define LL_ScriptedUnit__LABEL_SEEN   "SEEN"
 		#define LL_ScriptedUnit__LABEL_PLAYERON "PLAYERON"
 	//Vars
 		string mysClass;
 		LOOP_LOOP*				mypoLOOP;
 		LL_LOOPLib_LoreInfo*	mypoLibInfo;
		ASFC_LinkedList<string> mylsDefaultStrings;
		ASFC_LinkedList<string> mylsDefaultStringsValues;
		ASFC_LinkedList<string> mylsDefaultInts;
		ASFC_LinkedList<int> 	myliDefaultIntsValues;
		ASFC_LinkedList<string> mylsDefaultFloats;
		ASFC_LinkedList<double> myldDefaultFloatsValues;
		LL_DailyRoutine			myoDailyRoutine;
		ASFC_Input				myoInput;
};

//Now ending scriptedunit.h
	#endif
