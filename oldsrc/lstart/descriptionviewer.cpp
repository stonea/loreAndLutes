/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			starter.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Starter
   | ----` |	Last Updated:
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "descriptionviewer.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LSTART_Starter
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//----------------------------------------------------------------------------------------- [Constructor] -
LSTART_DescriptionViewer::LSTART_DescriptionViewer()
{	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LSTART_DescriptionViewer::Setup(ASFC_Surface* poScreen, int iX, int iY, int iWidth, int iHeight)
{	myoConFont.Load("./data/gui/fonts/normal_console_font.png", 8, 14, COLOR_BLUE);
	myoFonts.Push(myoConFont);
	myoConsole.SetFontPalette(&myoFonts);
	myoConsole.SetSurface(poScreen);
	myoConsole.SetConsolePosition(iX, iY);
	myoConsole.SetViewport(0, 0);
	myoConsole.SetViewportSize(iWidth, iHeight);
	myoConsole.SetConsoleSize (iWidth, iHeight);
	SetConsole(&myoConsole);
}
//-------------------------------------------------------------------------------------------- [Viewing] -
void LSTART_DescriptionViewer::ViewDescription(string sGame)
{	//Load the text file
		myoText.Load("./games/" + sGame + "/description.txt");
	//Draw this bit'
		//Map params to the appropriate vars
			mypoText = &myoText;
			mypoText->SetMaximumNumColumns(mypoConsole->ConsoleWidth());
		//Set defaults
//			SetDefaults();	
		//Draw everything important for the edit
			DrawText();
			mypoConsole->Surface()->Update();
}
