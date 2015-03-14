/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terrainseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "terrainseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_TerrainSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_TerrainSetEditor::LEDIT_TerrainSetEditor()
{	myiSelected 	= 0;
	myiNumTiles		= 253;
}
//-------------------------------------------------------------------------------------- [Game Handeling] -
//MEMVAR_SETGET(SetGame, Game, LL_Game*, mypoGame);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetTerrainEditor, TerrainEditor, LEDIT_TerrainEditor*, mypoTerrainEditor);
//-------------------------------------------------------------------------------------------- [Editting] -
int LEDIT_TerrainSetEditor::ChooseTile()
{	//Vars
		int iOption;
		bool fDone = false;
		
	//Draw quick keys
		DrawQuickKeys();
	
	//Set grab option to include just the good ol default space and return plus e for edit
		int iKey = -1;
		ASFC_LinkedList<int> lChoosers;
		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
		lChoosers.Push(KEY_EDIT);
				
	//While we're not done
		while(!fDone)
		{	//Now grab an option 
				iKey = -1;
				iOption = GrabOption(&iKey, lChoosers);
				
			//If its "edit"	
				if(iKey == SDLKey(KEY_EDIT))
				{	//Edit this terrain
						mypoTerrainEditor->EditTerrain(&mypoGame->TerrainSet().Terrain(iOption), mypoGame);
				}
			
			//Else we're done
				else
					fDone = true;
		}

	//Return our current option
		return(iOption);
}
//P----------------------------------------------------------------------------------------- [Editting] -P
void LEDIT_TerrainSetEditor::DrawQuickKeys()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
	mypoPainter->TalkConsole() << "Arrows: Move\n";
	mypoPainter->TalkConsole() << "C:      Copy\n";
	mypoPainter->TalkConsole() << "V, P:   Paste\n";
	mypoPainter->TalkConsole() << "E:      Edit\n";
	mypoPainter->TalkConsole() << "Enter:  Choose\n";
	mypoPainter->TalkConsole() << "Esc:    Exit\n";
}
//P------------------------------------------------------------------------------------------- [Drawing] -P
void LEDIT_TerrainSetEditor::DrawTile(int iX, int iY, int iTile)
{	//Draw a terrain
		mypoGame->TerrainSet().Terrain(iTile).BlitTo(*mypoScreen, iX, iY);
}
