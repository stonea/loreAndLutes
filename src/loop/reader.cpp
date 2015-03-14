/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cReader
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "reader.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Reader
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Reader::LOOP_Reader()
:	cVarEnclosure1('['),
	cVarEnclosure2(']')
{	//Set defaults
		SetLineComment("//");
		SetBlockComment("/*", "*/");
//		SetDefaults();
	//Create a file
		mypFile = new fstream;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Reader::~LOOP_Reader()
{	delete mypFile;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Reader::SetDefaults()
{	//Set the parser up with comments
		SetLineComment("//");
		SetBlockComment("/*", "*/");

	//Setup variable enclosure marks
		cVarEnclosure1 = '[';
		cVarEnclosure2 = ']';
		
	//Setup the error state
		myiReaderError = READER_ERROR_GOOD;	// <-- This line is evil!
		myiParserError = PARSER_ERROR_GOOD;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Reader::SetCommandLibrary(LOOP_CommandLibrary* poCommandLibrary)
{	mypoCommandLibrary = poCommandLibrary;
}
//-------------------------------------------------------------------------------------------- [Reading] -
void LOOP_Reader::Read(LOOP_Class* pClass, int iClassCode, string sFile)
{	//Set defaults
		SetDefaults();

	//Close up the file
		mypFile->close();
		
	//Set the file and the class
		SetFile(sFile);
		mypoClass = pClass;
		myiClassCode = iClassCode;
   	
	//Now Read
		Read();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Reader::Read(LOOP_Class* pClass, int iClassCode, string sFile, int iStart)
{	//Set defaults
		SetDefaults();
		
	//Close up the file
		mypFile->close();

	//Set the file and the class
		SetFile(sFile);
		mypoClass = pClass;
		myiClassCode = iClassCode;
		
	//Move to the starting line
 		GotoLine(mypFile, iStart);
   		
	//Now Read
		Read();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Reader::Debug(int iClassCode, string sFile, int iStart, string* psErr, int* piErrLocal,
						string sClassName)
{	//Vars
		LOOP_Class 	toClass;

	//Set defaults
		SetDefaults();
		
	//Close up the file
		mypFile->close();

	//Set the file and the class
		SetFile(sFile);
		mypoClass 	 = &toClass;
		myiClassCode = -1;
		
	//Move to the starting line
 		GotoLine(mypFile, iStart);
   		
	//Now read watching for bugs
		//vars
			LOOP_CONTROL_SYMBOL 	iControlSym  = CONTROLSYMBOL_NOTHING;
			bool		 			fDone = false;

		//While we haven't reached the end!
			while(iControlSym != CONTROLSYMBOL_END && !mypFile->eof())
			{	//Grab the command type
					iControlSym = GrabControlSymbol();
			
				//If the control symbol is name make sure the class name is correct
					if(iControlSym == CONTROLSYMBOL_NAME)
					{	HandleName();
     					if(UpperString(mypoClass->Identifier()) != UpperString(sClassName))
     					{	//Return with a name error
     							*psErr = "Wrong class name, change to " + sClassName;
								*piErrLocal = mypFile->tellg();
cerr << "ERROR LOCAL: " << myiErrorLocal;
						
							//Quit out, return true for errors
								return true;
     					}
					}
			
				//If we've got an okay control symbol work with it
					else if(iControlSym != CONTROLSYMBOL_ERROR && iControlSym != CONTROLSYMBOL_END)
						WorkWithControlSymbol(iControlSym);
					
				//Check for errors
					if(myiReaderError != READER_ERROR_GOOD || myiParserError != PARSER_ERROR_GOOD)
					{	//Set the error message
							*psErr = GrabErrorMessage();
							//*piErrLocal = mypFile->tellg(); !!!
							*piErrLocal = myiErrorLocal;
cerr << "ERROR LOCAL: " << myiErrorLocal;
						
						//Quit out, return true for errors
							return true;
					}
			}
			
	//It was read succesfully
		return false;
}
//P------------------------------------------------------------------------------------------ [Reading] -P
void LOOP_Reader::Read()
{	//vars
		LOOP_CONTROL_SYMBOL 	iControlSym  = CONTROLSYMBOL_NOTHING;
		bool		 			fDone = false;

	//While we haven't reached the end!
		while(iControlSym != CONTROLSYMBOL_END && !mypFile->eof())
		{	//Grab the command type
				iControlSym = GrabControlSymbol();
			
			//If we've got an okay control symbol work with it
				if(iControlSym != CONTROLSYMBOL_ERROR && iControlSym != CONTROLSYMBOL_END)
					WorkWithControlSymbol(iControlSym);
					
			//Check for errors
				HandleErrors();
		}
		
	//If we've exitted abnormally set an error
		if(iControlSym != CONTROLSYMBOL_END)
		{	myiReaderError = READER_ERROR_ABNORMAL_EXIT;
			myiErrorLocal = mypFile->tellg();
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::GotoLine(fstream* oFile, int iLine)
{	//Vars
		char str[1000];

	//Seek to the very start
		  oFile->seekg(0, ios::beg);
		  
	//Loop through iLine lines
		for(int i = 0; i < iLine; i++)
		{	oFile->getline(&str[0], 1000);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
LOOP_CONTROL_SYMBOL LOOP_Reader::GrabControlSymbol()
{	//Vars
		char c;			//Character
	
	//Read in a char
		c = ParseChar();

	//Determine what to do based on c
		switch(c)
		{	//- [Command '#'] -
			case '#':
			{	return CONTROLSYMBOL_COMMAND;
			}break;
			
			//- [Label ':'] -
			case ':':
			{	return CONTROLSYMBOL_LABEL;
			}break;
			
			//- [Variable '%'] -
			case '%':
			{	return CONTROLSYMBOL_VARIABLE;
			}break;
			
			//- [Public Variable '$'] -
			case '$':
			{	return CONTROLSYMBOL_PUB_VARIABLE;
			}break;
			
			//- [Name '@'] -
			case '@':
			{	return CONTROLSYMBOL_NAME;
			}break;
			
			//- [End '^'] -
			case '^':
			{	return CONTROLSYMBOL_END;
			}
			
			//- [Derive '>'] -
			case '>':
   			{	return CONTROLSYMBOL_DERIVE;
   			}
			
			//- [Error] -
			default:
				myiReaderError = READER_ERROR_ILLEGAL_CONTROL_SYMBOL;
				myiErrorLocal = mypFile->tellg();
				HandleErrors();
				return(CONTROLSYMBOL_ERROR);
			break;
		}
				
	//Return Error, spiffer
		return(CONTROLSYMBOL_ERROR);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::WorkWithControlSymbol(LOOP_CONTROL_SYMBOL iSymbol)
{	//Decide what to do depending on what symbol we've got
		switch(iSymbol)
		{	//- [Command] -
			case CONTROLSYMBOL_COMMAND:
			{	//Very well deal with the command
					HandleCommand();
			}break;
			
			//- [Label] -
			case CONTROLSYMBOL_LABEL:
			{	//Very well deal with the label
					HandleLabel();					
			}break;
			
			//- [Variable] -
			case CONTROLSYMBOL_VARIABLE:
			{	//Very well deal with the variable
					HandleVar(false);
			}break;
			
			//- [Public Var] -
			case CONTROLSYMBOL_PUB_VARIABLE:
			{	//Very well deal with the variable
					HandleVar(true);
			}break;
			
			//- [Name] -
			case CONTROLSYMBOL_NAME:
			{	//Very well deal with the name
					HandleName();
			}break;
			
			//- [Derive] -
			case CONTROLSYMBOL_DERIVE:
			{	//Very well deal with this so called parent class
					HandleDerive();
			}
		};
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::HandleCommand()
{	//Vars
		LOOP_Code			oNewCode;
		string			sCommandIdentifier;
		int				iCommandIdentifier;
		LOOP_Command*		pCommand;
		LOOP_Parameters		oParams;
		LOOP_ParamMap		oMap;
	
	//Parse out the identifier, capatilize it, & figure out its location in the command library
		sCommandIdentifier = ParseWord();
		sCommandIdentifier = UpperString(sCommandIdentifier);
		iCommandIdentifier = mypoCommandLibrary->SearchForCommand(sCommandIdentifier);
		
	//If we have an illegal command identifier
		if(iCommandIdentifier == mypoCommandLibrary->UNKNOWN_COMMAND)
		{	//Set an error
				myiReaderError = READER_ERROR_UNKNOWN_COMMAND;
				myiErrorLocal = mypFile->tellg();
		}
	//If alls okay grap the command and continue on
		else
		{	pCommand		   = mypoCommandLibrary->GetCommand(iCommandIdentifier);
	
			//*Gulp* now parse out the command vars
				GrabParams(&oMap, &oParams, iCommandIdentifier);
			//If we have an error stop
				if(myiParserError != PARSER_ERROR_GOOD)
					return;
			//Setup a code object with this information
				oNewCode.SetCommand			(pCommand);
				oNewCode.SetParameters		(oParams);
				oNewCode.SetParametersMap	(oMap);
			//And associate this code to the object
				mypoClass->PushCode(oNewCode);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::GrabParams(LOOP_ParamMap* poMap, LOOP_Parameters* poParams, int iCommandIdentifier)
{	//Vars
		LOOP_Command*	poCommand;
		eParam		iParam;

	//Grab the command for which we're parsing variables out for
		poCommand = mypoCommandLibrary->GetCommand(iCommandIdentifier);

	//Now loop through all the params of this command
		for(int i = 0; i < poCommand->NumParams(); i++)
		{	//Grab the param
				iParam = poCommand->GetParam(i);

			//If this param is being passed as a variable mask iParam to it's pointer type				
				if(NextParamVar())
				{	switch(iParam)
					{	case PARAM_INT:			{iParam = PARAM_INT_REF;	}break;
						case PARAM_FLOAT:		{iParam = PARAM_FLOAT_REF;	}break;
						case PARAM_STRING:		{iParam = PARAM_STRING_REF;	}break;
						case PARAM_INT_REF:		break;
						case PARAM_FLOAT_REF:	break;
						case PARAM_STRING_REF:	break;
					}					
				}				
				
			//Map it
				poMap->New(iParam);
			
			//Read in the parameter
				ReadParam(iParam, poParams);
			//If we have an error stop
				if(myiParserError != PARSER_ERROR_GOOD)
					return;
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//True if the next param written in the A*ML doc is a variable
bool LOOP_Reader::NextParamVar()
{	//Var
		int  iLastPosition;	//Holds the position of the cursor before any parsing occurs
		char c;				//Holds a character	
	
	//Grab the last (current) position
		iLastPosition = mypFile->tellg();
	
	//Grab the next character
		c = ParseChar();
	
	//If it's the enclosure, you've got some fine variable there! Otherwise, you've got some fine constant!
		if(c == cVarEnclosure1)
			return(true);
		else
		{	//Set the cursor back to where it was before
				mypFile->seekg(iLastPosition);			
					return(false);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::ReadParam(eParam iParam, LOOP_Parameters* poParams)
{	//Vars
		int		tiInt;
		double	tdFloat;
		string	tsString;
		string  sIdentifier;

	//Decide what to do baed on what the param is
		switch(iParam)
		{	//- [Int] -
			case PARAM_INT:
			{	//Okay, parse out an int
					tiInt = ParseInt();
				//If we have an error return
					if(myiParserError != PARSER_ERROR_GOOD)
						return;
				//Push it into the params
					poParams->NewInt(tiInt);
			}break;
			
			//- [Float] -
			case PARAM_FLOAT:
			{	//Read it in and add it
					tdFloat = ParseDouble();
					poParams->NewFloat(tdFloat);
			}break;
			
			//- [String] -
			case PARAM_STRING:
			{	//Read it in and add it
					tsString = ParseString();
					poParams->NewString(tsString);
			}break;
			
			//- [*Int] -
			case PARAM_INT_REF:
			{	//Read it in, check for errors, and add it
					sIdentifier = ParseTillChar(cVarEnclosure2);
					tiInt = mypoClass->FindInt(sIdentifier);
					
					if(tiInt == mypoClass->NO_VAR_FOUND)
					{	myiReaderError = READER_ERROR_VARIABLE_IDENTIFIER;
						myiErrorLocal = mypFile->tellg();
					}
					else
						poParams->NewIntRef(tiInt);
			}break;
			
			//- [*Float] -
			case PARAM_FLOAT_REF:
			{	//Read it in, check for errors, and add it
					sIdentifier = ParseTillChar(cVarEnclosure2);
					tiInt = mypoClass->FindFloat(sIdentifier);
	
     				if(tiInt == mypoClass->NO_VAR_FOUND)
					{	myiReaderError = READER_ERROR_VARIABLE_IDENTIFIER;
						myiErrorLocal = mypFile->tellg();
					}
					else
						poParams->NewFloatRef(tiInt);
			}break;
			
			//- [*String] -
			case PARAM_STRING_REF:
			{	//Read it in, check for errors, and add it
					sIdentifier = ParseTillChar(cVarEnclosure2);
					tiInt = mypoClass->FindString(sIdentifier);
					
					if(tiInt == mypoClass->NO_VAR_FOUND)
					{	myiReaderError = READER_ERROR_VARIABLE_IDENTIFIER;
						myiErrorLocal = mypFile->tellg();
					}
					else
						poParams->NewStringRef(tiInt);
			}break;
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::HandleVar(bool fPublic)
{	//Const
		//AML Var Strings (The part after the %)
			const string AMLPARAMSTR_INT       = "int";
			const string AMLPARAMSTR_FLOAT     = "float";
			const string AMLPARAMSTR_STRING	   = "string";
		//Holds the defaultl values associated with each type
			const int		AMLVARDEFAULT_INT    = 0;
			const double	AMLVARDEFAULT_FLOAT  = 0;
			const string	AMLVARDEFAULT_STRING = "";
	
	//Vars
		string sType;		//Holds the variable type
		string sIdentifier;	//Holds the variable identifier
	
	//Read in the type and identifier
		sType 		= ParseWord();
		sIdentifier = ParseString();
		
	//Check to make sure we have a valid identifier
		CheckVariableIdentifier(sIdentifier);

	//Figure out what to do based on what sType is
		//- [Int] -
			if(sType ==	AMLPARAMSTR_INT)
			{	//Make an int
					mypoClass->NewInt(sIdentifier, AMLVARDEFAULT_INT, fPublic);
			}
			
		//- [float] -
			else if(sType == AMLPARAMSTR_FLOAT)
			{	//Make a float
					mypoClass->NewFloat(sIdentifier, AMLVARDEFAULT_FLOAT, fPublic);
			}
			
		//- [string] -
			else if(sType == AMLPARAMSTR_STRING)
			{	//Make a string
					mypoClass->NewString(sIdentifier, AMLVARDEFAULT_STRING, fPublic);
			}
		//- [error] -
			else
			{	myiReaderError = READER_ERROR_VARIABLE_TYPE;
				myiErrorLocal = mypFile->tellg();
			}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::CheckVariableIdentifier(string sIdentifier)
{	//Loop through all chars
		for(int i = 0; i < sIdentifier.size(); i++)
		{	//If we have some type of illegal char
				if(	sIdentifier[i] == '['  || sIdentifier[i] == ']' || sIdentifier[i] == '\'' ||
    				sIdentifier[i] == '\"')
				{	//We've got an error
						myiReaderError = READER_ERROR_ILLEGAL_VARIABLE_IDENTIFIER;
						myiErrorLocal = mypFile->tellg();
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::HandleLabel()
{	//Vars
		string sIdentifier;	//Holds the label identifier, nifty!
		LOOP_Label oLabel;		//Holds label object that will be added to the object
		LOOP_Code oCode;		//Holds the code that'll be added to the object
		
	//Read in the label identifier and capatilize it
		sIdentifier = ParseWord();
		sIdentifier = UpperString(sIdentifier);		
	
	//Use that to make a label:
		oLabel.SetLabel(sIdentifier, myiClassCode, mypoClass->NumCodes());
	
	//Shtick this labels
		mypoClass->PushLabel(oLabel);
	
	//Add in a NULL code to the object, so the :label is counted as a line
		oCode.SetCommand(NULL);
		mypoClass->PushCode(oCode);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
string LOOP_Reader::GrabErrorMessage()
{	switch(myiReaderError)
	{	case READER_ERROR_GOOD:
		{
		}break;

		case READER_ERROR_VARIABLE_TYPE:
		{	return("Var Type");
		}break;
			
		case READER_ERROR_VARIABLE_IDENTIFIER:
		{	return("Var Identifier");
		}
			
		case READER_ERROR_ILLEGAL_VARIABLE_IDENTIFIER:
		{	return("Illegal Character in Identifier");
		}
			
		case READER_ERROR_ILLEGAL_CONTROL_SYMBOL:
		{	return("Illegal control symbol");
		}
			
		case READER_ERROR_ABNORMAL_EXIT:
		{	return("Abnormal Exit");
		}
			
		case READER_ERROR_UNKNOWN_COMMAND:
		{	return("Unknown Command");
		}
			
		case READER_ERROR_UNKNOWN_PARENT_CLASS:
		{	return("Unknown Class");
		}
	}
	
	switch(myiParserError)
	{	case PARSER_ERROR_GOOD:
		{
		}break;
		
		case PARSER_ERROR_UNABLE_TO_FIND_STARTING_QOUTE:
		{	return("Parser Error: Unable to find starting qoute");
		}break;
			case PARSER_ERROR_UNABLE_TO_FIND_ENDING_QOUTE:
		{	return("Parser Error: Unable to find ending qoute");
		}break;
		
		case PARSER_ERROR_READ_INT:
		{	return("Parser Error: Error trying to read an int");
		}break;
		
		case PARSER_ERROR_READ_DOUBLE:
		{	return("Parser Error: Error trying to read a float");
		}break;
		
		case PARSER_ERROR_READ_UNTILSTRING:
		{	return("Parser Error: Error trying to read to an ending character sequence");
		}break;
		
		case PARSER_ERROR_READ_UNTILCHAR:
		{	return("Parser Error: Error trying to read to an ending character");
		}break;
	}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::HandleErrors()
{	//Cerr the error if we have one
		if(myiReaderError != READER_ERROR_GOOD || myiParserError != PARSER_ERROR_GOOD)
			cerr << GrabErrorMessage() << endl;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::HandleName()
{	//Vars
		string sName;
	
	//Read in the name and capatilize it
		sName 	= ParseWord();
		sName	= UpperString(sName);
	
	//Set this object's identifier as sName
		mypoClass->SetIdentifier(sName);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LOOP_Reader::HandleDerive()
{	//Vars
		string 	sName;
		int		iDeriveClass;
	
	//Read in the name and capatilize it
		sName 	= ParseWord();
		sName	= UpperString(sName);
		
	//Now figure out the location of the derived class
		iDeriveClass = mypoClassSet->FindClass(sName);
		
	//If we've got an error
		if(iDeriveClass == mypoClassSet->NOTHING_FOUND)
		{	myiReaderError = READER_ERROR_UNKNOWN_PARENT_CLASS;
			myiErrorLocal = mypFile->tellg();
		}	
	//Now derive (if no erroro)
		else
			mypoClass->Derive(mypoClassSet->GetClass(iDeriveClass));
}
//*********************************************************************************************************
//											Parser
//*********************************************************************************************************
//--------------------------------------------------------------------------------------------- [Loading] -
//Sets the input file to the file represented by the variable sFile in the parameters over there
void LOOP_Reader::SetFile(string sFile)
{	//Create file sFile
		mypFile->open(sFile.c_str(), ios::in | ios::binary);
		
	//Reset our state
		myiParserError = PARSER_ERROR_GOOD;
}

//-------------------------------------------------------------------------------------- [Comment Setting] -
//Sets the chars that signify a line comment
void LOOP_Reader::SetLineComment(string s)
{	//Map params to member functions
		mysLineComment = s;
}

//.........................................................................................................
//Sets the chars that signify block comments
void LOOP_Reader::SetBlockComment(string s1, string s2)
{	//Map params to member functions
		mysStartBlockComment	= s1;
		mysEndBlockComment		= s2;
}

//---------------------------------------------------------------------------------------- [Parse Values] -
//Reads in an int from the file assumes cursor is set correctly)
int	LOOP_Reader::ParseInt()
{	//Vars
		string	s;	//String input
		int 	i;	//Integer output
		
	//Align the cursor (as always)
		Align();
	
	//Grab input
		*mypFile >> s;
		
	//If the 1st char isn't a # or - sign we've got an error
		char c = s[0];
		if(! (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' ||
			  c == '7' || c == '8' || c == '9' || c == '-'))
 		{	//We've got error
	 			myiParserError = PARSER_ERROR_READ_INT;
	 			myiErrorLocal = mypFile->tellg();
	 		//Return -1
	 			return(-1);
 		}
	
	//Simply convert the string to an integer:
		i = atoi(s.c_str());
	
	//Return the integer
		return(i);
}

//.........................................................................................................
//Reads in a double from the file (assumes cursor is set correctly)
double	LOOP_Reader::ParseDouble()
{	//Vars
		string	s;	//String input
		double  d;	//Double output
		
	//Align the cursor (as always)
		Align();
	
	//Grab input
		*mypFile >> s;
		
	//If the 1st char isn't a # or a . or - we've got an error
		char c = s[0];
		if(! (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' ||
			  c == '7' || c == '8' || c == '9' || c == '.' || c == '-'))
 		{	//We've got error
	 			myiParserError = PARSER_ERROR_READ_DOUBLE;
	 			myiErrorLocal = mypFile->tellg();
 		}
	
	//Simply convert the string to a double:
		d = atof(s.c_str());
	
	//Return the double
		return(d);
}
//.........................................................................................................
//Reads in a string	
string	LOOP_Reader::ParseString()
{	//Vars
		char	c; 		//Character input
		string	s; 		//String output
		bool    fDone;	//True when we're done grabbing the string
	
	//Align the cursor (as always)
		Align();
	
	//Read in the starting double qoute
		*mypFile >> c;
		
	//Only continue if c is infact a double qoute
		if(c == '\"')
		{	//Set fDone to false
				fDone = false;
	
			//Loop until we're done reading in the string
				while(fDone == false)
				{	//Read in a char
						mypFile->get(c);
									
					//Determine what to do based on that char
						switch(c)
						{	//- [Slash '\'] -
							case '\\':
							{	//Read in the next char
									mypFile->get(c);
						
								//Decide what to do based on that char
									switch(c)
									{	//- [Another Slash '\'] -
										case '\\':
										{	//Push a slash onto the output string
												s += '\\';
										}break;
										
										//- [Double Qoute '"'] -
										case '"':	
										{	//Push a double qoute onto the output string
												s += '\"';
										}break;
									}
							}break;
					
							//- [Double Qoute '"'] -
							case '"':
							{	//We're done
									fDone = true;
							}break;
							
							//- [Illegal new line] -
							case char(11):
							case '\n':
							{	//Bad, turn on an error
									myiParserError = PARSER_ERROR_UNABLE_TO_FIND_ENDING_QOUTE;
									myiErrorLocal = mypFile->tellg();
								//We're done
									fDone = true;
							}break;
					
							//- [Anything else] -
							default:
							{	//Simply push it onto the output string
									s += c;
							}break;
						}
						
					//If we're at the end of the file quit now
						if(mypFile->eof())
						{	//Bad, turn on an error
								myiParserError = PARSER_ERROR_UNABLE_TO_FIND_ENDING_QOUTE;
								myiErrorLocal = mypFile->tellg();
							//We're done
								fDone = true;
						}
				}
		}
		else
		{	//We've got an error say so
				myiParserError = PARSER_ERROR_UNABLE_TO_FIND_STARTING_QOUTE;
				myiErrorLocal = mypFile->tellg();
		}
	
	//We're done, ship off the string as the return
		return(s);
}

//.........................................................................................................
//Parses the next (string) word
string  LOOP_Reader::ParseWord()
{	//vars
		string s;	//Output string
	
	//Align, as always
		Align();
	
	//Grab the word
		*mypFile >> s;
	
	//Shippidy dippidy the retun!
		return(s);
}

//.........................................................................................................
//Reads in 1 character, fun!
char	LOOP_Reader::ParseChar()
{	//vars
		char c;	//Output char
			
	//Align the cursor (as always)
		Align();
	
	//Grab the char
		*mypFile >> c;
	
	//Shippidy dippidy the retun!
		return(c);
}

//.........................................................................................................
//Keeps on parsing until character c is reached
string	LOOP_Reader::ParseTillChar(char c)
{	//Vars
		string	s;		//String that'll be returned
		bool 	fDone;	//True when we're done parsing
		char	cParse;	//Char that's been parsed out
	
	//Set fDone to false
		fDone = false;
	
	//Keep looping until we reach c
		while(fDone == false)
		{	//If we've reached the end state an error
				if(mypFile->eof())
				{	myiParserError = PARSER_ERROR_READ_UNTILCHAR;
					myiErrorLocal = mypFile->tellg();
					fDone = true;
				}
			//Else if all is normal
				else
				{	//Parse out a char
						mypFile->get(cParse);
			
					//Set fDone if we've reached c
						if(cParse == c)
							fDone = true;
			
					//Otherwise add the parsed char to s
						else
							s += cParse;
				}
		}
		
	//Return s
		return(s);
}
//---------------------------------------------------------------------------------------------- [Delays] -
//Reads the rest of the line
void LOOP_Reader::FinishLine()
{	//Var
		char strDummy[1024];		//Dummy character to let allow getlines
		
	//Just read in the rest of the line
		mypFile->getline(strDummy, 1024);
}

//.........................................................................................................
//Reads until the set of characters in s is reached
void LOOP_Reader::ReadTillString(string s)
{	//Var
		bool fDone  = false;		//True when we've read in the complete string
		bool fErr   = false;		//True when an error while reading in occured (a wrong char or something)
		char c;						//Temporary string (to read in)
		unsigned int  i;			//Index counter

	//Loop until all the chars have been read in (and we're not at the end of the file)
		while(fDone == false && !mypFile->eof())
		{	//Read junk until we reach the the first character	
				//Set fErr to false
					fErr = false;											//Random :)
				//Read chars until we reach the first of s
					while(fErr == false && !mypFile->eof())
					{	mypFile->get(c);
						if(c == s[0])
							fErr = true;
					}
					
				//Only continue if we didn't jump out because of eof
					if(fErr == true)
					{	//Loop the rest of the characters until we complete the string or theres a problem				
							//Set vars to their defaults
									fErr = false;
							//DO IT:
								for(i = 1; i < s.length() && fErr == false; i++)
								{	//Read in a char
										mypFile->get(c);
								
									//If this character is the next in the string					
									if(c == s[i])
									{	//Do nothing!
									}
							  
									//If not
									else
									{	//We've got an error scotty
											fErr = true;
										
										//Return the cursor back to where it was before all this checking
											long lPos = mypFile->tellg();
											lPos -= i;
											mypFile->seekg(lPos, ios::beg);
									}
								}
				
						//If we read that all in without error we're done!
							if(fErr == false)
								fDone = true;
					}
				}
		
	//If we exited because of an end of file display an error
		if(fDone == false)
		{	myiParserError == PARSER_ERROR_READ_UNTILSTRING;
			myiErrorLocal = mypFile->tellg();
		}
}

//P-------------------------------------------------------------------------------------- [Cursor moving] -P
//Moves the cursor to the first non-commented area
void LOOP_Reader::Align()
{	//Loop while we're in a commented (white space) area:		
		while(Comment()) {}
}

//P........................................................................................................P
//If comments follow the cursor just read past the comments, return true if a comment was reached
bool LOOP_Reader::Comment()
{	//Vars
		unsigned int i; 	//Looping index
		char c;				//Character read in
		bool fDone;			//True when we're done checking for comments
		bool fComment = false;	//True once we've reached a comment
		int	 iLastSeek;		//Holds a position in a file, before we started seeking around
	
	//Check and deal w/ line comments:
		//Set fDone false
			fDone = false;
		
		//Loop until we get a non commented character (when fdone is true)
			while(fDone == false && !mypFile->eof())
			{	//Record where the cursor is
					iLastSeek = mypFile->tellg();
					
   				//Read in and loop through all the characters that define a line comment
					for(i = 0; (i < mysLineComment.length()) && (fDone == false); i++)
					{	//Read in a char
							*mypFile >> c;
						//Decide what to do based on if c is a char in the line comment string
							//If it is
							if(c == mysLineComment[i])
							{	//Do nothing!
							}
							//If not
							else
							{	//Seek back to where we were before this mess.
									mypFile->seekg(iLastSeek);
								//We're done
									fDone = true;
							}
					}
					
				//If fDone is still false then we just read in a valid line comment symbol thingy. So read in the rest of the line:
					if(fDone == false)
					{	fComment = true;
						FinishLine();
					}
			}
		
	//Check and deal w/ block comments:
		//Set fDone false
			fDone = false;
		
		//Loop until we get a non commented character (when fdone is true)
		while(fDone == false && !mypFile->eof())
		{	//Record where the cursor is
				iLastSeek = mypFile->tellg();
  
  			//Read in and loop through all the characters that define the start of a block comment
				for(i = 0; (i < mysStartBlockComment.length()) && (fDone == false); i++)
				{	//Read in a char
						*mypFile >> c;
					//Decide what to do based on if c is a char in the line comment string
						//If it is
						if(c == mysStartBlockComment[i])
						{	//Do nothing!
						}
						//If not
						else
						{	//Seek back to where we were before this mess.
									mypFile->seekg(iLastSeek);
							//We're done
								fDone = true;
						}
				}
			
			//If fDone is still false then we just read in a valid block comment, so read until the ending block comment string
				if(fDone == false)
				{	fComment = true;
					ReadTillString(mysEndBlockComment);
				}
		}
		
	//Return whether we reached a comment or not
		return(fComment);
}
