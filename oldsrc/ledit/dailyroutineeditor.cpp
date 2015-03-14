/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			dailyroutineeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "dailyroutineeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_DailyRoutineEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//--------------------------------------------------------------------------------------- [Construction] -
LEDIT_DailyRoutineEditor::LEDIT_DailyRoutineEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_DailyRoutineEditor::EditDailyRoutine(LL_DailyRoutine* poDailyRoutine)
{	//Map params
		mypoDailyRoutine = poDailyRoutine;
		
	//Setup keys
		int iKey;
		ASFC_LinkedList<int> lChoosers;
  		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
		lChoosers.Push(KEY_DELETE);
		lChoosers.Push(KEY_CANCEL);
		
	//Setup the editor
		DrawQuickKeys();
		Setup();
	
	//Now grab an option
		bool fNotDone = true;
		while(fNotDone)
		{	Setup();
			DrawQuickKeys();
			int iOption = GrabOption(&iKey, lChoosers);
			fNotDone = EditOption(iOption, iKey);
		}
}
//P----------------------------------------------------------------------------------------- [Editting] -P
void LEDIT_DailyRoutineEditor::Setup()
{	//Vars
		LL_DailyRoutine::LL_DailyRoutineInstruction toInstruction;
		string sTime;
		
	//Clear the old editor
		Reset(false);

	//Draw info
		Heading("                 Daily Routine Editor");
		Heading("===================================================");

	//Loop through all the commands, write the appropriate info
		for(int i = 0; i < mypoDailyRoutine->NumInstructions(); i++)
		{	//Get instruct
				toInstruction = mypoDailyRoutine->GetInstruction(i);
				sTime = Val(toInstruction.myiStartTimeHr) + ":" + Val(toInstruction.myiStartTimeMin) +
						"-" + Val(toInstruction.myiEndTimeHr) + ":" + Val(toInstruction.myiEndTimeMin);
  
  			//If a move
				if(toInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_MOVE)
				{	Option("Move       " + sTime + " to position: " + Val(toInstruction.myiXParam) +
    					   ", " + Val(toInstruction.myiYParam));
				}
			//If a region
				else if(toInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_FIELD)
					Option("Region     " + sTime + " to position: " + Val(toInstruction.myiXParam) +
    					   ", " + Val(toInstruction.myiYParam));
			//If idle
				else if(toInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_IDLE)
		  			Option("Idle       " + sTime);
		}
		
	//Display the <New Instruction> option
		Option("<New instruction>");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LEDIT_DailyRoutineEditor::EditOption(int i, int iKey)
{	//Vars
		LL_DailyRoutine::LL_DailyRoutineInstruction toInstruction;

	//If the key down is exit escape!!
		if(iKey == KEY_CANCEL)
		{	return false;
		}
	//If the key down is "choose" decide what to do based on the option
		else if(iKey == KEY_CHOOSE || iKey == KEY_CHOOSE2)
		{	//Edit option #i
				if(i >= 0 && i < mypoDailyRoutine->NumInstructions())
				{	toInstruction = mypoDailyRoutine->GetInstruction(i);
   	
    				//If this command is a move edit it as a move
						if(toInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_MOVE)
							EditInstruction(i, true);
					//If this command is a region edit it as a region
						else if(toInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_FIELD)
							EditInstruction(i, true);
					//If this command is an idle edit it as an idel
						else if(toInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_IDLE)
							EditInstruction(i, false);
					//Keep on edittin'
						return(true);
				}
			//Create a new instruction
				else if(i == mypoDailyRoutine->NumInstructions())
				{	//Vars
						LL_DailyRoutine::LL_DailyRoutineInstruction oInstruction;
					
					//Grab a new instruction, stash it into the instruct list
			   			oInstruction = NewInstruction();
			   			mypoDailyRoutine->AddInstruction(oInstruction);
		   				
					//Keep on edittin'
						return(true);
				}
		}
	//If the key was kill delete destroy wha ha ha ha!!!
		else if(iKey == KEY_DELETE)
		{	//If an instruction whose chosen delete it
				if(i >= 0 && i < mypoDailyRoutine->NumInstructions())
				{	mypoDailyRoutine->DeleteInstruction(i);
				}
				
			//Keep on truckin'... errr.. edittin'
				return(true);
		}

	//Else return to quit
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_DailyRoutine::LL_DailyRoutineInstruction LEDIT_DailyRoutineEditor::NewInstruction()
{	//Vars
		LL_DailyRoutine::LL_DailyRoutineInstruction	oInstruction;
		LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND iCommand;
		int iOpt;
		int iStartHr, iStartMin, iEndHr, iEndMin;
		int iX, iY;
		
	//First grab a command
		iCommand = PollForCommand();
		oInstruction.myiCommand = iCommand;
		
	//Space
		mypoPainter->MainConsole();
		
	//Ask for start and ending times
		AskTime("Enter the starting hour [0-24]:", "Enter the starting minute [0-59]:", &iStartHr, &iStartMin);
		AskTime("Enter the ending hour [0-24]:",   "Enter the ending minute [0-59]:",   &iEndHr,   &iEndMin);
		
	//Stash time info
		oInstruction.myiStartTimeHr		= iStartHr;
		oInstruction.myiStartTimeMin	= iStartMin;
		oInstruction.myiEndTimeHr		= iEndHr;
		oInstruction.myiEndTimeMin		= iEndMin;
		
	//If it was a move or region command ask for a position
		if(iCommand != LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_IDLE)
		{	//Pick a point and redraw
	  			mypoLocationPicker->PickPoint(&iX, &iY);
				DrawInit();
				DrawQuickKeys();
  			
			//Stash this info into the commmand
				oInstruction.myiXParam = iX;
				oInstruction.myiYParam = iY;
		}
		
	//Return da' instruction
		return(oInstruction);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND LEDIT_DailyRoutineEditor::PollForCommand()
{	//Vars
		LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND iCommand;
		int iOpt;
		
	//Clear the old editor
		Reset(false);

	//Draw info
		Heading("                 New Instruction Creator");
		Heading("===================================================");
		Heading("Choose one:");
		Option("Move to position");
		Option("Move randomley in field");
		Option("Idle");
		
	//Grab an option
		iOpt = GrabOption();
		
	//Formulate this option into a routine command
			 if(iOpt == 0)	iCommand = LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_MOVE;
		else if(iOpt == 1)	iCommand = LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_FIELD;
		else				iCommand = LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_IDLE;
		
	//Return the command
		return(iCommand);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_DailyRoutineEditor::AskTime(string sMsgHr, string sMsgMin, int* piHr, int* piMin)
{	//Ask for hour (0-24)
		mypoPainter->MainConsole() << "\n";
		(*piHr) = GrabIntWithoutAClear(sMsgHr, 0, 24);
		
	//Ask for minute (0-59)
		mypoPainter->MainConsole() << "\n";
		(*piMin) = GrabIntWithoutAClear(sMsgMin, 0, 59);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_DailyRoutineEditor::EditInstruction(int i, bool fLocation)
{	//Vars
		LL_DailyRoutine::LL_DailyRoutineInstruction toInstruction = mypoDailyRoutine->GetInstruction(i);
		int iOpt = 0;
		int iX, iY;

	//While the user hasn't exitted
		while(iOpt != CONSOLEEDIT_NONE)
		{	//Clear the old editor
				Reset(false);

			//Draw info
				Heading("         Edit Daily Routine Instruction");
				Heading("===================================================");
				Option("Start Hour   " + Val(toInstruction.myiStartTimeHr));
		  		Option("Start Minute " + Val(toInstruction.myiStartTimeMin));
		  		Option("End Hour     " + Val(toInstruction.myiEndTimeHr));
		  		Option("End Minute   " + Val(toInstruction.myiEndTimeMin));
		  		if(fLocation)
					Option("Move to      " + Val(toInstruction.myiXParam) + ", " + Val(toInstruction.myiYParam));
		
			//Grab an option
				iOpt = GrabOption();
		
			//Decide what to do based on the option
				//Start Hour
					if(iOpt == 0)
	  					toInstruction.myiStartTimeHr = GrabInt("Enter the new start hour [0-24]", 0, 24);
				//Start Minute
					else if(iOpt == 1)
	  					toInstruction.myiStartTimeMin = GrabInt("Enter the new start min [0-59]", 0, 59);
				//End hour
					else if(iOpt == 2)
	  					toInstruction.myiEndTimeHr = GrabInt("Enter the new end hour [0-24]", 0, 24);
				//End Minute
					else if(iOpt == 3)
	  					toInstruction.myiEndTimeMin = GrabInt("Enter the new end min [0-59]", 0, 59);
				//Move to
					else if(iOpt == 4 && fLocation)
					{	//Pick a point and redraw
							mypoLocationPicker->SetStartLocation(toInstruction.myiXParam,
       															 toInstruction.myiYParam);
				  			mypoLocationPicker->PickPoint(&iX, &iY);
							DrawInit();
							DrawQuickKeys();
  			
						//Stash this info into the commmand
							toInstruction.myiXParam = iX;
							toInstruction.myiYParam = iY;
					}
		}
		
	//Save changes
		mypoDailyRoutine->GetInstruction(i) = toInstruction;
}
