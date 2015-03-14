/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			pathfindingnodes.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
 	Lore and Lutes uses a variation of the A* (A star) path finding algorithm. The path node describes a
	theoretical result of a movement. Multiple path nodes can be combined to form an LL_Route. Don't
	confuse this with a path node which desrbies a preprogammed position on a map linked to preprogammed
	routes. Each path finding node works like a link list in that it points to the previous and next
 	nodes.
*/
#ifndef LL_PATHFINDINGNODES_H_
#define LL_PATHFINDINGNODES_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Realizes
	#include "legalmovesmap.h"
//Dependencies
	#include <asfc/utils.h>
	#include "route.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PathNodes
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_PathFindingNode
{	public:
		LL_PathFindingNode();
		MEMVAR_SETGET(SetLegalMovesMap, LegalMovesMap, LL_LegalMovesMap*, mypoMap);
		MEMVAR_SETGET(SetParent, Parent, LL_PathFindingNode*, mypoParent);
		MEMVAR_SETGET(SetChild,  Child,  LL_PathFindingNode*, mypoChild);
		MEMVAR_SETGET(SetX, X, int, myiX);
		MEMVAR_SETGET(SetY, Y, int, myiY);
		MEMVAR_GET(G, float, myfG);
		MEMVAR_SETGET(SetH, H, float, myfH);
		MEMVAR_GET(F, float, myfF);
		void SetCostFor1stNode(LL_PathFindingNode &oGoal);
		void SetCost(LL_PathFindingNode &oParent, LL_PathFindingNode &oGoal);
		bool SameAsNode(LL_PathFindingNode &oRHS);
		LL_PathFindingNode SuccessorNorth(LL_PathFindingNode &oGoal);
		LL_PathFindingNode SuccessorSouth(LL_PathFindingNode &oGoal);
		LL_PathFindingNode SuccessorWest (LL_PathFindingNode &oGoal);
		LL_PathFindingNode SuccessorEast (LL_PathFindingNode &oGoal);
	
	protected:
		LL_LegalMovesMap*	mypoMap;
		LL_PathFindingNode* mypoParent;
		LL_PathFindingNode* mypoChild;
		float myfG; //Cost of this node and the ones before it
		float myfH; //Heuristic estimate
		float myfF; //g + h
		int	myiX, myiY;
};
#endif
