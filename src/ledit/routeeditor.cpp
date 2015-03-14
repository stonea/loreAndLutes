/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			routeeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "routeeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_RouteEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_RouteEditor::LEDIT_RouteEditor(LL_Game* poGame)
{	//Map vars
		mypoGame = poGame;
		mypoPathNodes = &poGame->PathNodes();

	//Load up the arrow images
		myimgArrowN.LoadImage(LEDIT_RouteEditor__IMAGE_ARROW_NORTH, COLOR_BLUE);
  		myimgArrowS.LoadImage(LEDIT_RouteEditor__IMAGE_ARROW_SOUTH, COLOR_BLUE);
		myimgArrowW.LoadImage(LEDIT_RouteEditor__IMAGE_ARROW_WEST,  COLOR_BLUE);
  		myimgArrowE.LoadImage(LEDIT_RouteEditor__IMAGE_ARROW_EAST,  COLOR_BLUE);
  		
	//Create a fake lighting matrix that'll display all
		mylNoLight.Resize(11, 11);
		for(int iY = 0; iY < 11; iY++)
			for(int iX = 0; iX < 11; iX++)
				mylNoLight[iX][iY] = true;
}
//------------------------------------------------------------------------------------- [Editting routes] -
void LEDIT_RouteEditor::EditRoute(LL_Game* poGame, int iStartX, int iStartY)
{	//Vars
		SDLKey iKey;
			
	//Wait for all keys to be released
		int tiKey = -2;
		while (tiKey != -1)
		{	myoInput.Update();
			tiKey = SDLKey(myoInput.GetKey(false, 250, 0));
		}

	//Map vars
		mypoPathNodes = &poGame->PathNodes();
		mypoGame = poGame;
		myiCurX = iStartX;
  		myiCurY = iStartY;

	//Create a new route here
		LL_Route toRoute;
		toRoute.SetX(iStartX);
		toRoute.SetY(iStartY);
		mypoPathNodes->AddRoute(toRoute);
		mypoRoute = &mypoPathNodes->Route(mypoPathNodes->NumRoutes() - 1);
  		
	//Set defaults
		myfCursorBlink = false;
		myoCursorBlinkTimer.Reset();
		myfEditting = true;
		myfGemView  = false;
		
	//Grab the node here
		myiStartNode = mypoPathNodes->NodeOn(myiCurX, myiCurY);
		mypStartNode = &mypoPathNodes->Node(myiStartNode);
		
	//Redraw
		Draw();
		
	//While we're still editting edit!
		while(myfEditting)
		{	//Get a key, Handle it
				iKey = GrabKey();
				HandleKey(iKey);
			//Check to see if we're over a node (and the route is > 0 nodes!)
				if(mypoPathNodes->NodeOn(myiCurX, myiCurY) != mypoPathNodes->NO_NODE && mypoRoute->Length() > 0)
		  			myfEditting = false;
		   	//Draw
				Draw();
		}
		
	//Now set the route ending values
		mypoRoute->SetEndX(myiCurX);
		mypoRoute->SetEndY(myiCurY);
		
	//Now update node values
		myiEndNode = mypoPathNodes->NodeOn(myiCurX, myiCurY);
		mypEndNode = &mypoPathNodes->Node(myiEndNode);
		mypStartNode->myfStart.push_back(true);
		mypStartNode->myiNodes.push_back(myiEndNode);
		mypStartNode->myiRoutes.push_back(mypoPathNodes->NumRoutes() - 1);
		mypEndNode->myfStart.push_back(false);
		mypEndNode->myiNodes.push_back(myiStartNode);
		mypEndNode->myiRoutes.push_back(mypoPathNodes->NumRoutes() - 1);
}
//-------------------------------------------------------------------------------------------- [Drawing] -
void LEDIT_RouteEditor::DrawRoute(int iCurX, int iCurY)
{	//Vars
		int iX;
		int iY;
		int iCornerX, iCornerY, iCornerX2, iCornerY2;
		int iPixX, iPixY;
		LL_Route* poRoute;
		int iCursorOnRoute;
		
	//Calculate the corners of the screen (tile wise)
		iCornerX  = iCurX - PLAYFIELD_TILEWIDTH/2;
		iCornerY  = iCurY - PLAYFIELD_TILEHEIGHT/2;
		iCornerX2 = iCornerX + PLAYFIELD_TILEWIDTH;
		iCornerY2 = iCornerY + PLAYFIELD_TILEHEIGHT;
		
	//Calculate which route the cursor is on
		iCursorOnRoute = mypoPathNodes->RouteOn(iCurX, iCurY);

	//Loop through all the routes
		for(int iRoute = 0; iRoute < mypoPathNodes->NumRoutes(); iRoute++)
		{	//Grab a pointa' to this route
				poRoute = &mypoPathNodes->Route(iRoute);

			//Define the starting point
				iX = poRoute->X();
				iY = poRoute->Y();

			//Loop through all elements in the route
				for(int i = 0; i < poRoute->Length(); i++)
				{	//If this local is on the screen draw there
						if(iX >= iCornerX && iX < iCornerX2 && iY >= iCornerY && iY < iCornerY2)
						{	//Calculamate the pixel location of this tile
								iPixX = (iX - iCornerX) * TILE_WIDTH  + PLAYFIELD_X;
								iPixY = (iY - iCornerY) * TILE_HEIGHT + PLAYFIELD_Y;
    
		    				//Draw the appropriate arrow
								if((*poRoute)[i] == DIR_NORTH)
									myimgArrowN.BlitTo(*mypoScreen, iPixX, iPixY);
								else if((*poRoute)[i] == DIR_SOUTH)
									myimgArrowS.BlitTo(*mypoScreen, iPixX, iPixY);
								else if((*poRoute)[i] == DIR_WEST)
									myimgArrowW.BlitTo(*mypoScreen, iPixX, iPixY);
								else if((*poRoute)[i] == DIR_EAST)
									myimgArrowE.BlitTo(*mypoScreen, iPixX, iPixY);
									
							//If the route is on this cursor draw a trans yellow marker
								if(iCursorOnRoute == iRoute)
									mypoScreen->DrawFillRectangle(iPixX, iPixY, TILE_WIDTH, TILE_HEIGHT,
																  COLOR_YELLOW, 150);
						}
		
					//Move the cursor based on how the route goes
							 if((*poRoute)[i] == DIR_NORTH) iY--;
						else if((*poRoute)[i] == DIR_SOUTH) iY++;
						else if((*poRoute)[i] == DIR_WEST)  iX--;
						else if((*poRoute)[i] == DIR_EAST)  iX++;
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_RouteEditor::DrawGemViewRoute()
{	//Vars
		int iX;
		int iY;
		int iTileWidth, iTileHeight, iStartX, iStartY;
		LL_Route* poRoute;

	//Calculate various locals on the screen
		iTileWidth = (PLAYFIELD_X2 - PLAYFIELD_X) / 100;
		iTileHeight= (PLAYFIELD_Y2 - PLAYFIELD_Y) / 100;
 		iStartX = PLAYFIELD_X + ((PLAYFIELD_X2 - PLAYFIELD_X) - (iTileWidth  * 100))/2;
 		iStartY = PLAYFIELD_Y + ((PLAYFIELD_Y2 - PLAYFIELD_Y) - (iTileHeight * 100))/2;

	//Loop through all routes
		for(int iRoute = 0; iRoute < mypoPathNodes->NumRoutes(); iRoute++)
		{	//Grab a pointa' to this route
				poRoute = &mypoPathNodes->Route(iRoute);

			//Define the starting point
				iX = poRoute->X();
				iY = poRoute->Y();
	
			//Loop through all elements in the route
				for(int i = 0; i < poRoute->Length(); i++)
				{	//Draw a rectangle at this local
						mypoScreen->DrawFillRectangle(iStartX + iTileWidth * iX, iStartY + iTileHeight * iY,
												  iTileWidth, iTileHeight, COLOR_GREEN, 150);
						mypoScreen->DrawFillRectangle(iStartX + iTileWidth * iX+1, iStartY + iTileHeight * iY+1,
												  iTileWidth-2, iTileHeight-2, COLOR_WHITE, 150);
										  
					//Move the cursor based on how the route goes
							 if((*poRoute)[i] == DIR_NORTH) iY--;
						else if((*poRoute)[i] == DIR_SOUTH) iY++;
						else if((*poRoute)[i] == DIR_WEST)  iX--;
						else if((*poRoute)[i] == DIR_EAST)  iX++;
				}
		}
}
//P----------------------------------------------------------------------------------------- [Editting] -P
SDLKey LEDIT_RouteEditor::GrabKey()
{	//Vars
		SDLKey tiKey  = SDLKey(int(-1));
		SDLKey tiKey2 = SDLKey(int(-1));

	while (tiKey == -1)
	{	myoInput.Update();
		tiKey = SDLKey(myoInput.GetKey(false, 250, 0));
		
		//If we're in gem view redraw the cursor
			if(myfGemView)
			{	DrawGemViewCursor();
				Screen()->Update();
			}
	}

	if(!(tiKey == KEY_MOVECUR_NORTH || tiKey ==	KEY_MOVECUR_NORTH2 || tiKey == KEY_MOVECUR_SOUTH ||
		 tiKey == KEY_MOVECUR_SOUTH2|| tiKey ==	KEY_MOVECUR_WEST   || tiKey == KEY_MOVECUR_WEST2 ||
		 tiKey == KEY_MOVECUR_EAST  || tiKey ==	KEY_MOVECUR_EAST2))
	{
		tiKey2 = tiKey;

		while(tiKey2 == tiKey || myoInput.KeyDown(tiKey))
		{	tiKey2 = SDLKey(myoInput.GetKey(false, 250, 0));
			myoInput.Update();
		}
	}
	
	//Translate repeated keys
		if(tiKey == KEY_EXIT2 || tiKey == KEY_EXIT3 || tiKey == KEY_EXIT4) tiKey = KEY_EXIT;
	
	//Return this key
		return(tiKey);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_RouteEditor::HandleKey(SDLKey iKey)
{	//- [North] -
		if(iKey == KEY_MOVECUR_NORTH)
		{	myiCurY--;
			mypoRoute->Push(DIR_NORTH);
		}
	//- [South] -
		else if(iKey == KEY_MOVECUR_SOUTH)
		{	myiCurY++;
			mypoRoute->Push(DIR_SOUTH);
		}
	//- [West] -
		else if(iKey == KEY_MOVECUR_WEST)
		{	myiCurX--;
			mypoRoute->Push(DIR_WEST);
		}
	//- [East] -
		else if(iKey == KEY_MOVECUR_EAST)
		{	myiCurX++;
			mypoRoute->Push(DIR_EAST);
		}
	//- [Switch gem view] -
		else if(iKey == KEY_GEM_VIEW)
		{	myfGemView = !myfGemView;
		}
	//- [Exit] -
		else if(iKey == KEY_EXIT)
		{	//Make sure the user is on a node
				if(mypoPathNodes->NodeOn(myiCurX, myiCurY) != mypoPathNodes->NO_NODE)
		  			myfEditting = false;
		}
}
//P------------------------------------------------------------------------------------------- [Drawing] -P
void LEDIT_RouteEditor::Draw()
{	//Always draw the quick keys, aren't I nice providing you with all this help :-)
		DrawQuickKeys();
		mypoPainter->TalkConsole().Draw(0xFF);

	//If we're in gem view
		if(myfGemView)
		{	//Draw gem view and path nodes
				mypoGame->TerrainMap().DrawGemView(*Screen());
				
			//Draw route
				DrawGemViewRoute();
				
			//Draw path nodes
				mypoGame->PathNodes().DrawGemView(*Screen());
		
			//Draw gem view cursor
				DrawGemViewCursor();

			//Update graphics		
				Screen()->Update();
		}
		
	//Else if we're in zoomed in view
		else
		{	//Move viewports to the correct local
				MoveViewports();
  		
    		//Draw terrain, unit, and path finding (if necessary), maps
				mypoGame->TerrainMap().Draw(*mypoScreen, mylNoLight);
				mypoPainter->DrawUnitMap(&mylNoLight);
				mypoGame->PathNodes().Draw(*mypoScreen, myiCurX - PLAYFIELD_TILEWIDTH/2,
										   myiCurY - PLAYFIELD_TILEHEIGHT/2, PLAYFIELD_X, PLAYFIELD_Y);
										   
			//Draw the route
				DrawRoute(myiCurX, myiCurY);
			
			//Draw the cursor
				mypoPainter->Cursor().BlitTo(*mypoScreen,
  									(PLAYFIELD_X2 - PLAYFIELD_X)/2 - TILE_WIDTH/2  + PLAYFIELD_X,
									(PLAYFIELD_Y2 - PLAYFIELD_Y)/2 - TILE_HEIGHT/2 + PLAYFIELD_Y);
			//Update
				mypoScreen->Update();
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_RouteEditor::DrawGemViewCursor()
{	//Vars
		int iTileWidth, iTileHeight, iStartX, iStartY;

	//If enough time has passed change the cursor blink setting
		if(myoCursorBlinkTimer.Ellapsed(CURSOR_BLINK_RATE))
		{	myfCursorBlink = !myfCursorBlink;
			myoCursorBlinkTimer.Reset();
		}

	//Calculate various locals on the screen
		iTileWidth = (PLAYFIELD_X2 - PLAYFIELD_X) / 100;
		iTileHeight= (PLAYFIELD_Y2 - PLAYFIELD_Y) / 100;
 		iStartX = PLAYFIELD_X + ((PLAYFIELD_X2 - PLAYFIELD_X) - (iTileWidth  * 100))/2;
 		iStartY = PLAYFIELD_Y + ((PLAYFIELD_Y2 - PLAYFIELD_Y) - (iTileHeight * 100))/2;
 		
	//If cursor is on blink true draw red, else draw blue
		if(myfCursorBlink)
			mypoScreen->DrawFillRectangle(iStartX + iTileWidth * myiCurX, iStartY + iTileHeight * myiCurY,
										  iTileWidth, iTileHeight, COLOR_RED, 150);
		else
			mypoScreen->DrawFillRectangle(iStartX + iTileWidth * myiCurX, iStartY + iTileHeight * myiCurY,
										  iTileWidth, iTileHeight, COLOR_BLUE, 150);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_RouteEditor::MoveViewports()
{	//Only so that myiCurX, myiCurY is centered
	   	mypoGame->TerrainMap().SetViewX(myiCurX - PLAYFIELD_TILEWIDTH/2);
	   	mypoGame->TerrainMap().SetViewY(myiCurY - PLAYFIELD_TILEHEIGHT/2);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_RouteEditor::DrawQuickKeys()
{	//Be a good editor and always offer help
		mypoPainter->TalkConsole().Clear();
		mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->TalkConsole() << "Arrows: Direct Route\n";
		mypoPainter->TalkConsole() << "G:      Switch gem view\n";
		mypoPainter->TalkConsole() << "Esc:    Finish Route\n";
}
