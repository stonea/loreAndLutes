/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			pathfindingnodes.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "pathfindingnode.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PathFindingNodes
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_PathFindingNode::LL_PathFindingNode()
	:	mypoParent(0),
		myfG(0),
		myfH(0),
		myfF(0)
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathFindingNode::SetCostFor1stNode(LL_PathFindingNode &oGoal)
{	//Grab the heuristic estimage
		float fX, fY;
	
		if((float)X() > (float)oGoal.X())
		{	fX = float(((float)oGoal.X() - (float)myiX));
			fY = float(((float)oGoal.Y() - (float)myiY));
		}
		else
		{	fX = float(((float)X() - (float)oGoal.myiX));
			fY = float(((float)Y() - (float)oGoal.myiY));
		}
		float fEstimate = (fX*fX) + (fY*fY);

	//Set cost variables
		myfG = 0;
		myfH = fEstimate;
		myfF = G() + H();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathFindingNode::SetCost(LL_PathFindingNode &oParent, LL_PathFindingNode &oGoal)
{	//Grab the heuristic estimage
		float fX, fY;
	
		if((float)X() > (float)oGoal.X())
		{	fX = float(((float)oGoal.X() - (float)myiX));
			fY = float(((float)oGoal.Y() - (float)myiY));
		}
		else
		{	fX = float(((float)X() - (float)oGoal.myiX));
			fY = float(((float)Y() - (float)oGoal.myiY));
		}

	//Set cost variables
		myfG = oParent.G() + 1;
		myfH = (fX*fX) + (fY*fY);
		myfF = myfG + myfH;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_PathFindingNode::SameAsNode(LL_PathFindingNode &oRHS)
{	if(oRHS.X() == X() && oRHS.Y() == Y())
		return true;
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_PathFindingNode LL_PathFindingNode::SuccessorNorth(LL_PathFindingNode &oGoal)
{	LL_PathFindingNode toNode;
	toNode.SetX(X());
	toNode.SetY(Y() - 1);
	toNode.SetCost(*this, oGoal);
	toNode.SetParent(this);
	return(toNode);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_PathFindingNode LL_PathFindingNode::SuccessorSouth(LL_PathFindingNode &oGoal)
{	LL_PathFindingNode toNode;
	toNode.SetX(X());
	toNode.SetY(Y() + 1);
	toNode.SetCost(*this, oGoal);
	toNode.SetParent(this);
	return(toNode);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_PathFindingNode LL_PathFindingNode::SuccessorWest(LL_PathFindingNode &oGoal)
{	LL_PathFindingNode toNode;
	toNode.SetX(X() - 1);
	toNode.SetY(Y());
	toNode.SetCost(*this, oGoal);
	toNode.SetParent(this);
	return(toNode);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_PathFindingNode LL_PathFindingNode::SuccessorEast(LL_PathFindingNode &oGoal)
{	LL_PathFindingNode toNode;
	toNode.SetX(X() + 1);
	toNode.SetY(Y());
	toNode.SetCost(*this, oGoal);
	toNode.SetParent(this);
	return(toNode);
}
