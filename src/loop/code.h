/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Code
*/

//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Multiple inclusion protection:
	#ifndef CODE_H_
	#define CODE_H_
	
//Foundation
	#include <asfc/utils.h>

//Aggregates
	#include "parameters.h"
	#include "command.h"
	#include "parammap.h"
	#include "variables.h"

//��������������������������������������������������������������������������������������������������������
//												LOOP_Code
//��������������������������������������������������������������������������������������������������������
class LOOP_Code
{	public:
	//- [Constuctors] -
 		LOOP_Code();
 		
	//- [Command Handeling] -
		MEMVAR_SETGET(SetCommand,	 Command,    LOOP_Command*, mypoCommand);
	
	//- [Parameters Setting] -
		MEMVAR_SETGET(SetParameters, 	Parameters, 	LOOP_Parameters, myoParameters);
		MEMVAR_SETGET(SetParametersMap, ParametersMap, 	LOOP_ParamMap, 	 myoParamsPassed);
 	
 	private:
 	//Vars
 		LOOP_Command*	mypoCommand;
 		LOOP_Parameters	myoParameters;
 		LOOP_ParamMap	myoParamsPassed;
 		LOOP_Variables* mypoVariables;
};

//Now ending code.h
	#endif
