/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			scriptedunit.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "scriptedunit.h"	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_ScriptedUnit
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_ScriptedUnit::LL_ScriptedUnit()
{
}
/*
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_ScriptedUnit::LL_ScriptedUnit(LL_ScriptedUnit oCopy)
{	*this = oCopy;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_ScriptedUnit& LL_ScriptedUnit::operator=(LL_ScriptedUnit oCopy)
{	mysClass		= oCopy.Class();
	mysIdentifier	= oCopy.Identifier();
	mypoLOOP		= oCopy.LOOP();
	mypoLibInfo		= oCopy.LibInfo();

	return(*this);
}*/
//------------------------------------------------------------------------------------------- [File I/O] -
//See mapobjects.file_desc for saving descript
void LL_ScriptedUnit::Save(ofstream &oFile)
{	//%X Local%, %Y Local%, %Layer%
		oFile << Val(myiX) << " " << Val(myiY) << " " << Val(myiLayer) << " ";
	//"Image file"
		oFile << myfCustomImage << " ";
		oFile << Qoute(ImageFile()) << " ";
	//"Class (used) Identifier"
		oFile << Qoute(Class()) << " ";
	//"Instance Identifier"
		oFile << Qoute(Identifier()) << " ";
	//%Weight%, %Strength%, %Dex% %Intelligence%
		oFile << Weight() << " " << Strength() << " " << Dexterity()
			  << " " << Intelligence() << " ";
	//%MP%, %Max MP%, %HP%, %Max HP%
		oFile << MP() << " " << MaxMP() << " " << HP() << " " << MaxHP() << " ";
	//%Experience%, %Vehicle (code)%
		oFile << Experience() << " " << Vehicle().Code() << endl;
	//%# of default strings%
		oFile << mylsDefaultStrings.Length() << " ";
	//<Loop for # of default strings>
		for(int i = 0; i < mylsDefaultStrings.Length(); i++)
		{	oFile << Qoute(mylsDefaultStrings[i]) << " ";
			oFile << Qoute(mylsDefaultStringsValues[i]) << endl;
		}
	//%# of default ints%
		oFile << mylsDefaultInts.Length() << " ";
	//<Loop for # of default ints>
		for(int i = 0; i < mylsDefaultInts.Length(); i++)
		{	oFile << Qoute(mylsDefaultInts[i]) << " ";
			oFile << myliDefaultIntsValues[i] << endl;
		}
	//%# of default floats%
		oFile << mylsDefaultFloats.Length() << " ";
	//<Loop for # of default floats>
		for(int i = 0; i < mylsDefaultFloats.Length(); i++)
		{	oFile << Qoute(mylsDefaultFloats[i]) << " ";
			oFile << myldDefaultFloatsValues[i] << endl;
		}
	//<Save Daily Routine>
		oFile << endl;
		myoDailyRoutine.Save(oFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		int 	iX, iY, iLayer;
		string	sImageFile, sClass, sIdentifier;
		int		iWeight, iStrength, iDex, iIntelligence, iMP, iMaxMP, iHP, iMaxHP, iExp, iVehicle;
		int		iNumDefaultStrings, iNumDefaultInts, iNumDefaultFloats;
		string  sVarIdentifier;
		int		ti;
		string	ts;
		double	td;

	//Read info
		//%X Local%, %Y Local% %Layer%
			oFile >> iX >> iY >> iLayer;
		//"Image file"
			oFile >> myfCustomImage;
			sImageFile = ReadString(oFile);
		//"Class (used) Identifier"
			sClass = UpperString(ReadString(oFile));
		//"Instance Identifier"
			sIdentifier = UpperString(ReadString(oFile));
		//%Weight%, %Strength%, %Dex% %Intelligence%
			oFile >> iWeight >> iStrength >> iDex >> iIntelligence;
		//%MP%, %Max MP%, %HP%, %Max HP%
			oFile >> iMP >> iMaxMP >> iHP >> iMaxHP;
		//%Experience%, %Vehicle (code)%
			oFile >> iExp >> iVehicle;
					
		//%# of default strings%
			oFile >> iNumDefaultStrings;
			mylsDefaultStrings.Resize(iNumDefaultStrings);
			mylsDefaultStringsValues.Resize(iNumDefaultStrings);
		//<Loop for # of default strings>
			for(int i = 0; i < mylsDefaultStrings.Length(); i++)
			{	sVarIdentifier = ReadString(oFile);
				ts = ReadString(oFile);
				mylsDefaultStrings[i] 		= sVarIdentifier;
				mylsDefaultStringsValues[i] = ts;
			}
		//%# of default ints%
			oFile >> iNumDefaultInts;
			mylsDefaultInts.Resize(iNumDefaultInts);
			myliDefaultIntsValues.Resize(iNumDefaultInts);
		//<Loop for # of default ints>
			for(int i = 0; i < mylsDefaultInts.Length(); i++)
			{	sVarIdentifier = ReadString(oFile);
				oFile >> ti;
				mylsDefaultInts[i] 		 = sVarIdentifier;
				myliDefaultIntsValues[i] = ti;
			}
		//%# of default floats%
			oFile >> iNumDefaultFloats;
			mylsDefaultFloats.Resize(iNumDefaultFloats);
			myldDefaultFloatsValues.Resize(iNumDefaultFloats);
		//<Loop for # of default floats>
			for(int i = 0; i < mylsDefaultFloats.Length(); i++)
			{	sVarIdentifier = ReadString(oFile);
				oFile >> td;
				mylsDefaultFloats[i]		= sVarIdentifier;
				myldDefaultFloatsValues[i]	= td;
			}
		//<Load Daily Routine>
			myoDailyRoutine.Load(oFile);
			if(myoDailyRoutine.NumInstructions() == 0)
				myfCalling = false;

	//Use this info to set up this scripted unit
		Place(iX, iY, iLayer);
		LoadAnimation(sImageFile, sGraphicsDir);
		SetClass(sClass);
		SetIdentifier(sIdentifier);
		SetWeight(iWeight);
		SetStrength(iStrength);
		SetDexterity(iDex);
		SetIntelligence(iIntelligence);
		SetMP(iMP);
		SetMaxMP(iMaxMP);
		SetHP(iHP);
		SetMaxHP(iMaxHP);
		SetExperience(iExp);
		//!!! TMP
			LL_Vehicle oVehicle;
			oVehicle.SetCode(iVehicle);
		SetVehicle(oVehicle);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::SaveRecordingInfo(ofstream &oFile)
{	//Vars
		LOOP_Instance*   mypoInstance;
		LOOP_Variables*  mypoVars;

	//%X Local%, %Y Local%, %Layer%
		oFile << Val(myiX) << " " << Val(myiY) << " " << Val(myiLayer) << " ";
	//?Null?
		oFile << myfNullify << " ";
	//"Image file"
		oFile << myfCustomImage << " ";
		oFile << Qoute(ImageFile()) << " ";
		oFile << myiCurrentImage << " ";
	//"Class (used) Identifier"
		oFile << Qoute(Class()) << " ";
	//"Instance Identifier"
		oFile << Qoute(Identifier()) << " ";
	//%Weight%, %Strength%, %Dex% %Intelligence%
		oFile << Weight() << " " << Strength() << " " << Dexterity()
			  << " " << Intelligence() << " ";
	//%MP%, %Max MP%, %HP%, %Max HP%
		oFile << MP() << " " << MaxMP() << " " << HP() << " " << MaxHP() << " ";
	//%Experience%, %Vehicle (code)%
		oFile << Experience() << " " << Vehicle().Code() << endl;
	//<Save Daily Routine>
		oFile << endl;
		myoDailyRoutine.Save(oFile);
		oFile << endl;
	//Grab this instance if it exists
		if(mypoLOOP->IsClass(mysClass))
		{	mypoInstance = &mypoLOOP->Instance(Identifier());
			mypoVars = mypoInstance->Variables();
			//Loop through all vars this instance holds
				//Ints
					for(int i = 0; i < mypoVars->NumInts(); i++)
					{	oFile << mypoVars->GetInt(i) << " ";
					}
				//Floats
					for(int i = 0; i < mypoVars->NumFloats(); i++)
					{	oFile << mypoVars->GetFloat(i) << " ";
					}
				//Strings
					for(int i = 0; i < mypoVars->NumStrings(); i++)
					{	oFile << Qoute(mypoVars->GetString(i)) << " ";
					}
			//Save zap information
				oFile << mypoInstance->Zaps().size() << " ";
				for(int i = 0; i < mypoInstance->Zaps().size(); i++)
				{	oFile << Qoute(mypoInstance->Zaps()[i].sLabel) << " ";
					oFile << mypoInstance->Zaps()[i].iTimesZapped << " ";
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_ScriptedUnit::LoadRecordingInfo(ifstream &oFile, string sGraphicsDir)
{	//Vars
		int 	iX, iY, iLayer;
		string	sImageFile, sClass, sIdentifier;
		int		iWeight, iStrength, iDex, iIntelligence, iMP, iMaxMP, iHP, iMaxHP, iExp, iVehicle;
		string  sVarIdentifier;
		int		iCurrentImage;

	//Read info
		//%X Local%, %Y Local% %Layer%
			oFile >> iX >> iY >> iLayer;
		//?Null?
			oFile >> myfNullify;
		//"Image file"
			oFile >> myfCustomImage;
			sImageFile = ReadString(oFile);
			oFile >> iCurrentImage;
		//"Class (used) Identifier"
			sClass = UpperString(ReadString(oFile));
		//"Instance Identifier"
			sIdentifier = UpperString(ReadString(oFile));
		//%Weight%, %Strength%, %Dex% %Intelligence%
			oFile >> iWeight >> iStrength >> iDex >> iIntelligence;
		//%MP%, %Max MP%, %HP%, %Max HP%
			oFile >> iMP >> iMaxMP >> iHP >> iMaxHP;
		//%Experience%, %Vehicle (code)%
			oFile >> iExp >> iVehicle;
		//<Load Daily Routine>
			myoDailyRoutine.Load(oFile);
	
	//Use this info to set up this scripted unit
		Place(iX, iY, iLayer);
		LoadAnimation(sImageFile, sGraphicsDir);
		myiCurrentImage = iCurrentImage;
		SetClass(sClass);
		SetIdentifier(sIdentifier);
		SetWeight(iWeight);
		SetStrength(iStrength);
		SetDexterity(iDex);
		SetIntelligence(iIntelligence);
		SetMP(iMP);
		SetMaxMP(iMaxMP);
		SetHP(iHP);
		SetMaxHP(iMaxHP);
		SetExperience(iExp);
		//!!! TMP
			LL_Vehicle oVehicle;
			oVehicle.SetCode(iVehicle);
		SetVehicle(oVehicle);

	//Done
		return true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_ScriptedUnit::LoadRecordingInfoVars(ifstream &oFile, string sGraphicsDir)
{	//Vars
		LOOP_Instance*   mypoInstance;
		LOOP_Variables*  mypoVars;
		int iVar;
		double dVar;
		string sVar;
		char tc;
		int iNumZaps;
		string sZap;

	//If the class doesn't exist than the vars can't be loaded
		if(!mypoLOOP->IsClass(mysClass))
			return false;
	//Grab this instance
		mypoInstance = &mypoLOOP->Instance(Identifier());
		mypoVars = mypoInstance->Variables();
	//Loop through all vars this instance holds
		//Ints
			for(int i = 0; i < mypoVars->NumInts(); i++)
			{	oFile >> iVar;
			    mypoVars->SetInt(i, iVar);
			    oFile.read(&tc, 1);
			}
		//Floats
			for(int i = 0; i < mypoVars->NumFloats(); i++)
			{	oFile >> dVar;
   				mypoVars->SetFloat(i, dVar);
   				oFile.read(&tc, 1);
			}
		//Strings
			for(int i = 0; i < mypoVars->NumStrings(); i++)
			{	sVar = ReadString(oFile);
   				mypoVars->SetString(i, sVar);
   				oFile.read(&tc, 1);
			}
		//Load zap information
				oFile >> iNumZaps;
    			mypoInstance->Zaps().resize(iNumZaps);
				for(int i = 0; i < mypoInstance->Zaps().size(); i++)
				{	sZap = ReadString(oFile);
					mypoInstance->Zaps()[i].sLabel = sZap;
					oFile >> mypoInstance->Zaps()[i].iTimesZapped;
				}
	//return
		return true;
}
//----------------------------------------------------------------------------------------- [Callbacks] -
void LL_ScriptedUnit::Run()
{	//Vars
		bool fHardBreak = false;
		LOOP_Instance* mypoInstance;
	//If this unit is nullified don't run
		if(myfNullify)
			return;
	//Update AI
		UpdateRoutineAI();
		UpdateAI();
	//Grab this instance
		mypoInstance = &mypoLOOP->Instance(Identifier());
	//If this unit is stopped just hang and do nada
 		if(mypoInstance->NumOffsets() <= 0)
   			return;
	//Set the lib
		ReadyForLOOP();
	//Run while the turn hasn't ended
		while(!mypoLibInfo->TurnEnded() && mypoInstance->NumOffsets() > 0
              && !fHardBreak && LOOP()->LegalOffset(mypoInstance->CurrentOffset()))
		{	//Run
	  			mypoLOOP->RunInstance(Identifier());
			//Check for a hard break (Pressing cntrl + break or cntrl + c)
				myoInput.Update();
				if(	(myoInput.KeyDown(SDLK_LCTRL) && myoInput.KeyDown(SDLK_c))		||
					(myoInput.KeyDown(SDLK_RCTRL) && myoInput.KeyDown(SDLK_c))		||
					(myoInput.KeyDown(SDLK_LCTRL) && myoInput.KeyDown(SDLK_PAUSE))	||
					(myoInput.KeyDown(SDLK_RCTRL) && myoInput.KeyDown(SDLK_PAUSE)))
				{
					cerr << "Scripted unit was hard breaked as specified by user\n";
					mypoLOOP->ClearInstanceOffsets(mypoLOOP->Instance(Identifier()).Identifier());
					fHardBreak = true;
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Talk()
{	//Gosub "talk"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_TALK);
	//Now run
		Run();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Look()
{	//Set the lib
		ReadyForLOOP();
	//Gosub "look"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_LOOK);
	//Now run
		Run();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_ScriptedUnit::Push()
{	//Gosub "push"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_PUSH);
	//Now run
		Run();
	//Don't have the engine intercept the push event
		return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Search()
{	//Gosub "search"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_SEARCH);
	//Now run
		Run();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Attack()
{	//Gosub "attack"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_ATTACK);
	//Now run
		Run();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Init()
{	//Gosub "init"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_INIT);
	//Now run
		Run();

}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Gosub(string sLabel)
{	//Gosub sLabel
		mypoLOOP->GosubInstance(Identifier(), sLabel);
	//Now run
		Run();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::Seen()
{	//Gosub "seen"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_SEEN);
	//Now run
		Run();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::PlayerOn()
{	//Gosub "seen"
		mypoLOOP->GosubInstance(Identifier(), LL_ScriptedUnit__LABEL_PLAYERON);
	//Now run
		Run();
}
//-------------------------------------------------------------------------------- [LOOP Script Linking] -
//MEMVAR_SETGET(SetClass,		 Class,			string, mysClass);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetIdentifier, Identifier,	string, mysIdentifier);
//-------------------------------------------------------------------- [Default Variable Adding\Setting] -
void LL_ScriptedUnit::SetDefaultString(string sIdentifier, string sValue)
{	//Check to see if this variable is already registered, if so replace its value
		for(int i = 0; i < mylsDefaultStrings.Length(); i++)
		{	if(UpperString(mylsDefaultStrings[i]) == UpperString(sIdentifier))
			{	mylsDefaultStringsValues[i] = sValue;
				return;
			}
		}

	//Else (if not already registered) register it anew
		mylsDefaultStrings.Push(sIdentifier);
		mylsDefaultStringsValues.Push(sValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::SetDefaultInt(string sIdentifier, int	iValue)
{	//Check to see if this variable is already registered, if so replace its value
		for(int i = 0; i < mylsDefaultInts.Length(); i++)
		{	if(UpperString(mylsDefaultInts[i]) == UpperString(sIdentifier))
			{	myliDefaultIntsValues[i] = iValue;
				return;
			}
		}

	//Else (if not already registered) register it anew
		mylsDefaultInts.Push(sIdentifier);
		myliDefaultIntsValues.Push(iValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_ScriptedUnit::SetDefaultFloat(string sIdentifier, double dValue)
{	//Check to see if this variable is already registered, if so replace its value
		for(int i = 0; i < mylsDefaultFloats.Length(); i++)
		{	if(UpperString(mylsDefaultFloats[i]) == UpperString(sIdentifier))
			{	myldDefaultFloatsValues[i] = dValue;
				return;
			}
		}

	//Else (if not already registered) register it anew
		mylsDefaultFloats.Push(sIdentifier);
		myldDefaultFloatsValues.Push(dValue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_ScriptedUnit::DefaultString(string sIdentifier)
{	//Loop through all default strings, return value if sIdentifierfound
		for(int i = 0; i < mylsDefaultStrings.Length(); i++)
		{	if(UpperString(mylsDefaultStrings[i]) == UpperString(sIdentifier))
			{	return mylsDefaultStringsValues[i];
			}
		}

	//Default
		return("\n");
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_ScriptedUnit::DefaultInt(string sIdentifier)
{	//Loop through all default ints, return value if sIdentifierfound
		for(int i = 0; i < mylsDefaultInts.Length(); i++)
		{	if(UpperString(mylsDefaultInts[i]) == UpperString(sIdentifier))
			{	return myliDefaultIntsValues[i];
			}
		}

	//Default
		return(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
double LL_ScriptedUnit::DefaultFloat(string sIdentifier)
{	//Loop through all default floats, return value if sIdentifierfound
		for(int i = 0; i < mylsDefaultFloats.Length(); i++)
		{	if(UpperString(mylsDefaultFloats[i]) == UpperString(sIdentifier))
			{	return myldDefaultFloatsValues[i];
			}
		}

	//Default
		return(0);
}
//------------------------------------------------------------------------------------------------ [Ops] -
LL_ScriptedUnit& LL_ScriptedUnit::operator=(LL_ScriptedUnit oRHS)
{	
}
//P------------------------------------------------------------------------------ [LOOP Script Linking] -P
void LL_ScriptedUnit::ReadyForLOOP()
{	mypoLibInfo->SetIdentifier(Identifier());
	mypoLibInfo->SetX(X());
	mypoLibInfo->SetY(Y());
	mypoLibInfo->SetSeg(Seg());
	mypoLibInfo->SetOff(Off());
	mypoLibInfo->SetTurnEnded(false);
	mypoLibInfo->SetTalking(false);
}
//P----------------------------------------------------------------------------------------- [Route AI] -P
void LL_ScriptedUnit::UpdateRoutineAI()
{	//Exit if this unit doesn't have a routine
		if(myoDailyRoutine.NumInstructions() == 0)
			return;

	//If we need to update the routine
		if(myoDailyRoutine.Update(mypoClock))
		{	//If the current instruction is do nothing remove all calls and randoms and quit
				if(myoDailyRoutine.CurrentInstructionNum() == LL_DailyRoutine::NO_INSTRUCTION)
				{	myfCalling = false;
					myfRandom  = false;
					return;
				}

   			//Vars
				LL_DailyRoutine::LL_DailyRoutineInstruction oInstruction;
				LL_Area oArea;
				int iArea;

   			//Grab the current instruction
				oInstruction = myoDailyRoutine.GetCurrentInstruction();
				
			//If its a move to call that location
				if(oInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_MOVE)
				{	Call(oInstruction.myiXParam, oInstruction.myiYParam);
				}

			//If its a random region call that location and define the random region
				if(oInstruction.myiCommand == LL_DailyRoutine::LL_DAILY_ROUTINE_COMMAND_FIELD)
				{	Call(oInstruction.myiXParam, oInstruction.myiYParam);
				    iArea = PathNodes()->AreaOn(oInstruction.myiXParam, oInstruction.myiYParam);

				    if(iArea != LL_PathNodes::NO_AREA)
				    {	oArea = PathNodes()->Area(iArea);
						RandomArea(oArea.iX, oArea.iY, oArea.iWidth, oArea.iHeight);
					}

				}
		}
}
