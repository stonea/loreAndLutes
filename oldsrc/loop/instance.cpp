/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Instance
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "instance.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Instance
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Instance::LOOP_Instance()
{
}
//------------------------------------------------------------------------------- [Identifier Handeling] -
//MEMVAR_SETGET(SetIdentifier, Identifier, string, mysIdentifier);
//------------------------------------------------------------------------------------ [Class Handeling] -
void LOOP_Instance::SetClass(LOOP_Class* poClass)
{	//Set the class
		mypoClass = poClass;

	//Copy over all the variables
		myoVariables = *mypoClass->GetVariables();
}
//--------------------------------------------------------------------------------- [Variable Handeling] -
LOOP_Variables* LOOP_Instance::Variables()
{	return(&myoVariables);
}
//----------------------------------------------------------------------------------- [Offset Handeling] -
LOOP_Offset LOOP_Instance::CurrentOffset()
{	return(myoOffsets[myoOffsets.size() - 1]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Instance::MoveCurrentOffset(int iClassCode, int iOffset)
{	myoOffsets[myoOffsets.size() - 1].SetClassCode	(iClassCode);
	myoOffsets[myoOffsets.size() - 1].SetOffset		(iOffset);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Instance::AddOffset(int iClassCode, int iOffset)
{	LOOP_Offset toOffset;
	toOffset.SetClassCode	(iClassCode);
	toOffset.SetOffset		(iOffset);
	
	myoOffsets.push_back(toOffset);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Instance::RemoveLastOffset()
{	myoOffsets.pop_back();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Instance::NumOffsets()
{	return(myoOffsets.size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Instance::ChangeOffset(int iIndex, LOOP_Offset oNewOffset)
{	myoOffsets[iIndex] = oNewOffset;
}
