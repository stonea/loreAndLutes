/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes

    File: mousepointer.cpp
    By:   Andy Stone
    Desc:	
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "mousepointer.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 ASFC_MousePointer
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//--------------------------------------------------------------------------------------- [Construction] -
ASFC_MousePointer::ASFC_MousePointer()
{
}
//------------------------------------------------------------------------------------ [Loading\Setting] -
void ASFC_MousePointer::Load(string sFile)
{	//Vars
		ifstream oFile(sFile.c_str());
		char c;

	//Read in the hot spot info
		oFile >> myiHotX;
		oFile >> myiHotY;
	
	//Loop through all cursor data
		for(int iY = 0; iY < NUM_ROWS; iY++)
			for(int iX = 0; iX < NUM_COLS; iX++)
			{	//Read a char, decide what to do based on it
					oFile >> c;
					mylcImage[iY][iX] = c;
			}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_MousePointer::Set()
{	//Convert the character array into a weird MSB format char array
	//(code below ripped from: http://sdldoc.csn.ul.ie/sdlcreatecursor.php
		Uint8 data[4*32];
		Uint8 mask[4*32];
		int i = -1;

		for (int row=0; row<32; ++row)
		{	for(int col=0; col<32; ++col)
			{	if (col % 8)
				{	data[i] <<= 1;
					mask[i] <<= 1;
				}
				else
				{	++i;
					data[i] = mask[i] = 0;
				}
				
				switch (mylcImage[row][col])
				{	case 'X':
						data[i] |= 0x01;
						mask[i] |= 0x01;
					break;
					case '#':
						mask[i] |= 0x01;
					break;
					case '.':
					break;
				}
			}
		}

	SDL_SetCursor(SDL_CreateCursor(data, mask, 32, 32, myiHotX, myiHotY));
}
