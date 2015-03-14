/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes

    File: effects.h
    By:   Andy Stone
    Desc:	
*/

#ifndef ASFC_EFFECTS_H_
#define ASFC_EFFECTS_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include "timer.h"
//Dependencies
	#include "screen.h"
	#include "image.h"
	#include "linkedlist.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class ASFC_Effects
{	public:
	//- [Construction] -
		ASFC_Effects();
	//- [Effects] -
/*		void FadeOutAndIn(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen);
		void Dissolve(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen);
		void Triambulate(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen);
		void CheckerBoard(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen);
		void Blend(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen, int iSpeed = 100, int iStep = 5);
		void SplitVert(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen, int iSpeed = 5, int iStep = 2);
		void SplitHoriz(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen, int iSpeed = 5, int iStep = 2);
		
	protected:
		//Vars
			ASFC_Timer oTimer;
		//Type
			struct ASFC_Effects_Image_Vector
			{	ASFC_Surface oSurf;
				int iX, iY;
				int iDeltaX, iDeltaY;
			};*/
};

#endif
