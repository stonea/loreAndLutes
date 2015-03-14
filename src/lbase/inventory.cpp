/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			inventory.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
#include "inventory.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Inventory
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Inventory::LL_Inventory()
{	//Start off drunk po'
		myiGold = 0;
		myiFood = 0;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::Init(LL_ItemSet* poSet)
{	mypoSet = poSet;
	mylArmors.Resize(poSet->NumArmors(), 0);
	mylWeapons.Resize(poSet->NumWeapons(), 0);
	mylScriptedItems.Resize(poSet->NumScriptedItems(), 0);
	
	//Clear out the lists
		for(int i = 0; i < mylArmors.Length(); i++)
		{	mylArmors[i] = 0;
		}
		for(int i = 0; i < mylWeapons.Length(); i++)
		{	mylWeapons[i] = 0;
		}
		for(int i = 0; i < mylScriptedItems.Length(); i++)
		{	mylScriptedItems[i] = 0;
		}
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Inventory::SaveRecordingInfo(ofstream &oFile)
{	//<Num Armors>
		oFile << mylArmors.Length() << " ";
	//<Loop through armors>
		for(int i = 0; i < mylArmors.Length(); i++)
		{	oFile << mylArmors[i] << " ";
		}
	//<Num Weapons>
		oFile << mylWeapons.Length() << " ";
	//<Loop through weapons>
		for(int i = 0; i < mylWeapons.Length(); i++)
		{	oFile << mylWeapons[i] << " ";
		}
	//<Num Scripted items>
		oFile << mylScriptedItems.Length() << " ";
	//<Loop Scripted items>
		for(int i = 0; i < mylScriptedItems.Length(); i++)
		{	oFile << mylScriptedItems[i] << " ";
		}	
	//%Gold% %Food% %Torches%
		oFile << myiGold << " " << myiFood << " " << myiTorches << " ";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::LoadRecordingInfo(ifstream &oFile, string sGraphicsDir)
{	//Vars
		int iNumArmors, iNumWeapons, iNumScriptedItems;

	//<Num Armors>
		oFile >> iNumArmors;
		mylArmors.Resize(iNumArmors);
	//<Loop through armors>
		for(int i = 0; i < mylArmors.Length(); i++)
		{	oFile >> mylArmors[i];
		}
	//<Num Weapons>
		oFile >> iNumWeapons;
  		mylWeapons.Resize(iNumWeapons);
	//<Loop through weapons>
		for(int i = 0; i < mylWeapons.Length(); i++)
		{	oFile >> mylWeapons[i];
		}
	//<Num Scripted items>
		oFile >> iNumScriptedItems;
  		mylScriptedItems.Resize(iNumScriptedItems);
	//<Loop Scripted items>
		for(int i = 0; i < mylScriptedItems.Length(); i++)
		{	oFile >> mylScriptedItems[i];
		}	
	//%Gold% %Food% %Torches%
		oFile >> myiGold >> myiFood >> myiTorches;
}
//-------------------------------------------------------------------------------------- [Give and take] -
void LL_Inventory::GiveArmor(int iNum, int iAmount)
{	mylArmors[iNum] += iAmount;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Inventory::TakeArmor(int iNum, int iAmount)
{	if(mylArmors[iNum] - iAmount < 0)
		return false;

	mylArmors[iNum] -= iAmount;
	return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Inventory::Armors(int iNum)
{	return(mylArmors[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::SetArmors(int iNum, int iTo)
{	mylArmors[iNum] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::GiveWeapon(int iNum, int iAmount)
{	mylWeapons[iNum] += iAmount;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Inventory::TakeWeapon(int iNum, int iAmount)
{	if(mylWeapons[iNum] - iAmount < 0)
		return false;

	mylWeapons[iNum] -= iAmount;
	return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Inventory::Weapons(int iNum)
{	return(mylWeapons[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::SetWeapons(int iNum, int iTo)
{	mylWeapons[iNum] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::GiveScriptedItem(int iNum, int iAmount)
{	mylScriptedItems[iNum] += iAmount;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Inventory::TakeScriptedItem(int iNum, int iAmount)
{	if(mylScriptedItems[iNum] - iAmount < 0)
		return false;

	mylScriptedItems[iNum] -= iAmount;
	return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Inventory::ScriptedItems(int iNum)
{	return(mylScriptedItems[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::SetScriptedItems(int iNum, int iTo)
{	mylScriptedItems[iNum] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::GiveGold(int iAmount)
{	myiGold += iAmount;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Inventory::TakeGold(int iAmount)
{	if(myiGold - iAmount < 0)
		return false;

	myiGold -= iAmount;
	return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::GiveFood(int iAmount)
{	myiFood += iAmount;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Inventory::TakeFood(int iAmount)
{	if(myiFood - iAmount < 0)
		return false;

	myiFood -= iAmount;
	return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Inventory::GiveTorches(int iAmount)
{	myiTorches += iAmount;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Inventory::TakeTorches(int iAmount)
{	if(myiTorches - iAmount < 0)
		return false;
		
	myiTorches -= iAmount;
	return true;
}
//------------------------------------------------------------------------------------ [List generation] -
ASFC_LinkedList<string> LL_Inventory::BattleItemInventory(LL_ItemSet* poSet)
{	//Vars
		ASFC_LinkedList<string> ls;
		char strNum[80];
		string s;

	//Header
		ls.Push("Battle inventory:");
		ls.Push("--------------------");
	//Loop through armors
		for(int i = 0; i < mylArmors.Length(); i++)
		{	if(mylArmors[i] > 0)
			{	sprintf(strNum, "%2u", mylArmors[i]);
   				s = strNum;
       			s += " ";
          		s += poSet->Armor(i).Identifier();
				ls.Push(s);
			}
		}
	//Loop through weapons
		for(int i = 0; i < mylWeapons.Length(); i++)
		{	if(mylWeapons[i] > 0)
			{	sprintf(strNum, "%2u", mylWeapons[i]);
				s = strNum;
    			s += " ";
				s += poSet->Weapon(i).Identifier();
				ls.Push(s);
			}
		}
		
	//Return the list
		return(ls);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_LinkedList<string> LL_Inventory::ScriptedItemInventory(LL_ItemSet* poSet)
{	//Vars
		ASFC_LinkedList<string> ls;
		char strNum[80];
		string s;

	//Header
		ls.Push("Inventory:");
		ls.Push("--------------------");
	//Loop scripted items
		for(int i = 0; i < mylScriptedItems.Length(); i++)
		{	if(mylScriptedItems[i] > 0)
			{	sprintf(strNum, "%2u", mylScriptedItems[i]);
   				s = strNum;
       			s += " ";
          		s += poSet->ScriptedItem(i).Identifier();
				ls.Push(s);
			}
		}
		
	//Return the list
		return(ls);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Return the numeric identifier of the ith item in the scripted item inventory
int LL_Inventory::ScriptedItemNum(int iNum)
{	//Vars
		ASFC_LinkedList<string> ls;
		int iCurrent = -1;
		
	//Loop scripted items
		for(int i = 0; i < mylScriptedItems.Length(); i++)
		{	if(mylScriptedItems[i] > 0)
			{	iCurrent += 1;
			}
			
			if(iCurrent == iNum)
			{	return(i);
			}
		}
		
	//Default to -1
		return(-1);
}
//----------------------------------------------------------------------------------- [List information] -
int LL_Inventory::NumTypesArmors()
{	return(mylArmors.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Inventory::NumTypesWeapons()
{	return(mylWeapons.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Inventory::NumTypesScriptedItems()
{	return(mylScriptedItems.Length());
}
