/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			classet.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "classset.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_ClassSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_ClassSet::LL_ClassSet()
{
}
//------------------------------------------------------------------------------------ [Class Handeling] -
void LL_ClassSet::AddClassEntry(LL_ClassSetEntry &oAdd)
{	mylClasses.Push(oAdd);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ClassSet::RemoveClassEntry(int &iNum)
{	mylClasses.Delete(iNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ClassSet::Clear()
{	mylClasses.Resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_ClassSetEntry& LL_ClassSet::ClassEntry(C_i(iNum))
{	return(mylClasses[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_ClassSet::NumClassEntry()
{	return(mylClasses.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_ClassSet::FindClassEntry(string sClass)
{	//Loop through all the classes
		for(int i = 0; i < NumClassEntry(); i++)
		{	//If sClass matches this class's identifier (in all caps) return the local
				if(UpperString(mylClasses[i].mysDescription) == UpperString(sClass))
				{	return(i);
				}
		}
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_ClassSet::Save(ofstream &oFile)
{	//Output the header info
		oFile << ".classset 0\n";
	//%# O' Classes%
		oFile << mylClasses.Length() << endl;
	//<Loop for # of classes>
		for(int i = 0; i < mylClasses.Length(); i++)
		{	//"Description"
				oFile << Qoute(mylClasses[i].mysDescription) << " ";
			//%Bounded Start%
				oFile << mylClasses[i].myiStart << " ";
			//%Bounded End%
				oFile << mylClasses[i].myiEnd << " ";
			//End line
				oFile << endl;
		}
	//Close the file
		oFile.close();
} 
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ClassSet::Load(ifstream &oFile, string sClassName)
{	//Vars
		string 	sFileType;
		int		iVersion;
		int		iNumClasses;
		int		iNumVars;

	//Read in the header info
		oFile >> sFileType;
		oFile >> iVersion;
	//If this is a valid file continue onward
		if(ValidVersionNum("cLLClassSet::Load() 000, invalid file type or version", sFileType, iVersion))
		{	//%# O' Classes%
				oFile >> iNumClasses;
				mylClasses.Resize(iNumClasses);
			//<Loop for # of classes>
				for(int i = 0; i < mylClasses.Length(); i++)
				{	//"Description"
						mylClasses[i].mysDescription = ReadString(oFile);
					//%Bounded Start%
						oFile >> mylClasses[i].myiStart;
					//%Bounded End%
						oFile >> mylClasses[i].myiEnd;
					//Now actually load this class
						mypoLOOP->ReadClass(sClassName, mylClasses[i].myiStart);
				}
		}
}
//P----------------------------------------------------------------------------------------- [Editting] -P
string LL_ClassSet::ClassFileName()
{	//Just chop off the set in .classset (the last three letters)
		return(mysClassesFile.substr(0, mysClassesFile.size() - 3));
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LL_ClassSet::MoveEntryTo(int iEntryNum, int iFirstLine)
{	//Vars
		int iLength;

	//Calculate the length of this entry
		iLength = mylClasses[iEntryNum].myiEnd - mylClasses[iEntryNum].myiStart;

	//Move the entry
		mylClasses[iEntryNum].myiStart = iFirstLine;
		mylClasses[iEntryNum].myiEnd   = iFirstLine + iLength;
}
//P---------------------------------------------------------------------------------------- [Debugging] -P
bool LL_ClassSet::ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum))
{	//Const
		const string REQUIRED_FILE_TYPE 		= ".classset";	//Holds the required file type
		const int	 REQUIRED_VERSION_NUMBER	= 0;			//Holds the required version number
		
	//If invalid
		if(sFileType != REQUIRED_FILE_TYPE || iVersionNum != REQUIRED_VERSION_NUMBER)
		{	cout << sErrorCode << endl;
			cout << "--[File Type]-->               "  << sFileType   				<< endl;
			cout << "--[Required File Type]-->      "  << REQUIRED_FILE_TYPE   		<< endl;
			cout << "--[Version Number]-->          "  << iVersionNum   			<< endl;
			cout << "--[Required Version Number]--> "  << REQUIRED_VERSION_NUMBER   << endl;
			return false;
		}
		else
			return true;
}
