/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			friendeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "friendeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LEDIT_FriendEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_FriendEditor::LEDIT_FriendEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_FriendEditor::EditFriend(LL_MonsterTemplate* poTemplate)
{	//Set the friend to edit
		mypoTemplate = poTemplate;
	//Set up the keys
		int iKey;
		bool fNotDone = true;
		ASFC_LinkedList<int> lChoosers;
  		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
		lChoosers.Push(KEY_DELETE);
		lChoosers.Push(KEY_CANCEL);
	//Setup the editor
		DrawInit();
		DrawFriendQuickKeys();
		Setup();
	//Now grab an option
		while(fNotDone)
		{	Setup();
			DrawFriendQuickKeys();
			int iOption = GrabOption(&iKey, lChoosers);
			fNotDone = EditOption(iOption, iKey);
		}
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_FriendEditor::Setup()
{	//Vars
		string ts;
	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Friends Editor");
		Heading("===================================================");
	//Loop through all existing friends
		for(int i = 0; i < mypoTemplate->NumFriends(); i++)
		{	ts = mypoGame->MonsterSet().Monster(mypoTemplate->Friend(i)).Identifier();
			ts += " ";
			ts += Val(mypoTemplate->FriendChance(i));
			ts += "%";
			Option(ts);
		}
	//Do the obligatory new friend option
		Option("-- [New friend] --");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_FriendEditor::EditOption(int i, int iKey)
{	//If the key down is exit escape!!
		if(iKey == KEY_CANCEL)
		{	return false;
		}
	//If the key down is "choose"
		else if(iKey == KEY_CHOOSE || iKey == KEY_CHOOSE2)
		{	//If we choosed a friend edit it
				if(i < mypoTemplate->NumFriends())
				{	EditSpecificFriend(i);
					return(true);
				}
  			//If we selected the new friend option make a new friend
				else
				{	NewFriend();
					return(true);
				}
		}
	//If the key was delete
		else if(iKey == KEY_DELETE)
		{	//If we selected a friend remove it
				if(i < mypoTemplate->NumFriends())
				{	mypoTemplate->DeleteFriend(i);
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_FriendEditor::NewFriend()
{	//Vars
		int iMonster, iChance;
		
	//Grab monster and chance values
		iMonster = MonsterPick();
		iChance = GrabInt("Enter the chance of friends appearance [0-100]", 0, 100);
	//Create this friend
		mypoTemplate->AddFriend(iMonster, iChance);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_FriendEditor::DrawFriendQuickKeys()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
	mypoPainter->TalkConsole() << "Up:     Move up\n";
	mypoPainter->TalkConsole() << "Down:   Move down\n";
	mypoPainter->TalkConsole() << "Delete: Remove Entry\n";
	mypoPainter->TalkConsole() << "Enter:  Change Value\n";
	mypoPainter->TalkConsole() << "Escape: Exit\n";
}
//P------------------------------------------------------------------------------------- [Monster Pick] -P
int LEDIT_FriendEditor::MonsterPick()
{	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		SetupMonsterPick();
	//Now grab an option
		return(GrabOption());
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_FriendEditor::SetupMonsterPick()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Monster Set");
		Heading("===================================================");
	//List the monsters
		for(int i = 0; i < mypoGame->MonsterSet().NumMonsters(); i++)
			Option(mypoGame->MonsterSet().Monster(i).Identifier());
}
//P---------------------------------------------------------------------------------- [Specific Friend] -P
int LEDIT_FriendEditor::EditSpecificFriend(int iFriendNum)
{	//Map vars
		myiFriendNum = iFriendNum;
	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		SetupSpecificFriend();
	//Now grab an option
		while(EditSpecificFriendOption(GrabOption()))
		{	SetupSpecificFriend();
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_FriendEditor::SetupSpecificFriend()
{	//Vars
		string ts;

	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Friend Options");
		Heading("===================================================");
	//List the options
		ts =  "Monster: ";
		ts += mypoGame->MonsterSet().Monster(mypoTemplate->Friend(myiFriendNum)).Identifier();
		Option(ts);
		ts =  "Chance:  ";
		ts += Val(mypoTemplate->FriendChance(myiFriendNum));
		ts += "%";
		Option(ts);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_FriendEditor::EditSpecificFriendOption(int i)
{	//Vars
		int iMonster, iChance;
	
	//Do something based on which option was selected
		//- [Monster] -
		if(i == OPTION_MONSTER)
		{	iMonster = MonsterPick();
			mypoTemplate->SetFriend(myiFriendNum, iMonster);
			return true;
		}
		//- [Chance] -
		else if(i == OPTION_CHANCE)
		{	iChance = GrabInt("Enter the chance of friends appearance [0-100]", 0, 100);
			mypoTemplate->SetFriendChance(myiFriendNum, iChance);
			return true;
		}
		
	return false;
}
