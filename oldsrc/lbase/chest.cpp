/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			chest.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "chest.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Chest
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Chest::LL_Chest()
	: myfDisappears(false)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Chest::Save(ofstream &oFile)
{	//%X Local%, %Y Local%, %Layer%
		oFile << Val(myiX) << " " << Val(myiY) << " " << Val(myiLayer) << " ";
	//"Image file"  %Custom image%
		oFile << Qoute(ImageFile()) << " ";
		oFile << myfCustomImage << " ";
	//?Disappears?
		oFile << myfDisappears << " ";
	//<Loop through all contents>
		oFile << myloItems.Length() << " ";
		for(int i = 0; i < myloItems.Length(); i++)
		{	//%Type%
				oFile << int(myloItems[i].iType) << " ";
   			//%Offset%
   				oFile << myloItems[i].iItemOff << " ";
   			//%Amount%
   				oFile << myloItems[i].iAmount << " ";
			//%Chance%
   				oFile << myloItems[i].iChance << " ";
		}
	//<endl>
		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Chest::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		int iX, iY, iL;
		string sImage;
		int iNumItems;
		int iType;

	//%X Local%, %Y Local%, %Layer%
		oFile >> iX >> iY >> iL;
		SetX(iX);
		SetY(iY);
		SetLayer(iL);
	//"Image file" %Custom image%
		sImage = ReadString(oFile);
		oFile >> myfCustomImage;
		LoadAnimation(sImage, sGraphicsDir);
	//?Disappears?
		oFile >> myfDisappears;
	//<Loop through all contents>
		oFile >> iNumItems;
		myloItems.Resize(iNumItems);
		for(int i = 0; i < iNumItems; i++)
		{	//%Type%
				oFile >> iType;
    			myloItems[i].iType = LL_ChestItemType(iType);
   			//%Offset%
				oFile >> myloItems[i].iItemOff;
   			//%Amount%
				oFile >> myloItems[i].iAmount;
			//%Chance%
   				oFile >> myloItems[i].iChance;
		}
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_Chest::Talk()
{	//!!!
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::Look()
{	//!!!
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Chest::Push()
{	//!!!
		return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::Search(LL_ItemSet* poItemSet, ASFC_Console* poConsole)
{	//Vars
		string ts;
		double dRand;
		int iItemsAquired = 0;
		
	//Display Message:
		poConsole->Writeln("Found:", 1);
	//Loop through all items, adding each one
		for(int i = 0; i < myloItems.Length(); i++)
		{	//Determine randomley whether to actually give this item
				//Grab a random value from (0-1)
					dRand = rand()/(RAND_MAX + 1.0);
				//Determine whether to give
					if(dRand <= myloItems[i].iChance)
					{	//Increase the # of item's aquired
							iItemsAquired++;
     					//Give the appropriate type of item
				  			switch(myloItems[i].iType)
							{	case TYPE_ARMOR:
								{	ts = Val(myloItems[i].iAmount);
									ts += ": ";
      								ts += poItemSet->Armor(myloItems[i].iItemOff).Identifier();
      								poConsole->Writeln(ts, 1);
								}break;
					
								case TYPE_WEAPON:
								{	ts = Val(myloItems[i].iAmount);
									ts += ": ";
			      					ts += poItemSet->Weapon(myloItems[i].iItemOff).Identifier();
      								poConsole->Writeln(ts, 1);
								}break;
					
								case TYPE_SCRIPTED_ITEM:
								{	ts = Val(myloItems[i].iAmount);
									ts += ": ";
      								ts += poItemSet->ScriptedItem(myloItems[i].iItemOff).Identifier();
			      					poConsole->Writeln(ts, 1);
								}break;
								
								case TYPE_GOLD:
								{	ts = Val(myloItems[i].iAmount);
			      					ts += ": Gold";
      								poConsole->Writeln(ts, 1);
								}break;
								
								case TYPE_FOOD:
								{	ts = Val(myloItems[i].iAmount);
			      					ts += ": Food";
      								poConsole->Writeln(ts, 1);
								}break;
								
								case TYPE_TORCHES:
								{	ts = Val(myloItems[i].iAmount);
			      					ts += ": Torches";
      								poConsole->Writeln(ts, 1);
								}break;
					
								default:
								{	cerr << "What the! You found the item from helk! The password is XYZZY.\n";
								}break;
							}
						//End the line
							poConsole->Writeln("", 1);
					}
		}
	//If the player got nothing call him stoopid
		if(iItemsAquired == 0)
			poConsole->Writeln("Nothing", 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::Attack()
{	//!!!
}
//------------------------------------------------------------------------------------------- [Contents] -
void LL_Chest::AddArmor(int iArmor, int iAmount)
{	myloItems.Resize(myloItems.Length() + 1);
	int iUnit = myloItems.Length() - 1;
	myloItems[iUnit].iType	 = TYPE_ARMOR;
	myloItems[iUnit].iItemOff = iArmor;
	myloItems[iUnit].iAmount  = iAmount;
	myloItems[iUnit].iChance  = 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::AddWeapon(int iWeapon, int iAmount)
{	myloItems.Resize(myloItems.Length() + 1);
	int iUnit = myloItems.Length() - 1;
	myloItems[iUnit].iType	 = TYPE_WEAPON;
	myloItems[iUnit].iItemOff = iWeapon;
	myloItems[iUnit].iAmount  = iAmount;
	myloItems[iUnit].iChance  = 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::AddScriptedItem(int iScriptedItem, int iAmount)
{	myloItems.Resize(myloItems.Length() + 1);
	int iUnit = myloItems.Length() - 1;
	myloItems[iUnit].iType	 = TYPE_SCRIPTED_ITEM;
	myloItems[iUnit].iItemOff = iScriptedItem;
	myloItems[iUnit].iAmount  = iAmount;
	myloItems[iUnit].iChance  = 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::AddGold(int iAmount)
{	myloItems.Resize(myloItems.Length() + 1);
	int iUnit = myloItems.Length() - 1;
	myloItems[iUnit].iType	 = TYPE_GOLD;
	myloItems[iUnit].iAmount  = iAmount;
	myloItems[iUnit].iChance  = 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::AddFood(int iAmount)
{	myloItems.Resize(myloItems.Length() + 1);
	int iUnit = myloItems.Length() - 1;
	myloItems[iUnit].iType	 = TYPE_FOOD;
	myloItems[iUnit].iAmount  = iAmount;
	myloItems[iUnit].iChance  = 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::AddTorches(int iAmount)
{	myloItems.Resize(myloItems.Length() + 1);
	int iUnit = myloItems.Length() - 1;
	myloItems[iUnit].iType	  = TYPE_TORCHES;
	myloItems[iUnit].iAmount  = iAmount;
	myloItems[iUnit].iChance  = 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Chest::NumItems()
{	return(myloItems.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Chest::LL_ChestItem& LL_Chest::Item(int iNum)
{	return(myloItems[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Chest::ClearItems()
{	myloItems.Resize(0);
}
//--------------------------------------------------------------------------------------------- [Giving] -
void LL_Chest::AddToInventory(LL_Inventory* poInventory,  LL_ItemSet* poItemSet, ASFC_Console* poConsole)
{	//Vars
		string ts;
		double dRand;
		int iItemsAquired = 0;
		
	//Display Message:
		poConsole->Writeln("Recieved:", 1);
	//Loop through all items, adding each one
		for(int i = 0; i < myloItems.Length(); i++)
		{	//Determine randomley whether to actually give this item
				//Grab a random value from (0-1)
					dRand = rand()/(RAND_MAX + 1.0);
				//Determine whether to give
					if(dRand <= myloItems[i].iChance)
					{	//Increase the # of item's aquired
							iItemsAquired++;
     					//Give the appropriate type of item
				  			switch(myloItems[i].iType)
							{	case TYPE_ARMOR:
								{	poInventory->GiveArmor(myloItems[i].iItemOff, myloItems[i].iAmount);
									ts = Val(myloItems[i].iAmount);
									ts += ": ";
      								ts += poItemSet->Armor(myloItems[i].iItemOff).Identifier();
      								poConsole->Writeln(ts, 1);
								}break;
					
								case TYPE_WEAPON:
								{	poInventory->GiveWeapon(myloItems[i].iItemOff, myloItems[i].iAmount);
									ts = Val(myloItems[i].iAmount);
									ts += ": ";
			      					ts += poItemSet->Weapon(myloItems[i].iItemOff).Identifier();
      								poConsole->Writeln(ts, 1);
								}break;
					
								case TYPE_SCRIPTED_ITEM:
								{	poInventory->GiveScriptedItem(
        								myloItems[i].iItemOff, myloItems[i].iAmount);
									ts = Val(myloItems[i].iAmount);
									ts += ": ";
      								ts += poItemSet->ScriptedItem(myloItems[i].iItemOff).Identifier();
			      					poConsole->Writeln(ts, 1);
								}break;
								
								case TYPE_GOLD:
								{	poInventory->GiveGold(myloItems[i].iAmount);
									ts = Val(myloItems[i].iAmount);
			      					ts += ": Gold";
      								poConsole->Writeln(ts, 1);
								}break;
								
								case TYPE_FOOD:
								{	poInventory->GiveFood(myloItems[i].iAmount);
									ts = Val(myloItems[i].iAmount);
			      					ts += ": Food";
      								poConsole->Writeln(ts, 1);
								}break;
								
								case TYPE_TORCHES:
								{	poInventory->GiveTorches(myloItems[i].iAmount);
									ts = Val(myloItems[i].iAmount);
			      					ts += ": Torches";
      								poConsole->Writeln(ts, 1);
								}break;
					
								default:
								{	cerr << "What the! You found the item from helk! The password is XYZZY.\n";
								}break;
							}
						//End the line
							poConsole->Writeln("", 1);
					}
		}
	//If the player got nothing call him stoopid
		if(iItemsAquired == 0)
			poConsole->Writeln("Nothing", 1);
}
