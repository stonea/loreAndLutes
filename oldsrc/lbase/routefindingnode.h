/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			routefindingnode.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_ROUTEFINDINGNODE_H_
#define LL_ROUTEFINDINGNODE_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Realizes
	#include "aistructures.h"
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PathNodes
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_RouteFindingNode
{	public:
	//- [Constructors] -
		LL_RouteFindingNode();
		MEMVAR_SETGET(SetNodeList, NodeList, ASFC_LinkedList<LL_Node>*, mylpoNodes);
		MEMVAR_SETGET(SetParent, Parent, LL_RouteFindingNode*, mypoParent);
		MEMVAR_SETGET(SetChild,  Child,  LL_RouteFindingNode*, mypoChild);
		MEMVAR_SETGET(SetCost, Cost, int, myiCost);
		MEMVAR_SETGET(SetNode, Node, int, myiNode);
	//- [Operations] -
		void SetCost(LL_RouteFindingNode &oParent);
		bool SameAsNode(LL_RouteFindingNode &oRHS);
		ASFC_LinkedList<LL_RouteFindingNode> Successors();
	
	protected:
		ASFC_LinkedList<LL_Node>* mylpoNodes;
		LL_RouteFindingNode* mypoParent;
		LL_RouteFindingNode* mypoChild;
		int myiCost, myiNode;
};
#endif
