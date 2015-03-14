/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Command
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "command.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Command
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Command::LOOP_Command()
{
}
//------------------------------------------------------------------------------- [Identifier Handeling] -
void LOOP_Command::SetIdentifier(string sIdentifier)
{	mysIdentifier = UpperString(sIdentifier);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetIdentifier, Identifier, string, mysIdentifier);
//------------------------------------------------------------------------------------ [Param Handeling] -
//MEMVAR_SETGET(SetParamsToRecieve, ParamsToRecieve, cParamMap, myoParamsToRecieve)
void LOOP_Command::ClearParams()
{	myoParamsToRecieve.Clear();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Command::NewParam(eParam iWhat)
{	myoParamsToRecieve.New(iWhat);
}
//--------------------------------------------------------------------------------- [Callback Handeling] -
//MEMVAR_SETGET(SetCallbackIdentifier, CallbackIdentifier, int, myiCallbackIdentifier)		
//-------------------------------------------------------------------------------- [Parameter Handeling] -
int LOOP_Command::NumParams()
{	return(myoParamsToRecieve.NumParams());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
eParam	LOOP_Command::GetParam(int iParamNum)
{	return(myoParamsToRecieve.Param(iParamNum));
}
