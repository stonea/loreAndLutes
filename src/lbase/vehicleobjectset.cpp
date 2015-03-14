/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleobjectset.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "vehicleobjectset.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_VehicleObjectSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_VehicleObjectSet::LL_VehicleObjectSet()
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_VehicleObjectSet::Save(ofstream &oFile)
{	//".vehicleobjset 0"
		oFile << ".vehicleobjSet 0 ";
	//%# of vehicles%
		oFile << myloVehicles.Length() << " ";
	//<Loop through every vehicle object>
		for(int i = 0; i < myloVehicles.Length(); i++)
		{	myloVehicles[i].Save(oFile);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_VehicleObjectSet::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		string sVer;
		int iVer;
		int iNumVehicles;

	//".vehicleobjset 0"
		oFile >> sVer >> iVer;
	//%# of vehicles%
		oFile >> iNumVehicles;
		myloVehicles.Resize(iNumVehicles);
	//<Loop through every vehicle object>
		for(int i = 0; i < myloVehicles.Length(); i++)
		{	myloVehicles[i].Load(oFile, sGraphicsDir);
		}
}
//------------------------------------------------------------------------------------------ [Handeling] -
void LL_VehicleObjectSet::AddVehicleObject(LL_VehicleObject oAdd)
{	myloVehicles.Push(oAdd);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_VehicleObjectSet::AddDefaultVehicleObject()
{	//Resize to add a new one
		myloVehicles.Resize(myloVehicles.Length() + 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_VehicleObject& LL_VehicleObjectSet::VehicleObject(int iIndex)
{	return myloVehicles[iIndex];
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_VehicleObjectSet::NumVehicleObject()
{	return(myloVehicles.Length());
}
