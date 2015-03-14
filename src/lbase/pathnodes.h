/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			pathnodes.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LL_PATHNODES_H_
#define LL_PATHNODES_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include <asfc/linkedlist.h>
	#include "aistructures.h"
//Dependencies
	#include <vector>
	#include <iostream>
	#include <asfc/surface.h>
	#include <asfc/timer.h>
	#include "guimetrics.h"
	#include "route.h"
	#include "legalmovesmap.h"
	#include "pathfindingnode.h"
	#include "routefindingnode.h"
	#include "unitmap.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PathNodes
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_PathNodes
{	public:
	//Const
		static const int NO_NODE  = -1;
		static const int NO_AREA  = -1;
		static const int NO_ROUTE = -1;

	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);
		MEMVAR_SETGET(SetUnitMap, UnitMap, LL_UnitMap*, mypoUnitMap);
	//- [Node Handeling] -
		LL_Node& Node(int iNum);
		void	 AddNode(LL_Node oNode);
		void	 DynamicallyPlotNode(int iNodeX, int iNodeY);
		int		 NumNodes();
		void	 RemoveNode(int iX, int iY);
		int		 NodeOn(int iX, int iY);
		void	 ClearNodes();
	//- [Area Handeling] -
		LL_Area& Area(int iNum);
		int		 AreaOn(int iX, int iY);
		void	 AddArea(LL_Area oArea);
		int		 NumAreas();
		void	 RemoveArea(int iX, int iY);
		void	 ClearAreas();
		void	 ClearMap();
	//- [Route Handeling] -
		LL_Route&	Route(int iNum);
		void		AddRoute(LL_Route oRoute);
		int			NumRoutes();
		int			RemoveRoute(int iX, int iY);
		int			ClearRoutes();
		int			RouteOn(int iX, int iY);
		LL_Route	GrabRoute(int iStartX, int iStartY, int iEndX, int iEndY);
	//- [Drawing] -
		void Draw(ASFC_Surface &oScreen, int iStartX, int iStartY, int iPixStartX, int iPixStartY);
		void DrawGemView(ASFC_Surface &oScreen);
 		
//	protected:
	//P- [Route Handeling] -P
		LL_Route	BuildRouteDirectly(int iStartX, int iStartY, int iEndX, int iEndY,
  									   LL_LegalMovesMap* plfMap);
  		LL_Route	BuildRouteIndirectly(int iStartX, int iStartY, int iEndX, int iEndY,
  									   LL_LegalMovesMap* plfMap, int iLayer);
  		int			FindNodeNearestTo(int iX, int iY, LL_LegalMovesMap* plfMap);
  		LL_Route	GrabPathBetweenNodes(int iStartNode, int iEndNode);
	  	LL_Route	PathFind(int iStartX, int iStartY, int iEndX, int iEndY, LL_LegalMovesMap* plfMap);

	protected:
	//Type
		const static int NO_TILE = -1;
		struct LL_PathNodeMapObject
		{	int  iNode, iArea;
		
			LL_PathNodeMapObject::LL_PathNodeMapObject()
			{	iNode = NO_TILE;
				iArea = NO_TILE;
			}
		};
		struct LL_FindNodeNearestTo_Node
		{	int iX;
			int iY;
			ASFC_DIRECTION iDirOfParent;
		};
	//Vars
		ASFC_LinkedList<LL_Node> myloNodes;
		ASFC_LinkedList<LL_Area> myloArea;
		LL_PathNodeMapObject myloNodeMap[100][100];
		ASFC_LinkedList<LL_Route> myloRoutes;
		bool myfSearchingForRoute;
		ASFC_LinkedList<LL_Route> myltoAIRoute;
		LL_UnitMap* mypoUnitMap;
		int myiLayer;
};

#endif
