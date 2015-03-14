/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			globalscripteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "globalscripteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LEDIT_GlobalScriptEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_GlobalScriptEditor::LEDIT_GlobalScriptEditor()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_GlobalScriptEditor::Setup(LL_Painter* poPainter)
{	myoTextEditor.SetConsole(&poPainter->MainConsole());
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_GlobalScriptEditor::EditGlobalScript(LL_Game* poGame, string sClassFile)
{	//Clear the screen
		mypoScreen->DrawFillRectangle(PLAYFIELD_X, PLAYFIELD_Y, PLAYFIELD_X2 - PLAYFIELD_X,
 	 								  PLAYFIELD_Y2 - PLAYFIELD_Y, COLOR_BLACK, 255);
	//Set up the game yo'
		mypoGame = poGame;
	//Load up the text
		mysClassFile = sClassFile;
	  	myoText.Load(mysClassFile);
	//Edit
		EditText();
	//Save it
		myoText.Save();
	//Check for errors
		CheckForErrors();
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_GlobalScriptEditor::EditText(int iLine)
{	//Edit text
		int iBegin = 0;
		int iEnd = myoText.NumRows() - 2;
		if(iLine == -1)
			myoTextEditor.EditText(&myoText, &iBegin, &iEnd);
		else
			myoTextEditor.EditText(&myoText, &iBegin, &iEnd, iLine);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_GlobalScriptEditor::CheckForErrors()
{	//Debug
		int iLine = 0;
		int	iErr  = 0;
		string sErr = "";
		int	iCharStart;

		mypoGame->LOOP().Reader().Debug(0, mysClassFile,
  										0, &sErr, &iErr,
            							"GLSCRIPT");

	//While we have errors
		while(sErr != "")
		{	//Output in talk console	
				mypoPainter->TalkConsole().Clear();
				mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
				mypoPainter->TalkConsole() << "ERRORS\n";
				mypoPainter->TalkConsole() << "----------\n";
				mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
				mypoPainter->TalkConsole() << "Char: " << iErr << "\n";
				mypoPainter->TalkConsole() << "Err:  " << sErr << "\n";
				mypoPainter->TalkConsole().Draw(0xFF);

			//ReEdit the text
				//Determine which character starts the text we're interested in
					iLine =  myoText.LineAtChar(iErr);
				//Load up the text
					myoText.Load(mysClassFile);
				//Edit it
					EditText(iLine);
				//Save it
					myoText.Save();
					
			//Recheck for errors
				iErr = 0;
				sErr = "";
				mypoGame->LOOP().Reader().Debug(0, mysClassFile,
  												0, &sErr, &iErr,
              									"glscript");
		}
}
