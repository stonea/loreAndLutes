/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Info
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "info.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Info
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Info::LOOP_Info()
{
}
//-------------------------------------------------------------------------------------- [Param Reading] -
int LOOP_Info::GrabInt(int iNumber)
{	//Vars
		vector<eParam> 	liType;
		int			    iLocation;
	
	//Set what a int type is:
		liType.push_back(PARAM_INT);
		liType.push_back(PARAM_INT_REF);

	//Find the location of the iIndexth liType
		iLocation = FindType(liType, iNumber);
	
	//Decide what to do based on whether this param was passed as a constant or var
		//- [Constant] -
			if(mypParamMap->Param(iLocation) == PARAM_INT)
				return(mypParameters->GetInt(Occurances(PARAM_INT, iLocation)));
		//- [Var] -
			else
				return(mypInstance->Variables()->GetInt(
    				mypParameters->GetIntRef(Occurances(PARAM_INT_REF, iLocation))));
			
	//Return 0 by deafult
		return(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
double LOOP_Info::GrabFloat(int iNumber)
{	//Vars
		vector<eParam> 	liType;
		int			    iLocation;

	//Set what a float type is:
		liType.push_back(PARAM_FLOAT);
		liType.push_back(PARAM_FLOAT_REF);

	//Find the location of the iIndexth liType
		iLocation = FindType(liType, iNumber);
		
	//Decide what to do based on whether this param was passed as a constant or var
		//- [Constant] -
			if(mypParamMap->Param(iLocation) == PARAM_FLOAT)
			{	double d =	mypParameters->GetFloat(Occurances(PARAM_FLOAT, iLocation));
   				return(d);
			}
		//- [Var] -
			else
				return(mypInstance->Variables()->GetFloat(
	 				mypParameters->GetFloatRef(Occurances(PARAM_FLOAT_REF, iLocation))));
			
	//Return 0 by deafult
		return(0.0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LOOP_Info::GrabString(int iNumber)
{	//Vars
		vector<eParam> 	liType;
		int			    iLocation;
	
	//Set what a string type is:
		liType.push_back(PARAM_STRING);
		liType.push_back(PARAM_STRING_REF);

	//Find the location of the iIndexth liType
		iLocation = FindType(liType, iNumber);
	
	//Decide what to do based on whether this param was passed as a constant or var
		//- [Constant] -
			if(mypParamMap->Param(iLocation) == PARAM_STRING)
				return(mypParameters->GetString(Occurances(PARAM_STRING, iLocation)));
		//- [Var] -
			else
				return(mypInstance->Variables()->GetString(
    				mypParameters->GetStringRef(Occurances(PARAM_STRING_REF, iLocation))));
			
	//Return "" by deafult
		return("");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Info::GrabIntRef(int iNumber)
{	//Okay return that iIndexth pointer to int
		return(mypParameters->GetIntRef(GrabLocal(PARAM_INT_REF, iNumber)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Info::GrabFloatRef(int iNumber)
{	//Okay return that iIndexth pointer to float
		return(mypParameters->GetFloatRef(GrabLocal(PARAM_FLOAT_REF, iNumber)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Info::GrabStringRef(int iNumber)
{	//Okay return that iIndexth pointer to string
		return(mypParameters->GetStringRef(GrabLocal(PARAM_STRING_REF, iNumber)));
}
//----------------------------------------------------------------------------------- [Variable Setting] -
void LOOP_Info::SetInt(int iLocation, int iTo)
{	mypInstance->Variables()->SetInt(iLocation, iTo);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Info::SetFloat(int iLocation, double dTo)
{	mypInstance->Variables()->SetFloat(iLocation, dTo);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Info::SetString(int iLocation, string sTo)
{	mypInstance->Variables()->SetString(iLocation, sTo);
}
//------------------------------------------------------------------------------------ [Label Handeling] -
//Sends this objects point of execution to the label w/ identifier sLabel
bool LOOP_Info::Seek(string sLabel)
{	//vars
		LOOP_Label oLabel;
		int iZapCount = 0;
		bool fLabelFound = false;
	//Capatilize the label
		sLabel  = UpperString(sLabel);
	//Translate the label identifier into caps
		sLabel = UpperString(sLabel);
	//While we haven't found it
		while(fLabelFound == false)
		{	//Grab the label
				oLabel = mypInstance->Class()->GetLabel(sLabel, iZapCount);
			//If it isn't a valid label then we're done
				if(oLabel.Identifier() == "")
					fLabelFound = true;
			//If it is check for zaps
				else
				{	if(ZappedLabel(sLabel))
					{	if(iZapCount >= ZapCount(sLabel))
						{	fLabelFound = true;
						}
		
     					iZapCount++;
					}
					else
						fLabelFound = true;
				}
		}
	//If a valid label seek there
		if(oLabel.Identifier() != "")
		{	mypInstance->MoveCurrentOffset(oLabel.Class(), oLabel.Location());
			return true;
		}
		
	//We failed
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Sends object sObject to sLabel point of execution
bool LOOP_Info::Seek(string sObject, string sLabel)
{	//vars
		LOOP_Label oLabel;
		int iZapCount = 0;
		bool fLabelFound = false;
	//Capatilize the label and the object
		sObject = UpperString(sObject);
		sLabel  = UpperString(sLabel);
	//Translate the label identifier into caps
		sLabel = UpperString(sLabel);
	//While we haven't found it
		while(fLabelFound == false)
		{	//Grab the label
				oLabel = mypInstance->Class()->GetLabel(sLabel, iZapCount);
			//If it isn't a valid label then we're done
				if(oLabel.Identifier() == "")
					fLabelFound = true;
			//If it is check for zaps
				else
				{	if(ZappedLabel(sLabel))
					{	if(iZapCount >= ZapCount(sLabel))
						{	fLabelFound = true;
						}
		
     					iZapCount++; 
					}
					else
						fLabelFound = true;
				}
		}
	//If a valid label seek there
		if(oLabel.Identifier() != "")
		{	mypInstanceSet->GetInstance(sObject)->MoveCurrentOffset(oLabel.Class(), oLabel.Location());
			return true;
		}
			
	//We failed
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Seeks two lines
void LOOP_Info::SeekSkip()
{	//Make an offset 1 from the current one
		LOOP_Offset oOffset = mypInstance->CurrentOffset();
		oOffset.SetOffset(oOffset.Offset() + 1);
	//Seek there
		mypInstance->ChangeOffset(mypInstance->NumOffsets()-1, oOffset);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Seeks the point of execution to the next sCommand, ignore 1 sCommand for every sNewBlock found
void LOOP_Info::SeekToCommand(string sCommand, string sNewBlock)
{	//Vars
		bool fDone = false;		//True once we're done
		string sIdentifier;		//Holds a command's identifier
		int  iBlocksLeft = 1;	//Holds # of blocks left to parse (occurances of sIdentifier to find)
		LOOP_Command*	poCommand;
	
	//Read in and ignore the "Begin" command
		mypInstance->MoveCurrentOffset(	mypInstance->CurrentOffset().ClassCode(),
  										mypInstance->CurrentOffset().Offset()+1);
	
	//When we're not done
		while(fDone == false)
		{	//Grab a command
				poCommand = NULL;
				poCommand = mypClassSet->GetClass
    						(	mypInstance->CurrentOffset().ClassCode()
          					)->GetCode
               				(	mypInstance->CurrentOffset().Offset()
                			).Command();

			//Grab the identifier
				if(poCommand != NULL)
					sIdentifier = poCommand->Identifier();
				else
					sIdentifier = "#?#NULLCMD";

			//Keep on a truckin' down that lil' ol' code-a-stream
				mypInstance->MoveCurrentOffset(	mypInstance->CurrentOffset().ClassCode(),
  												mypInstance->CurrentOffset().Offset()+1);
			
			//See if this is a new block command
				if(sIdentifier == sNewBlock)
				{	//1 more block to find
						iBlocksLeft++;
				}
			
			//See if that command qualifies
				if(sIdentifier == sCommand)
				{	//Decriment the blocks left
						iBlocksLeft--;
					
					//If we're done
						if(iBlocksLeft == 0)
						{	//We're done
								fDone = true;
						}
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//True if the command on the next line has the identifier sCommand
bool LOOP_Info::NextLine(string sCommand)
{	//Vars
		LOOP_Class* pClass;
	//If the next offset is legal
		if(mypInstance->CurrentOffset().Offset()+1 < mypInstance->Class()->NumCodes())
		{	//Grab the class
				pClass = mypClassSet->GetClass(mypInstance->CurrentOffset().ClassCode());
  
  			//See if our code's identifier mathces sCommand return true else false
				if(	pClass->GetCode(mypInstance->CurrentOffset().Offset()).Command()->Identifier() ==
					sCommand)
				{	return true;
				}
				else
					return false;
				
		}
	//If the next offset was illegal return false
		else
			return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Adds a new offset in the offset list
void LOOP_Info::NewOffset()
{	//If there's > 0 offset create an offset there
		if(mypInstance->NumOffsets() > 0)
			mypInstance->AddOffset(	mypInstance->CurrentOffset().ClassCode(),
									mypInstance->CurrentOffset().Offset());
	//Else create an offset at the start
		else
			mypInstance->AddOffset(mypInstance->Class()->NumericIdentifier(), 0);
		
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Deletes the last offset in the offset list
void LOOP_Info::DelOffset()
{	mypInstance->RemoveLastOffset();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Returns the # of offsets
int	 LOOP_Info::NumOffsets()
{	return(mypInstance->NumOffsets());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Returns the location of offset # iIndex
int	 LOOP_Info::OffsetAt(int iIndex)
{	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_Info::ZappedLabel(string sLabel)
{	//Loop through all possible zaps
		for(int i = 0; i < mypInstance->Zaps().size(); i++)
		{	if(mypInstance->Zaps()[i].sLabel == sLabel)
				return(true);
		}
	//If execution gets here no zaps were found
		return(false);
}
//P----------------------------------------------------------------------------- [Label Handeling] -P
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... .P
int	LOOP_Info::ZapCount(string sLabel)
{	//Loop through all possible zaps
		for(int i = 0; i < mypInstance->Zaps().size(); i++)
		{	if(mypInstance->Zaps()[i].sLabel == sLabel)
				return(mypInstance->Zaps()[i].iTimesZapped);
		}
	//If execution gets here no zaps were found
		return(-1);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... .P
LOOP_Instance::LOOP_Instance_Zap& LOOP_Info::Zap(string sLabel)
{	//Loop through all possible zaps
		for(int i = 0; i < mypInstance->Zaps().size(); i++)
		{	if(mypInstance->Zaps()[i].sLabel == sLabel)
				return(mypInstance->Zaps()[i]);
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... .P
void LOOP_Info::ZapLabel(string sLabel)
{	//Capatilize the label
		sLabel  = UpperString(sLabel);
	//If this label exists
		if(ZappedLabel(sLabel))
		{	//Add it in
				Zap(sLabel).iTimesZapped++;
		}
	//Else add this sucker in
		mypInstance->Zaps().resize(mypInstance->Zaps().size() + 1);
		mypInstance->Zaps()[mypInstance->Zaps().size() - 1].sLabel = sLabel;
		mypInstance->Zaps()[mypInstance->Zaps().size() - 1].iTimesZapped = 1;
		
cerr << "Label Zapped; " << sLabel << "\n";
}
//P------------------------------------------------------------------------------------ [Param Reading] -P
int LOOP_Info::FindType(vector<eParam> lType, int iIndexth)
{	//Vars
		int iOccurances = 0;	//Counts # of occurances of lType found so far

	//Loop through all the params in the map
		for(int i = 0; i < mypParamMap->NumParams(); i++)
		{	//Determine if we've found another lType
				//Loop through all the lTypes
					for(unsigned  int k = 0; k < lType.size(); k++)
					{	//If this lType is the same as the param						
							if(lType[k] == mypParamMap->Param(i))
							{	//Update the counter
									iOccurances++;
							}
					}
					
			//See if we've met iIndexth occurances
				if(iIndexth == iOccurances-1)
				{	//If so return location i
						return(i);
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Returns # of occurances of iType in map oMap until the iMaxElment of oMap
int LOOP_Info::Occurances(eParam iType, int iMaxElement)
{	//Vars
		int iOccurances = 0;	//Holds the # of ouccurances of iType so far
	
	//Loop through all the elements we're searching through
		for(int i = 0; i < iMaxElement; i++)
		{	//See if this is a new occurance
				if(mypParamMap->Param(i) == iType)
					iOccurances++;
		}
		
	//Return # of occurances
		return(iOccurances);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Grabs the location of the iIndexth iParam passed to the command
int LOOP_Info::GrabLocal(eParam iParam, int iIndex)
{	//Vars
		int iParameter;
		int iOccurances;
		
	//Figure out which parameter is the one of interest
		iParameter = ParamLocation(iParam, iIndex);

	//Grab the occurances
		iOccurances = Occurances(iParam, iParameter);
	
	//Return iOccurances
		return(iOccurances);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
//Figures out the location of the iOccurances-th iParam
int	LOOP_Info::ParamLocation(eParam iParam, int iOccurances)
{	//vars
		int iOccurancesSoFar = 0;	//Holds the # of occurances found of iParam so far
	
	//Loop through all the elements of oMap
		for(int i = 0; i < mypParamMap->NumParams(); i++)
		{	//If param i matches param iParam
				if(mypParamMap->Param(i) == iParam)
				{	//Update # of occurances found so far
						iOccurancesSoFar++;
				}
				
			//If we've found the iOccurances param of iParam
				if(iOccurancesSoFar == iOccurances + 1)
					return(i);
		}
}
