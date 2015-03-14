/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			armoreditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "armoreditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_ArmorEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ArmorEditor::LEDIT_ArmorEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_ArmorEditor::EditArmor(LL_Armor* poArmor)
{	//Set the armor to edit
		mypoArmor = poArmor;

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
void LEDIT_ArmorEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Armor Information");
		Heading("===================================================");
	//Stats
		Option("Image: " + mypoArmor->ImageFile());
		if(mypoArmor->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image");
		Option("Description: " + mypoArmor->Identifier());
		Option("Weight: " + Val(mypoArmor->Weight()));
  		Option("Defense: " + Val(mypoArmor->Defense()));
		
		if(mypoArmor->EquipsHands() == 0)
  			Option("Don't Equip Hands");
		else if(mypoArmor->EquipsHands() == 1)
			Option("Equip 1 Hands");
		else
			Option("Equip both Hands");
			
		if(mypoArmor->EquipsArms())
  			Option("Equip Arms");
		else
			Option("Don't Equip Arms");
			
		if(mypoArmor->EquipsTorso())
  			Option("Equip Torso");
		else
			Option("Don't Equip Torso");
			
		if(mypoArmor->EquipsHead()) 
			Option("Equip Head");    
		else                         
			Option("Don't Equip Head");
} 
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_ArmorEditor::EditOption(int i)
{	//Decide what to edit based on what was chosen
		switch(i)
		{	case OPTION_IMAGE:
			{	string s;
				if(mypoArmor->CustomImage())
					s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
				else
					s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
				mypoArmor->LoadAnimation(s, mypoGame->GraphicsDir());
		 		return(true);
			}break;
			
			case OPTION_CUSTOM_IMAGE:
			{	string s;
				s = mypoArmor->ImageFile();
				mypoArmor->SetCustomImage(!mypoArmor->CustomImage());
				if(!mypoArmor->AnimationExists(mypoGame->GraphicsDir()))
				{	if(mypoArmor->CustomImage())
						s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
					else
						s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
				}
				mypoArmor->LoadAnimation(s, mypoGame->GraphicsDir());

				return(true);
			}break;
			
			case OPTION_EDIT_IMAGE:
			{	// !!! <CODE>
				return(true);
			}break;
			
  			case OPTION_DESCRIPTION:
			{	string s = GrabString("Enter the new description");
				mypoArmor->SetIdentifier(s);
		 		return(true);
			}break;
			
			case OPTION_WEIGHT:
			{	int i = GrabInt("Enter the new weight value [0-255]", 0, 255);
				mypoArmor->SetWeight(i);
		 		return(true);
			}break;
			
			case OPTION_DEFENSE:
			{	int i = GrabInt("Enter the new defense value [0-255]", 0, 255);
				mypoArmor->SetDefense(i);
		 		return(true);
			}break;
			
			case OPTION_EQUIP_HANDS:
			{	mypoArmor->SetEquipsHands(mypoArmor->EquipsHands() + 1);
				if(mypoArmor->EquipsHands() > 2)
					mypoArmor->SetEquipsHands(0);
		 		return(true);
			}break;
			
			case OPTION_EQUIP_ARMS:
			{	mypoArmor->SetEquipsArms(!mypoArmor->EquipsArms());
				return(true);
			}break;
			
			case OPTION_EQUIP_TORSO:
			{	mypoArmor->SetEquipsTorso(!mypoArmor->EquipsTorso());
				return(true);
			}break;
			
			case OPTION_EQUIP_HEAD:
			{	mypoArmor->SetEquipsHead(!mypoArmor->EquipsHead());
				return(true);
			}break;
			
			default: break;
		}

	return(false);
}
