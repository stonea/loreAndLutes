/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleset.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "vehicleset.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_VehicleSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_VehicleSet::LL_VehicleSet()
{
}
//---------------------------------------------------------------------------------- [Vehicle Handeling] -
void LL_VehicleSet::AddVehicle(LL_Vehicle &oAdd)
{	myloVehicles.Push(oAdd);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_VehicleSet::RemoveVehicle(int &iVehicleNum)
{	myloVehicles.Delete(iVehicleNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Vehicle& LL_VehicleSet::Vehicle(C_i(iVehicleNum))
{	if(iVehicleNum >= 0 && iVehicleNum < NumVehicles())
		return(myloVehicles[iVehicleNum]);
	cerr << "LL_VehicleSet::Vehicle() ERR 00 Attempt to return illegal vehicle.\n";
	return(myloVehicles[0]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_VehicleSet::NumVehicles()
{	return(myloVehicles.Length());
} 	
//------------------------------------------------------------------------------------------ [File I/O] -
void LL_VehicleSet::Save(ofstream &oFile)
{	//Write down the file type & version
		oFile << ".vehicle 0" << endl;
	
	//The # of vehicles
		oFile << NumVehicles() << endl;
	
	//Loop for the # of vehicles
		for(int i = 0; i < NumVehicles(); i++)
		{	//Save this vehicles identifier
				oFile << Qoute(myloVehicles[i].Identifier()) << endl;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_VehicleSet::Load(ifstream &oFile)
{	//Vars
		string 	sFileType;
		int		iVersionNumber,
				iNumVehicles;
		string	sVehicleIdentifier;
     	
	//Read in the file type and version number
		oFile >> sFileType;
		oFile >> iVersionNumber;
	
	//Continue if this is valid
		if	(ValidVersionNum("cVehicleSet::Load 000, Invalid file type or version", sFileType,
		 	iVersionNumber))
		{	//Read in the # of vehicles
				oFile >> iNumVehicles;
				
			//Resize the vehicle set
				myloVehicles.Resize(iNumVehicles);
				
			//Loop for iNumVehicles
				for(int i = 0; i < iNumVehicles; i++)
				{	//Read in this vehicle's identifier
						sVehicleIdentifier = ReadString(oFile);
						
					//Setup this vehicle
						myloVehicles[i].SetCode(i);
						myloVehicles[i].SetIdentifier(sVehicleIdentifier);
				}
		}
}
//P---------------------------------------------------------------------------------- [Error Handeling] -P
//Makes sure iVersionNumber is the correct version number for a .terrain file, if it is return true
bool LL_VehicleSet::ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum))
{	//Const
		const string REQUIRED_FILE_TYPE 		= ".vehicle";	//Holds the required file type
		const int	 REQUIRED_VERSION_NUMBER	= 0;			//Holds the required version number
		
	//If invalid
		if(sFileType != REQUIRED_FILE_TYPE || iVersionNum != REQUIRED_VERSION_NUMBER)
		{	cout << sErrorCode << endl;
			cout << "--[File Type]-->               "  << sFileType   				<< endl;
			cout << "--[Required File Type]-->      "  << REQUIRED_FILE_TYPE   		<< endl;
			cout << "--[Version Number]-->          "  << iVersionNum   			<< endl;
			cout << "--[Required Version Number]--> "  << REQUIRED_VERSION_NUMBER   << endl;
			return false;
		}
		else
			return true;
}
