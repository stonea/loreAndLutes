/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cOffset
*/

//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Multiple inclusion protection:
	#ifndef OFFSET_H_
	#define OFFSET_H_
	
//Foundation
	#include <asfc/utils.h>
	
//��������������������������������������������������������������������������������������������������������
//												cOffset
//��������������������������������������������������������������������������������������������������������
class LOOP_Offset
{	public:
	//- [Constuctors] -
 		LOOP_Offset();
 		
	//- [MEM VAR MAPS] -
		MEMVAR_SETGET(SetClassCode,	ClassCode,	int, myiClassCode);
		MEMVAR_SETGET(SetOffset,	Offset,		int, myiOffset);
 	
 	private:
 	//Vars
 		int myiClassCode;
		int myiOffset;
};

//Now ending offset.h
	#endif
