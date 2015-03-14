/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monstertemplate.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "monstertemplate.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_monstertemplate
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_MonsterTemplate::LL_MonsterTemplate()
	: myiRarity(50),
	  myiStrength(50),
	  myiDexterity(50),
	  myiIntelligence(50),
	  myiMP(0),
	  myiMaxMP(0),
	  myiHP(30),
	  myiMaxHP(30),
	  myiExperience(5),
	  myiWeapon1(-1),
	  myiWeapon2(-1),
	  myiArmor1(-1),
	  myiArmor2(-1),
	  myiVehicleCode(0),
	  myiChanceOfChest(0),
	  myiChanceOfFood(50),
	  myiMaxFood(5),
	  myiPartyMin(2),
	  myiPartyMax(5),
	  myfCustomImage(false)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_MonsterTemplate::Save(ofstream &oFile)
{	//"Image File" !Custom Image!
		oFile << Qoute(mysImage) << endl;
		oFile << myfCustomImage  << endl;
	//"Identifier"
		oFile << Qoute(mysIdentifier) << endl;
	//%Rarity%
		oFile << myiRarity << " ";
	//%Strength% %Dexterity% %Intelligence%
		oFile << myiStrength << " " << myiDexterity << " " << myiIntelligence << " ";
	//%MP% %MaxMP% %HP$ %MaxHP%
		oFile << myiMP << " " << myiMaxMP << " " << myiHP << " " << myiMaxHP << " ";
	//%Experience%
		oFile << myiExperience << " ";
	//%Weapon1% %Weapon2% %Armor1% %Armor2%
		oFile << myiWeapon1 << " " << myiWeapon2 << " " << myiArmor1 << " " << myiArmor2 << " ";
	//%Vehicle Code%
		oFile << myiVehicleCode << endl;
	//%Num Strategies%, <Loop for strategies>
		oFile << myliStratgies.Length() <<  " ";
		for(int i = 0; i < myliStratgies.Length(); i++)
		{	//%Strategy
				oFile << myliStratgies[i] << " ";
		}
	//%Party size min% %Party size max%
  		oFile << myiPartyMin << " " << myiPartyMax << " ";
	//<Save friends>
		//%Num Friends%
			oFile << NumFriends() << " ";
		//<Loop through friends>
			for(int i = 0; i < NumFriends(); i++)
			{	//%Monster% %Chance%
					oFile << myliFriends[i] << " " << myliFriendChance[i] << " ";
			}
	//%Chance of Chest% %Chance of food% %Max food%
		oFile <<  myiChanceOfChest << " " << myiChanceOfFood << " " << myiMaxFood << " ";
	//<Save chest>
  		myoDeathChest.Save(oFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MonsterTemplate::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
 		int iNum, iStrategy;
		string ts;
		int iNumFriends;

	//"Image File" !Custom Image!
		ts = ReadString(oFile);
		mysImage = ts;
		oFile >> myfCustomImage;
	//"Identifier"
		ts = ReadString(oFile);
		mysIdentifier = ts;
	//%Rarity%
		oFile >> myiRarity;
	//%Strength% %Dexterity% %Intelligence%
		oFile >> myiStrength >> myiDexterity >> myiIntelligence;
	//%MP% %MaxMP% %HP$ %MaxHP%
		oFile >> myiMP >> myiMaxMP >> myiHP >> myiMaxHP;
	//%Experience%
		oFile >> myiExperience;
	//%Weapon1% %Weapon2% %Armor1% %Armor2%
 		oFile >> myiWeapon1 >> myiWeapon2 >> myiArmor1 >> myiArmor2;
	//%Vehicle Code%
		oFile >> myiVehicleCode;
	//%Num Strategies%, <Loop for strategies>
		oFile >> iNum;
		myliStratgies.Resize(iNum);
		for(int i = 0; i < iNum; i++)
		{	//%Strategy%
				oFile >> iStrategy;
    			myliStratgies[i] = LL_Strategy(iStrategy);
		}
	//%Party size min% %Party size max%
  		oFile >> myiPartyMin >> myiPartyMax;
	//<Load friends>
		//%Num Friends%
			oFile >> iNumFriends;
			myliFriends.Resize(iNumFriends);
			myliFriendChance.Resize(iNumFriends);
		//<Loop through friends>
			for(int i = 0; i < NumFriends(); i++)
			{	//%Monster% %Chance%
					oFile >> myliFriends[i] >> myliFriendChance[i];
			}
	//%Chance of Chest% %Chance of food% %Max food%
		oFile >> myiChanceOfChest >> myiChanceOfFood >> myiMaxFood;
	//<Load chest>
  		myoDeathChest.Load(oFile, sGraphicsDir);
}
//--------------------------------------------------------------------------------------- [Object Maker] -
void LL_MonsterTemplate::MakeMonster(string sGraphicsPath, LL_Monster* poMonster)
{	//Set attributes
		LL_Vehicle oVehicle;
		oVehicle.SetCode(VehicleCode());
		poMonster->SetRarity(Rarity());
		poMonster->SetStrength(Strength());
		poMonster->SetDexterity(Dexterity());
		poMonster->SetIntelligence(Intelligence());
		poMonster->SetMP(MP());
		poMonster->SetMaxMP(MaxMP());
		poMonster->SetHP(HP());
		poMonster->SetMaxHP(MaxHP());
		poMonster->SetExperience(Experience());
		poMonster->SetVehicle(oVehicle);
		poMonster->SetChanceOfChest(ChanceOfChest());
		poMonster->SetChanceOfFood(ChanceOfFood());
		poMonster->SetMaxFood(MaxFood());
	//Load weapons & armors
		poMonster->EquipWithWeapon(myiWeapon1, NULL, NULL, false);
		poMonster->EquipWithWeapon(myiWeapon2, NULL, NULL, false);
		poMonster->EquipWithArmor (myiArmor1, NULL, NULL, false);
		poMonster->EquipWithArmor (myiArmor2, NULL, NULL, false);
	//Load image
		poMonster->SetCustomImage(myfCustomImage);
		poMonster->LoadAnimation(Image(), sGraphicsPath);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_MonsterTemplate::LL_Strategy LL_MonsterTemplate::PickStrategy()
{	//Vars
		double dRand;
		int iRand;

	//If we have no strategies default to normal
		if(myliStratgies.Length() == 0)
			return(STRATEGY_NORMAL);

	//Pick a random strategy
  		dRand = ((double)rand() / (double)(RAND_MAX+1));
		iRand = dRand * myliStratgies.Length();
		return(myliStratgies[iRand]);
}
//-------------------------------------------------------------------------------------------- [Friends] -
void LL_MonsterTemplate::AddFriend(int iMonsterCode, int iChance)
{	myliFriends.Push(iMonsterCode);
	myliFriendChance.Push(iChance);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MonsterTemplate::DeleteFriend(int iNum)
{	myliFriends.Delete(iNum);
	myliFriendChance.Delete(iNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_MonsterTemplate::Friend(int iNum)
{	return(myliFriends[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_MonsterTemplate::FriendChance(int iNum)
{	return(myliFriendChance[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MonsterTemplate::SetFriend(int iNum, int iTo)
{	myliFriends[iNum] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MonsterTemplate::SetFriendChance(int iNum, int iTo)
{	myliFriendChance[iNum] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_MonsterTemplate::NumFriends()
{	return(myliFriendChance.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_MonsterTemplate::PickMonster(int iSelfCode)
{	//Vars
		double dRand;
		int iRand;

	//Loop through all friends
		for(int i = 0; i < NumFriends(); i++)
		{	//Chose a random number from [0-100]
				dRand = ((double)rand() / (double)(RAND_MAX+1));
				iRand = dRand * 100;
			//Determine whether this friend has been chosen
				if(iRand <= myliFriendChance[i])
					return(myliFriends[i]);
		}
	//If no friend was chosen then this monster has been picked
		return(iSelfCode);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_MonsterTemplate::NumMonstersToPlace()
{	//Vars
		double dRand;
		int iRand;
		
	//Determine randomly how many monsters to place
		dRand = ((double)rand() / (double)(RAND_MAX+1));
		iRand = dRand * (myiPartyMax - myiPartyMin) + myiPartyMin;
  		if(iRand < myiPartyMin)
  			iRand = myiPartyMin;
  		return iRand;
}
