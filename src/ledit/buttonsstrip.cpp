/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			buttonsstrip.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "buttonsstrip.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LEDIT_ButtonsStrip
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ButtonsStrip::LEDIT_ButtonsStrip()
	: myiCurrentSet(0),
	  myiOffsetX(0),
	  myiOffsetY(0)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LEDIT_ButtonsStrip::Load(string sFile)
{	//Vars
		ifstream oFile;
		string sFileType;
		string sImagesDir;
		string sPrefix;
		string sImageFile;
		int iFileVer;
		int iNumMenus;
		int iNumButtons;

	//Open er up
		oFile.open(sFile.c_str());
	//"strip" 0
		oFile >> sFileType;
		oFile >> iFileVer;
	//"Images dir"
		sImagesDir = ReadString(oFile);
	//%Num menus%
		oFile >> iNumMenus;
		myloButtons.Resize(iNumMenus);
		mylsDescriptions.Resize(iNumMenus);
		mylsPrefixes.Resize(iNumMenus);
	//<Loop through each menu>
		for(int i = 0; i < iNumMenus; i++)
		{	//"Prefix"
				sPrefix = ReadString(oFile);
				mylsPrefixes[i] = sPrefix;
			//%Num Buttons%
				oFile >> iNumButtons;
				myloButtons[i].Resize(iNumButtons);
				mylsDescriptions[i].Resize(iNumButtons);
			//<Load images>
				for(int j = 0; j < iNumButtons; j++)
				{	myloButtons[i][j].LoadImage(ImageFile(sImagesDir, sPrefix, j), COLOR_BLUE);
				}
			//<Loop through each button>
				for(int j = 0; j < iNumButtons; j++)
				{	mylsDescriptions[i][j] = ReadString(oFile);
				}
		}
}
//-------------------------------------------------------------------------------------------- [Drawing] -
void LEDIT_ButtonsStrip::Draw()
{	//Vars
		int iCurrentX;
	//Set the current y to the offset
		iCurrentX = myiOffsetX;
	//Loop through each button drawing each one
		for(int i = 0; i < myloButtons[myiCurrentSet].Length(); i++)
		{	myloButtons[myiCurrentSet][i].BlitTo(*mypoScreen, iCurrentX, myiOffsetY);
			iCurrentX += myloButtons[myiCurrentSet][i].GetWidth() + 3;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_ButtonsStrip::DrawKeyInfo(ASFC_Console* poConsole)
{	//Go through every button
		for(int i = 0; i < myloButtons[myiCurrentSet].Length(); i++)
		{	//Draw its key
				if(i <= 8)			(*poConsole) << Val(i + 1);
				else if(i == 9) 	(*poConsole) << "0";
				else if(i == 10)	(*poConsole) << "-";
				else if(i == 11)	(*poConsole) << "+";
			//And description
				(*poConsole) << ": ";
				(*poConsole) << mylsDescriptions[myiCurrentSet][i];
				(*poConsole) << "\n";
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_ButtonsStrip::Highlight(int iButton)
{	//Vars
		int iCurrentX;
	//Set the current y to the offset
		iCurrentX = myiOffsetX;
	//Loop through each button drawing each one
		for(int i = 0; i < myloButtons[myiCurrentSet].Length(); i++)
		{	myloButtons[myiCurrentSet][i].BlitTo(*mypoScreen, iCurrentX, myiOffsetY);
	
			//If this is the highlighted one
				if(i == iButton)
				{	mypoScreen->DrawFillRectangle
					(	iCurrentX, myiOffsetY,
						myloButtons[myiCurrentSet][i].GetWidth(),
						myloButtons[myiCurrentSet][i].GetHeight(),
						COLOR_WHITE,
						0xAA
					);
				}

			iCurrentX += myloButtons[myiCurrentSet][i].GetWidth() + 3;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
int LEDIT_ButtonsStrip::ButtonAt(int iX, int iY)
{	//Vars
		int iCurrentX;

	//Pretend to draw it if we ever get in the iX, iY area return the button #	
		//Set the current y to the offset
			iCurrentX = myiOffsetX;
		//Loop through each button drawing each one
			for(int i = 0; i < myloButtons[myiCurrentSet].Length(); i++)
			{	if(iX >= iCurrentX  && iX <= iCurrentX + myloButtons[myiCurrentSet][i].GetWidth() &&
				   iY >= myiOffsetY && iY <= myiOffsetY + myloButtons[myiCurrentSet][i].GetHeight())
				{
					return(i);
				}

				iCurrentX += myloButtons[myiCurrentSet][i].GetWidth() + 3;
			}
	//If execution gets here no button was pressed
		return(-1);
}
//P----------------------------------------------------------------------------------------- [File I/O] -P
string LEDIT_ButtonsStrip::ImageFile(string sDirectory, string sPrefix, int iButtonNum)
{	//Vars
		string sImageFile;

	//All image files have the prefix and dir
		sImageFile = sDirectory;
		sImageFile += sPrefix;

	//If we have a numerical value
		if(iButtonNum >= 0 && iButtonNum <= 8)
		{	sImageFile += "_c";
			sImageFile += Val(iButtonNum + 1);
			sImageFile += ".png";
			return(sImageFile);
		}
	//If we have a 10
		if(iButtonNum == 9)
		{	sImageFile += "_c0.png";
			return(sImageFile);
		}
	//If we have a non numerical value
		else if(iButtonNum == 10)
		{	sImageFile += "_cminus";
			sImageFile += ".png";
			return(sImageFile);
		}
		else
		{	
			sImageFile += "_cplus";
			sImageFile += ".png";
			return(sImageFile);
		}
}
