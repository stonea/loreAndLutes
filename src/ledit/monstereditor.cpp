/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monstereditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "monstereditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_MonsterEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MonsterEditor::LEDIT_MonsterEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_MonsterEditor::EditMonster(LL_MonsterTemplate* poMonster, LL_Game* poGame)
{	//Map vars
		mypoMonster	= poMonster;
		mypoGame	= poGame;
	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup();
	//Now grab an option
		while(EditOption(GrabOption()))
		{	Setup();
		}
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_MonsterEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 	Monster");
		Heading("===================================================");
	//List all the various vars
		Heading("--------------------------------------[Attributes]-");
		Option("Name:           " + mypoMonster->Identifier());
		Option("Image:          " + mypoMonster->Image());
		if(mypoMonster->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Strength:       " + Val(mypoMonster->Strength()));
		Option("Dexterity:      " + Val(mypoMonster->Dexterity()));
		Option("Intelligence:   " + Val(mypoMonster->Intelligence()));
		Option("MP\\Max:         " + Val(mypoMonster->MP()) + " \\ " + Val(mypoMonster->MaxMP()));
		Option("HP\\Max:         " + Val(mypoMonster->HP()) + " \\ " + Val(mypoMonster->MaxHP()));
		Option("Experience:     " + Val(mypoMonster->Experience()));
		Option("Rarity:         " + Val(mypoMonster->Rarity()));
		Option("Vehicle:        " + mypoGame->VehicleSet().Vehicle(
								  mypoMonster->VehicleCode()).Identifier() + " ");
		Heading("------------------------------[Battle Information]-");
		Option("Weapon 1:       " + mypoGame->ItemSet().Weapon(mypoMonster->Weapon1()).Identifier());
		Option("Weapon 2:       " + mypoGame->ItemSet().Weapon(mypoMonster->Weapon2()).Identifier());
		Option("Armor 1:        " + mypoGame->ItemSet().Armor(mypoMonster->Armor1()).Identifier());
		Option("Armor 2:        " + mypoGame->ItemSet().Armor(mypoMonster->Armor2()).Identifier());
		Option("<Strategies>    ");
		Option("Party size min: " + Val(mypoMonster->PartyMin()));
		Option("Party size max: " + Val(mypoMonster->PartyMax()));
		Option("<Friends>       ");
		Heading("--------------------------------------------[Death]-");
		Option("Chest chance:   " + Val(mypoMonster->ChanceOfChest()) + "%");
		Option("Food chance:    " + Val(mypoMonster->ChanceOfFood()) + "%");
		Option("Max food:       " + Val(mypoMonster->MaxFood()));
		Option("<Death Chest>   ");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_MonsterEditor::EditOption(int i)
{	//Vars
		string ts;
		int ti;

	//Do something based on which option was selected
		//- [Name] -
		if(i == EDITOPTION_NAME)
		{	ts = GrabString("Enter the name for this species of monster");
			mypoMonster->SetIdentifier(ts);
			return true;
		}
		//- [Image] -
		else if(i == EDITOPTION_IMAGE)
		{	string s;
			if(mypoMonster->CustomImage())
				s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
			else
				s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
			mypoMonster->SetImage(s);
			return true;
		}
		//- [Custom Image] -
		else if(i == EDITOPTION_CUSTOM_IMAGE)
		{	mypoMonster->SetCustomImage(!mypoMonster->CustomImage());
			return true;
		}
		//- [Strength] -
		else if(i == EDITOPTION_STRENGTH)
		{	ti = GrabInt("Enter the default strength [0-250]", 0, 250);
			mypoMonster->SetStrength(ti);
			return true;
		}
		//- [Dexterity] -
		else if(i == EDITOPTION_DEXTERITY)
		{	ti = GrabInt("Enter the default dexterity [0-250]", 0, 250);
			mypoMonster->SetDexterity(ti);
			return true;
		}
		//- [Intelligence] -
		else if(i == EDITOPTION_INTELLIGENCE)
		{	ti = GrabInt("Enter the default intelligence [0-250]", 0, 250);
			mypoMonster->SetIntelligence(ti);
			return true;
		}
		//- [MP] -
		else if(i == EDITOPTION_MP)
		{	ti = GrabInt("Enter the default MP [0-2000000000]", 0, 2000000000);
			mypoMonster->SetMP(ti);
			ti = GrabInt("Enter the default Max MP [0-2000000000]", 0, 2000000000);
			mypoMonster->SetMaxMP(ti);
			return true;
		}
		//- [HP] -
		else if(i == EDITOPTION_HP)
		{	ti = GrabInt("Enter the default HP [0-2000000000]", 0, 2000000000);
			mypoMonster->SetHP(ti);
			ti = GrabInt("Enter the default Max HP [0-2000000000]", 0, 2000000000);
			mypoMonster->SetMaxHP(ti);
			return true;
		}
		//- [Experience] -
		else if(i == EDITOPTION_EXPERIENCE)
		{	ti = GrabInt("Enter the default Experience [0-2000000000]", 0, 2000000000);
			mypoMonster->SetExperience(ti);
			return true;
		}
		//- [Weapon 1] -
		else if(i == EDITOPTION_WEAPON1)
		{	int ti = mypoItemSetEditor->GetWeapon(&mypoGame->ItemSet());
			mypoMonster->SetWeapon1(ti);
			return true;
		}
		//- [Weapon 2] -
		else if(i == EDITOPTION_WEAPON2)
		{	int ti = mypoItemSetEditor->GetWeapon(&mypoGame->ItemSet());
			mypoMonster->SetWeapon2(ti);
			return true;
		}
		//- [Armor 1] -
		else if(i == EDITOPTION_ARMOR1)
		{	int ti = mypoItemSetEditor->GetArmor(&mypoGame->ItemSet());
			mypoMonster->SetArmor1(ti);
			return true;
		}
		//- [Armor 2] -
		else if(i == EDITOPTION_ARMOR2)
		{	int ti = mypoItemSetEditor->GetArmor(&mypoGame->ItemSet());
			mypoMonster->SetArmor2(ti);
			return true;
		}
		//- [Vehicle] -
		else if(i == EDITOPTION_VEHICLE)
		{	ti = mypoVehicleSetEditor->GrabVehicle();
			mypoMonster->SetVehicleCode(ti);
			return true;
		}
		//- [Rarity] -
		else if(i == EDITOPTION_RARITY)
		{	ti = GrabInt("Enter the default MP [0-100]", 0, 100);
			mypoMonster->SetRarity(ti);
			return true;
		}
		//- [Death Chest] -
		else if(i == EDITOPTION_DEATH_CHEST)
		{	mypoChestEditor->EditChest(&mypoMonster->DeathChest());
  			return true;
		}
		//- [Strategies] -
		else if(i == EDITOPTION_STRATEGIES)
		{	EditStrategies();
			return true;
		}
		//- [Party size min] -
		else if(i == EDITOPTION_PARTSIZE_MIN)
		{	ti = GrabInt("Enter the minimum party size [1-100]", 1, 100);
			mypoMonster->SetPartyMin(ti);
			return true;
		}
		//- [Party size max] -
		else if(i == EDITOPTION_PARTSIZE_MAX)
		{	ti = GrabInt("Enter the maximum party size [1-100]", 1, 100);
			mypoMonster->SetPartyMax(ti);
			return true;
		}
		//- [Friends] -
		else if(i == EDITOPTION_FRIENDS)
		{	mypoFriendEditor->EditFriend(mypoMonster);
			return true;
		}
		//- [Chest chance] -
		else if(i == EDITOPTION_CHEST_CHANCE)
		{	ti = GrabInt("Enter the chance of death chest appearance [0-100]", 0, 100);
			mypoMonster->SetChanceOfChest(ti);
			return true;
		}
		//- [Food chance] -
		else if(i == EDITOPTION_FOOD_CHANCE)
		{	ti = GrabInt("Enter the chance of food appearance if guts [0-100]", 0, 100);
			mypoMonster->SetChanceOfFood(ti);
			return true;
		}
		//- [Max food] -
		else if(i == EDITOPTION_MAX_FOOD)
		{	ti = GrabInt("Enter the maximum amount of food in guts [0-2000000000]", 0, 2000000000);
			mypoMonster->SetMaxFood(ti);
			return true;
		}
		
	return false;
}
//P---------------------------------------------------------------------------------- [Strategy ditting] -P
void LEDIT_MonsterEditor::EditStrategies()
{	//Set up the keys
		int iKey;
		bool fNotDone = true;
		ASFC_LinkedList<int> lChoosers;
  		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
		lChoosers.Push(KEY_DELETE);
		lChoosers.Push(KEY_CANCEL);
	//Setup the editor
		DrawInit();
		DrawStrategyQuickKeys();
		SetupStrategies();
	//Now grab an option
		while(fNotDone)
		{	SetupStrategies();
			DrawStrategyQuickKeys();
			int iOption = GrabOption(&iKey, lChoosers);
			fNotDone = EditStrategy(iOption, iKey);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_MonsterEditor::DrawStrategyQuickKeys()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole() << "Up:     Move up\n";
	mypoPainter->TalkConsole() << "Down:   Move down\n";
	mypoPainter->TalkConsole() << "Delete: Remove Entry\n";
	mypoPainter->TalkConsole() << "Enter:  Change Value\n";
	mypoPainter->TalkConsole() << "Escape: Exit\n";
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_MonsterEditor::SetupStrategies()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 	Strategies");
		Heading("===================================================");
	//List all the various vars
		for(int i = 0; i < mypoMonster->Strategies().Length(); i++)
		{	switch(mypoMonster->Strategies()[i])
			{	case LL_MonsterTemplate::STRATEGY_IDIOT:
				{	Option("Idiot");
				}break;
				case LL_MonsterTemplate::STRATEGY_NORMAL:
				{	Option("Normal");
				}break;
				case LL_MonsterTemplate::STRATEGY_UBER_WIMP:
				{	Option("Uber wimp");
				}break;
				case LL_MonsterTemplate::STRATEGY_WIMP:
				{	Option("Wimp");
				}break;
				case LL_MonsterTemplate::STRATEGY_SMART_WIMP:
				{	Option("Smart wimp");
				}break;
				case LL_MonsterTemplate::STRATEGY_AERIAL_ATTACKER:
				{	Option("Aerial attacker");
				}break;
				case LL_MonsterTemplate::STRATEGY_EXPLOITER:
				{	Option("Exploiter");
				}break;
				case LL_MonsterTemplate::STRATEGY_SLACKER:
				{	Option("Slacker");
				}break;
				case LL_MonsterTemplate::STRATEGY_BLOODTHIRSTY:
				{	Option("Bloodthirsty");
				}break;
				case LL_MonsterTemplate::STRATEGY_WARRIOR:
				{	Option("Warrior");
				}break;
				default:
				{	Option("ERR: That strategy is whack!");
				}break;
			}
		}
	//The obligatory make new strategy option
		Option("-- [New Strategy] --");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_MonsterEditor::EditStrategy(int i, int iKey)
{	//If the key down is exit escape!!
		if(iKey == KEY_CANCEL)
		{	return false;
		}
	//If the key down is "choose"
		else if(iKey == KEY_CHOOSE || iKey == KEY_CHOOSE2)
		{	//If we selected an option change it
				if(i < mypoMonster->Strategies().Length() & i >= 0)
				{	int(mypoMonster->Strategies()[i])++;
					if(int(mypoMonster->Strategies()[i]) >= LL_MonsterTemplate::STRATEGY_NUM_STRATGIES)
					{	mypoMonster->Strategies()[i] = LL_MonsterTemplate::LL_Strategy(0);
					}
					return true;
				}
			//If we need to create a new strategy create it
				if(i == mypoMonster->Strategies().Length())
				{	mypoMonster->Strategies().Push(LL_MonsterTemplate::STRATEGY_IDIOT);
					return true;
				}
 		}
	//If we be a deletin'
		else if(iKey == KEY_DELETE)
		{	//If we selected an option kill it
				if(i < mypoMonster->Strategies().Length() & i >= 0)
				{	mypoMonster->Strategies().Delete(i);
					return true;
				}
		}
		
	return false;
}
