/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cInfo
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef INFO_H_
	#define INFO_H_

//Aggregates
	#include "instance.h"
	#include "instanceset.h"
	#include "code.h"
	#include "parameters.h"
	#include "parammap.h"
	#include "classlibrary.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cInfo
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_Info
{	public:
	//- [Constuctors] -
 		LOOP_Info();
 		
	//- [Direct Info Setting\Getting] -
		MEMVAR_SETGET(SetInstance, 	  Instance,		LOOP_Instance*, 	mypInstance);
		MEMVAR_SETGET(SetInstanceSet, InstanceSet, 	LOOP_InstanceSet*, 	mypInstanceSet);
		MEMVAR_SETGET(SetCode, 		  Code, 		LOOP_Code*, 	mypCode);
		MEMVAR_SETGET(SetParameters,  Parameters,	LOOP_Parameters*, 	mypParameters);
		MEMVAR_SETGET(SetParamMap, 	  ParamMap, 	LOOP_ParamMap*, 	mypParamMap);
		MEMVAR_SETGET(SetClassSet,	  ClassSet,		LOOP_ClassLibrary*,	mypClassSet);
		
	//- [Param Reading] -
		int 	GrabInt			(int iNumber);
		double 	GrabFloat		(int iNumber);
		string 	GrabString		(int iNumber);
		int 	GrabIntRef		(int iNumber);
		int 	GrabFloatRef	(int iNumber);
		int 	GrabStringRef	(int iNumber);
		
	//- [Variable Setting] -
		void	SetInt	 (int iLocation, int iTo);
		void	SetFloat (int iLocation, double dTo);
		void	SetString(int iLocation, string sTo);
		
	//- [Label Handeling] -
		bool Seek(string sLabel);								//Sends this objects point of execution to the label w/ identifier sLabel
		bool Seek(string sObject, string sLabel);				//Sends object sObject to sLabel point of execution
		void SeekSkip();										//Seeks two lines
		void SeekToCommand(string sCommand, string sNewBlock);  //Seeks the point of execution to the next sCommand, ignore 1 sCommand for every sNewBlock found
		bool NextLine(string sCommand);							//True if the command on the next line has the identifier sCommand
		void NewOffset();										//Adds a new offset in the offset list
		void DelOffset();										//Deletes the last offset in the offset list
		int	 NumOffsets();										//Returns the # of offsets
		int	 OffsetAt(int iIndex);								//Returns the location of offset # iIndex
		void ZapLabel(string sLabel);	
 	
 	private:
 	//P- [Label Handeling] -P
 		bool ZappedLabel(string sLabel);
		int	 ZapCount(string sLabel);
		LOOP_Instance::LOOP_Instance_Zap& Zap(string sLabel);
 	
	//P- [Param Reading] -P
 		int FindType(vector<eParam> lType, int iIndexth);
 		int Occurances(eParam iType, int iMaxElement);
 		int GrabLocal(eParam iParam, int iIndex);
 		int	ParamLocation(eParam iParam, int iOccurances);
 	//Vars
 		LOOP_Instance*		mypInstance;
 		LOOP_InstanceSet*	mypInstanceSet;
 		LOOP_Code*			mypCode;
 		LOOP_Parameters*	mypParameters;
 		LOOP_ParamMap*		mypParamMap;
 		LOOP_ClassLibrary*	mypClassSet;
};

//Now ending info.h
	#endif
