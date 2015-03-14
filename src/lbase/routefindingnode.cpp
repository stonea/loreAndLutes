/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			routefindingnode.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "routefindingnode.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_RouteFindingNode
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//--------------------------------------------------------------------------------------- [Constructors] -
LL_RouteFindingNode::LL_RouteFindingNode()
		:	mypoParent(0),
			myiCost(0)
{
}
//----------------------------------------------------------------------------------------- [Operations] -
void LL_RouteFindingNode::SetCost(LL_RouteFindingNode &oParent)
{	myiCost = oParent.Cost() + 1; //(*mylpoNodes)[oParent.Node()].Length();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_RouteFindingNode::SameAsNode(LL_RouteFindingNode &oRHS)
{	if(oRHS.Node() == Node())
		return true;
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_LinkedList<LL_RouteFindingNode> LL_RouteFindingNode::Successors()
{	//Vars
		ASFC_LinkedList<LL_RouteFindingNode> lSuccessors;
	
	//Loop through all possible successors creating 'em
		lSuccessors.Resize((*mylpoNodes)[Node()].myiNodes.size());
		for(int i = 0; i < (*mylpoNodes)[Node()].myiNodes.size(); i++)
		{	lSuccessors[i].SetNodeList(this->NodeList());
			lSuccessors[i].SetParent(this);
  			lSuccessors[i].SetCost(*this);
			lSuccessors[i].SetNode((*mylpoNodes)[Node()].myiNodes[i]);
		}
	
	//Return
		return(lSuccessors);
}
