/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_ClassLibary
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "classlibrary.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_ClassLibrary
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_ClassLibrary::LOOP_ClassLibrary()
{	myloClasses.Resize(0);
}
//------------------------------------------------------------------------------------ [Class Handeling] -
void LOOP_ClassLibrary::NewClass(LOOP_Class &oClass)
{	//oClass.SetNumericIdentifier(NumClasses());
	//myloClasses.Push(oClass);
	cerr << "This function shouldn't be called: " << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_ClassLibrary::NewClass()
{	//Here lies the great fix for the great bug of Feb '03! Rejoice Happy! w00t!
	myloClasses.Resize(myloClasses.Length() + 1);
	myloClasses[myloClasses.Length() - 1].SetNumericIdentifier(myloClasses.Length() - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_ClassLibrary::NumClasses()
{	return(myloClasses.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Class*	LOOP_ClassLibrary::GetClass	(int iLocation)
{	if(iLocation < 0)
		return(NULL);
	return(&myloClasses[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Class*	LOOP_ClassLibrary::LastClass()
{	return(&myloClasses[NumClasses() - 1]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_ClassLibrary::FindClass(string sIdentifier)
{	//Loop through all classes
		for(int i = 0; i < NumClasses(); i++)
		{	//If this class mathces identifiers
				if(GetClass(i)->Identifier() == sIdentifier)
				{	return(i);
				}
		}
		
	//Return No class if no class if found
		return(NOTHING_FOUND);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_ClassLibrary::ClearClasses()
{	myloClasses.Resize(0);
}
