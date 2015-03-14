/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS
	By: Andy Stone

	File for: TE_Text
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "text.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												TE_Text
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
TE_Text::TE_Text()
	:	mysLastSavedTo(""),
		myfSavedBefore(false),
		myiCursorColumn(0),
		myiCursorRow(0),
		myfAutoCursor(true),
		myiMaximumNumColumns(999999)
{	mylsData.resize(0);
}
//------------------------------------------------------------------------------------------- [File I/O] -
bool TE_Text::Save()
{	//If we've saved before (so we have an actual known file to save to)
		if(myfSavedBefore)
		{	//Vars
				ofstream oFile(mysLastSavedTo.c_str());		//Open the last known opened file
		
			//Loop through all of our data
				for(int i = 0; i < mylsData.size(); i++)
				{	//Output this piece o' data followed by a new line char
      					oFile << mylsData[i] << endl;
						
				}
				
			//Return true for Yes! We hast saved
				return(true);
		}
	//Else a jerk and yell at the user, returning false for FAILURE!
		else
		{	cout << "Many a silly chickens laugh at your ignorance!\n";
			cout << "You have tried to save a text but hast not given\n";
			cout << "it the proper file name. Whazzamattawityoufoo!\n";
			
			return(false);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::SaveAs(string sFileName)
{	//Reset our last saved to file
		mysLastSavedTo = sFileName;
		myfSavedBefore = true;
	//Now save
		Save();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::Load(string sFileName)
{	//Vars
		ifstream 	oFile;
		const int 	MAX_CHARS = 999999;
		char		str[MAX_CHARS];
		string		s;

	//Reset all of our old data
		mylsData.resize(0);

	//Open sFileName
		oFile.open(sFileName.c_str());
		
	//Update our last saved (really last handled thing)
		mysLastSavedTo = sFileName;
		myfSavedBefore = true;
		
	//If it can't be opened well just create a blank line and return 
		if(oFile.fail())
		{	mylsData.push_back("");
  			return;
		}

	//Read until we can read no more
		while(!oFile.eof())
		{	//Get a line
				oFile.getline(&str[0], MAX_CHARS);
				s = str;				

			//Push this line in if we're not at the end
				if(!oFile.eof())
				{	mylsData.push_back(s);
				}
		}
		
	//Close the file
		oFile.close();
}
//------------------------------------------------------------------------------- [Character and Cursor] -
void TE_Text::Insert(char c, int iColumn, int iRow)
{	//Vars
		string s = mylsData[iRow];
		int iNumChars = 0;
		
	//Calculate the # of chars currently on the row (tabs and all)
		for(int i = 0; i < s.length(); i++)
		{	//If we have a tab add the # of chars in a tab
  				if(s[i] == '\t')
		  			iNumChars += TAB_SIZE;
			//Else assume we have a normal char
				else
					iNumChars += 1;
		}

	//Insert this char in if theres room for it
		if(iNumChars + 1 < myiMaximumNumColumns)
			mylsData[iRow].insert(iColumn, &c, 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::Insert(char c)
{	//Insert a char at the current cursor position
		Insert(c, myiCursorColumn, myiCursorRow);

	//If AutoCursor is on move the cursor down a char
		if(myfAutoCursor)
			MoveCursor(1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::Delete(int iColumn, int iRow)
{	//Be a pall kill this char!
		mylsData[iRow].erase(iColumn, 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::Delete()
{	//Insert a char at the current cursor position
		Delete(myiCursorColumn, myiCursorRow);
}

//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::BackSpace()
{	//If there's a previous char to delete, delete
		if(myiCursorColumn - 1 >= 0)
		{	Delete(myiCursorColumn-1, myiCursorRow);
		
			//If AutoCursor is on move the cursor up a char
				if(myfAutoCursor)
					MoveCursor(-1);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::MoveCursor(int iColumn, int iRow)
{	//Move the cursor to the desired local
		myiCursorColumn = iColumn;
		myiCursorRow	= iRow;	
		
	//If we're negative send to zero
		if(myiCursorColumn < 0) myiCursorColumn = 0;
		if(myiCursorRow < 0) 	myiCursorRow 	= 0;

	//If we're too positive send to the max
		if(myiCursorRow		>= mylsData.size())
  			myiCursorRow = mylsData.size() - 1;
		if(myiCursorColumn 	> mylsData[myiCursorRow].length())
  			myiCursorColumn = mylsData[myiCursorRow].length();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::MoveCursor(int iCharsDown)
{	//Vars
		bool fDone;
		int	 iOldCursorColumn 	= myiCursorColumn;
		int	 iOldCursorRow		= myiCursorRow;

	//Add iCharsDown to the current cursor row
		myiCursorColumn += iCharsDown;
		
	//While the cursor column is too small
		fDone = false;
		while(myiCursorColumn < 0 && !false)
		{	//If theres no legal previos row to move to
				if(myiCursorRow - 1 < 0)
				{	//Break out
						myiCursorColumn = iOldCursorColumn;
						myiCursorRow	= iOldCursorRow;
						fDone = true;
				}
			//Else
				else
				{	//Move to the previous row
    					myiCursorRow 	-= 1;
						
					//Update the cursor column
						myiCursorColumn	+=  mylsData[myiCursorRow].length() + 1;
				}
		}
	
	//While the cursor column is too big
		fDone = false;
		while(myiCursorColumn > mylsData[myiCursorRow].length() && !false)
		{	//Move to the next row
				myiCursorColumn -= mylsData[myiCursorRow].length() + 1;
				myiCursorRow 	+= 1;
				
			//If the cursor is too far down the file
				if(myiCursorRow >= mylsData.size())
				{	//Set the cursor to the last row
					myiCursorRow = mylsData.size()-1;
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(	CursorColumn, 	int, myiCursorColumn);
//{
//}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(	CursorRow,		int, myiCursorRow);
//{
//}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SET(	SetAutoCursor,	int, myfAutoCursor);
//{
//}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string	TE_Text::GetData(int iRow)
{	//If we try to access an invalid piece of data off the return ""
		if(iRow < 0 || iRow >= mylsData.size())
			return("");	

	//Else simply return that piece o' data
		return(mylsData[iRow]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::SetData(int iRow, string s)
{	mylsData[iRow] = s;
}

//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void	TE_Text::AddRow(int iColumn, int iAfterRowNum)
{	//Vars
		string s;
		
	//Copy everything after iColumn on row # iAfterRowNum
		s = mylsData[iAfterRowNum].substr(iColumn, mylsData[iAfterRowNum].length() - iColumn);
		
	//Delete that everything out now
		mylsData[iAfterRowNum].erase(iColumn, mylsData[iAfterRowNum].length() - iColumn);

	//Add in a row
		mylsData.insert(mylsData.begin() + iAfterRowNum+1, s);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void	TE_Text::DeleteRow(int iRowNum)
{	//Die row, die!
		mylsData.erase(mylsData.begin() + iRowNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_GET(	MaximumNumColumns,		int,	myiMaximumNumColumns);
//{
//}

//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SET(	SetMaximumNumColumns,	int,	myiMaximumNumColumns)
//{
//}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	TE_Text::NumRows()
{	//Simply return the size of the list
		return(mylsData.size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::AddLine(string sText)
{	mylsData.push_back(sText);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::AddLine(string sText, int iAfterLine)
{	//If its before 0 just set element 0 to it
		if(iAfterLine < 0)
			mylsData[0] = sText;
	//Else add it after iAfterLine
		else
		{	mylsData.insert(mylsData.begin() + iAfterLine+1, sText);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::String(string* poString)
{	*poString = "";
	
	for(int i = 0; i < mylsData.size(); i++)
	{	*poString += mylsData[i];
 		if(i != mylsData.size() - 1)
   			*poString += "\n";
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void TE_Text::ReadString(string s, bool fReset)
{	//Vars
		int iPos = 0;
		string ts;
		
	//Size our data to zero if reset is on
		if(fReset)
			mylsData.resize(0);
		
	//While there's still some more good stringin'
		while(iPos < s.size())
		{	//Read in 1 line of text
				ts = "";
				while(s[iPos] != '\n' && iPos < s.size())
				{	ts += s[iPos];
					iPos++;
				}
				
			//Inser t this line in
				AddLine(ts);
				
			//Move down after the newline
				iPos++;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...}
TE_Text& TE_Text::operator<<(string s)
{	//Read in this string
		ReadString(s, false);

	//Return this text
		return(*this);
}
//-------------------------------------------------------------------------------------------- [Testing] -
void TE_Text::OutputTextToConsole()
{	//Loop through all the data and output it
		for(int i = 0; i < mylsData.size(); i++)
		{	cout << mylsData[i] << endl;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...}
void TE_Text::Clear()
{	mylsData.resize(0);
	mylsData.push_back("");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...}
int	TE_Text::LineAtChar(int iChar)
{	//Vars
		int iLine = 0;

	//While we still haven't found that line
		while(iChar > 0)
		{	//If iChar is past line iLine
				if(iChar > mylsData[iLine].size())
				{	//Move down 1 line and down that many chars
						iChar -= (mylsData[iLine].size()+1) + 1;	//+1 for binary files
      					iLine++;
				}
			//Otherwise we're done at this line
				else
				{	iChar = 0;
				}
		}
		
	//Return this line #
		return iLine;
}
