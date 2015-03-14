/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cCommandLibrary
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef COMMANDLIBRARY_H_
	#define COMMANDLIBRARY_H_

//Foundation
	#include <vector>

//Aggragates
	#include "command.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cCommandLibrary
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_CommandLibrary
{	public:
	//- [Constuctors] -
 		LOOP_CommandLibrary();
 		
	//- [Command Handeling] -
		static const int UNKNOWN_COMMAND = -1;
		void 			ClearCommands();
		void 			AddCommand(LOOP_Command &oCommand);
		int				SearchForCommand(string sIdentifier);
		LOOP_Command*	GetCommand(int iCommandNum);
		int				NumCommands();
 	
 	private:
	//Vars
 		vector<LOOP_Command> myloCommands;
};

//Now ending commandlibrary.h
	#endif
