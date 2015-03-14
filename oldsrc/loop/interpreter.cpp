/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Interpreter
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "interpreter.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Interpreter
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Interpreter::LOOP_Interpreter()
{
}
//-------------------------------------------------------------------------------------------- [Running] -
void LOOP_Interpreter::Run(int iObject)
{	//Vars
		LOOP_Instance* 	poInstance;
		LOOP_Class*		poClass;
		LOOP_Code		oCode;
		LOOP_Command*	poCommand;
		LOOP_Info		oInfo;
		LOOP_Parameters	oParams;
		LOOP_ParamMap	oParamMap;

	//Grab the object and the class of the current offset
		poInstance 	= mypoInstances->GetInstance(iObject);
		poClass		= mypoClassSet->GetClass(poInstance->CurrentOffset().ClassCode());

	//Only continue if theres atleast 1 offset
		if(poInstance->NumOffsets() > 0)
		{	//Grab the code (if possible)
				if(poInstance->CurrentOffset().Offset() < poClass->NumCodes());
					oCode = poClass->GetCode(poInstance->CurrentOffset().Offset());
			//Move the offset on down
				poInstance->MoveCurrentOffset(	poInstance->CurrentOffset().ClassCode(),
  												poInstance->CurrentOffset().Offset() + 1);
	
			//Grab the command
				poCommand = NULL;
				poCommand = oCode.Command();

			//Only Continue If this isn't a NULL command
    			if(poCommand != NULL)
		     	{	//Grab the parameters
						oParams 	= oCode.Parameters();
						oParamMap	= oCode.ParametersMap();

					//Define the info object
						oInfo.SetInstance	(poInstance);
						oInfo.SetCode		(&oCode);
						oInfo.SetParameters	(&oParams);
						oInfo.SetParamMap	(&oParamMap);
						oInfo.SetClassSet	(mypoClassSet);
					
					//Call this command's callback (This is the extremley cool part!)
						mypoCallbacks->Run(poCommand->CallbackIdentifier(), &oInfo);
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Interpreter::Run(string sObject)
{	//Vars
		const static int NO_OBJECT = -1;
		int iObject = NO_OBJECT;

	//Capatilize sObject
		sObject = UpperString(sObject);
	//Search for the object
		for(int i = 0; i < mypoInstances->NumInstances(); i++)
		{	if(mypoInstances->GetInstance(i)->Identifier() == sObject)
				iObject = i;
		}
	//If we found the object run it
		if(iObject != NO_OBJECT)
		{	Run(iObject);
		}
}
