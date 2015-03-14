/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			guimetrics.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: Contains a whole bunch of constants describing the Lore and Lutes interface.
*/

#ifndef LL_GUIMetrics_H_
#define LL_GUIMetrics_H_
	//.GUI Files
		#define GUIMetrics__LAL_GUI_PREFERENCE_FILE		"./data/gui/normal.gui"
		#define GUIMetrics__LALEDIT_GUI_PREFERENCE_FILE	"./data/gui/editor.gui"

	//Interface object positions
		//Playfield
	 		static const int PLAYFIELD_X			= 10;
 			static const int PLAYFIELD_Y			= 52;
 			static const int PLAYFIELD_X2			= 428;
 			static const int PLAYFIELD_Y2			= 470;
			static const int PLAYFIELD_TILEWIDTH	= 11;	//# of tiles across, not the width of an individal tile
			static const int PLAYFIELD_TILEHEIGHT	= 11;	//# of tiles down, not the height of an individal tile
			static const int TILE_WIDTH  = 38;
			static const int TILE_HEIGHT = 38;
		//Celestial view (the sun\moon clock on the top)
			static const int CELESTIALVIEW_X	= 10;
			static const int CELESTIALVIEW_Y	= 10;
		//LL View (the top box with the game logo in it)
	 		static const int LLVIEW_X = 438;
			static const int LLVIEW_Y = 10;
		//Stat View (the console with player names and zStats)
			static const int STATVIEW_X				= 438;
			static const int STATVIEW_Y				= 52;
			static const int STATVIEW_CHARWIDTH		= 24;
	 		static const int STATVIEW_CHARHEIGHT	= 10;
		//Info view (the lower right console)
 			static const int INFOVIEW_X				= 438;
			static const int INFOVIEW_Y				= 204;
 			static const int INFOVIEW_CHARWIDTH		= 24;
	 		static const int INFOVIEW_CHARHEIGHT	= 19;
		//The text shown above a scroll
	 		static const int SCROLLHEADER_X			= 9999;
			static const int SCROLLHEADER_Y			= 9999;
 			static const int SCROLLHEADER_CHARWIDTH	= 9999;
			static const int SCROLLHEADER_CHARHEIGHT= 9999;
		//Scroll output
	 		static const int SCROLL_X			= 9999;
			static const int SCROLL_Y			= 9999;
			static const int SCROLL_CHARWIDTH	= 9999;
	 		static const int SCROLL_CHARHEIGHT	= 9999;
		//Main console (editor thingy)
			static const int MAINCON_CHARWIDTH  = 52;
			static const int MAINCON_CHARHEIGHT = 29;
#endif
