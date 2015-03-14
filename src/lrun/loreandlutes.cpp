/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			loreandlutes.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "loreandlutes.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LRUN_LoreAndLutes
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LRUN_LoreAndLutes::LRUN_LoreAndLutes(ASFC_Screen* poScreen)
{	//Set up the game object
		myoGame.SetScreen(poScreen);
	//Set up the menu
		myoMenu.Load(LRUN_LoreAndLutes_MENU_FILE);
		myoMenu.Init(*poScreen, myoEffects);
	//Setup the lighting matrix
		lLight.Resize(100, 100);
		lFreeLight.Resize(100, 100);
		for(int iY = 0; iY < 100; iY++)
			for(int iX = 0; iX < 100; iX++)
				lFreeLight[iX][iY] = true;
	//Set the screen
		SetScreen(poScreen);
	//Setup the shader
		myoShader.LoadShades(LRUN_LoreAndLutes_SHADES_FILE);
		myoShader.SetClock(&myoGame.Clock());
	//Setup the ZStater
		myoZStats.SetScreen(poScreen);
		myoZStats.SetPainter(&myoPaint);
	//Setup the readyer
		myoReady.SetScreen(poScreen);
		myoReady.SetPainter(&myoPaint);
	//Setup the user interface
		myoPaint.SetScreen(mypoScreen);
		myoPaint.Load(LRUN_LoreAndLutes_GUI_PREFERENCE_FILE);
		myoPaint.SetGame(&myoGame);
	//Setup the Lore LOOP Library (and the linker)
		myoLOOPLib.SetGame(&myoGame);
		myoLOOPLib.SetScreen(poScreen);
		myoLOOPLib.SetPainter(&myoPaint);
		myoLOOPLib.SetZStats(&myoZStats);
		myoLOOPLib.Link(&myoGame.LOOP());
	//Display the hard coded greeting message
		myoPaint.TalkConsole().CurrentFont(2);
		myoPaint.TalkConsole() << "- - - - - - - - - - -\n";
		myoPaint.TalkConsole().CurrentFont(0);
		myoPaint.TalkConsole() << "      Welcome to     \n";
		myoPaint.TalkConsole() << " ~ [Lore And Lutes] ~\n";
		myoPaint.TalkConsole() << "    By: Andy Stone   \n";
		myoPaint.TalkConsole().CurrentFont(2);
		myoPaint.TalkConsole() << "- - - - - - - - - - -\n";
	//Setup the player
		myoGame.Player().SetConsole(&myoPaint.TalkConsole());
		myoGame.Player().SetScreen(poScreen);
	//Reset timers
		myoAnimationTime.Reset();
	//Randomize
		time_t oSeconds;
		oSeconds = time(NULL);
		srand(oSeconds);
}
//-------------------------------------------------------------------------------------- [Game Handeling] -
//MEMVAR_GETREF(Game, LL_Game, myoGame);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetScreen, Screen, ASFCSurface*, mypoScreen);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LRUN_LoreAndLutes::LoadGame(string sFile, string sSaveGame)
{	//Vars
		string sLine2, sLine3;
	
	//Yes we have lighting
		myfViewAll = false;
	//Clear the screen
	//	mypoScreen->DrawFillRectangle(0, 0, 639, 479, COLOR_BLACK, 0xFF);
	//Display the loading message
		sLine2 = "Game: " + sFile;
		sLine3 = "Save: " + sSaveGame;
		myoPaint.DisplayMessage("Loading game...", sLine2, sLine3, 1);
	//Yes we're recording
		myoGame.SetRecorderOn(true);
	//Let the player have input
		myoGame.Player().SetInput(&myoInput);
	//Tell the game object to load a game!
		myoGame.Load(sFile, mypoScreen, &myoPaint.FontPalette());
	//Set up the ee engine
		myoGame.SetInBattleMode(true);
		myoGame.LoadMap(-1);
		myoGame.LoadClasses("", mypoScreen);
		myoBattle.Setup(&myoGame, &myoLOOPLibLinker, &myoLOOPLib, &myoPaint, mypoScreen, &myoEffects,
  						&myoInput, &myoZStats);
		myoGame.SetInBattleMode(false);
	//Load saved game
		if(sSaveGame != "")
			myoGame.RestoreGame(sSaveGame);
		else
		{	//Load the first map
				myoGame.LoadMap(myoGame.StartMap());
				myoGame.LoadClasses("", mypoScreen);
			//Create a party of one
				myoGame.Player().PartyMembers().Resize(myoGame.Player().PartyMembers().Length() + 1);
				myoGame.PlayerSet().Player(
    				myoGame.InitialPlayer()).MakePartyMember(myoGame.GraphicsDir(),
		     		&myoGame.Player().PartyMembers()[myoGame.Player().PartyMembers().Length() - 1]);
		  	 	myoGame.Player().PartyMembers()
     				[myoGame.Player().PartyMembers().Length() - 1].SetItemSet(&myoGame.ItemSet());
		}
	//Reposition the player
		myoGame.Player().Place(myoGame.Player().X(), myoGame.Player().Y());
	//Init for the newly loaded map
		InitForNewMap();
	//Fade in the border
		PerformEffect(BORDER_EFFECT_FADE);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LRUN_LoreAndLutes::RunGame()
{	//Vars
		ASFC_Timer oTime;
		oTime.Reset();
		LL_Player::LL_UPDATE iUpdate;
		int iPlayerX, iPlayerY;
		bool fDoneWithPlayer = false;
		LRUN_Menu::LRUN_MENU_CHOICE iChoice;
	//Call labels
		myoGame.UnitSet().CallLabels(myoGame.Player().X(), myoGame.Player().Y());
	//Run other units
		if(myiOnlyExecuteUnit.Length() > 0)
			myoGame.UnitSet().SetOnlyRunUnit(myiOnlyExecuteUnit.ReadLast());
		else
			myoGame.UnitSet().SetOnlyRunUnit(-1);
		myoGame.UnitSet().Run();
	//Process any events
		ProcessEvents();
	//Loop while there's a locked state
		while(myiOnlyExecuteUnit.Length() > 0)
		{	//Run other units
				myoGame.UnitSet().SetOnlyRunUnit(myiOnlyExecuteUnit.ReadLast());
				myoGame.UnitSet().Run();
			//Delete the last unit of the execution stack
	  			myiOnlyExecuteUnit.Delete(myiOnlyExecuteUnit.Length() - 1);
			//Process any events
				ProcessEvents();
		}
	//Check to see if the player is alive
		if(!PlayerAlive())
		{	//We're done with the player for now
				fDoneWithPlayer = true;
			//Give the player 10 health
				myoGame.Player().PartyMembers()[0].SetHP(10);
				myoGame.Player().PartyMembers()[0].SetState(LL_PartyMember::STATE_GOOD);
			//Add an event to the queue to switch now
				myoGame.EventQueue().Clear();
				myoGame.EventQueue().GoMap(myoGame.DeathMap(), BORDER_EFFECT_DISSOLVE, -1, -1);
			//Process any events
				ProcessEvents();
		}
	//While we're not done with the player run him
		while(!fDoneWithPlayer && myiOnlyExecuteUnit.Length() == 0)
		{	//Run the player
				myoGame.Player().Run();
			//Decide what to do based on the player update value
				iUpdate = myoGame.Player().UpdateValue();
				switch(iUpdate)
				{	//- [Quit] -
		  			case LL_Player::UPDATE_QUIT:
						//Display the menu
							iChoice = myoMenu.Choose();
						//Wait for the key to be released
							myoInput.Update();
							while(myoInput.KeyDown(SDLK_ESCAPE))
								myoInput.Update();
						//If the choice was tt we're done
							if(iChoice == LRUN_Menu::CHOICES_EXIT)
							{	//We're done, fa-neesh!
									myfReturnToStarter = false;
									fDoneWithPlayer = true;
				  					return(false);
							}
						//If it's new game
							else if(iChoice == LRUN_Menu::CHOICES_NEW)
							{	if(myoPaint.PromptYN("Starting a new game will exit the current one.",
													 "Are you sure (Y/N)", "", 1))
						 		{	LoadGame(Game().GlobalInfofile(), "");
								}
							}
						//If it's switch worlds
							else if(iChoice == LRUN_Menu::CHOICES_SWITCH)
							{		myfReturnToStarter = true;
									fDoneWithPlayer = true;
				  					return(false);
							}
						//If it's save\load save\load
							else if(iChoice == LRUN_Menu::CHOICES_SAVE)
							{	Game().DataRecorder().RecordInformation(Game().CurrentMap());
								Game().SaveGame(Game().GameFile() + ".save");
							}
						//If it's save\load save\load
							else if(iChoice == LRUN_Menu::CHOICES_LOAD)
							{	LoadGame("./games/" + Game().GameFile() + "/" + Game().GameFile() + ".game", Game().GameFile() + ".save");
							}
						//If it's help
							else if(iChoice == LRUN_Menu::CHOICES_HELP)
							{	myoPaint.Draw();
								mypoHelp->RunnerHelp();
							}
					break;
					
					case LL_Player::UPDATE_GO_DONE:
						//We're done
							fDoneWithPlayer = true;
					break;
					
					default: break;
				}
			//Repaint
				if(myoAnimationTime.Ellapsed(ANIMATION_DELAY) && !fDoneWithPlayer)
				{	
					Draw();
					mypoScreen->Update();
					myoAnimationTime.Reset();
				}
		}
	//Process any events
		ProcessEvents();
	//Handle Spawners
		myoGame.UnitSet().HandleSpawners(myoGame.GraphicsDir());
	//Repaint (if we're not locked)
		myoAnimationTime.Delay(GAME_DELAY);
		Draw();
		mypoScreen->Update();
		myoAnimationTime.Reset();
	//Return true (for keep on truckin')
		return(true);
}
//P----------------------------------------------------------------------------------- [Game Handeling] -P
void LRUN_LoreAndLutes::InitForNewMap()
{	//Link the lib to the scripted units
		myoLOOPLibLinker.Link(&myoGame, &myoLOOPLib);
	//If this is the first time the map has loaded call init
		//if(myoGame.TerrainMap().FirstLoad())	!!!!!!!!
		//{
			myoGame.UnitSet().CallInitLabels();
			ProcessEvents();
			myoGame.TerrainMap().SetFirstLoad(false);
		//}
	//All units are allowed to run
		myiOnlyExecuteUnit.Resize(0);
	//Clear the event queue
		myoGame.EventQueue().Clear();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_LoreAndLutes::Draw()
{	//Clear
		mypoScreen->DrawFillRectangle(0, 0, 639, 479, COLOR_BLACK, 255);
	//Reset animations
  		myoGame.UnitSet().ResetAnimations();

	if(!myfViewAll)
	{	bool fTorch = false;
 		if(myoGame.Player().TorchTurns() > 0)
 			fTorch = true;
 		myoShader.GrabLight(myoGame.TerrainMap().ViewX(), myoGame.TerrainMap().ViewY(),
					myoGame.Player().X(), myoGame.Player().Y(), myoGame.TerrainMap(), lLight,
     				fTorch);
		myoGame.TerrainMap().Draw(*mypoScreen, lLight);
		myoPaint.DrawUnitMap(&lLight);
	}
	else
	{	
		myoGame.TerrainMap().Draw(*mypoScreen, lFreeLight);
		myoPaint.DrawUnitMap(&lFreeLight);
	}
	//Clock
		myoGame.Clock().Draw();	
		myoPaint.StatsConsole().Clear();
		myoPaint.StatsConsole() << myoGame.Clock().Hour() << ":" << myoGame.Clock().Minute() << "\n";
		myoPaint.StatsConsole() << "X: " << myoGame.Player().X() << "\n";
		myoPaint.StatsConsole() << "Y: " << myoGame.Player().Y() << "\n";
	myoPaint.Draw();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LRUN_LoreAndLutes::PlayerAlive()
{	//Loop through all members if any are alive then yes the player is alive
		for(int i = 0; i < myoGame.Player().PartyMembers().Length(); i++)
		{	if(myoGame.Player().PartyMembers()[i].HP() > 0)
				return true;
		}
	//If execution gets here sorry man, you're dead
		return false;
}
//------------------------------------------------------------------------------------------- [EventProc] -
void LRUN_LoreAndLutes::ProcessEvents()
{	//Vars
		LL_EventQueue::LL_Event oEvent;
		int iSeg, iOff, iLayer;
		int iMoveTo;
	//While events exist pop one out and process it
		while(Game().EventQueue().NumEvents() > 0)
		{	//Grab the next event to process
	  			oEvent = Game().EventQueue().GetEvent();
			//Decide on what to do based on this type of event (Yay for ugly switch statement!)
				switch(oEvent.myiType)
				{	//- [Talk] -
	    				case LL_EventQueue::EVENT_TALK:
						{	//Get the unit to talk to
								iSeg = Game().UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = Game().UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);
							
							//Now talk blaa
	      						Game().UnitSet().Unit(iSeg, iOff).Talk();
						}break;
					//- [Look] -
						case LL_EventQueue::EVENT_LOOK:
						{	//If this is off the map do nada
								if(	oEvent.myiParam1 < 0 || oEvent.myiParam1 >= LL_UnitMap::MAP_WIDTH ||
									oEvent.myiParam2 < 0 || oEvent.myiParam2 >= LL_UnitMap::MAP_HEIGHT)
								{}
								
      						//Get the unit to talk to
								iSeg = Game().UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = Game().UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);
								
							//If there's a unit there look at the unit
								if(iSeg != LL_UnitMap::SEG_NULL)
								{	Game().UnitSet().Unit(iSeg, iOff).Look();
								}
							//Otherwise look at the purdy terrain
								else
								{	myoPaint.TalkConsole() << Game().TerrainMap().GetTerrain(
        								oEvent.myiParam1,oEvent.myiParam2).Info() << "\n";
								}
						}break;
					//- [Push] -
	    				case LL_EventQueue::EVENT_PUSH:
						{	//Get the unit to talk to
								iSeg = Game().UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = Game().UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);
						
							//Now push
	      						Game().UnitSet().Unit(iSeg, iOff).Push();
						}break;	
					//- [Search] -
	    				case LL_EventQueue::EVENT_SEARCH:
						{	//Search the unit to talk to
								iSeg = Game().UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = Game().UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);
								iLayer = Game().UnitMap().TopLayerOn(oEvent.myiParam1, oEvent.myiParam2);
				
								//If we have armor search it
									if(iSeg == LL_UnitMap::SEG_ARMORS)
									{	//Search this item
											
									}
 								//If we have a weapon search it
									else if(iSeg == LL_UnitMap::SEG_WEAPONS)
									{	//Search this item
											
									}
								//If we have a scripted item search it
									else if(iSeg == LL_UnitMap::SEG_SCRIPTED_ITEMS)
									{	//Search this item
											
									}
								//If we have a chest search down!
									else if(iSeg == LL_UnitMap::SEG_CHESTS)
									{	//Search this item
											Game().UnitSet().Chest(iOff).Search
          									(	&Game().ItemSet(),
                  								&myoPaint.TalkConsole()
                   							);
									}
									
								//Else try the hard way
									else
									{	Game().UnitSet().Unit(iSeg, iOff).Search();
									}
							}break;
					//- [Attack] -					
						case LL_EventQueue::EVENT_ATTACK:
						{	//Ataaaaaaaaack!!!
								bool fEnemyDead;
								int iMonster;
								if(oEvent.myiParam1 >= 0)
									iMonster = myoGame.UnitSet().MonsterOn(oEvent.myiParam1, oEvent.myiParam2);
								else
									iMonster = oEvent.myiParam3;
								if(iMonster >= 0)
								{	if(oEvent.myiParam4 < 0)
									{	//If we have a map between the player's vehicle and the monster's chooose that map
    	      								int iKeyBetweenVehicles = myoGame.MobilityTerrainMap().KeyBetweenVehicles
        	  								(	myoGame.Player().Vehicle().Code(),
          										myoGame.UnitSet().Monster
                	   							( iMonster
		    									).Vehicle().Code()
          									);
          									if(iKeyBetweenVehicles >= 0)
											{	fEnemyDead =
													myoBattle.Attack
            										(	oEvent.myiParam3,
            											myoGame.MobilityTerrainMap().VehicleBattleKey(iKeyBetweenVehicles).iBattleMap,
            											oEvent.myiCallingSeg,
                      									oEvent.myiCallingOff,
	                      								&iMoveTo
													);
											}
      									//Else judge my terrain
      										else
											{	fEnemyDead =
													myoBattle.Attack(oEvent.myiParam3,
													myoGame.TerrainSet().Terrain(myoGame.TerrainMap().Get(
													Game().Player().X(), Game().Player().Y())).BattleMap(),
          											oEvent.myiCallingSeg, oEvent.myiCallingOff,
                      								&iMoveTo);
	          								}
    		  							}
      								else
      								{
             							fEnemyDead =
											myoBattle.Attack(oEvent.myiParam3, oEvent.myiParam4,
	          								oEvent.myiCallingSeg,oEvent.myiCallingOff,
                      						&iMoveTo);
	      							}
									//Always remove the enemy
									//If the enemy is dead remove him
									//	if(fEnemyDead && oEvent.myiParam1 >= 0)
									//	{
									//Remove the enemy if it exists
										iMonster = myoGame.UnitSet().MonsterOn(oEvent.myiParam1, oEvent.myiParam2);
										if(iMonster >= 0)
										{	int iLayer = myoGame.UnitSet().Monster(iMonster).Layer();
          									myoGame.UnitSet().RemoveUnit(LL_UnitSet::SEG_MONSTERS, iMonster);
											myoGame.UnitMap().RemoveUnitOn
           									(	oEvent.myiParam1, oEvent.myiParam2,
           										iLayer
											);
										}
									//If there was an exit direction move there
	      								if(iMoveTo >= 0)
    	  									myoGame.Player().Move((ASFC_DIRECTION)iMoveTo);
									//Perform an effect
										PerformEffect(BORDER_EFFECT_FADE);
	    							//Wait for all keys to be cleared
	    								myoInput.Update();
	    								while(myoInput.GetKey() != -1)
	    								myoInput.Update();
	    							//Clear any existing events
	    								Game().EventQueue().Clear();
								}
						}break;
					//- [Get] -					
						case LL_EventQueue::EVENT_GET:
						{	//Get the item to get
								iSeg = Game().UnitMap().TopSegOn(oEvent.myiParam1, oEvent.myiParam2);
								iOff = Game().UnitMap().TopOffOn(oEvent.myiParam1, oEvent.myiParam2);
								iLayer = Game().UnitMap().TopLayerOn(oEvent.myiParam1, oEvent.myiParam2);
				
							//If we have armor get it
								if(iSeg == LL_UnitMap::SEG_ARMORS)
								{	//Get this item
										Game().Player().Inventory().GiveArmor(
          									Game().UnitSet().ArmorType(iOff), 1);
									//Remove it
										Game().UnitSet().RemoveUnit(iSeg, iOff);
										Game().UnitMap().RemoveUnitOn(
          									oEvent.myiParam1, oEvent.myiParam2, iLayer);
								}
 							//If we have a weapon get it
								else if(iSeg == LL_UnitMap::SEG_WEAPONS)
								{	//Get this item
										Game().Player().Inventory().GiveWeapon(
											Game().UnitSet().WeaponType(iOff), 1);
									//Remove it
										Game().UnitSet().RemoveUnit(iSeg, iOff);
										Game().UnitMap().RemoveUnitOn(
          									oEvent.myiParam1, oEvent.myiParam2, iLayer);
								}
							//If we have a scripted item get it
								else if(iSeg == LL_UnitMap::SEG_SCRIPTED_ITEMS)
								{	//Get this item
										Game().Player().Inventory().GiveScriptedItem(
											Game().UnitSet().ScriptedItemType(iOff), 1);
									//Remove it
										Game().UnitSet().RemoveUnit(iSeg, iOff);
										Game().UnitMap().RemoveUnitOn(
          									oEvent.myiParam1, oEvent.myiParam2, iLayer);
								}
							//If we have a chest get down!
								else if(iSeg == LL_UnitMap::SEG_CHESTS)
								{	//Get this item
										Game().UnitSet().Chest(iOff).AddToInventory
          								(	&Game().Player().Inventory(),
                  							&Game().ItemSet(),
                  							&myoPaint.TalkConsole()
                   						);
									//Remove items
										Game().UnitSet().Chest(iOff).ClearItems();
									//Remove it if you're supposed to
										if(Game().UnitSet().Chest(iOff).Disappears())
										{	Game().UnitSet().RemoveUnit(iSeg, iOff);
											Game().UnitMap().RemoveUnitOn(
    	      									oEvent.myiParam1, oEvent.myiParam2, iLayer);
										}
								}
						}break;
					//- [Use] -
						case LL_EventQueue::EVENT_USE:
						{	myoZStats.UseItem(&Game());
						}break;
					//- [Go Map North] -
						case LL_EventQueue::EVENT_GO_MAP_NORTH:
						{	//Capture the player's position and get the effect
								int iPlayerX = myoGame.Player().X();
    							int iPlayerY = myoGame.Player().Y();
								LL_BORDER_EFFECT iEffect = myoGame.TerrainMap().NorthEffect();
								LL_BORDER_WARP_TYPE iWarpType = myoGame.TerrainMap().NorthWarpType();
								
							//If theres a map to the north
								if(myoGame.TerrainMap().MapNorth() != NO_MAP)
    							{	//Load the map
		    							myoGame.LoadMap(myoGame.TerrainMap().MapNorth());
									//Load classes
										myoGame.LoadClasses("", mypoScreen);
									//Decide how to reposition the player
										if(iWarpType == WARP_TYPE_ROLL)
										{	myoGame.Player().Place
											(	iPlayerX,
       											myoGame.TerrainMap().MapBorderSouthY()
											);
										}
										else if(iWarpType == WARP_TYPE_ROLL_LAST_POSITION)
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().ExitX(),
       											myoGame.TerrainMap().ExitY() - 1
											);
										}
										else
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().PlayerX(),
   												myoGame.TerrainMap().PlayerY()
											);
										}
									//Init for the newly loaded map
										InitForNewMap();
									//Do a transition effect
										PerformEffect(iEffect);
								}
						}break;
					//- [Go Map South] -
						case LL_EventQueue::EVENT_GO_MAP_SOUTH:
						{	//Capture the player's position and get the effect
								int iPlayerX = myoGame.Player().X();
    							int iPlayerY = myoGame.Player().Y();
    							LL_BORDER_EFFECT iEffect = myoGame.TerrainMap().SouthEffect();
								LL_BORDER_WARP_TYPE iWarpType = myoGame.TerrainMap().SouthWarpType();
					
							//If theres a map to the south
								if(myoGame.TerrainMap().MapSouth() != NO_MAP)
								{	//Load the Southern map		
		    							myoGame.LoadMap(myoGame.TerrainMap().MapSouth());
									//Load classes
										myoGame.LoadClasses("", mypoScreen);
									//Decide how to reposition the player
										if(iWarpType == WARP_TYPE_ROLL)
										{	myoGame.Player().Place
											(	iPlayerX,
										        myoGame.TerrainMap().MapBorderNorthY()
											);
										}
										else if(iWarpType == WARP_TYPE_ROLL_LAST_POSITION)
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().ExitX(),
       											myoGame.TerrainMap().ExitY() + 1
											);
										}
										else
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().PlayerX(),
   												myoGame.TerrainMap().PlayerY()
											);
										}
									//Init for the newly loaded map
										InitForNewMap();
									//Do a transition effect
										PerformEffect(iEffect);
								}
						}break;
					//- [Go Map West] -
						case LL_EventQueue::EVENT_GO_MAP_WEST:
						{	//Capture the player's position and get the effect
								int iPlayerX = myoGame.Player().X();
    							int iPlayerY = myoGame.Player().Y();
    							LL_BORDER_EFFECT iEffect = myoGame.TerrainMap().WestEffect();
								LL_BORDER_WARP_TYPE iWarpType = myoGame.TerrainMap().WestWarpType();
					
							//If theres a map to the west
								if(myoGame.TerrainMap().MapWest() != NO_MAP)
								{	//Load the Western map
		    							myoGame.LoadMap(myoGame.TerrainMap().MapWest());
									//Load classes
										myoGame.LoadClasses("", mypoScreen);
									//Decide how to reposition the player
										if(iWarpType == WARP_TYPE_ROLL)
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().MapBorderEastX(),
   												iPlayerY
											);
										}
										else if(iWarpType == WARP_TYPE_ROLL_LAST_POSITION)
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().ExitX() - 1,
       											myoGame.TerrainMap().ExitY()
											);
										}
										else
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().PlayerX(),
   												myoGame.TerrainMap().PlayerY()
											);
										}
									//Init for the newly loaded map
										InitForNewMap();
									//Do a transition effect
										PerformEffect(iEffect);
								}
						}break;
					//- [Go Map East] -
						case LL_EventQueue::EVENT_GO_MAP_EAST:
						{	//Capture the player's position and get the effect
								int iPlayerX = myoGame.Player().X();
    							int iPlayerY = myoGame.Player().Y();
    							LL_BORDER_EFFECT iEffect = myoGame.TerrainMap().EastEffect();
								LL_BORDER_WARP_TYPE iWarpType = myoGame.TerrainMap().EastWarpType();
					
    						//Load the Eastern map (if legal)
		    					if(myoGame.TerrainMap().MapEast() != NO_MAP)
				    			{	myoGame.LoadMap(myoGame.TerrainMap().MapEast());
									//Load classes
										myoGame.LoadClasses("", mypoScreen);
									//Decide how to reposition the player
										if(iWarpType == WARP_TYPE_ROLL)
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().MapBorderWestX(),
          										iPlayerY
											);
										}
										else if(iWarpType == WARP_TYPE_ROLL_LAST_POSITION)
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().ExitX() + 1,
       											myoGame.TerrainMap().ExitY()
											);
										}
										else
										{	myoGame.Player().Place
											(	myoGame.TerrainMap().PlayerX(),
   												myoGame.TerrainMap().PlayerY()
											);
										}
									//Init for the newly loaded map
										InitForNewMap();
									//Do a transition effect
										PerformEffect(iEffect);
								}
						}break;
					//- [Go Map Map] -
						case LL_EventQueue::EVENT_GO_MAP:
						{	//If the map doesn't exist error
								if(oEvent.myiParam1 < 0 || oEvent.myiParam1 >= myoGame.MapSet().NumMaps())
								{	myoPaint.TalkConsole() << "* * * * * *\n" << "ERROR!\n";
									myoPaint.TalkConsole() << "Map: " << oEvent.myiParam1
         												   << " doesn't exist!\n";
									return;
								}
							//If the position is invalid error
								if(oEvent.myiParam3 >= 100 ||
        						   oEvent.myiParam4 >= 100)
								{	myoPaint.TalkConsole() << "* * * * * *\n" << "ERROR!\n";
									myoPaint.TalkConsole() << "Position: " << oEvent.myiParam3
         												   << ":" << oEvent.myiParam4
                        								   << " doesn't exist!\n";
									return;
								}
      						//Load the map
		    					myoGame.LoadMap(oEvent.myiParam1);
							//Load classes
								myoGame.LoadClasses("", mypoScreen);
							//Reposition the player
								if(oEvent.myiParam3 >= 0)
									myoGame.Player().Place(oEvent.myiParam3, oEvent.myiParam4);
								else
									myoGame.Player().Place
									(	myoGame.TerrainMap().PlayerX(),
										myoGame.TerrainMap().PlayerY()
									);
							//Init for the newly loaded map
								InitForNewMap();
							//Do a transition effect
								PerformEffect((LL_BORDER_EFFECT)oEvent.myiParam2);
						}break;
					//- [ZStats] -
						case LL_EventQueue::EVENT_ZSTATS:
						{	//Black out the play area
	      						mypoScreen->DrawFillRectangle
    	  						(	PLAYFIELD_X, PLAYFIELD_Y,
        	    					PLAYFIELD_X2 - PLAYFIELD_X,
            						PLAYFIELD_Y2 - PLAYFIELD_Y,
            						COLOR_BLACK,
            						100
            					);
      						myoZStats.Display(&Game());
						}break;
					//- [Ready] -
						case LL_EventQueue::EVENT_READY:
						{	//Black out the play area
	      						mypoScreen->DrawFillRectangle
    	  						(	PLAYFIELD_X, PLAYFIELD_Y,
        	    					PLAYFIELD_X2 - PLAYFIELD_X,
            						PLAYFIELD_Y2 - PLAYFIELD_Y,
            						COLOR_BLACK,
            						100
	            				);
      						myoReady.SetScreen(mypoScreen);
							myoReady.SetPainter(&myoPaint);
      						myoReady.Display(myoZStats.GetPlayer(&Game()), &Game());

						}break;
					//- [Gosub Global] -
						case LL_EventQueue::EVENT_GOSUB_GLOBAL:
						{	//Gosub on
	      						Game().LOOP().GosubInstance(LL_Game__GLOBAL_IDENTIFIER, oEvent.mysParam1);
						}break;
					//- [Call] -
						case LL_EventQueue::EVENT_CALL:
						{	Game().LOOP().GosubInstance(oEvent.mysParam1, oEvent.mysParam2);
							myiOnlyExecuteUnit.Push(oEvent.myiParam1);
							myiOnlyExecuteUnit.Push(myoGame.UnitSet().ScriptedUnit(UpperString(oEvent.mysParam1)).Off());
						}break;
					//- [Call Position] -
						case LL_EventQueue::EVENT_CALL_POSITION:
						{	//Vars
								bool fExitLoop = false;
								int iSeg, iOff;
							//Loop through all layers
	      						for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS && !fExitLoop; iLayer++)
								{	if(Game().UnitMap().SegOn(oEvent.myiParam1, oEvent.myiParam2, iLayer) == LL_UnitMap::SEG_SCRIPTED_UNITS)
									{	iSeg = Game().UnitMap().SegOn(oEvent.myiParam1, oEvent.myiParam2, iLayer);
       									iOff = Game().UnitMap().OffOn(oEvent.myiParam1, oEvent.myiParam2, iLayer);
         								Game().LOOP().GosubInstance
                 						(	UpperString(Game().UnitSet().ScriptedUnit(iOff).Identifier()),
                       						oEvent.mysParam1
                 						);
										myiOnlyExecuteUnit.Push(oEvent.myiParam3);
										myiOnlyExecuteUnit.Push(iOff);
										fExitLoop = true;
									}
      							}
						}break;
					//- [Ping] -
						case LL_EventQueue::EVENT_PING:
						{	myoGame.UnitSet().Ping(oEvent.mysParam1);
						}break;
					//- [Ping class] -
						case LL_EventQueue::EVENT_PING_CLASS:
						{	myoGame.UnitSet().PingClass(oEvent.mysParam1, oEvent.mysParam2);
						}break;
					//- [Ping class & derivs] -
						case LL_EventQueue::EVENT_PING_CLASS_DERIV:
						{	myoGame.UnitSet().PingClassAndDeriv(oEvent.mysParam1, oEvent.mysParam2);
						}break;
					//- [Help] -
						case LL_EventQueue::EVENT_HELP:
						{	mypoHelp->RunnerHelp();
						}break;
					//- [Board] -
						case LL_EventQueue::EVENT_BOARD_VEHICLE:
						{	//!!! Make sure a vehicle exists here.
							//Change the graphic
								myoGame.Player().SetAnimation
								(	myoGame.UnitSet().VehicleObject
									(	myoGame.UnitMap().OffOn(oEvent.myiParam1,
																oEvent.myiParam2,
																LL_UnitMap::LAYER_VEHICLE)
									)
								);
							//Switch the player's vehicle
								myoGame.Player().ChangeVehicle
								(	myoGame.UnitSet().VehicleObject
									(	myoGame.UnitMap().OffOn(oEvent.myiParam1,
																oEvent.myiParam2,
																LL_UnitMap::LAYER_VEHICLE)
									).VehicleCode()
								);
								myoGame.Player().SetVehicleObject
								(	myoGame.UnitSet().VehicleObjectNum
									(	myoGame.UnitMap().OffOn(oEvent.myiParam1,
																oEvent.myiParam2,
																LL_UnitMap::LAYER_VEHICLE)
									)
								);
							//Remove that vehicle
								myoGame.UnitSet().RemoveVehicle
								(	myoGame.UnitMap().OffOn(oEvent.myiParam1,
									oEvent.myiParam2,
									LL_UnitMap::LAYER_VEHICLE)
								);

							//Ra ra redraw
								Draw();
						}break;
					// - [Redraw map] -
						case LL_EventQueue::EVENT_REDRAW_MAP:
						{	//Re:Re:ReDraw!
								Draw();
								myiOnlyExecuteUnit.Push(oEvent.myiParam1);
								mypoScreen->Update();
							//Lock all units for the next turn except 
								//myoGame.UnitSet().Run();
						}break;
					// - [Do Effect] -
						case LL_EventQueue::EVENT_DO_EFFECT:
						{	//Do effect
								PerformEffect(LL_BORDER_EFFECT(oEvent.myiParam1));
							//Lock all units for the next turn except iOff
								myiOnlyExecuteUnit.Push(oEvent.myiParam2);
						}break;
					// - [Do Image Effect] -
						case LL_EventQueue::EVENT_DO_EFFECT_WITH_IMAGE:
						{	//Do effect
								PerformEffect
	       						(	LL_BORDER_EFFECT(oEvent.myiParam3),
	             					oEvent.mysParam1,
   									oEvent.myiParam1,
	           						oEvent.myiParam2
    	             			);
							
							//Lock all units for the next turn except iOff
								myiOnlyExecuteUnit.Push(oEvent.myiParam4);
						}break;
					//- [Exit] -
						case LL_EventQueue::EVENT_DEBOARD_VEHICLE:
						{	string s;
							//Switch the player's vehicle to the default
								myoGame.Player().ChangeVehicle(0);
							//Reload the player image
	 							myoGame.Player().LoadAnimation("/creatures/player_n.png", myoGame.GraphicsDir(), TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);	//!!!
							//Plot a vehicle here if the player was on one
								if(myoGame.Player().VehicleObject() >= 0)
								{	int iUnit;
									int iX = myoGame.Player().X();
									int iY = myoGame.Player().Y();
									myoGame.UnitSet().AddVehicle(iX, iY, LL_UnitMap::LAYER_VEHICLE, "", myoGame.Player().VehicleObject());
									iUnit = myoGame.UnitSet().NumVehicles() - 1;
									myoGame.UnitMap().SetUnitOn(iX, iY, LL_UnitMap::LAYER_VEHICLE, LL_UnitSet::SEG_VEHICLES, iUnit);
								}
								myoGame.Player().SetVehicleObject(-1);
						}break;
					//- [Lighting] -
						case LL_EventQueue::EVENT_LIGHTING:
						{	if(oEvent.myiParam1 == 1)
								myfViewAll = false;
							else
								myfViewAll = true;
							myiOnlyExecuteUnit.Push(oEvent.myiParam2);
							mypoScreen->Update();
						}break;
					//- [Switch units] -
						case LL_EventQueue::EVENT_SWITCH_UNITS:
						{	//If the two units in question exist
								if(myoGame.UnitSet().UnitExists(oEvent.myiParam1, oEvent.myiParam2) &&
								   myoGame.UnitSet().UnitExists(oEvent.myiParam3, oEvent.myiParam4))
								{	//Save information about their positions
										LL_Unit* mypoUnit1 = &myoGame.UnitSet().Unit(oEvent.myiParam1, oEvent.myiParam2);
										LL_Unit* mypoUnit2 = &myoGame.UnitSet().Unit(oEvent.myiParam3, oEvent.myiParam4);
										int iUnit1X = mypoUnit1->X();
										int iUnit1Y = mypoUnit1->Y();
									//Now switch em
										mypoUnit1->SetX(mypoUnit2->X());
										mypoUnit1->SetY(mypoUnit2->Y());
										myoGame.UnitMap().SetUnitOn
          								(	mypoUnit2->X(), mypoUnit2->Y(), mypoUnit1->Layer(),
                  							mypoUnit1->Seg(), mypoUnit1->Off()
                         				);
                  							
										mypoUnit2->SetX(iUnit1X);
										mypoUnit2->SetY(iUnit1Y);
										myoGame.UnitMap().SetUnitOn
          								(	iUnit1X, iUnit1Y, mypoUnit2->Layer(),
                  							mypoUnit2->Seg(), mypoUnit2->Off()
                         				);
								}
						}break;
					//- [Call Units Under] -
						case LL_EventQueue::EVENT_CALL_UNITS_UNDER:
						{	//Vars
								bool fExitLoop = false;
								int iSeg, iOff;
							//Loop through all layers below the calling layer
	      						for(int iLayer = 0; iLayer < oEvent.myiParam3 && !fExitLoop; iLayer++)
								{	if(Game().UnitMap().SegOn(oEvent.myiParam1, oEvent.myiParam2, iLayer) == LL_UnitMap::SEG_SCRIPTED_UNITS)
									{	iSeg = Game().UnitMap().SegOn(oEvent.myiParam1, oEvent.myiParam2, iLayer);
       									iOff = Game().UnitMap().OffOn(oEvent.myiParam1, oEvent.myiParam2, iLayer);
         								Game().LOOP().GosubInstance
                 						(	UpperString(Game().UnitSet().ScriptedUnit(iOff).Identifier()),
                       						oEvent.mysParam1
                 						);
										myiOnlyExecuteUnit.Push(oEvent.myiParam3);
										myiOnlyExecuteUnit.Push(iOff);
										
										//Delete the global call
											Game().EventQueue().DeleteGosubCall();
									}
      							}
						}break;
					//- [Sleep] -
						case LL_EventQueue::EVENT_SLEEP:
						{	//Vars
								ASFC_Timer oTime;
      						//Loop for the number of hours in sleep
								for(int iHour = 0; iHour < oEvent.myiParam1; iHour++)
								{	//Loop through all members in the players party
										for(int iMember = 0; iMember < myoGame.Player().PartyMembers().Length(); iMember++)
										{	//See if this player gets to heal this hour
												int iRand = PollRandom(100);
												if(iRand < oEvent.myiParam2)
												{	myoGame.Player().PartyMembers()[iMember].AddHP(oEvent.myiParam3);
												}
										}
									//Loop for 12 5 minute segments
										for(int i = 0; i < 12; i++)
										{	//Add an 10 minutes of sleep in
												myoGame.Clock().AddTicks(myoGame.Clock().TicksPerMinute() * 5);
											//Redraw
												Draw();
												mypoScreen->Update();
											//Pause
												oTime.Reset();
												oTime.Delay(SLEEP_DELAY);
										}
								}
						}break;
				}
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_LoreAndLutes::PerformEffect(LL_BORDER_EFFECT iEffect, string sAddImage, int iImageX, int iImageY)
{	//Save pictures of the map
		ASFC_Surface oSurf1(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
		oSurf1.Blit(*mypoScreen, 0, 0);
		Draw();
		//If we're adding an image add it
			if(sAddImage != "")
			{	ASFC_Surface oAddImage;
				oAddImage.LoadImage(sAddImage, COLOR_BLUE);
				oAddImage.BlitTo(*mypoScreen, iImageX, iImageY);
			}
		ASFC_Surface oSurf2(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
		oSurf2.Blit(*mypoScreen, 0, 0);

	//Decide what to do based on which effect
		switch(iEffect)
		{	case BORDER_EFFECT_NONE:
			{
			}break;
			
			case BORDER_EFFECT_FADE:
			{	myoEffects.FadeOutAndIn(oSurf1, oSurf2, *mypoScreen);
			}break;
			
			case BORDER_EFFECT_DISSOLVE:
			{	myoEffects.Dissolve(oSurf1, oSurf2, *mypoScreen);
			}break;
			
			case BORDER_EFFECT_TRIAMBULATE:
			{	myoEffects.Triambulate(oSurf1, oSurf2, *mypoScreen);
			}break;
			
			case BORDER_EFFECT_CHECKERBOARD:
			{	myoEffects.CheckerBoard(oSurf1, oSurf2, *mypoScreen);
			}break;

			case BORDER_EFFECT_BLEND:
			{	myoEffects.Blend(oSurf1, oSurf2, *mypoScreen, 25, 15);
			}break;

			case BORDER_EFFECT_SPLIT_VERTICLE:
			{	myoEffects.SplitVert(oSurf1, oSurf2, *mypoScreen, 5, 4);
			}break;

			case BORDER_EFFECT_SPLIT_HORIZONTAL:
			{	myoEffects.SplitHoriz(oSurf1, oSurf2, *mypoScreen, 5, 4);
			}break;
			
			default: break;
		};
}
