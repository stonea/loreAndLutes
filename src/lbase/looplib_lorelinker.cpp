/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			looplib_lorelinker.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "looplib_lorelinker.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Vehicle
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_LOOPLib_LoreLinker::LL_LOOPLib_LoreLinker()
{
}
//-------------------------------------------------------------------------------------------- [Linking] -
void LL_LOOPLib_LoreLinker::Link(LL_Game* poGame, LL_LOOPLib_Lore* LL_Lib)
{	//Vars
		string sInstance;
		
	//Link the global script
		poGame->UnitSet().GlobalScript()->SetLibInfo(&LL_Lib->LoreInfo());
		poGame->UnitSet().GlobalScript()->SetLOOP(&poGame->LOOP());

	//Just loop through the scripted unit sets and link
		for(int i = 0; i < poGame->UnitSet().NumScriptedUnits(); i++)
		{	//Link
				poGame->UnitSet().ScriptedUnit(i).SetLibInfo(&LL_Lib->LoreInfo());
				poGame->UnitSet().ScriptedUnit(i).SetLOOP(&poGame->LOOP());
			//Grab the instance identifier
				sInstance = UpperString(poGame->UnitSet().ScriptedUnit(i).Identifier());

			//Set default vars
				SetDefaults(&poGame->UnitSet().ScriptedUnit(i),
    						&poGame->LOOP().Instance(sInstance));
		}
}
//---------------------------------------------------------------------------------------- [Defaults] -
int LL_LOOPLib_LoreLinker::DefaultInt(LL_Game* poGame, string sObjectIdentifier, string sVarIdentifier)
{	//Vars
		LL_ScriptedUnit* poScriptedUnit;
  		LOOP_Instance* poInstance;

	//Just loop through all scripted units until we find the one with sObjectIdentifier
	for(int i = 0; i < poGame->UnitSet().NumScriptedUnits(); i++)
	{	//Grab the instance identifier
			string sInstance = UpperString(poGame->UnitSet().ScriptedUnit(i).Identifier());
		//If this = sObjectIdentifier
			if(sInstance == UpperString(sObjectIdentifier))
			{	//Grab pointers to the unit and instance
					poScriptedUnit = &poGame->UnitSet().ScriptedUnit(i);
					poInstance	   = &poGame->LOOP().Instance(sInstance);
   
   				//Loop until we find the int, return that
					for(int j = 0; j < poScriptedUnit->DefaultInts().Length(); j++)
					{	if(poInstance->Variables()->IntPublic(poScriptedUnit->DefaultInts()[j]))
						{	return(
      							poInstance->Variables()->GetInt(poScriptedUnit->DefaultInts()[j]));
						}
					}
			}
	}

	//Default
		return(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
double LL_LOOPLib_LoreLinker::DefaultFloat(LL_Game* poGame, string sObjectIdentifier,
										   string sVarIdentifier)
{	//Vars
		LL_ScriptedUnit* poScriptedUnit;
  		LOOP_Instance* poInstance;
  		
	//Just loop through all scripted units until we find the one with sObjectIdentifier
	for(int i = 0; i < poGame->UnitSet().NumScriptedUnits(); i++)
	{	//Grab the instance identifier
			string sInstance = UpperString(poGame->UnitSet().ScriptedUnit(i).Identifier());
		//If this = sObjectIdentifier
			if(sInstance == UpperString(sObjectIdentifier))
			{	//Grab pointers to the unit and instance
					poScriptedUnit = &poGame->UnitSet().ScriptedUnit(i);
					poInstance	   = &poGame->LOOP().Instance(sInstance);
   			
      			//Loop until we find the float, return that
					for(int j = 0; j < poScriptedUnit->DefaultFloats().Length(); j++)
					{	if(poInstance->Variables()->FloatPublic(poScriptedUnit->DefaultFloats()[j]))
						{	return(
      							poInstance->Variables()->GetFloat(poScriptedUnit->DefaultFloats()[j]));
						}
					}
			}
	}

	//Default
		return(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_LOOPLib_LoreLinker::DefaultString(LL_Game* poGame, string sObjectIdentifier,
											string sVarIdentifier)
{	//Vars
		LL_ScriptedUnit* poScriptedUnit;
  		LOOP_Instance* poInstance;
	//Just loop through all scripted units until we find the one with sObjectIdentifier
	for(int i = 0; i < poGame->UnitSet().NumScriptedUnits(); i++)
	{	//Grab the instance identifier
			string sInstance = UpperString(poGame->UnitSet().ScriptedUnit(i).Identifier());
		//If this = sObjectIdentifier
			if(sInstance == UpperString(sObjectIdentifier))
			{	//Grab pointers to the unit and instance
					poScriptedUnit = &poGame->UnitSet().ScriptedUnit(i);
					poInstance	   = &poGame->LOOP().Instance(sInstance);
					
   				//Loop until we find the string, return that
					for(int j = 0; j < poScriptedUnit->DefaultStrings().Length(); j++)
					{	if(UpperString(poScriptedUnit->DefaultStrings()[j]) == UpperString(sVarIdentifier))
	     					if(poInstance->Variables()->StringPublic(poScriptedUnit->DefaultStrings()[j]))
							{	return(poInstance->Variables()->GetString(
									   poScriptedUnit->DefaultStrings()[j]));
							}
					}
			}
	}

	//Default
		return("\n");
}
//P---------------------------------------------------------------------------------------- [Defaults] -P
void LL_LOOPLib_LoreLinker::SetDefaults(LL_ScriptedUnit* poScriptedUnit, LOOP_Instance* poInstance)
{	//Loop through default strings, change if public
		for(int i = 0; i < poScriptedUnit->DefaultStrings().Length(); i++)
		{	if(poInstance->Variables()->StringPublic(poScriptedUnit->DefaultStrings()[i]))
			{	poInstance->Variables()->SetString(poScriptedUnit->DefaultStrings()[i],
			 	  		 		    			   poScriptedUnit->DefaultStringsValues()[i]);
			}
		}
	//Loop through default ints, change if public
		for(int i = 0; i < poScriptedUnit->DefaultInts().Length(); i++)
		{	if(poInstance->Variables()->IntPublic(poScriptedUnit->DefaultInts()[i]))
	  		{	poInstance->Variables()->SetInt(poScriptedUnit->DefaultInts()[i],
  				 				 			poScriptedUnit->DefaultIntsValues()[i]);
			}
		}
	//Loop through default floats, change if public
		for(int i = 0; i < poScriptedUnit->DefaultFloats().Length(); i++)
		{	if(poInstance->Variables()->FloatPublic(poScriptedUnit->DefaultFloats()[i]))
  			{	poInstance->Variables()->SetFloat(poScriptedUnit->DefaultFloats()[i],
			   					   				  poScriptedUnit->DefaultFloatsValues()[i]);
		  	}
		}
}
