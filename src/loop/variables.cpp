 /*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Variables
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "variables.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Variables
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Variables::LOOP_Variables()
{
}
//------------------------------------------------------------------------------------ [Variable Adding] -
void LOOP_Variables::NewInt(string sIdentifier, int iNewValue, bool fPublic)
{	mylInts.push_back			(iNewValue);
	mylIntsIdentifiers.push_back(sIdentifier);
	mylIntsPublic.push_back		(fPublic);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::NewFloat(string sIdentifier, double dNewValue, bool fPublic)
{	mylFloats.push_back				(dNewValue);
	mylFloatsIdentifiers.push_back	(sIdentifier);
	mylFloatsPublic.push_back		(fPublic);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::NewString(string sIdentifier, string sNewValue, bool fPublic)
{	mylStrings.push_back			(sNewValue);
	mylStringsIdentifiers.push_back	(sIdentifier);
	mylStringsPublic.push_back		(fPublic);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::CopyIn(LOOP_Variables* poFrom)
{	//Copy in Ints
		for(int i = 0; i < poFrom->NumInts(); i++)
			NewInt(poFrom->GetIntIdentifier(i), poFrom->GetInt(i), poFrom->IntPublic(i));
	//Copy in Floats
		for(int i = 0; i < poFrom->NumFloats(); i++)
			NewFloat(poFrom->GetFloatIdentifier(i), poFrom->GetFloat(i), poFrom->FloatPublic(i));
	//Copy in Strings
		for(int i = 0; i < poFrom->NumStrings(); i++)
			NewString(poFrom->GetStringIdentifier(i), poFrom->GetString(i), poFrom->StringPublic(i));
}
//----------------------------------------------------------------------------------- [Variable Removal] -
void LOOP_Variables::ClearAllVariables()
{	mylInts.resize(0);
 	mylIntsIdentifiers.resize(0);
 	mylFloats.resize(0);
 	mylFloatsIdentifiers.resize(0);
 	mylStrings.resize(0);
 	mylStringsIdentifiers.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::RemoveInt   (string sIdentifier)
{	int iLocation = FindInt(sIdentifier);
	mylInts.erase(mylInts.begin() + iLocation);
	mylIntsIdentifiers.erase(mylIntsIdentifiers.begin() + iLocation);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::RemoveFloat (string sIdentifier)
{	int iLocation = FindFloat(sIdentifier);
	mylFloats.erase(mylFloats.begin() + iLocation);
	mylFloatsIdentifiers.erase(mylFloatsIdentifiers.begin() + iLocation);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::RemoveString(string sIdentifier)
{	int iLocation = FindString(sIdentifier);
	mylStrings.erase(mylStrings.begin() + iLocation);
	mylStringsIdentifiers.erase(mylStringsIdentifiers.begin() + iLocation);
}
//----------------------------------------------------------------------------------- [Variable Getting] -
int LOOP_Variables::GetInt(string sIdentifier)
{	int iLocation = FindInt(sIdentifier);
	return(mylInts[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
double LOOP_Variables::GetFloat (string sIdentifier)
{	int iLocation = FindFloat(sIdentifier);
	return(mylFloats[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LOOP_Variables::GetString(string sIdentifier)
{	int iLocation = FindString(sIdentifier);
	return(mylStrings[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Variables::GetInt(int iLocation)
{	return(mylInts[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
double LOOP_Variables::GetFloat(int iLocation)
{	return(mylFloats[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LOOP_Variables::GetString(int iLocation)
{	return(mylStrings[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LOOP_Variables::GetIntIdentifier(int iLocation)
{	return(mylIntsIdentifiers[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LOOP_Variables::GetFloatIdentifier(int iLocation)
{	return(mylFloatsIdentifiers[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LOOP_Variables::GetStringIdentifier(int iLocation)
{	return(mylStringsIdentifiers[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Variables::IntPublic(int iLocation)
{	return(mylIntsPublic[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Variables::FloatPublic(int iLocation)
{	return(mylFloatsPublic[iLocation]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Variables::StringPublic(int iLocation)
{	return(mylStringsPublic[iLocation]);
}
//----------------------------------------------------------------------------------- [Variable Setting] -
void LOOP_Variables::SetInt   (string sIdentifier, int 	  iTo)
{	int iLocation = FindInt(sIdentifier);
	mylInts[iLocation] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::SetFloat (string sIdentifier, double dTo)
{	int iLocation = FindFloat(sIdentifier);
	mylFloats[iLocation] = dTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::SetString(string sIdentifier, string sTo)
{	int iLocation = FindString(sIdentifier);
	mylStrings[iLocation] = sTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::SetInt(int iLocation, int iTo)
{	mylInts[iLocation] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::SetFloat(int iLocation, double dTo)
{	mylFloats[iLocation] = dTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Variables::SetString(int iLocation, string sTo)
{	mylStrings[iLocation] = sTo;
}
//----------------------------------------------------------------------------------- [Variable Finding] -
int LOOP_Variables::FindInt(string sIdentifier)
{	return(Find(mylIntsIdentifiers, sIdentifier));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Variables::FindFloat(string sIdentifier)
{	return(Find(mylFloatsIdentifiers, sIdentifier));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Variables::FindString(string sIdentifier)
{	return(Find(mylStringsIdentifiers, sIdentifier));
}
//-------------------------------------------------------------------------------- [Variable Statistics] -
int	LOOP_Variables::NumInts()
{	return(mylIntsIdentifiers.size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Variables::NumFloats()
{	return(mylFloatsIdentifiers.size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Variables::NumStrings()
{	return(mylStringsIdentifiers.size());
}
//---------------------------------------------------------------------------------------- [Public Vars] -
ASFC_LinkedList<string> LOOP_Variables::PublicInts()
{	//Vars
		ASFC_LinkedList<string> lsReturn;

	//Loop through all ints, push the identifiers of the public ones onto the list
		for(int i = 0; i < NumInts(); i++)
		{	if(IntPublic(i))
				lsReturn.Push(GetIntIdentifier(i));
		}
		
	//Return the return list of course!
		return(lsReturn);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_LinkedList<string> LOOP_Variables::PublicFloats()
{	//Vars
		ASFC_LinkedList<string> lsReturn;

	//Loop through all ints, push the identifiers of the public ones onto the list
		for(int i = 0; i < NumFloats(); i++)
		{	if(FloatPublic(i))
				lsReturn.Push(GetFloatIdentifier(i));
		}
		
	//Return the return list of course!
		return(lsReturn);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_LinkedList<string> LOOP_Variables::PublicStrings()
{	//Vars
		ASFC_LinkedList<string> lsReturn;

	//Loop through all ints, push the identifiers of the public ones onto the list
		for(int i = 0; i < NumStrings(); i++)
		{	if(StringPublic(i))
				lsReturn.Push(GetStringIdentifier(i));
		}
		
	//Return the return list of course!
		return(lsReturn);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Variables::IntPublic(string sIdentifier)
{	return(IntPublic(FindInt(sIdentifier)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Variables::FloatPublic(string sIdentifier)
{	return(FloatPublic(FindFloat(sIdentifier)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Variables::StringPublic(string sIdentifier)
{	return(StringPublic(FindString(sIdentifier)));
}
//P--------------------------------------------------------------------------------- [Variable Finding] -P
int LOOP_Variables::Find(vector<string> &oVector, string s)
{	//Loop through all values in oVector
		for(int i = 0; i < oVector.size(); i++)
		{	//If this value matches s return the location
				if(oVector[i] == s)
					return(i);
		}
		
	//Else return the error (for nothing found)
		return(NO_VAR_FOUND);
}
