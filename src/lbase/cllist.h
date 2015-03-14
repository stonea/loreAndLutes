/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			cllist.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_CLLIST_H_
#define LL_CLLIST_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Realizes
	#include "eventqueue.h"
//Aggregates
	#include <asfc/linkedlist.h>
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_CLList
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_CLList
{	public:
	//- [Constuctors] -
 		LL_CLList();
 		MEMVAR_SETGET(SetEventQueue, EventQueue, LL_EventQueue*, mypoEventQueue);
 	//- [Entry Adding] -
 		void AddCollision(	int iSourceX, int iSourceY, int iDestinationX,
							int iDestinationY, int iLayer, int iSeg, int iOff
						 );
 	//- [Entry Cheking] -
 		void CheckEntries();

 	private:
 	//Type
 		struct LL_CollisionEntry
 		{	int iSourceX, iSourceY;
 			int iDestinationX, iDestinationY;
 			int iLayer;
 			int iSeg, iOff;
 		};
 	
	//Vars
		ASFC_LinkedList<LL_CollisionEntry> mylCollisions;
		LL_EventQueue* mypoEventQueue;
};

#endif
