/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			playerseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "playerseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//										 LEDIT_PlayerSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_PlayerSetEditor::LEDIT_PlayerSetEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_PlayerSetEditor::EditPlayerSet(LL_PlayerSet* poSet, LL_Game* poGame)
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
int LEDIT_PlayerSetEditor::GrabPlayer(LL_PlayerSet* poSet, LL_Game* poGame)
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
void LEDIT_PlayerSetEditor::Setup(bool fNewPlayerOption)
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Player Set");
		Heading("===================================================");
	//List the Players
		for(int i = 0; i < mypoSet->NumPlayers(); i++)
			Option(mypoSet->Player(i).Name());
	//And display the "new player" option
		if(fNewPlayerOption)
			Option("-- [New Player] --");
}
//... ... ... ... 	... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LEDIT_PlayerSetEditor::EditOption(int i)
{	//Edit this player (if the user selected a player)
		if(i >= 0 && i < mypoSet->NumPlayers())
		{	mypoPlayerEdit->EditPlayer(&mypoSet->Player(i), mypoGame);
			return true;
		}
	//If the user wants a new player
		if(i == mypoSet->NumPlayers())
		{	NewPlayer();
			return true;
		}
	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_PlayerSetEditor::NewPlayer()
{	//Vars
		string sIdentifier;

	//Ask for an identifier
		mypoPainter->MainConsole().Write("===================================================", 2);
		mypoPainter->MainConsole().CurrentFont(0);
		mypoPainter->MainConsole() << "What shall this new player be called?\n";
		mypoPainter->MainConsole().CurrentFont(1);
		mypoPainter->MainConsole() << ">";
		mypoPainter->MainConsole() >> sIdentifier;
				
     //Create a new Playerw
		LL_PartyMemberTemplate toPlayer;
		toPlayer.SetName(sIdentifier);
		mypoSet->AddPlayer(toPlayer);
}
