/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapinfoeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "mapinfoeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_MapInfoEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MapInfoEditor::LEDIT_MapInfoEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_MapInfoEditor::EditMap(LL_TerrainMap* poMap)
{	mypoMap = poMap;

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
void LEDIT_MapInfoEditor::Setup()
{	//Clear the old editor
		Reset(false);
	
	Heading("                 Map Information");
	Heading("===================================================");
	Option ("Description:      " + mypoMap->Description());
	Option ("Music file:       " + mypoMap->MusicFile());
	Option ("Terrain set:      " + mypoMap->TerrainSetFile());
	Option ("Ticks per minute: " + Val(mypoMap->TicksPerMinute()));
	Option ("Map Type:         " + mypoMap->MapType());
	Option ("Default player X: " + Val(mypoMap->PlayerX()));
	Option ("Default player Y: " + Val(mypoMap->PlayerY()));
	Heading("--------------------------------------- [Enemies] -");
	Option ("Max monsters:       " + Val(mypoMap->MaxMonsters()));
	Option ("Chance of monsters: " + Val(mypoMap->ChanceOfMonsters()));
	Heading("--------------------------------------- [Borders] -");
	Option ("Map to north: "        + mypoMapSet->MapName(mypoMap->MapNorth()));
	Option ("       North border: " + Val(mypoMap->MapBorderNorthY()));
	Option ("       North warp type" + WarpType(mypoMap->NorthWarpType()));
	Option ("       North effect: " + Effect(mypoMap->NorthEffect()));
	Option ("Map to south: "        + mypoMapSet->MapName(mypoMap->MapSouth()));
	Option ("       South border: " + Val(mypoMap->MapBorderSouthY()));
	Option ("       South warp type" + WarpType(mypoMap->SouthWarpType()));
	Option ("       South effect: " + Effect(mypoMap->SouthEffect()));
	Option ("Map to west: "         + mypoMapSet->MapName(mypoMap->MapWest()));
	Option ("       West border: "  + Val(mypoMap->MapBorderWestX()));
	Option ("       West warp type" + WarpType(mypoMap->WestWarpType()));
	Option ("       West effect: "  + Effect(mypoMap->WestEffect()));
	Option ("Map to east: "         + mypoMapSet->MapName(mypoMap->MapEast()));
	Option ("       East border: "  + Val(mypoMap->MapBorderEastX()));
	Option ("       East warp type" + WarpType(mypoMap->EastWarpType()));
	Option ("       East effect: "  + Effect(mypoMap->EastEffect()));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... .
bool LEDIT_MapInfoEditor::EditOption(int i)
{	//Decide what to do based on i
		if(i == EDITOPTION_DESCRIPTION)
		{	string ts = GrabString("Enter the description");
			mypoMap->SetDescription(ts);
			return(true);
		}
		else if(i == EDITOPTION_MUSIC_FILE)
		{	string s = mypoFileChooser->GrabFile(mypoGame->MusicDir(), "*");
			mypoMap->SetMusicFile(s);
			return(true);
		}
		else if(i == EDITOPTION_TERRAIN_SET)
		{	return(true);
		}
		else if(i == EDITOPTION_TICKS_PER_MINUTE)
		{	int ti = GrabInt("Enter the # of ticks per minute [0-255]", 0, 255);
			mypoMap->SetTicksPerMinute(ti);
   			return(true);
		}
		else if(i == EDITOPTION_MAP_TYPE)
		{	string ts = GrabString("Enter the map type");
			mypoMap->SetMapType(ts);
   			return(true);
		}
		else if(i == EDITOPTION_PLAYER_X)
		{	int ti = GrabInt("Enter the default player X position [0-100]", 0, 100);
			mypoMap->SetPlayerX(ti);
  			return(true);
		}
		else if(i == EDITOPTION_PLAYER_Y)
		{	int ti = GrabInt("Enter the default player Y position [0-100]", 0, 100);
			mypoMap->SetPlayerY(ti);	
  			return(true);
		}
		else if(i == EDITOPTION_MAX_MONSTERS)
		{	int ti = GrabInt("Enter the maximum # of monsters [0-255]", 0, 255);
			mypoMap->SetMaxMonsters(ti);
  			return(true);
		}
		else if(i == EDITOPTION_CHANCE_MONSTERS)
		{	int ti = GrabInt("Enter the % chance of monsters [0-100]", 0, 100);
			mypoMap->SetChanceOfMonsters(ti);
  			return(true);
		}
		else if(i == EDITOPTION_MAPNORTH)
		{	int ti = mypoMapSetEdit->GrabMap(mypoMapSet);
			mypoMap->MapNorth(ti);
			return(true);
		}
		else if(i == EDITOPTION_NORTH_BORDER)
		{	int ti = GrabInt("Enter the new north border [0-100]", 0, 100);
			mypoMap->SetMapBorderNorthY(ti);
  			return(true);
		}
		else if(i == EDITOPTION_NORTH_WARP)
		{	if(mypoMap->NorthWarpType()+1 < WARP_TYPE_ROLL ||
			   mypoMap->NorthWarpType()+1 >= WARP_TYPE_DEFAULT_NUMEFFECTS)
					mypoMap->SetNorthWarpType(WARP_TYPE_ROLL);
			else
				mypoMap->SetNorthWarpType(LL_BORDER_WARP_TYPE(int(mypoMap->NorthWarpType()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_NORTH_EFFECT)
		{	if(mypoMap->NorthEffect()+1 < BORDER_EFFECT_NONE ||
			   mypoMap->NorthEffect()+1 >= BORDER_EFFECT_NUMEFFECTS)
					mypoMap->SetNorthEffect(BORDER_EFFECT_NONE);
			else
				mypoMap->SetNorthEffect(LL_BORDER_EFFECT(int(mypoMap->NorthEffect()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_MAPSOUTH)
		{	int ti = mypoMapSetEdit->GrabMap(mypoMapSet);
			mypoMap->MapSouth(ti);
			return(true);
		}
		else if(i == EDITOPTION_SOUTH_BORDER)
		{	int ti = GrabInt("Enter the new south border [0-100]", 0, 100);
			mypoMap->SetMapBorderSouthY(ti);
  			return(true);
		}
		else if(i == EDITOPTION_SOUTH_WARP)
		{	if(mypoMap->SouthWarpType()+1 < WARP_TYPE_ROLL ||
			   mypoMap->SouthWarpType()+1 >= WARP_TYPE_DEFAULT_NUMEFFECTS)
					mypoMap->SetSouthWarpType(WARP_TYPE_ROLL);
			else
				mypoMap->SetSouthWarpType(LL_BORDER_WARP_TYPE(int(mypoMap->SouthWarpType()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_SOUTH_EFFECT)
		{	if(mypoMap->SouthEffect()+1 < BORDER_EFFECT_NONE ||
			   mypoMap->SouthEffect()+1 >= BORDER_EFFECT_NUMEFFECTS)
					mypoMap->SetSouthEffect(BORDER_EFFECT_NONE);
			else
				mypoMap->SetSouthEffect(LL_BORDER_EFFECT(int(mypoMap->SouthEffect()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_MAPWEST)
		{	int ti = mypoMapSetEdit->GrabMap(mypoMapSet);
			mypoMap->MapWest(ti);
			return(true);
		}
		else if(i == EDITOPTION_WEST_BORDER)
		{	int ti = GrabInt("Enter the new west border [0-100]", 0, 100);
			mypoMap->SetMapBorderWestX(ti);
  			return(true);
		}
		else if(i == EDITOPTION_WEST_WARP)
		{	if(mypoMap->WestWarpType()+1 < WARP_TYPE_ROLL ||
			   mypoMap->WestWarpType()+1 >= WARP_TYPE_DEFAULT_NUMEFFECTS)
					mypoMap->SetWestWarpType(WARP_TYPE_ROLL);
			else
				mypoMap->SetWestWarpType(LL_BORDER_WARP_TYPE(int(mypoMap->WestWarpType()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_WEST_EFFECT)
		{	if(mypoMap->WestEffect()+1 < BORDER_EFFECT_NONE ||
			   mypoMap->WestEffect()+1 >= BORDER_EFFECT_NUMEFFECTS)
					mypoMap->SetWestEffect(BORDER_EFFECT_NONE);
			else
				mypoMap->SetWestEffect(LL_BORDER_EFFECT(int(mypoMap->WestEffect()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_MAPEAST)
		{	int ti = mypoMapSetEdit->GrabMap(mypoMapSet);
			mypoMap->MapEast(ti);
			return(true);
		}
		else if(i == EDITOPTION_EAST_BORDER)
		{	int ti = GrabInt("Enter the new east border [0-100]", 0, 100);
			mypoMap->SetMapBorderEastX(ti);
  			return(true);
		}
		else if(i == EDITOPTION_EAST_WARP)
		{	if(mypoMap->EastWarpType()+1 < WARP_TYPE_ROLL ||
			   mypoMap->EastWarpType()+1 >= WARP_TYPE_DEFAULT_NUMEFFECTS)
					mypoMap->SetEastWarpType(WARP_TYPE_ROLL);
			else
				mypoMap->SetEastWarpType(LL_BORDER_WARP_TYPE(int(mypoMap->EastWarpType()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_EAST_EFFECT)
		{	if(mypoMap->EastEffect()+1 < BORDER_EFFECT_NONE ||
			   mypoMap->EastEffect()+1 >= BORDER_EFFECT_NUMEFFECTS)
					mypoMap->SetEastEffect(BORDER_EFFECT_NONE);
			else
				mypoMap->SetEastEffect(LL_BORDER_EFFECT(int(mypoMap->EastEffect()+1)));
  			return(true);
		}
		else if(i == EDITOPTION_NUM_OPTIONS)
		{	return(true);
		}

	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... .
string LEDIT_MapInfoEditor::Effect(LL_BORDER_EFFECT i)
{		 if(i == BORDER_EFFECT_NONE)  			 return("(0) No effect");
	else if(i == BORDER_EFFECT_FADE)			 return("(1) Fade");
	else if(i == BORDER_EFFECT_DISSOLVE)		 return("(2) Dissolve");
	else if(i == BORDER_EFFECT_TRIAMBULATE)		 return("(3) Triambulate");
	else if(i == BORDER_EFFECT_CHECKERBOARD)	 return("(4) Checkerboard");
	else if(i == BORDER_EFFECT_BLEND)			 return("(5) Blend");
	else if(i == BORDER_EFFECT_SPLIT_VERTICLE)	 return("(6) Split verticle");
	else if(i == BORDER_EFFECT_SPLIT_HORIZONTAL) return("(7) Split horizontal");
	else return("Que! Es tonto, porque tengas un effecto invalidad!");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... .
string LEDIT_MapInfoEditor::WarpType(LL_BORDER_WARP_TYPE i)
{		 if(i == WARP_TYPE_ROLL)			 	return("(0) Roll over edge");
	else if(i == WARP_TYPE_DEFAULT_POSITION)	return("(1) Default position");
	else if(i == WARP_TYPE_ROLL_LAST_POSITION)	return("(2) Roll from last position");
}
