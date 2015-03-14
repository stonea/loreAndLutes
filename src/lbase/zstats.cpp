/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			zstats.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "zstats.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LL_ZStats
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LL_ZStats::LL_ZStats()
{
}
//--------------------------------------------------------------------------------------------- [Display] -
void LL_ZStats::Display(LL_Game* pGame)
{	//Vars
		int iLastOption;
		mypoGame = pGame;

	//Clear
		mypoPainter->StatsConsole().Clear();
		myiLine = 0;
		myiScreen = 0;
		myfScreenLock = true;
		myfDrawCursor = true;
		iLastOption = -100;
		myfUsingItem = false;

	//Grab away
		myfQuit = false;
		while(!myfQuit)
		{	//Setups
				SetupScreen();
			//Grab
				iLastOption = GrabOption();
			//Proc it
				ProcessOption(iLastOption);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ZStats::UseItem(LL_Game* pGame)
{	//Vars
		int iOption;
		mypoGame = pGame;

	//Clear
		mypoPainter->StatsConsole().Clear();
		myiLine = 0;
		myfDrawCursor = true;
		myfScreenLock = false;
		myfUsingItem = true;
		myiScreen = SCREEN_INVENTORY_SCRIPTS;
	//Setup
		SetupScreen();

	//Grab away
		iOption  = GrabOption() - HEADER_LINES;
		int iNum = mypoGame->Player().Inventory().ScriptedItemNum(iOption);
	//If we have an item use it
		if(iNum >= 0 && iNum < mypoGame->ItemSet().NumScriptedItems())
		{	//Get the label to call
	  			string sCall = mypoGame->ItemSet().ScriptedItem(iNum).Call();
			//Decide what to do based on the message type
				switch(mypoGame->ItemSet().ScriptedItem(iNum).Message())
				{	case LL_ScriptedItem::MESSAGE_GLOBAL:
						pGame->EventQueue().GosubGlobal(sCall);
					break;
		
					case LL_ScriptedItem::MESSAGE_PING:
						pGame->EventQueue().Ping(sCall);
					break;

					case LL_ScriptedItem::MESSAGE_PING_CLASS:
						pGame->EventQueue().PingClass
						(	mypoGame->ItemSet().ScriptedItem(iNum).MessageClass(),
							sCall
						);
					break;

					case LL_ScriptedItem::MESSAGE_PING_CLASS_DERIV:
						pGame->EventQueue().PingClassDeriv
						(	mypoGame->ItemSet().ScriptedItem(iNum).MessageClass(),
							sCall
						);
					break;

					default:
					break;
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_ZStats::GetPlayer(LL_Game* pGame)
{	//Vars
		int iOption;
		mypoGame = pGame;

	//If there's no player don't zStat
		if(mypoGame->Player().PartyMembers().Length() <= 0)
			return -1;
	//Clear
		myfUsingItem = false;
		mypoPainter->StatsConsole().Clear();
		myiLine = 0;
		myiScreen = SCREEN_PLAYERS;
	//Setup
		SetupScreen();
	//Grab away
		return(GrabOption());
}
//-------------------------------------------------------------------------------------------- [ZStating] -
void LL_ZStats::SetupScreen()
{	//Clear old data
		mylEntries.Resize(0);
		myiLine = 0;

	//Decide what to display based on what screen we're on
		//- [Players] -
	 		if(myiScreen == SCREEN_PLAYERS)
			{	for(int i = 0; i < mypoGame->Player().PartyMembers().Length(); i++)
	   				mylEntries.Push(mypoGame->Player().PartyMembers().operator[](i).Name());

	   			myfDrawCursor = true;
				myfScreenLock = true;
			}
		//- [Player Info] -
			else if(myiScreen >= SCREEN_PLAYER1_INFO && myiScreen <= SCREEN_PLAYER8_INFO)
			{	SetupPlayerInfo(myiScreen - SCREEN_PLAYER1_INFO);
				myfDrawCursor = false;
				myfScreenLock = true;
			}
		//- [Battle Inventory] -
			else if(myiScreen == SCREEN_INVENTORY_BATTLE)
			{	mylEntries = mypoGame->Player().Inventory().BattleItemInventory(&mypoGame->ItemSet());

				myfDrawCursor = false;
				myfScreenLock = false;
			}
		//- [Scripted Inventory] -
			else if(myiScreen == SCREEN_INVENTORY_SCRIPTS)
			{	mylEntries = mypoGame->Player().Inventory().ScriptedItemInventory(&mypoGame->ItemSet());

				if(!myfUsingItem)
       			{	myfDrawCursor = false;
					myfScreenLock = false;
				}
			}
		//- [Gold and Food] -
			else if(myiScreen == SCREEN_GOLD_FOOD)
			{	mylEntries.Resize(0);
				mylEntries.Push("Gold:    " + Val(mypoGame->Player().Inventory().Gold()));
				mylEntries.Push("Food:    " + Val(mypoGame->Player().Inventory().Food()));
				mylEntries.Push("Torches: " + Val(mypoGame->Player().Inventory().Torches()));
			}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ZStats::SetupPlayerInfo(int iPlayer)
{	//Vars
		string s;
	//If this member exists
		if(iPlayer < mypoGame->Player().PartyMembers().Length())
		{	//Get the member
	  			LL_PartyMember oMember = mypoGame->Player().PartyMembers().operator[](iPlayer);
			//Display information
				mylEntries.Push("Name:   " + oMember.Name());
				mylEntries.Push("--------------------");
				s = "Gender  ";
				s += oMember.Gender();
				mylEntries.Push(s);
				s = "State:  ";
				s += oMember.State();
				mylEntries.Push(s);
				mylEntries.Push("Str:    " + Val(oMember.Strength()));
				mylEntries.Push("Dex:    " + Val(oMember.Dexterity()));
				mylEntries.Push("Int:    " + Val(oMember.Intelligence()));
				mylEntries.Push("MP\\MAX: " + Val(oMember.MP()) + "\\" + Val(oMember.MaxMP()));
				mylEntries.Push("HP\\MAX: " + Val(oMember.HP()) + "\\" + Val(oMember.MaxHP()));
				mylEntries.Push("Exp:    " + Val(oMember.Experience()));
			//Set the line
				myiLine  = 5;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ZStats::ProcessOption(int iOption)
{	//Decide what to do based on the option
		//- [Quit] -
			if(iOption == OPTION_EXIT)
			{	//If we're at the start screen quit, otherwise go to the start screen
					if(myiScreen != 0)
					{	myiScreen = 0;
					}
					else
						myfQuit = true;
			}
		//- [Next Screen] -
	  		else if(iOption == OPTION_NEXT_SCREEN)
			{	if(myiScreen + 1 < SCREEN_COUNT)
	   				myiScreen++;
				else
					myiScreen = 0;
					
				//If we're on a screen for a player who isn't a member yet go to the inventory screen
					if(myiScreen > mypoGame->Player().PartyMembers().Length() - SCREEN_PLAYER1_INFO +1 &&
     					myiScreen < SCREEN_INVENTORY_BATTLE)
					{
     					myiScreen = SCREEN_INVENTORY_BATTLE;
					}
			}
		//- [Previous Screen] -
			else if(iOption == OPTION_PREV_SCREEN)
			{	if(myiScreen - 1 >= 0)
		   			myiScreen--;
				else
					myiScreen = SCREEN_COUNT - 1;
					
				//If we're on a screen for a player who isn't a member yet go to the last member
					if(myiScreen > mypoGame->Player().PartyMembers().Length() - SCREEN_PLAYER1_INFO +1 &&
     					myiScreen < SCREEN_INVENTORY_BATTLE)
					{
     					myiScreen = mypoGame->Player().PartyMembers().Length() + SCREEN_PLAYER1_INFO -1;
					}
			}
		//- [Player to view] -
			else if(iOption >= 0)
			{	myiScreen = SCREEN_PLAYER1_INFO + iOption;
			}
	//Make sure the cursor is off except if we're on the first screen
		if(myiScreen == 0)
			myfDrawCursor = true;
		else
			myfDrawCursor = false;
}
