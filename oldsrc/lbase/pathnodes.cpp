/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			pathnodes.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "pathnodes.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PathNodes
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_PathNodes::Save(ofstream &oFile)
{	//%Num Nodes%
		oFile << NumNodes() << endl;
	//<Loop for # of nodes>
		for(int i = 0; i < NumNodes(); i++)
		{	//%X%, //%Y%
				oFile << Val(myloNodes[i].iX) << " ";
				oFile << Val(myloNodes[i].iY) << " ";
			//%Num Nodes\Routes\Starts%
				oFile << myloNodes[i].myiNodes.size() << " ";

			//<Loop for # of nodes>
				for(int j = 0; j < myloNodes[i].myiNodes.size(); j++)
				{	//%Node%, %Route%, %Start%
						oFile << myloNodes[i].myiNodes[j]  << " ";
	    				oFile << myloNodes[i].myiRoutes[j] << " ";
						oFile << myloNodes[i].myfStart[j]  << endl;
				}
		}

	//%Num Area%
		oFile << NumAreas() << endl;
	//<Loop for # of areas>
		for(int i = 0; i < NumAreas(); i++)
		{	//%X%, %Y%, %Width%, %Height%
				oFile << myloArea[i].iX << " ";
				oFile << myloArea[i].iY << " ";
				oFile << myloArea[i].iWidth  << " ";
				oFile << myloArea[i].iHeight << endl;
		}
	
	//%Num Routes%
		oFile << NumRoutes() << endl;
	//<Loop for # of routes>
		for(int i = 0; i < NumRoutes(); i++)
		{	//<Save Route>
				myloRoutes[i].Save(oFile);
				oFile << "\n";
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::Load(ifstream &oFile)
{	//Vars
		int iNumNodes, iNumAreas, iNumRoutes;
		int iNodesPerNode;
		LL_Node oNode;
		LL_Area oArea;
		int tiVal;

	//Clear old info
		ClearNodes();
		ClearAreas();
		ClearMap();

	//%Num Nodes%
		oFile >> iNumNodes;

	//<Loop for # of nodes>
		for(int i = 0; i < iNumNodes; i++)
		{	//%X%, //%Y%
				oFile >> oNode.iX >> oNode.iY;
			//%Num Nodes\Routes\Starts%
				oFile >> iNodesPerNode;
				oNode.myiNodes.resize(iNodesPerNode);
				oNode.myiRoutes.resize(iNodesPerNode);
				oNode.myfStart.resize(iNodesPerNode);
			//<Loop for # of nodes>
				for(int j = 0; j < iNodesPerNode; j++)
				{	oFile >> oNode.myiNodes[j];
	    			oFile >> oNode.myiRoutes[j];
					oFile >> tiVal;
     				oNode.myfStart[j] = tiVal;
				}
				AddNode(oNode);
		}

	//%Num Area%
		oFile >> iNumAreas;
	//<Loop for # of areas>
		for(int i = 0; i < iNumAreas; i++)
		{	//%X%, %Y%, %Width%, %Height%
				oFile >> oArea.iX >> oArea.iY >> oArea.iWidth >> oArea.iHeight;
				AddArea(oArea);
		}
		
	//%Num Routes%
		oFile >> iNumRoutes;
		myloRoutes.Resize(iNumRoutes);
	//<Loop for # of routes>
		for(int i = 0; i < iNumRoutes; i++)
		{	//<Load Route>
				myloRoutes[i].Load(oFile);
		}
}
//------------------------------------------------------------------------------------- [Node Handeling] -
LL_Node& LL_PathNodes::Node(int iNum)
{	return(myloNodes[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::AddNode(LL_Node oNode)
{	//If a node doesn't already exist here make one
		if(myloNodeMap[oNode.iX][oNode.iY].iNode == NO_TILE)
		{	myloNodes.Push(oNode);
			myloNodeMap[oNode.iX][oNode.iY].iNode = NumNodes() - 1;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::DynamicallyPlotNode(int iNodeX, int iNodeY)
{	//Vars
		int iNode;
		int iStartNode;

	//Plot dis' node down' brotha'?
		LL_Node oNode;
		oNode.iX = iNodeX;
		oNode.iY = iNodeY;
		AddNode(oNode);
		iNode = myloNodes.Length() - 1;
		
	//Check and see if a route starts on this tile
		//if(NodeOn(iNodeX, iNodeY) != NO_NODE)
		//{	cerr << "This shouldn't happen. You've got an error void DynamicallyPlotNode(...)\n";
		//	return;
		//}
	
	//Check all routes and see if any start or end on one of the adjecent squares
		for(int i = 0; i < myloRoutes.Length(); i++)
		{	//Loop through adjecent tiles
				for(int iX = iNodeX - 1; iX <= iNodeX + 1; iX++)
				{	for(int iY = iNodeY - 1; iY <= iNodeY + 1; iY++)
					{	//If a route ends on this tile
							if(myloRoutes[i].EndX() == iX && myloRoutes[i].EndY() == iY)
							{	//Get the node that this route starts on
									iStartNode = NodeOn(myloRoutes[i].X(), myloRoutes[i].Y());
        						//If this route does start somewhere
									if(iStartNode != NO_NODE)
									{	//Link to this node
											myloNodes[iNode].myiNodes.push_back (iStartNode);
											myloNodes[iNode].myiRoutes.push_back(i);
											myloNodes[iNode].myfStart.push_back (false);
											
										//Link the start node to this node
											myloNodes[iStartNode].myiNodes.push_back (iNode);
											myloNodes[iStartNode].myiRoutes.push_back(i);
											myloNodes[iStartNode].myfStart.push_back (true);
									}
							}
					}
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_PathNodes::NumNodes()
{	return(myloNodes.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
/*
Removing a node
===============
Steps:
* Remove all references
* Promote all higher nodes
* Promote all references above deleted node

Example: Before

1-2-6    1: 2, 3
| | |    2: 1, 4, 6
3-4-7    3: 1, 4
  | |    4: 2, 3, 5, 7
  5-8    5: 4, 8
		 6: 2, 7
		 7: 6, 4, 8
		 8: 7, 5

Example: After
Delete 4
1-2-5    1: 2, 3
|   |    2: 1, 5
3   6    3: 1
    |    
  4-7    4: 7
		 5: 2, 6
		 6: 5, 7
		 7: 6, 4
*/
void LL_PathNodes::RemoveNode(int iX, int iY)
{	//Figure out which node is at iX, iY, if it doesn't exit
		int iNode = NodeOn(iX, iY);
		if(iNode == NO_TILE)
			return;

	//Delete the node
		myloNodeMap[iX][iY].iNode = NO_TILE;
		myloNodes.Delete(iNode);

	//Remove all references to the old node
		for(int j = 0; j < myloNodes.Length(); j++)
		{	for(int k = 0; k < myloNodes[j].myiNodes.size(); k++)
			{	if(myloNodes[j].myiNodes[k] == iNode)
				{	myloNodes[j].myiNodes.erase(myloNodes[j].myiNodes.begin() + k);
					myloNodes[j].myiRoutes.erase(myloNodes[j].myiRoutes.begin() + k);
					myloNodes[j].myfStart.erase(myloNodes[j].myfStart.begin() + k);
					k--;
				}
			}
		}

	//All references on the map above old node i get promoted
		for(int itY = 0; itY < 100; itY++)
		{	for(int itX = 0; itX < 100; itX++)
	       	{	if(myloNodeMap[itX][itY].iNode > iNode)
		       		myloNodeMap[itX][itY].iNode--;
       		}
		}

	//Promote all references above the old node
		for(int j = 0; j < myloNodes.Length(); j++)
		{	for(int k = 0; k < myloNodes[j].myiNodes.size(); k++)
			{	if(myloNodes[j].myiNodes[k] > iNode)
				{	myloNodes[j].myiNodes[k]--;
				}
			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_PathNodes::NodeOn(int iX, int iY)
{	return(myloNodeMap[iX][iY].iNode);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::ClearNodes()
{	myloNodes.Resize(0);
}
//------------------------------------------------------------------------------------- [Area Handeling] -
LL_Area& LL_PathNodes::Area(int iNum)
{	return(myloArea[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_PathNodes::AreaOn(int iX, int iY)
{	//Loop through all areas once we find one that includes iX, iY return it
		for(int i = 0; i < myloArea.Length(); i++)
		{	if(	iX >= myloArea[i].iX && iY >= myloArea[i].iY && 
  				iX < myloArea[i].iX + myloArea[i].iWidth && iY < myloArea[i].iY + myloArea[i].iHeight)
			{	
				return(i);
			}
		}
		
	//No area found
		return(NO_AREA);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::AddArea(LL_Area oArea)
{	myloArea.Push(oArea);
	
	//Put this area on the map
		for(int iY = oArea.iY; iY < oArea.iY + oArea.iHeight; iY++)
			for(int iX = oArea.iX; iX < oArea.iX + oArea.iWidth; iX++)
				myloNodeMap[iX][iY].iArea = NumAreas() -1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_PathNodes::NumAreas()
{	return(myloArea.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::RemoveArea(int iX, int iY)
{	//Vars
		int iArea = myloNodeMap[iX][iY].iArea;

	//First make sure area actually exists here
		if(iArea != NO_TILE)
		{	//Remove refrences to this area on the map
				for(int itY = myloArea[iArea].iY; itY < myloArea[iArea].iY + myloArea[iArea].iHeight; itY++)
				{	for(int itX = myloArea[iArea].iX; itX < myloArea[iArea].iX + myloArea[iArea].iWidth; itX++)
    				{	myloNodeMap[itX][itY].iArea = NO_TILE;
    				}
				}
				
			//Delete the area object
				myloArea.Delete(iArea);

			//All references above old area i get promoted
				for(int itY = 0; itY < 100; itY++)
   				{	for(int itX = 0; itX < 100; itX++)
 					{	if(myloNodeMap[iX][iY].iArea > iArea)
	   						myloNodeMap[iX][iY].iArea--;
	   				}
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::ClearAreas()
{	myloArea.Resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::ClearMap()
{	for(int iY = 0; iY < 100; iY++)
		for(int iX = 0; iX < 100; iX++)
		{	myloNodeMap[iX][iY].iNode = NO_TILE;
  			myloNodeMap[iX][iY].iArea = NO_TILE;
		}
}
//----------------------------------------------------------------------------------- [Route Handeling] -
LL_Route& LL_PathNodes::Route(int iNum)
{	return(myloRoutes[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::AddRoute(LL_Route oRoute)
{	myloRoutes.Push(oRoute);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_PathNodes::NumRoutes()
{	return(myloRoutes.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
/*
Removing a route
===============
Steps:
* Remove the route
* Remove all references to the route
* Promote all higher routes
* Promote all references to higher routes

Example: Before

(x) = Node  #
~x  = Route #
                              Node  | Connects to ~
(1)-------~1---------(2)      ------|--------------
 |                    |          1     ~1, ~4
 ~4                   ~5         2     ~1, ~5
 |                    |          3     ~4, ~2, ~6
 (3)------~2---------(4)         4     ~5, ~2, ~7
 |                    |          5     ~6, ~3
 ~6                   ~7         6     ~3, ~7
 |                    |
 (5)------~3---------(6)

After:
Delete route 2
                              Node  | Connects to ~
(1)-------~1---------(2)      ------|--------------
 |                    |          1     ~1, ~3
 ~3                   ~4         2     ~1, ~4
 |                    |          3     ~3, ~5
 (3)                 (4)         4     ~4, ~6
 |                    |          5     ~5, ~2
 ~5                   ~6         6     ~2, ~6
 |                    |
 (5)------~2---------(6)

*/

int	LL_PathNodes::RemoveRoute(int iX, int iY)
{	//Figure out which route we're dealing with, if no route exit
		int iRoute = RouteOn(iX, iY);
		if(iRoute == NO_ROUTE)
			return 0;
		
	//Remove the route
		myloRoutes.Delete(iRoute);
	//Remove all references to the route, promote all higher references
		for(int i = 0; i < myloNodes.Length(); i++)
		{	for(int j = 0; j < myloNodes[i].myiRoutes.size(); j++)
			{	if(myloNodes[i].myiRoutes[j] == iRoute)
				{	myloNodes[i].myiNodes.erase(myloNodes[i].myiNodes.begin() + j);
    				myloNodes[i].myiRoutes.erase(myloNodes[i].myiRoutes.begin() + j);
    				myloNodes[i].myfStart.erase(myloNodes[i].myfStart.begin() + j);
					j--;
				}
				else if(myloNodes[i].myiRoutes[j] > iRoute)
					myloNodes[i].myiRoutes[j]--;
			}
		}

	//Remove the route at iX, iY

	//Return good
 		return 1;		
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_PathNodes::ClearRoutes()
{	myloRoutes.Resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_PathNodes::RouteOn(int iX, int iY)
{	//Vars
		int iCurX, iCurY;
		LL_Route* poRoute;

	//Loop through all routes, if we find one here return the route # else return NO_ROUTE
		for(int iRoute = 0; iRoute < NumRoutes(); iRoute++)
		{	//Grab a pointer to this route
	  			poRoute = &Route(iRoute);
			//Place iCurX, iCurY on the start
				iCurX = poRoute->X();
				iCurY = poRoute->Y();
  			//Loop through all the places this route goes
				for(int i = 0; i < poRoute->Length(); i++)
				{	//If iCurX, iCurY equals iX, iY
						if(iCurX == iX && iCurY == iY)
							return iRoute;
						
					//Move the cursor based on how the route goes
							 if((*poRoute)[i] == DIR_NORTH) iCurY--;
						else if((*poRoute)[i] == DIR_SOUTH) iCurY++;
						else if((*poRoute)[i] == DIR_WEST)  iCurX--;
						else if((*poRoute)[i] == DIR_EAST)  iCurX++;
				}
		}
		
	return NO_ROUTE;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Route LL_PathNodes::GrabRoute(int iStartX, int iStartY, int iEndX, int iEndY)
{	
}
//------------------------------------------------------------------------------------------- [Drawing] -
void LL_PathNodes::Draw(ASFC_Surface &oScreen, int iStartX, int iStartY, int iPixStartX, int iPixStartY)
{	//Vars
		//Cursor
			int iTileX = iStartX; 		//Holds (map wise) of the location of the tile to draw
			int	iTileY = iStartY;
			int iPixX  = iPixStartX;	//Where to draw the tile
   			int	iPixY  = iPixStartY;			
		//Misc. Variables
			int iWidth  = 100;	//# of tiles across the screen to draw
			int iHeight = 100;	//# of tiles down the screen to draw

	//Loop through all the tiles and draw them
		for(int iY = 0; iY < PLAYFIELD_TILEHEIGHT; iY++)	
		{	for(int iX = 0; iX < PLAYFIELD_TILEWIDTH; iX++)
			{	//If this is a legal local
					if(iTileX > 0 && iTileX < 100 && iTileY > 0 && iTileY < 100)
					{	//If a node exists here draw a translucent red node square
							if(myloNodeMap[iTileX][iTileY].iNode != NO_TILE)
							{	oScreen.DrawFillRectangle(iPixX, iPixY, TILE_WIDTH, TILE_HEIGHT,
														  COLOR_RED, 100);
						  	}
		  				//If an area exists here draw a translucent yellow node square
							if(myloNodeMap[iTileX][iTileY].iArea != NO_TILE)
							{	oScreen.DrawFillRectangle(iPixX, iPixY, TILE_WIDTH, TILE_HEIGHT,
														  COLOR_YELLOW, 100);
						  	}
					}
				//Move our invisible cursor to the next tile
					iTileX++;
					iPixX += TILE_WIDTH;
			}
			//Move our invisible cursor to the next row
				iTileY++;
				iTileX = iStartX;
				iPixX  = iPixStartX;
				iPixY += TILE_HEIGHT;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PathNodes::DrawGemView(ASFC_Surface &oScreen)
{	//Vars
		int iPixX, iPixY;
		int iStartX, iStartY;
		int iTileWidth, iTileHeight;

	//Calculate the tile width & height
		iTileWidth = (PLAYFIELD_X2 - PLAYFIELD_X) / 100;
		iTileHeight= (PLAYFIELD_Y2 - PLAYFIELD_Y) / 100;
 	 								  
 	//Calculate the offset of the map (e.g. where the topleft pixel of it should be drawn)
 		iStartX = PLAYFIELD_X + ((PLAYFIELD_X2 - PLAYFIELD_X) - (iTileWidth  * 100))/2;
 		iStartY = PLAYFIELD_Y + ((PLAYFIELD_Y2 - PLAYFIELD_Y) - (iTileHeight * 100))/2;

	//Loop through all the tiles
		for(int iY = 0; iY < 100; iY++)
		{	for(int iX = 0; iX < 100; iX++)
			{	//If a node or area exists here
					if(myloNodeMap[iX][iY].iNode != NO_TILE || myloNodeMap[iX][iY].iArea != NO_TILE)
					{	//Calculate where to draw this tile
			   				iPixX = iStartX + iTileWidth  * iX;
							iPixY = iStartY + iTileHeight * iY;
							
						//If its a node draw the node circle
							if(myloNodeMap[iX][iY].iNode != NO_TILE)
							{	oScreen.DrawFillCircle(iPixX + iTileWidth/2-1, iPixY + iTileHeight/2-1,
       												   iTileWidth/2+1, COLOR_WHITE, 255);
       							oScreen.DrawFillCircle(iPixX + iTileWidth/2, iPixY + iTileHeight/2,
       												   iTileWidth/2, COLOR_RED, 255);
			   				}
			   				
  						//If an area exists here draw a yellow circle
							if(myloNodeMap[iX][iY].iArea != NO_TILE)
							{	oScreen.DrawFillCircle(iPixX + iTileWidth/2, iPixY + iTileHeight/2,
       												   iTileWidth/2, COLOR_YELLOW, 255);
			   					oScreen.DrawFillCircle(iPixX + iTileWidth/2, iPixY + iTileHeight/2,
       												   iTileWidth/2, COLOR_RED, 255);
			   				}
					}
			}
		}
}
//P--------------------------------------------------------------------------------- [Route Handeling] -P
LL_Route LL_PathNodes::BuildRouteDirectly(int iStartX, int iStartY, int iEndX, int iEndY,
										  LL_LegalMovesMap* plfMap)
{	LL_Route oRoute;
	oRoute.SetX(iStartX);
	oRoute.SetY(iStartY);
	myfSearchingForRoute = true;
	oRoute = PathFind(iStartX, iStartY, iEndX, iEndY, plfMap);
	return(oRoute);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Route	LL_PathNodes::BuildRouteIndirectly(int iStartX, int iStartY, int iEndX, int iEndY, 
											LL_LegalMovesMap* plfMap, int iLayer)
{	//Vars
		int iStartNode, iEndNode;
		LL_Route oRouteAdd;
		LL_Route oRoute;
	
	//Save vars
		myiLayer = iLayer;
		
	//First formulate the start for this route
		oRoute.SetX(iStartX);
		oRoute.SetY(iStartY);

	//Find the node nearest to the start
		iStartNode 	= FindNodeNearestTo(iStartX, iStartY, plfMap);
		iEndNode	= FindNodeNearestTo(iEndX, iEndY, plfMap);

	//If we couldn't find any nodes then make no route and exit
		if(iStartNode == NO_NODE || iEndNode == NO_NODE)
		{	return(oRoute);
		}

	//Path find to the start node
		oRoute = PathFind(iStartX, iStartY, Node(iStartNode).iX, Node(iStartNode).iY, plfMap);
		
	//Now route find from the start node to end node
		oRouteAdd = GrabPathBetweenNodes(iStartNode, iEndNode); 
		oRoute.AppendRoute(oRouteAdd, true);

	//Path find to the end node
		oRouteAdd = PathFind(Node(iEndNode).iX, Node(iEndNode).iY, iEndX, iEndY, plfMap);
		oRoute.AppendRoute(oRouteAdd, true);

	//Return this route
		return(oRoute);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_PathNodes::FindNodeNearestTo(int iX, int iY, LL_LegalMovesMap* plfMap)
{	//Vars
		ASFC_LinkedList<LL_FindNodeNearestTo_Node*> lOpenNodes;
		ASFC_LinkedList<LL_FindNodeNearestTo_Node*> lClosedNodes;
		ASFC_LinkedList<LL_FindNodeNearestTo_Node>  lNodes;
		LL_FindNodeNearestTo_Node* poNode;
		LL_FindNodeNearestTo_Node  toNewNode;
		int iLoops = 0;
		bool fAdded;
	//Const
		const static int ITERATION_MAX = 10000;
				
	//Add this node to the nodes list
		toNewNode.iX = iX;
		toNewNode.iY = iY;
		toNewNode.iDirOfParent = DIR_IDLE;
		lNodes.Push(toNewNode);
		lOpenNodes.Push(&lNodes[0]);
		
	//While there's still nodes in the list grab the last and check it
		while(lNodes.Length() > 0 && iLoops < ITERATION_MAX)
		{	poNode = lOpenNodes[0];
			lClosedNodes.Push(lOpenNodes[0]);
			lOpenNodes.Delete(0);
			
				//Check and see if there's a path finding node on this checking node if so return it
						if(myloNodeMap[poNode->iX][poNode->iY].iNode != NO_NODE)
						{	//Only return if there's not a unit on this node
								if(!mypoUnitMap->IsUnitOn(poNode->iX, poNode->iY, myiLayer))
	      							return(myloNodeMap[poNode->iX][poNode->iY].iNode);
						}
		
					//Otherwise add nodes to the north south west and east if legal
						if(poNode->iDirOfParent != DIR_NORTH && plfMap->LegalNorth(poNode->iX, poNode->iY))
						{	toNewNode.iX = poNode->iX;
							toNewNode.iY = poNode->iY - 1;
							toNewNode.iDirOfParent = DIR_SOUTH;
							lNodes.Push(toNewNode);
							lOpenNodes.Push(&lNodes[lNodes.Length() - 1]);
						}
		
						if(poNode->iDirOfParent != DIR_SOUTH && plfMap->LegalSouth(poNode->iX, poNode->iY))
						{	toNewNode.iX = poNode->iX;
							toNewNode.iY = poNode->iY + 1;
							toNewNode.iDirOfParent = DIR_NORTH;
							
							//Insure the would be node hasn't already been added if not add away
								fAdded = false;
								for(int i = 0; i < lNodes.Length(); i++)
								{	if(lNodes[i].iX == toNewNode.iX && lNodes[i].iY == toNewNode.iY)
										fAdded = true;
								}
								if(fAdded == false)
								{	lNodes.Push(toNewNode);
									lOpenNodes.Push(&lNodes[lNodes.Length() - 1]);
								}
						}

						if(poNode->iDirOfParent != DIR_WEST && plfMap->LegalWest(poNode->iX, poNode->iY))
						{	toNewNode.iX = poNode->iX - 1;
							toNewNode.iY = poNode->iY;
							toNewNode.iDirOfParent = DIR_EAST;
							
							//Insure the would be node hasn't already been added if not add away
								fAdded = false;
								for(int i = 0; i < lNodes.Length(); i++)
								{	if(lNodes[i].iX == toNewNode.iX && lNodes[i].iY == toNewNode.iY)
										fAdded = true;
								}
								if(fAdded == false)
								{	lNodes.Push(toNewNode);
									lOpenNodes.Push(&lNodes[lNodes.Length() - 1]);
								}
						}

						if(poNode->iDirOfParent != DIR_EAST && plfMap->LegalEast(poNode->iX, poNode->iY))
						{	toNewNode.iX = poNode->iX + 1;
							toNewNode.iY = poNode->iY;
							toNewNode.iDirOfParent = DIR_WEST;
					
							//Insure the would be node hasn't already been added if not add away
								fAdded = false;
								for(int i = 0; i < lNodes.Length(); i++)
								{	if(lNodes[i].iX == toNewNode.iX && lNodes[i].iY == toNewNode.iY)
										fAdded = true;
								}
								if(fAdded == false)
								{	lNodes.Push(toNewNode);
									lOpenNodes.Push(&lNodes[lNodes.Length() - 1]);
								}
						}
		
					//Add 1 to our iteration count
						iLoops++;
			}

	//If we ran out of nodes just return no node :-(  			
		return NO_NODE;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Route LL_PathNodes::GrabPathBetweenNodes(int iStartNode, int iEndNode)
{	//Vars
		LL_Route oRoute;
		LL_Route oAppendRoute;
		ASFC_LinkedList<LL_RouteFindingNode*> lOpenNodes;
		ASFC_LinkedList<LL_RouteFindingNode*> lClosedNodes;
		ASFC_LinkedList<LL_RouteFindingNode>  lNodes;
		ASFC_LinkedList<LL_RouteFindingNode>  lSuccessorNodes;
		LL_RouteFindingNode  toNode;
		LL_RouteFindingNode* poCurrentNode;
		bool fSuccessorDeleted, fBreak;
		int  iListPosition;
		
	//Put the first node into the open list
		toNode.SetNode(iStartNode);
		toNode.SetNodeList(&myloNodes);
		lNodes.Push(toNode);
		lOpenNodes.Push(&lNodes[0]);
	
  	//Loop until we run out o' nodes	
		while(lOpenNodes.Length() > 0)
		{	//Pop out the node with the lowest cost
				poCurrentNode = lOpenNodes[0];
				lOpenNodes.Delete(0);
				lClosedNodes.Push(poCurrentNode);
										
			//If this node matches our ending node we've found our path
				if(poCurrentNode->Node() == iEndNode)
				{	LL_RouteFindingNode* poNode = poCurrentNode;
					ASFC_LinkedList<int> lNodePath;

					//Grab the list of nodes
						while(poNode != 0)
						{	lNodePath.Push(poNode->Node());
							poNode = poNode->Parent();
						}
						
					//Loop through the node list backwards
						for(int i = lNodePath.Length() - 1; i > 0; i--)
						{	//Figure out the route that goes between this node and the next
								for(int j = 0; j < myloNodes[lNodePath[i]].myiNodes.size(); j++)
								{	if(myloNodes[lNodePath[i]].myiNodes[j] == lNodePath[i-1])
									{	oAppendRoute.Resize(0);
          								oAppendRoute.AppendRoute(myloRoutes[myloNodes[lNodePath[i]].myiRoutes[j]], 
															myloNodes[lNodePath[i]].myfStart[j]);
										
         								oRoute.AppendRoute(oAppendRoute, true);
										//Set the for loop to stop loopin'
											j = myloNodes[lNodePath[i]].myiNodes.size() + 1;
									}
								}
						}
     				return oRoute;
				}
				
			//Create a list of successor nodes
				lSuccessorNodes = poCurrentNode->Successors();
				
			//Check to see if any of the successors already exist in the closed list
				for(int iSuccessor = 0; iSuccessor < lSuccessorNodes.Length(); iSuccessor++)
				{	//Set flag defaults
	    				fSuccessorDeleted = false;
	    								
    				//Check for repeat nodes in the open list
						for(int i = 0; i < lOpenNodes.Length() && !fSuccessorDeleted; i++)
						{	if(lOpenNodes[i]->SameAsNode(lSuccessorNodes[iSuccessor]))
							{	//If the one in the list is a better node forget this successor, delete it
									if(lOpenNodes[i]->Cost() <= lSuccessorNodes[iSuccessor].Cost())
									{	lSuccessorNodes.Delete(iSuccessor);
										iSuccessor--;
										fSuccessorDeleted = true;
									}
							}
						}
				
					//Only continue if we didn't delete the node
						if(!fSuccessorDeleted)
						{	//Check for repeat nodes in the closed list
								for(int i = 0; i < lClosedNodes.Length() && !fSuccessorDeleted; i++)
								{	if(lClosedNodes[i]->SameAsNode(lSuccessorNodes[iSuccessor]))
									{	//If the one in the list is a better node forget this successor
											if(lClosedNodes[i]->Cost() <= lSuccessorNodes[iSuccessor].Cost())
											{	lSuccessorNodes.Delete(iSuccessor);
												iSuccessor--;
												fSuccessorDeleted = true;
											}
									}
								}
						}
				}
				
			//Add all successors to the open list
				for(int iSuccessor = 0; iSuccessor < lSuccessorNodes.Length(); iSuccessor++)
				{	//Push this successor into the nodes list
	    				lNodes.Push(lSuccessorNodes[iSuccessor]);
	    							
					//If no open nodes just push it in there
						if(lOpenNodes.Length() == 0)
						{	lOpenNodes.Push(&lNodes[lNodes.Length() - 1]);
						}
					//If this node is the cheapest then stick it first
						else if(lSuccessorNodes[iSuccessor].Cost() <= lOpenNodes[0]->Cost())
     					{	lOpenNodes.PushFront(&lNodes[lNodes.Length() - 1]);
     					}
     				//If this node is more expensive then the most expensive stick it last
   	 					else if(lSuccessorNodes[iSuccessor].Cost() >= lOpenNodes[lOpenNodes.Length() - 1]->Cost())
    	 				{	lOpenNodes.Push(&lNodes[lNodes.Length() - 1]);
						}
					//If not search back from the end to figure out where to stick this bugger
   						else
     					{	fBreak = false;
     						iListPosition = -1;
           					for(int i = lOpenNodes.Length() - 1; i >= 1 && fBreak == false; i--)
     						{	if(lSuccessorNodes[iSuccessor].Cost() <= lOpenNodes[i]->Cost())
			    				{	iListPosition = i;
			    				}
     						}
     						
     						if(iListPosition != -1)
     						{	lOpenNodes.AddElement(iListPosition - 1, &lNodes[lNodes.Length() - 1]);
		    					fBreak = true;
    						}
     					}
				}
		}
	//Return
		return oRoute;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Very cool path finding algorithm, took me forever to write, I'm so spifferin' proud :-)
LL_Route LL_PathNodes::PathFind(int iStartX, int iStartY, int iEndX, int iEndY, LL_LegalMovesMap* plfMap)
{	//Vars
		ASFC_LinkedList<LL_PathFindingNode*> loOpen;
  		vector<LL_PathFindingNode*> loClosed;
  		LL_PathFindingNode loSuccessors[4];
  		bool loSuccessorExists[4];
  		int iNumSuccessors;
  		ASFC_LinkedList<LL_PathFindingNode>  loNodes;
  		LL_Route oRoute;
  		LL_PathFindingNode* oCurrentNode;
  		LL_PathFindingNode oEndNode;
  		LL_PathFindingNode toNode;
  		int iCurrentNodePos;
  		bool fSuccessorDeleted;
  		bool fBreak;
  		int iListPosition;
  		int iCurrentNodeX, iCurrentNodeY;
  		
	//Set the route to start at the start
		oRoute.SetX(iStartX);
		oRoute.SetY(iStartY);
		
	//Create what the theoretical ending node would be
		oEndNode.SetX(iEndX);
		oEndNode.SetY(iEndY);
		
	//Push the starting node onto the open list
		toNode.SetX(iStartX);
		toNode.SetY(iStartY);
		toNode.SetCostFor1stNode(oEndNode);
		loNodes.Push(toNode);
		loOpen.Push(&loNodes[0]);

	//Loop forever unless the open list is empty in which case this path is impossible
		while(loOpen.Length() > 0)
		{	//Find the path in the open list with the lowest F it always is the first
				oCurrentNode = loOpen[0];
				iCurrentNodeX = oCurrentNode->X();
    			iCurrentNodeY = oCurrentNode->Y();

			//Delete the current node off the open list
				loOpen.Delete(0);

			//If this node is the goal node we're done
				if(oCurrentNode->SameAsNode(oEndNode))
				{	LL_PathFindingNode* poNode = oCurrentNode;
					while(poNode->Parent() != 0)
					{	if(poNode->X() - 1 == poNode->Parent()->X())
						{	oRoute.PushFront(DIR_EAST);
						}
						else if(poNode->X() + 1 == poNode->Parent()->X())
						{	oRoute.PushFront(DIR_WEST);
						}
						else if(poNode->Y() - 1 == poNode->Parent()->Y())
						{	oRoute.PushFront(DIR_SOUTH);
						}
						else if(poNode->Y() + 1 == poNode->Parent()->Y())
						{	oRoute.PushFront(DIR_NORTH);
					 	}
					
     					poNode = poNode->Parent();
					}
     				return oRoute;
				}
				
			//Create the new adjacent successor nodes, the nodes where this node could move to
				//Clear out old sucessor data
	    			iNumSuccessors = 0;
 					for(int i = 0; i < 4; i++)
 						loSuccessorExists[i] = true;
				
				//North
					if(plfMap->LegalNorth(iCurrentNodeX, iCurrentNodeY))
					{	loSuccessors[iNumSuccessors] = oCurrentNode->SuccessorNorth(oEndNode);
						iNumSuccessors++;
					}
				//South
					if(plfMap->LegalSouth(iCurrentNodeX, iCurrentNodeY))
					{	loSuccessors[iNumSuccessors] = oCurrentNode->SuccessorSouth(oEndNode);
						iNumSuccessors++;
					}
				//West
					if(plfMap->LegalWest(iCurrentNodeX, iCurrentNodeY))
					{	loSuccessors[iNumSuccessors] = oCurrentNode->SuccessorWest(oEndNode);
						iNumSuccessors++;
					}
				//East
					if(plfMap->LegalEast(iCurrentNodeX, iCurrentNodeY))
					{	loSuccessors[iNumSuccessors] = oCurrentNode->SuccessorEast(oEndNode);
						iNumSuccessors++;
					}
						
			//Loop through all successors check to make sure this isn't a repeat
				for(int iSuccessor = 0; iSuccessor < iNumSuccessors; iSuccessor++)
				{	//Set flag defaults
	    				fSuccessorDeleted = false;

    				//Check for repeat nodes in the open list
						for(int i = 0; i < loOpen.Length() && !fSuccessorDeleted; i++)
						{	if(loOpen[i]->SameAsNode(loSuccessors[iSuccessor]))
							{	//If the one in the list is a better node forget this successor, delete it
									if(loOpen[i]->F() <= loSuccessors[iSuccessor].F())
									{	//loSuccessors.Delete(iSuccessor);
										loSuccessorExists[iSuccessor] = false;
										//iSuccessor--;
										fSuccessorDeleted = true;
									}
							}
						}

					//Only continue if we didn't delete the node
						if(!fSuccessorDeleted)
						{	//Check for repeat nodes in the closed list
								for(int i = 0; i < loClosed.size() && !fSuccessorDeleted; i++)
								{	if(loClosed[i]->SameAsNode(loSuccessors[iSuccessor]))
									{	//If the one in the list is a better node forget this successor
											if(loClosed[i]->F() <= loSuccessors[iSuccessor].F())
											{	//loSuccessors.Delete(iSuccessor);
												loSuccessorExists[iSuccessor] = false;
												//iSuccessor--;
												fSuccessorDeleted = true;
											}
									}
								}
						}
				}

				//Add all successors to the open list
					for(int iSuccessor = 0; iSuccessor < iNumSuccessors; iSuccessor++)
					{	if(loSuccessorExists[iSuccessor])
     					{	loNodes.Push(loSuccessors[iSuccessor]);
					
							//If no open nodes just push it in there
								if(loOpen.Length() == 0)
								{	loOpen.Push(&loNodes[loNodes.Length() - 1]);
								}
					
							//If this node is the cheapest then stick it first
								else if(loSuccessors[iSuccessor].F() < loOpen[0]->F())
	     							loOpen.PushFront(&loNodes[loNodes.Length() - 1]);
						
	     					//If this node is more expensive then the most expensive stick it last
    	 						else if(loSuccessors[iSuccessor].F() > loOpen[loOpen.Length() - 1]->F())
	    	 						loOpen.Push(&loNodes[loNodes.Length() - 1]);

     						//If not search back from the end to figure out where to stick this bugger
     							else
     							{	fBreak = false;
     								iListPosition = -1;
           							for(int i = loOpen.Length() - 2; i >= 1 && fBreak == false; i--)
     								{	if(loSuccessors[iSuccessor].F() < loOpen[i]->F())
				     					{	iListPosition = i;
				     					}
     								}
     							
     								if(iListPosition != -1)
     								{	loOpen.AddElement(iListPosition - 1, &loNodes[loNodes.Length() - 1]);
			     						fBreak = true;
    								}
     							}
						}
					}
					
				//Send the current node to the closed list
					loClosed.push_back(oCurrentNode);
			}
	
	//Return the route
		return(oRoute);
}
