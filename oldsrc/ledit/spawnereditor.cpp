/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			armoreditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "spawnereditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_ArmorEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_SpawnerEditor::LEDIT_SpawnerEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_SpawnerEditor::EditSpawner(LL_Spawner* poSpawner)
{	//Set the armor to edit
		mypoSpawner = poSpawner;
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
void LEDIT_SpawnerEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                Spawner Information");
		Heading("===================================================");
	//Monsters
		Heading("-------------------------------------- [Monsters] -");
		for(int i = 0; i < mypoSpawner->Monsters().Length(); i++)
		{	Option
			(	mypoGame->MonsterSet().Monster(mypoSpawner->Monsters()[i]).Identifier()
			);
		}
		Option("-- [New Monster] --");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_SpawnerEditor::EditOption(int i)
{	//If the user wants a new monster
		if(i == NumOptions() - 1)
		{	//Add a new one
				mypoSpawner->Monsters().Resize(mypoSpawner->Monsters().Length() + 1);
				mypoSpawner->Monsters()[mypoSpawner->Monsters().Length() - 1] = 0;
			return(true);
		}
	//If the user selected a monster
		else if(i >= 0)
		{	int ti = mypoMonsterSetEditor->GrabMonster(&mypoGame->MonsterSet(), mypoGame);
			if(ti >= 0)
				mypoSpawner->Monsters()[i] = ti;
			return(true);
		}
	
	return(false);
}
