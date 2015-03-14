/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			itemseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "itemseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_ItemSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ItemSetEditor::LEDIT_ItemSetEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_ItemSetEditor::EditItemSet(LL_ItemSet* poSet)
{	//Map vars
		mypoSet = poSet;

	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup(true);

	//Now grab an option
		while(EditOption(GrabOption()))
		{	Setup(true);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LEDIT_ItemSetEditor::GetItemType()
{	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup(false);

	//Now grab an option
		return(GrabOption());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LEDIT_ItemSetEditor::GetArmor(LL_ItemSet* poSet)
{	//Setup the editor
		mypoSet = poSet;
		DrawInit();
		DrawQuickKeys();
		SetupArmors(false);

	//Now grab an option
		return(GrabOption());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LEDIT_ItemSetEditor::GetWeapon(LL_ItemSet* poSet)
{	//Setup the editor
		mypoSet = poSet;
		DrawInit();
		DrawQuickKeys();
		SetupWeapons(false);

	//Now grab an option
		return(GrabOption());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LEDIT_ItemSetEditor::GetScriptedItem(LL_ItemSet* poSet)
{	//Setup the editor
		mypoSet = poSet;
		DrawInit();
		DrawQuickKeys();
		SetupScriptedItems(false);

	//Now grab an option
		return(GrabOption());
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_ItemSetEditor::Setup(bool fEditing)
{	//Clear the old editor
		Reset(false);
		
	//If we're editting
		if(fEditing)
		{	//Draw info
				Heading("                 Items Set");
				Heading("===================================================");
	
			//Display options
				Option("Edit armors");
				Option("Edit weapons");
				Option("Edit scripted items");
		}
	//If we're grabbing
		else
		{	//Draw info
				Heading("                 Place Items");
				Heading("===================================================");
	
			//Display options
				Option("Place armor");
				Option("Place weapon");
				Option("Place scripted item");
				Option("Place Chest");
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_ItemSetEditor::EditOption(int i)
{	switch(i)
	{	case EDITOPTION_ARMORS: 	EditArmors();			return true; break;
		case EDITOPTION_WEAPONS:	EditWeapons();			return true; break;
		case EDITOPTION_SCRIPTS:	EditScriptedItems();	return true; break;
		default: break;
	}

	return false;
}
//P----------------------------------------------------------------------------------- [Armors editting] -P
void LEDIT_ItemSetEditor::EditArmors()
{	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		SetupArmors(true);

	//Now grab an option
		while(EditArmorOption(GrabOption()))
		{	SetupArmors(true);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ItemSetEditor::SetupArmors(bool fEditing)
{	//Clear the old editor
		Reset(false);
		
	//If we're editting
		if(fEditing)
		{	//Draw info
				Heading("                 Armors Set");
				Heading("===================================================");

			//Draw los armors
				for(int i = 0; i < mypoSet->NumArmors(); i++)
				{	Option(Val(i) + ": " + mypoSet->Armor(i).Identifier());
				}

			//Draw last option
				Option("-- [New armor] --");
		}
	//If we be'sa pickin'
		else
		{	//Draw info
				Heading("                 Armors Set");
				Heading("===================================================");

			//Draw los armors
				for(int i = 0; i < mypoSet->NumArmors(); i++)
				{	Option(Val(i) + ": " + mypoSet->Armor(i).Identifier());
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_ItemSetEditor::EditArmorOption(int i)
{	//If the user wants to edit an armor let him do it
		if(i >= 0 && i < NumOptions() - 1)
		{	mypoArmorEditor->EditArmor(&mypoSet->Armor(i));
			return true;
		}

	//If the user just yearns to create a new armor
		if(i == NumOptions() - 1)
		{	NewArmor();
			return true;
		}
		
	//Return false, yeah, yeah, by de-false, we all know the stupid joke...
		return false;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ItemSetEditor::NewArmor()
{	//Vars
		string sName;
		string sImageFile;
		LL_Armor toArmor;
	
	//Clear the console
		mypoPainter->MainConsole().Clear();
	//Draw the header
		mypoPainter->MainConsole().CurrentFont(FONT_HEADING);
		mypoPainter->MainConsole() << "                     New Armor\n";
		mypoPainter->MainConsole() << "===================================================\n";
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "Answer the following question then choose a graphic\n";
  		mypoPainter->MainConsole() << "in order to create a template for this new armor:\n\n";
		
	//Ask for a armor name
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "\n";
		mypoPainter->MainConsole() << "What would you like the armor name (identifier) to be?\n";
		mypoPainter->MainConsole().CurrentFont(FONT_HIGHLIGHT);
		mypoPainter->MainConsole() >> sName;
		
	//Grab a graphic
		sImageFile = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
		toArmor.LoadAnimation(sImageFile, mypoGame->GraphicsDir());
	//Now create this armor!
		toArmor.SetIdentifier(sName);
 		mypoSet->AddArmor(toArmor);
}
//P---------------------------------------------------------------------------------- [Weapons editting] -P
void LEDIT_ItemSetEditor::EditWeapons()
{	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		SetupWeapons(true);

	//Now grab an option
		while(EditWeaponOption(GrabOption()))
		{	SetupWeapons(true);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ItemSetEditor::SetupWeapons(bool fEditing)
{	//Clear the old editor
		Reset(false);
		
	//If we're editting
		if(fEditing)
		{	//Draw info
				Heading("                 Weapons Set");
				Heading("===================================================");
			//Draw weapons
				for(int i = 0; i < mypoSet->NumWeapons(); i++)
				{	Option(Val(i) + ": " + mypoSet->Weapon(i).Identifier());
				}		
			//Draw last option
				Option("-- [New weapon] --");
		}
	//If we're picking
		else
		{	//Draw info
				Heading("                 Weapons Set");
				Heading("===================================================");
			//Draw weapons
				for(int i = 0; i < mypoSet->NumWeapons(); i++)
				{	Option(Val(i) + ": " + mypoSet->Weapon(i).Identifier());
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_ItemSetEditor::EditWeaponOption(int i)
{	//If the user wants to edit a weapon let him do it
		if(i >= 0 && i < NumOptions() - 1)
		{	mypoWeaponEditor->EditWeapon(&mypoSet->Weapon(i));
			return true;
		}

	//If the user just yearns to create a new weapon
		if(i == NumOptions() - 1)
		{	NewWeapon();
			return true;
		}
		
	//Return false, yeah, yeah, by de-false, we all know the stupid joke...
		return false;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ItemSetEditor::NewWeapon()
{	//Vars
		string sName;
		string sImageFile;
		LL_Weapon toWeapon;
	
	//Clear the console
		mypoPainter->MainConsole().Clear();
	//Draw the header
		mypoPainter->MainConsole().CurrentFont(FONT_HEADING);
		mypoPainter->MainConsole() << "                     New Weapon\n";
		mypoPainter->MainConsole() << "===================================================\n";
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "Answer the following question then choose a graphic\n";
  		mypoPainter->MainConsole() << "in order to create a template for this new weapon:\n\n";
		
	//Ask for a weapon name
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "\n";
		mypoPainter->MainConsole() << "What would you like the weapon name (identifier) to be?\n";
		mypoPainter->MainConsole().CurrentFont(FONT_HIGHLIGHT);
		mypoPainter->MainConsole() >> sName;
		
	//Grab a graphic
		sImageFile = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
		toWeapon.LoadAnimation(sImageFile, mypoGame->GraphicsDir());
		
	//Now create this weapon!
		toWeapon.SetIdentifier(sName);
 		mypoSet->AddWeapon(toWeapon);
}
//P---------------------------------------------------------------------------------- [ScriptedItem set] -P
void LEDIT_ItemSetEditor::EditScriptedItems()
{	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		SetupScriptedItems(true);

	//Now grab an option
		while(EditScriptedItemOption(GrabOption()))
		{	SetupScriptedItems(true);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ItemSetEditor::SetupScriptedItems(bool fEditing)
{	//Clear the old editor
		Reset(false);
		
	//If we're editing
		if(fEditing)
		{	//Draw info
				Heading("                 Scripted Items Set");
				Heading("===================================================");
			//Draw scripteditems
				for(int i = 0; i < mypoSet->NumScriptedItems(); i++)
				{	Option(Val(i) + ": " + mypoSet->ScriptedItem(i).Identifier());
				}
			//Draw last option
				Option("-- [New scripted item] --");
		}
	//If we're picking
		else
		{	//Draw info
				Heading("                 Scripted Items Set");
				Heading("===================================================");
			//Draw scripteditems
				for(int i = 0; i < mypoSet->NumScriptedItems(); i++)
				{	Option(Val(i) + ": " + mypoSet->ScriptedItem(i).Identifier());
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_ItemSetEditor::EditScriptedItemOption(int i)
{	//If the user wants to edit a scripted item let him do it
		if(i >= 0 && i < NumOptions() - 1)
		{	mypoScriptedItemEditor->EditScriptedItem(&mypoSet->ScriptedItem(i));
			return true;
		}

	//If the user just yearns to create a new scripted item
		if(i == NumOptions() - 1)
		{	NewScriptedItem();
			return true;
		}
		
	//Return false, yeah, yeah, by de-false, we all know the stupid joke...
		return false;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ItemSetEditor::NewScriptedItem()
{	//Vars
		string sName;
		string sImageFile;
		LL_ScriptedItem toScriptedItem;
	
	//Clear the console
		mypoPainter->MainConsole().Clear();
	//Draw the header
		mypoPainter->MainConsole().CurrentFont(FONT_HEADING);
		mypoPainter->MainConsole() << "                  New Scripted Item\n";
		mypoPainter->MainConsole() << "===================================================\n";
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "Answer the following question then choose a graphic\n";
  		mypoPainter->MainConsole() << "in order to create a template for this new scripted\n";
  		mypoPainter->MainConsole() << "item:\n";
		
	//Ask for a scripted item name
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "\n";
		mypoPainter->MainConsole() << "What would you like the scripted item name\n";
		mypoPainter->MainConsole() << "(identifier) to be?\n";
		mypoPainter->MainConsole().CurrentFont(FONT_HIGHLIGHT);
		mypoPainter->MainConsole() >> sName;
		
	//Grab a graphic
		sImageFile = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
		toScriptedItem.LoadAnimation(sImageFile, mypoGame->GraphicsDir());
		
	//Now create this ScriptedItem!
		toScriptedItem.SetIdentifier(sName);
 		mypoSet->AddScriptedItem(toScriptedItem);
}
