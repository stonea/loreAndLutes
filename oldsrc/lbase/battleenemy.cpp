/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleenemy.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "battleenemy.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LL_BattleEnemey
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LL_BattleEnemy::LL_BattleEnemy()
{	SetHP(100);
	SetDead(false);
	myiStrategy = LL_MonsterTemplate::STRATEGY_NORMAL;
	myiMapEdgeX = 10;
	myiMapEdgeY = 10;
	myiEnemy = -1;
	myiCurrentWeapon = 1;
	myfFlee = false;
}
//-------------------------------------------------------------------------------------------- [Drawing] -
int LL_BattleEnemy::BlitTo(ASFC_Surface &screen, const int & iX, const int & iY)
{	if(myfDead)
		mypoCorpseImage->BlitTo(screen, iX, iY);
	else
		mylAnimations[myiCurrentImage].BlitTo(screen, iX, iY);
}
//------------------------------------------------------------------------------------------- [Updating] -
void LL_BattleEnemy::Run(ASFC_Surface &oScreen)
{	//The enemy hasn't fleed yet
		myfFlee = false;
	//If the enemy is dead he can't move
		if(Dead())
			return;
	//Display the enemy tag in the console
		mypoConsole->Write("\nEnemy - \n", 1);
	//Switch weapons
		myiCurrentWeapon++;
		if(Weapon(myiCurrentWeapon) == LL_Creature::NO_EQUIP)
			myiCurrentWeapon = 1;
			
	//AI this sucker!
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_IDIOT)			RunAsIdiot();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_NORMAL)			RunAsNormal();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_WIMP)			RunAsWimp();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_SMART_WIMP)		RunAsSmartWimp();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_AERIAL_ATTACKER)	RunAsAerialAttacker();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_EXPLOITER)		RunAsExploiter();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_SLACKER)			RunAsSlacker();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_BLOODTHIRSTY)	RunAsBloodThirsty();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_WARRIOR)			RunAsWarrior();
		if(myiStrategy == LL_MonsterTemplate::STRATEGY_UBER_WIMP)		RunAsUberWimp();
	//Check to see if the enemy has fleed
		CheckFlee();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleEnemy::Damage(int iAmount)
{	//If the enemy is already dead call the user a luser
		if(Dead())
		{	mypoConsole->Write("This enemy is already dead!\n", 0);
			return;
		}
	//The enemy is hit
		mypoConsole->Write("Enemy is hit!\n", 1);
	//Calculate this damage against the player's defense value
  		int iDefense = DefenseValue();
 		if(iDefense > iAmount)
 			iAmount = 0;
		else
			iAmount -= iDefense;
	//Based on the amount of damage display it
/*		if(iAmount <= 0)
			mypoConsole->Write("No damage\n", 0);
		else if(iAmount < 3)
			mypoConsole->Write("Scratched\n", 0);
		else if(iAmount >= 3  && iAmount < 6)
			mypoConsole->Write("Light damage\n", 0);
		else if(iAmount >= 6  && iAmount < 12)
			mypoConsole->Write("Heavy damage\n", 0);
		else if(iAmount >= 12 && iAmount < 24)
			mypoConsole->Write("Lightly wounded\n", 0);
		else if(iAmount >= 24  && iAmount < 48)
			mypoConsole->Write("Heavily wounded\n", 0);
		else
			mypoConsole->Write("Critical damage!\n", 0);
*/
mypoConsole->Write("Damage = ", 0);
mypoConsole->Writeln(Val(iAmount), 0);

	//Change the HP
		SetHP(HP() - iAmount);
	//Check to see if the enemy is dead
		if(HP() < 0)
		{	mypoConsole->Write("-~ Enemy Killed! -~\n", 2);
			myfDead = true;
			Die();
		}
}
//P----------------------------------------------------------------------------------------- [Updating] -P
void LL_BattleEnemy::AttackTo(int iX, int iY)
{	//Attack there
		EventQueue()->Attack(LL_UnitMap::SEG_BATTLE_ENEMY, Off(), iX, iY, AttackValue());
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_BattleEnemy::Die()
{	//Vars
		int iOldX = myiX;
		int iOldY = myiY;
		double dRand; int iRand;
		
	//Move off the map
		RemoveFromMap();
	//Determine whether to place a chest where you died
  		dRand = ((double)rand() / (double)(RAND_MAX+1));
		iRand = dRand * 100;
		if(iRand <= ChanceOfChest())
			EventQueue()->PlotMonsterChest(Template(), iOldX, iOldY);
	//If a chest wasn't placed place some good ol' guts
		else
		{	EventQueue()->PlotMonsterGuts(Template(), iOldX, iOldY);
		}
}
//P------------------------------------------------------------------------------------- [Calculations] -P
int LL_BattleEnemy::AttackValue()
{	//Vars
		int iAttack;
		int iAttackSkill;
		double dStrengthConstant;
		double dHitConstant;
		int iMinAttack;

	//If the player has no weapons the attack value is always (1/8) * strength
		if(Weapon(myiCurrentWeapon) == LL_Creature::NO_EQUIP)
		{	iAttack = (1.0/8.0) * float(Strength());
			dHitConstant = 0;
		}
	//For ground weapons Attack value = ((Str)^.8/7500)(Attack)^2 + 1
		else
  		{	dStrengthConstant =  pow(double(Strength()), 0.8)/7500;
			iAttackSkill = ItemSet()->Weapon(Weapon(myiCurrentWeapon)).AttackSkill();
			iAttack = dStrengthConstant * iAttackSkill * iAttackSkill + 1;
			dHitConstant = double(Dexterity()) / 200.0;
		}
	//Determine the minimum attack value. It is equal to (Dex / 200) * iAttack
		iMinAttack   = dHitConstant * iAttack;
	//Pick a value between iMinAttack and iAttack
		double dRand = ((double)rand() / (double)(RAND_MAX+1));
		int iRand    = dRand * (iAttack - iMinAttack);
		iAttack      = iMinAttack + iRand;
		return(iAttack);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_BattleEnemy::DefenseValue()
{	//Vars
		int iDefense = 0;
		int iMinDefense;
		double dHitConstant;
		double dStrengthConstant = double(Strength()) / 1000.0;
	//Defense Value = (Str/1000)DefenseValArm1 + (Str/1000)DefenseValArm2 + (Str/1000)DefenseValArm3
		if(Armor(1) != LL_Creature::NO_EQUIP)
			iDefense += dStrengthConstant * ItemSet()->Armor(Armor(1)).Defense();
		if(Armor(2) != LL_Creature::NO_EQUIP)
			iDefense += dStrengthConstant * ItemSet()->Armor(Armor(2)).Defense();
		if(Armor(3) != LL_Creature::NO_EQUIP)
			iDefense += dStrengthConstant * ItemSet()->Armor(Armor(3)).Defense();
	//Get a minimum hit constant
		dHitConstant = double(Dexterity()) / 200.0;
		iMinDefense   = dHitConstant * iDefense;
	//Pick a value between iMinAttack and iDefense
		double dRand = ((double)rand() / (double)(RAND_MAX+1));
		int iRand    = dRand * (iDefense - iMinDefense);
		iDefense     = iMinDefense + iRand;
	//Return this defense
		return(iDefense);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LL_BattleEnemy::WithinRadius(int iX, int iY)
{	//Vars
		int iRadius;
		double dDistance;
		
	//Calculate the radius
		if(Weapon(myiCurrentWeapon) == LL_Creature::NO_EQUIP)
     		iRadius = 1;
   		else
   			iRadius = ItemSet()->Weapon(Weapon(myiCurrentWeapon)).Radius();
  	//Determine if it's within (Distance = sqrt((x2 - x1)^2 + (y2 - y1)^2))
		dDistance = sqrt(pow(double(iX - myiX), 2) + pow(double(iY - myiY), 2));
	//Is it within?
		if(int(dDistance) <= iRadius)
			return true;
		return false;
}
//P----------------------------------------------------------------------------------------------- [AI] -P
/*	Idiots move randomly attacking when the player is next to them.
	They never flee.
*/
void LL_BattleEnemy::RunAsIdiot()
{	//Vars
		double dRand;
  		int iDir;
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
	//Grab a random value from (0-3)
  		dRand = ((double)rand() / (double)(RAND_MAX+1));
		iDir = dRand * 4;
	//Move randomly
		switch(iDir)
		{	case RNDDIR_NORTH:
			{	Move(DIR_NORTH);
			}break;
			case RNDDIR_SOUTH:
			{	Move(DIR_SOUTH);
			}break;
			case RNDDIR_WEST:
			{	Move(DIR_WEST);
			}break;
			case RNDDIR_EAST:
			{	Move(DIR_EAST);
			}break;
			default:
			{	cerr << "LL_BattleEnemy::RunAsIdiot() Error! Check your randomizer!\n";
			}break;
		};
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Normals attack a random player.
	They flee when they're HP is 20% of their maximum.	
*/
void LL_BattleEnemy::RunAsNormal()
{	//Vars
		double dRand;
		int iLoops = 0;
	
	//If we're damaged to less than 20% of our health or 10hp turn into an uber wimp
		if(HP() < MaxHP() * .2 || HP() < 10)
		{	myiStrategy = LL_MonsterTemplate::STRATEGY_UBER_WIMP;
			return;
		}
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
	//If the player this enemy really hates is dead or nonexistant pick another one randomley
		while(!EnemyExists(myiEnemy) && iLoops < 100)
		{	//Grab a random player to hate
	  			dRand = ((double)rand() / (double)(RAND_MAX+1));
				myiEnemy = dRand * mylpoBattlePlayers->Length();
				iLoops++;
		}
	//Beacon this enemy towards the player
		BeaconEnemyToPlayer(myiEnemy);
	//Move towards this player you hate so much
		MoveTowardsBeacon();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Uber wimps just run. No fighty just run.
	Uber wimps always flee.
*/
void LL_BattleEnemy::RunAsUberWimp()
{	//Run run run run run!
		BeaconEnemyToExit();
		Flee();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Wimps attack a random player.
	They flee when they're HP is 50% of their maximum.	
*/
void LL_BattleEnemy::RunAsWimp()
{	//Vars
		double dRand;
		int iLoops = 0;
	
	//If we're damaged to less than 20% of our health or 10hp turn into an uber wimp
		if(HP() < MaxHP() * .5 || HP() < 10)
		{	myiStrategy = LL_MonsterTemplate::STRATEGY_UBER_WIMP;
			return;
		}
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
	//If the player this enemy really hates is dead or nonexistant pick another one randomley
		while(!EnemyExists(myiEnemy) && iLoops < 100)
		{	//Grab a random player to hate
	  			dRand = ((double)rand() / (double)(RAND_MAX+1));
				myiEnemy = dRand * mylpoBattlePlayers->Length();
				iLoops++;
		}
	//Beacon this enemy towards the player
		BeaconEnemyToPlayer(myiEnemy);
	//Move towards this player you hate so much
		MoveTowardsBeacon();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Wimps attack a random player.
	They will always keep their distance when their HP is < 75% of their maximum.
	They flee when they're HP is < 90% of their maximum.
*/
void LL_BattleEnemy::RunAsSmartWimp()
{	//Vars
		double dRand;
		int iLoops = 0;

	//If we're damaged to less than 20% of our health or 10hp turn into an uber wimp
		if(HP() < MaxHP() * .5 || HP() < 10)
		{	myiStrategy = LL_MonsterTemplate::STRATEGY_UBER_WIMP;
			return;
		}
	//If we're damaged to less than 90% of the max then keep distance from the player
		if(HP() < MaxHP() * .9)
		{	if(KeepDistance())
			{	return;
			}
		}
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
	//If the player this enemy really hates is dead or nonexistant pick another one randomley
		while(!EnemyExists(myiEnemy) && iLoops < 100)
		{	//Grab a random player to hate
	  			dRand = ((double)rand() / (double)(RAND_MAX+1));
				myiEnemy = dRand * mylpoBattlePlayers->Length();
				iLoops++;
		}
	//Beacon this enemy towards the player
		BeaconEnemyToPlayer(myiEnemy);
	//Move towards this player you hate so much
		MoveTowardsBeacon();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Aerial attackers attack a random player.
	They flee when they're HP is 20% of their maximum.
	They always will aerial attack
	They always keep their distance
*/
void LL_BattleEnemy::RunAsAerialAttacker()
{	//Vars
		double dRand;
		int iLoops = 0;

	//If we're damaged to less than 20% of our health or 10hp turn into an uber wimp
		if(HP() < MaxHP() * .2 || HP() < 10)
		{	myiStrategy = LL_MonsterTemplate::STRATEGY_UBER_WIMP;
			return;
		}
	//Always keep distance
		if(KeepDistance())
			return;
	//If we can't help being next to a player attack him
		if(AttackIfNextToPlayer())
			return;
	//Hate the enemy with the lowest HP
		myiEnemy = PlayerWithLowestHP();
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Exploiters try to kill the player with the lowest HP
	They flee when they're HP is 20% of their maximum.
*/
void LL_BattleEnemy::RunAsExploiter()
{	//Vars
		double dRand;
		int iLoops = 0;
	
	//If we're damaged to less than 20% of our health or 10hp turn into an uber wimp
		if(HP() < MaxHP() * .2 || HP() < 10)
		{	myiStrategy = LL_MonsterTemplate::STRATEGY_UBER_WIMP;
			return;
		}
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//Choose the player to hate to be the one with the lowest HP
		myiEnemy = PlayerWithLowestHP();
	//Beacon this enemy towards the player
		BeaconEnemyToPlayer(myiEnemy);
	//Move towards this player you hate so much
		MoveTowardsBeacon();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Slackers choose the player with the lowest HP to be beaconed to
	They only move 30% of the time. Slackers
	They never flee (too lazy)
*/
void LL_BattleEnemy::RunAsSlacker()
{	//Vars
		double dRand;
		int iRand;
		int iLoops = 0;
	
	//We don't like the player with the lowest HP
		myiEnemy = PlayerWithLowestHP();
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
	//30% of the time beacon this enemy towards the player
		dRand = ((double)rand() / (double)(RAND_MAX+1));
		iRand = dRand * 100;
		if(iRand < 30)
		{	BeaconEnemyToPlayer(myiEnemy);
			MoveTowardsBeacon();
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Bloodthirsty's always attack
	They never flee, never aerial attack, and never keep distance
*/
void LL_BattleEnemy::RunAsBloodThirsty()
{	//Vars
		double dRand;
		int iLoops = 0;
	
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
	//If the player this enemy really hates is dead or nonexistant pick another one randomley
		while(!EnemyExists(myiEnemy) && iLoops < 100)
		{	//Grab a random player to hate
	  			dRand = ((double)rand() / (double)(RAND_MAX+1));
				myiEnemy = dRand * mylpoBattlePlayers->Length();
				iLoops++;
		}
	//Beacon this enemy towards the player
		BeaconEnemyToPlayer(myiEnemy);
	//Move towards this player you hate so much
		MoveTowardsBeacon();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
/*	Warriors
	Keep distance when they're HP is 20% of their maximum.
	They never flee.
*/
void LL_BattleEnemy::RunAsWarrior()
{	//Vars
		double dRand;
		int iLoops = 0;

	//Keep distance if we're at less then 20% health
		if(HP() < MaxHP() * .2)
		{	if(KeepDistance())
			{	return;
			}
		}
	//If we can attack do so and we're done
		if(AttackIfNextToPlayer())
			return;
	//If we can do an aerial attack we're done
		if(AerialAttack())
			return;
	//If the player this enemy really hates is dead or nonexistant pick another one randomley
		while(!EnemyExists(myiEnemy) && iLoops < 100)
		{	//Grab a random player to hate
	  			dRand = ((double)rand() / (double)(RAND_MAX+1));
				myiEnemy = dRand * mylpoBattlePlayers->Length();
				iLoops++;
		}
	//Beacon this enemy towards the player
		BeaconEnemyToPlayer(myiEnemy);
	//Move towards this player you hate so much
		MoveTowardsBeacon();
}
//P--------------------------------------------------------------------------------- [AI Sub Functions] -P
bool LL_BattleEnemy::AttackIfNextToPlayer()
{	//Check north, south, west, and east to see where that pesky player is hiding.
		if(mypoBattleUnitMap->PlayerOn(X()-1, Y()) != LL_BattleUnitMap::NONE)
		{	AttackTo(X()-1, Y());
			return true;
		}
		else if(mypoBattleUnitMap->PlayerOn(X()+1, Y()) != LL_BattleUnitMap::NONE)
		{	AttackTo(X()+1, Y());
			return true;
		}
		else if(mypoBattleUnitMap->PlayerOn(X(), Y()-1) != LL_BattleUnitMap::NONE)
		{	AttackTo(X(), Y()-1);
			return true;
		}
		else if(mypoBattleUnitMap->PlayerOn(X(), Y()+1) != LL_BattleUnitMap::NONE)
		{	AttackTo(X(), Y()+1);
			return true;
		}
	//Return it
		return false;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
//Move so this battle enemy isn't adjacent to any players. Return true if you moved.
bool LL_BattleEnemy::KeepDistance()
{	//Vars
		ASFC_LinkedList<LL_DistanceInfo> loDirections;
		LL_DistanceInfo toDistance;
		int iLowestCostElement, iLowestCost;
		
	//If there are no player's adjecent here then it's cool, don't move
		if(PlayersAdjacent(myiX, myiY) == 0)
  			return false;
	//Figure out the number of players adjecent to the north, south, west, and east. Sort into a list.
		//North
			if(CanMove(DIR_NORTH))
			{	toDistance.iDirection = DIR_NORTH;
				toDistance.iX = myiX;
				toDistance.iY = myiY - 1;
				toDistance.iCost = PlayersAdjacent(toDistance.iX, toDistance.iY);
				loDirections.Push(toDistance);
			}
		//South
			if(CanMove(DIR_SOUTH))
			{	toDistance.iDirection = DIR_SOUTH;
				toDistance.iX = myiX;
				toDistance.iY = myiY + 1;
				toDistance.iCost = PlayersAdjacent(toDistance.iX, toDistance.iY);
				loDirections.Push(toDistance);
			}
		//West
			if(CanMove(DIR_WEST))
			{	toDistance.iDirection = DIR_WEST;
				toDistance.iX = myiX - 1;
				toDistance.iY = myiY;
				toDistance.iCost = PlayersAdjacent(toDistance.iX, toDistance.iY);
				loDirections.Push(toDistance);
			}
		//East
			if(CanMove(DIR_EAST))
			{	toDistance.iDirection = DIR_EAST;
				toDistance.iX = myiX + 1;
				toDistance.iY = myiY;
				toDistance.iCost = PlayersAdjacent(toDistance.iX, toDistance.iY);
				loDirections.Push(toDistance);
			}
	//Find the element with the lowest cost value
		iLowestCostElement = -1;
		iLowestCost = 0xFF;
		for(int i = 0; i < loDirections.Length(); i++)
		{	if(loDirections[i].iCost < iLowestCost)
			{	iLowestCost = loDirections[i].iCost;
				iLowestCostElement = i;
			}
		}
	//Move in the direction specified by that element
		if(iLowestCostElement >= 0)
		{	Move(loDirections[iLowestCostElement].iDirection);
			return true;
		}
		return false;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
//Return the number of players on (or adjecent to) the tile on iX, iY
int LL_BattleEnemy::PlayersAdjacent(int iX, int iY)
{	//Vars
		int iPlayers = 0;

	//Is a player on this tile
		if(mypoBattleUnitMap->PlayerOn(iX, iY) != LL_BattleUnitMap::NONE)
			iPlayers++;
	//Check N, S, W, E, NW, NE, SW, SE
		if(mypoBattleUnitMap->PlayerOn(iX, iY-1) != LL_BattleUnitMap::NONE)
			iPlayers++;
		if(mypoBattleUnitMap->PlayerOn(iX, iY+1) != LL_BattleUnitMap::NONE)
			iPlayers++;
		if(mypoBattleUnitMap->PlayerOn(iX-1, iY) != LL_BattleUnitMap::NONE)
			iPlayers++;
		if(mypoBattleUnitMap->PlayerOn(iX+1, iY) != LL_BattleUnitMap::NONE)
			iPlayers++;
		if(mypoBattleUnitMap->PlayerOn(iX-1, iY-1) != LL_BattleUnitMap::NONE)
			iPlayers++;
		if(mypoBattleUnitMap->PlayerOn(iX+1, iY-1) != LL_BattleUnitMap::NONE)
			iPlayers++;
		if(mypoBattleUnitMap->PlayerOn(iX-1, iY+1) != LL_BattleUnitMap::NONE)
			iPlayers++;
		if(mypoBattleUnitMap->PlayerOn(iX+1, iY+1) != LL_BattleUnitMap::NONE)
			iPlayers++;
	//Return the # of adjecent players
		return iPlayers;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LL_BattleEnemy::AerialAttack()
{	//If'n we hate no one (You dirty hippy!) or we hate the dead just relax
		if(myiEnemy < 0 || !EnemyExists(myiEnemy))
			return(false);
	//If our hated enemy is within range shoot!
		if(WithinRadius((*mylpoBattlePlayers)[myiEnemy].X(), (*mylpoBattlePlayers)[myiEnemy].Y()))
		{	AttackTo((*mylpoBattlePlayers)[myiEnemy].X(), (*mylpoBattlePlayers)[myiEnemy].Y());
			return true;
		}
	return false;
}	
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LL_BattleEnemy::EnemyExists(int iEnemy)
{	//Check to make sure this enemy exists
		for(int i = 0; i < mylpoBattlePlayers->Length(); i++)
		{	if((*mylpoBattlePlayers)[i].Member()->State() != LL_PartyMember::STATE_DEAD &&
				!(*mylpoBattlePlayers)[i].Escaped())
			{	if((*mylpoBattlePlayers)[i].MemberNum() == iEnemy)
			    {	return(true);
				}
			}
		}
	//If execution get's here this enemy (player) doesn't exist
		return(false);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_BattleEnemy::BeaconEnemyToPlayer(int iPartyMember)
{	//Vars
		int iPlayerNum;
		
	//Grab the player num
		iPlayerNum = PlayerAssociatedToPartyMember(iPartyMember);
		if(iPlayerNum < 0)
			return;
	//Set the beaconning coods
		myiBeaconX = (*mylpoBattlePlayers)[iPlayerNum].X();
		myiBeaconY = (*mylpoBattlePlayers)[iPlayerNum].Y();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_BattleEnemy::BeaconEnemyToExit()
{	//Vars
		int iClosestBorder;
		int iDistance = 1000;

	//Determine which border this enemy is closest too
		//North?, South?, West?, East?
			if(Y() < iDistance)
			{	iDistance = Y();
				myiBeaconBorder = BORDER_NORTH;
			}
			if(PLAYFIELD_TILEHEIGHT - Y() < iDistance)
			{	iDistance = PLAYFIELD_TILEHEIGHT - Y();
				myiBeaconBorder = BORDER_SOUTH;
			}
			if(X() < iDistance)
			{	iDistance = X();
				myiBeaconBorder = BORDER_WEST;
			}
			if(PLAYFIELD_TILEWIDTH - X() < iDistance)
			{	iDistance = PLAYFIELD_TILEWIDTH - X();
				myiBeaconBorder = BORDER_EAST;
			}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_BattleEnemy::PlayerAssociatedToPartyMember(int iMember)
{	//Loop through all players if we find the right member return it's player code
		for(int i = 0; i < mylpoBattlePlayers->Length(); i++)
		{	if((*mylpoBattlePlayers)[i].Member()->State() != LL_PartyMember::STATE_DEAD)
			{	if((*mylpoBattlePlayers)[i].MemberNum() == iMember)
     				return(true);
			}
		}
	return -1;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_BattleEnemy::MoveTowardsBeacon()
{	//Vars
		bool fDone = false;
		double dRand;
		int iRand;
		ASFC_LinkedList<int> liRandomInts;
		ASFC_LinkedList<int> liOrderOfChecks;
		liRandomInts.Push(0);
		liRandomInts.Push(1);
		liRandomInts.Push(2);
		liRandomInts.Push(3);
		
	//Randomize iOrderOfChecks
		while(liRandomInts.Length() > 0)
		{	dRand = ((double)rand() / (double)(RAND_MAX+1));
			iRand = dRand * liRandomInts.Length();
   			if(iRand < liRandomInts.Length())
			{	liOrderOfChecks.Push(liRandomInts[iRand]);
				liRandomInts.Delete(iRand);
			}
		}
	//Take a number out of lOrderOfChecks, check it
		while(liOrderOfChecks.Length() > 0 && !fDone)
		{	//Decide what to do based on this random int
				if(liOrderOfChecks[0] == 0)
				{	if(myiBeaconY < Y())
    					fDone = Move(DIR_NORTH);
				}
				else if(liOrderOfChecks[0] == 1)
				{	if(myiBeaconY > Y())
    					fDone = Move(DIR_SOUTH);
				}
				else if(liOrderOfChecks[0] == 2)
				{	if(myiBeaconX < X())
    					fDone = Move(DIR_WEST);
				}
				else if(liOrderOfChecks[0] == 3)
				{	if(myiBeaconX > X())
    					fDone = Move(DIR_EAST);
				}
			//Delete it
				liOrderOfChecks.Delete(0);
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_BattleEnemy::Flee()
{	//Flee towards the beacon you should flee towards
		switch(myiBeaconBorder)
		{	case BORDER_NORTH:
			{	if(Y() - 1 < myiMapEdgeY)
				{	EventQueue()->EscapeMonster(Off());
					mypoConsole->Write("  Escaped!\n", 1);
					myfFlee = true;
				}
				else
					Move(DIR_NORTH);
			}break;
			case BORDER_SOUTH:
			{	if(Y() + 1 >= myiMapEdgeY + PLAYFIELD_TILEHEIGHT)
				{	EventQueue()->EscapeMonster(Off());
					mypoConsole->Write("  Escaped!\n", 1);
					myfFlee = true;
				}
				else
					Move(DIR_SOUTH);
			}break;
			case BORDER_WEST:
			{	if(X() - 1 < myiMapEdgeX)
				{	EventQueue()->EscapeMonster(Off());
					mypoConsole->Write("  Escaped!\n", 1);
					myfFlee = true;
				}
				else
					Move(DIR_WEST);
			}break;
			case BORDER_EAST:
			{	if(X() + 1 >= myiMapEdgeX + PLAYFIELD_TILEWIDTH - 1)
				{	EventQueue()->EscapeMonster(Off());
					mypoConsole->Write("  Escaped!\n", 1);
					myfFlee = true;
				}
				else
					Move(DIR_EAST);
			}break;
			default: break;
		};
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_BattleEnemy::CheckFlee()
{	//Only check if the player hasn't already fleed
		if(!myfFlee)
		{	if(Y() < myiMapEdgeY)
			{	EventQueue()->EscapeMonster(Off());
				mypoConsole->Write("  Escaped!\n", 1);
			}
			else if(Y() >= myiMapEdgeY + PLAYFIELD_TILEHEIGHT)
			{	EventQueue()->EscapeMonster(Off());
				mypoConsole->Write("  Escaped!\n", 1);
			}
			else if(X() < myiMapEdgeX)
			{	EventQueue()->EscapeMonster(Off());
				mypoConsole->Write("  Escaped!\n", 1);
			}
			else if(X() >= myiMapEdgeX + PLAYFIELD_TILEWIDTH - 1)
			{	EventQueue()->EscapeMonster(Off());
				mypoConsole->Write("  Escaped!\n", 1);
			}
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_BattleEnemy::PlayerWithLowestHP()
{	//Vars
		int iPlayer = -1;
		int iLowestHP = -1;
	//Loop through all players
		for(int i = 0; i < mylpoBattlePlayers->Length(); i++)
		{	if(EnemyExists(i))
			{	//If this player has a lower HP
					if((*mylpoBattlePlayers)[i].HP() < iLowestHP || iLowestHP == -1)
					{	iPlayer   = i;
						iLowestHP = (*mylpoBattlePlayers)[i].HP();
					}
			}
		}
	//Return dis' playa
		return(iPlayer);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int	LL_BattleEnemy::PlayerWithHighestHP()
{	//Vars
		int iPlayer = -1;
		int iHighestHP = -1;
	//Loop through all players
		for(int i = 0; i < mylpoBattlePlayers->Length(); i++)
		{	if(EnemyExists(i))
			{	//If this player has a higher HP
					if((*mylpoBattlePlayers)[i].HP() > iHighestHP || iHighestHP == -1)
					{	iPlayer   = i;
						iHighestHP = (*mylpoBattlePlayers)[i].HP();
					}
			}
		}
	//Return dis' playa
		return(iPlayer);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_BattleEnemy::PlayerWithHighestMP()
{	//Vars
		int iPlayer = -1;
		int iHighestMP = -1;
	//Loop through all players
		for(int i = 0; i < mylpoBattlePlayers->Length(); i++)
		{	if(EnemyExists(i))
			{	//If this player has a higher mp
					if((*mylpoBattlePlayers)[i].MP() > iHighestMP || iHighestMP == -1)
					{	iPlayer   = i;
						iHighestMP = (*mylpoBattlePlayers)[i].MP();
					}
			}
		}
	//Return dis' playa
		return(iPlayer);
}
