/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			creature.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "creature.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Creature
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Creature::LL_Creature()
	: myfCalling(false),
	  myfRandom(false),
	  myiWeapon1(NO_EQUIP),
	  myiWeapon2(NO_EQUIP),
	  myiWeapon3(NO_EQUIP),
	  myiArmor1(NO_EQUIP),
	  myiArmor2(NO_EQUIP),
	  myiArmor3(NO_EQUIP),
	  myfTorsoEquip(false),
	  myfHeadEquip(false),
	  myfArmEquip(false),
	  myfHand1Equip(false),
	  myfHand2Equip(false),
	  myiMapEdgeX(100),
	  myiMapEdgeY(100),
	  myiStrength(50),
	  myiDexterity(50),
	  myiIntelligence(50),
	  myiMP(0),
	  myiMaxMP(0),
	  myiHP(30),
	  myiMaxHP(30),
	  myiExperience(5),
	  myfPerp(false)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Creature::Save(ofstream &oFile)
{	//"Identifier"
		oFile << Qoute(Identifier()) << endl;
	//%X%, %Y%
		oFile << myiX << " " << myiY << endl;
	//%Stength%, %Dexterity%, %Intelligence%
		oFile << myiStrength << " " << myiDexterity << " " << myiIntelligence << endl;
	//%MP%, %MaxMP%, %HP%, %MaxHP%
		oFile << myiMP << " " << myiMaxMP << " " << myiHP << " " << myiMaxHP << endl;
	//%Experience%
		oFile << myiExperience << endl;
	//%Vehicle Code%
		oFile << myoVehicle.Code() << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::Load(ifstream &oFile)
{	//Vars
		int tiVehicleCode;
		string ts;
	//"Identifier"
		ts = ReadString(oFile);
		SetIdentifier(ts);
	//%X%, %Y%
		oFile >> myiX >> myiY;
	//%Stength%, %Dexterity%, %Intelligence%
		oFile >> myiStrength >> myiDexterity >> myiIntelligence;
	//%MP%, %MaxMP%, %HP%, %MaxHP%
		oFile >> myiMP >> myiMaxMP >> myiHP >> myiMaxHP;
	//%Experience%
		oFile >> myiExperience;
	//%Vehicle Code%
		oFile >> tiVehicleCode;
		myoVehicle.SetCode(tiVehicleCode);
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_Creature::Run()
{	cout << "ERR cCreature::Run() 000 Fail to overload\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::Talk()
{	cout << "ERR cCreature::Talk() 000 Fail to overload\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::Look()
{	cout << "ERR cCreature::Look() 000 Fail to overload\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::Search()
{	cout << "ERR cCreature::Search() 000 Fail to overload\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::Attack()
{	cout << "ERR cCreature::Attack() 000 Fail to overload\n";
}
//-------------------------------------------------------------------------------------- [Map Handeling] -
//MEMVAR_SETGET(SetTerrainMap, TerrainMap, cTerrainMap*, mypoTerrainMap)
//MEMVAR_SETGET(SetUnitMap,    UnitMap,    cUnitMap*,    mypoUnitMap)
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::Place(int iX, int iY, int iLayer)
{	myiX = iX;
	myiY = iY;
	myiLayer = iLayer;
	mypoUnitMap->SetUnitOn(iX, iY, iLayer, myiIdentifierSeg, myiIdentifierOff);
}
//-------------------------------------------------------------------------------- [Attribute Handeling] -
void LL_Creature::AddHP(int iAmount)
{	myiHP += iAmount;
	if(myiHP > myiMaxHP)
		myiHP = myiMaxHP;
}
//------------------------------------------------------------------------------------ [Weapons & Armor] -	
bool LL_Creature::EquipWithWeapon(int iWeapon, ASFC_Console* poConsole, ASFC_Screen* poScreen, 
								  bool fReport)
{	//Vars
		bool fToEquipHand1, fToEquipHand2, fToEquipTorso, fToEquipHead, fToEquipArms;
	//If this weapon is nothing (hands) no need to equip
  		if(iWeapon < 0)
  			return false;
	//Default to equip nada
  		fToEquipHand1 = false;
  		fToEquipHand2 = false;
  		fToEquipTorso = false;
  		fToEquipHead  = false;
  		fToEquipArms  = false;
	//If the weapon is too heavy
		if(mypoItemSet->Weapon(iWeapon).Weight() + mypoItemSet->Weapon(myiWeapon1).Weight() +
		   mypoItemSet->Weapon(myiWeapon2).Weight() + mypoItemSet->Weapon(myiWeapon3).Weight() +
		   mypoItemSet->Armor(myiArmor1).Weight() +
		   mypoItemSet->Armor(myiArmor2).Weight() + mypoItemSet->Armor(myiArmor3).Weight() >
		   Strength())
		{
  			poConsole->Writeln("Too heavy.", 1);
			poConsole->Draw(0xFF);
			poScreen->Update();
			return false;
		}
	//See where this weapon equips and check to make sure it can be equipped der'
		//Check for hand equippin'	
			if(mypoItemSet->Weapon(iWeapon).EquipsHands() == 1)
			{	if(myfHand1Equip && myfHand2Equip)
				{	if(fReport)
					{	poConsole->Writeln("No free hand", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				if(!myfHand1Equip) fToEquipHand1 = true;
				else fToEquipHand2 = true;
			}
			if(mypoItemSet->Weapon(iWeapon).EquipsHands() == 2)
			{	if(myfHand1Equip || myfHand2Equip)
				{	if(fReport)
					{	poConsole->Writeln("Both hands must be free", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipHand1 = true;
				fToEquipHand2 = true;
			}
		//Check for arm equipping
			if(mypoItemSet->Weapon(iWeapon).EquipsArms())
			{	if(myfArmEquip)
				{	if(fReport)
					{	poConsole->Writeln("Arms are already equipped", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipArms = true;
			}
		//Check for torso equipping
			if(mypoItemSet->Weapon(iWeapon).EquipsTorso())
			{	if(myfTorsoEquip)
				{	if(fReport)
					{	poConsole->Writeln("Torso is already equipped", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipTorso = true;
			}
		//Check for head equipping
			if(mypoItemSet->Weapon(iWeapon).EquipsHead())
			{	if(myfHeadEquip)
				{	if(fReport)
					{	poConsole->Writeln("Head is already equipped", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipHead = true;
			}
	//If all three weapons are full this character is too full
		if(myiWeapon1 != NO_EQUIP && myiWeapon2 != NO_EQUIP && myiWeapon3 != NO_EQUIP)
			return false;

	//Find the first free weapon and equip it there
		if(myiWeapon1 == NO_EQUIP)
			myiWeapon1 = iWeapon;
		else if(myiWeapon2 == NO_EQUIP)
			myiWeapon2 = iWeapon;
		else
			myiWeapon3 = iWeapon;

	//Now set this equippment
		if(fToEquipHand1) myfHand1Equip = true;
		if(fToEquipHand2) myfHand2Equip = true;
		if(fToEquipTorso) myfTorsoEquip = true;
		if(fToEquipHead ) myfHeadEquip  = true;
		if(fToEquipArms ) myfArmEquip	= true;
	//Yay we gotched it!
		return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Creature::EquipWithArmor(int iArmor, ASFC_Console* poConsole, ASFC_Screen* poScreen, 
								 bool fReport)
{	//Vars
		bool fToEquipHand1, fToEquipHand2, fToEquipTorso, fToEquipHead, fToEquipArms;

	//If this armor is nothing no need to equip
  		if(iArmor < 0)
			return false;
	//Default to equip nada
  		fToEquipHand1 = false;
  		fToEquipHand2 = false;
  		fToEquipTorso = false;
  		fToEquipHead  = false;
  		fToEquipArms  = false;
	//If the weapon is too heavy
		if(mypoItemSet->Armor(iArmor).Weight() + mypoItemSet->Weapon(myiWeapon1).Weight() +
		   mypoItemSet->Weapon(myiWeapon2).Weight() + mypoItemSet->Weapon(myiWeapon3).Weight() +
		   mypoItemSet->Armor(myiArmor1).Weight() +
		   mypoItemSet->Armor(myiArmor2).Weight() + mypoItemSet->Armor(myiArmor3).Weight() >
		   Strength())
		{	poConsole->Writeln("Too heavy.", 1);
			poConsole->Draw(0xFF);
			poScreen->Update();
			return false;
		}
	//See where this armor equips and check to make sure it can be equipped der'
		//Check for hand equippin'
			if(mypoItemSet->Armor(iArmor).EquipsHands() == 1)
			{	if(myfHand1Equip && myfHand2Equip)
				{	if(fReport)
						poConsole->Writeln("No free hand", 1);
					return false;
				}
				if(!myfHand1Equip) fToEquipHand1 = true;
				else fToEquipHand2 = true;
			}
			if(mypoItemSet->Armor(iArmor).EquipsHands() == 2)
			{	if(myfHand1Equip || myfHand2Equip)
				{	if(fReport)
					{	poConsole->Writeln("Both hands must be free", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipHand1 = true;
				fToEquipHand2 = true;
			}
		//Check for arm equipping
			if(mypoItemSet->Armor(iArmor).EquipsArms())
			{	if(myfArmEquip)
				{	if(fReport)
					{	poConsole->Writeln("Arms are already equipped", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipArms = true;
			}
		//Check for torso equipping
			if(mypoItemSet->Armor(iArmor).EquipsTorso())
			{	if(myfTorsoEquip)
				{	if(fReport)
					{	poConsole->Writeln("Torso is already equipped", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipTorso = true;
			}
		//Check for head equipping
			if(mypoItemSet->Armor(iArmor).EquipsHead())
			{	if(myfHeadEquip)
				{	if(fReport)
					{	poConsole->Writeln("Head is already equipped", 1);
						poConsole->Draw(0xFF);
						poScreen->Update();
					}
					return false;
				}
				fToEquipHead = true;
			}			
	//If all three armors are full this character is too full
		if(myiArmor1 != NO_EQUIP && myiArmor2 != NO_EQUIP && myiArmor3 != NO_EQUIP)
			return false;

	//Find the first free armor and equip it there
		if(myiArmor1 == NO_EQUIP)
			myiArmor1 = iArmor;
		else if(myiArmor2 == NO_EQUIP)
			myiArmor2 = iArmor;
		else
			myiArmor3 = iArmor;

	//Now set this equippment
		if(fToEquipHand1) myfHand1Equip = true;
		if(fToEquipHand2) myfHand2Equip = true;
		if(fToEquipTorso) myfTorsoEquip = true;
		if(fToEquipHead ) myfHeadEquip  = true;
		if(fToEquipArms ) myfArmEquip	= true;

	//Yay we gotched it!
		return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::UnEquipWeapon(int iWeapon)
{	//Free whatever body parts this weapon used to take up
		if(mypoItemSet->Weapon(iWeapon).EquipsHands() == 1)
		{	if(myfHand1Equip) myfHand1Equip = false;
			else myfHand2Equip = false;
		}
		if(mypoItemSet->Weapon(iWeapon).EquipsHands() == 2)
		{	myfHand1Equip = false;
			myfHand2Equip = false;
		}
		if(mypoItemSet->Weapon(iWeapon).EquipsArms())
		{	myfArmEquip = false;
		}
		if(mypoItemSet->Weapon(iWeapon).EquipsTorso())
		{	myfTorsoEquip = false;
		}
		if(mypoItemSet->Weapon(iWeapon).EquipsHead())
		{	myfHeadEquip = false;
		}
	//Figure out which weapon iWeapon is set to, free it
		if(myiWeapon1 == iWeapon) myiWeapon1 = NO_EQUIP;
		if(myiWeapon2 == iWeapon) myiWeapon2 = NO_EQUIP;
		if(myiWeapon3 == iWeapon) myiWeapon3 = NO_EQUIP;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::UnEquipArmor(int iArmor)
{	//Free whatever body parts this armor used to take up
		if(mypoItemSet->Armor(iArmor).EquipsHands() == 1)
		{	if(myfHand1Equip) myfHand1Equip = false;
			else myfHand2Equip = false;
		}
		if(mypoItemSet->Armor(iArmor).EquipsHands() == 2)
		{	myfHand1Equip = false;
			myfHand2Equip = false;
		}
		if(mypoItemSet->Armor(iArmor).EquipsArms())
		{	myfArmEquip = false;
		}
		if(mypoItemSet->Armor(iArmor).EquipsTorso())
		{	myfTorsoEquip = false;
		}
		if(mypoItemSet->Armor(iArmor).EquipsHead())
		{	myfHeadEquip = false;
		}
	//Figure out which armor iArmor is set to, free it
		if(myiArmor1 == iArmor) myiArmor1 = NO_EQUIP;
		if(myiArmor2 == iArmor) myiArmor2 = NO_EQUIP;
		if(myiArmor3 == iArmor) myiArmor3 = NO_EQUIP;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Creature::NumWeapons()
{	if(myiWeapon1 != NO_EQUIP && myiWeapon2 != NO_EQUIP && myiWeapon3 != NO_EQUIP)
		return(3);
	if(myiWeapon1 != NO_EQUIP && myiWeapon2 != NO_EQUIP)
		return(2);
	if(myiWeapon1 != NO_EQUIP)
		return(1);
	return(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Creature::Weapon(int iNum)
{	if(iNum == 1) return(myiWeapon1);
	if(iNum == 2) return(myiWeapon2);
	if(iNum == 3) return(myiWeapon3);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Creature::NumArmors()
{	if(myiArmor1 != NO_EQUIP && myiArmor2 != NO_EQUIP && myiArmor3 != NO_EQUIP)
		return(3);
	if(myiArmor1 != NO_EQUIP && myiArmor2 != NO_EQUIP)
		return(2);
	if(myiArmor1 != NO_EQUIP)
		return(1);
	return(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Creature::Armor(int iNum)
{	if(iNum == 1) return(myiArmor1);
	if(iNum == 2) return(myiArmor2);
	if(iNum == 3) return(myiArmor3);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Creature::HoldsWeapon(int iWeaponNumber)
{	int iHeld = 0;
	if(myiWeapon1 == iWeaponNumber) iHeld++;
	if(myiWeapon2 == iWeaponNumber) iHeld++;
	if(myiWeapon3 == iWeaponNumber) iHeld++;
	return(iHeld);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_Creature::HoldsArmor(int iArmorNumber)
{	int iHeld = 0;
	if(myiArmor1 == iArmorNumber) iHeld++;
	if(myiArmor2 == iArmorNumber) iHeld++;
	if(myiArmor3 == iArmorNumber) iHeld++;
	return(iHeld);
}
//-------------------------------------------------------------------------------------------- [Running] -
bool LL_Creature::CanMove(ASFC_DIRECTION iDirection)
{	//Vars
		int iDesiredX, iDesiredY;

	//If idle return true
		if(iDirection == DIR_IDLE)
			return true;

	//Change the direction in our image
		ChangeDir(iDirection);
	//Figure out which tile the creature wants to move onto
		//Set the desired position to the current position
			iDesiredX = myiX;
			iDesiredY = myiY;
	//Offset this position based on the direction
		OffsetCoods(iDesiredX, iDesiredY, iDirection);
	//If it's off the map don't move
		if(iDesiredX < 0 || iDesiredY < 0 || iDesiredX > myiMapEdgeX || iDesiredY > myiMapEdgeY)
			return false;
	//If its legal to move
		if(mypoTerrainMap->MobilityTerrainMap()->LegalMove(mypoTerrainMap->GetTerrain(myiX, myiY).Code(),
		   mypoTerrainMap->GetTerrain(iDesiredX, iDesiredY).Code(), myoVehicle.Code(), iDirection))
		{	//If there isn't an object blocking us
				if(mypoUnitMap->IsPassable(iDesiredX, iDesiredY, myiLayer))
				{	//We can move
						return true;
				}
		}
	//Return false
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Creature::Move(ASFC_DIRECTION iDirection)
{	//Vars
		int iDesiredX, iDesiredY;

	//Change the direction in our image
		ChangeDir(iDirection);
	//Figure out which tile the creature wants to move onto
		//Set the desired position to the current position
			iDesiredX = myiX;
			iDesiredY = myiY;
	//Offset this position based on the direction
		OffsetCoods(iDesiredX, iDesiredY, iDirection);
	//If it's off the map don't move
		if(iDesiredX < 0 || iDesiredY < 0 || iDesiredX > myiMapEdgeX || iDesiredY > myiMapEdgeY)
			return false;
	//If its legal to move
		if(mypoTerrainMap->MobilityTerrainMap()->LegalMove(mypoTerrainMap->GetTerrain(myiX, myiY).Code(),
		   mypoTerrainMap->GetTerrain(iDesiredX, iDesiredY).Code(), myoVehicle.Code(), iDirection))
		{	//If there isn't an object blocking us
				if(mypoUnitMap->IsPassable(iDesiredX, iDesiredY, myiLayer))
				{	//Move to these coods
						MoveFromTo(myiX, myiY, iDesiredX, iDesiredY);
					//We moved
						return true;
				}
		}
	//If we're moving on to a vehicle then its legal
		if(mypoUnitMap->SegOn(iDesiredX, iDesiredY, LL_UnitMap::LAYER_VEHICLE) ==
		  LL_UnitMap::SEG_VEHICLE)
		{	//If there isn't an object blocking us
				if(mypoUnitMap->IsPassable(iDesiredX, iDesiredY, myiLayer))
				{	//Move to these coods
						MoveFromTo(myiX, myiY, iDesiredX, iDesiredY);
					//We moved
						return true;
				}
		}
	//Return false
		return false;
}
//------------------------------------------------------------------------------------------------- [AI] -
void LL_Creature::Call(int iX, int iY)
{	//Set this objects calling to iX, iY. Go forth creature, travel there!
		myiBlockedMoves = 0;
		myfCalling	= true;
		myfPerp     = false; // !!! CHANGE OCCURED HERE STRANGO $$$ !!!
		myiCallingX = iX;
  		myiCallingY = iY;
		myiOnStep	= 0;

	//Create the route
		mytpoLegalMovesMap = new LL_LegalMovesMap;
  		mypoTerrainMap->GrabLegalSpaces(myoVehicle.Code(), mytpoLegalMovesMap);

// 		myoRoute = mypoPathNodes->BuildRouteDirectly(myiX, myiY, myiCallingX, myiCallingY,
// 								   				 mytpoLegalMovesMap);
		myoRoute = mypoPathNodes->BuildRouteIndirectly(myiX, myiY, myiCallingX, myiCallingY, mytpoLegalMovesMap, myiLayer);
	 	myoRoute.Optimize();
  		delete mytpoLegalMovesMap;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Creature::RandomArea(int iX, int iY, int iWidth, int iHeight)
{	myfRandom = true;
	myiRandomX      = iX;
 	myiRandomY      = iY;
  	myiRandomWidth  = iWidth;
   	myiRandomHeight = iHeight;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Moves from X1, Y1 to X2, Y2 and updates changes on the unit map
void LL_Creature::MoveFromTo(C_i4(iX1, iY1, iX2, iY2))
{	//Move the unit
		mypoUnitMap->SetUnitOn(iX1, iY1, myiLayer, NULL_SEG, NULL_OFF);
		mypoUnitMap->SetUnitOn(iX2, iY2, myiLayer, myiIdentifierSeg, myiIdentifierOff);
		
	//Update this units coods
		myiX = iX2;
		myiY = iY2;
}
//P------------------------------------------------------------------------------------------ [Running] -P
void LL_Creature::RemoveFromMap()
{	//Remove the unit
		mypoUnitMap->SetUnitOn(myiX, myiY, myiLayer, NULL_SEG, NULL_OFF);
	//Update this units coods
		myiX = 0xFF;
		myiY = 0xFF;
}
//P-------------------------------------------------------------------------------------------- [Utils] -P
//Changes X, Y to the X, Y in direction iDirection
void LL_Creature::OffsetCoods(int &iX, int &iY, ASFC_DIRECTION iDirection)
{	//Offset this position based on the direction		
		switch(iDirection)
		{	case DIR_EAST:			{iX++;			}break;
			case DIR_NORTH_EAST:	{iY--; iX++;	}break;
			case DIR_NORTH:			{iY--;			}break;
			case DIR_NORTH_WEST:	{iY--; iX--;	}break;
			case DIR_WEST:			{iX--;			}break;
			case DIR_SOUTH_WEST:	{iY++; iX--;	}break;
			case DIR_SOUTH:			{iY++;			}break;
			case DIR_SOUTH_EAST:	{iY++; iX++;	}break;
			default: break;
		};
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Returns the opposite direction of iDirection (e.g. North returns South, West returns East...)
int LL_Creature::OppositeDir(ASFC_DIRECTION iDirection)
{	//Decide whats opposite based on what the direction is
		switch(iDirection)
		{	case DIR_EAST:			{return(DIR_WEST);}			break;
			case DIR_NORTH_EAST:	{return(DIR_SOUTH_WEST);}	break;
			case DIR_NORTH:			{return(DIR_SOUTH);}		break;
			case DIR_NORTH_WEST:	{return(DIR_SOUTH_EAST);}	break;
			case DIR_WEST:			{return(DIR_EAST);}			break;
			case DIR_SOUTH_WEST:	{return(DIR_NORTH_EAST);}	break;
			case DIR_SOUTH:			{return(DIR_NORTH);}		break;
			case DIR_SOUTH_EAST:	{return(DIR_NORTH_WEST);}	break;
			default: break;
		};
}
//P----------------------------------------------------------------------------------------------- [AI] -P
void LL_Creature::UpdateAI()
{	//Vars
		double dRand;
		int iRand;

	//If we're calling
		if(myfCalling)
		{	//If we're at our calling space stop routing
				if(myiCallingX == myiX && myiCallingY == myiY)
				{	myfCalling = false;
					myiBlockedMoves = 0;
				}
			//If we've ran out of steps and we're not at the calling position re call
				else if(myiOnStep >= myoRoute.Length())
				{	Call(myiCallingX, myiCallingY);
					myiBlockedMoves = 0;
				}
			//If we've had 5 blocked moves add to the CL List and lockdown
				else if(myiBlockedMoves > 5)
				{	//Recall it all
	    				Call(myiCallingX, myiCallingY);
						myiBlockedMoves = 0;
					//Try the step
						if(Move(myoRoute[myiOnStep]))
						{	myfPerp = false;
							myiOnStep++;
							myiBlockedMoves = 0;
						}
					//Else file a complaint
						else
						{	int iDesiredX = myiX;
							int iDesiredY = myiY;
							OffsetCoods(iDesiredX, iDesiredY, myoRoute[myiOnStep]);
							mypoCLList->AddCollision(  myiX, myiY, iDesiredX, iDesiredY, 
     												   myiLayer, myiIdentifierSeg, myiIdentifierOff
												    );
							mypoCLList->CheckEntries();
						}
				}
			//Otherwise Follow this step if legal
				else if(myiOnStep < myoRoute.Length())
				{	if(Move(myoRoute[myiOnStep]))
					{	myfPerp = false;
						myiOnStep++;
					}
					//If we couldn't move either move back or perpendicullay
					else
					{	//Choose a random number from 0-1
/*							dRand = ((double)rand() / (double)(RAND_MAX+1));
							iRand = dRand * 2;
						//If iRand == 0 go back
							if(iRand == 0)
							{	if(Move(ASFC_DIRECTION(OppositeDir(myoRoute[myiOnStep - 1]))))
									myiOnStep--;
							}
						//Else try moving perpendicully !!! NEW !!!
							else
							{*/
					//Increase our block count
						myiBlockedMoves++;
					//If we're blocked because of a creature move
						if(!myfPerp)
						{	//Choose a random number from 0-4
      							dRand = ((double)rand() / (double)(RAND_MAX+1));
								iRand = int(iRand * 4);
							//If that random number was 3 or 2 then do stuff
								if(iRand == 3 || iRand == 2 || myiBlockedMoves > 4)
								{	int iDir = myoRoute[myiOnStep];
									int iOriginalDir = myoRoute[myiOnStep];
	
									if(iDir == DIR_NORTH) iDir = DIR_WEST;
									else if(iDir == DIR_SOUTH) iDir = DIR_EAST;
									else if(iDir == DIR_WEST)  iDir = DIR_NORTH;
									else if(iDir == DIR_EAST)  iDir = DIR_SOUTH;
			
									myoRoute.AddElement(myiOnStep, ASFC_DIRECTION(iDir));
									myiOnStep++;
									iDir = OppositeDir(ASFC_DIRECTION(iDir));
									myoRoute.AddElement(myiOnStep, ASFC_DIRECTION(iDir));
									myoRoute.AddElement(myiOnStep+1, ASFC_DIRECTION(iOriginalDir));
									
									/*
									//Choose a random number from 0-3
										dRand = ((double)rand() / (double)(RAND_MAX+1));
										iRand = dRand * 3;
									//Pause for that random amount
										for(int i = 1; i < iRand + 1; i++)
										{	myoRoute.AddElement(myiOnStep + i, DIR_IDLE);
										}
									//Re enter the original direction
										myoRoute.AddElement(iRand + 1, ASFC_DIRECTION(iOriginalDir));
									*/
									
									//We've gone perp
										myfPerp = true;
										
									if(Move(myoRoute[myiOnStep]))
									{	myfPerp = true;
										myiOnStep++;
									}
								}
							//Else try back stepping
								else
								{	if(myiOnStep > 1)
									{	if(Move(ASFC_DIRECTION(OppositeDir(myoRoute[myiOnStep - 1]))))
	        							{	myiOnStep--;
										}
									}
								}

						//	}
						}
					}
				}
		}
	
	//Const
		const static int RAND_NORTH = 0;
		const static int RAND_SOUTH = 1;
		const static int RAND_WEST  = 2;
		const static int RAND_EAST  = 3;

	//If the object is randomifying and we're not calling
		if(myfRandom && !myfCalling)
		{	//Pick a random direction
	  			double dRand = ((double)rand() / (double)(RAND_MAX+1));
				int iRand = int(dRand * 8);
	  			
			//If North move north if possible
				if(iRand == RAND_NORTH && myiY - 1 >= myiRandomY)
					Move(DIR_NORTH);
				else if(iRand == RAND_SOUTH && myiY + 1 < myiRandomY + myiRandomHeight)
					Move(DIR_SOUTH);
				else if(iRand == RAND_WEST && myiX - 1 >= myiRandomX)
					Move(DIR_WEST);
				else if(iRand == RAND_EAST && myiX + 1 < myiRandomX + myiRandomWidth)
					Move(DIR_EAST);
		}
}
