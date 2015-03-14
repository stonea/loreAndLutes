/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			scripteditem.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: An item that when used will call a LOOP object.
*/
#ifndef LL_SCRIPTEDITEM_H_
#define LL_SCRIPTEDITEM_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "item.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_ScriptedItem
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_ScriptedItem : public LL_Item
{	public:
	//type
		enum LL_ScriptedItemMessage
		{	MESSAGE_GLOBAL = 0,			//Call the global script
			MESSAGE_PING,				//Call all objects
			MESSAGE_PING_CLASS,			//Call all objects of a certain class
			MESSAGE_PING_CLASS_DERIV,	//Call all objects of a certain class and its child classes
			MESSAGE_NUM_MESSAGES
		};

	//- [Constuctors] -
 		LL_ScriptedItem();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsPath);
	//- [Callbacks] -
		void Run();
		void Talk();
		void Look();
		void Search();
		void Attack();
	//- [Attributes] -
		MEMVAR_SETGET(SetCall, Call, string, sCall);
		MEMVAR_SETGET(SetMessage, Message, LL_ScriptedItemMessage, myiMessage);
		MEMVAR_SETGET(SetMessageClass, MessageClass, string, mysMessageClass);

 	protected:
 		string sCall;
		LL_ScriptedItemMessage myiMessage;
		string mysMessageClass;
};

//Now ending scripteditem.h
	#endif
