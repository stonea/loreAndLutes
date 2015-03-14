/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			transport.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "transport.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Transport
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Transport::LL_Transport()
	: myiRoomNum(0),
	  myiTransportX(50),
	  myiTransportY(50),
	  myiEffect(BORDER_EFFECT_NONE),
	  myfTransportIfPlayerOn(false),
	  myfTransportIfTalk(false),
	  myfTransportIfLook(false),
	  myfTransportIfPush(false),
	  myfTransportIfSearch(false),
	  myfTransportIfAttack(false)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Transport::Save(ofstream &oFile)
{	//%X Local%, %Y Local%, %Layer%
		oFile << Val(myiX) << " " << Val(myiY) << " " << Val(myiLayer) << " ";
	//"Image file" ?Custom Image?
		oFile << Qoute(ImageFile()) << " ";
		oFile << myfCustomImage << " ";
	//%RoomNum% %TransportX% %TransportY%
		oFile << myiRoomNum << " " << myiTransportX << " " << myiTransportY << " ";
	//%Effect%
		oFile << (int)myiEffect << " ";
	//%TransportIfPlayerOn% %TransportIfTalk% %TransportIfLook% %TransportIfPush%
	//%TransportIfSearch% %TransportIfAttack%
		oFile 	<< myfTransportIfPlayerOn << " " << myfTransportIfTalk << " " << myfTransportIfLook
				<< " " << myfTransportIfPush << " " << myfTransportIfSearch << " "
				<< myfTransportIfAttack << " ";
	//<endl>
 		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Transport::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		int iX, iY, iL;
		string sImage;
		int ti;
	
	//%X Local%, %Y Local%, %Layer%
		oFile >> iX >> iY >> iL;
		SetX(iX);
		SetY(iY);
		SetLayer(iL);
	//"Image file" ?Custom Image?
		sImage = ReadString(oFile);
		oFile >> myfCustomImage;
		LoadAnimation(sImage, sGraphicsDir, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
	//%RoomNum% %TransportX% %TransportY%
		oFile >> myiRoomNum >> myiTransportX >> myiTransportY;
	//%Effect%
		oFile >> ti;
		myiEffect = (LL_BORDER_EFFECT)ti;
	//%TransportIfPlayerOn% %TransportIfTalk% %TransportIfLook% %TransportIfPush%
	//%TransportIfSearch% %TransportIfAttack%
		oFile 	>> myfTransportIfPlayerOn >> myfTransportIfTalk >> myfTransportIfLook
				>> myfTransportIfPush >> myfTransportIfSearch >> myfTransportIfAttack;
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_Transport::Run()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Transport::Talk()
{	if(myfTransportIfTalk)
		mypoEventQueue->GoMap(myiRoomNum, (int)myiEffect, myiTransportX, myiTransportY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Transport::Look()
{	if(myfTransportIfLook)
		mypoEventQueue->GoMap(myiRoomNum, (int)myiEffect, myiTransportX, myiTransportY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Transport::Push()
{	if(myfTransportIfPush)
		mypoEventQueue->GoMap(myiRoomNum, (int)myiEffect, myiTransportX, myiTransportY);
	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Transport::Search()
{	if(myfTransportIfSearch)
		mypoEventQueue->GoMap(myiRoomNum, (int)myiEffect, myiTransportX, myiTransportY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Transport::Attack()
{	if(myfTransportIfAttack)
		mypoEventQueue->GoMap(myiRoomNum, (int)myiEffect, myiTransportX, myiTransportY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Transport::Init()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Transport::Seen()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Transport::PlayerOn()
{	if(myfTransportIfPlayerOn)
		mypoEventQueue->GoMap(myiRoomNum, (int)myiEffect, myiTransportX, myiTransportY);
}
