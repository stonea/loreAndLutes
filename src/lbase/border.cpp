/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			border.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/15/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "border.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Border
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Border::LL_Border()
{
}
//-------------------------------------------------------------------------------------- [Image Loading] -
void LL_Border::LoadHorizontalBorder(string sFileName)
{	myoimgHoriz.LoadImage(sFileName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Border::LoadHorizontalInfoBorder(string sFileName)
{	myoimgHorizInfo.LoadImage(sFileName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Border::LoadHorizontalPlayBorder(string sFileName)
{	myoimgHorizPlay.LoadImage(sFileName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Border::LoadVerticalBorder(string sFileName)
{	myoimgVert.LoadImage(sFileName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Border::LoadVerticalInfoBorder(string sFileName)
{	myoimgVertInfo.LoadImage(sFileName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Loads borders from a .border file
void LL_Border::Load(string sFile)
{	//Vars
		ifstream oFile(sFile.c_str(), ios::binary);
		string 	 sFileType;
		int	   	 iFileVersion;
		string	 sImagePath;

	//Read in the file type and version
		oFile >> sFileType;
		oFile >> iFileVersion;

	//If we have the right type of file
		//Read in the horizontal border
			oFile >> sImagePath;
			LoadHorizontalBorder(sImagePath);
		//Read in the horizontal image border
			oFile >> sImagePath;
			LoadHorizontalInfoBorder(sImagePath);
		//Read in the horizontal play border
			oFile >> sImagePath;
			LoadHorizontalPlayBorder(sImagePath);
		//Read in the vertical border
			oFile >> sImagePath;
			LoadVerticalBorder(sImagePath);
		//Read in the vertical info border
			oFile >> sImagePath;
			LoadVerticalInfoBorder(sImagePath);
}
//-------------------------------------------------------------------------------------------- [Drawing] -
void LL_Border::Draw(ASFC_Surface& oTo)
{	oTo.Blit(myoimgHorizInfo,	HORIZ_INFO_X,	HORIZ_INFO_Y);
	oTo.Blit(myoimgHorizInfo,	HORIZ_INFO2_X,	HORIZ_INFO2_Y);
 	oTo.Blit(myoimgHorizPlay,	HORIZ_PLAY_X,	HORIZ_PLAY_Y);
	oTo.Blit(myoimgVertInfo,	VERT_INFO_X,	VERT_INFO_Y);
  	oTo.Blit(myoimgVert,		VERT_X,			VERT_Y);
  	oTo.Blit(myoimgVert,		VERT2_X,		VERT2_Y);
 	oTo.Blit(myoimgHoriz,		HORIZ_X,		HORIZ_Y);
 	oTo.Blit(myoimgHoriz,		HORIZ2_X,		HORIZ2_Y);
}
