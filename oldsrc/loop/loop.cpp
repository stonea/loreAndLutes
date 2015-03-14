/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_LOOP
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "loop.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_LOOP
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_LOOP::LOOP_LOOP()
{	Setup();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::Setup()
{	//Setup the reader
		myoRead.SetCommandLibrary(&myoLib);
		myoRead.SetClassSet(&myoClassSet);
		
	//Setup the VM
		myoVM.SetCommandLibrary	(&myoLib);
		myoVM.SetCallbackLibrary(&myoCallbackLib);
		myoVM.SetInstanceSet	(&myoInstanceSet);
		myoVM.SetClassSet		(&myoClassSet);
		myoVM.SetInstanceSet	(&myoInstanceSet);
}
//------------------------------------------------------------------------------------------- [Commands] -
void LOOP_LOOP::NewCommand(string sIdentifier, void (*pFunction)(LOOP_Info, void*), void* pObject)
{	LOOP_Callback	oCall;
	LOOP_Command	oCmd;

	oCall.SetFunction(pFunction);
	oCall.SetObject(pObject);
	myoCallbackLib.AddCallback(oCall);
	
	oCmd.ClearParams();
	oCmd.SetIdentifier(sIdentifier);
	oCmd.SetCallbackIdentifier(myoCallbackLib.NumCallbacks()-1);
	myoLib.AddCommand(oCmd);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::AddParam(eParam iParam)
{	LOOP_Command* poCmd;
	poCmd = myoLib.GetCommand(myoLib.NumCommands()-1);
	poCmd->NewParam(iParam);
}		
//---------------------------------------------------------------------------------- [Classes & Objects] -
void LOOP_LOOP::ReadClass(string sFile)
{	myoClassSet.NewClass();
	myoRead.Read(myoClassSet.LastClass(), myoClassSet.NumClasses()-1, sFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::ReadClass(string sFile, int iStart, bool fError)
{
if(!fError)
{	myoClassSet.NewClass();
	myoRead.Read(myoClassSet.LastClass(), myoClassSet.NumClasses()-1, sFile, iStart);
}
else
{	myoClassSet.NewClass();
	myoRead.Read(myoClassSet.LastClass(), myoClassSet.NumClasses()-1, sFile, iStart);
}

}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::NewInstance(int iOfClass, string sObjectIdentifier, eScope iScope)
{	//Capatilize the identifier
		sObjectIdentifier = UpperString(sObjectIdentifier);
	//Make the new instance
		myoInstanceSet.NewInstance(myoClassSet.GetClass(iOfClass), iScope);
	//Identify it yo'
		myoInstanceSet.GetInstance(myoInstanceSet.NumInstances()-1)->SetIdentifier(
  			UpperString(sObjectIdentifier));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::NewInstance(string sOfClass, string sObjectIdentifier, eScope iScope)
{	//Capatilize the identifier
		sObjectIdentifier = UpperString(sObjectIdentifier);
	//Make the new instance
		myoInstanceSet.NewInstance(myoClassSet.GetClass(myoClassSet.FindClass(sOfClass)), iScope);
	//Identify it yo'
		myoInstanceSet.GetInstance(myoInstanceSet.NumInstances()-1)->SetIdentifier(
  			UpperString(sObjectIdentifier));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::RunInstance(int iNumber)
{	myoVM.Run(iNumber);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::RunInstance(string sObjectIdentifier)
{	myoVM.Run(sObjectIdentifier);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Assumes standard lib with "GoSub" commmand is linked and workin'
void LOOP_LOOP::GosubInstance(string sObjectIdentifier, string sTo)
{	//Find the object (map its local to iObject)
		//Vars
			const static int NO_OBJECT = -1;
			int iObject = NO_OBJECT;
		//Capatilize sObject
			sObjectIdentifier = UpperString(sObjectIdentifier);
		//Search for the object
			for(int i = 0; i < myoInstanceSet.NumInstances(); i++)
			{	if(myoInstanceSet.GetInstance(i)->Identifier() == sObjectIdentifier)
					iObject = i;
			}
	//If we couldn't find an object we're done
		if(iObject == NO_OBJECT)
			return;
	//Now call the GOSub command on this objecto
		//Vars
			LOOP_Instance* 	poInstance;
			LOOP_Code		oCode;
			LOOP_Command*	poCommand;
			LOOP_Info		oInfo;
			LOOP_Parameters	oParams;
			LOOP_ParamMap	oParamMap;
		//Grab the object
			poInstance 	= myoInstanceSet.GetInstance(iObject);
		//Create the code to gosub
			oParams.NewString(sTo);
			oParamMap.New(PARAM_STRING);
			oCode.SetCommand(myoLib.GetCommand(myoLib.SearchForCommand("GOSUB")));
			oCode.SetParameters		(oParams);
			oCode.SetParametersMap	(oParamMap);
		//Grab the command
			poCommand = NULL;
			poCommand = oCode.Command();
		//Define the info object
			oInfo.SetInstance	(poInstance);
			oInfo.SetCode		(&oCode);
			oInfo.SetParameters	(&oParams);
			oInfo.SetParamMap	(&oParamMap);
			oInfo.SetClassSet	(&myoClassSet);
		//Call this command's callback (This is the extremley cool part!)
			myoCallbackLib.Run(poCommand->CallbackIdentifier(), &oInfo);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::ClearInstanceOffsets(string sObjectIdentifier)
{	//Find the object (map its local to iObject)
		//Vars
			const static int NO_OBJECT = -1;
			int iObject = NO_OBJECT;
			LOOP_Instance* 	poInstance;
		//Capatilize sObject
			sObjectIdentifier = UpperString(sObjectIdentifier);
		//Search for the object
			for(int i = 0; i < myoInstanceSet.NumInstances(); i++)
			{	if(myoInstanceSet.GetInstance(i)->Identifier() == sObjectIdentifier)
					iObject = i;
			}
			
	//If we have an object
		if(iObject != NO_OBJECT)
		{	//Grab a pointer to it
	  			poInstance = myoInstanceSet.GetInstance(iObject);
			//Clear all offsets
				while(poInstance->NumOffsets() > 0)
				{	poInstance->RemoveLastOffset();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::ClearClasses()
{	myoClassSet.ClearClasses();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_LOOP::ClearInstances()
{	myoInstanceSet.ClearInstances();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Class& LOOP_LOOP::Class(string sIdentifier)
{	//Return the class from the class set
		return(*myoClassSet.GetClass(myoClassSet.FindClass(UpperString(sIdentifier))));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Instance& LOOP_LOOP::Instance(string sIdentifier)
{	//Vars
		int iObject = -1;
	//Search for the object
		for(int i = 0; i < myoInstanceSet.NumInstances(); i++)
		{	if(myoInstanceSet.GetInstance(i)->Identifier() == sIdentifier)
				iObject = i;
		}
	//return the instance
		if(iObject == -1)
			cerr << "ERR Invalid Instance in LOOP_LOOP::Instance()\n";
		
		return(*myoInstanceSet.GetInstance(iObject));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_LOOP::LegalOffset(LOOP_Offset oOffset)
{	if(oOffset.ClassCode() >= 0 && oOffset.ClassCode() < myoClassSet.NumClasses())
	{	if	(	oOffset.Offset() >= 0 &&
 				oOffset.Offset() < myoClassSet.GetClass(oOffset.ClassCode())->NumCodes()
    		)
		{			
			return true;
		}
	}
	
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_LOOP::IsDerivative(string sClass, string sOf)
{	//Vars
		LOOP_Class* mypoClass;

	//Capatilize it all
		sClass = UpperString(sClass);
		sOf    = UpperString(sOf);
	//Grab a pointer to this class
		mypoClass = myoClassSet.GetClass(myoClassSet.FindClass(sClass));
	//If we didn't find it we're done
		if(mypoClass == NULL)
			return(false);
	//Backtrack through all of this classes parents
		while(sClass != "")
		{	//If this class has the same identifier as sOf we're done
				if(sClass == sOf)
					return true;
			//If this class has a parent change to that
				if(mypoClass->Parent() != NULL)
				{	mypoClass = mypoClass->Parent();
					sClass = mypoClass->Identifier();
				}
			//If the parent is null we're done
				else
				{	return(false);
				}
		}
	//If execution gets here (it shouldn't) nothing was found
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LOOP_LOOP::IsClass(string sClass)
{	//Capatilize it all
		sClass = UpperString(sClass);
	//See if it's a class
		if(myoClassSet.FindClass(sClass) >= 0)
			return true;
		return false;
}
