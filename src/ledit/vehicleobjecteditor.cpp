/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleobjecteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "vehicleobjecteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LEDIT_VehicleObjectEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_VehicleObjectEditor::LEDIT_VehicleObjectEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_VehicleObjectEditor::EditVehicleObject(LL_VehicleObject* poVehicleObject)
{	//Set the vehicle object to edit
		mypoVehicleObject = poVehicleObject;

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
void LEDIT_VehicleObjectEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("            Vehicle Object Information");
		Heading("===================================================");
	//Stats
		Option("Identifier: " + mypoVehicleObject->Identifier());
		Option("Image: " + mypoVehicleObject->ImageFile());
		if(mypoVehicleObject->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image");
		Option("Vehicle: " + mypoGame->VehicleSet().Vehicle(mypoVehicleObject->VehicleCode()).Identifier());
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_VehicleObjectEditor::EditOption(int i)
{	//Vars
		string ts;
		int ti;

	//Decide what to edit based on what was chosen
		switch(i)
		{	//- [Identifier] -
			case OPTION_IDENTIFIER:
				ts = GrabString("Enter the new identifier:");
				mypoVehicleObject->SetIdentifier(ts);
				return true;
			break;

			//- [Image] -
			case OPTION_IMAGE:
				if(mypoVehicleObject->CustomImage())
					ts = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
				else
					ts = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
				mypoVehicleObject->LoadAnimation(ts, mypoGame->GraphicsDir());
				return true;
			break;

			//- [Custom\Default Image] -
			case OPTION_CUSTOM_IMAGE:
				ts = mypoVehicleObject->ImageFile();
				mypoVehicleObject->SetCustomImage(!mypoVehicleObject->CustomImage());
				if(!mypoVehicleObject->AnimationExists(mypoGame->GraphicsDir()))
				{	if(mypoVehicleObject->CustomImage())
						ts = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
					else
						ts = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
				}
				mypoVehicleObject->LoadAnimation(ts, mypoGame->GraphicsDir());
				return true;
			break;

			//- [Edit Image] -
			case OPTION_EDIT_IMAGE:
				return true;
			break;
			
			//- [Vehicle] -
			case OPTION_VEHICLE:
				ti = mypoVehicleObject->VehicleCode();
				ti++;
				if(ti >= mypoGame->VehicleSet().NumVehicles())
					ti = 0;
	
				mypoVehicleObject->SetVehicleCode(ti);
				return true;
			break;

			default: break;
		}

	return(false);
}
