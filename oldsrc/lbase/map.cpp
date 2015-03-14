/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			map.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/17/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Self
	#include "map.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												 LL_Map
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//------------------------------------------------------------------------------------- [Construction] -
LL_Map::LL_Map()
{	SetDefaults();
	Resize(100, 100);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Map::LL_Map(int iWidth, int iHeight, int iViewX, int iViewY, int iTileWidth, int iTileHeight,
			   int iX, int iY)
{
	Resize(iWidth, iHeight);
	ResizeViewPort(iViewX, iViewY);
	ResizeTile(iTileWidth, iTileHeight);
	Position(iX, iY);
	PositionViewport(0, 0);
}
//------------------------------------------------------------------------------ [Attribute Handeling] -
void LL_Map::ResizeViewPort(C_i2(iWidth, iHeight))
{	myiViewportWidth  = iWidth;
	myiViewportHeight = iHeight;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Map::ResizeTile(C_i2(iWidth, iHeight))
{	myiTileWidth  = iWidth;
	myiTileHeight = iHeight;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Map::Position(C_i2(iX, iY))
{	myiX = iX;
	myiY = iY;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Map::PositionViewport(C_i2(iX, iY))
{	myiViewX = iX;
	myiViewY = iY;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(ViewportWidth, int, myiViewportWidth)
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(ViewportHeight, int, myiViewportHeight)
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(ViewX, int, myiViewX)
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(ViewY, int, myiViewY)
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(X, int, myiX)
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(Y, int, myiY)
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Map::LoadErrImage(string sPath)
{	mysimgErr = sPath;
	myimgErr.LoadImage(mysimgErr);
}
//------------------------------------------------------------------------------ [Reading, Setting] -
void LL_Map::Set(int iX, int iY, Uint16 iTo)
{	myliData[iX][iY] = iTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
Uint16 LL_Map::Get(int iX, int iY)
{	return(myliData[iX][iY]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Map::Resize(int iWidth, int iHeight)
{	for(int iY = 0; iY < iHeight; iY++)
		for(int iX = 0; iX < iWidth; iX++)
			Set(iX, iY, 0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_Map::Width()
{	return(100);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_Map::Height()
{	return(100);
}
//P-------------------------------------------------------------------------------- [Construction] -P
void LL_Map::SetDefaults()
{	Resize(10, 10);
	ResizeViewPort(10, 10);
	Position(0, 0);
	PositionViewport(0, 0);
}
