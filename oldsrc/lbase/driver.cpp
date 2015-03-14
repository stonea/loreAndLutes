/*Protected under the GNU General Public License read and see copying.txt for details

   `\    /,--.\ ,--.  ,,--     /\    ||     ,. ,. __||__ ,,--  ,---             |             // , .
   ||    ||  || |__'  ||__     \/    ||     || || --,.-- ||__  `__              |            //
   ||__. ||__|| |-\\  ||--    / \/   ||___  ||_||   ||   ||--     `         \   |   /       //    '  
   ----` \____/ || \\ ''__    \_/\   `----  `---'   ||   ''__  ___/           * * *        //       ,
   ----------------------------------------------------------------------=== *  +  * ===--//    `   \ 
                                                                              * * *      //          * 
Powered By: Annex Solutions' LOOP, TextEdit, and ASFC, plus PhysFS and SDL  /   |   \   //     *      \
Written and Designed By: Andy Stone                                             |      // *           '
Much Thanks To: Eoin Coffey, Sam Latinga, ...                                   |     // 
See credits.txt for full credit (where credit is due!)                               //`   |   `  .
Protected under the GNU General Public License (see license.txt)                    //    -*-
                                                                                   //      |         ,
==================================================================================`/.           . 
Source Last Updated: MM/DD/YY                                                     /      `         `
Version GRK VV.SS.RR                                                             / `
See updates.txt for a list of changes                                           /     .        /
Visit Lore And Lutes On the Web! Visit: http://INSERTADRESSHERE.NETORWHATEVER  /               *     .
                                                                              /       `       /
For the best lookin' source code please set your tab size to be four spaces, /    .  
and if possible size your window to have 107 characters across the screen   /    .               . 
horizontally.                                                              /           .   `         `
-------------------------------------------------------------------------*/










































/* ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			driver.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
   Description:	This is the driver program for the L&L base module. When this module is being compiled
   				into a library all code within here SHOULD be commented out. Code can go into this
				module for testing purposes (if this module is being compiled as an executable).
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initilization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Debugging objects
	#include <asfc/screen.h>
	#include <asfc/input.h>
	#include "painter.h"
	#include "game.h"
	#include "map.h"
	#include "terrainset.h"
	#include "terrainmap.h"
	#include "player.h"
	#include "route.h"
	#include "pathnodes.h"
	#include "legalmovesmap.h"
//	#include <asfc/filemanager.h>
	#include <asfc/linkedlist.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Main
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Point of execution, program starts here
int main(int argc, char *argv[])
{///	LL_DataRecorder oRecord;
//	oRecord.LoadGame("t");
}

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												xyzzy
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//-------------------------------------------------------------------------------------------- [xyzzy] -
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
