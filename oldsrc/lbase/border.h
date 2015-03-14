/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			border.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/15/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
   Description: A border contains several images that are meant to surround the screen. Currently border
   				assumes that the screen will be 640x480 pixels and that the border layoug is constant.
				A border gets information about what images should go around the screen from a .border
				file.
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef LL_BORDER_H_
	#define LL_BORDER_H_

//Aggregates
	#include <asfc/surface.h>
//Dependencies
	#include <asfc/utils.h>
	#include <string>
	using namespace std;

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Border
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Border
{	public:
	//- [Constuctors] -
 		LL_Border();
	//- [Image Loading] -
		void LoadHorizontalBorder(string sFileName);
		void LoadHorizontalInfoBorder(string sFileName);
		void LoadHorizontalPlayBorder(string sFileName);
		void LoadVerticalBorder(string sFileName);
		void LoadVerticalInfoBorder(string sFileName);
		void Load(string sFile);
	//- [Drawing] -
		void Draw(ASFC_Surface& oTo);
 	
 	protected:
 	//Const
 		static const int HORIZ_X		= 0;
 		static const int HORIZ_Y		= 0;
 		static const int HORIZ2_X		= 0;
 		static const int HORIZ2_Y		= 470;
	  	static const int HORIZ_INFO_X	= 438;
   		static const int HORIZ_INFO_Y	= 42;
 		static const int HORIZ_INFO2_X	= 438;
 		static const int HORIZ_INFO2_Y	= 192;
 		static const int HORIZ_PLAY_X	= 10;
 		static const int HORIZ_PLAY_Y	= 42;
 		static const int VERT_X			= 0;
 		static const int VERT_Y			= 10;
 		static const int VERT2_X		= 630;
 		static const int VERT2_Y		= 10;
 		static const int VERT_INFO_X	= 428;
 		static const int VERT_INFO_Y	= 10;
 	//Vars
 		ASFC_Surface	myoimgHoriz,
 						myoimgHorizInfo,
 						myoimgHorizPlay,
 						myoimgVert,
 						myoimgVertInfo;
};

//Now ending llborder.h
	#endif
