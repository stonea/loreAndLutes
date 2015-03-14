/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battle.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "battle.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LRUN_Battle
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LRUN_Battle::LRUN_Battle()
{	//Empty light matrix
		lLight.Resize(100, 100);
		for(int iY = 0; iY < 100; iY++)
			for(int iX = 0; iX < 100; iX++)
				lLight[iX][iY] = true;
	myoTimer.Reset();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LRUN_Battle::Setup(LL_Game* poGame, LL_LOOPLib_LoreLinker* poLOOPLibLinker,
						LL_LOOPLib_Lore* poLOOPLib, LL_Painter* poPaint, ASFC_Screen* poScreen,
     					ASFC_Effects* poEffects, ASFC_Input* poInput, LL_ZStats* poZStats)
{	//Map the vars
		mypoLOOPLibLinker = poLOOPLibLinker;
		mypoLOOPLib	= poLOOPLib;
		mypoGame	= poGame;
		mypoPaint	= poPaint;
		mypoScreen	= poScreen;
		mypoEffects = poEffects;
		mypoInput	= poInput;
		mypoZStats  = poZStats;
	//Load the dead image !!!!!!!!!!!!!!!!!!!!
		string sImage = "./games/lore";
  		sImage += LRUN__DEAD_IMAGE;
		myoDeadImage.Load(sImage, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
		sImage = "./games/lore";
  		sImage += LRUN__HIT_IMAGE;
	    myoHitImage.Load(sImage, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
	//Load the battle information
/*		mypoGame->SetInBattleMode(true);
		mypoGame->LoadMap(-1);
		mypoGame->Classes("", mypoScreen);
		mypoGame->SetInBattleMode(false);
*/
}
//---------------------------------------------------------------------------------------------- [Attack] -
bool LRUN_Battle::Attack(int iMonster, int iBattleMap, int iMonsterSeg, int iMonsterOff, int* piDir)
{	//Switch to battle mode *click*
		mypoGame->SetInBattleMode(true);
	//Load the battle info
		mypoGame->ReloadBattleInfo();
	//Link and load
		mypoLOOPLibLinker->Link(mypoGame, mypoLOOPLib);
	//Store params
		myiMonster = iMonster;
		myiMonsterSeg = iMonsterSeg;
		myiMonsterOff = iMonsterOff;
		myiBattleMap = iBattleMap;
		mypiExitDir = piDir;
		*mypiExitDir = -1;
	//Move to the appropriate map
		myiViewX = mypoGame->BattleMap().MapEdgeX(myiBattleMap);
		myiViewY = mypoGame->BattleMap().MapEdgeY(myiBattleMap);
		myiMapEdgeX = mypoGame->BattleMap().MapEdgeX(myiBattleMap);
  		myiMapEdgeY = mypoGame->BattleMap().MapEdgeY(myiBattleMap);
	//Setup friends and foes
		mypoGame->BattleUnitMap().ClearBattleUnits();
		PlaceParty();
		PlaceEnemies();
	//Say we're attacking
		mypoPaint->TalkConsole() << "Battle on!\n";
	//Clear the queue
		mypoGame->EventQueue().Clear();
	//Perform an effect
		PerformEffect(BORDER_EFFECT_BLEND);
	//Wait for all keys to be released
		while(mypoInput->GetKey() != -1)
			mypoInput->Update();

	while(mypoInput->KeyUp(SDLK_f))
	{  	Run();
		mypoInput->Update();
		//If all player's are gone exit
			if(!mypoGame->BattleUnitSet().AnyPlayers())
			{	if(!mypoGame->BattleUnitSet().AnyEnemies())
				{	mypoPaint->TalkConsole() << "Victory!\n";
					mypoGame->SetInBattleMode(false);
					return true;
				}
				mypoGame->SetInBattleMode(false);
				return false;
			}
	}

	//Return true if all enemies are dead
		if(!mypoGame->BattleUnitSet().AnyEnemies())
		{	mypoPaint->TalkConsole() << "Victory!\n";
			mypoGame->SetInBattleMode(false);
			return true;
		}
		mypoGame->SetInBattleMode(false);
		return false;

	//Switch off battle mode *click*
		mypoGame->SetInBattleMode(false);
}
//P-------------------------------------------------------------------------------------------- [Engine] -P
void LRUN_Battle::Run()
{	//Vars
		ASFC_Timer oDelayer;
		oDelayer.Reset();
	//Update queue
		UpdateQueue();
	//Redraw
 		Draw();
		mypoScreen->Update();
	//Update players
		for(myiRunning = 0; myiRunning < mypoGame->BattleUnitSet().NumPlayers(); myiRunning++)
		{	//If we don't have a selected player
					//Update
			  			while(!mypoGame->BattleUnitSet().Player(myiRunning).Run(*mypoScreen, myiRunning))
	  					{	//Redraw
	  							myiRunningPlayer = mypoGame->BattleUnitSet().Player(myiRunning).MemberNum();
						 		Draw();
			  			}
			  			mypoLOOPLib->SetBattlePlayerX(mypoGame->BattleUnitSet().Player(myiRunning).X());
			  			mypoLOOPLib->SetBattlePlayerY(mypoGame->BattleUnitSet().Player(myiRunning).Y());
  						UpdateQueue();
					//Redraw
						if(myiRunning < mypoGame->BattleUnitSet().NumPlayers() && myiRunning >= 0)
						{	myiRunningPlayer = mypoGame->BattleUnitSet().Player(myiRunning).MemberNum();
						}
				 		Draw();
						mypoScreen->Update();
		}
		for(int i = 0; i < mypoGame->BattleUnitSet().NumEnemies(); i++)
		{
			oDelayer.Reset();
  			mypoGame->BattleUnitSet().Enemy(i).Run(*mypoScreen);
  			UpdateQueue();
			Draw();
			mypoScreen->Update();
			if(!mypoGame->BattleUnitSet().Enemy(i).Dead())
			{	oDelayer.Delay(ENEMY_DELAY);
			}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_Battle::UpdateQueue()
{	//Vars
		LL_EventQueue::LL_Event oEvent;
		int iSeg, iOff, iLayer;

	//While events exist pop one out and process it
		while(mypoGame->EventQueue().NumEvents() > 0)
		{	//Grab the next event to process
	  			oEvent = mypoGame->EventQueue().GetEvent();

			//Decide on what to do based on this type of event (Yay for ugly switch statement!)
				switch(oEvent.myiType)
				{	//- [Talk] -
	    				case LL_EventQueue::EVENT_TALK:
						{	//Get the unit to talk to
								iSeg = mypoGame->UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = mypoGame->UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);

							//Now talk blaa
	      						mypoGame->UnitSet().Unit(iSeg, iOff).Talk();
						}break;
					//- [Look] -
						case LL_EventQueue::EVENT_LOOK:
						{	//If this is off the map do nada
								if(	oEvent.myiParam1 < 0 || oEvent.myiParam1 >= LL_UnitMap::MAP_WIDTH ||
									oEvent.myiParam2 < 0 || oEvent.myiParam2 >= LL_UnitMap::MAP_HEIGHT)
								{}

      						//Get the unit to talk to
								iSeg = mypoGame->UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = mypoGame->UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);

							//If there's a unit there look at the unit
								if(iSeg != LL_UnitMap::SEG_NULL)
								{	mypoGame->UnitSet().Unit(iSeg, iOff).Look();
								}
							//Otherwise look at the purdy terrain
								else
								{	mypoPaint->TalkConsole() << mypoGame->TerrainMap().GetTerrain(
        								oEvent.myiParam1,oEvent.myiParam2).Info() << "\n";
								}
						}break;
					//- [Push] -
	    				case LL_EventQueue::EVENT_PUSH:
						{	//Get the unit to talk to
								iSeg = mypoGame->UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = mypoGame->UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);
							//Now push
	      						mypoGame->UnitSet().Unit(iSeg, iOff).Push();
						}break;
					//- [Search] -z
	    				case LL_EventQueue::EVENT_SEARCH:
						{	//Get the unit to talk to
								iSeg = mypoGame->UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = mypoGame->UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);

							//Now talk blaa
	      						mypoGame->UnitSet().Unit(iSeg, iOff).Search();
						}break;
					//- [Attack] -
						case LL_EventQueue::EVENT_ATTACK:
						{	//Ataaaaaaaaack!
								PlayerAttack(oEvent.myiCallingOff, oEvent.myiParam1, oEvent.myiParam2,
											 oEvent.myiParam3);
								EnemyAttack(oEvent.myiCallingOff, oEvent.myiParam1, oEvent.myiParam2,
											oEvent.myiParam3);
       						//Graphic
       							DrawHit(oEvent.myiParam1, oEvent.myiParam2);
						}break;
					//- [Get] -
						case LL_EventQueue::EVENT_GET:
						{	//Get the item to get
								iSeg = mypoGame->UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = mypoGame->UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);
								iLayer = mypoGame->UnitMap().TopLayerOn(oEvent.myiParam1, oEvent.myiParam2);
							//If we have armor get it
								if(iSeg == LL_UnitMap::SEG_ARMORS)
								{	//Get this item
										mypoGame->Player().Inventory().GiveArmor(
          									mypoGame->UnitSet().ArmorType(iOff), 1);
									//Remove it
										mypoGame->UnitMap().RemoveUnitOn(
          									oEvent.myiParam1, oEvent.myiParam2, iLayer);
								}
							//If we have a weapon get it
								else if(iSeg == LL_UnitMap::SEG_WEAPONS)
								{	//Get this item
										mypoGame->Player().Inventory().GiveWeapon(
											mypoGame->UnitSet().WeaponType(iOff), 1);
									//Remove it
										mypoGame->UnitMap().RemoveUnitOn(
          									oEvent.myiParam1, oEvent.myiParam2, iLayer);
								}
							//If we have a scripted item get it
								else if(iSeg == LL_UnitMap::SEG_SCRIPTED_ITEMS)
								{	//Get this item
										mypoGame->Player().Inventory().GiveScriptedItem(
											mypoGame->UnitSet().ScriptedItemType(iOff), 1);
									//Remove it if you're supposed to
										if(mypoGame->UnitSet().Chest(iOff).Disappears())
										{	mypoGame->UnitMap().RemoveUnitOn(
          										oEvent.myiParam1, oEvent.myiParam2, iLayer);
										}
								}
    						//If we have a chest get down!
								else if(iSeg == LL_UnitMap::SEG_CHESTS)
								{	//Get this item
										mypoGame->UnitSet().Chest(iOff).AddToInventory
          								(	&mypoGame->Player().Inventory(),
                  							&mypoGame->ItemSet(),
                  							&mypoPaint->TalkConsole()
                   						);
									//Remove items
										mypoGame->UnitSet().Chest(iOff).ClearItems();
									//Remove it
										mypoGame->UnitMap().RemoveUnitOn(
          									oEvent.myiParam1, oEvent.myiParam2, iLayer);
								}
						}break;
					//- [Use] -
						case LL_EventQueue::EVENT_USE:
						{	mypoZStats->UseItem(mypoGame);
						}break;
					//- [ZStats] -
						case LL_EventQueue::EVENT_ZSTATS:
						{	mypoZStats->Display(mypoGame);
						}break;
					//- [Escape] -
						case LL_EventQueue::EVENT_ESCAPE:
						{	//Remove all player's mapped to this party member
								for(int i = 0; i < mypoGame->BattleUnitSet().NumPlayers(); i++)
								{	if(	mypoGame->BattleUnitSet().Player(i).MemberNum() ==
        								oEvent.myiParam1)
									{	mypoGame->BattleUnitSet().Player(i).SetEscaped(true);
										*mypiExitDir = mypoGame->BattleUnitSet().Player(i).LastDirection();
										mypoGame->BattleUnitMap().SetUnitOn
          								(	mypoGame->BattleUnitSet().Player(i).X(),
                  							mypoGame->BattleUnitSet().Player(i).Y(),
                         					mypoGame->BattleUnitSet().Player(i).Layer(),
                              				LL_UnitMap::SEG_NULL, LL_UnitMap::OFF_NULL
                  						);
                  						mypoGame->BattleUnitSet().Player(i).SetX(0xFF);
										mypoGame->BattleUnitSet().Player(i).SetY(0xFF);
									}
								}
						}break;
					//- [Quick Escape] -
    					case LL_EventQueue::EVENT_QUICK_ESCAPE:
						{	//If all enemies are dead remove all player's, we're done!
	      						if(!mypoGame->BattleUnitSet().AnyEnemies())
								{	for(int i = 0; i < mypoGame->BattleUnitSet().NumPlayers(); i++)
									{	mypoGame->BattleUnitSet().Player(i).SetEscaped(true);
										mypoGame->BattleUnitMap().SetUnitOn
          								(	mypoGame->BattleUnitSet().Player(i).X(),
                  							mypoGame->BattleUnitSet().Player(i).Y(),
                         					mypoGame->BattleUnitSet().Player(i).Layer(),
                              				LL_UnitMap::SEG_NULL, LL_UnitMap::OFF_NULL
                  						);
                  						mypoGame->BattleUnitSet().Player(i).SetX(0xFF);
										mypoGame->BattleUnitSet().Player(i).SetY(0xFF);
										
										Draw();
	        							mypoScreen->Update();
	        							myoTimer.Reset();
	        							myoTimer.Delay(EXIT_DELAY);
									}
								}
     						//Else call the user a loser
     							else
     							{	mypoPaint->TalkConsole() << "Battle is not finished!\n";
     								mypoPaint->Draw();
     								mypoScreen->Update();
     							}
						}break;
					//- [Escape Monster] -
						case LL_EventQueue::EVENT_ESCAPE_MONSTER:
						{	mypoGame->BattleUnitMap().SetUnitOn
          					(	mypoGame->BattleUnitSet().Enemy(oEvent.myiParam1).X(),
								mypoGame->BattleUnitSet().Enemy(oEvent.myiParam1).Y(),
								mypoGame->BattleUnitSet().Enemy(oEvent.myiParam1).Layer(),
                              	LL_UnitMap::SEG_NULL,
								LL_UnitMap::OFF_NULL
                  			);
                  			mypoGame->BattleUnitSet().Enemy(oEvent.myiParam1).SetX(0xFF);
							mypoGame->BattleUnitSet().Enemy(oEvent.myiParam1).SetY(0xFF);
							mypoGame->BattleUnitSet().Enemy(oEvent.myiParam1).SetDead(true);
						}break;
  					//- [Select (Lock) Player] -
  						case LL_EventQueue::EVENT_SELECT_PLAYER:
  						{
  						}break;
  					//- [Plot Monster Chest] -
  						case LL_EventQueue::EVENT_PLOT_MONSTER_CHEST:
  						{	mypoGame->UnitSet().AddChest(oEvent.myiParam2, oEvent.myiParam3, 3);
	  						int iUnit = mypoGame->UnitSet().NumChests() - 1;
	  						mypoGame->UnitSet().Chest(iUnit) = mypoGame->MonsterSet().Monster(
         						oEvent.myiParam1).DeathChest();
							mypoGame->UnitMap().SetUnitOn(	oEvent.myiParam2, oEvent.myiParam3, 3,
															LL_UnitMap::SEG_CHESTS, iUnit);
  						}break;
  					//- [Plot Monster Guts] - (ecch...)
  						case LL_EventQueue::EVENT_PLOT_MONSTER_GUTS:
  						{	mypoGame->UnitSet().AddGuts
        					(	oEvent.myiParam2,
             					oEvent.myiParam3,
                  				3,
                  				myoDeadImage,
                  				&mypoGame->Player().Inventory(),
                  				&mypoPaint->TalkConsole()
    						);
	  						int iUnit = mypoGame->UnitSet().NumGuts() - 1;
	  						mypoGame->UnitSet().Guts(iUnit).SetChanceOfFood
         						(mypoGame->MonsterSet().Monster(oEvent.myiParam1).ChanceOfFood());
	  						mypoGame->UnitSet().Guts(iUnit).SetMaxFood
         						(mypoGame->MonsterSet().Monster(oEvent.myiParam1).MaxFood());
							mypoGame->UnitMap().SetUnitOn(	oEvent.myiParam2, oEvent.myiParam3, 3,
															LL_UnitMap::SEG_GUTS, iUnit);
  						}break;
					//- [Gosub Global] -
						case LL_EventQueue::EVENT_GOSUB_GLOBAL:
						{	//Gosub on
	      						mypoGame->LOOP().GosubInstance(
             						LL_Game__GLOBAL_IDENTIFIER, oEvent.mysParam1);
						}break;
				}
		}
	//Update global script
		mypoGame->GlobalScript().Run();
}
//P--------------------------------------------------------------------------------------------- [Setup] -P
void LRUN_Battle::PlaceParty()
			{	//Vars
		int iPlayerToPlace = 0;
		int iNumPlayers = mypoGame->Player().PartyMembers().Length();
		LL_PartyMember* poPartyMember;
	//Delete all old data
		mypoGame->BattleUnitSet().ClearPlayers();
	//Loop through all player start point place a player there
		for(int iY = myiMapEdgeY; iY < myiMapEdgeY + PLAYFIELD_TILEHEIGHT; iY++)
		{	for(int iX = myiMapEdgeX; iX < myiMapEdgeX + PLAYFIELD_TILEWIDTH; iX++)
			{	//If a player warp in point exists here and there's players to spare plot a player
					if(mypoGame->BattleMap().FriendOn(iX, iY) && iPlayerToPlace < iNumPlayers)
					{	//Only create this player if he's alive! Alive! Whahahahahaha!
							poPartyMember = &mypoGame->Player().PartyMembers()[iPlayerToPlace];
							if(poPartyMember->HP() > 0)
							{	mypoGame->BattleUnitSet().AddPlayer
       							(	&mypoGame->TerrainMap(),
               						&mypoGame->BattleUnitMap(),
  									&mypoGame->Clock(),
            						&mypoGame->EventQueue(),
                  									&mypoGame->ItemSet(),
            						mypoGame->GraphicsDir(),
            						&myoDeadImage,
                  					iPlayerToPlace,
                  					poPartyMember,
									mypoInput,
									&mypoPaint->TalkConsole(),
									mypoScreen,
									myiMapEdgeX,
									myiMapEdgeY,
         							iX,
                					iY,
                     				3	//!!!
                         		);
							}
						iPlayerToPlace++;
					}
			}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_Battle::PlaceEnemies()
{	//Vars
		double dRandX, dRandY;
		int iEnemyToPlace = 0;
		int iLoops = 0;
	//Delete all old data
		mypoGame->BattleUnitSet().ClearEnemies();
	//Determine how many monsters to place
		myiNumMonsters = mypoGame->MonsterSet().Monster(myiMonster).NumMonstersToPlace();
	//Loop through all player start point place a player there
		while(iEnemyToPlace < myiNumMonsters && iLoops < 5000)
		{	dRandX = ((double)rand() / (double)(RAND_MAX+1));
			dRandY = ((double)rand() / (double)(RAND_MAX+1));
			int iX = dRandX * PLAYFIELD_TILEWIDTH;
			int iY = dRandY * PLAYFIELD_TILEHEIGHT;
			
			//If an enemy warp in point exists here and there's space available plot
					if(mypoGame->BattleMap().FoeOn(iX + myiMapEdgeX, iY + myiMapEdgeY) &&
     				   iEnemyToPlace < myiNumMonsters &&
     				   !mypoGame->BattleUnitMap().IsUnitOn(iX, iY, 3))
					{	//Determine which enemy to place
							int iMonsterToPlace =
       							mypoGame->MonsterSet().Monster(myiMonster).PickMonster(myiMonster);
      					//Make the enemy
							mypoGame->BattleUnitSet().AddEnemy
      						(	&mypoGame->TerrainMap(),
               					&mypoGame->BattleUnitMap(),
  								&mypoGame->Clock(),
            					&mypoGame->EventQueue(),
                  				&mypoGame->ItemSet(),
                       			"error2.png",	//!!!
            					mypoGame->GraphicsDir(),
            					&myoDeadImage,
								&mypoPaint->TalkConsole(),
								mypoScreen,
								iMonsterToPlace,
								myiMapEdgeX,
								myiMapEdgeY,
         						iX + myiMapEdgeX,
                				iY + myiMapEdgeY,
                     			3	//!!!
                        	);
						iEnemyToPlace++;
					}
   			//Increase loop counter
   				iLoops++;
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_Battle::PlayerAttack(int iPlayer, int iX, int iY, int iAmount)
{	//Vars
		int iFound = mypoGame->BattleUnitMap().PlayerOn(iX, iY);
	//If a player lies on this square
		if(iFound != LL_BattleUnitMap::NONE)
		{	//Damage this player
			    mypoGame->BattleUnitSet().Player(iFound).Damage(iAmount);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_Battle::EnemyAttack(int iPlayer, int iX, int iY, int iAmount)
{	//Vars
		int iFound = mypoGame->BattleUnitMap().EnemyOn(iX, iY);
	//If a player lies on this square
		if(iFound != LL_BattleUnitMap::NONE)
		{	//Damage this enemy
			    mypoGame->BattleUnitSet().Enemy(iFound).Damage(iAmount);
		}
}
//P------------------------------------------------------------------------------------------ [Graphics] -P
void LRUN_Battle::Draw()
{	//Set the viewports
		mypoGame->TerrainMap().SetViewX(myiViewX);
		mypoGame->TerrainMap().SetViewY(myiViewY);
	//Clear
		mypoScreen->DrawFillRectangle(0, 0, 639, 479, COLOR_BLACK, 255);
	//If we need to update animations do so
		if(myoTimer.Ellapsed() > ANIMATION_DELAY)
		{  	mypoGame->BattleUnitSet().ResetAnimations();
			myoTimer.Reset();
		}
	//Draw the map and units
		mypoGame->TerrainMap().Draw(*mypoScreen, lLight);
		mypoPaint->DrawUnitMap(&lLight);
	//And the player info
		mypoPaint->DrawPlayerInfo(-1, myiRunningPlayer);
	//Clock
		mypoGame->Clock().Draw();
		mypoPaint->Draw();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_Battle::DrawHit(int iX, int iY)
{	//Vars
		ASFC_Timer oDelayer;
		int iMapOffsetX, iMapOffsetY;
	//Const
		const static int DELAY = 300;

	//Figure out how much we're off
		iMapOffsetX = myiMapEdgeX * TILE_WIDTH;
		iMapOffsetY = myiMapEdgeY * TILE_HEIGHT;		
	//Blit and delay
		Draw();
		myoHitImage.BlitTo(	*mypoScreen, iX * TILE_WIDTH + PLAYFIELD_X - iMapOffsetX,
							iY * TILE_HEIGHT + PLAYFIELD_Y - iMapOffsetY);
		mypoScreen->Update();
		oDelayer.Reset();
		oDelayer.Delay(DELAY);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_Battle::PerformEffect(LL_BORDER_EFFECT iEffect)
{	//Save pictures of the map
		ASFC_Surface oSurf1(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
		oSurf1.Blit(*mypoScreen, 0, 0);
		Draw();
		ASFC_Surface oSurf2(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
		oSurf2.Blit(*mypoScreen, 0, 0);

	//Decide what to do based on which effect
		switch(iEffect)
		{	case BORDER_EFFECT_NONE:
			{
			}break;
			
			case BORDER_EFFECT_FADE:
			{	mypoEffects->FadeOutAndIn(oSurf1, oSurf2, *mypoScreen);
			}break;
			
			case BORDER_EFFECT_DISSOLVE:
			{	mypoEffects->Dissolve(oSurf1, oSurf2, *mypoScreen);
			}break;
			
			case BORDER_EFFECT_TRIAMBULATE:
			{	mypoEffects->Triambulate(oSurf1, oSurf2, *mypoScreen);
			}break;
			
			case BORDER_EFFECT_CHECKERBOARD:
			{	mypoEffects->CheckerBoard(oSurf1, oSurf2, *mypoScreen);
			}break;

			case BORDER_EFFECT_BLEND:
			{	mypoEffects->Blend(oSurf1, oSurf2, *mypoScreen, 15, 15);
			}break;

			case BORDER_EFFECT_SPLIT_VERTICLE:
			{	mypoEffects->SplitVert(oSurf1, oSurf2, *mypoScreen, 5, 4);
			}break;

			case BORDER_EFFECT_SPLIT_HORIZONTAL:
			{	mypoEffects->SplitHoriz(oSurf1, oSurf2, *mypoScreen, 5, 4);
			}break;
			
			default: break;
		};
}
