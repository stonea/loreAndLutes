/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			classseteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "classseteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_ClassSetEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ClassSetEditor::LEDIT_ClassSetEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_ClassSetEditor::EditClassSet(LL_Game* poGame, LL_ClassSet* poSet, string sClassFile,
										string sClassSetFile)
{	//Map params
		mypoGame 	 = poGame;
		mypoClassSet = poSet;
		mysClassFile = sClassFile;
		mysClassSetFile = sClassSetFile;

	//Set up the keys
		int iKey;
		ASFC_LinkedList<int> lChoosers;
  		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
		lChoosers.Push(KEY_DELETE);
		lChoosers.Push(KEY_CANCEL);

	//Set up the text editor
		myoTextEditor.SetConsole(&mypoPainter->MainConsole());

	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup(true);

	//Now grab an option
		bool fNotDone = true;
		while(fNotDone)
		{	Setup(true);
			DrawQuickKeys();
			int iOption = GrabOption(&iKey, lChoosers);
			fNotDone = EditOption(iOption, iKey);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LEDIT_ClassSetEditor::GrabClass(LL_Game* poGame, LL_ClassSet* poSet)
{	//Vars
		int iOption;

	//Map params
		mypoGame 	 = poGame;
		mypoClassSet = poSet;

	//Set up the text editor
		myoTextEditor.SetConsole(&mypoPainter->MainConsole());

	//Setup the editor
		DrawInit();
		DrawQuickKeys();
		Setup(false);

	//Now grab an option
		iOption = GrabOption();
					
		//If we had an invalid option return "" 
			if(iOption == CONSOLEEDIT_NONE || iOption >= mypoClassSet->NumClassEntry())
				return "";
		//Else
			return(mypoClassSet->ClassEntry(iOption).mysDescription);
}
//P------------------------------------------------------------------------------------------ [Editting] -P
void LEDIT_ClassSetEditor::Setup(bool fNewOption)
{	//Clear the old editor
		Reset(false);
     	
	//Draw the header
		Heading("                     Class Set");
		Heading("===================================================");
	//Draw the choices
		//All the classes
			for(int i = 0; i < mypoClassSet->NumClassEntry(); i++)
			{	Option(mypoClassSet->ClassEntry(i).mysDescription);
			}
		//The "New Class" button if needed, else draw the "<other class set> button"
			if(fNewOption)
				Option("-- [New Class] --");
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LEDIT_ClassSetEditor::EditOption(int iOpt, int iKey)
{	//Vars
		bool fOkay;

	//If the key down is exit escape!!
		if(iKey == KEY_CANCEL)
		{	return false;
		}
	//If the key down is "choose"
		else if(iKey == KEY_CHOOSE || iKey == KEY_CHOOSE2)
		{	//If we just chose a class
				if(iOpt >= 0 && iOpt < mypoClassSet->NumClassEntry())
				{	//Load up the text
						myoText.Load(mysClassFile);
					//Edit it
						DrawQuickKeysForClassEdit();
						EditText(iOpt);
					//Save it
						myoText.Save();
					//Update boundries
						HandleBoundries();
					//Check for errors
						CheckForErrors(iOpt);
					//ReLoad classes
						mypoGame->SaveClassSet(mysClassSetFile, mypoClassSet);
						mypoGame->LoadClasses("", mypoScreen);
						mypoLOOPLibLinker->Link(mypoGame, mypoLOOPLib);
			
					//Keep on editting
						return true;
				}
			//If we need to create a new class
				else if(iOpt == mypoClassSet->NumClassEntry())
				{	//Create this new class
					  	NewClass();
					//Load up the text
					  	myoText.Load(mysClassFile);
		 			//Insert a starting space
						//Edit it
							DrawQuickKeysForClassEdit();
							EditText(iOpt);
						//Save it
							myoText.Save();
						//Update boundries
							HandleBoundries();
							
						//Check for errors
							CheckForErrors(iOpt);
							
						//ReLoad classes
							mypoGame->SaveClassSet(mysClassSetFile, mypoClassSet);
							mypoGame->LoadClasses("", mypoScreen);
							mypoLOOPLibLinker->Link(mypoGame, mypoLOOPLib);

					//Keep on editting
						return true;
				}
		}
	//If the key down is "delete"
		else if(iKey == KEY_DELETE)
		{	//If we gotch a legal class
				if(iOpt >= 0 && iOpt < mypoClassSet->NumClassEntry())
				{	//Set Okay "continue" true on default
						fOkay = true;
    				//If any objects use this class ask if its okay to delete
						if(mypoMapObjectRemover->AnyInstancesUseClass(
							mypoClassSet->ClassEntry(iOpt).mysDescription))
						{	
							fOkay = mypoPainter->PromptYN("Objects existing on this map use this class.",
													"Deleting the class will also delete these objects.",
    												"Continue? (Y/N)", 1);
    												
							//Delete any objects that use this class if okay
								if(fOkay)
								{	mypoMapObjectRemover->DeleteInstancesUsingClass(
    	    							mypoClassSet->ClassEntry(iOpt).mysDescription);

									//And saveapleiua the units set
										mypoGame->SaveUnitSet(mypoGame->UnitSetFileName());
								}
						}
					//If the user still wishes to delete
						if(fOkay)
						{	//Delete it out of the file	
								//Load up the text
									myoText.Load(mysClassFile);
  								//Delete it out
  									for(int i = mypoClassSet->ClassEntry(iOpt).myiStart;
         								i < mypoClassSet->ClassEntry(iOpt).myiEnd+1; i++)
		 							{	
										if(myoText.NumRows() > 1)
											myoText.DeleteRow(mypoClassSet->ClassEntry(iOpt).myiStart);
									}
		          					//Save it
										myoText.Save();
    
    						//Delete it out of the records
								mypoClassSet->RemoveClassEntry(iOpt);
							//Check boundries
								HandleBoundries();					
						}
					//If there's no more classes clear the file out
						if(mypoClassSet->NumClassEntry() == 0)
						{	myoText.Load(mysClassFile);
    						myoText.Clear();
							myoText.Save();
						}
						
					//ReLoad classes
						mypoGame->SaveClassSet(mysClassSetFile, mypoClassSet);
						mypoGame->LoadClasses("", mypoScreen);
						mypoLOOPLibLinker->Link(mypoGame, mypoLOOPLib);
				}
				//Keep on edittin'
					return true;
		}

	return false;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ClassSetEditor::HandleBoundries()
{	//If we have a first class
		if(mypoClassSet->NumClassEntry())
		{	//Make sure the start is line #0, if not move it there
				if(mypoClassSet->ClassEntry(0).myiStart != 0)
					mypoClassSet->ClassEntry(0).myiStart = 0;
		}

	//Loop through all the classes in the list (except the first)
		for(int i = 1; i < mypoClassSet->NumClassEntry(); i++)
		{	//If this entry doesn't immediatly following the previous one set it to
				if(mypoClassSet->ClassEntry(i).myiStart != mypoClassSet->ClassEntry(i-1).myiEnd + 1)
					MoveEntryTo(i, mypoClassSet->ClassEntry(i-1).myiEnd + 1);
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ClassSetEditor::MoveEntryTo(int iEntryNum, int iFirstLine)
{	//Vars
		int iLength;

	//Calculate the length of this entry
		iLength = 	mypoClassSet->ClassEntry(iEntryNum).myiEnd -
					mypoClassSet->ClassEntry(iEntryNum).myiStart;

	//Move the entry
		mypoClassSet->ClassEntry(iEntryNum).myiStart = iFirstLine;
		mypoClassSet->ClassEntry(iEntryNum).myiEnd   = iFirstLine + iLength;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_ClassSetEditor::NewClass()
{	//Vars
		string sName;
		int	   iNewClassLocal;
	
	//Clear the console
		mypoPainter->MainConsole().Clear();
	//Draw the header
		mypoPainter->MainConsole().CurrentFont(FONT_HEADING);
		mypoPainter->MainConsole() << "                     New Class\n";
		mypoPainter->MainConsole() << "===================================================\n";
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "Answer the following questions in order to create a\n";
		mypoPainter->MainConsole() << "template for this new class:\n\n";
		
	//Ask for a class name
		mypoPainter->MainConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->MainConsole() << "\n";
		mypoPainter->MainConsole() << "What would you like the class name (identifier) to be?\n";
		mypoPainter->MainConsole().CurrentFont(FONT_HIGHLIGHT);
		mypoPainter->MainConsole() >> sName;
		
	//Now create this class!
 		//If this isn't the first class
			if(mypoClassSet->NumClassEntry() > 0)
			{	//Create the class give it rights to space immediatly after the previous class
					LL_ClassSetEntry oAdd;
					int iLastClass = mypoClassSet->NumClassEntry() - 1;
					oAdd.mysDescription = sName;
					oAdd.myiStart		= mypoClassSet->ClassEntry(iLastClass).myiEnd+1;
					oAdd.myiEnd			= mypoClassSet->ClassEntry(iLastClass).myiEnd+1;
					mypoClassSet->AddClassEntry(oAdd);
			}
		//If it is (the first class)
			else
			{	LL_ClassSetEntry oAdd;
				oAdd.mysDescription = sName;
					oAdd.myiStart		= 0;
					oAdd.myiEnd			= 0;
				mypoClassSet->AddClassEntry(oAdd);
			}
			
	//Add in the template to this class
		//Figure out the # of classes in this set
			int iNumClasses = mypoClassSet->NumClassEntry();
		//Set the templates C tag to represent the class name
			myoTemplateReader.SetTag(CLASS_TAG, sName);
		//Load it
	  		myoText.Load(mysClassFile);
		//Template it
			myoTemplateReader.ReadTemplate(LEDIT_ClassSetEditor__CLASS_TEMPLATE, &myoText,
   										   &mypoClassSet->ClassEntry(iNumClasses-1).myiStart,
										   &mypoClassSet->ClassEntry(iNumClasses-1).myiEnd);
		//Save it
			myoText.Save();
			
		//Update boundries
			HandleBoundries();
			
	//Save the class set
		mypoGame->SaveClassSet(mysClassSetFile, mypoClassSet);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ClassSetEditor::DrawQuickKeys()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
	mypoPainter->TalkConsole() << "Up:     Move up\n";
	mypoPainter->TalkConsole() << "Down:   Move down\n";
	mypoPainter->TalkConsole() << "Enter:  Edit Class\n";
	mypoPainter->TalkConsole() << "E:      Class Options\n";
	mypoPainter->TalkConsole() << "Delete: Delete Class\n";
	mypoPainter->TalkConsole() << "Escape: Exit\n";
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ClassSetEditor::DrawQuickKeysForClassEdit()
{	mypoPainter->TalkConsole().Clear();
	mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
	mypoPainter->TalkConsole() << "Arrows:      Move\n";
	mypoPainter->TalkConsole() << "#s and ABCs: Type\n";
	mypoPainter->TalkConsole() << "Cntrl + Y:   Delete Line";
	mypoPainter->TalkConsole() << "Delete:      Delete\n";
	mypoPainter->TalkConsole() << "Backspace:   Backspace\n";
	mypoPainter->TalkConsole() << "Escape:      Exit\n";
	mypoPainter->TalkConsole().Draw(0xFF);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ClassSetEditor::CheckForErrors(int iClass)
{	//Debug
		int iLine = 0;
		int	iErr  = 0;
		string sErr = "";
		int	iCharStart;
		mypoGame->LOOP().Reader().Debug(0, mysClassFile,
  										mypoClassSet->ClassEntry(iClass).myiStart, &sErr, &iErr,
            							mypoClassSet->ClassEntry(iClass).mysDescription);
  										
	//While we have errors
		while(sErr != "")
		{	//Output in talk console	
				mypoPainter->TalkConsole().Clear();
				mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
				mypoPainter->TalkConsole() << "ERRORS\n";
				mypoPainter->TalkConsole() << "----------\n";
				mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
				mypoPainter->TalkConsole() << "Char: " << iErr << "\n";
				mypoPainter->TalkConsole() << "Err:  " << sErr << "\n";
				mypoPainter->TalkConsole().Draw(0xFF);
				
			//ReEdit the text
				//Determine which character starts the text we're interested in
					iLine =  myoText.LineAtChar(iErr);
				//Load up the text
					myoText.Load(mysClassFile);
				//Edit it
					EditText(iClass, iLine);
				//Save it
					myoText.Save();
				//Update boundries
					HandleBoundries();
					
			//Recheck for errors
				iErr = 0;
				sErr = "";
				mypoGame->LOOP().Reader().Debug(0, mysClassFile,
  												mypoClassSet->ClassEntry(iClass).myiStart, &sErr, &iErr,
              									mypoClassSet->ClassEntry(iClass).mysDescription);
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
void LEDIT_ClassSetEditor::EditText(int iClass, int iLine = -1)
{	//Vars (set the end to clip out the last line (the carrot))
		int tiStart = mypoClassSet->ClassEntry(iClass).myiStart;
		int tiEnd   = mypoClassSet->ClassEntry(iClass).myiEnd - 2;

	//Edit text
		if(iLine == -1)
			myoTextEditor.EditText(&myoText, &tiStart, &tiEnd);
		else
			myoTextEditor.EditText(&myoText, &tiStart, &tiEnd, iLine);
						   
 	//Reset the start and end
 		mypoClassSet->ClassEntry(iClass).myiStart	= tiStart;
		mypoClassSet->ClassEntry(iClass).myiEnd		= tiEnd + 2;
}
