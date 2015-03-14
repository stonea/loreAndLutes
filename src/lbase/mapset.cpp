/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapset.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "mapset.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_MapSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_MapSet::LL_MapSet()
{
}
//--------------------------------------------------------------------------------------- [Set Editting] -
void LL_MapSet::AddMap(C_s2(sMapFile, sMapDescription))
{	mylsMapFiles.Push(sMapFile);
	mylsMapDescriptions.Push(sMapDescription);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_MapSet::Map(C_i(iMapNum))
{	//If iMapNum is < 0 return the battle map map
		if(iMapNum < 0)
			return(LL_MapSet__BATTLE_MAP);
	//Else return that map's file name
		return(mylsMapFiles[iMapNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MapSet::RemoveMap(C_i(iMapNum))
{	mylsMapFiles.Delete(iMapNum);
	mylsMapDescriptions.Delete(iMapNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int  LL_MapSet::NumMaps()
{	return(mylsMapFiles.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_MapSet::MapName(C_i(iMapNum))
{	//If we have a valid map number
		if(iMapNum >= 0 && iMapNum < NumMaps())
			//Return that map
				return(mylsMapDescriptions[iMapNum]);
	//If we have a no map #
		else if(iMapNum == NO_MAP)
			//Return "No Map"
				return("-- [No Map] --");	

	//Else return "NO EXISTO!"
		return("ERR: INVALID MAP");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MapSet::SetMapName(C_i(iMapNum), C_s(sName))
{	mylsMapDescriptions[iMapNum] = sName;
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_MapSet::Save(ofstream &oFile)
{	//~.mapset 0~				File type and version number
		oFile << ".mapset 0" << endl;
		
	//%Number of maps%
		oFile << NumMaps() << endl;

	//Loop for # of maps
		for(int i = 0; i < NumMaps(); i++)
		{	//"Map File"
				oFile << Qoute(mylsMapFiles[i])			<< endl;
				oFile << Qoute(mylsMapDescriptions[i])	<< endl;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MapSet::Load(ifstream &oFile)
{	//Vars
		string sFileType;
		int	iVersionNumber;
		int iNumMaps;
		string 	sMapFile,
				sMapDescription;

	//~.mapset 0~				File type and version number
		oFile >> sFileType;
  		oFile >> iVersionNumber;
  	
    //If we have a valid version	
		if(ValidVersionNum("cMapSet::Load 000, Invalid file type or version", sFileType, iVersionNumber))
		{	//%Number of maps%
				oFile >> iNumMaps;
				
			//Loop for the # of maps
				for(int i = 0; i < iNumMaps; i++)
				{	sMapFile		= ReadString(oFile);
					sMapDescription	= ReadString(oFile);
					
					//Now add this map
						AddMap(sMapFile, sMapDescription);
				}
		}
}
//P---------------------------------------------------------------------------------------- [Debugging] -P
bool LL_MapSet::ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum))
{	//Const
		const string REQUIRED_FILE_TYPE 		= ".mapset";	//Holds the required file type
		const int	 REQUIRED_VERSION_NUMBER	= 0;			//Holds the required version number
		
	//If invalid
		if(sFileType != REQUIRED_FILE_TYPE || iVersionNum != REQUIRED_VERSION_NUMBER)
		{	cout << sErrorCode << endl;
			cout << "--[File Type]-->               "  << sFileType   				<< endl;
			cout << "--[Required File Type]-->      "  << REQUIRED_FILE_TYPE   		<< endl;
			cout << "--[Version Number]-->          "  << iVersionNum   			<< endl;
			cout << "--[Required Version Number]--> "  << REQUIRED_VERSION_NUMBER   << endl;
			return false;
		}
		else
			return true;
}
