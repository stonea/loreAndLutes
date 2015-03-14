/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			scripteditemeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "scripteditemeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_ScriptedItemEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_ScriptedItemEditor::LEDIT_ScriptedItemEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_ScriptedItemEditor::EditScriptedItem(LL_ScriptedItem* poScriptedItem)
{	//Set the ScriptedItem to edit
		mypoScriptedItem = poScriptedItem;

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
void LEDIT_ScriptedItemEditor::Setup()
{	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("               Scripted Item Information");
		Heading("===================================================");
	//Stats
		Option("Image: " + mypoScriptedItem->ImageFile());
		if(mypoScriptedItem->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image");
		Option("Description: " + mypoScriptedItem->Identifier());
		Option("Weight: " + Val(mypoScriptedItem->Weight()));
  		Option("Call: "   + mypoScriptedItem->Call());
		Option("Message: " + Message(mypoScriptedItem->Message()));
		if(mypoScriptedItem->Message() == LL_ScriptedItem::MESSAGE_PING_CLASS ||
		   mypoScriptedItem->Message() == LL_ScriptedItem::MESSAGE_PING_CLASS_DERIV)
		{
			Option("Class: " + mypoScriptedItem->MessageClass());
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_ScriptedItemEditor::EditOption(int i)
{	//Decide what to edit based on what was chosen
		switch(i)
		{	case OPTION_IMAGE:
			{	string s;
				if(mypoScriptedItem->CustomImage())
					s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
				else
					s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
    	
				mypoScriptedItem->LoadAnimation(s, mypoGame->GraphicsDir());
		 		return(true);
			}break;

			case OPTION_CUSTOM_IMAGE:
			{	string s;
				s = mypoScriptedItem->ImageFile();
				mypoScriptedItem->SetCustomImage(!mypoScriptedItem->CustomImage());
				if(!mypoScriptedItem->AnimationExists(mypoGame->GraphicsDir()))
				{	if(mypoScriptedItem->CustomImage())
						s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
					else
						s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
				}
				mypoScriptedItem->LoadAnimation(s, mypoGame->GraphicsDir());
			
			}break;
			
			case OPTION_EDIT_IMAGE:
			{	// !!! <CODE>
				return(true);
			}break;
			
  			case OPTION_DESCRIPTION:
			{	string s = GrabString("Enter the new description");
				mypoScriptedItem->SetIdentifier(s);
		 		return(true);
			}break;
			
			case OPTION_WEIGHT:
			{	int i = GrabInt("Enter the new weight value [0-255]", 0, 255);
				mypoScriptedItem->SetWeight(i);
		 		return(true);
			}break;
			
			case OPTION_CALL:
			{	string s = GrabString("Enter the new call");
				mypoScriptedItem->SetCall(s);
		 		return(true);
			}break;

			case OPTION_MESSAGE:
			{	mypoScriptedItem->SetMessage
				(	LL_ScriptedItem::LL_ScriptedItemMessage(mypoScriptedItem->Message() + 1)
				);
				if(mypoScriptedItem->Message() >= LL_ScriptedItem::MESSAGE_NUM_MESSAGES)
				{	mypoScriptedItem->SetMessage(LL_ScriptedItem::LL_ScriptedItemMessage(0));
				}
				return(true);
			}break;

			case OPTION_MESSAGE_CLASS:
			{	string sClass;
				if(mypoPainter->PromptKey(SDLK_g, SDLK_l,
  								  "What class set holds the class?",
	          				   	  "(G) Global", "(L) Local", FONT_HIGHLIGHT))
				{	mypoPainter->Draw();
					sClass = mypoClassSetEditor->GrabClass(mypoGame, &mypoGame->GlobalClassSet());
				}
				else
				{	mypoPainter->Draw();
					sClass = mypoClassSetEditor->GrabClass(mypoGame, &mypoGame->ClassSet());
				}
				mypoScriptedItem->SetMessageClass(sClass);
				return(true);
			}break;

			default: break;
		}

	return(false);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
string LEDIT_ScriptedItemEditor::Message(LL_ScriptedItem::LL_ScriptedItemMessage iMessage)
{	switch(iMessage)
	{	case LL_ScriptedItem::MESSAGE_GLOBAL:		return("Gosub global"); break;
		case LL_ScriptedItem::MESSAGE_PING:			return("Ping"); break;
		case LL_ScriptedItem::MESSAGE_PING_CLASS:	return("Ping class"); break;
		case LL_ScriptedItem::MESSAGE_PING_CLASS_DERIV:	return("Ping class & its derivatives"); break;
		default: return("ERR INVALID MESSAGE"); break;
	}
}
