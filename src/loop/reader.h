/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cReader
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef READER_H_
	#define READER_H_

//Aggregates
	#include "class.h"
	#include "commandlibrary.h"
	#include "classlibrary.h"
	#include <iostream>
	#include <string>
	#include <vector>
	using namespace std;
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												eCommandType
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
enum LOOP_CONTROL_SYMBOL
{	CONTROLSYMBOL_COMMAND = 0,
	CONTROLSYMBOL_LABEL,
	CONTROLSYMBOL_VARIABLE,
	CONTROLSYMBOL_PUB_VARIABLE,
	CONTROLSYMBOL_NAME,
	CONTROLSYMBOL_END,
	CONTROLSYMBOL_DERIVE,
	CONTROLSYMBOL_ERROR,
	CONTROLSYMBOL_NOTHING
};

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												eReaderError
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
enum LOOP_READ_ERROR
{	READER_ERROR_GOOD =	0,
	READER_ERROR_VARIABLE_TYPE,
	READER_ERROR_VARIABLE_IDENTIFIER,
	READER_ERROR_ILLEGAL_VARIABLE_IDENTIFIER,
	READER_ERROR_ILLEGAL_CONTROL_SYMBOL,
	READER_ERROR_ABNORMAL_EXIT,
	READER_ERROR_UNKNOWN_PARENT_CLASS,
	READER_ERROR_UNKNOWN_COMMAND
};

enum LOOP_PARSE_ERROR
{	PARSER_ERROR_GOOD = 0,
	PARSER_ERROR_READ_INT,
	PARSER_ERROR_READ_DOUBLE,
	PARSER_ERROR_UNABLE_TO_FIND_ENDING_QOUTE,
	PARSER_ERROR_UNABLE_TO_FIND_STARTING_QOUTE,
	PARSER_ERROR_READ_UNTILCHAR,
	PARSER_ERROR_READ_UNTILSTRING
};

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cReader
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Reader
{	public:
	//- [Constuctors] -
 		LOOP_Reader();
 		~LOOP_Reader();
 		void SetDefaults();

 		void SetCommandLibrary(LOOP_CommandLibrary* poCommandLibrary);
 		MEMVAR_SETGET(SetClassSet, ClassSet, LOOP_ClassLibrary*, mypoClassSet);
	//- [Reading] -
		void Read(LOOP_Class* pClass, int iClassCode, string sFile);
		void Read(LOOP_Class* pClass, int iClassCode, string sFile, int iStart);
		bool Debug(int iClassCode, string sFile, int iStart, string* psErr, int* piErrLocal,
  				  string sClassName);
		LOOP_CONTROL_SYMBOL	GrabControlSymbol();

 	protected:
	//P- [Reading] -P
		void Read();
		void GotoLine(fstream* oFile, int iLine);
		void WorkWithControlSymbol(LOOP_CONTROL_SYMBOL iSymbol);
		void HandleCommand();
		void GrabParams(LOOP_ParamMap* poMap, LOOP_Parameters* poParams, int iCommandIdentifier);
		bool NextParamVar();
		void ReadParam(eParam iParam, LOOP_Parameters* poParams);
		void HandleVar(bool fPublic);
		void CheckVariableIdentifier(string sIdentifier);
		void HandleLabel();
		string GrabErrorMessage();
		void HandleErrors();
		void HandleName();
		void HandleDerive();

 	//Vars
 		LOOP_Class* 			mypoClass;
 		LOOP_CommandLibrary*	mypoCommandLibrary;
 		LOOP_ClassLibrary*		mypoClassSet;
 		char 					cVarEnclosure1;			//Holds the first variable enclosure character
		char 					cVarEnclosure2;			//Holds the second variable enclosure character
		int						myiClassCode;
		LOOP_READ_ERROR			myiReaderError;
		
	public:
	//- [Parser] -
	//- [Loading] -
		void	SetFile(string sFile);	//Sets the input file to the file represented by the variable sFile in the parameters over there, do you see that parameter, yeah it's prefixed with the 's' character so that means its a string and the file part says that this string somehow represents a file, which it does, which is good since that was my intention. Allrighty then, I'll shut up now................
	
	//- [Comment Setting] -
		void SetLineComment(string s);				//Sets the chars that signify a line comment
		void SetBlockComment(string s1, string s2);	//Sets the chars that signify block comments

	//- [Parse Values] -
		int		ParseInt();				//Reads in an int from the file assumes cursor is set correctly)
		double	ParseDouble();			//Reads in a double from the file (assumes cursor is set correctly)
		string	ParseString();			//Reads in a string	
		string  ParseWord();			//Parses the next (string) word
		char	ParseChar();			//Reads in 1 character, fun!
		string	ParseTillChar(char c);	//Keeps on parsing until character c is reached

	//- [Delays] -
		void FinishLine();				//Reads the rest of the line
		void ReadTillString(string s);	//Reads until the set of characters in s is reached
	
	protected:
	//P- [Cursor moving] -P
		void Align();		//Moves the cursor to the first non-commented area
		bool Comment();		//If comments follow the cursor just read past the comments

	//Vars
		fstream* mypFile;				//File that gets read in
		bool   myfCommenting;			//True when commenting is on (chars being ignored mode)
		string mysLineComment;			//Set of chars that start a line comment, default = '\\'
		string mysStartBlockComment;	//Set of chars that starts a block comment
		string mysEndBlockComment;		//Set of chars that ends a block comment
		LOOP_PARSE_ERROR myiParserError;
		int	   myiErrorLocal;
};

//Now ending reader.h
	#endif
