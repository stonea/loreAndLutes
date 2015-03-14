/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Label
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "label.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cLabel
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Label::LOOP_Label()
{
}
//-------------------------------------------------------------------------------- [Setting and getting] -
void LOOP_Label::SetLabel(string sIdentifier, int iClass, 	int 	iLocation)
{	SetIdentifier(sIdentifier);
	SetClass(iClass);
	SetLocation(iLocation);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetIdentifier, 	  Identifier, 	string, mysIdentifier);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetClass,			  Class,		int,	myiClass);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetLocation,		  Location,		int,	myiLocation);
