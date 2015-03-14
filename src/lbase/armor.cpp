/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			armor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "armor.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Armor
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Armor::LL_Armor()
	: myiDefense(0)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Armor::Save(ofstream &oFile)
{	//"Image file path"  %Custom image%
 		oFile << Qoute(ImageFile()) << " ";
		oFile << myfCustomImage << " ";
	//"Description"
		oFile << Qoute(Identifier()) << " ";
	//%Weight% %Defense%
		oFile << Val(Weight()) << " ";
		oFile << Val(Defense()) << " ";
	//%Equip Hands%
 		oFile << Val(EquipsHands()) << " ";
   	//?Equip Arms? ?Equip Torso? ?EquipHead?
		oFile << Val(EquipsArms()) << " ";
		oFile << Val(EquipsTorso()) << " ";
		oFile << Val(EquipsHead()) << " ";
	//<endl>
		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Armor::Load(ifstream &oFile, string sGraphicsPath)
{	//Vars
		string sImageFile, sDescription;
		int iWeight, iDefense, iEquipHands;
		bool fEquipArms, fEquipTorso, fEquipHead;

	//"Image file path" %Custom image%
 		sImageFile = ReadString(oFile);
		oFile >> myfCustomImage;
		LoadAnimation(sImageFile, sGraphicsPath, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
	//"Description"
		sDescription = ReadString(oFile);
		SetIdentifier(sDescription);
	//%Weight% %Defense%
		oFile >> iWeight >> iDefense;
  		SetWeight(iWeight);
		SetDefense(iDefense);
	//%Equip Hands%
 		oFile >> iEquipHands;
 		SetEquipsHands(iEquipHands);
   	//?Equip Arms? ?Equip Torso? ?Equips Head?
		oFile >> fEquipArms >> fEquipTorso >> fEquipHead;
		SetEquipsArms(fEquipArms);
		SetEquipsTorso(fEquipTorso);
		SetEquipsHead(fEquipHead);
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_Armor::Run()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Armor::Talk()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Armor::Look()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Armor::Search()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Armor::Attack()
{
}
