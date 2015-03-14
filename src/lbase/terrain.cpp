/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terrain.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/16/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "terrain.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Terrain
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Terrain::LL_Terrain()
	: mysGroup("DEFAULT")
{	myiColorRed		= 0;
	myiColorGreen	= 255;
 	myiColorBlue	= 0;
	myiBattleMap	= 0;
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Terrain::SaveTerrain(ofstream &oFile)
{	//"Image file path" %Custom image%
 		oFile << Qoute(ImageFile()) << " ";
		oFile << myfCustomImage << " ";
	//"Terrain Description"
		oFile << Qoute(Info()) << " ";						
	//%Color Red%, %Color Green%, %Color Blue%
		oFile << ColorRed()  << " ";
		oFile << ColorGreen()<< " ";
		oFile << ColorBlue() << " ";
	//Light effect
		oFile << int(LightEffect()) << " ";
	//%Battle Map%
		oFile << int(BattleMap())   << " ";
	//"Group"
		oFile << Qoute(mysGroup) << " ";
	//<newline>
		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Terrain::LoadTerrain(ifstream &oFile, string sGraphicsPath)
{	//Vars
		string sImageFile;
		int iLightEffect;
	//"Image file path"  %Custom image%
		sImageFile = ReadString(oFile);
		oFile >> myfCustomImage;
		LoadAnimation(sImageFile, sGraphicsPath, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
	//"Terrain Description"
		mysInfo = ReadString(oFile);
	//%Color Red%, %Color Green%, %Color Blue%
		oFile >> myiColorRed >> myiColorGreen >> myiColorBlue;
	//Light effect
		oFile >> iLightEffect;
		myiLightEffect = LL_LIGHTEFFECT(iLightEffect);
	//%Battle Map%
		oFile >> myiBattleMap;
	//"Group"
		mysGroup = ReadString(oFile);
}
//------------------------------------------------------------------------------------------ [Callbacks] -
string LL_Terrain::Info()
{	return(mysInfo);
}
//------------------------------------------------------------------------------------ [Info Attributes] -
//MEMVAR_SET(SetInfo, string, mysInfo);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET	(SetColorRed, 	ColorRed, 	int, myiColorRed);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET	(SetColorGreen,	ColorGreen, int, myiColorGreen);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET	(SetColorBlue, 	ColorBlue, 	int, myiColorBlue);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET	(SetLightEffect,LightEffect, eLIGHTEFFECT, myiLightEffect);
//--------------------------------------------------------------------------------------- [Group Reading] -
bool LL_Terrain::IsGroup(string sGroup)
{	//Capatilize sGroup and compare
		sGroup = UpperString(sGroup);
		if(sGroup == mysGroup)
			return true;
		return false;
}
