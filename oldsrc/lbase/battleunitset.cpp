/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleunitset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "battleunitset.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BattleUnitSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_BattleUnitSet::LL_BattleUnitSet()
{
}
//---------------------------------------------------------------------------- [General Unit Management] -
LL_Unit& LL_BattleUnitSet::Unit(int iSeg, int iOff)
{	switch(iSeg)
	{	case SEG_SCRIPTED_ITEMS:
		{	return(mypoItemSet->ScriptedItem(myloScriptedItems[iOff].iNum));
		}break;

		case SEG_WEAPONS:
		{	return(mypoItemSet->Weapon(myloWeapons[iOff].iNum));
		}break;

		case SEG_ARMORS:
		{	return(mypoItemSet->Armor(myloArmors[iOff].iNum));
		}break;

		case SEG_MONSTERS:
		{	return(myloMonsters[iOff]);
		}break;

		case SEG_SCRIPTED_UNITS:
		{	return(ScriptedUnit(iOff));
		}break;
		
		case SEG_CHESTS:
		{	return(myloChests[iOff]);
		}break;

		case SEG_TRANSPORTS:
		{	return(myloTransports[iOff]);
		}break;
		
		case SEG_GUTS:
		{	return(myloGuts[iOff]);
		}break;

		
		case SEG_BATTLE_ENEMY:
		{	return(myloBattleEnemies[iOff]);
		}

		case SEG_BATTLE_PLAYER:
		{	return(myloBattlePlayers[iOff]);
		}

		case SEG_VEHICLES:
		{	return(mypoVehicleObjectSet->VehicleObject(myloVehicleObjects[iOff].iNum));
		}

		case SEG_PLAYER:
		{	return(*mypoPlayer);
		}break;
		
		default:
			cerr << "Request for invalid unit: " << iSeg << ":" << iOff << endl;
		break;
	};
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleUnitSet::Run()
{	//Loop through all units and run
		//Global Script
//			myoGlobalScript.Run();		(Should use global script from the real LL_UnitSet)
		//Scripted Items
			//Don't run
		//Weapons
			//Don't run
		//Armors
			//Don't run
		//ScriptedUnits
			for(int i = 0; i < NumScriptedUnits(); i++)
			{	ScriptedUnit(i).Run();
			}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleUnitSet::ResetAnimations()
{	//Loop through all units reset their animation
		mypoPlayer->Reset();
		for(int i = 0; i < NumScriptedItems(); i++)
		{	//myloScriptedItems[i].Reset();
		}
 		for(int i = 0; i < NumWeapons(); i++)
 		{	//myloWeapons[i].Reset();
		}
 		for(int i = 0; i < NumArmors(); i++)
 		{	//myloArmors[i].Reset();
		}
 		for(int i = 0; i < NumMonsters(); i++)
 		{	myloMonsters[i].Reset();
		}
 		for(int i = 0; i < NumScriptedUnits(); i++)
 		{	myloScriptedUnits[i].Reset();
		}
		for(int i = 0; i < NumPlayers(); i++)
 		{	myloBattlePlayers[i].Reset();
		}
		for(int i = 0; i < NumEnemies(); i++)
 		{	myloBattleEnemies[i].Reset();
		}
}
//--------------------------------------------------------------------------------------------- [Players]-
int LL_BattleUnitSet::NumPlayers()
{	return(myloBattlePlayers.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleUnitSet::DeletePlayer(int iNum)
{	myloBattlePlayers.Delete(iNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleUnitSet::ClearPlayers()
{	myloBattlePlayers.Resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_BattlePlayer& LL_BattleUnitSet::Player(int iNum)
{	return(myloBattlePlayers[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_BattlePlayer& LL_BattleUnitSet::PlayerMappedToPartyMember(int iNum)
{	// !!!!
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleUnitSet::AddPlayer(LL_TerrainMap* poTerrainMap, LL_BattleUnitMap* poUnitMap,
  								 LL_GameClock* poClock, LL_EventQueue* poQueue, LL_ItemSet* poItemSet,
			           			 string sGraphicsDir, ASFC_Animation* pCorpseImg,
            		   			 int iMemberNum, LL_PartyMember* poPartyMember, ASFC_Input* poInput,
         						 ASFC_Console* poConsole, ASFC_Screen* poScreen, int iMapEdgeX,
								 int iMapEdgeY,int iX, int iY, int iL)
{
	//Dynamically allocate room for the player
		myloBattlePlayers.Resize(myloBattlePlayers.Length() + 1);
		int iUnit = myloBattlePlayers.Length() - 1;
	//Set dis' playa' up get the bling bling and such
		myloBattlePlayers[iUnit].SetTerrainMap(poTerrainMap);
		myloBattlePlayers[iUnit].SetUnitMap(poUnitMap);
  		myloBattlePlayers[iUnit].SetBattleUnitMap(poUnitMap);
  		myloBattlePlayers[iUnit].SetClock(poClock);
  		myloBattlePlayers[iUnit].SetEventQueue(poQueue);
  		myloBattlePlayers[iUnit].SetItemSet(poItemSet);
  		myloBattlePlayers[iUnit].SetSeg(SEG_BATTLE_PLAYER);
		myloBattlePlayers[iUnit].SetOff(iUnit);
  		myloBattlePlayers[iUnit].Place(iX, iY, iL);
		myloBattlePlayers[iUnit].SetMapEdgeX(iMapEdgeX);
		myloBattlePlayers[iUnit].SetMapEdgeY(iMapEdgeY);
		myloBattlePlayers[iUnit].SetAnimation(*poPartyMember);
//		myloBattlePlayers[iUnit].LoadAnimation(sGraphicsFile, sGraphicsDir);
		myloBattlePlayers[iUnit].SetCorpseImage(pCorpseImg);
		myloBattlePlayers[iUnit].SetMemberNum(iMemberNum);
		myloBattlePlayers[iUnit].SetMember(poPartyMember);
		myloBattlePlayers[iUnit].SetInput(poInput);
		myloBattlePlayers[iUnit].SetConsole(poConsole);
		myloBattlePlayers[iUnit].SetScreen(poScreen);
		
		//!!! TMP
			LL_Vehicle oVehicle;
			oVehicle.SetCode(0);
		myloBattlePlayers[iUnit].SetVehicle(oVehicle);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_BattleUnitSet::AnyPlayers()
{	//Loop through all player's if any aren't dead than there are players
		for(int i = 0; i < myloBattlePlayers.Length(); i++)
		{	if(	mypoPlayer->PartyMembers()[myloBattlePlayers[i].MemberNum()].State()
	 			!= LL_PartyMember::STATE_DEAD &&
     			!myloBattlePlayers[i].Escaped())
			{
   				return true;
   			}
		}
	//We're done
		return false;
}
//-------------------------------------------------------------------------------------------- [Enemies] -
int LL_BattleUnitSet::NumEnemies()
{	return(myloBattleEnemies.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleUnitSet::ClearEnemies()
{	myloBattleEnemies.Resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_BattleEnemy& LL_BattleUnitSet::Enemy(int iNum)
{	return(myloBattleEnemies[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleUnitSet::AddEnemy(LL_TerrainMap* poTerrainMap, LL_BattleUnitMap* poUnitMap,
  								LL_GameClock* poClock, LL_EventQueue* poQueue, LL_ItemSet* poItemSet,
            					string sGraphicsFile, string sGraphicsDir, ASFC_Animation* pCorpseImg,
               					ASFC_Console* poConsole, ASFC_Screen* poScreen, int iMonsterType,
                    			int iMapEdgeX, int iMapEdgeY, int iX, int iY, int iL)
{
	//Dynamically allocate room for the player
		myloBattleEnemies.Resize(myloBattleEnemies.Length() + 1);
		int iUnit = myloBattleEnemies.Length() - 1;
	//Set dis' playa' up! Get dat' whack bling bling'n and such:
		myloBattleEnemies[iUnit].SetTerrainMap(poTerrainMap);
		myloBattleEnemies[iUnit].SetUnitMap(poUnitMap);
  		myloBattleEnemies[iUnit].SetBattleUnitMap(poUnitMap);
  		myloBattleEnemies[iUnit].SetClock(poClock);
  		myloBattleEnemies[iUnit].SetEventQueue(poQueue);
  		myloBattleEnemies[iUnit].SetItemSet(poItemSet);
  		myloBattleEnemies[iUnit].SetSeg(SEG_BATTLE_ENEMY);
		myloBattleEnemies[iUnit].SetOff(iUnit);
  		myloBattleEnemies[iUnit].Place(iX, iY, iL);
		myloBattleEnemies[iUnit].LoadAnimation(sGraphicsFile, sGraphicsDir);
		myloBattleEnemies[iUnit].SetCorpseImage(pCorpseImg);
		myloBattleEnemies[iUnit].SetConsole(poConsole);
		myloBattleEnemies[iUnit].SetScreen(poScreen);
		myloBattleEnemies[iUnit].SetBattlePlayers(&myloBattlePlayers);
		myloBattleEnemies[iUnit].SetMapEdgeX(iMapEdgeX);
		myloBattleEnemies[iUnit].SetMapEdgeY(iMapEdgeY);
		myloBattleEnemies[iUnit].SetTemplate(iMonsterType);
		mypoMonsterSet->Monster(iMonsterType).MakeMonster(sGraphicsDir, &myloBattleEnemies[iUnit]);
	//Choose a strategy
		myloBattleEnemies[iUnit].SetStrategy(mypoMonsterSet->Monster(iMonsterType).PickStrategy());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_BattleUnitSet::AnyEnemies()
{	//Loop through all enemies if any aren't dead than there are enemies
		for(int i = 0; i < myloBattleEnemies.Length(); i++)
		{	if(!myloBattleEnemies[i].Dead())
				return true;
		}
	//We're done
		return false;
}
