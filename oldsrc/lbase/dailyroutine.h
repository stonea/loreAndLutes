/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			dailyroutine.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A dailyroutine describes how a scripted unit will move throughout the course
				 of a day.
*/
#ifndef LL_DAILYROUTINE_H_
#define LL_DAILYROUTINE_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Dependencies
	#include <fstream>
	#include <vector>
	#include <asfc/utils.h>
	#include "gameclock.h"
	using namespace std;

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_DailyRoutine
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_DailyRoutine
{	public:
	//Type
		static const int NO_INSTRUCTION = -1;
	
		enum LL_DAILY_ROUTINE_COMMAND
		{	LL_DAILY_ROUTINE_COMMAND_MOVE = 0,
			LL_DAILY_ROUTINE_COMMAND_FIELD,
			LL_DAILY_ROUTINE_COMMAND_IDLE
		};
		
		struct LL_DailyRoutineInstruction
		{	LL_DAILY_ROUTINE_COMMAND	myiCommand;
			int myiXParam, myiYParam;
			int myiStartTimeHr, myiStartTimeMin, myiEndTimeMin, myiEndTimeHr;
			bool myfStartZone;
			
			LL_DailyRoutineInstruction::LL_DailyRoutineInstruction()
			{	myiCommand = LL_DAILY_ROUTINE_COMMAND_IDLE;
				myiXParam = -1;
    			myiYParam = -1;
				myiStartTimeHr  = -1;
    			myiStartTimeMin = -1;
       			myiEndTimeMin   = -1;
          		myiEndTimeHr    = -1;
				myfStartZone    = true;
			}
		};

	//- [Constuctors] -
 		LL_DailyRoutine();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);
	//- [Instruction Handeling] -
		LL_DailyRoutineInstruction& GetInstruction(int iTimeHr, int iTimeMin);
		void AddInstruction(LL_DailyRoutineInstruction oRoutineInstruction);
		void ClearInstructions();
		void DeleteInstruction(int iNum);
		int  NumInstructions();
		LL_DailyRoutineInstruction& GetInstruction(int iNum);
		bool Update(LL_GameClock* poGameClock);
		LL_DailyRoutineInstruction& GetCurrentInstruction();
		MEMVAR_GET(CurrentInstructionNum, int, myiCurrentInstruction);
 		
	protected:
	//Vars
		vector<LL_DailyRoutineInstruction> mylRoutineInstructions;
		int myiCurrentInstruction;
};

#endif
