/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			itemset.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "itemset.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LL_ItemSet
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//--------------------------------------------------------------------------------------- [Construction] -
LL_ItemSet::LL_ItemSet()
{	myoDefaultArmor.SetIdentifier("Nothing");
	myoDefaultArmor.SetWeight(0);
	myoDefaultWeapon.SetIdentifier("Hands");
	myoDefaultWeapon.SetWeight(0);
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_ItemSet::Save(ofstream &oFile)
{	//~.items 0~				File type and version number
		oFile << ".items 0" << endl;
	//%Number Of Armors%
		oFile << NumArmors() << endl;
	//<Loop for the # of armors>
		for(int i = 0; i < NumArmors(); i++)
		{	//<Save Armor>
				Armor(i).Save(oFile);
		}
		oFile << endl << endl;
	//%Number Of Weapons%
		oFile << NumWeapons() << endl;
	//<Loop for the # of weaopns>
		for(int i = 0; i < NumWeapons(); i++)
		{	//<Save Weapons>
				Weapon(i).Save(oFile);
		}
		oFile << endl << endl;
	//%Number Of Scripted Items%
		oFile << NumScriptedItems() << endl;
	//<Loop for the # of weaopns>
		for(int i = 0; i < NumScriptedItems(); i++)
		{	//<Scripted item>
				ScriptedItem(i).Save(oFile);
		}
		oFile << endl << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ItemSet::Load(ifstream &oFile, string sGraphicsPath)
{	//Vars
		string sFileType;
		int iVersionNum;
		int iNumArmors, iNumWeapons, iNumScriptedItems;

	//~.items 0~				File type and version number
		oFile >> sFileType;
		oFile >> iVersionNum;
		
	//%Number Of Armors%
		oFile >> iNumArmors;
		myloArmors.Resize(iNumArmors);
	//<Loop for the # of armors>
		for(int i = 0; i < iNumArmors; i++)
		{	//<Load Armor>
				Armor(i).Load(oFile, sGraphicsPath);
		}
		
	//%Number Of Weapons%
		oFile >> iNumWeapons;
		myloWeapons.Resize(iNumWeapons);
	//<Loop for the # of weaopns>
		for(int i = 0; i < NumWeapons(); i++)
		{	//<Save Weapons>
				Weapon(i).Load(oFile, sGraphicsPath);
		}
		
	//%Number Of Scripted Items%
		oFile >> iNumScriptedItems;
		myloScriptedItems.Resize(iNumScriptedItems);
	//<Loop for the # of weaopns>
		for(int i = 0; i < iNumScriptedItems; i++)
		{	//<Scripted item>
				ScriptedItem(i).Load(oFile, sGraphicsPath);
		}
}
//------------------------------------------------------------------------------------ [Armor Handeling] -
void LL_ItemSet::AddArmor(LL_Armor &oAdd)
{	myloArmors.Resize(myloArmors.Length() + 1);
	myloArmors[myloArmors.Length() - 1] = oAdd;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Armor& LL_ItemSet::Armor(int iIndex)
{	if(iIndex < 0)
		return myoDefaultArmor;
	return(myloArmors[iIndex]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_ItemSet::NumArmors()
{	return(myloArmors.Length());
}
//----------------------------------------------------------------------------------- [Weapon Handeling] -
void LL_ItemSet::AddWeapon(LL_Weapon &oAdd)
{	myloWeapons.Resize(myloWeapons.Length() + 1);
	myloWeapons[myloWeapons.Length() - 1] = oAdd;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Weapon& LL_ItemSet::Weapon(int iIndex)
{	if(iIndex < 0)
		return myoDefaultWeapon;
	return(myloWeapons[iIndex]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_ItemSet::NumWeapons()
{	return(myloWeapons.Length());
}
//----------------------------------------------------------------------------- [ScriptedItem Handeling] -
void LL_ItemSet::AddScriptedItem(LL_ScriptedItem &oAdd)
{		myloScriptedItems.Resize(myloScriptedItems.Length() + 1);
	myloScriptedItems[myloScriptedItems.Length() - 1] = oAdd;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_ScriptedItem& LL_ItemSet::ScriptedItem(int iIndex)
{	return(myloScriptedItems[iIndex]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_ItemSet::NumScriptedItems()
{	return(myloScriptedItems.Length());
}
