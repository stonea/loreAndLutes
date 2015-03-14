/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS		© 2002 Annex Solutions, Eoin Coffey, Andy Stone
     
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
	
	File:	macros.cpp
    By:		Andy Stone
    Desc:	This file includes various macros you may find helpful in your coding. Have fun!
*/

//Associated Header
	#include "utils.h"
	#include <stdio.h>
	#include <math.h>
	#include <string>
	using namespace std;

//.........................................................................................................
//Returns s in all caps
string UpperString(string s)
{	//Loop through all the characters of s
		for(int i = 0; i < s.length(); i++)
		{	//If this char is a lower case letter
				if(s[i] >= 'a' && s[i] <= 'z')
				{	//Capatilize this letter
						s[i] = s[i] + 'A' - 'a';
				}
		}
		
	//Return s
		return(s);
}
//.........................................................................................................
//Returns s in all lower case letters
string LowerString(string s)
{	//Loop through all the characters of s
		for(int i = 0; i < s.length(); i++)
		{	//If this char is a lower case letter
				if(s[i] >= 'A' && s[i] <= 'Z')
				{	//Capatilize this letter
						s[i] = s[i] + 'a' - 'A';
				}
		}
		
	//Return s
		return(s);
}
//.........................................................................................................
//Converts a value to a string
string Val(double dVal)
{	char str[100];
	if(dVal == int(dVal))
	{	sprintf(str, "%d", int(dVal));
	}
	else
	{	sprintf(str, "%f", dVal);
	}
	
	return(str);
}
//.........................................................................................................
//Converts a string to a value
double Val(string s)
{	double d;
	
	d = atof(s.c_str());
	
	return(d);
}
//.........................................................................................................
//Rotates all the chars iChars down in a string
string Rot(int iChars, string s)
{	//Loop through all the chars
		for(int i = 0; i < s.length(); i++)
		{	//Rotate this cahr
				s[i] += iChars;
		}
		
	//Return the string
		return s;
}
//.........................................................................................................
//Converts a C++ string to an C string
void SToStr(string s, char* str)
{	sprintf(str, "%s", s.c_str());
}
//.........................................................................................................
//Range checks variable i (inclusive min & max)
void RangeCheck(int i, int iMin, int iMax, string sFunction, string sVar, int iErrCode)
{	//If i is too low
		if(i < iMin)
		{	cout << sFunction << " ERR " << Val(iErrCode) << ": " << sVar << " too low\n";
			cout << "--[" << sVar << "]--> " << Val(i) << endl;
			cout << "--[Min]--> " << Val(iMin) << endl;
		}
		
	//If i is too high
		if( i > iMax)
		{	if(i < iMin)
			cout << sFunction << " ERR " << Val(iErrCode) << ": " << sVar << " too high\n";
			cout << "--[" << sVar << "]--> " << Val(i) << endl;
			cout << "--[Max]--> " << Val(iMax) << endl;
		}
}
//.........................................................................................................
//Returns string s surrounded with qoutes (translates "s into \" and \s into \\s
string Qoute(string s)
{	//Vars
		string sReturn = "\"";

	//Loop through all the letters
		for(int i = 0; i < s.length() ; i++)
		{	//If this char is a qoute (")
				if(s[i] == '\"')
				{	//Add \" to the return string
						sReturn += "\\\"";
				}
				
			//If this char is a slash (\)
				else if(s[i] == '\\')
				{	//Add \\ to the return string
						sReturn += "\\\\";
				}
			//If its just a normal char
				else
				{	//Add this character
						sReturn += s[i];
				}
		}

	//Add the ending qoutes
		sReturn += "\"";
	
	return(sReturn);
}
//.........................................................................................................
//Reads in a string surrounded by double qoutes from an ifstream
string ReadString(ifstream &oFile)
{	char	cStart;
	char	tc;
	string  sReturn;
	bool	fDone = false;
	
	//Move the file pointer to the start of this new string
		oFile >> cStart;

	//While we haven't hit that qoute
		while(!fDone)
		{	//Read in a char
				oFile.get(tc);
				
			//If its a slash
				if(tc == '\\')
				{	//Read in the next char
						oFile.get(tc);
						
					//If this char is a qoute (if the string had these two chars \")
						if(tc == '\"')
						{	//Add one qoute to the string
								sReturn += '\"';
						}
						
					//If this char is another slash (if the string had these two chars \\)
						else if(tc == '\\')
						{	//Add 1 slash to the string
								sReturn += '\\';
						}
					
					//If its any other char
						else
						{	//Just add a slash and this char to the string
								sReturn += '\\' + tc;
						}
				}
			//If its a double qoute
				else if(tc == '\"')
				{	sReturn += tc;
    	
      				//We be done!
	    				fDone = true;
				}
			//If its a normal char
				else
				{	sReturn += tc;
				}
		}


	//Delete the trailing qoute
		sReturn = sReturn.substr(0, sReturn.size() - 1);
	
	return(sReturn);
}
//.........................................................................................................
//Returns true if sFile is a valid file
bool FileExist(string sFile)
{	//Open the file, if it opens its succesfull
		ifstream oFile(sFile.c_str());
		if(!oFile.is_open())
			return false;

	oFile.close();
	return true;
}
