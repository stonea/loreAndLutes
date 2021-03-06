/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			menu.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//Self
	#include "menu.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//											LRUN_Menu
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//---------------------------------------------------------------------------------------- [Construction] -
LRUN_Menu::LRUN_Menu()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LRUN_Menu::Init(ASFC_Screen &oScreen, ASFC_Effects& oEffects)
{	mypoScreen  = &oScreen;
	mypoEffects = &oEffects;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LRUN_Menu::Load(ifstream oFile)
{	//Vars
		int iNumButtons;
		int iWidth, iHeight;
		string sImage;
		string sFileType;
		int iFileVersion;
		int iX, iY;
	//Set default vars
		myiLargestWidth = -1;
	//Read in the file type and version
		oFile >> sFileType;
		oFile >> iFileVersion;
	//Read in the offsets
		oFile >> myiXOffset >> myiYOffset;
		iX = myiXOffset;
		iY = myiYOffset;
	//Read in the # of buttons
		oFile >> iNumButtons;
		myoButtons.Resize(iNumButtons);
	//Read in all the buttons
		for(int i = 0; i < iNumButtons; i++)
		{	//Read in this image's attributes
				oFile >> iWidth >> iHeight;
				sImage = ReadString(oFile);
			//If the width of this image is the largest remember it
				if(myiLargestWidth < iWidth)
					myiLargestWidth = iWidth;
			//Load 'er up
				myoButtons[i].oImage.Load(sImage, iWidth, iHeight, COLOR_BLUE);
			//Record the size information	
				myoButtons[i].iX  = iX;
				myoButtons[i].iY  = iY;
				myoButtons[i].iX2 = iX + myoButtons[i].oImage.XBlock();
				myoButtons[i].iY2 = iY + myoButtons[i].oImage.YBlock();
			//If this button is full size or is the second one go to the next line
				if(myoButtons[i].oImage.XBlock() == myiLargestWidth || iX != myiXOffset)
				{	iX = myiXOffset;
					iY += myoButtons[i].oImage.YBlock();
				}
			//Otherwise move the x over
				else
				{	iX += myoButtons[i].oImage.XBlock();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LRUN_Menu::LRUN_MENU_CHOICE LRUN_Menu::Choose()
{	//Set the default options
		myiChosen = CHOICES_NONE;
		myiSelectedKey = LRUN_MENU_CHOICE(-1);//!!!
	//Take a shot of the current screen
		ASFC_Surface oSurf1(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
		oSurf1.Blit(*mypoScreen, 0, 0);
	//Darken the background
		mypoScreen->DrawFillRectangle(0, 0, mypoScreen->GetWidth(),
									  mypoScreen->GetHeight(), COLOR_BLACK, 100);
		Draw();
		ASFC_Surface oSurf2(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
		oSurf2.Blit(*mypoScreen, 0, 0);
	//Do a fade effect
//		mypoEffects->Blend(oSurf1, oSurf2, *mypoScreen, 15, 30);
	//Until we've selected something keep drawing
		while(myiChosen == CHOICES_NONE || myoInput.GetMouseButton(MOUSE_LEFT))
		{	myiSelectedKey = LRUN_MENU_CHOICE(-1);

			//Figure out what button is selected based on the mouse
				HandleMouse();
				
			//Check the 'y' key return with exit
				myoInput.Update();
				if(myoInput.KeyDown(SDLK_y))
					return(LRUN_MENU_CHOICE(myoButtons.Length() - 1));

			Draw();
			mypoScreen->Update();
		}
	//Do a fade effect if the choice wasn't exit
//		if(myiChosen != CHOICES_EXIT)
//			mypoEffects->Blend(oSurf2, oSurf1, *mypoScreen, 15, 30);
	//Otherwise fade to darkness
//		else
//		{	oSurf1.DrawFillRectangle(0, 0, oSurf1.GetWidth()-1, oSurf1.GetHeight()-1, COLOR_BLACK, 0xFF);
//			mypoEffects->Blend(oSurf2, oSurf1, *mypoScreen, 30, 3);
//		}
	//Return our choice
		return(myiChosen);
}
//P------------------------------------------------------------------------------------------- [Drawing] -P
void LRUN_Menu::Draw()
{	//Vars
		int iX, iY;
	//Loop through all existing buttons
		for(int i = 0; i < myoButtons.Length(); i++)
		{	//Figure out the position
				iX = myoButtons[i].iX;
				iY = myoButtons[i].iY;
			//Draw this button
				if(myiSelectedKey == i)
					myoButtons[i].oImage.BlitTo(*mypoScreen, iX, iY, IMAGE_HOVER);
				else if(myiSelectedMouse == i && myoInput.GetMouseButton(MOUSE_LEFT))
					myoButtons[i].oImage.BlitTo(*mypoScreen, iX, iY, IMAGE_DOWN);
				else if(myiSelectedMouse == i)
					myoButtons[i].oImage.BlitTo(*mypoScreen, iX, iY, IMAGE_HOVER);
				else
					myoButtons[i].oImage.BlitTo(*mypoScreen, iX, iY, IMAGE_NORMAL);
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_Menu::HandleMouse()
{	//Vars
		int iX, iY;

	//Figure out what button is selected based on the cursor's position
		myiSelectedMouse = LRUN_MENU_CHOICE(-1);
		myoInput.Update();
		iX = myoInput.GetMouseX();
		iY = myoInput.GetMouseY();
		for(int i = 0; i < myoButtons.Length(); i++)
		{	if(iX >= myoButtons[i].iX && iX <= myoButtons[i].iX2)
				if(iY >= myoButtons[i].iY && iY <= myoButtons[i].iY2)
				{	myiSelectedMouse = LRUN_MENU_CHOICE(i);
					if(myoInput.GetMouseButton(MOUSE_LEFT))
						myiChosen = LRUN_MENU_CHOICE(i);
					return;
				}
		}
		if(myoInput.GetMouseButton(MOUSE_LEFT))
			myiChosen = CHOICES_NONE;
}
