/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			chesteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "chesteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LEDIT_ChestEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ChestEditor::LEDIT_ChestEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_ChestEditor::EditChest(LL_Chest* poChest)
{	//Set the Chest to edit
		mypoChest = poChest;

	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup();

	//Now grab an option
		while(EditOption(GrabOption()))
		{	Setup();
		}
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_ChestEditor::Setup()
{	//Vars
		string ts;
	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Chest Editor");
		Heading("===================================================");
	//Stats\Add
		Heading("-------------------------------------------[Image]-");
		Option("Image: " + mypoChest->ImageFile());
		if(mypoChest->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image");
		Heading("-------------------------------------------[Misc.]-");
		Option("Disappears: " + YesNo(mypoChest->Disappears()));
		Heading("---------------------------------------------[Add]-");
		Option("Add Weapon");
		Option("Add Armor");
		Option("Add Scripted Item");
		Option("Add Gold");
		Option("Add Food");
		Option("Add Torches");
	//All the added items
		Heading("-------------------------------------------[Items]-");
		//Loop through each item, display it as an option
			for(int i = 0; i < mypoChest->NumItems(); i++)
			{	//Decide what to write based on what type of item this is
					switch(mypoChest->Item(i).iType)
     				{	case LL_Chest::TYPE_ARMOR:
     					{	ts  = Val(mypoChest->Item(i).iAmount);
     						ts += " <";
     						ts += Val(int(mypoChest->Item(i).iChance * 100));
     						ts += "%> ";
     						ts += Game()->ItemSet().Armor(mypoChest->Item(i).iItemOff).Identifier();
     						Option(ts);
     					}break;
     					
     					case LL_Chest::TYPE_WEAPON:
     					{	ts  = Val(mypoChest->Item(i).iAmount);
     						ts += " <";
     						ts += Val(int(mypoChest->Item(i).iChance * 100));
     						ts += "%> ";
     						ts += Game()->ItemSet().Weapon(mypoChest->Item(i).iItemOff).Identifier();
     						Option(ts);
     					}break;
     					
     					case LL_Chest::TYPE_SCRIPTED_ITEM:
     					{	ts  = Val(mypoChest->Item(i).iAmount);
     						ts += " <";
     						ts += Val(int(mypoChest->Item(i).iChance * 100));
     						ts += "%> ";
     						ts += Game()->ItemSet().ScriptedItem(mypoChest->Item(i).iItemOff).Identifier();
     						Option(ts);
     					}break;
     					
     					case LL_Chest::TYPE_GOLD:
     					{	ts = Val(mypoChest->Item(i).iAmount);
     						ts += " <";
     						ts += Val(int(mypoChest->Item(i).iChance * 100));
     						ts += "%> ";
     						ts += " Gold";
     						Option(ts);
     					}break;
     					
     					case LL_Chest::TYPE_FOOD:
     					{	ts = Val(mypoChest->Item(i).iAmount);
     						ts += " <";
     						ts += Val(int(mypoChest->Item(i).iChance * 100));
     						ts += "%> Food";
     						Option(ts);
     					}break;
     					
     					case LL_Chest::TYPE_TORCHES:
     					{	ts = Val(mypoChest->Item(i).iAmount);
     						ts += " <";
     						ts += Val(int(mypoChest->Item(i).iChance * 100));
     						ts += "%> Torches";
     						Option(ts);
     					}
         			}
			}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_ChestEditor::EditOption(int i)
{	//Decide what to edit based on what was chosen
		switch(i)
		{	case OPTION_IMAGE:
			{	string s;
				if(mypoChest->CustomImage())
					s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
				else
					s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
				mypoChest->LoadAnimation(s, mypoGame->GraphicsDir());
		 		return(true);
			}break;
			
			case OPTION_CUSTOM_IMAGE:
			{	string s;
				s = mypoChest->ImageFile();
				mypoChest->SetCustomImage(!mypoChest->CustomImage());
				if(!mypoChest->AnimationExists(mypoGame->GraphicsDir()))
				{	if(mypoChest->CustomImage())
						s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
					else
						s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
				}
				mypoChest->LoadAnimation(s, mypoGame->GraphicsDir());
				return true;
			}

			case OPTION_EDIT_IMAGE:
			{	
			}break;

			case OPTION_DISAPPEARS:
			{	//Switch it
					mypoChest->SetDisappears(!mypoChest->Disappears());
				return(true);
			}break;
			
			case OPTION_ADD_WEAPON:
			{	//Grab a weapon
					int    iWeapon = mypoItemSetEditor->GetWeapon(&Game()->ItemSet());
					int    iAmount = GrabInt("How many? [0-1000]", 0, 1000);
					double dChance = double(GrabInt("Chance of exitance? [0-100]", 0, 100)) / 100;
					mypoChest->AddWeapon(iWeapon, iAmount);
					mypoChest->Item(mypoChest->NumItems()-1).iChance = dChance;
				return(true);
			}break;
			
			case OPTION_ADD_ARMOR:
			{	//Grab an armor
					int iArmor = mypoItemSetEditor->GetArmor(&Game()->ItemSet());
     				int iAmount = GrabInt("How many? [0-1000]", 0, 1000);
     				double dChance = double(GrabInt("Chance of exitance? [0-100]", 0, 100)) / 100;
					mypoChest->AddArmor(iArmor, iAmount);
					mypoChest->Item(mypoChest->NumItems()-1).iChance = dChance;
				return(true);
			}break;
			
			case OPTION_ADD_SCRIPTED_ITEM:
			{	//Grab a scriptedItem
					int iItem = mypoItemSetEditor->GetScriptedItem(&Game()->ItemSet());
         			int iAmount = GrabInt("How many? [0-1000]", 0, 1000);
         			double dChance = double(GrabInt("Chance of exitance? [0-100]", 0, 100)) / 100;
					mypoChest->AddScriptedItem(iItem, iAmount);
					mypoChest->Item(mypoChest->NumItems()-1).iChance = dChance;
				return(true);
			}break;
			
			case OPTION_ADD_SCRIPTED_GOLD:
			{	//Ask how much
					int iAmount = GrabInt("How much gold? [0-1000]", 0, 1000);
					double dChance = double(GrabInt("Chance of exitance? [0-100]", 0, 100)) / 100;
					mypoChest->AddGold(iAmount);
					mypoChest->Item(mypoChest->NumItems()-1).iChance = dChance;
				return(true);
			}break;
			
			case OPTION_ADD_SCRIPTED_FOOD:
			{	//Ask how much
					int iAmount = GrabInt("How much food? [0-1000]", 0, 1000);
					double dChance = double(GrabInt("Chance of exitance? [0-100]", 0, 100)) / 100;
					mypoChest->AddFood(iAmount);
					mypoChest->Item(mypoChest->NumItems()-1).iChance = dChance;
				return(true);
			}break;
			
			case OPTION_ADD_SCRIPTED_TORCHES:
			{	//Ask how much
					int iAmount = GrabInt("How many torches? [0-1000]", 0, 1000);
					double dChance = double(GrabInt("Chance of exitance? [0-100]", 0, 100)) / 100;
					mypoChest->AddTorches(iAmount);
					mypoChest->Item(mypoChest->NumItems()-1).iChance = dChance;
				return(true);
			}break;
			
			default: break;
		}
	//If an item was selected redetermine the amount and chance
		if(i >= OPTION_NUM_OPTIONS)
		{	int iItem = i - OPTION_NUM_OPTIONS;
			int iAmount = GrabInt("Change amount to? [0-1000]", 0, 1000);
			double iChance = double(GrabInt("Change chance to? [0-100]", 0, 100)) / 100;
			mypoChest->Item(iItem).iAmount = iAmount;
			mypoChest->Item(iItem).iChance = iChance;
			return(true);
		}
		
	return(false);
}
