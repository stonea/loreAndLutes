/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes

    File: multiimage.cpp
    By:   Eoin Coffey
    Desc:	
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Self
	#include "multiimage.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												 ASFC_MultiImage
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//------------------------------------------------------------------------------------- [Construction] -
ASFC_MultiImage::ASFC_MultiImage()
{
	myTransRed = myTransGreen = myTransBlue = myXB = myYB = -1;
}

ASFC_MultiImage::ASFC_MultiImage(string file, int xb, int yb, int transred, int transgrn, int transblu)
{
	DBG("In ASFC_MultiImage::ASFC_MultiImage(string, int, int, int, int, int)\n");
	this->Load(file, xb, yb, transred, transgrn, transblu);
	DBG("Leaving ASFC_MultiImage::ASFC_MultiImage(string, int, int, int, int, int)\n");
}

ASFC_MultiImage::~ASFC_MultiImage() { }

void ASFC_MultiImage::BlitTo(ASFC_Surface &surf, int x, int y, int num)
{
	DBG("In ASFC_MultiImage::BlitTo()\n");
	if (num < this->NumImages())
		surf.Blit(mySurface, x, y, myXB * num, 0, myXB, myYB);
	DBG("Leaving ASFC_MultiImaeg::BlitTo()\n");
}
//------------------------------------------------------------------------------------------ [Loading] -
//*AIS
int ASFC_MultiImage::Load(string sFile, int iXB, int iYB, int transred, int transgrn,
			  			   int transblu)
{	
	DBG("In ASFC_MultiImage::Load(string, int, int, int, int, int)\n");
	myXB = iXB;
	myYB = iYB;
	myTransRed = transred;
	myTransGreen = transgrn;
	myTransBlue = transblu;
	return(this->LoadImage(sFile, transred, transgrn, transblu));
	DBG("Leaving ASFC_MultiImage::Load(string, int, int, int, int, int)\n");
}
