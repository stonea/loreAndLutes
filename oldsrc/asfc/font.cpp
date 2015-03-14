/*    Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
	
	File:	font.cpp	[Class Font]
    By:		Andy Stone
    Desc:	This file includes the code of the ASFC_Font object
*/

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
#include <string>
using namespace std;
#include "font.h"
#include "utils.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												ASFC_Font Data
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//--------------------------------------------------------------------------------- [Constructors\Deconstructors] -
//Constructs a ASFC_Font object, but doesn't load a font yet...
ASFC_Font::ASFC_Font(void)
{	//Set vars to their defaults
		this->SetDefaultVariables();
}
//.................................................................................................................
//Constructs a ASFC_Font object, using the multiimage sFontPath
ASFC_Font::ASFC_Font(string sFontPath, C_i(iWidth), C_i(iHeigth))
{	//Set vars to their defaults
		this->SetDefaultVariables();	
	
	//Load up the Multi-Image
		this->Load(sFontPath, iWidth, iHeigth);
		mysFile = sFontPath;
}
//.................................................................................................................
//Constructs a ASFC_Font object, using the multiimage sFontPath
ASFC_Font::ASFC_Font(string sFontPath, C_i5(iWidth, iHeigth, iTransRed, iTransGreen, iTransBlue))
{	//Set vars to their defaults
		this->SetDefaultVariables();	
	
	//Load up the Multi-Image
		this->Load(sFontPath, iWidth, iHeigth, iTransRed, iTransGreen, iTransBlue);
		mysFile = sFontPath;
}
//PRIVATE..........................................................................................................
//Set's variables to their default values
void ASFC_Font::SetDefaultVariables()
{	myfFontLoaded	=	false;
}
//----------------------------------------------------------------------------------------------------- [Loading] -
//Loads the multiimage strFontPath as the font's image		
void ASFC_Font::Load(string sFontPath, C_i2(iWidth, iHeigth))
{	//Load up the Multi-Image
		myXB = iWidth;
		myYB = iHeigth;
		myTransRed = 0xFF;
		myTransGreen = 0xFF;
		myTransBlue = 0xFF;
		this->LoadImage(sFontPath, myTransRed, myTransGreen, myTransBlue);
	
		mysFile = sFontPath;
	
	//Set loaded font flag on
		myfFontLoaded = true;
	
	//Set Width & Heigth Vars
		myiWidth  = iWidth;
		myiHeigth = iHeigth;
}
//..................................................................................................................
//Loads the multiimage strFontPath as the font's image, set transperency
void ASFC_Font::Load(string sFontPath, C_i5(iWidth, iHeigth, iTransRed, iTransGreen, iTransBlue))
{	//Load up the Multi-Image
		myXB = iWidth;
		myYB = iHeigth;
		myTransRed = iTransRed;
		myTransGreen = iTransGreen;
		myTransBlue = iTransBlue;
		this->LoadImage(sFontPath, myTransRed, myTransGreen, myTransBlue);

		mysFile = sFontPath;
	
	//Set loaded font flag on
		myfFontLoaded = true;
	
	//Set Width & Heigth Vars
		myiWidth  = iWidth;
		myiHeigth = iHeigth;
}	
//----------------------------------------------------------------------------------------- [Text Output] -
//Draws a char of text at iX, iY
void ASFC_Font::WriteTo(ASFC_Surface &surf, C_i2(iX, iY), char cToDraw)
{	if(myfFontLoaded == false)
	{	cout << "ERR in ASFC_Font::Draw 000, unloaded font";
		return;
	}
	this->BlitTo(surf, iX, iY, cToDraw - ' ');
}
//.................................................................................................................
//Draws a string of text at iX, iY
void ASFC_Font::WriteTo(ASFC_Surface &surf, C_i2(iX, iY), C_s(sToDraw))
{	//First make sure a font's been loaded, if not give an error
		if(myfFontLoaded == false)
			cout << "ERR in ASFC_Font::Draw 000, unloaded font";
	//Loop through all of the characters of the string		
		for(unsigned int i = 0; i < sToDraw.length(); i++)
		{	//Draw a char
				this->BlitTo(surf, iX + (i * myiWidth), iY, sToDraw[i] - ' ');
		}
}
