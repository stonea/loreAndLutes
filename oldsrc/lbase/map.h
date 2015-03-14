/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			map.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/17/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A generic map class containing a matrix of numbers that map to something. This class
				 is abstract. All maps are 100x100!
*/
#ifndef LL_MAP_H_
#define LL_MAP_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parents
	#include <asfc/matrix.h>
	#include "mapobject.h"
//Aggregates
	#include <asfc/surface.h>
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												 Prototype
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Map
{	public:
	//Const
		static const int NO_TILE = 255;
		
	//- [Construction] -
		LL_Map();
		LL_Map(int iWidth, int iHeight, int iViewX, int iViewY, int iTileWidth, int iTileHeight,
			   int iX, int iY);
	//- [Attribute Handeling] -
		void ResizeViewPort(C_i2(iWidth, iHeight));
		void ResizeTile(C_i2(iWidth, iHeight));
		void Position(C_i2(iX, iY));
		void PositionViewport(C_i2(iX, iY));
		MEMVAR_SETGET(SetViewportWidth,  ViewportWidth, int, myiViewportWidth);
		MEMVAR_SETGET(SetViewportHeight, ViewportHeight, int, myiViewportHeight);
		MEMVAR_SETGET(SetViewX, ViewX, int, myiViewX);
		MEMVAR_SETGET(SetViewY, ViewY, int, myiViewY);
		MEMVAR_SETGET(SetX, X, int, myiX);
		MEMVAR_SETGET(SetY, Y, int, myiY);
		void LoadErrImage(string sPath);
	//- [Reading, Setting] -
		void 	Set(int iX, int iY, Uint16 iTo);
		Uint16	Get(int iX, int iY);
		void	Resize(int iWidth, int iHeight);
		int		Width();
		int		Height();
		
	protected:
	//P- [Construction] -P
		void SetDefaults();
		
	//Vars
		Uint16 myliData[100][100];
		int myiViewportWidth, myiViewportHeight;	//Viewport dimensions (in tiles)
		int myiTileWidth, myiTileHeight;			//Dimensions of a tile
		int myiViewX, myiViewY;						//TopLeft tile seen in the viewport
		int myiX, myiY;								//Pixel Location of where to draw the map
		ASFC_Surface myimgErr;						//Image to draw if theres an error
		string		 mysimgErr;						//Path of the error image
};

#endif
