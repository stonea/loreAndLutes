/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS
	By: Andy Stone

	File for: TE_Text
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef TEXT_H_
	#define TEXT_H_
	
//Uses
	#include <asfc/utils.h>
	#include <string>
	#include <fstream>
	using namespace std;
//Recognizes
	#include <asfc/console.h>
//Aggregates
	#include <vector>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												TE_Text
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class TE_Text
{	public:
	//- [Constuctors] -
 		TE_Text();

	//- [File I/O] -
		bool Save();
		void SaveAs(string sFileName);
		void Load(string sFileName);
		
	//- [Character and Cursor] -
		void 		Insert(char c, int iColumn, int iRow);
		void 		Insert(char c);
		void		Delete(int iColumn, int iRow);
		void		Delete();
		void		BackSpace();
		void 		MoveCursor(int iColumn, int iRow);
		void 		MoveCursor(int iCharsDown);
		MEMVAR_GET(	CursorColumn, 	int, myiCursorColumn);
		MEMVAR_GET(	CursorRow,		int, myiCursorRow);
		MEMVAR_SET(	SetAutoCursor,	int, myfAutoCursor);
		string		GetData(int iRow);
		void		SetData(int iRow, string s);
		void		AddRow(int iColumn, int iAfterRowNum);
		void		DeleteRow(int iRowNum);
		MEMVAR_GET(	MaximumNumColumns,		int,	myiMaximumNumColumns);
		MEMVAR_SET(	SetMaximumNumColumns,	int,	myiMaximumNumColumns);
		int			NumRows();
		void		AddLine(string sText);
		void		AddLine(string sText, int iAfterLine);
		void		Clear();
		void		String(string* poString);
		void		ReadString(string s, bool fReset);
		TE_Text&	operator<<(string s);
		int			LineAtChar(int iChar);

	//- [Testing] -
		void OutputTextToConsole();

 	private:
 	//Vars
		vector<string>		mylsData;
  		string				mysLastSavedTo;
    	bool				myfSavedBefore;
    	int					myiCursorColumn;
    	int					myiCursorRow;
     	bool				myfAutoCursor;
      	int					myiMaximumNumColumns;
	//Const
		static const int TAB_SIZE = 4;
};

//Now ending text.h
	#endif
