/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			player.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "player.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Player
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Player::LL_Player()
	: myiVehicleObject(-1),
	  myiTorchTurns(0)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Player::Save(ofstream &oFile)
{	//%X Local%, %Y Local%, %Layer%
		oFile << Val(myiX) << " " << Val(myiY) << " " << Val(myiLayer) << " ";
	//%Vehicle Object% %Vehicle Code% %Torch Truns%
		oFile << Val(myiVehicleObject) << " " << Val(myoVehicle.Code()) << " "
  			  << Val(myiTorchTurns) << " ";
	//?Custom Image? "Image File" %Current Image%
		oFile << myfCustomImage << " " << Qoute(sImageFile) << " " << Val(myiCurrentImage) << " ";
	//<Creature information>
		//%Stength%, %Dexterity%, %Intelligence%
			oFile << myiStrength << " " << myiDexterity << " " << myiIntelligence << endl;
		//%MP%, %MaxMP%, %HP%, %MaxHP%
			oFile << myiMP << " " << myiMaxMP << " " << myiHP << " " << myiMaxHP << endl;
		//%Experience%
			oFile << myiExperience << endl;
	//<Inventory information>
		myoInventory.SaveRecordingInfo(oFile);
	//<Num Party Members>
		oFile << myloPartyMembers.Length() << " ";
	//<Save party members>
		for(int i = 0; i < myloPartyMembers.Length(); i++)
		{	myloPartyMembers[i].SaveRecordingInfo(oFile);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Player::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		int iX, iY, iLayer, iCode, iImageNum, iNumPartyMembers;

	//%X Local%, %Y Local%, %Layer%
		oFile >> iX >> iY >> iLayer;
	//%Vehicle% %Vehicle Code% %Torch Truns%
		oFile >> myiVehicleObject >> iCode >> myiTorchTurns;
	//?Custom Image? "Image File" %Current Image%
		oFile >> myfCustomImage;
  		sImageFile = ReadString(oFile);
    	oFile >> iImageNum;
    //<Creature information>
    	//%Stength%, %Dexterity%, %Intelligence%
			oFile >> myiStrength >> myiDexterity >> myiIntelligence;
		//%MP%, %MaxMP%, %HP%, %MaxHP%
			oFile >> myiMP >> myiMaxMP >> myiHP >> myiMaxHP;
		//%Experience%
			oFile >> myiExperience;
	//<Inventory information>
		myoInventory.LoadRecordingInfo(oFile, sGraphicsDir);
	//<Num Party Members>
		oFile >> iNumPartyMembers;
  		myloPartyMembers.Resize(iNumPartyMembers);
	//<Load party members>
		for(int i = 0; i < myloPartyMembers.Length(); i++)
		{	myloPartyMembers[i].LoadRecordingInfo(oFile, sGraphicsDir);
		}
	//Set it all up
		LoadAnimation(sImageFile, sGraphicsDir, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
		myiCurrentImage = iImageNum;
		myoVehicle.SetCode(iCode);
		Place(iX, iY);
}
//----------------------------------------------------------------------------------------- [Callbacks] -
void LL_Player::Run()
{	//Vars
		bool fDone = false;
		SDLKey tiKey = SDLKey(int(-1));
		SDLKey tiKey2 = SDLKey(int(-1));
		SDL_Event oEvent;
		
	//Check to see if the user is trying to close the window
		SDL_PumpEvents();
		if(SDL_PeepEvents(&oEvent, 1, SDL_PEEKEVENT, SDL_EVENTMASK(SDL_QUIT)) > 0)
        {	switch (oEvent.type)
	        {	case SDL_QUIT:
				{	myiUpdateValue = UPDATE_QUIT;
					return;
				}break;
			
				default:
				break;
            }
		}

	//Grab a key
 		mypoInput->Update();
		tiKey = SDLKey(mypoInput->GetKey(false, 250, 0));

	//Set the update value
		myiUpdateValue = UPDATE_OKAY;
	
   	//Decide what to do based on what keys are down
  	//- [Move North] -
  		if(tiKey == KEY_MOVE_NORTH)
   		{	//If north is off the map
   				if(Y() - 1 == TerrainMap()->MapBorderNorthY() - 1)
   				{	//Add a map move into the queue
   						EventQueue()->GoMapNorth();
					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
   				}
   			//If north is on the map
				else
       			{	mypoCon->Write("North", 0);
   					if(Move(DIR_NORTH))
    			   		MoveViewports(DIR_NORTH);
		  			else
						mypoCon->Write(" - blocked", 0);
					mypoCon->Write("\n", 0);
					
					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
				}
					
			fDone = true;
		}
		//- [Move South] -
		else if(tiKey == KEY_MOVE_SOUTH)
		{	//If south is off the map
     			if(Y() + 1 == TerrainMap()->MapBorderSouthY() + 1)
     			{	//Add a map move into the queue
   						EventQueue()->GoMapSouth();
					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
				}
       		//If south is on the map
       			else
       			{	mypoCon->Write("South", 0);
					if(Move(DIR_SOUTH))
						MoveViewports(DIR_SOUTH);
					else
						mypoCon->Write(" - blocked", 0);
					mypoCon->Write("\n", 0);
					
					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
				}
			
			fDone = true;
		}
		//- [Move West] -
		else if(tiKey == KEY_MOVE_WEST)
		{	//If west is off the map
   				if(X() - 1 == TerrainMap()->MapBorderWestX() - 1)
     			{	//Add a map move into the queue
   						EventQueue()->GoMapWest();
					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
     			}
			//If west is on the map
   				else
   				{	mypoCon->Write("West", 0);
					if(Move(DIR_WEST))
						MoveViewports(DIR_WEST);
					else
						mypoCon->Write(" - blocked", 0);
					mypoCon->Write("\n", 0);

					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
				}
			
			fDone = true;
		}
		//- [Move East] -
		else if(tiKey == KEY_MOVE_EAST)
		{	//If east is off the map
     			if(X() + 1 == TerrainMap()->MapBorderEastX() + 1)
     			{	//Add a map move into the queue
   						EventQueue()->GoMapEast();
					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
     			}
			//If east is on the map
				else
				{	mypoCon->Write("East", 0);
					if(Move(DIR_EAST))
						MoveViewports(DIR_EAST);
					else
						mypoCon->Write(" - blocked", 0);
					mypoCon->Write("\n", 0);
					
					//Set to player done
						myiUpdateValue = UPDATE_GO_DONE;
				}
			
			fDone = true;
		}
		//- [Pass] -
		else if(tiKey == KEY_PASS)
		{	mypoCon->Write("Pass...\n", 0);
			mypoClock->AddTicks(mypoClock->TicksPerMinute());
		
			//Set to player done
				myiUpdateValue = UPDATE_GO_DONE;
		
			fDone = true;
		}
		//- [Board] -
		else if(tiKey == KEY_BOARD)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("Board\n", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			//If we're on a vehicle board it
				if(mypoUnitMap->SegOn(myiX, myiY, LL_UnitMap::LAYER_VEHICLE) == LL_UnitMap::SEG_VEHICLE)
				{	//Change the player's vehicle to the vehicle of this vehicle object
						EventQueue()->BoardVehicle(myiX, myiY);
				}
			//Else nothing there
				else
				{	mypoCon->Write("Nothing to board\n", 1);
					mypoCon->Draw(0xFF);
					mypoScreen->Update();
				}
			//Yay! We're done!
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		//- [Exit] -
		else if(tiKey == KEY_EXIT)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("Exit\n", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			//Deboard it
				EventQueue()->DeboardVehicle();
			//We bes done
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		//- [Ignite] -
		else if(tiKey == KEY_IGNITE)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("Ignite\n", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			//If we have a torch ignite it
				if(myoInventory.TakeTorches(1))
				{	myiTorchTurns += TORCH_LENGTH;
				}
			//We bes done
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		//- [Talk] -
		else if(tiKey == KEY_TALK)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("Talk to what? <DIR> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			
			//Talk to the unit in the direction the user enters, if we failed to talk to a unit
				if(!TalkTo(PromptDirection()))
				{	mypoCon->Write("Can\'t talk there", 0);
				}
   		
       		//We be done
		       	mypoCon->Write("\n", 0);
				fDone = true;
				
			//Set to player done
				myiUpdateValue = UPDATE_GO_DONE;
		}
		//- [Look] -
		else if(tiKey == KEY_LOOK)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("Look where? <DIR> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			
			//Look to the tile in the direction the user enters
				LookTo(PromptDirection());

			//We be done
		       	mypoCon->Write("\n", 0);
				fDone = true;
		
			//Set to player done
				myiUpdateValue = UPDATE_GO_DONE;
		}
		//- [Push] -
		else if(tiKey == KEY_PUSH)
		{	//Set the update value, we be done
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
			//Write A message on the console, draw it too
	   			mypoCon->Write("Push what? <DIR> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			//Push
				PushTo(PromptDirection());
				mypoCon->Write("\n", 0);
		}
		//- [Search] -
		else if(tiKey == KEY_SEARCH)
		{	//Set the update value, we be done
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
			//Write A message on the console, draw it too
	   			mypoCon->Write("Search what? <DIR> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			//Search
				SearchTo(PromptDirection());
				mypoCon->Write("\n", 0);
		}
		//- [Attack] -
		else if(tiKey == KEY_ATTACK)
		{	//Set the update value, we be done
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
			//Write A message on the console, draw it too
	   			mypoCon->Write("Attack what? <DIR> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
		}
		//- [Get] -
		else if(tiKey == KEY_GET)
		{	//Set the update value, we be done
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
			//Write A message on the console, draw it too
	   			mypoCon->Write("Get what? <DIR> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
			//Get
				GetTo(PromptDirection());
				mypoCon->Write("\n", 0);
		}
		//- [Use] -
		else if(tiKey == KEY_USE)
		{	//Wait for the key to be depressed
				while(mypoInput->KeyDown(KEY_USE))
				{	mypoInput->Update();
				}
				
			//Write A message on the console, draw it too
	   			mypoCon->Write("Use what? <ITEM> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
				
   			//Call use and we be done
	  			EventQueue()->Use();
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		//- [Climb] -
		else if(tiKey == KEY_CLIMB)
		{	//Wait for the key to be depressed
				while(mypoInput->KeyDown(KEY_CLIMB))
				{	mypoInput->Update();
				}
				
			//Write A message on the console, draw it too
	   			mypoCon->Write("Climb <DIR> ", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();

			//Talk to the unit in the direction the user enters, if we failed to talk to a unit
				ClimbTo(PromptDirection());
   		
       		//We be done
		       	mypoCon->Write("\n", 0);
				fDone = true;
				
			//Set to player done
				myiUpdateValue = UPDATE_GO_DONE;
		}
		//- [ZStats] -
		else if(tiKey == KEY_ZSTATS)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("View stats", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
  
   			//Wait for the key to be depressed
				while(mypoInput->KeyDown(KEY_ZSTATS))
				{	mypoInput->Update();
				}
  
   			//Call ZStats and we be done
	  			EventQueue()->ZStats();
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		//- [Ready] -
		else if(tiKey == KEY_READY)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("Ready players", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
  
   			//Wait for the key to be depressed
				while(mypoInput->KeyDown(KEY_READY))
				{	mypoInput->Update();
				}
  
   			//Call ZStats and we be done
	  			EventQueue()->Ready();
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		//- [Help] -
		else if(tiKey == KEY_HELP || tiKey == KEY_HELP2)
		{	//Write A message on the console, draw it too
	   			mypoCon->Write("View help", 0);
				mypoCon->Draw(0xFF);
				mypoScreen->Update();
  
   			//Wait for the key to be depressed
				while(mypoInput->KeyDown(KEY_HELP) || mypoInput->KeyDown(KEY_HELP2))
				{	mypoInput->Update();
				}
  
   			//Call help and we be done
	  			EventQueue()->Help();
				myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		//- [Quit] -
		else if(tiKey == KEY_QUIT)
		{	//Set the update value, we be done
				myiUpdateValue = UPDATE_QUIT;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_W)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_w", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_w");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_E)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_e", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_e");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_Y)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_y", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_y");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_O)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_o", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_o");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_D)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_d", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_d");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_F)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_f", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_f");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_J)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_j", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_j");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_C)
		{	//Call global and the units under
				EventQueue()->CallUnitsUnder("onkey_c", myiX, myiY, myiLayer);
				EventQueue()->GosubGlobal("onkey_c");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_V)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_v", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_v");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_N)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_n", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_n");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		else if(tiKey == KEY_ONKEY_M)
		{	//Call global and the units under
	  			EventQueue()->CallUnitsUnder("onkey_m", myiX, myiY, myiLayer);
	  			EventQueue()->GosubGlobal("onkey_m");
	  		//We're done
	  			myiUpdateValue = UPDATE_GO_DONE;
				fDone = true;
		}
		
	//If we're done update the torch value
		if(myiUpdateValue == UPDATE_GO_DONE)
		{	//Reduce a torch turn
				myiTorchTurns -= 1;
				if(myiTorchTurns < 0)
					myiTorchTurns = 0;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Player::Talk()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Player::Look()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Player::Push()
{	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Player::Search()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Player::Attack()
{
}
//-------------------------------------------------------------------------------------------- [Running] -
bool LL_Player::Move(ASFC_DIRECTION iDirection)
{	//Vars
		int iDesiredX, iDesiredY;
		
	//Change the direction in our image
		ChangeDir(iDirection);

	//Figure out which tile the creature wants to move onto
		//Set the desired position to the current position
			iDesiredX = myiX;
			iDesiredY = myiY;
		
		//Offset this position based on the direction		
			OffsetCoods(iDesiredX, iDesiredY, iDirection);

	//If its legal to move
		if(mypoTerrainMap->MobilityTerrainMap()->LegalMove(mypoTerrainMap->GetTerrain(myiX, myiY).Code(),
			mypoTerrainMap->GetTerrain(iDesiredX, iDesiredY).Code(), myoVehicle.Code(), iDirection))
		{	//If there isn't an object blocking us
				if(mypoUnitMap->IsPassable(iDesiredX, iDesiredY, myiLayer))
				{	//Move to these coods
						MoveFromTo(myiX, myiY, iDesiredX, iDesiredY);
					//Move viewports
						MoveViewports(iDirection);
					//Update the clock
						mypoClock->AddTicks
      					(	mypoTerrainMap->MobilityTerrainMap()->Mobility
      						(	mypoTerrainMap->GetTerrain(iDesiredX, iDesiredY).Code(),
            					myoVehicle.Code()
      						).NormalTicks()
						);
					//Update the recognized player position (where monsters are attracted to)
						mypoUnitMap->SetKnownPlayerX(myiX);
						mypoUnitMap->SetKnownPlayerY(myiY);
						
					//We moved
						return true;
				}
		}
	//If we're moving on to a vehicle then its legal
		if(mypoUnitMap->SegOn(iDesiredX, iDesiredY, LL_UnitMap::LAYER_VEHICLE) ==
		  LL_UnitMap::SEG_VEHICLE)
		{	//If there isn't an object blocking us
				if(mypoUnitMap->IsPassable(iDesiredX, iDesiredY, myiLayer))
				{	//Move to these coods
						MoveFromTo(myiX, myiY, iDesiredX, iDesiredY);
					//We moved
						return true;
				}
		}
	//If we're moving off to a vehicle then its legal
		if(mypoUnitMap->SegOn(myiX, myiY, LL_UnitMap::LAYER_VEHICLE) == LL_UnitMap::SEG_VEHICLE)
		{	if(mypoTerrainMap->MobilityTerrainMap()->LegalMoveIn(mypoTerrainMap->GetTerrain(iDesiredX, iDesiredY).Code(), myoVehicle.Code(), iDirection))
			{	//If there isn't an object blocking us
					if(mypoUnitMap->IsPassable(iDesiredX, iDesiredY, myiLayer))
					{	//Move to these coods
							MoveFromTo(myiX, myiY, iDesiredX, iDesiredY);
						//Move viewports
							MoveViewports(iDirection);
						//Update the clock
							mypoClock->AddTicks
      						(	mypoTerrainMap->MobilityTerrainMap()->Mobility
      							(	mypoTerrainMap->GetTerrain(iDesiredX, iDesiredY).Code(),
            						myoVehicle.Code()
      							).NormalTicks()
							);
						//Update the recognized player position (where monsters are attracted to)
							mypoUnitMap->SetKnownPlayerX(myiX);
							mypoUnitMap->SetKnownPlayerY(myiY);
							
						//We moved
							return true;
					}
			}
		}


	//Return false
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Player::ChangeVehicle(int iVehicle)
{	//Vars

	//Change the vehicle code
		myoVehicle.SetCode(iVehicle);

//		string sVehicleGraphic;

	//Change the vehicle
//		myoVehicle.SetCode(oInfo.GrabInt(iVehicle));
	//Grab the default graphic
//		sVehicleGraphic = "error.png";
	//If this vehicle has a graphic associated with it load this graphic
//		for(int i = 0; i < myloVehicleGraphicKeys.Length(); i++)
//		{	if(myloVehicleGraphicKeys[i].iVehicleCode == iVehicle)
//			{	sVehicleGraphic = myloVehicleGraphicKeys[i].sReplacementGraphic;
//			}
//		}
	//Change the graphic
		
}
//P------------------------------------------------------------------------------------------ [Running] -P
//Moves various viewports so we focus on the player
void LL_Player::MoveViewports(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;

	//Move the terrain map
		//Figure out where we should move the map
			iX = mypoTerrainMap->ViewX();
			iY = mypoTerrainMap->ViewY();
			OffsetCoods(iX, iY, iDirection);
			
		//If iX is indeed a okay and on the map move the viewport
			if(iX >= 0 && iX + mypoTerrainMap->ViewportWidth() <= mypoTerrainMap->Width() &&
   			   myiX - iX == mypoTerrainMap->ViewportWidth()/2)
				mypoTerrainMap->SetViewX(iX);
		
		//If iY is indeed a okay and on the map move the viewport
			if(iY >= 0 && iY + mypoTerrainMap->ViewportHeight() <= mypoTerrainMap->Height() &&
   			   myiY - iY == mypoTerrainMap->ViewportHeight()/2)
					mypoTerrainMap->SetViewY(iY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Returns a direction based on what key is down
ASFC_DIRECTION LL_Player::PromptDirection()
{	//Loop until we return
	while(1 == 1)
	{	//Update Input
			mypoInput->Update();
 
 		//Decide what to do based on what keys are down
	  		//- [North] -
  			if(mypoInput->KeyDown(KEY_MOVE_NORTH))
     		{	mypoCon->Write("North", 0);
     			while(mypoInput->KeyDown(KEY_MOVE_NORTH)) mypoInput->Update();
       			return(DIR_NORTH);
			}
			
			//- [South] -
			else if(mypoInput->KeyDown(KEY_MOVE_SOUTH))
			{	mypoCon->Write("South", 0);
				while(mypoInput->KeyDown(KEY_MOVE_SOUTH)) mypoInput->Update();
   				return(DIR_SOUTH);
			}
			
			//- [Move West] -
			else if(mypoInput->KeyDown(KEY_MOVE_WEST))
			{	mypoCon->Write("West", 0);
				while(mypoInput->KeyDown(KEY_MOVE_WEST)) mypoInput->Update();
   				return(DIR_WEST);
			}
			
			//- [Move East] -
			else if(mypoInput->KeyDown(KEY_MOVE_EAST))
			{	mypoCon->Write("East", 0);
				while(mypoInput->KeyDown(KEY_MOVE_EAST)) mypoInput->Update();
   				return(DIR_EAST);
			}
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Talks to the unit in iDirection, returns true if a unit was called
bool LL_Player::TalkTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;
		
	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;

	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
		
	//Set the console up to output talk info
		mypoCon->Write("\n", 0);
		
	//Check all layers (from top to bottom) if any thing is found talk there
		for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
		{	//If a unit is in that direction
				if(mypoUnitMap->IsUnitOn(iX, iY, iLayer))
				{	//Add a talk event to the queue
						EventQueue()->Talk(Seg(), Off(), iX, iY);
				
					//We called a unit
						return(true);
				}
		}

	//We failed to talk to a unit if execution reaches here
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Looks to the unit or terrain in iDirection
bool LL_Player::LookTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;
		
	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;

	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
		
	//Set the console up to output talk info
		mypoCon->Write("\n", 0);
		
	//Add a look event to the queue
		EventQueue()->Look(Seg(), Off(), iX, iY);
		
	//Check all layers (from top to bottom) if any thing is found talk there
		for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
		{	//If a unit is in that direction
				if(mypoUnitMap->IsUnitOn(iX, iY, iLayer))
				{	//We called a unit
						return(true);
				}
		}
	//We failed to talk to a unit if execution reaches here
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Player::PushTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;
		
	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;

	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
		
	//Set the console up to output talk info
		mypoCon->Write("\n", 0);
		
	//Check all layers (from top to bottom) if any thing is found talk there
		for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
		{	//If a unit is in that direction
				if(mypoUnitMap->IsUnitOn(iX, iY, iLayer))
				{	//Add a look event to the queue
						EventQueue()->Push(Seg(), Off(), iX, iY);
    				//We called a unit
						return(true);
				}
		}
	//We failed to talk to a unit if execution reaches here
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Player::SearchTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;
		
	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;

	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
		
	//Set the console up to output talk info
		mypoCon->Write("\n", 0);
		
	//Check all layers (from top to bottom) if any thing is found talk there
		for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
		{	//If a unit is in that direction
				if(mypoUnitMap->IsUnitOn(iX, iY, iLayer))
				{	//Add a look event to the queue
						EventQueue()->Search(Seg(), Off(), iX, iY);
     				//We called a unit
						return(true);
				}
		}
	//We failed to talk to a unit if execution reaches here
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Player::AttackTo(ASFC_DIRECTION iDirection)
{	//!!! <CODE> !!!
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Player::GetTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;
		
	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;

	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
		
	//Set the console up to output talk info
		mypoCon->Write("\n", 0);
		
	//Check all layers (from top to bottom) if any thing is found talk there
		for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
		{	//If a unit is in that direction
				if(mypoUnitMap->IsUnitOn(iX, iY, iLayer))
				{	//Add a look event to the queue
						EventQueue()->Get(iX, iY);
     				//We called a unit
						return(true);
				}
		}
	//We failed to talk to a unit if execution reaches here
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Player::ClimbTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iOldCode;

	//Switch vehicles
		iOldCode = myoVehicle.Code();
		myoVehicle.SetCode(1);
	//Move in the proper direction
		//- [Move North] -
  			if(iDirection == DIR_NORTH)
	   		{	//If north is off the map
   					if(Y() - 1 < 0)
   					{	//Add a map move into the queue
   							EventQueue()->GoMapNorth();
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
   					}
   				//If north is on the map
					else
	       			{	mypoCon->Write(" ", 0);
   						if(Move(DIR_NORTH))
    				   		MoveViewports(DIR_NORTH);
		  				else
							mypoCon->Write(" - blocked", 0);
						mypoCon->Write("\n", 0);
						
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
					}
			}
			//- [Move South] -
			else if(iDirection == DIR_SOUTH)
			{	//If south is off the map
    	 			if(Y() + 1 >= TerrainMap()->Height())
     				{	//Add a map move into the queue
   							EventQueue()->GoMapSouth();
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
					}
    	   		//If south is on the map
       				else
       				{	mypoCon->Write(" ", 0);
						if(Move(DIR_SOUTH))
							MoveViewports(DIR_SOUTH);
						else
							mypoCon->Write(" - blocked", 0);
						mypoCon->Write("\n", 0);
						
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
					}
			}	
			//- [Move West] -
			else if(iDirection == DIR_WEST)
			{	//If west is off the map
   					if(X() - 1 < 0)
     				{	//Add a map move into the queue
   							EventQueue()->GoMapWest();
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
    	 			}
				//If west is on the map
   					else
	   				{	mypoCon->Write(" ", 0);
						if(Move(DIR_WEST))
							MoveViewports(DIR_WEST);
						else
							mypoCon->Write(" - blocked", 0);
						mypoCon->Write("\n", 0);
	
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
					}
			}
			//- [Move East] -
			else if(iDirection == DIR_EAST)
			{	//If east is off the map
     				if(X() + 1 >= TerrainMap()->Width())
     				{	//Add a map move into the queue
   							EventQueue()->GoMapEast();
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
    	 			}
				//If east is on the map
					else
					{	mypoCon->Write(" ", 0);
						if(Move(DIR_EAST))
							MoveViewports(DIR_EAST);
						else
							mypoCon->Write(" - blocked", 0);
						mypoCon->Write("\n", 0);
						
						//Set to player done
							myiUpdateValue = UPDATE_GO_DONE;
					}
			}
	//Switch vehicles back
		myoVehicle.SetCode(iOldCode);
	//Done
		return(true);
}
//---------------------------------------------------------------------------------------------- [Misc.] -
void LL_Player::Place(C_i2(iX, iY))
{	//Vars
		int iViewX, iViewY;

	//Remove the old place (if on a valid tile) !!! IsUnitOn Better Way??
		if(myiX >= 0 && myiX < TerrainMap()->Width() && myiY >= 0 && myiY < TerrainMap()->Height())
		{	if(UnitMap()->IsUnitOn(myiX, myiY, myiLayer))
			{	UnitMap()->SetUnitOn(myiX, myiY, myiLayer, LL_UnitMap::SEG_NULL, LL_UnitMap::OFF_NULL);
			}
		}
		
	//Now place the player
		myiX = iX;
		myiY = iY;
		UnitMap()->SetUnitOn(myiX, myiY, myiLayer, LL_UnitMap::SEG_PLAYER, LL_UnitMap::OFF_PLAYER);

	//Now figure out where the viewport should go
		//Set the viewport to the player position - 1/2 the viewport width/height
			iViewX = iX - PLAYFIELD_TILEWIDTH/2;
			iViewY = iY - PLAYFIELD_TILEHEIGHT/2;
		//If that projected viewport is too low slide it to the verrry edge
			if(iViewX < 0) iViewX = 0;
			if(iViewY < 0) iViewY = 0;

		//If that projected viewport is too hgih slide it to the verrry other edge
			if(iViewX + mypoTerrainMap->ViewportWidth() >= mypoTerrainMap->Width())
				iViewX = mypoTerrainMap->Width() - mypoTerrainMap->ViewportWidth();
			if(iViewY + mypoTerrainMap->ViewportHeight() >= mypoTerrainMap->Height())
				iViewY = mypoTerrainMap->Height() - mypoTerrainMap->ViewportHeight();

		//Now set those viewports	
			TerrainMap()->SetViewX(iViewX);
			TerrainMap()->SetViewY(iViewY);
/* !!!			UnitMap()->SetViewX(iViewX);
			UnitMap()->SetViewY(iViewY);

 	//Overlay the unit map ontop of the terrain map	
		UnitMap()->SetX(TerrainMap()->X());
		UnitMap()->SetY(TerrainMap()->Y());
*/
}
