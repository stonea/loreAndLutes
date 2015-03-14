/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Callback
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "callback.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Callback
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Callback::LOOP_Callback()
{
}
//-------------------------------------------------------------------------------------------- [Calling] -
void LOOP_Callback::Run(LOOP_Info* poInfo)
{	//Simply run it!
		mypFunction(*poInfo, mypObj);
}
//------------------------------------------------------------------------------------ [Setting\Getting] -
void LOOP_Callback::SetFunction(void (*pFunction)(LOOP_Info, void*))
{	mypFunction = pFunction;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Callback::SetObject(void* pObject)
{	mypObj = pObject;
}
