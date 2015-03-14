/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_CallbackLibrary
*/

//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Associated Header:
	#include "callbacklibrary.h"
	
//��������������������������������������������������������������������������������������������������������
//												LOOP_CallbackLibrary
//��������������������������������������������������������������������������������������������������������
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_CallbackLibrary::LOOP_CallbackLibrary()
{
}
//--------------------------------------------------------------------------------- [Callback Handeling] -
void LOOP_CallbackLibrary::ClearCallbacks()
{	myloCallbacks.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_CallbackLibrary::AddCallback(LOOP_Callback &oCallback)
{	myloCallbacks.push_back(oCallback);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Callback*	LOOP_CallbackLibrary::GetCallback(int iCallbackNum)
{	return(&myloCallbacks[iCallbackNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_CallbackLibrary::Run(int iCallbackNum, LOOP_Info* pInfo)
{	myloCallbacks[iCallbackNum].Run(pInfo);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_CallbackLibrary::NumCallbacks()
{	return(myloCallbacks.size());
}
