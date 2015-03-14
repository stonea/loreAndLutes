/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			help.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "help.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LL_Help
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LL_Help::LL_Help()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Help::Setup(LL_Painter* poPainter, ASFC_Screen* poScreen)
{	myoTextEditor.SetConsole(&poPainter->MainConsole());
	mypoScreen = poScreen;
	mypoPainter = poPainter;
}
//----------------------------------------------------------------------------------------------- [Help] -
void LL_Help::MapEditorHelp()
{	//Draw a black background & info
		DrawBackground();
		DrawViewingInfo();
	//Now view the text
		myoText.Load(LL_Help__MapEditorHelp);
		myoTextEditor.ViewText(&myoText);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Help::RunnerHelp()
{	//Draw a black background & info
		DrawBackground();
	//Now view the text
		myoText.Load(LL_Help__RunnerHelp);
		myoTextEditor.ViewText(&myoText);
}
//------------------------------------------------------------------------------------------ [Self Help] -
void LL_Help::JotNotes(string sNotesFile)
{	//Draw a black background & info
		DrawBackground();
		DrawJottingInfo();
	//Load the jots file, edit it, and save it
		myoText.Load(sNotesFile);
		myoTextEditor.EditText(&myoText);
		myoText.Save();
}
//P------------------------------------------------------------------------------------------ [Drawing] -P
void LL_Help::DrawBackground()
{	mypoScreen->DrawFillRectangle(PLAYFIELD_X, PLAYFIELD_Y, PLAYFIELD_X2 - PLAYFIELD_X,
 	 							  PLAYFIELD_Y2 - PLAYFIELD_Y, COLOR_BLACK, 255);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_Help::DrawViewingInfo()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(0);
	mypoPainter->TalkConsole() << "Up:   Move up\n";
	mypoPainter->TalkConsole() << "Down: Move down\n";
	mypoPainter->TalkConsole() << "PgUp: Move 1 page up\n";
	mypoPainter->TalkConsole() << "PgDn: Move 1 page down";
	mypoPainter->TalkConsole() << "Escape: Exit\n";
	mypoPainter->TalkConsole().Draw(0xFF);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_Help::DrawJottingInfo()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(0);
	mypoPainter->TalkConsole() << "Arrows:      Move\n";
	mypoPainter->TalkConsole() << "#s and ABCs: Type\n";
	mypoPainter->TalkConsole() << "Cntrl + Y:   Delete Line";
	mypoPainter->TalkConsole() << "Delete:      Delete\n";
	mypoPainter->TalkConsole() << "Backspace:   Backspace\n";
	mypoPainter->TalkConsole() << "Escape:      Exit\n";
	mypoPainter->TalkConsole().Draw(0xFF);
}
