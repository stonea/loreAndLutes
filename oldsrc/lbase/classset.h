/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			classet.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A classet maps a string identifier (the name of a class) to a position within a file.
*/
#ifndef LL_CLASSSET_H_
#define LL_CLASSSET_H_
//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Parent
	#include "set.h"
//Agregates
	#include <asfc/linkedlist.h>
	#include <vector>
	#include <string>
//Dependencies
	#include <iostream>
	using namespace std;
//Realizes
	#include <textedit/text.h>
	#include <loop/loop.h>

//��������������������������������������������������������������������������������������������������������
//											LL_ClassSetEntry
//��������������������������������������������������������������������������������������������������������	
struct LL_ClassSetEntry
{	int 	myiClassCode;
	string	mysDescription;
	int 	myiStart;
	int 	myiEnd;
};

//��������������������������������������������������������������������������������������������������������
//												LL_ClassSet
//��������������������������������������������������������������������������������������������������������
class LL_ClassSet : public LL_Set
{	public:
	//- [Constuctors] -
 		LL_ClassSet();
		MEMVAR_SETGET(SetLOOP, LOOP, LOOP_LOOP*, mypoLOOP);
	//- [Class Handeling] -
		void 	  			AddClassEntry(LL_ClassSetEntry &oAdd);
		void 	  			RemoveClassEntry(int &iNum);
		void				Clear();
		LL_ClassSetEntry&	ClassEntry(C_i(iNum));
	  	int 	  			NumClassEntry();
		int					FindClassEntry(string sClass);
	//- [File I/O] -
		void 	Save(ofstream &oFile);
		void	Load(ifstream &oFile, string sClassName);

 	private:
 	//P- [Editting] -P
 		string 	ClassFileName();
 		void 	MoveEntryTo(int iEntryNum, int iFirstLine);
	//P- [Debugging] -P
 		bool ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum));
 	//Vars
 		ASFC_LinkedList<LL_ClassSetEntry> mylClasses;
 		string		mysClassesFile;
 		LOOP_LOOP*	mypoLOOP;
	//Const
		//Keys
			const static SDLKey KEY_DELETE = SDLK_DELETE;
};

//Now ending llclassset.h
	#endif
