/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mobilityeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "mobilityeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_MobilityEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MobilityEditor::LEDIT_MobilityEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_MobilityEditor::EditMobility(LL_Mobility* poMobility)
{	mypoMobility = poMobility;

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
void LEDIT_MobilityEditor::Setup()
{	//Clear the old editor
		Reset(false);
		
	//Draw info
		Heading("                 Mobility Information");
		Heading("===================================================");
		Heading("---------------------------------------- [Select] -");
		Option("Select All");
		Option("Deselect All");
		Heading("------------------------------------------- [In] -");
		Option("In  North         " + YesOrNo(mypoMobility->InNorth()));
		Option("    South         " + YesOrNo(mypoMobility->InSouth()));
		Option("    West          " + YesOrNo(mypoMobility->InWest()));
		Option("    East          " + YesOrNo(mypoMobility->InEast()));
		Heading("------------------------------------------ [Out] -");
		Option("Out North         " + YesOrNo(mypoMobility->OutNorth()));
		Option("    South         " + YesOrNo(mypoMobility->OutSouth()));
		Option("    West          " + YesOrNo(mypoMobility->OutWest()));
		Option("    East          " + YesOrNo(mypoMobility->OutEast()));
		Heading("---------------------------------------- [Misc.] -");
		Option("Normal Ticks:     " + Val(mypoMobility->NormalTicks()));
		Option("Damage:           " + Val(mypoMobility->Damage()));
		Option("Chance o' Damage: " + Val(mypoMobility->DamageChance()));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_MobilityEditor::EditOption(int i)
{	//Decide what to do based on i
		if(i == EDITOPTION_SELECT_ALL)
		{	mypoMobility->SetInNorth (true);
			mypoMobility->SetInSouth (true);
			mypoMobility->SetInWest  (true);
			mypoMobility->SetInEast  (true);
			mypoMobility->SetOutNorth(true);
			mypoMobility->SetOutSouth(true);
			mypoMobility->SetOutWest (true);
			mypoMobility->SetOutEast (true);
			return(true);
		}
		if(i == EDITOPTION_DESELECT_ALL)
		{	mypoMobility->SetInNorth (false);
			mypoMobility->SetInSouth (false);
			mypoMobility->SetInWest  (false);
			mypoMobility->SetInEast  (false);
			mypoMobility->SetOutNorth(false);
			mypoMobility->SetOutSouth(false);
			mypoMobility->SetOutWest (false);
			mypoMobility->SetOutEast (false);
			return(true);
		}
		if(i ==	EDITOPTION_IN_NORTH)
		{	mypoMobility->SetInNorth(!mypoMobility->InNorth());
			return(true);
		}
		if(i ==	EDITOPTION_IN_SOUTH)
		{	mypoMobility->SetInSouth(!mypoMobility->InSouth());
			return(true);
		}		
		if(i ==	EDITOPTION_IN_WEST)
		{	mypoMobility->SetInWest(!mypoMobility->InWest());
			return(true);
		}
		if(i ==	EDITOPTION_IN_EAST)
		{	mypoMobility->SetInEast(!mypoMobility->InEast());
			return(true);
		}
		if(i ==	EDITOPTION_OUT_NORTH)
		{	mypoMobility->SetOutNorth(!mypoMobility->OutNorth());
			return(true);
		}
		if(i ==	EDITOPTION_OUT_SOUTH)
		{	mypoMobility->SetOutSouth(!mypoMobility->OutSouth());
			return(true);
		}
		if(i ==	EDITOPTION_OUT_WEST)
		{	mypoMobility->SetOutWest(!mypoMobility->OutWest());
			return(true);
		}
		if(i ==	EDITOPTION_OUT_EAST)
		{	mypoMobility->SetOutEast(!mypoMobility->OutEast());
			return(true);
		}
		if(i ==	EDITOPTION_NORMAL_TICKS)
		{	int ti = GrabInt("Enter the new # of ticks for this mobility [0-255]", 0, 255);
			mypoMobility->SetNormalTicks(ti);
 			return(true);
		}
		if(i ==	EDITOPTION_DAMAGE)
		{	int ti = GrabInt("Enter the amount of damage for this mobility [0-255]", 0, 255);
			mypoMobility->SetDamage(ti);
 			return(true);
		}
		if(i ==	EDITOPTION_CHANCE_OF_DAMAGE)
		{	int ti = GrabInt("Enter the % chance of damage for this mobility [0-100]", 0, 100);
			mypoMobility->SetDamageChance(ti);
 			return(true);
		}
		if(i ==	EDITOPTION_NUM_OPTIONS)
		{
		}
		
	//Return to stop
		return(false);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Returns "Yes" if the bool is true, else "No"
string LEDIT_MobilityEditor::YesOrNo(bool f)
{	if(f)
		return("Yes");
	else
		return("No");
}
