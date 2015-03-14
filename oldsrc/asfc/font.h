/*  Protected under the GNU General Public License read and see copying.txt for details  
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
	
	File:	font.h	[Class Font Header File]
    By:		Andy Stone
    Desc:	This file includes the prototype of the ASFC_Font object
*/

#ifndef ASFC_FONT_H_
#define ASFC_FONT_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
#include <string>
using namespace std;

#include "multiimage.h"
#include "utils.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											ASFC_Font prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//ASFC_Font, holds data for a bitmapped font. This font can be used to output strings of text to the screen.
class ASFC_Font : public ASFC_MultiImage
{	public:
	//- [Constructors\Deconstructors] -
		ASFC_Font(void);											//Constructs a ASFC_Font object, but doesn't load a font yet...		
		ASFC_Font(string sFontPath, C_i(iWidth), C_i(iHeigth));		//Constructs a ASFC_Font object, using the multiimage sFontPath		
		ASFC_Font(string sFontPath, C_i5(iWidth, iHeigth, iTransRed, iTransGreen, iTransBlue));		//Constructs a ASFC_Font object, using the multiimage sFontPath
	//- [Loading] -
		void Load(string sFontPath, C_i2(iWidth, iHeigth));		//Loads the multiimage strFontPath as the font's image, set transperency to FF,FF,FF
		void Load(string sFontPath, C_i5(iWidth, iHeigth, iTransRed, iTransGreen, iTransBlue));		//Loads the multiimage strFontPath as the font's image, set transperency
	//- [Text Output] -
		void WriteTo(ASFC_Surface &surf, C_i2(iX, iY), C_s(sToDraw));	//Draws a string of text at iX, iY
		void WriteTo(ASFC_Surface &surf, C_i2(iX, iY), char cToDraw);	//Draws a char of text at iX, iY
	//- [Variable to Method mapping] -
		MEMVAR_LINK(Width,  int, myiWidth);
		MEMVAR_LINK(Height, int, myiHeigth);
		MEMVAR_LINK(File,	string, mysFile);
		
	private:
	//P- [Constructors\Deconstructors] -
		void SetDefaultVariables();		//Set's variables to their default values
	
	//vars
		bool			myfFontLoaded;		//True when a font's multiimage is loaded into memory
		int				myiWidth, myiHeigth;//Dimensions of characters in the font
		string			mysFile;			//Keeps track of what file loaded this font
};

#endif
