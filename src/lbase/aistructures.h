/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			aistructures.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LL_AISTRUCTURES_H_
#define LL_AISTRUCTURES_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include <asfc/linkedlist.h>
	#include <vector>
//Dependencies

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Structs
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Type
//A node, holds a point on a map
	struct LL_Node
	{	int iX, iY;
		vector<int>  myiNodes;
		vector<int>  myiRoutes;
		vector<bool> myfStart;
	};
	//An area defines a rectangular area on a map
	struct LL_Area
	{	int iX, iY, iWidth, iHeight;
	};

#endif
