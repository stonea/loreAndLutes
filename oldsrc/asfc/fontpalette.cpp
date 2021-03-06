/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes

    File: fontpalette.cpp
    By:   Andy Stone
    Desc:	
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//Self
	#include "fontpalette.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												 ASFC_FontPalette
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//---------------------------------------------------------------------------------------- [Construction] -
ASFC_FontPalette::ASFC_FontPalette()
{
}
//----------------------------------------------------------------------------------------- [Font Adding] -
void ASFC_FontPalette::AddFont(string sFile, int iWidth, int iHeight, int iTrRed,
							   int iTrGrn, int iTrBlu)
{
	//Create a font and then push it on
		Resize(Length() + 1);
  		operator[](Length() - 1).Load(sFile, iWidth, iHeight, iTrRed, iTrGrn, iTrBlu);
}
