/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehiclebattlekeyeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "vehiclebattlekeyeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//										LEDIT_VehicleBattleKeyEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_VehicleBattleKeyEditor::LEDIT_VehicleBattleKeyEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_VehicleBattleKeyEditor::EditVehicleBattleKeys()
{	//Set up the keys
		int iKey;
		ASFC_LinkedList<int> lChoosers;
  		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
		lChoosers.Push(KEY_DELETE);
		lChoosers.Push(KEY_CANCEL);
	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup();

	//Now grab an option
		bool fNotDone = true;
		while(fNotDone)
		{	Setup();
			DrawQuickKeys();
			int iOption = GrabOption(&iKey, lChoosers);
			fNotDone = EditOption(iOption, iKey);
		}
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_VehicleBattleKeyEditor::DrawQuickKeys()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
	mypoPainter->TalkConsole() << "Up:     Move up\n";
	mypoPainter->TalkConsole() << "Down:   Move down\n";
	mypoPainter->TalkConsole() << "Enter:  Edit key\n";
	mypoPainter->TalkConsole() << "Delete: Delete key\n";
	mypoPainter->TalkConsole() << "Escape: Exit\n";
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_VehicleBattleKeyEditor::Setup()
{	//Vars
		string ts;

	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("              Vehicle//Battle Keys");
		Heading("===================================================");
	//Loop through all keys
		for(int i = 0; i < mypoMobilityTerrainMap->NumVehicleBattleKeys(); i++)
		{	ts = mypoSet->Vehicle(mypoMobilityTerrainMap->VehicleBattleKey(i).iVehicleCode1).Identifier();
			ts += " and ";
   			ts += mypoSet->Vehicle(mypoMobilityTerrainMap->VehicleBattleKey(i).iVehicleCode2).Identifier();
	  		Option(ts);
		}
	//Give the option to create a new key
		Option("-- [New Key] --");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_VehicleBattleKeyEditor::EditOption(int iOpt, int iKey)
{	//If the key down is exit escape!!
		if(iKey == KEY_CANCEL)
		{	return false;
		}
	//If the key down is "choose"
		else if(iKey == KEY_CHOOSE || iKey == KEY_CHOOSE2)
		{	//If we selected a key edit it
				if(iOpt != mypoMobilityTerrainMap->NumVehicleBattleKeys())
				{
				cerr << "EK; " << iOpt << endl;
    				EditKey(iOpt);
					return(true);
				}
			//If we have the new key option add a default key
				else
				{	mypoMobilityTerrainMap->AddVehicleBattleKey(0, 1, 0);
					return(true);
				}
		}
	//If we're deleting something
		else if(iKey == KEY_DELETE)
		{	//Check to make sure this key exists, if it does delete it
				if(iOpt < mypoMobilityTerrainMap->NumVehicleBattleKeys())
				{	mypoMobilityTerrainMap->DeleteBattleKey(iOpt);
				}
			return true;
		}
	return(false);
}
//P-------------------------------------------------------------------------------------- [Editting Key] -P
void LEDIT_VehicleBattleKeyEditor::EditKey(int iKey)
{	//Map the key to a pointer
		mypoKey = &mypoMobilityTerrainMap->VehicleBattleKey(iKey);
	//Setup the editor
		DrawInit();
		DrawKeyQuickKeys();
		SetupKey();
	//Now grab an option
		while(EditKeyOption(GrabOption()))
		{	SetupKey();
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_VehicleBattleKeyEditor::DrawKeyQuickKeys()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
	mypoPainter->TalkConsole() << "Up:     Move up\n";
	mypoPainter->TalkConsole() << "Down:   Move down\n";
	mypoPainter->TalkConsole() << "Enter:  Edit value\n";
	mypoPainter->TalkConsole() << "Escape: Exit\n";
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_VehicleBattleKeyEditor::SetupKey()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("              Edit Vehicle\\Battle Keys");
		Heading("===================================================");
		Option ("Vehicle 1:  " + mypoSet->Vehicle(mypoKey->iVehicleCode1).Identifier());
		Option ("Vehicle 2:  " + mypoSet->Vehicle(mypoKey->iVehicleCode2).Identifier());
		Option ("Battle map: " + Val(mypoKey->iBattleMap));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_VehicleBattleKeyEditor::EditKeyOption(int iOpt)
{	//Decide what to do based on what option was selected
		//Vehicle 1
			if(iOpt == OPTION_VEHICLE1)
	  		{	mypoKey->iVehicleCode1 = mypoVehicleSetEditor->GrabVehicle();
	  			return true;
  			}
		//Vehicle 2
			else if(iOpt == OPTION_VEHICLE2)
  			{	mypoKey->iVehicleCode2 = mypoVehicleSetEditor->GrabVehicle();
  				return true;
	  		}
		//Battle map
			else if(iOpt == OPTION_MAP)
			{	mypoKey->iBattleMap = GrabInt("Enter the map number [0-80]", 0, 80);
				return true;
			}

	return false;
}
