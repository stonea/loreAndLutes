/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Command
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef COMMAND_H_
	#define COMMAND_H_

//Foundation
	#include <string>
	#include <asfc/utils.h>

//Aggregates
	#include "parammap.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Command
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Command
{	public:
	//- [Constuctors] -
 		LOOP_Command();
 		
	//- [Identifier Handeling] -
		void SetIdentifier(string sIdentifier);
		MEMVAR_GET(Identifier, string, mysIdentifier);
	
	//- [Param Handeling] -
		MEMVAR_SETGET(SetParamsToRecieve, ParamsToRecieve, LOOP_ParamMap, myoParamsToRecieve);
		void 	ClearParams();
		void 	NewParam(eParam iWhat);
		eParam	GetParam(int iParamNum);
	
	//- [Callback Handeling] -
		MEMVAR_SETGET(SetCallbackIdentifier, CallbackIdentifier, int, myiCallbackIdentifier);
		
	//- [Parameter Handeling] -
		int NumParams();
 	
 	private:
 	//Vars
		string			mysIdentifier;
		LOOP_ParamMap	myoParamsToRecieve;
		int				myiCallbackIdentifier;
};

//Now ending command.h
	#endif
