/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			ready.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "ready.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LL_Ready
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LL_Ready::LL_Ready()
{	myiLine = 0;
}
//--------------------------------------------------------------------------------------------- [Display] -
void LL_Ready::Display(int iPlayer, LL_Game* pGame)
{	//Vars
		int iLastOption = -100;

	//Map params to var
		mypoGame = pGame;
		myiPlayer = iPlayer;
	//If we have an invalid player stop
		if(iPlayer < 0)
			return;
	//Grab away
		while(iLastOption != OPTION_EXIT)
		{	//Setup
				SetupScreen();
			//Grab
				iLastOption = GrabOption();
			//Proc it
				ProcessOption(iLastOption);
		}
}
//P--------------------------------------------------------------------------------------------- [Ready] -P
void LL_Ready::SetupScreen()
{	//Clear old data
		mylEntries.Resize(0);
		int iNumItems;
		bool fHasItem;
		string s;
		char strNum[80];

	//Grab a pointer to the party member
		LL_PartyMember* poMember = &mypoGame->Player().PartyMembers()[myiPlayer];
	//Display all weapons
		for(int i = 0; i < mypoGame->Player().Inventory().NumTypesWeapons(); i++)
		{	//Grab the # of items
				iNumItems = mypoGame->Player().Inventory().Weapons(i);
			//Does the player have this item
				fHasItem = false;
				if(poMember->HoldsWeapon(i) > 0) fHasItem = true;
			//If the player either has this item or this item is in the inventory
				if(fHasItem || iNumItems > 0)
				{	//Write this entry write (X) if the player has this item
						s = "";
						if(fHasItem)
							s += "(X) ";
						sprintf(strNum, "%2u", mypoGame->Player().Inventory().Weapons(i));
   						s += strNum;
       					s += " ";
		          		s += mypoGame->ItemSet().Weapon(i).Identifier();
						mylEntries.Push(s);
				}
		}
	//Display all armors
		for(int i = 0; i < mypoGame->Player().Inventory().NumTypesArmors(); i++)
		{	//Grab the # of items
				iNumItems = mypoGame->Player().Inventory().Armors(i);
			//Does the player have this item
				fHasItem = false;
				if(poMember->HoldsArmor(i) > 0) fHasItem = true;
			//If the player either has this item or this item is in the inventory
				if(fHasItem || iNumItems > 0)
				{	//Write this entry write (X) if the player has this item
						s = "";
						if(fHasItem)
							s += "(X) ";
						sprintf(strNum, "%2u", mypoGame->Player().Inventory().Armors(i));
   						s += strNum;
       					s += " ";
		          		s += mypoGame->ItemSet().Armor(i).Identifier();
						mylEntries.Push(s);
				}
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_Ready::ProcessOption(int iOption)
{	//Vars
		int tiOptionCount = -1;
		int iNumItems;
		bool fHasItem;
			
	//If the option is less then zero we're done
		if(iOption < 0)
			return;
			
	//Grab a pointer to the party member
		LL_PartyMember* poMember = &mypoGame->Player().PartyMembers()[myiPlayer];
	//Think of all the weapons (so we can determine which weapon is matched to iOption)
		for(int i = 0; i < mypoGame->Player().Inventory().NumTypesWeapons(); i++)
		{	//Grab the # of items
				iNumItems = mypoGame->Player().Inventory().Weapons(i);
			//Does the player have this item
				fHasItem = false;
				if(poMember->HoldsWeapon(i) > 0) fHasItem = true;
			//If the player either has this item or this item is in the inventory
				if(fHasItem || iNumItems > 0)
				{	//Add to tiOptionCount
						tiOptionCount ++;
				}
			//If we've found the right weapon
				if(tiOptionCount == iOption)
				{	//If it's not currently equipped
						if(!fHasItem)
						{	//You must equip it. Equip it good!
								if(poMember->EquipWithWeapon(i, &mypoPainter->TalkConsole(), mypoScreen))
								{	//And if we equipped it lower the number in inventory
										mypoGame->Player().Inventory().TakeWeapon(i, 1);
								}
							return;
						}
					//If we need to unequipinate it
						else
						{ poMember->UnEquipWeapon(i);
							mypoGame->Player().Inventory().GiveWeapon(i, 1);
							return;
						}
				}
		}
	//Think of all the armors (so we can determine which armor is matched to iOption)
		for(int i = 0; i < mypoGame->Player().Inventory().NumTypesArmors(); i++)
		{	//Grab the # of items
				iNumItems = mypoGame->Player().Inventory().Armors(i);
			//Does the player have this item
				fHasItem = false;
				if(poMember->HoldsArmor(i) > 0) fHasItem = true;
			//If the player either has this item or this item is in the inventory
				if(fHasItem || iNumItems > 0)
				{	//Add to tiOptionCount
						tiOptionCount ++;
				}
			//If we've found the right Armor
				if(tiOptionCount == iOption)
				{	//If it's not currently equipped
						if(!fHasItem)
						{	//You must equip it. Equip it good!
								if(poMember->EquipWithArmor(i, &mypoPainter->TalkConsole(), mypoScreen))
								{	//And if we equipped it lower the number in inventory
										mypoGame->Player().Inventory().TakeArmor(i, 1);
								}
							return;
						}
					//If we need to unequipinate it
						else
						{	poMember->UnEquipArmor(i);
							mypoGame->Player().Inventory().GiveArmor(i, 1);
							return;
						}
				}
		}
}
