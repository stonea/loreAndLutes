/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			unit.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "unit.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Unit
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Unit::LL_Unit()
	:	myiIdentifierSeg(NULL_SEG),
		myiIdentifierOff(NULL_OFF),
		myiX(NULL_X),
  		myiY(NULL_Y),
  		myiLayer(NULL_LAYER),
		myfNullify(false)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Unit::SaveRecordingInfo(ofstream &oFile)
{	//Vars
		unsigned char c;

	//'| ' 'myiX' 'myiY' 'myiLayer' 'myfNullify' ' '
		oFile << "| ";
		c = myiX;		oFile.write(&c, 1);
		c = myiY;		oFile.write(&c, 1);
		c = myiLayer;	oFile.write(&c, 1);
		oFile << myfNullify << " ";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Unit::LoadRecordingInfo(ifstream &oFile)
{	//Vars
		unsigned char c;

	//'| ' 'myiX' 'myiY' 'myiLayer' 'myfNullify' ' '
		oFile >> c;
		if(c != '|')
		{	cerr << "ERR loading recording information\n";
			return false;
		}
		oFile.read(&c, 1);		myiX = (Uint8)c;
		oFile.read(&c, 1);		myiY = (Uint8)c;
		oFile.read(&c, 1);		myiLayer = (Uint8)c;
		oFile >> myfNullify;
	//return
		return true;
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_Unit::Run()
{	cout << "ERR LL_Unit::Run() 000, Run() not overloaded!\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Unit::Talk()
{	cout << "ERR LL_Unit::Talk() 000, Talk() not overloaded!\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Unit::Look()
{	cout << "ERR LL_Unit::Look() 000, Look() not overloaded!\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Unit::Push()
{	cout << "ERR LL_Unit::Push() 000, Push() not overloaded!\n";
	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Unit::Search()
{	cout << "ERR LL_Unit::Search() 000, Search() not overloaded!\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Unit::Attack()
{	cout << "ERR LL_Unit::Attack() 000, Attack() not overloaded!\n";
}
