/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terrainset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "terrainset.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_TerrainSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_TerrainSet::LL_TerrainSet()
{
}
//--------------------------------------------------------------------------------- [Terrains Handeling] -
void LL_TerrainSet::AddTerrain(LL_Terrain &oAdd)
{	//Simply push this terrain onto the list
		myloTerrains.Resize(myloTerrains.Length() + 1);
		myloTerrains[myloTerrains.Length() - 1] = oAdd;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_TerrainSet::RemoveTerrain(int &iTerrainNum)
{	//Make sure we have a valid parameter
		if(ValidTerrainNum("LL_TerrainSet::RemoveTerrain() 000 Attempt to remove invalid terrain", iTerrainNum))
		{	//remove the terrain
				myloTerrains.Delete(iTerrainNum);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Terrain& LL_TerrainSet::Terrain(C_i(iTerrainNum))
{	//If we have a valid terrain
		if(ValidTerrainNum("LL_TerrainSet::Terrain() 000 Attempt to read invalid terrain", iTerrainNum))
		{	//Return this terrain
				return(myloTerrains[iTerrainNum]);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_TerrainSet::NumTerrains()
{	//Return the size of the terrain list
		return(myloTerrains.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Reset animation cycle on all terrains
void LL_TerrainSet::ResetAnimations()
{	//Loop through all terrains
		for(int i = 0 ; i < NumTerrains(); i++)
		{	//Reset this terrain
				myloTerrains[i].Reset();
		}
}
//------------------------------------------------------------------------------------------- [File I/O] -
//See terrain.filedesc for info about the file format
void LL_TerrainSet::Save(ofstream &oFile)
{	//~.terrain 0~				File type and version number
		oFile << ".terrain 0" << endl;
		
	//%Number Of Terrains%
		oFile << NumTerrains() << endl;
		
	//<Loop for the # of terrains>
		for(int i = 0; i < NumTerrains(); i++)
		{	//<Save Terrain>
				myloTerrains[i].SaveTerrain(oFile);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//See terrain.filedesc for info about the file format
bool LL_TerrainSet::Load(ifstream &oFile, string sGraphicsPath)
{	//Vars
		string 	sFileType;
		int		iVersionNum;
		int		iNumTerrains;
		string	sFilePath;
		string	sDescription;
		int		iLightEffect;
		int		iColorRed, iColorGreen, iColorBlue;
		int		iNumMobilities;
		int		iVehicleCode;
		bool	fNorthIn, fSouthIn, fWestIn, fEastIn, fNorthOut, fSouthOut, fWestOut, fEastOut;
		int		iNormalTicks;
		int		iDamage;
		int		iChanceOfDamage;
		LL_Terrain	oTerrain;
		LL_Mobility	oMobility;
		
	//~.terrain 0~				File type and version number
		oFile >> sFileType;
		oFile >> iVersionNum;

	//If this is a valid file		
		if	(ValidVersionNum("LL_TerrainSet::LoadTerrains 000, Invalid file type or version", sFileType,
		 	iVersionNum))
		{	//%Number Of Terrains%
				oFile >> iNumTerrains;
				myloTerrains.Resize(iNumTerrains);
		
			//<Loop for the # of terrains>
				for(int i = 0; i < iNumTerrains; i++)
				{	//<Load & Set Code>
						myloTerrains[i].LoadTerrain(oFile, sGraphicsPath);
						myloTerrains[i].SetCode(i);
				}
		}

	//TerrainSet loaded succesfully
		return true;
}
//------------------------------------------------------------------------------------ [Info Attributes] -
//MEMVAR_SET(SetInfo, string, mysInfo)
//P---------------------------------------------------------------------------------------- [Debugging] -P
//Makes sure terrain iTerrainNum is a valid terrain number if it is return true, else false
bool LL_TerrainSet::ValidTerrainNum(C_s(sErrorCode), C_i(iTerrainNum))
{	if(iTerrainNum < 0 || iTerrainNum >= NumTerrains())
	{	cout << sErrorCode << endl;
		cout << "--[TerrainNum]--> "  << iTerrainNum   << endl;
		cout << "--[NumTerrains]--> " << NumTerrains() << endl;
		
		return false;
	}
	else
		return true;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
//Makes sure iVersionNumber is the correct version number for a .terrain file, if it is return true
bool LL_TerrainSet::ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum))
{	//Const
		const string REQUIRED_FILE_TYPE 		= ".terrain";	//Holds the required file type
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
