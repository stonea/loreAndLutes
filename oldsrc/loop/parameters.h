/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cParameters
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef PARAMETERS_H_
	#define PARAMETERS_H_
	
//Foundation
	#include <vector>
	#include <string>
	using namespace std;
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cParameters
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Parameters
{	public:
	//- [Constuctors] -
 		LOOP_Parameters();
 	
 	//- [Adding] -
 		void NewInt			(int 	iValue);
 		void NewFloat		(double	dValue);
 		void NewString		(string	sValue);
 		void NewIntRef		(int	iValue);
 		void NewFloatRef	(int	iValue);
 		void NewStringRef	(int	iValue);
 	
 	//- [Removing] -
 		void Clear();
 	
 	//- [Setting] -
 		void SetInt			(int iNumber, int 		iTo);
 		void SetFloat		(int iNumber, double 	dTo);
 		void SetString		(int iNumber, string	sTo);
 		void SetIntRef		(int iNumber, int iTo);
 		void SetFloatRef	(int iNumber, int iTo);
 		void SetStringRef	(int iNumber, int iTo);
 	
 	//- [Getting] -
 		int		GetInt		(int iNumber);
 		double	GetFloat	(int iNumber);
 		string	GetString	(int iNumber);
 		int		GetIntRef	(int iNumber);
 		int		GetFloatRef	(int iNumber);
 		int		GetStringRef(int iNumber);
 	
 	private:
 	//Vars
 		vector<int>		mylInts;
 		vector<double>	mylFloats;
 		vector<string>	mylStrings;
 		vector<int>		mylIntRef;
 		vector<int>		mylFloatRef;
 		vector<int>		mylStringRef;
};

//Now ending parameters.h
	#endif
