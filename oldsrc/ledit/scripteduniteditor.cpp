/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			scripteduniteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "scripteduniteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LEDIT_ScriptedUnitEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ScriptedUnitEditor::LEDIT_ScriptedUnitEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_ScriptedUnitEditor::EditScriptedUnit(LL_ScriptedUnit* poUnit, LL_Game* poGame)
{	//Set up more various pointas' and consoles
		myoTextEditor.SetConsole(&mypoPainter->MainConsole());
		mypoScriptedUnit   = poUnit;
		mypoGame		   = poGame;

	//Make sure the class exists if it doesn't quit out
		if(!mypoGame->LOOP().IsClass(poUnit->Class()))
		{	mypoPainter->DisplayMessage("Error in scripted unit:",
										"Instance derives from class that does not exist.",
										"Please delete this unit.", 0);
			//Pause
				myoInput.Update();
				myoInput.Pause();
				while(myoInput.GetKey() != -1) {myoInput.Update();}
				myoInput.Update();
			return;
		}

	//Set up more various pointas' and consoles
		mypoClass		   = &mypoGame->LOOP().Class(poUnit->Class());
		mypoClassSet	   = &mypoGame->ClassSet();
		myiLocalInClassSet = mypoGame->ClassSet().FindClassEntry(mypoClass->Identifier());

	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup();

	//Now grab an option
		while(EditOption(GrabOption()))
		{	Setup();
		}
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_ScriptedUnitEditor::Setup()
{	//Vars
		ASFC_LinkedList<string> lsVarIdentifiers;

	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("             Scripted Unit Information");
		Heading("===================================================");
		Heading("------------------------------ [General Settings] -");
		Heading("Class:      " + mypoScriptedUnit->Class());
		Option("Identifier: " + mypoScriptedUnit->Identifier());
		Option("Image:      " + mypoScriptedUnit->ImageFile());
		if(mypoScriptedUnit->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image (In GIMP)");
		Option("<Edit Daily Route>");
		//Ints
			Heading("------------------------------------------ [Ints] -");
			lsVarIdentifiers = mypoClass->GetVariables()->PublicInts();
			for(int i = 0; i < lsVarIdentifiers.Length(); i++)
			{	Option(lsVarIdentifiers[i]);
			}
		//Floats
			Heading("---------------------------------------- [Floats] -");
			lsVarIdentifiers = mypoClass->GetVariables()->PublicFloats();
			for(int i = 0; i < lsVarIdentifiers.Length(); i++)
			{	Option(lsVarIdentifiers[i]);
			}
		//Strings
			Heading("--------------------------------------- [Strings] -");
			lsVarIdentifiers = mypoClass->GetVariables()->PublicStrings();
			for(int i = 0; i < lsVarIdentifiers.Length(); i++)
			{	Option(lsVarIdentifiers[i]);
			}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_ScriptedUnitEditor::EditOption(int iOpt)
{	//Vars
		ASFC_LinkedList<string> lsVarIdentifiers;
		string ts;
		int	   ti;
		double td;
		int	   iOptCount;

	//If the user wants out let him out!
		if(iOpt == CONSOLEEDIT_NONE)
		{	return false;
		}
			
	//Edit Identifier
		else if(iOpt == LEDIT_SCRIPT_EDIT_OPTION_IDENTIFIER)
		{	EditIdentifier();
			return true;
		}
	//Edit Image (File)
		else if(iOpt == LEDIT_SCRIPT_EDIT_OPTION_IMAGE)
		{	string s;
			if(mypoScriptedUnit->CustomImage())
				s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
			else
				s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
			mypoScriptedUnit->LoadAnimation(s, mypoGame->GraphicsDir());
  			return true;
		}
	//Switch graphics set
		else if(iOpt == LEDIT_SCRIPT_EDIT_OPTION_CUSTOM_IMAGE)
		{	string s;
			s = mypoScriptedUnit->ImageFile();
			mypoScriptedUnit->SetCustomImage(!mypoScriptedUnit->CustomImage());
			if(!mypoScriptedUnit->AnimationExists(mypoGame->GraphicsDir()))
			{	if(mypoScriptedUnit->CustomImage())
					s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
				else
					s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
			}
			mypoScriptedUnit->LoadAnimation(s, mypoGame->GraphicsDir());

			return true;
		}
	//Edit Image
		else if(iOpt == LEDIT_SCRIPT_EDIT_OPTION_EDIT_IMAGE)
		{	// !!! TMP
			
  			return true;
		}
	//Edit Route
		else if(iOpt ==	LEDIT_SCRIPT_EDIT_OPTION_EDIT_ROUTE)
		{	mypoDailyRoutineEditor->EditDailyRoutine(&mypoScriptedUnit->DailyRoutine());
			
			return true;
		}

	//If the option we have is a public var
		else if(iOpt >= LEDIT_SCRIPT_EDIT_OPTION_VAR)
		{	//Set iCount to the starting var
				iOptCount = LEDIT_SCRIPT_EDIT_OPTION_VAR;
				
  			//Determine if it's an int
	  			lsVarIdentifiers = mypoClass->GetVariables()->PublicInts();
				for(int i = 0; i < lsVarIdentifiers.Length(); i++)
				{	if(iOpt == iOptCount)
					{	PromptForVar(lsVarIdentifiers[i], mypoScriptedUnit->DefaultInt(lsVarIdentifiers[i]));
	    				mypoPainter->MainConsole() >> ti;
    					mypoScriptedUnit->SetDefaultInt(lsVarIdentifiers[i], ti);
					}
					iOptCount++;
				}
			//Floats
				lsVarIdentifiers = mypoClass->GetVariables()->PublicFloats();
				for(int i = 0; i < lsVarIdentifiers.Length(); i++)
				{	if(iOpt == iOptCount)
					{	PromptForVar(lsVarIdentifiers[i], mypoScriptedUnit->DefaultFloat(lsVarIdentifiers[i]));
	    				mypoPainter->MainConsole() >> td;
    					mypoScriptedUnit->SetDefaultFloat(lsVarIdentifiers[i], td);
    				}
					iOptCount++;
				}
			//Strings
				lsVarIdentifiers = mypoClass->GetVariables()->PublicStrings();
				for(int i = 0; i < lsVarIdentifiers.Length(); i++)
				{	if(iOpt == iOptCount)
					{	myoText.Clear();
						myoText.ReadString(mypoScriptedUnit->DefaultString(lsVarIdentifiers[i]), true);
     					myoTextEditor.EditText(&myoText);
						myoText.String(&ts);
						if(ts != "")
							mypoScriptedUnit->SetDefaultString(lsVarIdentifiers[i], ts);
					}
					iOptCount++;
				}
				
			return true;
		}

	return false;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ScriptedUnitEditor::PromptForVar(string sIdentifier, double dValue)
{	mypoPainter->MainConsole().Clear();
	mypoPainter->MainConsole() << "Enter the new default value for: " << sIdentifier << "\n";
	mypoPainter->MainConsole() << "Previous value: " << dValue << "\n";
	mypoPainter->MainConsole() << ">";
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ScriptedUnitEditor::EditIdentifier()
{	//Vars
		string sIdentifier = "";

	//Grab an identifier
		sIdentifier = GrabString("Enter the new identifier");

	//Make sure sIdentifier is valid (e.g. not used!) unless used by self
	    while(mypoGame->UnitSet().IsScriptedUnit(sIdentifier) &&
     		  UpperString(sIdentifier) != UpperString(mypoScriptedUnit->Identifier()))
		{	
  			mypoPainter->MainConsole().CurrentFont(0);
    		mypoPainter->MainConsole() << "\nIdentifier already taken, enter another:\n";
			mypoPainter->MainConsole().CurrentFont(2);
			mypoPainter->MainConsole() << ">";
			mypoPainter->MainConsole().CurrentFont(1);
	    	mypoPainter->MainConsole() >> sIdentifier;	
		}

	//If the user didn't enter an identifier keep the old one
		if(sIdentifier == "")
			sIdentifier = mypoScriptedUnit->Identifier();
			
	//Set the identifier
		mypoScriptedUnit->SetIdentifier(sIdentifier);
}
