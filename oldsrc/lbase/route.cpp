/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			route.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "route.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Route
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Route::LL_Route()
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Route::Save(ofstream &oFile)
{	//%Num dirs%
		oFile << Length() << " ";
	//%Start X% %StartY%, %EndY%, %EndY%
		oFile << X() << " " << Y() << " " << EndX() << " " << EndY() << endl;
	//<Loop for # of dirs>
		for(int i = 0; i < Length(); i++)
		{	//%Direction%
				oFile << int(operator[](i)) << " ";
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Route::Load(ifstream &oFile)
{	//Vars
		int iNumDirs;
		int	ti;
		ASFC_DIRECTION iDir;

	//%Num dirs%
		oFile >> iNumDirs;
		Resize(iNumDirs);
	//%Start X% %StartY%, %EndY%, %EndY%
		oFile >> myiStartX >> myiStartY >> myiEndX >> myiEndY;
	//<Loop for # of dirs>
		for(int i = 0; i < Length(); i++)
		{	//%Direction%
				oFile >> ti;
				iDir = ASFC_DIRECTION(ti);
				operator[](i) = iDir;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_Route::String()
{	string ts;

	//Loop for # of dirs
		for(int i = 0; i < Length(); i++)
		{		 if((*this)[i] == DIR_NORTH) ts += 'N';
			else if((*this)[i] == DIR_SOUTH) ts += 'S';
			else if((*this)[i] == DIR_WEST)  ts += 'W';
			else if((*this)[i] == DIR_EAST)  ts += 'E';
		}
		
	return ts;
}
//--------------------------------------------------------------------------------------- [Optimization] -
void LL_Route::Optimize()
{	//Vars
		int iStartX, iStartY;
		int iX, iY;
		
	//If there's no nodes just retrun now
		if(Length() == 0)
			return;
		
	//Record the starting position
		iStartX = myiStartX;
		iStartY = myiStartY;
		iX = iStartX;
		iY = iStartY;
	//Run through the route. If we ever return to the start cut off all instructions before it
		for(int i = 0; i < Length(); i++)
		{	if((*this)[i] == DIR_NORTH) iY--;
			else if((*this)[i] == DIR_SOUTH) iY++;
			else if((*this)[i] == DIR_WEST) iX--;
			else if((*this)[i] == DIR_EAST) iX++;
			
			if(iStartX == iX && iStartY == iY)
			{	for(int j = 0; j < i; j++)
				{	Delete(0);
				}
				return;
			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Route::Copy(LL_Route& oFrom)
{	Resize(oFrom.Length());
	myiStartX = oFrom.myiStartX;
 	myiStartY = oFrom.myiStartY;
	myiEndX = oFrom.myiEndX;
 	myiEndY = oFrom.myiEndY;
 	for(int i = 0; i < Length(); i++)
 	{	operator[](i) = oFrom[i];
 	}
}
//------------------------------------------------------------------------------------------ [Appending] -
void LL_Route::AppendRoute(LL_Route oRHS, bool fStart)
{	//If we're going the right way (start to end)
		if(fStart)
		{	//Loop through all elements of RHS
				for(int i = 0; i < oRHS.Length(); i++)
				{	//Add
						Push(oRHS[i]);
				}
		}
		
	//If we're going backwards
		else
		{	//Loop backwards
				for(int i = oRHS.Length() - 1; i >= 0; i--)
				{	//Add
						Push(OppositeDir(oRHS[i]));
				}
		}
		
	//Figure out the end x\y
		myiEndX = myiStartX;
  		myiEndY = myiStartY;
		for(int i = 0; i < Length(); i++)
		{		 if(operator[](i) == DIR_NORTH)	myiEndY--;
			else if(operator[](i) == DIR_SOUTH)	myiEndY++;
			else if(operator[](i) == DIR_WEST)	myiEndX--;
			else if(operator[](i) == DIR_EAST)	myiEndX++;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_DIRECTION LL_Route::OppositeDir(ASFC_DIRECTION iDirection)
{	//Decide whats opposite based on what the direction is
		switch(iDirection)
		{	case DIR_EAST:			{return(DIR_WEST);}			break;
			case DIR_NORTH_EAST:	{return(DIR_SOUTH_WEST);}	break;
			case DIR_NORTH:			{return(DIR_SOUTH);}		break;
			case DIR_NORTH_WEST:	{return(DIR_SOUTH_EAST);}	break;
			case DIR_WEST:			{return(DIR_EAST);}			break;
			case DIR_SOUTH_WEST:	{return(DIR_NORTH_EAST);}	break;
			case DIR_SOUTH:			{return(DIR_NORTH);}		break;
			case DIR_SOUTH_EAST:	{return(DIR_NORTH_WEST);}	break;
			default: break;
		};
}
