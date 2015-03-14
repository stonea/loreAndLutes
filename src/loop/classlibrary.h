/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_ClassLibary
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef CLASSLIBRARY_H_
	#define CLASSLIBRARY_H_
	
//Foundation
	#include <vector>
	
//Aggregates
	#include "class.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_ClassLibary
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_ClassLibrary
{	public:
	static const int NOTHING_FOUND = -1;
	//- [Constuctors] -
 		LOOP_ClassLibrary();
 		
	//- [Class Handeling] -
		void 		NewClass(LOOP_Class &oClass);
		void		NewClass();
		int 		NumClasses();
		LOOP_Class*	GetClass(int iLocation);
		LOOP_Class*	LastClass();
		int			FindClass(string sIdentifier);
		void		ClearClasses();
 	
 	private:
  	//Vars
		ASFC_LinkedList<LOOP_Class>		myloClasses;
 	
 	private:
 	//Vars
 	
};

//Now ending classset.h
	#endif
