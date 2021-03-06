/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			descriptionviewer.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Starter
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LSTART_DESCRIPTIONVIEWER_H_
#define LSTART_DESCRIPTIONVIEWER_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//Parent
	#include <textedit/texteditor.h>
//Dependencies
	#include <asfc/surface.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												 Prototype
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
class LSTART_DescriptionViewer : TE_TextEditor
{	public:
	//- [Constructor] -
		LSTART_DescriptionViewer();
		void Setup(ASFC_Surface* poScreen, int iX, int iY, int iWidth, int iHeight);
	//- [Viewing] -
		void ViewDescription(string sGame);

	protected:
		ASFC_Console	myoConsole;
		ASFC_Font 		myoConFont;
		ASFC_FontPalette myoFonts;
		TE_Text 		myoText;
};

#endif
