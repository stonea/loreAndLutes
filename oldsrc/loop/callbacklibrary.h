/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_CallbackLibrary
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef CALLBACKLIBRARY_H_
	#define CALLBACKLIBRARY_H_

//Foundation
	#include <vector>

//Aggregates
	#include "callback.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_CallbackLibrary
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
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
