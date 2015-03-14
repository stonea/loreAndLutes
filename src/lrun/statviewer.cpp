/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			statviewer.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "statviewer.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LRUN_StatViewer
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LRUN_StatViewer::LRUN_StatViewer()
{	myfScreenLock = false;
	myfDrawCursor = true;
}
//-------------------------------------------------------------------------------------------- [Grab key] -
int LRUN_StatViewer::GrabOption()
{	//We're not done yet, reset
		myfDone = false;

	//Loop until we're done
		while(!myfDone)
		{	Draw();
  			ProcessKey(GrabKey());
		}

	//Return the selected option
		return(myiOption);
}
//P------------------------------------------------------------------------------------------- [Display] -P
void LRUN_StatViewer::Draw()
{	//Vars
		int iStartLine, iEndLine;

	//Clear the console
		mypoPainter->StatsConsole().Clear();
	//Calculate which lines to draw
		if(!myfScreenLock)
		{	iStartLine = myiLine - mypoPainter->StatsConsole().ConsoleHeight()/2;
			iEndLine = myiLine + mypoPainter->StatsConsole().ConsoleHeight()/2;
			
			if(iStartLine < 0)
				iStartLine = 0;
		}
		else
		{	iStartLine = 0;
			iEndLine = mypoPainter->StatsConsole().ConsoleHeight();
		}
	//Draw the next 10 items
		for(int i = iStartLine; i < iEndLine && i < mylEntries.Length(); i++)
		{	//If we have the selected item and we're supposed to draw it
			if(i == myiLine && myfDrawCursor)
			{	//Set font
					mypoPainter->StatsConsole().CurrentFont(1);
					
				//If this is a legal item
	  				if(i >= 0)
			  		{	//Draw this entry
		      				mypoPainter->StatsConsole() << mylEntries[i] << "\n";
	  				}
				//Othewise draw a blank
					else
					{	mypoPainter->StatsConsole() << "\n";
					}
			}
			//If this isn't selected
			else
			{	//Set font
					mypoPainter->StatsConsole().CurrentFont(0);
				
   				//If this is a legal item
	  				if(i >= 0)
			  		{	//Draw this entry
		      				mypoPainter->StatsConsole() << mylEntries[i] << "\n";
	  				}
				//Othewise draw a blank
					else
					{	mypoPainter->StatsConsole() << "\n";
					}
			}
		}
	//Update
		mypoPainter->StatsConsole().Draw(0xFF);
		mypoScreen->Update();
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
SDLKey LRUN_StatViewer::GrabKey()
{	//Reset the timer
  		myoTimer.Reset();

	//Loop until a return is forced (e.g. forever)
		while(1 == 1)
		{	//Update our input info
				myoInput.Update();
			
    		//Decide what to do based on what key is down (if enough time has passed since the last press
    			if(myoTimer.Ellapsed(DELAY))
    			{	//- [If a key is down handle it] -
    					if(myoInput.KeyDown(KEY_PREV))	{myoTimer.Reset(); return(KEY_PREV); }
    					if(myoInput.KeyDown(KEY_NEXT))	{myoTimer.Reset(); return(KEY_NEXT); }
    					if(myoInput.KeyDown(KEY_EXIT))	{myoTimer.Reset(); return(KEY_EXIT); }
    					if(myoInput.KeyDown(KEY_NEXT_SCREEN)){myoTimer.Reset(); return(KEY_NEXT_SCREEN);}
    					if(myoInput.KeyDown(KEY_PREV_SCREEN)){myoTimer.Reset(); return(KEY_PREV_SCREEN);}
    					if(myoInput.KeyDown(KEY_CHOOSE)) {myoTimer.Reset(); return(KEY_CHOOSE);}
    					if(myoInput.KeyDown(KEY_CHOOSE2)){myoTimer.Reset(); return(KEY_CHOOSE);}
				}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LRUN_StatViewer::ProcessKey(SDLKey iKey)
{	//Handle the key
		//- [Exit] -
			if(iKey == KEY_EXIT)
			{	myiOption = OPTION_EXIT;
   				myfDone = true;
			}
		//- [Previous] -
			else if(iKey == KEY_PREV)
			{	if(myiLine > 0)
	   				myiLine--;
			}
		//- [Next] -
			else if(iKey == KEY_NEXT)
			{	if(myiLine + 1 < mylEntries.Length())
	   				myiLine++;
			}
		//- [Previous Screen] -
			else if(iKey == KEY_PREV_SCREEN)
			{	//Wait for the key to be released
					while(myoInput.KeyDown(KEY_PREV_SCREEN)) myoInput.Update();
				//Return
	   				myiOption = OPTION_PREV_SCREEN;
   					myfDone = true;
			}
		//- [Next Screen] -
			else if(iKey == KEY_NEXT_SCREEN)
			{	//Wait for the key to be released
					while(myoInput.KeyDown(KEY_NEXT_SCREEN)) myoInput.Update();
				//Return
	   				myiOption = OPTION_NEXT_SCREEN;
	   				myfDone = true;
			}
		//- [Choose] -
			else if(iKey == KEY_CHOOSE)
			{	//Wait for the key to be released
					while(myoInput.KeyDown(KEY_CHOOSE) || myoInput.KeyDown(KEY_CHOOSE2))
     					myoInput.Update();
   				//Set the option to whatever's selected
					myiOption = myiLine;
					myfDone = true;
			}
}
