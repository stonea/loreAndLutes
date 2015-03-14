/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Class
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef CLASS_H_
	#define CLASS_H_

//Foundation
	#include <string>
	#include <vector>

//Aggregates
	#include "code.h"
	#include "label.h"
	#include "variables.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Class
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Class
{	public:
	//- [Constuctors] -
 		LOOP_Class();
 		
	//- [Code Handeling] -
		void  ClearCode();
		void  PushCode(LOOP_Code oNewCode);
		LOOP_Code GetCode(int iCodeNum);
		int   NumCodes();
		
	//- [Label Handeling] -
		void 	ClearLabels();
		void 	PushLabel(LOOP_Label oNewLabel);
		LOOP_Label 	GetLabel(int iLabelNum);
		LOOP_Label 	GetLabel(string sIdentifier);
		LOOP_Label 	GetLabel(string sIdentifier, int iIgnore);
		int  	NumLabels();
		vector<LOOP_Label>* Labels();
		
	//- [Parent Class Handeling] -
		void Derive(LOOP_Class* pFrom);
		MEMVAR_GET(Parent, LOOP_Class*, mypoParent);
	
	//- [Identifier Handeling] -
		MEMVAR_SETGET(SetIdentifier, Identifier, string, mysIdentifier);
		MEMVAR_SETGET(SetNumericIdentifier, NumericIdentifier, int, myiIdentifier);
		
	//- [Variable Handelings] -
		static const int NO_VAR_FOUND = -1;
		MEMVAR_SET	 	(SetVariables, LOOP_Variables, myoVars);
		LOOP_Variables*	GetVariables();
		void NewInt		(string sIdentifier, int 	iValue, bool fPublic);
		void NewFloat	(string sIdentifier, double	dValue, bool fPublic);
		void NewString	(string sIdentifier, string	sValue, bool fPublic);
		int  FindInt	(string sIdentifier);
		int  FindFloat	(string sIdentifier);
  		int  FindString	(string sIdentifier);
		
	//- [Debugging] -
		void WriteDebuggingInfo();
 	
 	private:
 	//Vars
 		vector<LOOP_Code> 	mylCodes;
 		vector<LOOP_Label>	mylLabels;
 		LOOP_Class*			mypoParent;
 		string				mysIdentifier;
 		int					myiIdentifier;
 		LOOP_Variables		myoVars;
};

//Now ending class.h
	#endif
