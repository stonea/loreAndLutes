/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			graphicsList.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	01/01/03 20:52
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "graphicslist.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//			 									 LEDIT_GraphicsLIst
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_GraphicsList::LEDIT_GraphicsList()
	: myimgBackground(640, 480, 16)
{
}
//-------------------------------------------------------------------------------------------- [Choosing] -
string LEDIT_GraphicsList::ChooseGraphic(ASFC_LinkedList<string> lsGraphicsList, string sFolder)
{	//Vars
		int iToChoose = -1;
	//Capture the background
		myimgBackground.Blit(*mypoScreen, 0, 0);
	//Delete all previous images, make room for the new ones
		mylimg.Resize(lsGraphicsList.Length());
	//Load all images
		for(int i = 0; i < lsGraphicsList.Length(); i++)
		{	mylimg[i].Load(sFolder + "/" + lsGraphicsList[i], TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
		}
	//Redraw
		Draw();
	//While we haven't chosen anything yet
		while(iToChoose < 0 || iToChoose >= lsGraphicsList.Length())
		{	//Get a key
				iToChoose = HandleKeys();
		}
	//Return our returnee
		return(lsGraphicsList[iToChoose]);
}
//P------------------------------------------------------------------------------------------- [Choosing] -P
void LEDIT_GraphicsList::Draw(int iHighlight)
{	//Const
		const int POS_X = 164;
		const int SPACE = 5;
	//Vars
		int iW, iH, iY, iX;
		
	//Draw background
		myimgBackground.BlitTo(*mypoScreen, 0, 0);
	//Calculate the Y position
		iW = 138;
  		iH = mylimg.Length() * (TILE_HEIGHT + SPACE);
		iY = (mypoScreen->GetHeight() + iH) / 2 - iH;
		iX = POS_X;
	//Draw the box
		iW += 5;
		iH += 15;
		mypoScreen->DrawRectangle(POS_X - 2, iY - 2, iW + 3, iH + 3, COLOR_WHITE, 200);
		mypoScreen->DrawRectangle(POS_X - 1, iY - 1, iW + 1, iH + 1, COLOR_GRAY,  200);
		mypoScreen->DrawFillRectangle(POS_X, iY, iW, iH, COLOR_BLACK, 200);
		mypoPainter->FontPalette()[0].WriteTo(*mypoScreen, POS_X + 3, iY, "Choose a graphic:");
	//Draw
		Highlight(iHighlight);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_GraphicsList::Highlight(int iHighlight)
{	//Vars
		int iX, iY, iW, iH;
	//Const
		const int POS_X = 164;
		const int SPACE = 5;

	//Set the cursor
		iW = 138;
  		iH = mylimg.Length() * (TILE_HEIGHT + SPACE);
		iY = (mypoScreen->GetHeight() + iH) / 2 - iH;
		iX = POS_X;
		iY = iY += mypoPainter->FontPalette()[0].Height();
	//Draw graphics
		for(int i = 0; i < mylimg.Length(); i++)
		{	mylimg[i].BlitTo(*mypoScreen, iX, iY);
			mypoPainter->FontPalette()[0].WriteTo(*mypoScreen, iX + TILE_WIDTH + SPACE, iY + TILE_HEIGHT/2 - 15, Val(i));
			if(i != mylimg.Length() - 1)
			{	mypoScreen->DrawRectangle(iX-1, iY + TILE_HEIGHT + SPACE/2-2, TILE_WIDTH + SPACE * 3, 2, COLOR_GRAY, 200);
				mypoScreen->DrawRectangle(iX-1, iY + TILE_HEIGHT + SPACE/2-2, TILE_WIDTH + SPACE * 3 - 1, 1, COLOR_WHITE, 200);
			}
			if(iHighlight == i)
			{	mypoScreen->DrawFillRectangle(iX, iY, iW, TILE_HEIGHT, COLOR_WHITE, 0x99);
			}
			iY += TILE_HEIGHT + SPACE;
		}
	//Update screen
		mypoScreen->Update();
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LEDIT_GraphicsList::HandleKeys()
{	while(true)
	{	myoInput.Update();
		int iMouse = HandleMouse();
		if(iMouse >= 0) return iMouse;
 		     if(myoInput.KeyDown(SDLK_0)) {Highlight(0); while(myoInput.KeyDown(SDLK_0)) myoInput.Update(); return 0;}
		else if(myoInput.KeyDown(SDLK_1)) {Highlight(1); while(myoInput.KeyDown(SDLK_1)) myoInput.Update(); return 1;}
		else if(myoInput.KeyDown(SDLK_2)) {Highlight(2); while(myoInput.KeyDown(SDLK_2)) myoInput.Update(); return 2;}
		else if(myoInput.KeyDown(SDLK_3)) {Highlight(3); while(myoInput.KeyDown(SDLK_3)) myoInput.Update(); return 3;}
		else if(myoInput.KeyDown(SDLK_4)) {Highlight(4); while(myoInput.KeyDown(SDLK_4)) myoInput.Update(); return 4;}
		else if(myoInput.KeyDown(SDLK_5)) {Highlight(5); while(myoInput.KeyDown(SDLK_5)) myoInput.Update(); return 5;}
		else if(myoInput.KeyDown(SDLK_6)) {Highlight(6); while(myoInput.KeyDown(SDLK_6)) myoInput.Update(); return 6;}
		else if(myoInput.KeyDown(SDLK_7)) {Highlight(7); while(myoInput.KeyDown(SDLK_7)) myoInput.Update(); return 7;}
		else if(myoInput.KeyDown(SDLK_8)) {Highlight(8); while(myoInput.KeyDown(SDLK_8)) myoInput.Update(); return 8;}
		else if(myoInput.KeyDown(SDLK_9)) {Highlight(9); while(myoInput.KeyDown(SDLK_9)) myoInput.Update(); return 9;}
	}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LEDIT_GraphicsList::HandleMouse()
{	//Const
		const int POS_X = 164;
		const int SPACE = 5;

	//If the user is clicking
		if(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
		{	//Get the position
				int iMouseX = -1;
				int iMouseY = -1;
				
			//Wait for the mouse to be released
				while(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
				{	myoInput.Update();
				
					int iMouseX2 = myoInput.GetMouseX();
					int iMouseY2 = myoInput.GetMouseY();
					
					//If the mouse has moved re-draw
						if(iMouseX2 != iMouseX || iMouseY2 != iMouseY)
						{	iMouseX = iMouseX2;
							iMouseY = iMouseY2;
				
							//Translate iMouseY to a button
								int iTranslatedY = -1;
								int iW = 138;
						  		int iH = mylimg.Length() * (TILE_HEIGHT + SPACE);
								int iY = (mypoScreen->GetHeight() + iH) / 2 - iH;
								int iX = POS_X;
								iY = iY += mypoPainter->FontPalette()[0].Height();
								
								for(int i = 0; i < mylimg.Length() && iTranslatedY == -1; i++)
								{	if(iMouseY >= iY && iMouseY < iY + TILE_HEIGHT + 3)
									{	iTranslatedY = i;
									}
									iY += TILE_HEIGHT + SPACE;
								}
						
							//Do your magic
								     if(iTranslatedY == 0) {Draw(0);}
								else if(iTranslatedY == 1) {Draw(1);}
								else if(iTranslatedY == 2) {Draw(2);}
								else if(iTranslatedY == 3) {Draw(3);}
								else if(iTranslatedY == 4) {Draw(4);}
								else if(iTranslatedY == 5) {Draw(5);}
								else if(iTranslatedY == 6) {Draw(6);}
								else if(iTranslatedY == 7) {Draw(7);}
								else if(iTranslatedY == 8) {Draw(8);}
								else if(iTranslatedY == 9) {Draw(9);}
								else Draw(-1);
						}
				}
				
			//Get the position
				iMouseX = myoInput.GetMouseX();
				iMouseY = myoInput.GetMouseY();

			//Translate iMouseY to a button
				int iTranslatedY = -1;
				int iW = 138;
		  		int iH = mylimg.Length() * (TILE_HEIGHT + SPACE);
				int iY = (mypoScreen->GetHeight() + iH) / 2 - iH;
				int iX = POS_X;
				iY = iY += mypoPainter->FontPalette()[0].Height();
				
				for(int i = 0; i < mylimg.Length() && iTranslatedY == -1; i++)
				{	if(iMouseY >= iY && iMouseY < iY + TILE_HEIGHT + 3)
					{	iTranslatedY = i;
					}
					iY += TILE_HEIGHT + SPACE;
				}
				
			//Do your magic
				     if(iTranslatedY == 0) {Highlight(0); return 0;}
				else if(iTranslatedY == 1) {Highlight(1); return 1;}
				else if(iTranslatedY == 2) {Highlight(2); return 2;}
				else if(iTranslatedY == 3) {Highlight(3); return 3;}
				else if(iTranslatedY == 4) {Highlight(4); return 4;}
				else if(iTranslatedY == 5) {Highlight(5); return 5;}
				else if(iTranslatedY == 6) {Highlight(6); return 6;}
				else if(iTranslatedY == 7) {Highlight(7); return 7;}
				else if(iTranslatedY == 8) {Highlight(8); return 8;}
				else if(iTranslatedY == 9) {Highlight(9); return 9;}
		}

	//Return -1 for "no clicks"
		return(-1);
}
