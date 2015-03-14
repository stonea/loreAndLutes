/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terraineditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "terraineditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_TerrainEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_TerrainEditor::LEDIT_TerrainEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_TerrainEditor::EditTerrain(LL_Terrain* poTerrain, LL_Game* poGame)
{	//Set the terrain to edit
		mypoTerrain	= poTerrain;
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
void LEDIT_TerrainEditor::Setup()
{	//Vars
		string sColorRed, sColorBlue, sColorGreen;
		char str[100];
			
	//Clear the old editor
		Reset(false);
		
	//Figure out the color messages
		sprintf(str, "%d", mypoTerrain->ColorRed());
		sColorRed	= "Color Red:   ";
  		sColorRed += str;
		sprintf(str, "%d", mypoTerrain->ColorGreen());
		sColorGreen	= "Color Green: ";
		sColorGreen += str;
		sprintf(str, "%d", mypoTerrain->ColorBlue());
		sColorBlue	= "Color Blue:  ";
  		sColorBlue  += str;
   	
	//Draw info
		Heading("                 Terrain Information:");
		Heading("===================================================");
		Heading("----------------------------------------[Graphics]-");
		Option("Image: " + mypoTerrain->ImageFile());
		if(mypoTerrain->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image");
		Option(sColorRed);
		Option(sColorGreen);
		Option(sColorBlue);
		Option("Light: " + LightEffect(mypoTerrain->LightEffect()));
		Heading("------------------------------------------[Misc.]-");
		Option("Battle Map: " + Val(mypoTerrain->BattleMap()));
		Option("Group: " + mypoTerrain->Group());
		Option("Descr: " + mypoTerrain->Info());
		Heading("-------------------------------------[Mobilities]-");
		MobilityOptions();
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Draws (as options) all the mobilities for direction iDir
void LEDIT_TerrainEditor::MobilityOptions()
{	//vars
		string sToWrite;
	
	//Loop through all vehicles
		for(int i = 0; i < mypoGame->VehicleSet().NumVehicles(); i++)
		{	//Set sToWrite equal to the vehicle name and how its mobility is set
				sToWrite = "<";
	  			sToWrite +=  mypoGame->VehicleSet().Vehicle(i).Identifier() + " ";
	  			sToWrite += mypoMobilityTerrainMap->Mobility(mypoTerrain->Code(), i).Description();
	  			sToWrite += ">";

			//Now write this as an option
				Option(sToWrite);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Decides what to do when option i is selecteds, returns whether we should keep edittin'
bool LEDIT_TerrainEditor::EditOption(int i)
{	//Const
		const int FONT_HIGHLIGHT = 2;
	//Vars
		string s;
		LL_Mobility toMobility;
		int iVehicle;

	//Decide what to edit based on i
	if(i == EDITOPTION_IMAGE)
 	{	if(mypoTerrain->CustomImage())
			s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
		else
			s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
		mypoTerrain->LoadAnimation(s, mypoGame->GraphicsDir());
 		return(true);
 	}
	else if(i == EDITOPTION_CUSTOM_IMAGE)
	{	string s;
		s = mypoTerrain->ImageFile();
		mypoTerrain->SetCustomImage(!mypoTerrain->CustomImage());
		if(!mypoTerrain->AnimationExists(mypoGame->GraphicsDir()))
		{	if(mypoTerrain->CustomImage())
				s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
			else
				s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
		}
		mypoTerrain->LoadAnimation(s, mypoGame->GraphicsDir());
		return true;
	}
	else if(i == EDITOPTION_EDITIMAGE)
	{	//Determine how we would execute a generic "edit this image" command in a console
/*			s = mypoEditingInfo->GraphicsProgram() + " " + GetOSDir(mypoEditingInfo->LoreDir() + "/" +
   				ImageFile());
		//Now edit it
			system(s.c_str());
		//Wait for the user to enter a key
			mypoEditingInfo->MainConsole().Clear();
			mypoEditingInfo->MainConsole().Write(	"Press return when you\'re done edittin\'",
   													FONT_HIGHLIGHT, - 1);
			mypoEditingInfo->MainConsole().Draw();
			Update();
			while(mypoEditingInfo->Input().KeyUp(SDLK_RETURN)) {mypoEditingInfo->Input().Update();}
		//Reload the image
			LoadImage(ImageFile(), TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
!!!	*/			
		return(true);
	}
	else if(i == EDITOPTION_COLORRED)
	{	int ti = GrabInt("Enter the new value for red [0-255]", 0, 255);
		mypoTerrain->SetColorRed(ti);
 		return(true);
 	}
	else if(i == EDITOPTION_COLORGREEN)
 	{	int ti = GrabInt("Enter the new value for green [0-255]", 0, 255);
		mypoTerrain->SetColorGreen(ti);
 		return(true);
  	}
	else if(i == EDITOPTION_COLORBLUE)
	{	int ti = GrabInt("Enter the new value for blue [0-255]", 0, 255);
		mypoTerrain->SetColorBlue(ti);
 		return(true);
  	}
	else if(i == EDITOPTION_LIGHT)
	{	if(mypoTerrain->LightEffect()+1 < LIGHTEFFECT_NONE ||
 		   mypoTerrain->LightEffect()+1 >= LIGHEFFECT_MAX)
  		{
			mypoTerrain->SetLightEffect(LIGHTEFFECT_NONE);
		}
		else
			mypoTerrain->SetLightEffect(LL_LIGHTEFFECT(int(mypoTerrain->LightEffect()+1)));
				
		return(true);
	}
	else if(i == EDITOPTION_BATTLE_MAP)
	{	int ti = GrabInt("Enter the new battle map [0-81]", 0, 81);
		mypoTerrain->SetBattleMap(ti);
 		return(true);
	}
	else if(i == EDITOPTION_DESCRIPTION)
	{	string ts = GrabString("Enter the new description");
		mypoTerrain->SetInfo(ts);
 		return(true);
	}
	else if(i == EDITOPTION_GROUP)
	{	string ts = GrabString("Enter the new group");
		ts = UpperString(ts);
		mypoTerrain->SetGroup(ts);
		return(true);
	}
	else if(i > EDITOPTION_DESCRIPTION && i < NumOptions())
	{	//Edit this mobility thingy
			mypoMobilityEditor->EditMobility(
				&mypoMobilityTerrainMap->Mobility(mypoTerrain->Code(), i - EDITOPTION_DESCRIPTION-1));

		//Reset the cursor
			SetSelected(i);
		
		return(true);
	}
		
	//Return false by defalse! <- Bad attempt of play on words, its supposed to be prounounced like
	//"default", but you see it has the word false in it 'cause I'm going to return false now
 	//thats what makes it soooo funnny!
		return(false);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Returns a description of light effect #i
string LEDIT_TerrainEditor::LightEffect(LL_LIGHTEFFECT i)
{	//Return the proper description
		if(i == LIGHTEFFECT_NONE)			return("No effect");
		if(i == LIGHTEFFECT_BLOCK)			return("Block light");
		if(i == LIGHTEFFECT_ILLUMINATE)		return("Illuminate");
		if(i == LIGHTEFFECT_SMALL_TORCH)	return("Small torch");
		if(i == LIGHTEFFECT_TORCH)			return("Torch");
		if(i == LIGHTEFFECT_LIGHTHOUSE)		return("Lighthouse effect");
	
	//Unknown light effect, return err
		return("ERR Unknownbeknowest effect of los lightios!");
}
