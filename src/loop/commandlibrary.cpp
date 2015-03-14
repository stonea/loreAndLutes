/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cCommandLibrary
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "commandlibrary.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cCommandLibrary
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_CommandLibrary::LOOP_CommandLibrary()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_CommandLibrary::ClearCommands()
{	//Simply resize the vector to zero
		myloCommands.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_CommandLibrary::AddCommand(LOOP_Command &oCommand)
{	//Add this new command
		myloCommands.push_back(oCommand);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_CommandLibrary::SearchForCommand(string sIdentifier)
{	//Loop through all of our commands
		for(int i = 0; i < myloCommands.size(); i++)
		{	//If this command maches in identifier
				if(myloCommands[i].Identifier() == sIdentifier)
				{	//Return it
						return(i);
				}
		}
		
	//If execution gets here we have an error
		return(UNKNOWN_COMMAND);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Command* LOOP_CommandLibrary::GetCommand(int iCommandNum)
{	return(&myloCommands[iCommandNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_CommandLibrary::NumCommands()
{	return(myloCommands.size());
}
