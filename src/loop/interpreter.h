/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cInterpreter
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef INTERPRETER_H_
	#define INTERPRETER_H_
	
//Aggregates
	#include "commandlibrary.h"
	#include "callbacklibrary.h"
	#include "instanceset.h"
	#include "classlibrary.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cInterpreter
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Interpreter
{	public:
	//- [Constuctors] -
 		LOOP_Interpreter();
 		
	//- [Libraries and sets] -
		MEMVAR_SETGET(SetCommandLibrary,	CommandLibrary,		LOOP_CommandLibrary*,	mypoCommands );
		MEMVAR_SETGET(SetCallbackLibrary,	CallbackLibrary,	LOOP_CallbackLibrary*,	mypoCallbacks);
		MEMVAR_SETGET(SetInstanceSet,		InstanceSet,		LOOP_InstanceSet*,		mypoInstances);
		MEMVAR_SETGET(SetClassSet,			ClassSet,			LOOP_ClassLibrary*,		mypoClassSet);
		
	//- [Running] -
		void Run(int 	iObject);
		void Run(string sObject);
 	
 	private:
 	//Vars
 		LOOP_CommandLibrary*	mypoCommands;
 		LOOP_CallbackLibrary*	mypoCallbacks;
 		LOOP_InstanceSet*		mypoInstances;
 		LOOP_ClassLibrary*		mypoClassSet;
};

//Now ending interpreter.h
	#endif
