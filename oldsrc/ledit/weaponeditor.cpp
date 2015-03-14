/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			weaponeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "weaponeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_WeaponEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_WeaponEditor::LEDIT_WeaponEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_WeaponEditor::EditWeapon(LL_Weapon* poWeapon)
{	//Set the Weapon to edit
		mypoWeapon = poWeapon;

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
void LEDIT_WeaponEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Weapon Informattion");
		Heading("===================================================");
	//Stats
		Option("Image: " + mypoWeapon->ImageFile());
		if(mypoWeapon->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image");
		Option("Description: " + mypoWeapon->Identifier());
		Option("Weight: " + Val(mypoWeapon->Weight()));
  		Option("Attack: " + Val(mypoWeapon->AttackSkill()));
  		Option("Radius: " + Val(mypoWeapon->Radius()));
		
		if(mypoWeapon->EquipsHands() == 0)
  			Option("Don't Equip Hands");
		else if(mypoWeapon->EquipsHands() == 1)
			Option("Equip 1 Hands");
		else if(mypoWeapon->EquipsHands() == 2)
			Option("Equip both Hands");
		else
			Option("ERR: Num of hands invalid!");
			
		if(mypoWeapon->EquipsArms())
  			Option("Equip Arms");
		else
			Option("Don't Equip Arms");
			
		if(mypoWeapon->EquipsTorso())
  			Option("Equip Torso");
		else
			Option("Don't Equip Torso");
			
		if(mypoWeapon->EquipsHead())
  			Option("Equip Head");
		else
			Option("Don't Equip Head");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_WeaponEditor::EditOption(int i)
{	//Decide what to edit based on what was chosen
		switch(i)
		{	case OPTION_IMAGE:
			{	string s;
				if(mypoWeapon->CustomImage())
					s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
				else
					s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
				mypoWeapon->LoadAnimation(s, mypoGame->GraphicsDir());
		 		return(true);
			}break;
			
			case OPTION_CUSTOM_IMAGE:
			{	string s;
				s = mypoWeapon->ImageFile();
				mypoWeapon->SetCustomImage(!mypoWeapon->CustomImage());
				if(!mypoWeapon->AnimationExists(mypoGame->GraphicsDir()))
				{	if(mypoWeapon->CustomImage())
						s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
					else
						s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
				}
				mypoWeapon->LoadAnimation(s, mypoGame->GraphicsDir());

				return true;
			}

			case OPTION_EDIT_IMAGE:
			{	// !!! <CODE>
				return(true);
			}break;
			
  			case OPTION_DESCRIPTION:
			{	string s = GrabString("Enter the new description");
				mypoWeapon->SetIdentifier(s);
		 		return(true);
			}break;
			
			case OPTION_WEIGHT:
			{	int i = GrabInt("Enter the new weight value [0-255]", 0, 255);
				mypoWeapon->SetWeight(i);
		 		return(true);
			}break;
			
			case OPTION_ATTACK:
			{	int i = GrabInt("Enter the new attack value [0-255]", 0, 255);
				mypoWeapon->SetAttackSkill(i);
		 		return(true);
			}break;
			
			case OPTION_RADIUS:
			{	int i = GrabInt("Enter the new attack radius [1-11]", 0, 255);
				mypoWeapon->SetRadius(i);
		 		return(true);
			}break;
			
			case OPTION_EQUIP_HANDS:
			{	if(mypoWeapon->EquipsHands() == 0)
		  			mypoWeapon->SetEquipsHands(1);
				else if(mypoWeapon->EquipsHands() == 1)
					mypoWeapon->SetEquipsHands(2);
				else
					mypoWeapon->SetEquipsHands(0);
				return(true);
			}break;

			case OPTION_EQUIP_ARMS:
			{	mypoWeapon->SetEquipsArms(!mypoWeapon->EquipsArms());
				return(true);
			}break;
			
			case OPTION_EQUIP_TORSO:
			{	mypoWeapon->SetEquipsTorso(!mypoWeapon->EquipsTorso());
				return(true);
			}break;
			
			case OPTION_EQUIP_HEAD:
			{	mypoWeapon->SetEquipsHead(!mypoWeapon->EquipsHead());
				return(true);
			}break;
			
			default: break;
		}

	return(false);
}
