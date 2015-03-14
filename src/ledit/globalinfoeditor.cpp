/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			globalinfoeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "globalinfoeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_GlobalInfoEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_GlobalInfoEditor::LEDIT_GlobalInfoEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_GlobalInfoEditor::EditInfo()
{	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup();

	//Now grab an option
		while(EditOption(GrabOption()))
		{	Setup();
		}
}
//P------------------------------------------------------------------------------------------- [Editting] -P
void LEDIT_GlobalInfoEditor::Setup()
{	//Clear the old editor
		Reset(false);
	Heading("                 Global Information");
	Heading("===================================================");
	Option ("Start map:   " + mypoMapSet->MapName(mypoGame->StartMap()));
	Option ("Death map:   " + mypoMapSet->MapName(mypoGame->DeathMap()));
	if(mypoGame->InitialPlayer() < 0 || mypoGame->InitialPlayer() >= mypoGame->PlayerSet().NumPlayers())
		Option("Player:      ERR: INVALID PLAYER");
	else
		Option ("Player:      " + mypoGame->PlayerSet().Player(mypoGame->InitialPlayer()).Name());
	Heading("--------------------------------- [Camp Settings] -");
	Option("Chance of heal: " + Val(mypoGame->ChanceOfHealInCamp()));
	Option("Amount of heal: " + Val(mypoGame->AmountOfHealInCamp())); 
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
bool LEDIT_GlobalInfoEditor::EditOption(int i)
{	//Decide what to do based on i
		if(i == EDITOPTION_START_MAP)
		{	int ti = mypoMapSetEdit->GrabMap(mypoMapSet);
			mypoGame->SetStartMap(ti);
			return(true);
		}
		else if(i == EDITOPTION_DEATH_MAP)
		{	int ti = mypoMapSetEdit->GrabMap(mypoMapSet);
			mypoGame->SetDeathMap(ti);
			return(true);
		}
		else if(i == EDITOPTION_PLAYER)
		{	int ti = mypoPlayerSetEdit->GrabPlayer(&mypoGame->PlayerSet(), mypoGame);
			mypoGame->SetInitialPlayer(ti);
			return(true);
		}
		else if(i == EDITOPTION_HEAL_CHANCE)
		{	int ti = GrabInt("Enter the % chance of healing per hour [0-100]", 0, 100);
			mypoGame->SetChanceOfHealInCamp(ti);
			return(true);
		}
		else if(i == EDITOPTION_HEAL_AMOUNT)
		{	int ti = GrabInt("Enter the amount ot heal [0-9999]", 0, 9999);
			mypoGame->SetAmountOfHealInCamp(ti);
			return(true);
		}

	//We  done
		return false;
}

