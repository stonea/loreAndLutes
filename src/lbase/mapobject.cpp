/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapobject.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/16/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Self
	#include "mapobject.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												 LL_MapObject
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//------------------------------------------------------------------------------------- [Construction] -
LL_MapObject::LL_MapObject()
	: myiCurrentImage(0),
	  myfCustomImage(false),
	  myfOccupied(false)
{
}
//------------------------------------------------------------------------------------------ [Loading] -
int LL_MapObject::LoadAnimation(string sPath, string sGraphicsDirectory, const int & iWidth,
								const int & iHeight, Uint8 iRed, Uint8 iGreen, Uint8 iBlue)
{	//Vars
		string tsImage;
		
	//If we're passed a blank file we're done
		if(sPath == "")
			return -1;

	//Default to non directional
		myfDirectional = false;
		myfOccupied = false;

	//If we're not using a custom image change the graphics dir to the default directory
		if(!myfCustomImage)
			sGraphicsDirectory = LL_MapObject__DEFAULT_GRAHPICS_DIR;
		
	//Reset our image #
		myiCurrentImage = 0;

	//Save file path into a string
		sImageFile = sPath;
		
	//Add the directory to the path
		sPath = "./" + sGraphicsDirectory + "/" + sPath;
			
	//Check to see if there's an occupied image
		string sOccupiedFileName = OccupiedFileName(sPath);
		if(FileExist(sOccupiedFileName))
		{	//Load the occupied image
				myfOccupied = true;
				myimgOccupied.Load(sOccupiedFileName, iWidth, iHeight, iRed, iGreen, iBlue);
		}
		
	//If we have a valid file
		if(FileExist(sPath))
		{	//If we don't have a directional image set us to have just one image
				myfDirectional = Directional(sPath);
				if(!myfDirectional)
				{	mylAnimations.Resize(1);
					mylAnimations[0].Load(sPath, iWidth, iHeight, iRed, iGreen, iBlue);
					return 0;
				}
		
			//If we have a directional image then load all possible directions
				myfDirectional = true;
				mylAnimations.Resize(4);
				
				tsImage = DirectionN(sPath);
				if(tsImage == sPath)
					myiCurrentImage = 0;
				if(FileExist(tsImage))
					mylAnimations[0].Load(tsImage, iWidth, iHeight, iRed, iGreen, iBlue);
				else
					mylAnimations[0].GetImage().DrawFillRectangle(0, 0, TILE_WIDTH, TILE_HEIGHT, COLOR_RED, 0xFF);

				tsImage = DirectionS(sPath);
				if(tsImage == sPath)
					myiCurrentImage = 1;
				if(FileExist(tsImage))
					mylAnimations[1].Load(tsImage, iWidth, iHeight, iRed, iGreen, iBlue);
				else
					mylAnimations[1].GetImage().DrawFillRectangle(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT, COLOR_RED, 0xFF);
				
    			tsImage = DirectionW(sPath);
    			if(tsImage == sPath)
					myiCurrentImage = 2;
				if(FileExist(tsImage))
					mylAnimations[2].Load(tsImage, iWidth, iHeight, iRed, iGreen, iBlue);
				else
					mylAnimations[2].GetImage().DrawFillRectangle(TILE_WIDTH*2, 0, TILE_WIDTH, TILE_HEIGHT, COLOR_RED, 0xFF);
	
    			tsImage = DirectionE(sPath);
    			if(tsImage == sPath)
					myiCurrentImage = 3;
    			if(FileExist(tsImage))
					mylAnimations[3].Load(tsImage, iWidth, iHeight, iRed, iGreen, iBlue);
				else
					mylAnimations[3].GetImage().DrawFillRectangle(TILE_WIDTH*3, 0, TILE_WIDTH, TILE_HEIGHT, COLOR_RED, 0xFF);
		}
	//If we have a bad image (Bad image!)
		else
		{	mylAnimations.Resize(1);
			mylAnimations[0].GetImage().DrawFillRectangle(0, 0, TILE_WIDTH, TILE_HEIGHT, COLOR_RED, 0xFF);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
void LL_MapObject::SetAnimation(ASFC_Animation& oAnimation)
{	mylAnimations.Resize(1);
	mylAnimations[1] = oAnimation;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
void LL_MapObject::SetAnimation(LL_MapObject& oTakeFrom)
{	//Copy the file location information
		sImageFile = oTakeFrom.ImageFile();
		myfCustomImage = oTakeFrom.CustomImage();
	//Resize to hold the images
		mylAnimations.Resize(oTakeFrom.NumImages());
	//If only one image then no es directional
		if(oTakeFrom.NumImages() == 1)
		{	myfDirectional = false;
			myiCurrentImage = 0;
		}
	//Copy 'em (by reference)
		for(int i = 0; i < oTakeFrom.NumImages(); i++)
		{	mylAnimations[i] = oTakeFrom.Animation(i);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
int LL_MapObject::LoadAnimation(string sPath, string sGraphicsDirectory)
{	return(LoadAnimation(sPath, sGraphicsDirectory, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
//MEMVAR_GET(ImageFile, string, sImageFile);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
void LL_MapObject::ChangeDir(ASFC_DIRECTION iDir)
{	//If we don't have a directional image forget it
		if(!myfDirectional) return;
		
	//Otherwise change the immage based on iDir
			 if(iDir == DIR_NORTH) myiCurrentImage = 0;
		else if(iDir == DIR_SOUTH) myiCurrentImage = 1;
		else if(iDir == DIR_WEST)  myiCurrentImage = 2;
		else if(iDir == DIR_EAST)  myiCurrentImage = 3;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
bool LL_MapObject::AnimationExists(string sGraphicsDirectory)
{	if(!myfCustomImage)
		sGraphicsDirectory = LL_MapObject__DEFAULT_GRAHPICS_DIR;
	//Add the directory to the path
		string sPath = "./" + sGraphicsDirectory + "/" + sImageFile;		
	//If we have a valid file
		return(FileExist(sPath));
}
//------------------------------------------------------------------------------------------- [Images] -
int LL_MapObject::NumImages()
{	return(mylAnimations.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
ASFC_Animation& LL_MapObject::Animation(int iNum)
{	return(mylAnimations[iNum]);
}
//------------------------------------------------------------------------------------------ [Drawing] -
int LL_MapObject::BlitTo(ASFC_Surface &screen, const int & iX, const int & iY)
{	mylAnimations[myiCurrentImage].BlitTo(screen, iX, iY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
int LL_MapObject::BlitOccupiedTo(ASFC_Surface &screen, const int & iX, const int & iY)
{	myimgOccupied.BlitTo(screen, iX, iY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
void LL_MapObject::Reset()
{	mylAnimations[myiCurrentImage].Reset();
}
//P---------------------------------------------------------------------------------------- [Loading] -P
//If 2 letters before the extension is a hypan and is followed by n,s,w,e,N,S,W,E then we have a
//direction
bool LL_MapObject::Directional(string sPath)
{	//Vars
		string sExtension;
		string sPathNoExtnsn;
		int	   iExtnsnPos;
		char   tc;
		
	//Grab the path w/o extension
		sPathNoExtnsn =	StripExtension(sPath, &sExtension);
		
	//If the extension is < 2 letters long then we don't have a directional image
		if(sPathNoExtnsn.size() < 2)
			return false;
			
	//If the second to last letter isn't a hypahn we don't have a directional image
		if(sPathNoExtnsn[sPathNoExtnsn.size() - 2] != '_')
			return false;
			
	//If the last letter isn't N,S,W,E,n,s,w,e  we don't have a directional image
		tc = sPathNoExtnsn[sPathNoExtnsn.size() - 1];
		if(	tc != 'N' && tc != 'S' && tc != 'W' && tc != 'E' && tc != 'n' && tc != 's' && tc != 'w'
			&& tc != 'e')
		{
			return false;
		}
	
	//Guess we have a directional image
		return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
string LL_MapObject::StripExtension(string sIn, string* pExtReturn)
{	//Vars
		string sPathNoExtnsn;
		string sExtension;
		int iExtnsnPos;
	//Grab the extension, Loop from the end of the string until we reach the start or a .
		for(int i = sIn.size() - 1; i > 0 && sIn[i] != '.'; i--) 
		{	sExtension = sIn[i] + sExtension;
		}
  		sExtension = '.' + sExtension;
  		
	//Grab the path - extension
		iExtnsnPos	  = sIn.find(sExtension);
		sPathNoExtnsn = "";
		sPathNoExtnsn = sIn.substr(0, iExtnsnPos);
	//Change pExtReturn to include the value of the extension
		*pExtReturn = sExtension;
		
	return(sPathNoExtnsn);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
string LL_MapObject::DirectionN(string sPath)
{	//Vars
		string sPathNoExtnsn, sExtension;

	//Grab the path w/o extension
		sPathNoExtnsn =	StripExtension(sPath, &sExtension);
		
	//Return path - extension - 1 char + dir + extension
		sPathNoExtnsn.erase(sPathNoExtnsn.size() - 1);
		return(sPathNoExtnsn + 'n' + sExtension);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
string LL_MapObject::DirectionS(string sPath)
{	//Vars
		string sPathNoExtnsn, sExtension;

	//Grab the path w/o extension
		sPathNoExtnsn =	StripExtension(sPath, &sExtension);
		
	//Return path - extension - 1 char + dir + extension
		sPathNoExtnsn.erase(sPathNoExtnsn.size() - 1);
		return(sPathNoExtnsn + 's' + sExtension);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
string LL_MapObject::DirectionW(string sPath)
{	//Vars
		string sPathNoExtnsn, sExtension;

	//Grab the path w/o extension
		sPathNoExtnsn =	StripExtension(sPath, &sExtension);
		
	//Return path - extension - 1 char + dir + extension
		sPathNoExtnsn.erase(sPathNoExtnsn.size() - 1);
		return(sPathNoExtnsn + 'w' + sExtension);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
string LL_MapObject::DirectionE(string sPath)
{	//Vars
		string sPathNoExtnsn, sExtension;

	//Grab the path w/o extension
		sPathNoExtnsn =	StripExtension(sPath, &sExtension);
		
	//Return path - extension - 1 char + dir + extension
		sPathNoExtnsn.erase(sPathNoExtnsn.size() - 1);
		return(sPathNoExtnsn + 'e' + sExtension);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
string LL_MapObject::OccupiedFileName(string sPath)
{	//Vars
		string sPathNoExtnsn, sExtension;
	//If the image is directional
		if(Directional(sPath))
		{	//Grab the path w/o extension
				sPathNoExtnsn =	StripExtension(sPath, &sExtension);
			//Return path - extension - 1 char + dir + extension
				sPathNoExtnsn.erase(sPathNoExtnsn.size() - 1);
				return(sPathNoExtnsn + 'o' + sExtension);
		}
	//It is isn't just append an o
		else
		{	//Grab the path w/o extension
				sPathNoExtnsn =	StripExtension(sPath, &sExtension);
			//Return path - extension + spacer + dir + extension
				if(sPathNoExtnsn.size() >= 1)
					sPathNoExtnsn.erase(sPathNoExtnsn.size());
				return(sPathNoExtnsn + "_o" + sExtension);
		}
}
