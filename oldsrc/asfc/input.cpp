/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes

	File:	input.cpp	
	By: 	Eoin Coffey	
	Desc: 	This is the implementation of the ASFC_Input class.			
*/

//Need the header
#include "input.h"

//Temp !!!
#include <iostream>
using namespace std;

ASFC_Input::ASFC_Input() : myfSelfUpdate(false) {SetDefaults();}				//AIS**
ASFC_Input::ASFC_Input(bool fSelfUpdate) : myfSelfUpdate(true) {SetDefaults();}	//AIS**

SDLKey ASFC_Input::GetKey()
{
	if (myfSelfUpdate)
		this->Update();
	
	switch (myEvent.type)
	{
		case SDL_KEYDOWN: return myEvent.key.keysym.sym; break;
		default: break;
	}
	
	return (SDLKey)myiInvalidKey;
}

SDLMod ASFC_Input::GetMod()
{
	return SDL_GetModState();
}

//AIS**: Get's keyboard input but handles keyboard repeat rates. Gives smoother output.
int ASFC_Input::GetKey(bool fRefreshData, int iKeyDelay, int iRepeatRate)
{	//Vars
		int iKey;		//Holds a key inputted
		int tiKey;		//Holds a temporary inputted key
		bool fDone = false;

	//If we should refresh
		if(fRefreshData)
		{	//Reset vars
				SetDefaults();
		}
	
	//Reset the timer
		myoTime.Reset();
	
	//Reset temp vars
		iKey  = myiInvalidKey;
		tiKey = myiInvalidKey;
				
	//Grab a key, give iRepeatRate time for the user to enter something		
		//while(!oTime.Ellapsed(iRepeatRate))
		//{	//Grab a temp key
				Update();
				tiKey = GetKey();
			//If a valid key was entered
				if(tiKey != myiInvalidKey)
				{	//Set the inputted key to this
						iKey = tiKey;
						
					//If this key isn't actually down enter no key
						if(!KeyDown((SDLKey)iKey))
						{	//while(iKey == tiKey)
      						//{
            					cerr << "ERROR Keyboard lock!\n";
      						
	      						SDL_PeepEvents(&myEvent, 0xFF, SDL_GETEVENT, SDL_EVENTMASK(SDL_KEYDOWN));
            					Update();
            					iKey = GetKey();
            					myiRepeatKey = -1;
            					
            					cerr << "iKey, tiKey " << iKey << " " << tiKey << endl;
      						//}
							
      						return(myiInvalidKey);
						}
				}
				
			//Update the key buffer
				this->Update();
		//}
						
		//Handle key repeats
			//If repeat mode is on
				if(myfRepeat)
				{	//If a new key was depressed
						if(iKey != myiRepeatKey)
						{	//Turn repeat mode off
								myfRepeat = false;
							//Set this to the new repeat key, reset the repeat timer
								myiRepeatKey = iKey;
								myoRepeatTime.Reset();
						}
					//Make sure enough time has passed
						while(!myoTime.Ellapsed(iRepeatRate) && myfRepeat)
						{
						}
				}
			//If repeat mode is off
				else
				{	//See if the repeat key was depressed
						if(iKey == myiRepeatKey)
						{	//Make sure enough time has ellapsed
								//If it has
									if(myoRepeatTime.Ellapsed(iKeyDelay))
									{	//Turn repeat mode on
											myfRepeat = true;
									}
								//If not enough time has ellapsed
									else
									{	//Set the current key to invalid
											iKey = myiInvalidKey;
									}
						}
					//If another key was depressed
						else
						{	//Set that to the new repeat key, reset the repeat timer
								myiRepeatKey = iKey;
								myoRepeatTime.Reset();
						}
				}

	Update();
	return(iKey);
}

void ASFC_Input::Update()
{	SDL_PollEvent(&myEvent);
}

bool ASFC_Input::KeyUp(SDLKey key) 
{
	if (myfSelfUpdate)
		this->Update();
	Uint8 *keys;
	
	keys = SDL_GetKeyState(NULL);
	if (keys[key] == SDL_RELEASED)
		return true;
	return false;
}
bool ASFC_Input::KeyDown(SDLKey key) 
{
	if (myfSelfUpdate)
		this->Update();
	Uint8 *keys;
	
	keys = SDL_GetKeyState(NULL);
	if (keys[key] == SDL_PRESSED)
		return true;
	return false;
}

int ASFC_Input::GetMouseX()
{
	int x;
	
	if (myfSelfUpdate)
		this->Update();
	
	SDL_GetMouseState(&x, NULL);
	
	return x;
}

int ASFC_Input::GetMouseY()
{
	int y;
	
	if (myfSelfUpdate)
		this->Update();
	
	SDL_GetMouseState(NULL, &y);
	
	return y;
}

bool ASFC_Input::GetMouseButton(int iButton)
{
	if (myfSelfUpdate)
		this->Update();
	
	return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(iButton));
}

//AIS** Sits waiting for the user to press a key
void ASFC_Input::Pause()
{	while(this->GetKey() == -1) {this->Update();}
}

//AIS** Sets variables to their defaults
void ASFC_Input::SetDefaults()
{	myiInvalidKey 	= -1;
	myiLastKey	  	= myiInvalidKey;
	myiRepeatKey	= myiInvalidKey;
	myfRepeat		= false;	
}

//end of keyinput.cpp
