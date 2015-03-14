/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cVariables
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef VARIABLES_H_
	#define VARIABLES_H_
	
//Foundation
	#include <vector>
	#include <asfc/linkedlist.h>
 	#include <string>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cVariables
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Variables
{	public:
	//- [Constuctors] -
 		LOOP_Variables();
	//- [Variable Adding] -
		void NewInt   (string sIdentifier, int    iNewValue, bool fPublic);
		void NewFloat (string sIdentifier, double dNewValue, bool fPublic);
		void NewString(string sIdentifier, string sNewValue, bool fPublic);
		void CopyIn	  (LOOP_Variables* poFrom);
	//- [Variable Removal] -
		void ClearAllVariables();
		void RemoveInt   (string sIdentifier);
		void RemoveFloat (string sIdentifier);
		void RemoveString(string sIdentifier);
	//- [Variable Getting] -
		int    GetInt   (string sIdentifier);
		double GetFloat (string sIdentifier);
		string GetString(string sIdentifier);
		int    GetInt   (int iLocation);
		double GetFloat (int iLocation);
		string GetString(int iLocation);
		string GetIntIdentifier		(int iLocation);
		string GetFloatIdentifier	(int iLocation);
		string GetStringIdentifier	(int iLocation);
		bool   IntPublic			(int iLocation);
		bool   FloatPublic			(int iLocation);
		bool   StringPublic			(int iLocation);
	//- [Variable Setting] -
		void SetInt   (string sIdentifier, int 	  iTo);
		void SetFloat (string sIdentifier, double dTo);
		void SetString(string sIdentifier, string sTo);
		void SetInt   (int iLocation, int 	 iTo);
		void SetFloat (int iLocation, double dTo);
		void SetString(int iLocation, string sTo);
	//- [Variable Finding] -
		static const int NO_VAR_FOUND = -1;
		int FindInt(string sIdentifier);
		int FindFloat(string sIdentifier);
		int FindString(string sIdentifier);
	//- [Variable Statistics] -
		int	NumInts();
		int NumFloats();
		int NumStrings();
	//- [Public Vars] -
		ASFC_LinkedList<string> PublicInts();
		ASFC_LinkedList<string> PublicFloats();
		ASFC_LinkedList<string> PublicStrings();
		bool IntPublic			(string sIdentifier);
		bool FloatPublic		(string sIdentifier);
		bool StringPublic		(string sIdentifier);

 	private:
 	//P- [Variable Finding] -P
 		int Find(vector<string> &oVector, string s);
 		
 	//Vars
 		vector<int>		mylInts;
 		vector<string>	mylIntsIdentifiers;
 		vector<bool>	mylIntsPublic;
 		vector<double>	mylFloats;
 		vector<string>	mylFloatsIdentifiers;
 		vector<bool>	mylFloatsPublic;
 		vector<string>	mylStrings;
 		vector<string> 	mylStringsIdentifiers;
 		vector<bool>	mylStringsPublic;
};

//Now ending variables.h
	#endif
