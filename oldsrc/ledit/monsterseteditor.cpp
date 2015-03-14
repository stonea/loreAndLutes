/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monsterseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "monsterseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//										 LEDIT_MonsterSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MonsterSetEditor::LEDIT_MonsterSetEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_MonsterSetEditor::EditMonsterSet(LL_MonsterSet* poSet, LL_Game* poGame)
{	//Map vars
		mypoSet  = poSet;
		mypoGame = poGame;
	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup(true);
	//Now grab an option
		while(EditOption(GrabOption()))
		{	Setup(true);
		}
}
//... ... ... ... 	... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LEDIT_MonsterSetEditor::GrabMonster(LL_MonsterSet* poSet, LL_Game* poGame)
{	//Map vars
		mypoSet  = poSet;
		mypoGame = poGame;
	//Setup the editor
		DrawInit();
		Setup(false);
	//Now grab an option
		return(GrabOption());
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_MonsterSetEditor::Setup(bool fNewMonsterOption)
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Monster Set");
		Heading("===================================================");
	//List the monsters
		for(int i = 0; i < mypoSet->NumMonsters(); i++)
			Option(mypoSet->Monster(i).Identifier());
	//And display the "new monster" option
		if(fNewMonsterOption)
			Option("-- [New Monster] --");
}
//... ... ... ... 	... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LEDIT_MonsterSetEditor::EditOption(int i)
{	//Edit this monster (if the user selected a monster)
		if(i >= 0 && i < mypoSet->NumMonsters())
		{	mypoMonsterEdit->EditMonster(&mypoSet->Monster(i), mypoGame);
			return true;
		}
	//If the user wants a new monster
		if(i == mypoSet->NumMonsters())
		{	NewMonster();
			return true;
		}
	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MonsterSetEditor::NewMonster()
{	//Vars
		string sIdentifier;

	//Ask for an identifier
		mypoPainter->MainConsole().Write("===================================================", 2);
		mypoPainter->MainConsole().CurrentFont(0);
		mypoPainter->MainConsole() << "What shall this new monster be called?\n";
		mypoPainter->MainConsole().CurrentFont(1);
		mypoPainter->MainConsole() << ">";
		mypoPainter->MainConsole() >> sIdentifier;
				
     //Create a new monsterw
		LL_MonsterTemplate toMonster;
		toMonster.SetIdentifier(sIdentifier);
		mypoSet->AddMonster(toMonster);
}
