/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleobject.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "vehicleobject.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_VehicleObject
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_VehicleObject::LL_VehicleObject()
{	SetIdentifier("New vehicle object");
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_VehicleObject::Save(ofstream &oFile)
{	//"Image file path"  %Custom image%
 		oFile << Qoute(ImageFile()) << " ";	
		oFile << myfCustomImage << " ";
	//"Description"
		oFile << Qoute(Identifier()) << " ";
	//%Vehicle code%
		oFile << myiVehicleCode << " ";
	//<endl>
		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_VehicleObject::Load(ifstream &oFile, string sGraphicsPath)
{	//Vars
		string sImageFile, sDescription;

	//"Image file path" %Custom image%
 		sImageFile = ReadString(oFile);
		oFile >> myfCustomImage;
		LoadAnimation(sImageFile, sGraphicsPath, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
	//"Description"
		sDescription = ReadString(oFile);
		SetIdentifier(sDescription);
	//%Vehicle code%
		oFile >> myiVehicleCode;
}
//----------------------------------------------------------------------------------------- [Callbacks] -
void LL_VehicleObject::Talk()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_VehicleObject::Look()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_VehicleObject::Push()
{	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_VehicleObject::Search()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_VehicleObject::Attack()
{
}
