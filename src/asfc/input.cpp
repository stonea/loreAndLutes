/*	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
*/


//Associated header
	#include "input.h"

//-------------------------------------------------------- [Construction] -
ASFC_Input::ASFC_Input()
	:
	_repeatKey(KEY_INVALID),
	_repeat(false)
{
}
//------------------------------------------------------- [Key Handeling] -
SDLKey ASFC_Input::GetKey()
{
	//If SDL reported a keydown return that key
		switch (_event.type)
		{
			case SDL_KEYDOWN:
			{
				return _event.key.keysym.sym;
			}break;
		}
	//Otherwise return invalid
		return (SDLKey)KEY_INVALID;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int ASFC_Input::GetKey(int keyDelay, int repeatRate)
{
	//Vars
		int key;
		int tmpKey;
		bool done = false;

	//Reset the timer
		_time.Reset();	
	//Reset temp vars
		key    = KEY_INVALID;
		tmpKey = KEY_INVALID;				
	//Grab a key
		Update();
		tmpKey = GetKey();
	//If a valid key was entered
		if(tmpKey != KEY_INVALID)
		{
			//Remember this key
				key = tmpKey;
			//Insure that the key is still being pressed
				if(!KeyDown((SDLKey)key))
				{	
					//Remove all events from the SDL buffer
	      				SDL_PeepEvents(&_event, 0xFF, SDL_GETEVENT, SDL_EVENTMASK(SDL_KEYDOWN));
            			Update();
            			key = GetKey();
            			_repeatKey = -1;
					//Return that no key was pressed
	      				return(KEY_INVALID);
				}
		}
	//Update the key buffer
		this->Update();

	//Handle key repeats (if repeat mode is on)
		if(_repeat)
		{	
			//If a new key was depressed
				if(key != _repeatKey)
				{
					//Turn repeat mode off
						_repeat = false;
					//Set the newly pressed key to the repeat key.
					//- and - reset the repeat timer
						_repeatKey = key;
						_repeatTime.Reset();
				}
			//Make sure enough time has passed
				while(!_time.Ellapsed(repeatRate) && _repeat)
				{
				}
		}
	//If repeat mode is off
		else
		{
			//See if the repeat key was depressed
				if(key == _repeatKey)
				{	
					//If enough time has passed to allow for a new key
						if(_repeatTime.Ellapsed(keyDelay))
						{
							//Turn repeat mode on
								_repeat = true;
						}
					//If not enough time has ellapsed
						else
						{
							//Set the current key to invalid
								key = KEY_INVALID;
						}
				}
			//If another key was depressed
				else
				{	
					//Set that to the new repeat key, reset the repeat timer
						_repeatKey = key;
						_repeatTime.Reset();
				}
		}
	//Return the depressed key
		Update();
		return(key);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
SDLMod ASFC_Input::GetMod()
{
	//Return any modifier keys being pressed down (alt, ctrl, etc.)
		return SDL_GetModState();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool ASFC_Input::KeyUp(SDLKey key) 
{
	//Vars
		Uint8 *keys;
		
	//Grab a map of the state of the keyboard
		keys = SDL_GetKeyState(NULL);
	//If the key in question is released
		if (keys[key] == SDL_RELEASED)
			return true;
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool ASFC_Input::KeyDown(SDLKey key) 
{
	//Vars
		Uint8 *keys;
	
	//Grab a map of the state of the keyboard
		keys = SDL_GetKeyState(NULL);
	//If the key in question is released
		if (keys[key] == SDL_PRESSED)
			return true;
		return false;
}
//----------------------------------------------------- [Mouse Handeling] -
int ASFC_Input::GetMouseX()
{
	//Vars
		int x;
		
	//Poll SDL for the cursor's X
		SDL_GetMouseState(&x, NULL);
		return x;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int ASFC_Input::GetMouseY()
{
	//Vars
		int y;
	
	//Poll SDL for the cursor's y
		SDL_GetMouseState(NULL, &y);
		return y;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool ASFC_Input::GetMouseButton(int iButton)
{
	//Poll SDL for the mouse button
		return(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(iButton));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Input::Pause()
{	
	//Loop until a key has been pressed
		while(GetKey() == KEY_INVALID)
		{	Update();
		}
}
//------------------------------------------------------------ [Updating] -
void ASFC_Input::Update()
{
	//Grab the next event from SDL
		SDL_PollEvent(&_event);
		SDL_PumpEvents();
}
