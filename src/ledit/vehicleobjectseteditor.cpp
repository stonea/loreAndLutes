/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleobjectseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "vehicleobjectseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LEDIT_VehicleObjectSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_VehicleObjectSetEditor::LEDIT_VehicleObjectSetEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_VehicleObjectSetEditor::EditVehicleObjectSet(LL_VehicleObjectSet* poVehicleObjectSet)
{	//Set the vehicle object to edit
		mypoVehicleObjectSet = poVehicleObjectSet;

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
void LEDIT_VehicleObjectSetEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("            Vehicle Object Information");
		Heading("===================================================");
	//Loop through all vehicle object's
		for(int i = 0; i < mypoVehicleObjectSet->NumVehicleObject(); i++)
		{	Option(mypoVehicleObjectSet->VehicleObject(i).Identifier());
		}
	//New vehicle option
		Option("-- [New Vehicle Object] --");
} 
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_VehicleObjectSetEditor::EditOption(int i)
{	//Decide what to edit based on what was chosen
		//If a vehicle object was chosen edit that
			if(i < mypoVehicleObjectSet->NumVehicleObject() && i >= 0)
			{	mypoVehicleObjectEditor->EditVehicleObject(&mypoVehicleObjectSet->VehicleObject(i));
				return(true);
			}
		//If we selected the new vehicle object create a new vehicle
			else if(i >= 0)
			{	//Create a new vehicle object
					mypoVehicleObjectSet->AddDefaultVehicleObject();
					return(true);
			}

	return(false);
}
