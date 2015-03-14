/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			playereditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "playereditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_PlayerEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_PlayerEditor::LEDIT_PlayerEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_PlayerEditor::EditPlayer(LL_PartyMemberTemplate* poPlayer, LL_Game* poGame)
{	//Map vars
		mypoPlayer	= poPlayer;
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
void LEDIT_PlayerEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 	Player");
		Heading("===================================================");
	//List all the various vars
		Heading("--------------------------------------[Attributes]-");
		Option("Name:           " + mypoPlayer->Name());
		Option("Image:          " + mypoPlayer->Image());
//		if(mypoPlayer->CustomImage()) Option("Using image from custom set");
//		else Option("Using image from default set");
		Option("ERR: PROGRAM IN CUSTOM IMAGE"); //!!!
		Option("Strength:       " + Val(mypoPlayer->Strength()));
		Option("Dexterity:      " + Val(mypoPlayer->Dexterity()));
		Option("Intelligence:   " + Val(mypoPlayer->Intelligence()));
		Option("MP\\Max:         " + Val(mypoPlayer->MP()) + " \\ " + Val(mypoPlayer->MaxMP()));
		Option("HP\\Max:         " + Val(mypoPlayer->HP()) + " \\ " + Val(mypoPlayer->MaxHP()));
		Option("Experience:     " + Val(mypoPlayer->Experience()));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_PlayerEditor::EditOption(int i)
{	//Vars
		string ts;
		int ti;

	//Do something based on which option was selected
		//- [Name] -
		if(i == EDITOPTION_NAME)
		{	ts = GrabString("Enter the name for this species of player");
			mypoPlayer->SetName(ts);
			return true;
		}
		//- [Image] -
		if(i == EDITOPTION_IMAGE)
		{	ts = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
			mypoPlayer->SetImage(ts);
			return true;
		}
		//- [Strength] -
		else if(i == EDITOPTION_STRENGTH)
		{	ti = GrabInt("Enter the default strength [0-100]", 0, 100);
			mypoPlayer->SetStrength(ti);
			return true;
		}
		//- [Dexterity] -
		else if(i == EDITOPTION_DEXTERITY)
		{	ti = GrabInt("Enter the default dexterity [0-100]", 0, 100);
			mypoPlayer->SetDexterity(ti);
			return true;
		}
		//- [Intelligence] -
		else if(i == EDITOPTION_INTELLIGENCE)
		{	ti = GrabInt("Enter the default intelligence [0-100]", 0, 100);
			mypoPlayer->SetIntelligence(ti);
			return true;
		}
		//- [MP] -
		else if(i == EDITOPTION_MP)
		{	ti = GrabInt("Enter the default MP [0-2000000000]", 0, 2000000000);
			mypoPlayer->SetMP(ti);
			ti = GrabInt("Enter the default Max MP [0-2000000000]", 0, 2000000000);
			mypoPlayer->SetMaxMP(ti);
			return true;
		}
		//- [HP] -
		else if(i == EDITOPTION_HP)
		{	ti = GrabInt("Enter the default HP [0-2000000000]", 0, 2000000000);
			mypoPlayer->SetHP(ti);
			ti = GrabInt("Enter the default Max HP [0-2000000000]", 0, 2000000000);
			mypoPlayer->SetMaxHP(ti);
			return true;
		}
		//- [Experience] -
		else if(i == EDITOPTION_EXPERIENCE)
		{	ti = GrabInt("Enter the default Experience [0-2000000000]", 0, 2000000000);
			mypoPlayer->SetExperience(ti);
			return true;
		}

	return false;
}
