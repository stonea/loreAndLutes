/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS
	By: Andy Stone

	File for: ASFC_Animation
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "animation.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												ASFC_Animation
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
ASFC_Animation::ASFC_Animation()
{	myiFrame = -1;
	myfAnimated = false;
}
//-------------------------------------------------------------------------------------------- [Loading] -
int ASFC_Animation::Load(string sPath, const int & iWidth, const int & iHeight, Uint8 iRed, Uint8 iGreen,
		 				 Uint8 iBlue)
{	myiFrame = -1;
	myfAnimated = false;
	return(myoImage.Load(sPath, iWidth, iHeight, iRed, iGreen, iBlue));
}
//------------------------------------------------------------------------------------------- [Drawing] -
int ASFC_Animation::BlitTo(ASFC_Surface &screen, const int & iX, const int & iY)
{	if(!myfAnimated)
	{	if(myiFrame+1 < myoImage.NumImages())
			myiFrame++;
		else
			myiFrame = 0;
		
 		myfAnimated = true;
	}

	myoImage.BlitTo(screen, iX, iY, myiFrame);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Animation::Reset()
{	myfAnimated = false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_MultiImage& ASFC_Animation::GetImage()
{	return(myoImage);
}
