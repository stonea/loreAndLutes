/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleplayer.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "battleplayer.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LL_BattlePlayer
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LL_BattlePlayer::LL_BattlePlayer()
{	//Defaults
		myfOnTurn = false;
		myiCurX = -1;
		myiCurY = -1;
		myiCurrentWeapon = 1;
		myoTimer.Reset();
		myfEscaped = false;
}
//-------------------------------------------------------------------------------------------- [Drawing] -
int LL_BattlePlayer::BlitTo(ASFC_Surface &screen, const int & iX, const int & iY)
{	//Blit it!
		if(mypoMember->State() == LL_PartyMember::STATE_DEAD)
			mypoCorpseImage->BlitTo(screen, iX, iY);
		else
			mylAnimations[myiCurrentImage].BlitTo(screen, iX, iY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattlePlayer::Reset()
{	mypoMember->Reset();
}
//------------------------------------------------------------------------------------------- [Updating] -
//Returns true if the player finished
bool LL_BattlePlayer::Run(ASFC_Surface &oScreen, int iRegisterNum)
{	//Var
		SDLKey tiKey = SDLKey(int(-1));
		SDLKey tiKey2 = SDLKey(int(-1));
		int iMapOffsetX, iMapOffsetY;

	//Switch weapons
		myiCurrentWeapon++;
		if(mypoMember->Weapon(myiCurrentWeapon) == LL_Creature::NO_EQUIP)
			myiCurrentWeapon = 1;
	//Determine the map offset (how many pixels the top left corner of this map is away from (0,0))
		iMapOffsetX = myiMapEdgeX * TILE_WIDTH;
		iMapOffsetY = myiMapEdgeY * TILE_HEIGHT;
	//If the player is dead or escaped skip over him (duh)
		if(mypoMember->State() == LL_PartyMember::STATE_DEAD || Escaped())
		{	return true;
		}
	//If the player is just starting his turn
		if(!myfOnTurn)
		{	//Reset all timers and vars
				myoTimer.Reset();
				myiBoxColor = 0xFF;
				myfBoxDown  = true;
				myfOnTurn = true;
			//Display which player's turn it is and which weapon they're using
				mypoConsole->Write("\n", 0);
				string s = mypoMember->Name();
				if(mypoMember->Weapon(myiCurrentWeapon) == LL_Creature::NO_EQUIP)
					s += " (hands)";
				else
				{	s += " (";
					s += ItemSet()->Weapon(mypoMember->Weapon(myiCurrentWeapon)).Identifier();
					s += ")";
				}
				s += " - \n";
				mypoConsole->Write(s, 1);
				mypoConsole->Draw(0xFF);
				oScreen.Update();
		}
	//While we haven't got a key
		//Switch the state of the select box and draw it if enough time has passed
				if(myoTimer.Ellapsed(BOX_DELAY))
				{	myoTimer.Reset();
					oScreen.DrawRectangle(	PLAYFIELD_X + int(myiX) * TILE_WIDTH - iMapOffsetX,
											PLAYFIELD_Y + int(myiY) * TILE_HEIGHT - iMapOffsetY,
        									TILE_WIDTH, TILE_HEIGHT, myiBoxColor, myiBoxColor,
											myiBoxColor, 0xFF);
					if(myfBoxDown)
						myiBoxColor -= BOX_DOWN_STEP;
  					else
  						myiBoxColor += BOX_DOWN_STEP;
					if(myiBoxColor < 0)
     				{	myiBoxColor = 0;
     					myfBoxDown = false;
     				}
     				if(myiBoxColor > 0xFF)
     				{	myfBoxDown = true;
     					myiBoxColor = 0xFF;
     				}
					oScreen.Update();
 				}
  			//Grab a key
		 		mypoInput->Update();
				tiKey = SDLKey(mypoInput->GetKey(false, 250, 0));
		   	//Decide what to do based on what keys are down
				//- [Move North] -
					if(tiKey == KEY_MOVE_NORTH)
					{	mypoConsole->Write("Move north\n", 0);
						mypoMember->ChangeDir(DIR_NORTH);
      					//If the player is off the map
							if(int(myiY)-1 - myiMapEdgeY < 0)
							{	mypoConsole->Write("Escape!\n", 2);
								EventQueue()->Escape(myiMemberNum);
								return true;
							}
						myiLastDirection = DIR_NORTH;
						Move(DIR_NORTH);
   						myfOnTurn = false;
   						return true;
					}
  				//- [Move South] -
					else if(tiKey == KEY_MOVE_SOUTH)
					{	mypoConsole->Write("Move south\n", 0);
						mypoMember->ChangeDir(DIR_SOUTH);
						//If the player is off the map
							if(int(myiY)+1-myiMapEdgeY >= PLAYFIELD_TILEHEIGHT)
							{	mypoConsole->Write("Escape!\n", 2);
								EventQueue()->Escape(myiMemberNum);
								return true;
							}
						Move(DIR_SOUTH);
						myiLastDirection = DIR_SOUTH;
   						myfOnTurn = false;
   						return true;
					}
  				//- [Move West] -
					else if(tiKey == KEY_MOVE_WEST)
					{	mypoConsole->Write("Move west\n", 0);
						mypoMember->ChangeDir(DIR_WEST);
						//If the player is off the map
							if(int(myiX)-1-myiMapEdgeX < 0)
							{	mypoConsole->Write("Escape!\n", 2);
								EventQueue()->Escape(myiMemberNum);
								return true;
							}
						Move(DIR_WEST);
						myiLastDirection = DIR_WEST;
						myfOnTurn = false;
						return true;
					}
		  		//- [Move East] -
					else if(tiKey == KEY_MOVE_EAST)
					{	mypoConsole->Write("Move east\n", 0);
						mypoMember->ChangeDir(DIR_EAST);
						//If the player is off the map
							if(int(myiX)+1-myiMapEdgeX >= PLAYFIELD_TILEWIDTH)
							{	mypoConsole->Write("Escape!\n", 2);
								EventQueue()->Escape(myiMemberNum);
								return true;
							}
						Move(DIR_EAST);
						myiLastDirection = DIR_EAST;
						myfOnTurn = false;
						return true;
					}
 				//- [Pass] -
 					else if(tiKey == SDLK_SPACE)
 					{	mypoConsole->Write("Pass turn\n", 0);
 						myfOnTurn = false;
 						return true;
 					}
  				//- [Talk]-
					else if(tiKey == KEY_TALK)
					{	//Write A message on the console, draw it too
			   				mypoConsole->Write("Talk to what? <DIR> ", 0);
							mypoConsole->Draw(0xFF);
							mypoScreen->Update();

						//Talk to the unit in the direction the user enters, if we failed to talk to a unit
							if(!TalkTo(PromptDirection()))
							{	mypoConsole->Write("Can\'t talk there", 0);
							}

       					//We be done
					       	mypoConsole->Write("\n", 0);
	     					myfOnTurn = false;
							return true;
					}
				//- [Look] -
					else if(tiKey == KEY_LOOK)
					{	//Write A message on the console, draw it too
				   			mypoConsole->Write("Look where? <DIR> ", 0);
							mypoConsole->Draw(0xFF);
							mypoScreen->Update();
						//Look to the tile in the direction the user enters
							LookTo(PromptDirection());
						//We be done
		    			   	mypoConsole->Write("\n", 0);
     						myfOnTurn = false;
	      					return true;
					}
				//- [Push] -
		 			else if(tiKey == KEY_PUSH)
		 			{	//Write A message on the console, draw it too
				   			mypoConsole->Write("Push what? <DIR> ", 0);
							mypoConsole->Draw(0xFF);
							mypoScreen->Update();
						//Push
							if(!PushTo(PromptDirection()))
							{	mypoConsole->Write("Nothing there", 0);
							}
							mypoConsole->Write("\n", 0);
						//We're done
	      					myfOnTurn = false;
			 				return true;
					}
				//- [Search] -
		 			else if(tiKey == KEY_SEARCH)
		 			{	//Write A message on the console, draw it too
				   			mypoConsole->Write("Search what? <DIR> ", 0);
							mypoConsole->Draw(0xFF);
							mypoScreen->Update();
						//Search
							if(!SearchTo(PromptDirection()))
							{	mypoConsole->Write("Nothing important", 0);
							}
							mypoConsole->Write("\n", 0);
						//Done
      						myfOnTurn = false;
		 					return true;
					}
				//- [Attack] -
					else if(tiKey == KEY_ATTACK)
					{	//Display an attack message
							mypoConsole->Write("Attack: ", 0);
						//Grab a location and attack
							int iAttackX, iAttackY;
							GrabLocation(&iAttackX, &iAttackY);
     						AttackTo(iAttackX, iAttackY);
						//Finishimo
	       					myfOnTurn = false;
    	   					return true;
					}
				//- [Get] -
					else if(tiKey == KEY_GET)
					{	//Write A message on the console, draw it too
				   			mypoConsole->Write("Get what? <DIR> ", 0);
							mypoConsole->Draw(0xFF);
							mypoScreen->Update();
						//Get
							if(!GetTo(PromptDirection()))
							{	mypoConsole->Write("Nothing there", 0);
							}
							mypoConsole->Write("\n", 0);
   						//We're done
	     					myfOnTurn = false;
							return true;
					}
				//- [Use] -
					else if(tiKey == KEY_USE)
					{	//Write A message on the console, draw it too
	     					mypoConsole->Write("Use what? <ITEM>\n", 0);
							mypoConsole->Draw(0xFF);
							oScreen.Update();
						//Wait for the key to be happy again
							while(mypoInput->KeyDown(KEY_USE))
							{	mypoInput->Update();
							}
			   			//Call ZStats and we be done
	  						EventQueue()->Use();
     					myfOnTurn = false;
     					return true;
					}
				//- [ZStats] -
					else if(tiKey == KEY_ZSTATS)
					{	//Write A message on the console, draw it too
				   			mypoConsole->Write("View stats\n", 0);
							mypoConsole->Draw(0xFF);
							oScreen.Update();
						//Wait for the key to be undepressed
							while(mypoInput->KeyDown(KEY_ZSTATS))
							{	mypoInput->Update();
							}
			   			//Call ZStats and we be done
	  						EventQueue()->ZStats();
     					myfOnTurn = false;
     					return true;
					}
 				//- [Set player 1-9]
					else if(tiKey == KEY_SET_PLAYER_1)
     				{	mypoConsole->Write("Set player 1\n", 0);
         				EventQueue()->SelectPlayer(0);
         				myfOnTurn = false;
         				return true;
         			}
		            else if(tiKey == KEY_SET_PLAYER_2)
     				{	mypoConsole->Write("Set player 2\n", 0);
         				EventQueue()->SelectPlayer(1);
         				myfOnTurn = false;
         				return true;
         			}
         			else if(tiKey == KEY_SET_PLAYER_3)
     				{	mypoConsole->Write("Set player 3\n", 0);
         				EventQueue()->SelectPlayer(2);
         				myfOnTurn = false;
         				return true;
         			}
         			else if(tiKey == KEY_SET_PLAYER_4)
     				{	mypoConsole->Write("Set player 4\n", 0);
         				EventQueue()->SelectPlayer(3);
         				myfOnTurn = false;
         				return true;
         			}
         			else if(tiKey == KEY_SET_PLAYER_5)
     				{	mypoConsole->Write("Set player 5\n", 0);
         				EventQueue()->SelectPlayer(4);
         				myfOnTurn = false;
         				return true;
         			}
         			else if(tiKey == KEY_SET_PLAYER_6)
     				{	mypoConsole->Write("Set player 6\n", 0);
         				EventQueue()->SelectPlayer(5);
         				myfOnTurn = false;
         				return true;
         			}
         			else if(tiKey == KEY_SET_PLAYER_7)
     				{	mypoConsole->Write("Set player 7\n", 0);
         				EventQueue()->SelectPlayer(6);
         				myfOnTurn = false;
         				return true;
         			}
         			else if(tiKey == KEY_SET_PLAYER_8)
     				{	mypoConsole->Write("Set player 8\n", 0);
         				EventQueue()->SelectPlayer(7);
         				myfOnTurn = false;
         				return true;
         			}
         			else if(tiKey == KEY_SET_PLAYER_9)
     				{	mypoConsole->Write("Set player 9\n", 0);
         				EventQueue()->SelectPlayer(8);
         				myfOnTurn = false;
         				return true;
         			}
				//- [Quit] -
					else if(tiKey == KEY_QUIT)
					{	//Wait for the key to be undepressed
							while(mypoInput->KeyDown(KEY_QUIT))
							{	mypoInput->Update();
							}
     					EventQueue()->QuickEscape();
     					myfOnTurn = false;
						return true;
					}
	//The player hasn't finished yet return false
	 	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattlePlayer::UpdateState()
{	//Is the player dead?
		if(mypoMember->HP() <= 0)
		{	mypoMember->SetState(LL_PartyMember::STATE_DEAD);
			mypoMember->SetHP(0);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattlePlayer::Damage(int iAmount)
{	//If this player is already dead say so and stop
		if(mypoMember->HP() <= 0)
		{	string s = mypoMember->Name();
			s += " is already dead!\n";
			mypoConsole->Write(s, 0);
			return;
		}
	//Calculate this damage against the player's defense value
  		int iDefense = DefenseValue();
 		if(iDefense > iAmount)
 			iAmount = 0;
		else
			iAmount -= iDefense;
	//Display the player is hit
		string s = mypoMember->Name();
		s += " is hit!\n";
		mypoConsole->Write(s, 1);
	//Based on the amount of damage display it
		if(iAmount <= 0)
			mypoConsole->Write("No damage\n", 0);
		else if(iAmount < float(mypoMember->MaxHP()) * .09)
			mypoConsole->Write("Scratched\n", 0);
		else if(iAmount < float(mypoMember->MaxHP()) * .19)
			mypoConsole->Write("Light damage\n", 0);
		else if(iAmount < float(mypoMember->MaxHP()) * .29)
			mypoConsole->Write("Heavy damage\n", 0);
		else if(iAmount < float(mypoMember->MaxHP()) * .39)
			mypoConsole->Write("Lightly wounded\n", 0);
		else if(iAmount < float(mypoMember->MaxHP()) * .49)
			mypoConsole->Write("Heavily wounded\n", 0);
		else
			mypoConsole->Write("Critical damage!\n", 0);
	//Inflict this damage
		mypoMember->SetHP(mypoMember->HP() - iAmount);
	//If the player is dead say so
		if(mypoMember->HP() <= 0)
			mypoConsole->Write("--~ Killed! ~--\n", 2);
	//Redraw
		mypoConsole->Draw(0xFF);
		mypoScreen->Update();
	//Update the state
		UpdateState();
}
//P----------------------------------------------------------------------------------------- [Updating] -
ASFC_DIRECTION LL_BattlePlayer::PromptDirection()
{	//Loop until we return
	while(1 == 1)
	{	//Update Input
			mypoInput->Update();

 		//Decide what to do based on what keys are down
	  		//- [North] -
  			if(mypoInput->KeyDown(KEY_MOVE_NORTH))
     		{	mypoConsole->Write("North", 0);
     			while(mypoInput->KeyDown(KEY_MOVE_NORTH)) mypoInput->Update();
       			return(DIR_NORTH);
			}
			//- [South] -
			else if(mypoInput->KeyDown(KEY_MOVE_SOUTH))
			{	mypoConsole->Write("South", 0);
				while(mypoInput->KeyDown(KEY_MOVE_SOUTH)) mypoInput->Update();
   				return(DIR_SOUTH);
			}
			//- [Move West] -
			else if(mypoInput->KeyDown(KEY_MOVE_WEST))
			{	mypoConsole->Write("West", 0);
				while(mypoInput->KeyDown(KEY_MOVE_WEST)) mypoInput->Update();
   				return(DIR_WEST);
			}
			//- [Move East] -
			else if(mypoInput->KeyDown(KEY_MOVE_EAST))
			{	mypoConsole->Write("East", 0);
				while(mypoInput->KeyDown(KEY_MOVE_EAST)) mypoInput->Update();
   				return(DIR_EAST);
			}
	}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LL_BattlePlayer::GrabLocation(int* piX, int* piY)
{	//Vars
		bool fDone = false;
		SDLKey tiKey = SDLKey(int(-1));
		SDLKey tiKey2 = SDLKey(int(-1));
		bool myfTransDown = true;
		int myiTrans = 0xFF;
		ASFC_Timer oTime;
		int iMapOffsetX, iMapOffsetY;
	//Const
		static const int KEY_DELAY = 50;

	//Determine the map offset (how many pixels the top left corner of this map is away from (0,0))
		iMapOffsetX = myiMapEdgeX * TILE_WIDTH;
		iMapOffsetY = myiMapEdgeY * TILE_HEIGHT;
	//Check to make sure the cursor is in a legal square (Aerial restrictions)
		if(!WithinRadius(myiCurX, myiCurY))
		{	myiCurX = int(myiX);
			myiCurY = int(myiY);
		}
	//If this is the first grab location set the cursor to the player's local
		if(myiCurX < 0 || myiCurY < 0)
		{	myiCurX = int(myiX);
			myiCurY = int(myiY);
		}
	//Draw a big box around the player
		mypoScreen->DrawRectangle(	PLAYFIELD_X + int(myiX) * TILE_WIDTH - iMapOffsetX,
									PLAYFIELD_Y + int(myiY) * TILE_HEIGHT - iMapOffsetY,
    								TILE_WIDTH, TILE_HEIGHT, COLOR_WHITE, 0xFF);
		mypoScreen->DrawRectangle(	PLAYFIELD_X + int(myiX) * TILE_WIDTH + 1 - iMapOffsetX,
									PLAYFIELD_Y + int(myiY) * TILE_HEIGHT + 1 - iMapOffsetY,
    								TILE_WIDTH-2, TILE_HEIGHT-2, COLOR_WHITE, 0xFF);
  	//Capture the screen
		ASFC_Surface oSurf1(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
		oSurf1.Blit(*mypoScreen, 0, 0);
	//Reset all timers and vars
		myoTimer.Reset();
		myiBoxColor = 0xFF;
		myfBoxDown  = true;
	//Loop forever (must hard break {return})
		while(true)
		{	//Grab a key
				SDLKey tiKey = SDLKey(int(-1));
   				while (tiKey == -1)
				{	//Grab a key
						oTime.Reset();
						mypoInput->Update();
						tiKey = SDLKey(mypoInput->GetKey(false, 250, 0));
	   				//Switch the state of the select box and draw it if enough time has passed
						if(myoTimer.Ellapsed(BOX_DELAY))
						{	oSurf1.BlitTo(*mypoScreen, 0, 0);
    						myoTimer.Reset();
							mypoScreen->DrawFillRectangle(	PLAYFIELD_X + myiCurX * TILE_WIDTH  - iMapOffsetX,
															PLAYFIELD_Y + myiCurY * TILE_HEIGHT  - iMapOffsetY,
        													TILE_WIDTH, TILE_HEIGHT, COLOR_RED, myiTrans);
		               		mypoScreen->DrawRectangle(	PLAYFIELD_X + myiCurX * TILE_WIDTH  - iMapOffsetX,
														PLAYFIELD_Y + myiCurY * TILE_HEIGHT  - iMapOffsetY,
        												TILE_WIDTH, TILE_HEIGHT,
            		      								myiBoxColor, myiBoxColor, myiBoxColor, 0xFF);
							mypoScreen->DrawRectangle(	PLAYFIELD_X + myiCurX * TILE_WIDTH + 1 - iMapOffsetX,
														PLAYFIELD_Y + myiCurY * TILE_HEIGHT + 1 - iMapOffsetY,
        												TILE_WIDTH - 2, TILE_HEIGHT - 2,
                  										myiBoxColor, myiBoxColor, myiBoxColor, 0xFF);
							if(myfBoxDown)
								myiBoxColor -= BOX_DOWN_STEP;
  							else
  								myiBoxColor += BOX_DOWN_STEP;
    						if(myfTransDown)
								myiTrans -= TRANS_DOWN_STEP;
	  						else
	  							myiTrans += TRANS_DOWN_STEP;
							if(myiBoxColor < 0)
     						{	myiBoxColor = 0;
     							myfBoxDown = false;
     						}
	     					if(myiBoxColor > 0xFF)
    	 					{	myfBoxDown = true;
	     						myiBoxColor = 0xFF;
    	 					}
     						if(myiTrans < 0)
     						{	myiTrans = 0;
	     						myfTransDown = false;
    	 					}
     						if(myiTrans > TRANS_HIGHEST)
	     					{	myfTransDown = true;
    	 						myiTrans = TRANS_HIGHEST;
     						}
							mypoScreen->Update();
 						}
	 			}
		   	//Decide what to do based on what keys are down
				//- [North] -
					if(tiKey == KEY_MOVE_NORTH)
					{	if(myiCurY-1-myiMapEdgeY >= 0 && WithinRadius(myiCurX, myiCurY-1))
     						myiCurY--;
					}
  				//- [South] -
					else if(tiKey == KEY_MOVE_SOUTH)
					{	if(myiCurY+1-myiMapEdgeY < PLAYFIELD_TILEHEIGHT && WithinRadius(myiCurX, myiCurY+1))
     						myiCurY++;
					}
  				//- [West] -
					else if(tiKey == KEY_MOVE_WEST && WithinRadius(myiCurX-1, myiCurY))
					{	if(myiCurX-1-myiMapEdgeX >= 0)
     						myiCurX--;
					}
		  		//- [East] -
					else if(tiKey == KEY_MOVE_EAST && WithinRadius(myiCurX+1, myiCurY))
					{	if(myiCurX+1-myiMapEdgeX < PLAYFIELD_TILEWIDTH)
     						myiCurX++;
					}
 				//- [Choose] -
 					else if(tiKey == KEY_CHOOSE || tiKey == KEY_CHOOSE2)
 					{	*piX = myiCurX;
						*piY = myiCurY;
 						return;
 					}
  			//Insure a delay
  				while(!oTime.Ellapsed(KEY_DELAY))
  					;
   				oTime.Reset();
 		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LL_BattlePlayer::AttackTo(int iX, int iY)
{	//Set the console up to output attack info
		string s;
		s = Val(iX);
		s += " ";
		s += Val(iY);
		s += "\n";
		mypoConsole->Write(s, 0);
	//Calculate the distance
		double dDistance = sqrt(pow(double(iX - myiX), 2) + pow(double(iY - myiY), 2));
	//Attack there
		EventQueue()->Attack(LL_UnitMap::SEG_PLAYER, myiMemberNum, iX, iY, AttackValue(int(dDistance)));
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LL_BattlePlayer::OffsetCoods(int &iX, int &iY, ASFC_DIRECTION iDirection)
{	//Offset this position based on the direction
		switch(iDirection)
		{	case DIR_EAST:			{iX++;			}break;
			case DIR_NORTH_EAST:	{iY--; iX++;	}break;
			case DIR_NORTH:			{iY--;			}break;
			case DIR_NORTH_WEST:	{iY--; iX--;	}break;
			case DIR_WEST:			{iX--;			}break;
			case DIR_SOUTH_WEST:	{iY++; iX--;	}break;
			case DIR_SOUTH:			{iY++;			}break;
			case DIR_SOUTH_EAST:	{iY++; iX++;	}break;
			default: break;
		};
}
//P------------------------------------------------------------------------------------ [Calculations] -P
int LL_BattlePlayer::AttackValue(int iDistance)
{	//Vars
		int iAttack;
		int iAttackSkill;
		double dStrengthConstant;
		double dHitConstant;
		int iMinAttack;

	//If the player has no weapons the attack value is always (1/16) * strength
		if(mypoMember->Weapon(myiCurrentWeapon) == LL_Creature::NO_EQUIP)
		{	iAttack = (1.0/16.0) * float(mypoMember->Strength());
			dHitConstant = 0;
		}
	//For ground weapons Attack value = ((Str)^.8/7500)(Attack)^2 + 1
		else
		{	dStrengthConstant =  pow(double(mypoMember->Strength()), 0.8)/7500;
			iAttackSkill = ItemSet()->Weapon(mypoMember->Weapon(myiCurrentWeapon)).AttackSkill();
			iAttack = dStrengthConstant * iAttackSkill * iAttackSkill + 1;
			dHitConstant = double(mypoMember->Dexterity()) / 200.0;
			
			//If this weapon is airreal and its being used in close range quarter its attack
				if(ItemSet()->Weapon(mypoMember->Weapon(myiCurrentWeapon)).Radius() > 1)
				{	if(iDistance <= 1)
					{	iAttack -= iAttack / 4;
					}
				}
		}
	//Determine the minimum attack value. It is equal to (Dex / 200) * iAttack
		iMinAttack   = dHitConstant * iAttack;
	//Pick a value between iMinAttack and iAttack
		int iRand = PollRandom(iAttack - iMinAttack); //This is correct
		iAttack      = iMinAttack + iRand;
		
		return(iAttack);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
int LL_BattlePlayer::DefenseValue()
{	//Vars
		int iDefense = 0;
		int iMinDefense;
		double dStrengthConstant = double(mypoMember->Strength()) / 1000.0;
		double dHitConstant;
	//Defense Value = (Str/1000)DefenseValArm1 + (Str/1000)DefenseValArm2 + (Str/1000)DefenseValArm3
		if(mypoMember->Armor(1) != LL_Creature::NO_EQUIP)
			iDefense += dStrengthConstant * ItemSet()->Armor(mypoMember->Armor(1)).Defense();
		if(mypoMember->Armor(2) != LL_Creature::NO_EQUIP)
			iDefense += dStrengthConstant * ItemSet()->Armor(mypoMember->Armor(2)).Defense();
		if(mypoMember->Armor(3) != LL_Creature::NO_EQUIP)
			iDefense += dStrengthConstant * ItemSet()->Armor(mypoMember->Armor(3)).Defense();
	//Get a minimum hit constant
		dHitConstant = double(mypoMember->Dexterity()) / 200.0;
		iMinDefense   = dHitConstant * iDefense;
	//Pick a value between iMinAttack and iDefense
		int iRand = PollRandom(iDefense - iMinDefense); //Correct
		iDefense     = iMinDefense + iRand;
	//Return this defense
		return(iDefense);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LL_BattlePlayer::WithinRadius(int iX, int iY)
{	//Vars
		int iRadius;
		double dDistance;
		
	//Calculate the radius
		if(mypoMember->Weapon(myiCurrentWeapon) == LL_Creature::NO_EQUIP)
     		iRadius = 1;
   		else
   			iRadius = ItemSet()->Weapon(mypoMember->Weapon(myiCurrentWeapon)).Radius();
  	//Determine if it's within (Distance = sqrt((x2 - x1)^2 + (y2 - y1)^2))
		dDistance = sqrt(pow(double(iX - myiX), 2) + pow(double(iY - myiY), 2));
	//Is it within?
		if(int(dDistance) <= iRadius)
			return true;
		return false;
}
//-------------------------------------------------------------------------------------- [Basic Actions] -
//Talks to the unit in iDirection, returns true if a unit was called
bool LL_BattlePlayer::TalkTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;

	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;

	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);

	//Set the console up to output talk info
		mypoConsole->Write("\n", 0);

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
bool LL_BattlePlayer::LookTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;

	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;
	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
	//Set the console up to output talk info
		mypoConsole->Write("\n", 0);
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
bool LL_BattlePlayer::PushTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;

	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;
	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
	//Set the console up to output talk info
		mypoConsole->Write("\n", 0);
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
bool LL_BattlePlayer::SearchTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;

	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;
	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
	//Set the console up to output talk info
		mypoConsole->Write("\n", 0);
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
bool LL_BattlePlayer::GetTo(ASFC_DIRECTION iDirection)
{	//Vars
		int iX, iY;

	//Set iX, iY to the player's location
		iX = myiX;
		iY = myiY;
	//Translate this direction to a location
		OffsetCoods(iX, iY, iDirection);
	//Set the console up to output talk info
		mypoConsole->Write("\n", 0);
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
