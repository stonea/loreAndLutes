/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Callback
*/

//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Multiple inclusion protection:
	#ifndef CALLBACK_H_
	#define CALLBACK_H_
	
//Aggregates
	//Function
	#include "info.h"	//Aggregates through function
	
//��������������������������������������������������������������������������������������������������������
//												LOOP_Callback
//��������������������������������������������������������������������������������������������������������
class LOOP_Callback
{	public:
	//- [Constuctors] -
 		LOOP_Callback();
 		
	//- [Calling] -
		void Run(LOOP_Info* poInfo);
	
	//- [Setting\Getting] -
		void SetFunction(void (*pFunction)(LOOP_Info, void*));
		void SetObject(void* pObject);

 	private:
 	//Vars
		void 	(*mypFunction)(LOOP_Info, void*);
		void* 	mypObj;
};

//Now ending callback.h
	#endif
