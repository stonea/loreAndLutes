/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_LOOPLib_Standard
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "looplib_standard.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											cLOOPLib_Standard
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_LOOPLib_Standard::LOOP_LOOPLib_Standard()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOPLib_Standard::Link(LOOP_LOOP* poLOOP)
{	//- [Debugging] -
		poLOOP->NewCommand("Cout", 			&LOOPCMDPRT_Cout,		this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("CoutFloat", 	&LOOPCMDPRT_CoutFloat,	this);	//F
			poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("CoutInt", 		&LOOPCMDPRT_CoutInt, 	this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("CoutDebugInfo", &LOOPCMDPRT_CoutDebugInfo, 	this);	//
		poLOOP->NewCommand("XYZZY", 		&LOOPCMDPRT_XYZZY, 			this); 	//
	//- [Conditional] -
		poLOOP->NewCommand("IfStrEqu", 		&LOOPCMDPRT_IfStrEqu, 	this);		//SS
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_STRING);
	 	poLOOP->NewCommand("IfIntEqu", 		&LOOPCMDPRT_IfIntEqu, 	this); 		//II
	 		poLOOP->AddParam(PARAM_INT);
	 		poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IfIntGT", 		&LOOPCMDPRT_IfIntGT, 	this); 		//II
			poLOOP->AddParam(PARAM_INT);
	 		poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IfIntLT", 		&LOOPCMDPRT_IfIntLT, 	this); 		//II
			poLOOP->AddParam(PARAM_INT);
	 		poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IfIntGTI", 		&LOOPCMDPRT_IfIntGTI,	this); 		//II
			poLOOP->AddParam(PARAM_INT);
	 		poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IfIntLTI", 		&LOOPCMDPRT_IfIntLTI, 	this); 		//II
			poLOOP->AddParam(PARAM_INT);
	 		poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IfFloatEqu", 	&LOOPCMDPRT_IfFloatEqu, this); 		//FF
			poLOOP->AddParam(PARAM_FLOAT);
	 		poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("IfFloatGT", 	&LOOPCMDPRT_IfFloatGT,	this); 		//FF
			poLOOP->AddParam(PARAM_FLOAT);
	 		poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("IfFloatLT", 	&LOOPCMDPRT_IfFloatLT, 	this); 		//FF
			poLOOP->AddParam(PARAM_FLOAT);
	 		poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("IfFloatGTI", 	&LOOPCMDPRT_IfFloatGTI, this); 		//FF
			poLOOP->AddParam(PARAM_FLOAT);
	 		poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("IfFloatLTI", 	&LOOPCMDPRT_IfFloatLTI, this); 		//FF
			poLOOP->AddParam(PARAM_FLOAT);
	 		poLOOP->AddParam(PARAM_FLOAT);
	//- [Misc] -
		poLOOP->NewCommand("Begin", 		&LOOPCMDPRT_Begin, 	this); 			//
		poLOOP->NewCommand("End", 			&LOOPCMDPRT_End, 	this);			//
		poLOOP->NewCommand("REM", 			&LOOPCMDPRT_REM, 	this); 			//S
			poLOOP->AddParam(PARAM_STRING);
	//- [String Manipulation] -
		poLOOP->NewCommand("StrEqu", 		&LOOPCMDPRT_StrEqu, 		this);	//[S]S
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("AppendStr", 	&LOOPCMDPRT_AppendStr,		this);	//[S]S
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("InsertStr", 	&LOOPCMDPRT_InsertStr,		this);	//[S]SI
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("RemoveSubStr", 	&LOOPCMDPRT_RemoveSubStr,	this);	//[S]II
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("UpperString", 	&LOOPCMDPRT_UpperString, 	this); 	//[S]S
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("SubStr", 		&LOOPCMDPRT_SubStr,		 	this); 	//[S]SII
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("StrSize", 		&LOOPCMDPRT_StrSize,		this); 	//[I]S
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("IntToStr", 		&LOOPCMDPRT_IntToStr,		this);	//[S]I
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("FloatToStr",	&LOOPCMDPRT_FloatToStr,		this);	//[S]F
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_FLOAT);
	//- [Int Manipulation] -
		poLOOP->NewCommand("IntEqu", 		&LOOPCMDPRT_IntEqu, this); 		//[I]I
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IntInc", 		&LOOPCMDPRT_IntInc, this);		//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("IntDec", 		&LOOPCMDPRT_IntDec, this); 		//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("IntAdd", 		&LOOPCMDPRT_IntAdd, this); 		//[I]II
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IntSub", 		&LOOPCMDPRT_IntSub, this); 		//[I]II
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IntMul", 		&LOOPCMDPRT_IntMul, this); 		//[I]II
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IntDiv", 		&LOOPCMDPRT_IntDiv, this);		//[I]II
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IntMod", 		&LOOPCMDPRT_IntMod, this);		//[I]II
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Float Manipulation] -
		poLOOP->NewCommand("FloatEqu", 		&LOOPCMDPRT_FloatEqu, this);	//[F]F
			poLOOP->AddParam(PARAM_FLOAT_REF);
			poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("FloatInc", 		&LOOPCMDPRT_FloatInc, this);	//[F]
			poLOOP->AddParam(PARAM_FLOAT_REF);
		poLOOP->NewCommand("FloatDec", 		&LOOPCMDPRT_FloatDec, this);	//[F]
			poLOOP->AddParam(PARAM_FLOAT_REF);
		poLOOP->NewCommand("FloatAdd", 		&LOOPCMDPRT_FloatAdd, this);	//[F]FF
			poLOOP->AddParam(PARAM_FLOAT_REF);
			poLOOP->AddParam(PARAM_FLOAT);
			poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("FloatSub", 		&LOOPCMDPRT_FloatSub, this);	//[F]FF
			poLOOP->AddParam(PARAM_FLOAT_REF);
			poLOOP->AddParam(PARAM_FLOAT);
			poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("FloatMul", 		&LOOPCMDPRT_FloatMul, this);	//[F]FF
			poLOOP->AddParam(PARAM_FLOAT_REF);
			poLOOP->AddParam(PARAM_FLOAT);
			poLOOP->AddParam(PARAM_FLOAT);
		poLOOP->NewCommand("FloatDiv", 		&LOOPCMDPRT_FloatDiv, this);	//[F]FF
			poLOOP->AddParam(PARAM_FLOAT_REF);
			poLOOP->AddParam(PARAM_FLOAT);
			poLOOP->AddParam(PARAM_FLOAT);
	//- [Seek] -
		poLOOP->NewCommand("Goto", 			&LOOPCMDPRT_Goto, 	this); 		//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GoSub", 		&LOOPCMDPRT_GoSub, 	this); 		//S
			poLOOP->AddParam(PARAM_STRING);			
		poLOOP->NewCommand("Send", 		&LOOPCMDPRT_Send, 	this); 			//SS
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GoSend", 	&LOOPCMDPRT_GoSend,	this);	 		//SS
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("Return", 		&LOOPCMDPRT_Return, this); 		//
		poLOOP->NewCommand("Zap", 			&LOOPCMDPRT_Zap,	this);		//S
			poLOOP->AddParam(PARAM_STRING);
}
//------------------------------------------------------------------------------------------ [Debugging] -
//S
void LOOP_LOOPLib_Standard::LOOPCMD_Cout(LOOP_Info oInfo)
{	cout << oInfo.GrabString(0) << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//F
void LOOP_LOOPLib_Standard::LOOPCMD_CoutFloat(LOOP_Info oInfo)
{	cout << oInfo.GrabFloat(0) << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LOOP_LOOPLib_Standard::LOOPCMD_CoutInt(LOOP_Info oInfo)
{	cout << oInfo.GrabInt(0) << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LOOP_LOOPLib_Standard::LOOPCMD_CoutDebugInfo(LOOP_Info oInfo)
{	cout << "LOOP Debug Report\n";
	cout << "=================\n";
	cout << "Class Info: \n";
	oInfo.Instance()->Class()->WriteDebuggingInfo();
	cout << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LOOP_LOOPLib_Standard::LOOPCMD_XYZZY(LOOP_Info oInfo)
{	cout << "And a good XYZZY to you too!\n";
}
//---------------------------------------------------------------------------------------- [Conditional] -
//SS
void LOOP_LOOPLib_Standard::LOOPCMD_IfStrEqu(LOOP_Info oInfo)
{	//If the two strings equal
		if(oInfo.GrabString(0) == oInfo.GrabString(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LOOP_LOOPLib_Standard::LOOPCMD_IfIntEqu(LOOP_Info oInfo)
{	//If the ints equal
		if(oInfo.GrabInt(0) == oInfo.GrabInt(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LOOP_LOOPLib_Standard::LOOPCMD_IfIntGT(LOOP_Info oInfo)
{	//If the int1 > int2
		if(oInfo.GrabInt(0) > oInfo.GrabInt(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ...  ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LOOP_LOOPLib_Standard::LOOPCMD_IfIntLT(LOOP_Info oInfo)
{	//If the int1 < int2
		if(oInfo.GrabInt(0) < oInfo.GrabInt(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LOOP_LOOPLib_Standard::LOOPCMD_IfIntGTI(LOOP_Info oInfo)
{	//If the int1 >= int2
		if(oInfo.GrabInt(0) >= oInfo.GrabInt(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LOOP_LOOPLib_Standard::LOOPCMD_IfIntLTI(LOOP_Info oInfo)
{	//If the int1 <= int2
		if(oInfo.GrabInt(0) <= oInfo.GrabInt(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//FF
void LOOP_LOOPLib_Standard::LOOPCMD_IfFloatEqu(LOOP_Info oInfo)
{	//If the float1 = float2
		if(oInfo.GrabFloat(0) == oInfo.GrabFloat(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//FF
void LOOP_LOOPLib_Standard::LOOPCMD_IfFloatGT(LOOP_Info oInfo)
{	//If the float1 > float2
		if(oInfo.GrabFloat(0) > oInfo.GrabFloat(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//FF
void LOOP_LOOPLib_Standard::LOOPCMD_IfFloatLT(LOOP_Info oInfo)
{	//If the float1 < float2
		if(oInfo.GrabFloat(0) < oInfo.GrabFloat(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//FF
void LOOP_LOOPLib_Standard::LOOPCMD_IfFloatGTI(LOOP_Info oInfo)
{	//If the float1 >= float2
		if(oInfo.GrabFloat(0) >= oInfo.GrabFloat(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//FF
void LOOP_LOOPLib_Standard::LOOPCMD_IfFloatLTI(LOOP_Info oInfo)
{	//If the float1 <= float2
		if(oInfo.GrabFloat(0) <= oInfo.GrabFloat(1))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//----------------------------------------------------------------------------------------------- [Misc] -
//
void LOOP_LOOPLib_Standard::LOOPCMD_Begin(LOOP_Info oInfo)
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LOOP_LOOPLib_Standard::LOOPCMD_End(LOOP_Info oInfo)
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LOOP_LOOPLib_Standard::LOOPCMD_REM(LOOP_Info oInfo)
{	//Do Nothing!
}
//-------------------------------------------------------------------------------- [String Manipulation] -
//[S]S
void LOOP_LOOPLib_Standard::LOOPCMD_StrEqu(LOOP_Info oInfo)
{	//Set the string
		oInfo.SetString(oInfo.GrabStringRef(0), oInfo.GrabString(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]S
void LOOP_LOOPLib_Standard::LOOPCMD_AppendStr(LOOP_Info oInfo)
{	//Append the string
		oInfo.SetString(oInfo.GrabStringRef(0), oInfo.GrabString(0) + oInfo.GrabString(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]SI
void LOOP_LOOPLib_Standard::LOOPCMD_InsertStr(LOOP_Info oInfo)
{	//vars
		string	s;		//The original string

	//Grab the original string
		s = oInfo.GrabString(0);
	
	//Insert the substring into it
 		s.insert(oInfo.GrabInt(0), oInfo.GrabString(1));	
   		
	//Set the string to its new value
		oInfo.SetString(oInfo.GrabStringRef(0), s);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]II
void LOOP_LOOPLib_Standard::LOOPCMD_RemoveSubStr(LOOP_Info oInfo)
{	//vars
		string	s;		//The original string
	
	//Grab the original string
		s = oInfo.GrabString(0);
	
	//Erase the sub string
		s.erase(oInfo.GrabInt(0), oInfo.GrabInt(1));
		
	//Set the string to the new s
		oInfo.SetString(oInfo.GrabStringRef(0), s);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]S
void LOOP_LOOPLib_Standard::LOOPCMD_UpperStr(LOOP_Info oInfo)
{	//Okey dokey, capatilize it
		oInfo.SetString(oInfo.GrabStringRef(0), UpperString(oInfo.GrabString(1)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]SII
void LOOP_LOOPLib_Standard::LOOPCMD_SubStr(LOOP_Info oInfo)
{	//vars
		string	s;
	
	//Grab the original string & sub string it
		s = oInfo.GrabString(1);
		s = s.substr(oInfo.GrabInt(0), oInfo.GrabInt(1));

	//Set the string to the substring
		oInfo.SetString(oInfo.GrabStringRef(0), s);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]S
void LOOP_LOOPLib_Standard::LOOPCMD_StrSize(LOOP_Info oInfo)
{	//Simply set the int to the size of the string
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabString(0).size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]I
void LOOP_LOOPLib_Standard::LOOPCMD_IntToStr(LOOP_Info oInfo)
{	//Simply set the int to the size of the string
		oInfo.SetString(oInfo.GrabStringRef(0), Val(oInfo.GrabInt(0)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]I
void LOOP_LOOPLib_Standard::LOOPCMD_FloatToStr(LOOP_Info oInfo)
{	//Simply set the int to the size of the string
		oInfo.SetString(oInfo.GrabStringRef(0), Val(oInfo.GrabFloat(0)));
}
//----------------------------------------------------------------------------------- [Int Manipulation] -
//[I]I
void LOOP_LOOPLib_Standard::LOOPCMD_IntEqu(LOOP_Info oInfo)
{	//Set the int
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]
void LOOP_LOOPLib_Standard::LOOPCMD_IntInc(LOOP_Info oInfo)
{	//Set the int
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(0) + 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]
void LOOP_LOOPLib_Standard::LOOPCMD_IntDec(LOOP_Info oInfo)
{	//Set the int
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(0) - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]II
void LOOP_LOOPLib_Standard::LOOPCMD_IntAdd(LOOP_Info oInfo)
{	//Add the ints
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(1) + oInfo.GrabInt(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]II
void LOOP_LOOPLib_Standard::LOOPCMD_IntSub(LOOP_Info oInfo)
{	//Subtract the ints
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(1) - oInfo.GrabInt(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]II
void LOOP_LOOPLib_Standard::LOOPCMD_IntMul(LOOP_Info oInfo)
{	//Multiply the ints
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(1) * oInfo.GrabInt(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]II
void LOOP_LOOPLib_Standard::LOOPCMD_IntDiv(LOOP_Info oInfo)
{	//Divide the ints
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(1) / oInfo.GrabInt(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]II
void LOOP_LOOPLib_Standard::LOOPCMD_IntMod(LOOP_Info oInfo)
{	//Modulate the ints
		oInfo.SetInt(oInfo.GrabIntRef(0), oInfo.GrabInt(1) % oInfo.GrabInt(2));
}
//--------------------------------------------------------------------------------- [Float Manipulation] -
//[F]F
void LOOP_LOOPLib_Standard::LOOPCMD_FloatEqu(LOOP_Info oInfo)
{	//Set the float
		oInfo.SetFloat(oInfo.GrabFloatRef(0), oInfo.GrabFloat(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[F]
void LOOP_LOOPLib_Standard::LOOPCMD_FloatInc(LOOP_Info oInfo)
{	//Increase the float
		oInfo.SetFloat(oInfo.GrabFloatRef(0), oInfo.GrabFloat(0) + 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[F]
void LOOP_LOOPLib_Standard::LOOPCMD_FloatDec(LOOP_Info oInfo)
{	//Decrease the float
		oInfo.SetFloat(oInfo.GrabFloatRef(0), oInfo.GrabFloat(0) - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[F]FF
void LOOP_LOOPLib_Standard::LOOPCMD_FloatAdd(LOOP_Info oInfo)
{	//Add floats
		oInfo.SetFloat(oInfo.GrabFloatRef(0), oInfo.GrabFloat(1) + oInfo.GrabFloat(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[F]FF
void LOOP_LOOPLib_Standard::LOOPCMD_FloatSub(LOOP_Info oInfo)
{	//Subtract floats
		oInfo.SetFloat(oInfo.GrabFloatRef(0), oInfo.GrabFloat(1) - oInfo.GrabFloat(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[F]FF
void LOOP_LOOPLib_Standard::LOOPCMD_FloatMul(LOOP_Info oInfo)
{	//Multiply floats
		oInfo.SetFloat(oInfo.GrabFloatRef(0), oInfo.GrabFloat(1) * oInfo.GrabFloat(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[F]FF
void LOOP_LOOPLib_Standard::LOOPCMD_FloatDiv(LOOP_Info oInfo)
{	//Divide floats
		oInfo.SetFloat(oInfo.GrabFloatRef(0), oInfo.GrabFloat(1) / oInfo.GrabFloat(2));
}
//----------------------------------------------------------------------------------------------- [Seek] -
//S
void LOOP_LOOPLib_Standard::LOOPCMD_Goto(LOOP_Info oInfo)
{	//Seek to the label
		oInfo.Seek(oInfo.GrabString(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LOOP_LOOPLib_Standard::LOOPCMD_GoSub(LOOP_Info oInfo)
{	//Create a new offset
		oInfo.NewOffset();
	
	//Now seek to that label, delete the offset if we failed
		if(!oInfo.Seek(oInfo.GrabString(0)))
		{	oInfo.DelOffset();
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//SS
void LOOP_LOOPLib_Standard::LOOPCMD_Send(LOOP_Info oInfo)
{	//Seek to the label of the object everybody gets another cookie oh yeah!
		oInfo.Seek(UpperString(oInfo.GrabString(0)), oInfo.GrabString(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//SS
void LOOP_LOOPLib_Standard::LOOPCMD_GoSend(LOOP_Info oInfo)
{	//Vars
		string sObject;
		LOOP_Instance* pInstance;
		
	//Grab the instance of the object
		sObject 	= UpperString(oInfo.GrabString(0));
		pInstance 	= oInfo.InstanceSet()->GetInstance(sObject);

	//Give the recieving object a new offset
		pInstance->AddOffset(pInstance->CurrentOffset().ClassCode(),
							 pInstance->CurrentOffset().Offset());

	//Seek to the label of the object everybody gets another cookie oh yeah!
		oInfo.Seek(UpperString(oInfo.GrabString(0)), oInfo.GrabString(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LOOP_LOOPLib_Standard::LOOPCMD_Return(LOOP_Info oInfo)
{	//Delete the last offset
		oInfo.DelOffset();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
//S
void LOOP_LOOPLib_Standard::LOOPCMD_Zap(LOOP_Info oInfo)
{	oInfo.ZapLabel(oInfo.GrabString(0));
}
