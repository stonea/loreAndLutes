/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapobject.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/16/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: An abstract base class from which all objects that are placed on a map derive from.
*/
#ifndef LL_MAPOBJECT_H_
#define LL_MAPOBJECT_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include <asfc/linkedlist.h>
	#include <asfc/animation.h>
//Dependencies
	#include <asfc/utils.h>
	#include "guimetrics.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_MapObject
{	public:
	//- [Construction] -
		LL_MapObject();
	//- [Loading] -
		int LoadAnimation(string sPath, string sGraphicsDirectory, const int & iWidth,
  			        	  const int & iHeight, Uint8 iRed, Uint8 iGreen, Uint8 iBlue);
  		int LoadAnimation(string sPath, string sGraphicsDirectory);
		void SetAnimation(ASFC_Animation& oAnimation);
		void SetAnimation(LL_MapObject& oTakeFrom);
		MEMVAR_GET(ImageFile, string, sImageFile);
		MEMVAR_GET(Directional, bool, myfDirectional);
		MEMVAR_GET(Occupied,	bool, myfOccupied);
		MEMVAR_SETGET(SetCustomImage, CustomImage, bool, myfCustomImage);
		void ChangeDir(ASFC_DIRECTION iDir);
		bool AnimationExists(string sGraphicsDirectory);
	//- [Images] -
		int NumImages();
		ASFC_Animation& Animation(int iNum);
	//- [Drawing] -
		virtual int BlitTo(ASFC_Surface &screen, const int & iX, const int & iY);
		virtual int BlitOccupiedTo(ASFC_Surface &screen, const int & iX, const int & iY);
 		void Reset();
	
	protected:
	//P- [Loading] -P
 		bool Directional(string sPath);
 		string StripExtension(string sIn, string* pExtReturn);
 		string DirectionN(string sPath);
 		string DirectionS(string sPath);
 		string DirectionW(string sPath);
 		string DirectionE(string sPath);
 		string OccupiedFileName(string sPath);

 	//Const
		#define LL_MapObject__DEFAULT_GRAHPICS_DIR	"data/graphics"
	//Vars
		string sImageFile;
		bool myfCustomImage;
		int myiCurrentImage;
		ASFC_LinkedList<ASFC_Animation> mylAnimations;
		ASFC_Animation myimgOccupied;
		bool myfOccupied;
		bool myfDirectional;
};

#endif
