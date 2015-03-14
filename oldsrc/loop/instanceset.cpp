/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_InstanceSet
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "instanceset.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_InstanceSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_InstanceSet::LOOP_InstanceSet()
{
}
//--------------------------------------------------------------------------------- [Instance Handeling] -
void LOOP_InstanceSet::NewInstance(LOOP_Class* poOfClass, eScope iScope)
{	//Create a temporary instance (give it a starting offset of zero)
		LOOP_Instance oNewInstance;
		oNewInstance.SetClass	(poOfClass);
	//	oNewInstance.AddOffset	(poOfClass->NumericIdentifier(), 0);
	//Add this instance
		myloInstances.push_back(oNewInstance);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_InstanceSet::RemoveInstance(string sIdentifier)
{	//Vars
		int iLocation = GetInstanceLocation(sIdentifier);

	myloInstances.erase		(myloInstances.begin() 		+ iLocation);
	myliInstancesScope.erase(myliInstancesScope.begin() + iLocation);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_InstanceSet::RemoveLocalInstances()
{	// !!!
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_InstanceSet::ClearInstances()
{	myloInstances.resize(0);
	myliInstancesScope.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int  LOOP_InstanceSet::NumInstances()
{	return(myloInstances.size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Instance*	LOOP_InstanceSet::GetInstance(string sIdentifier)
{	return(&myloInstances[GetInstanceLocation(sIdentifier)]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Instance*	LOOP_InstanceSet::GetInstance(int iLocation)
{	return(&myloInstances[iLocation]);
}
//-------------------------------------------------------------------------------P [Instance Handeling] -P
int	LOOP_InstanceSet::GetInstanceLocation(string sIdentifier)
{	//Loop through all of our instances
		for(int i = 0; i < NumInstances(); i++)
		{	//If this instance mathces the identifier
				if(sIdentifier == myloInstances[i].Identifier())
				{	return(i);
				}
		}
}
