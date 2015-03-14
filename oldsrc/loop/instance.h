/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cInstance
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef INSTANCE_H_
	#define INSTANCE_H_

//Foundation
	#include <vector>
	#include <string>

//Aggregates
	#include "variables.h"
	#include "class.h"
	#include "offset.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cInstance
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Instance
{	public:
	//Type
 		struct LOOP_Instance_Zap
 		{	string sLabel;
 			int iTimesZapped;
 			
 			LOOP_Instance_Zap()
 			{	sLabel = "";
 				iTimesZapped = 0;
 			}
 		};

	//- [Constuctors] -
 		LOOP_Instance();
 		
	//- [Identifier Handeling] -
 		MEMVAR_SETGET(SetIdentifier, Identifier, string, mysIdentifier);
 		
	//- [Class Handeling] -
		void SetClass(LOOP_Class* poClass);
		MEMVAR_GET(Class, LOOP_Class*, mypoClass);
		MEMVAR_GETREF(Zaps, vector<LOOP_Instance_Zap>, myoZaps);
		
	//- [Variable Handeling] -
		LOOP_Variables* Variables();
		
	//- [Offset Handeling] -
		LOOP_Offset	CurrentOffset();
		void 		MoveCurrentOffset(int iClassCode, int iOffset);
		void 		AddOffset(int iClassCode, int iOffset);
		void 		RemoveLastOffset();
		int 		NumOffsets();
		void		ChangeOffset(int iIndex, LOOP_Offset oNewOffset);
		void		SeekCommand(string  sIdentifier, string sNewBlock);

 	private:
 	//Vars
 		string						mysIdentifier;
 		LOOP_Class* 				mypoClass;
 		LOOP_Variables				myoVariables;
 		vector<LOOP_Offset>			myoOffsets;
 		vector<LOOP_Instance_Zap>	myoZaps;
};

//Now ending instance.h
	#endif
