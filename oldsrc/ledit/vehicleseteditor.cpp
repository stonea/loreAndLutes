/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "vehicleseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_VehicleSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_VehicleSetEditor::LEDIT_VehicleSetEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_VehicleSetEditor::EditVehicleSet()
{	//Setup the editor
		DrawInit();
		Setup(true);

	//Now grab an option
		while(EditOption(GrabOption()))
		{	Setup(true);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LEDIT_VehicleSetEditor::GrabVehicle()
{	//Setup the editor
cerr << "A\n";
		DrawInit();
cerr << "B\n";
		Setup(false);
cerr << "C\n";
	//Now grab an option
		return GrabOption();
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_VehicleSetEditor::Setup(bool fNewVehicleOption)
{	//Clear the old editor
		Reset(false);
		
	//Draw info
		Heading("                 Vehicle Set");
		Heading("===================================================");

	//List the vehicles
		for(int i = 0; i < mypoSet->NumVehicles(); i++)
			Option("<" + Val(mypoSet->Vehicle(i).Code()) + "> " + mypoSet->Vehicle(i).Identifier());
			
	//And display the "new vehicle" option
		if(fNewVehicleOption)
			Option("-- [New Vehicle] --");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_VehicleSetEditor::EditOption(int i)
{	//Edit this vehicle (if its a vehicle)
		if(i >= 0 && i < mypoSet->NumVehicles())
		{	string ts = GrabString("Enter what you want to change this vehicle's name to");
			mypoSet->Vehicle(i).SetIdentifier(ts);
			
			return(true);
		}
	//If we should create a new vehicle
		if(i == mypoSet->NumVehicles())
		{	LL_Vehicle tVehicle;
		
  			string ts = GrabString("Enter what you want the new vehicle name to be:");
			tVehicle.SetIdentifier(ts);
			tVehicle.SetCode(i);
			
			mypoSet->AddVehicle(tVehicle);
			
			return(true);
		}
	
	return(false);
}
