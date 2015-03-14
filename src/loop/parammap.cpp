/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_ParamMap
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "parammap.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_ParamMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_ParamMap::LOOP_ParamMap()
{
}
//--------------------------------------------------------------------------------- [Param Map Updating] -
void LOOP_ParamMap::Clear()
{	mylPasses.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_ParamMap::New(eParam iWhat)
{	mylPasses.push_back(iWhat);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
eParam	LOOP_ParamMap::Param(int iNumber)
{	return(mylPasses[iNumber]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_ParamMap::NumParams()
{	return(mylPasses.size());
}
