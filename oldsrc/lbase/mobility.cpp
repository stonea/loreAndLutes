/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mobility.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "mobility.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Mobility
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Mobility::LL_Mobility()
{	//Set de' faults
		myiVehicularCode	= 0;
		myfInNorth			= false;
		myfInSouth			= false;
		myfInWest			= false;
		myfInEast			= false;
		myfOutNorth			= false;
		myfOutSouth			= false;
		myfOutWest			= false;
		myfOutEast			= false;
		myiNormalTicks		= 0;
		myiDamage			= 0;
		myiChanceOfDamage	= 0;
}
//------------------------------------------------------------------------------------------- [File I/O] -
//Note: All values in mobilities are saved as characters
void LL_Mobility::Save(ofstream &oFile)
{	//Vars
		unsigned char cVehicularCode;
		unsigned char cCombine;
		unsigned char cTicks, cDamage, cChance;

	//| Char
		oFile << " |";
	//%myiVehicularCode%
		cVehicularCode = myiVehicularCode;
		oFile.write(&cVehicularCode, 1);
	//As one unsigned char: %In N% %In S% %In W% %In E% %Out N% %Out S% %Out W% %Out E%
		cCombine = (InNorth() * 1) + (InSouth() * 2) + (InWest() * 4) + (InEast() * 8) +
				   (OutNorth() * 16) + (OutSouth() * 32) + (OutWest() * 64) + (OutEast() * 128);
	//cCombine
		oFile.write(&cCombine, 1);
	//%Normal Ticks%
		cTicks = NormalTicks();
		oFile.write(&cTicks, 1);
	//%Damage% %Chance Of Damage%
		cDamage = Damage();
		cChance = DamageChance();
		oFile.write(&cDamage, 1);
		oFile.write(&cChance, 1);
		oFile << " ";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Mobility::Load(ifstream &oFile)
{	//Vars
		char cPaddingByte;
		unsigned char cVehicularCode;
		unsigned char cCombine;
		unsigned char cTicks, cDamage, cChance;
	
	//Pad byte
		oFile >> cPaddingByte;
		if(cPaddingByte != '|')
			cerr << "ERROR reading mobility. Couldn't find padding byte.\n";

	//%myiVehicularCode%
		oFile.read(&cVehicularCode, 1);
		myiVehicularCode = int(cVehicularCode);
	//As one unsigned char: %In N% %In S% %In W% %In E%
		oFile.read(&cCombine, 1);
		myfInNorth  = false;
		myfInSouth  = false;
		myfInWest   = false;
		myfInEast   = false;
		myfOutNorth = false;
		myfOutSouth = false;
		myfOutWest  = false;
		myfOutEast  = false;

		if(int(cCombine) / 128 != 0) {int(cCombine) -= 128; myfOutEast  = true;}
		if(int(cCombine) / 64  != 0) {int(cCombine) -= 64;  myfOutWest  = true;}
		if(int(cCombine) / 32  != 0) {int(cCombine) -= 32;  myfOutSouth = true;}
		if(int(cCombine) / 16  != 0) {int(cCombine) -= 16;  myfOutNorth = true;}
		if(int(cCombine) / 8   != 0) {int(cCombine) -= 8;   myfInEast   = true;}
		if(int(cCombine) / 4   != 0) {int(cCombine) -= 4;   myfInWest   = true;}
		if(int(cCombine) / 2   != 0) {int(cCombine) -= 2;   myfInSouth  = true;}
		if(int(cCombine) / 1   != 0) {int(cCombine) -= 1;   myfInNorth  = true;}
	//%Normal Ticks%
		oFile.read(&cTicks, 1);
  		myiNormalTicks = int(cTicks);;
	//%Damage% %Chance Of Damage%
		oFile.read(&cDamage, 1);
		oFile.read(&cChance, 1);
  		myiDamage = int(cDamage);
  	 	myiChanceOfDamage = int(cChance);;
}
//---------------------------------------------------------------------------------------- [MEMVAR_MAPS] -
//MEMVAR_SETGET(SetVehicularCode,	VehicularCode,	Uint8,		myiVehicularCode);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetInNorth,		InNorth,		bool,		myfInNorth);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetInSouth,		InSouth,		bool,		myfInSouth);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetInWest,		InWest,			bool,		myfInWest);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetInEast,		InEast,			bool,		myfInEast);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetOutNorth,		OutNorth,		bool,		myfOutNorth);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetOutSouth,		OutSouth,		bool,		myfOutSouth);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetOutWest,		OutWest,		bool,		myfOutWest);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetOutEast,		OutEast,		bool,		myfOutEast);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetNormalTicks,	NormalTicks,	Uint8,		myiNormalTicks);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetDamage,		Damage,			Uint8,		myiDamage);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetDamageChance,	DamageChance,	Uint8,		myiChanceOfDamage);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Mobility::In(ASFC_DIRECTION iDir)
{	if	   (iDir == DIR_NORTH) return InNorth();
	else if(iDir == DIR_SOUTH) return InSouth();
	else if(iDir == DIR_WEST)  return InWest();
	else if(iDir == DIR_EAST)  return InEast();
	else
	{	cerr << "ERR: You shouldn't see this. Why'd you break it?\n";
		cerr << "     There's an error in this mobility.\n";
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Mobility::Out(ASFC_DIRECTION iDir)
{	if	   (iDir == DIR_NORTH) return OutNorth();
	else if(iDir == DIR_SOUTH) return OutSouth();
	else if(iDir == DIR_WEST)  return OutWest();
	else if(iDir == DIR_EAST)  return OutEast();
	else
	{	cerr << "ERR: You shouldn't see this. Why'd you break it?\n";
		cerr << "     There's an error in this mobility.\n";
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Mobility::Description()
{	//Vars
		string sDescription;
		
	if(InNorth())	sDescription += "N"; else sDescription += " ";
	if(InSouth())	sDescription += "S"; else sDescription += " ";
	if(InWest())	sDescription += "W"; else sDescription += " ";
	if(InEast())	sDescription += "E"; else sDescription += " ";
	if(OutNorth())	sDescription += "n"; else sDescription += " ";
	if(OutSouth())	sDescription += "s"; else sDescription += " ";
	if(OutWest())	sDescription += "w"; else sDescription += " ";
	if(OutEast())	sDescription += "e"; else sDescription += " ";
	
	return sDescription;
}
