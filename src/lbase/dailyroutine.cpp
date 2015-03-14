/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			dailyroutine.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "dailyroutine.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_DailyRoutine
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_DailyRoutine::LL_DailyRoutine()
	: myiCurrentInstruction(NO_INSTRUCTION)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_DailyRoutine::Save(ofstream &oFile)
{	//%Num Instructions%
		oFile << Val(NumInstructions()) << " ";
	//<Looop for # of instructs>
		for(int i = 0; i < NumInstructions(); i++)
		{	//%Command%
				oFile << Val(mylRoutineInstructions[i].myiCommand) << " ";
	  		//%X%, %Y%
	  			oFile << Val(mylRoutineInstructions[i].myiXParam) << " "
	  				  << Val(mylRoutineInstructions[i].myiYParam) << " ";
    		//%StartHr%, %StartMin%, %EndHr%, %EndMin%
    			oFile << Val(mylRoutineInstructions[i].myiStartTimeHr)  << " "
    				  << Val(mylRoutineInstructions[i].myiStartTimeMin) << " "
				      << Val(mylRoutineInstructions[i].myiEndTimeHr)    << " "
				      << Val(mylRoutineInstructions[i].myiEndTimeMin)   << " ";
     		//%Start Zone%
     			oFile << Val(mylRoutineInstructions[i].myfStartZone) << " ";
		}
	//" "
		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_DailyRoutine::Load(ifstream &oFile)
{	//Vars
		int iNumInstructions, iCommand;

	//%Num Instructions%
		oFile >> iNumInstructions;
		mylRoutineInstructions.resize(iNumInstructions);
	//<Looop for # of instructs>
		for(int i = 0; i < iNumInstructions; i++)
		{	//%Command%
				oFile >> iCommand;
    			mylRoutineInstructions[i].myiCommand = LL_DAILY_ROUTINE_COMMAND(iCommand);
	  		//%X%, %Y%
	  			oFile >> mylRoutineInstructions[i].myiXParam
	  				  >> mylRoutineInstructions[i].myiYParam;
    		//%StartHr%, %StartMin%, %EndHr%, %EndMin%
    			oFile >> mylRoutineInstructions[i].myiStartTimeHr
    				  >> mylRoutineInstructions[i].myiStartTimeMin
				      >> mylRoutineInstructions[i].myiEndTimeHr
				      >> mylRoutineInstructions[i].myiEndTimeMin;
     		//%Start Zone%
     			oFile >> mylRoutineInstructions[i].myfStartZone;
		}
}
//------------------------------------------------------------------------------ [Instruction Handeling] -
LL_DailyRoutine::LL_DailyRoutineInstruction& LL_DailyRoutine::GetInstruction(int iTimeHr, int iTimeMin)
{	//Loop through all instructions
		for(int i = 0; i < NumInstructions(); i++)
		{	//If the instruction occurs during iTimeHr, iTimeMin
				if(	mylRoutineInstructions[i].myiStartTimeHr >= iTimeHr &&
					mylRoutineInstructions[i].myiEndTimeHr   <= iTimeHr)
				{	//Then if it lies in the correct minutes we've got our instruction!
						if(	mylRoutineInstructions[i].myiStartTimeMin >= iTimeMin &&
							mylRoutineInstructions[i].myiEndTimeMin   <= iTimeMin)
						{
							return(mylRoutineInstructions[i]);
						}
				}
		}
		
	//Otherwise just formulate a blank one and return that
		LL_DailyRoutineInstruction oBlankInstruct;
		return(oBlankInstruct);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_DailyRoutine::AddInstruction(LL_DailyRoutineInstruction oRoutineInstruction)
{	//Push back this instruct
		mylRoutineInstructions.push_back(oRoutineInstruction);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_DailyRoutine::ClearInstructions()
{	//Remove all instructs
		mylRoutineInstructions.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_DailyRoutine::DeleteInstruction(int iNum)
{	//Remove this instruction
		mylRoutineInstructions.erase(mylRoutineInstructions.begin() + iNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_DailyRoutine::NumInstructions()
{	//Return the number o' instructs
		return(mylRoutineInstructions.size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_DailyRoutine::LL_DailyRoutineInstruction& LL_DailyRoutine::GetInstruction(int iNum)
{	return(mylRoutineInstructions[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_DailyRoutine::Update(LL_GameClock* poGameClock)
{	//Vars
		int iOldInstruction = myiCurrentInstruction;

	//Find the current instruction
		myiCurrentInstruction = NO_INSTRUCTION;
		for(int i = 0; i < NumInstructions() && myiCurrentInstruction == NO_INSTRUCTION; i++)
		{	if(	poGameClock->Hour() * 60 + poGameClock->Minute() >=
				mylRoutineInstructions[i].myiStartTimeHr * 60 + 
	  			mylRoutineInstructions[i].myiStartTimeMin &&
				poGameClock->Hour() * 60 + poGameClock->Minute() <=
    			mylRoutineInstructions[i].myiEndTimeHr * 60 + 
				mylRoutineInstructions[i].myiEndTimeMin)
				{
					myiCurrentInstruction = i;
				}
		}

	//If the current instruction has changed update
		if(myiCurrentInstruction != iOldInstruction)
			return true;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_DailyRoutine::LL_DailyRoutineInstruction& LL_DailyRoutine::GetCurrentInstruction()
{	return(mylRoutineInstructions[myiCurrentInstruction]);
}
