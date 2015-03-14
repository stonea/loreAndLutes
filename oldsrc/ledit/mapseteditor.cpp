/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "mapseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_MapSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MapSetEditor::LEDIT_MapSetEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
int	LEDIT_MapSetEditor::GrabMap(LL_MapSet* poMapSet)
{	//Map vars
		mypoMapSet = poMapSet;
		
	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup(false);

	//Now grab an option
		return(GrabOption());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LEDIT_MapSetEditor::EditMapSet(LL_MapSet* poMapSet)
{	//Vars
		int iMap = -1;
		bool fNotDone = true;
		
	//Map vars
		mypoMapSet = poMapSet;
		
	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup(true);

	//Now grab an option
		while(fNotDone)
		{	iMap	 = GrabOption();
			fNotDone = EditOption(&iMap);
		}
		
	//return iMap
		return(iMap);
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_MapSetEditor::Setup(bool fNewMapOption)
{	//Clear out old data
		Reset(false);

	//Write the heading
		Heading("                 Game Map Set");
		Heading("===================================================");
	
	//Display all those neato maps as options
		for(int i = 0; i < mypoMapSet->NumMaps(); i++)
		{	Option("<" + Val(i) + "> " + mypoMapSet->MapName(i));
		}
		
	//Display other options (if we should display them)
		if(fNewMapOption)
			Option("-- [New Map] --");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_MapSetEditor::EditOption(int* pi)
{	//If we should make a new map
		if(*pi == mypoMapSet->NumMaps())
		{	string ts = "";
			while(ts == "")
	  			ts = GrabString("Enter the description for this new map:");
	  			
			//Figure out the new maps file name
				string sFileName = "map" + Val(mypoMapSet->NumMaps()) + ".map";
			
     		//Add a new map
       			mypoMapSet->AddMap(sFileName, ts);
       			
			//Change the recognized option to the special "new map" code
				*pi = NEW_MAP;
		}
		
	//We're always done
		return(false);
}
