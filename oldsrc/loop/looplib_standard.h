/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cLOOPLib_Standard
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef LOOPLIB_STANDARD_H_
	#define LOOPLIB_STANDARD_H_
	
//Foundation
	#include "loopmacros.h"

//Dependencies
	#include "info.h"
	#include "loop.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cLOOPLib_Standard
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_LOOPLib_Standard
{	public:
	//- [Constuctors] -
 		LOOP_LOOPLib_Standard();
 		void Link(LOOP_LOOP* poLOOP);
 		
	//- [Debugging] -
		LOOPPORT(LOOPCMDPRT_Cout, 			LOOP_LOOPLib_Standard, LOOPCMD_Cout);			//S
		LOOPPORT(LOOPCMDPRT_CoutFloat, 		LOOP_LOOPLib_Standard, LOOPCMD_CoutFloat);		//F
		LOOPPORT(LOOPCMDPRT_CoutInt, 		LOOP_LOOPLib_Standard, LOOPCMD_CoutInt);		//I
		LOOPPORT(LOOPCMDPRT_CoutDebugInfo, 	LOOP_LOOPLib_Standard, LOOPCMD_CoutDebugInfo);	//
		LOOPPORT(LOOPCMDPRT_XYZZY, 			LOOP_LOOPLib_Standard, LOOPCMD_XYZZY);			//
	//- [Conditional] -
		LOOPPORT(LOOPCMDPRT_IfStrEqu,		LOOP_LOOPLib_Standard, LOOPCMD_IfStrEqu);		//SS
	 	LOOPPORT(LOOPCMDPRT_IfIntEqu, 		LOOP_LOOPLib_Standard, LOOPCMD_IfIntEqu); 		//II
		LOOPPORT(LOOPCMDPRT_IfIntGT, 		LOOP_LOOPLib_Standard, LOOPCMD_IfIntGT); 		//II
		LOOPPORT(LOOPCMDPRT_IfIntLT, 		LOOP_LOOPLib_Standard, LOOPCMD_IfIntLT); 		//II
		LOOPPORT(LOOPCMDPRT_IfIntGTI, 		LOOP_LOOPLib_Standard, LOOPCMD_IfIntGTI); 	 	//II
		LOOPPORT(LOOPCMDPRT_IfIntLTI, 		LOOP_LOOPLib_Standard, LOOPCMD_IfIntLTI); 	 	//II
		LOOPPORT(LOOPCMDPRT_IfFloatEqu, 	LOOP_LOOPLib_Standard, LOOPCMD_IfFloatEqu);  	//FF
		LOOPPORT(LOOPCMDPRT_IfFloatGT, 		LOOP_LOOPLib_Standard, LOOPCMD_IfFloatGT);  	//FF
		LOOPPORT(LOOPCMDPRT_IfFloatLT, 		LOOP_LOOPLib_Standard, LOOPCMD_IfFloatLT);  	//FF
		LOOPPORT(LOOPCMDPRT_IfFloatGTI, 	LOOP_LOOPLib_Standard, LOOPCMD_IfFloatGTI);  	//FF
		LOOPPORT(LOOPCMDPRT_IfFloatLTI, 	LOOP_LOOPLib_Standard, LOOPCMD_IfFloatLTI);  	//FF
	//- [Misc] -
		LOOPPORT(LOOPCMDPRT_Begin, 			LOOP_LOOPLib_Standard, LOOPCMD_Begin);			//
		LOOPPORT(LOOPCMDPRT_End, 			LOOP_LOOPLib_Standard, LOOPCMD_End); 			//
		LOOPPORT(LOOPCMDPRT_REM, 			LOOP_LOOPLib_Standard, LOOPCMD_REM); 			//S
	//- [String Manipulation] -
		LOOPPORT(LOOPCMDPRT_StrEqu, 		LOOP_LOOPLib_Standard, LOOPCMD_StrEqu);			//[S]S
		LOOPPORT(LOOPCMDPRT_AppendStr, 		LOOP_LOOPLib_Standard, LOOPCMD_AppendStr); 		//[S]S
		LOOPPORT(LOOPCMDPRT_InsertStr, 		LOOP_LOOPLib_Standard, LOOPCMD_InsertStr); 		//[S]SI
		LOOPPORT(LOOPCMDPRT_RemoveSubStr, 	LOOP_LOOPLib_Standard, LOOPCMD_RemoveSubStr); 	//[S]II
		LOOPPORT(LOOPCMDPRT_UpperString, 	LOOP_LOOPLib_Standard, LOOPCMD_UpperStr);	 	//[S]S
		LOOPPORT(LOOPCMDPRT_SubStr, 		LOOP_LOOPLib_Standard, LOOPCMD_SubStr); 		//[S]SII
		LOOPPORT(LOOPCMDPRT_StrSize, 		LOOP_LOOPLib_Standard, LOOPCMD_StrSize); 	 	//[I]S
		LOOPPORT(LOOPCMDPRT_IntToStr, 		LOOP_LOOPLib_Standard, LOOPCMD_IntToStr); 	 	//[S]I
		LOOPPORT(LOOPCMDPRT_FloatToStr,		LOOP_LOOPLib_Standard, LOOPCMD_FloatToStr);  	//[S]F
	//- [Int Manipulation] -
		LOOPPORT(LOOPCMDPRT_IntEqu, 		LOOP_LOOPLib_Standard, LOOPCMD_IntEqu);			//[I]I
		LOOPPORT(LOOPCMDPRT_IntInc, 		LOOP_LOOPLib_Standard, LOOPCMD_IntInc);			//[I]
		LOOPPORT(LOOPCMDPRT_IntDec, 		LOOP_LOOPLib_Standard, LOOPCMD_IntDec);			//[I]
		LOOPPORT(LOOPCMDPRT_IntAdd, 		LOOP_LOOPLib_Standard, LOOPCMD_IntAdd);			//[I]II
		LOOPPORT(LOOPCMDPRT_IntSub, 		LOOP_LOOPLib_Standard, LOOPCMD_IntSub);			//[I]II
		LOOPPORT(LOOPCMDPRT_IntMul, 		LOOP_LOOPLib_Standard, LOOPCMD_IntMul);			//[I]II
		LOOPPORT(LOOPCMDPRT_IntDiv, 		LOOP_LOOPLib_Standard, LOOPCMD_IntDiv);			//[I]II
		LOOPPORT(LOOPCMDPRT_IntMod, 		LOOP_LOOPLib_Standard, LOOPCMD_IntMod);			//[I]II
	//- [Float Manipulation] -
		LOOPPORT(LOOPCMDPRT_FloatEqu, 		LOOP_LOOPLib_Standard, LOOPCMD_FloatEqu);		//[F]F
		LOOPPORT(LOOPCMDPRT_FloatInc, 		LOOP_LOOPLib_Standard, LOOPCMD_FloatInc);		//[F]
		LOOPPORT(LOOPCMDPRT_FloatDec, 		LOOP_LOOPLib_Standard, LOOPCMD_FloatDec);		//[F]
		LOOPPORT(LOOPCMDPRT_FloatAdd, 		LOOP_LOOPLib_Standard, LOOPCMD_FloatAdd);		//[F]FF
		LOOPPORT(LOOPCMDPRT_FloatSub, 		LOOP_LOOPLib_Standard, LOOPCMD_FloatSub);		//[F]FF
		LOOPPORT(LOOPCMDPRT_FloatMul, 		LOOP_LOOPLib_Standard, LOOPCMD_FloatMul);		//[F]FF
		LOOPPORT(LOOPCMDPRT_FloatDiv, 		LOOP_LOOPLib_Standard, LOOPCMD_FloatDiv);		//[F]FF
	//- [Seek] -
		LOOPPORT(LOOPCMDPRT_Goto, 			LOOP_LOOPLib_Standard, LOOPCMD_Goto);			//S
		LOOPPORT(LOOPCMDPRT_GoSub, 			LOOP_LOOPLib_Standard, LOOPCMD_GoSub);			//S
		LOOPPORT(LOOPCMDPRT_Send, 			LOOP_LOOPLib_Standard, LOOPCMD_Send);			//SS
		LOOPPORT(LOOPCMDPRT_GoSend, 		LOOP_LOOPLib_Standard, LOOPCMD_GoSend);			//SS
		LOOPPORT(LOOPCMDPRT_Return, 		LOOP_LOOPLib_Standard, LOOPCMD_Return);			//
		LOOPPORT(LOOPCMDPRT_Zap, 			LOOP_LOOPLib_Standard, LOOPCMD_Zap);			//S
 	private:
 	//Vars
};

//Now ending looplib_standard.h
	#endif
