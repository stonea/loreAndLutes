/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			ready.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LL_READY_H_
#define LL_READY_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//Parent
	#include "statviewer.h"
//Dependencies
	#include <asfc/linkedlist.h>
//Aggregates
	#include <asfc/input.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												 Prototype
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
class LL_Ready : public LL_StatViewer
{	public:
	//- [Construction] -
		LL_Ready();
	//- [Display] -
		void Display(int iPlayer, LL_Game* pGame);
		
	protected:
	//P- [Ready] -P
		void SetupScreen();
		void ProcessOption(int iOption);
	
	//Vars
		LL_Game* mypoGame;
		int myiScreen;
		int myiPlayer;
};

#endif
