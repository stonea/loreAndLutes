/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_CallbackLibrary
*/

//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Multiple inclusion protection:
	#ifndef CALLBACKLIBRARY_H_
	#define CALLBACKLIBRARY_H_

//Foundation
	#include <vector>

//Aggregates
	#include "callback.h"
	
//��������������������������������������������������������������������������������������������������������
//												LOOP_CallbackLibrary
//��������������������������������������������������������������������������������������������������������
class LOOP_CallbackLibrary
{	public:
	//- [Constuctors] -
 		LOOP_CallbackLibrary();
 		
	//- [Callback Handeling] -
		void 		ClearCallbacks();
		void 		AddCallback(LOOP_Callback &oCallback);
		LOOP_Callback*	GetCallback(int iCallbackNum);
		void		Run(int iCallbackNum, LOOP_Info* pInfo);
		int			NumCallbacks();
 	
 	private:
 	//Vars
 		vector<LOOP_Callback> myloCallbacks;
};

//Now ending callbacklibrary.h
	#endif
