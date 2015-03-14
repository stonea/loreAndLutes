/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cLOOP
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef LOOP_H_
	#define LOOP_H_
	
//Aggregates
	#include "commandlibrary.h"
	#include "callbacklibrary.h"
	#include "classlibrary.h"
	#include "instanceset.h"
	#include "reader.h"
	#include "interpreter.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												cLOOP
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LOOP_LOOP
{	public:
	//- [Constuctors] -
 		LOOP_LOOP();
 		void Setup();
 		
	//- [Commands] -
		void NewCommand(string sIdentifier, void (*pFunction)(LOOP_Info, void*), void* pObject);
		void AddParam(eParam iParam);
		
	//- [Classes & Objects] -
		void ReadClass  (string sFile);
		void ReadClass  (string sFile, int iStart, bool fError = false);
		void NewInstance(int 	iOfClass, string sObjectIdentifier, eScope iScope);
		void NewInstance(string sOfClass, string sObjectIdentifier, eScope iScope);
		void RunInstance(int iNumber);
		void RunInstance(string sObjectIdentifier);
		void GosubInstance(string sObjectIdentifier, string sTo);
		void ClearInstanceOffsets(string sObjectIdentifier);
		void ClearClasses();
		void ClearInstances();
		LOOP_Class&		Class(string sIdentifier);
		LOOP_Instance&	Instance(string sIdentifier);
		MEMVAR_GETREF(Reader, LOOP_Reader, myoRead);
		bool LegalOffset(LOOP_Offset oOffset);
		bool IsDerivative(string sClass, string sOf);
		bool IsClass(string sClass);
 	
 	private:
 	//Vars
 		//Commands
	 		LOOP_CommandLibrary		myoLib;
 			LOOP_CallbackLibrary 	myoCallbackLib;
		//Classes & Objects
			LOOP_ClassLibrary 		myoClassSet;
			LOOP_InstanceSet 		myoInstanceSet;
		//Reader & VM
			LOOP_Reader 			myoRead;
			LOOP_Interpreter 		myoVM;
};

//Now ending loop.h
	#endif
