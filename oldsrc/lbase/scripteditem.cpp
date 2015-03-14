/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			scripteditem.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "scripteditem.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_ScriptedItem
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_ScriptedItem::LL_ScriptedItem()
{	myiMessage = MESSAGE_GLOBAL;
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_ScriptedItem::Save(ofstream &oFile)
{	//"Image file path"  %Custom image%
 		oFile << Qoute(ImageFile()) << " ";
		oFile << myfCustomImage << " ";
	//"Description"
		oFile << Qoute(Identifier()) << " ";
	//%Message%
		oFile << LL_ScriptedItemMessage(myiMessage) << " ";
	//"Message class"
		oFile << Qoute(mysMessageClass) << " ";
	//"Call"
		oFile << Qoute(Call()) << " ";
	//<endl>
		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedItem::Load(ifstream &oFile, string sGraphicsPath)
{	//Vars
		string sImageFile, sDescription, sCall;
		int iMessage;

	//"Image file path" %Custom image%
 		sImageFile = ReadString(oFile);
		oFile >> myfCustomImage;
		LoadAnimation(sImageFile, sGraphicsPath, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
	//"Description"
		sDescription = ReadString(oFile);
		SetIdentifier(sDescription);
	//%Message%
		oFile >> iMessage;
		myiMessage = LL_ScriptedItemMessage(iMessage);
	//"Message class"
		mysMessageClass = ReadString(oFile);
	//"Call"
		sCall = ReadString(oFile);
		SetCall(sCall);
}
//----------------------------------------------------------------------------------------- [Callbacks] -
void LL_ScriptedItem::Run()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedItem::Talk()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedItem::Look()
{	cerr << "Item looked at!\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedItem::Search()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedItem::Attack()
{
}
