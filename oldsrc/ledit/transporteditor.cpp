/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			transporteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "transporteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LEDIT_TransportEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_TransportEditor::LEDIT_TransportEditor()
{
}
//------------------------------------------------------------------------------------------- [Editting] -
void LEDIT_TransportEditor::EditTransport(LL_Transport* poTransport)
{	//Set the transport to edit
		mypoTransport = poTransport;

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
void LEDIT_TransportEditor::Setup()
{	//Vars
		string ts;
	//Clear the old editor
		Reset(false);
	//Draw info
		Heading("                 Transport Editor");
		Heading("===================================================");
	//Stats\Add
		Heading("-------------------------------------------[Image]-");
		Option("Image: " + mypoTransport->ImageFile());
		if(mypoTransport->CustomImage()) Option("Using image from custom set");
		else Option("Using image from default set");
		Option("Edit Image");
		Heading("-----------------------------------[Warp Settings]-");
		Option("Map:    " + mypoGame->MapSet().MapName(mypoTransport->RoomNum()));
		Option("X:      " + Val(mypoTransport->TransportX()));
		Option("Y:      " + Val(mypoTransport->TransportY()));
		Option("Effect: " + Effect(mypoTransport->Effect()));
		Heading("------------------------------------[Transport If]-");
		Option("Player On: " + YesNo(mypoTransport->TransportIfPlayerOn()));
		Option("Talk:      " + YesNo(mypoTransport->TransportIfTalk()));
		Option("Look:      " + YesNo(mypoTransport->TransportIfLook()));
		Option("Push:      " + YesNo(mypoTransport->TransportIfPush()));
		Option("Search:    " + YesNo(mypoTransport->TransportIfSearch()));
		Option("Attack:    " + YesNo(mypoTransport->TransportIfAttack()));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
bool LEDIT_TransportEditor::EditOption(int i)
{	//Decide what to edit based on what was chosen
		switch(i)
		{	case OPTION_IMAGE:
			{	string s;
				if(mypoTransport->CustomImage())
					s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
				else
					s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
		    	
				mypoTransport->LoadAnimation(s, mypoGame->GraphicsDir());
		 		return(true);
			}break;

			case OPTION_CUSTOM_IMAGE:
			{	string s;
				s = mypoTransport->ImageFile();
				mypoTransport->SetCustomImage(!mypoTransport->CustomImage());
				if(!mypoTransport->AnimationExists(mypoGame->GraphicsDir()))
				{	if(mypoTransport->CustomImage())
						s = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
					else
						s = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
				}
				mypoTransport->LoadAnimation(s, mypoGame->GraphicsDir());
				return true;

			}break;
			
			case OPTION_EDIT_IMAGE:
			{	// !!! <CODE>
				return(true);
			}break;
			
			case OPTION_MAP:
			{	int ti = mypoMapSetEdit->GrabMap(&mypoGame->MapSet());
				mypoTransport->SetRoomNum(ti);
				return(true);
			}break;
			
			case OPTION_TRANSPORTX:
			{	int ti = GrabInt("Enter the transport in X position [0-100]", -1, 100);
				mypoTransport->SetTransportX(ti);
				return(true);
			}break;
			
			case OPTION_TRANSPORTY:
			{	int ti = GrabInt("Enter the transport in Y position [0-100]", -1, 100);
				mypoTransport->SetTransportY(ti);
				return(true);
			}break;
			
			case OPTION_EFFECT:
			{	if(mypoTransport->Effect()+1 < BORDER_EFFECT_NONE ||
					   mypoTransport->Effect()+1 >= BORDER_EFFECT_NUMEFFECTS)
				mypoTransport->SetEffect(BORDER_EFFECT_NONE);
				else
					mypoTransport->SetEffect(LL_BORDER_EFFECT(int(mypoTransport->Effect()+1)));
  			return(true);
				return(true);
			}break;
			
			case OPTION_TRANSPORT_IF_PLAYERON:
			{	mypoTransport->SetTransportIfPlayerOn(!mypoTransport->TransportIfPlayerOn());
				return(true);
			}break;

			case OPTION_TRANSPORT_IF_TALK:
			{	mypoTransport->SetTransportIfTalk(!mypoTransport->TransportIfTalk());
				return(true);
			}break;

			case OPTION_TRANSPORT_IF_LOOK:
			{	mypoTransport->SetTransportIfLook(!mypoTransport->TransportIfLook());
				return(true);
			}break;

			case OPTION_TRANSPORT_IF_PUSH:
			{	mypoTransport->SetTransportIfPush(!mypoTransport->TransportIfPush());
				return(true);
			}break;

			case OPTION_TRANSPORT_IF_SEARCH:
			{	mypoTransport->SetTransportIfSearch(!mypoTransport->TransportIfSearch());
				return(true);
			}break;

			case OPTION_TRANSPORT_IF_ATTACK:
			{	mypoTransport->SetTransportIfAttack(!mypoTransport->TransportIfAttack());
				return(true);
			}break;
		}
	return(false);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
string LEDIT_TransportEditor::YesNo(bool f)
{	if(f) return "Yes";
	return "No";
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
string LEDIT_TransportEditor::Effect(LL_BORDER_EFFECT i)
{		 if(i == BORDER_EFFECT_NONE)			return("(0) No effect");
	else if(i == BORDER_EFFECT_FADE)			return("(1) Fade");
	else if(i == BORDER_EFFECT_DISSOLVE)		return("(2) Dissolve");
	else if(i == BORDER_EFFECT_TRIAMBULATE)		return("(3) Triambulate");
	else if(i == BORDER_EFFECT_CHECKERBOARD)	return("(4) Checkerboard");
	else if(i == BORDER_EFFECT_BLEND)			 return("(5) Blend");
	else if(i == BORDER_EFFECT_SPLIT_VERTICLE)	 return("(6) Split verticle");
	else if(i == BORDER_EFFECT_SPLIT_HORIZONTAL) return("(7) Split horizontal");
	else return("Que! Es tonto, porque tu tengo un effecto invalidad!");
}
