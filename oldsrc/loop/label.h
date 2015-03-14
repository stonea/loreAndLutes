/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cLabel
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef LABEL_H_
	#define LABEL_H_
	
//Foundation
	#include <asfc/utils.h>
	#include <string>
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cLabel
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Label
{	public:
	//- [Constuctors] -
 		LOOP_Label();
 		
	//- [Setting and getting] -
		void SetLabel(string sIdentifier, int iClass, 	int 	iLocation);
		MEMVAR_SETGET(SetIdentifier, 	  Identifier, 	string, mysIdentifier);
		MEMVAR_SETGET(SetClass,			  Class,		int,	myiClass);
		MEMVAR_SETGET(SetLocation,		  Location,		int,	myiLocation);
 	
 	private:
 	//Vars
 		string 	mysIdentifier;
		int		myiClass;
 		int		myiLocation;
};

//Now ending label.h
	#endif
