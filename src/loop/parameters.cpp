/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Parameters
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "parameters.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Parameters
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Parameters::LOOP_Parameters()
{
}
//--------------------------------------------------------------------------------------------- [Adding] -
void LOOP_Parameters::NewInt		(int 	iValue)
{	mylInts.push_back(iValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::NewFloat		(double	dValue)
{	mylFloats.push_back(dValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::NewString		(string	sValue)
{	mylStrings.push_back(sValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::NewIntRef		(int	iValue)
{	mylIntRef.push_back(iValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::NewFloatRef	(int	iValue)
{	mylFloatRef.push_back(iValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::NewStringRef	(int	iValue)
{	mylStringRef.push_back(iValue);
}
//------------------------------------------------------------------------------------------- [Removing] -
void LOOP_Parameters::Clear()
{	mylInts.resize(0);
 	mylFloats.resize(0);
 	mylStrings.resize(0);
 	mylIntRef.resize(0);
 	mylFloatRef.resize(0);
	mylStringRef.resize(0);
}
//-------------------------------------------------------------------------------------------- [Setting] -
void LOOP_Parameters::SetInt		(int iNumber, int iTo)
{	mylInts[iNumber] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::SetFloat		(int iNumber, double dTo)
{	mylFloats[iNumber] = dTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::SetString		(int iNumber, string sTo)
{	mylStrings[iNumber] = sTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::SetIntRef		(int iNumber, int iTo)
{	mylIntRef[iNumber] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::SetFloatRef	(int iNumber, int iTo)
{	mylFloatRef[iNumber] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Parameters::SetStringRef	(int iNumber, int iTo)
{	mylStringRef[iNumber] = iTo;
}
//-------------------------------------------------------------------------------------------- [Getting] -
int	LOOP_Parameters::GetInt		(int iNumber)
{	return(mylInts[iNumber]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
double LOOP_Parameters::GetFloat	(int iNumber)
{	return(mylFloats[iNumber]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LOOP_Parameters::GetString	(int iNumber)
{	return(mylStrings[iNumber]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_Parameters::GetIntRef	(int iNumber)
{	return(mylIntRef[iNumber]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_Parameters::GetFloatRef(int iNumber)
{	return(mylFloatRef[iNumber]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LOOP_Parameters::GetStringRef(int iNumber)
{	return(mylStringRef[iNumber]);
}
