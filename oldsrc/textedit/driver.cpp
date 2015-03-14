/*	Protected under the GNU General Public License read and see copying.txt for details
	TextEdit
	By: Andy Stone
*********************************************************************************************************/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
#include <asfc/screen.h>
#include <asfc/fontpalette.h>
#include <asfc/console.h>

#include "text.h"
#include "texteditor.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Main
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
int main(int argc, char *argv[])
{	//Init
		//ASFC
			ASFC_Screen screen(640, 480, 16);
		//SDL (stuff not handled in ASFC Init)
			SDL_WM_SetCaption("Text Edit", "Text Edit");
	//Setup the console
		ASFC_Font oConFont("./fonts/normal_console_font.png", 8, 14, COLOR_BLUE);
		ASFC_FontPalette myoFonts;
		myoFonts.Push(oConFont);
		ASFC_Console oCon;
		oCon.SetFontPalette(&myoFonts);
		oCon.SetSurface(&screen);
		oCon.SetConsolePosition(0, 0);
		oCon.SetViewport(0, 0);
		oCon.SetViewportSize(52, 29);
		oCon.SetConsoleSize (62, 29);

	//Test
		TE_Text oText;
		TE_TextEditor oEdit;
		oEdit.SetConsole(&oCon);

  		oText.Load("test.txt");
		oEdit.EditText(&oText);
	//We be done!
		return 1;
}

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												xyzzy
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------------- [xyzzy] -
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
