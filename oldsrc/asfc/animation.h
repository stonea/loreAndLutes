/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS
	By: Andy Stone

	File for: ASFC_Animation
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef ASFC_ANIMATION_H_
	#define ASFC_ANIMATION_H_
	
//Uses
	#include "multiimage.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												ASFC_Animation
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class ASFC_Animation
{	public:
	//- [Constuctors] -
 		ASFC_Animation();
	//- [Loading] -
		virtual int Load(string sPath, const int & iWidth, const int & iHeight, Uint8 iRed,
  						 Uint8 iGreen, Uint8 iBlue);
	//- [Drawing] -
		int  BlitTo(ASFC_Surface &screen, const int & iX, const int & iY);
 		void Reset();
 		ASFC_MultiImage& GetImage();
 	
 	protected:
 	//Vars
 		ASFC_MultiImage myoImage;
 		bool myfAnimated;
 		int myiFrame;
};

//Now ending animation.h
	#endif
