/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes

	File:	input.h
	By:		Eoin Coffey
	Desc: 	Interface for the ASFC_Input class. ASFC_Input is responisble for handling input
*/

#ifndef INPUT_H_
#define INPUT_H_

#include <SDL/SDL.h>
#include "timer.h"

enum MOUSEBUTTON
{
	MOUSE_LEFT = 1,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

class ASFC_Input
{
	public:
		ASFC_Input();
		ASFC_Input(bool fSelfUpdate);
	
		void Update();
	
		SDLKey GetKey();
		SDLMod GetMod();
	
		int GetKey(bool fRefreshData, int iKeyDelay, int iRepeatRate);	//AIS**		
	
		bool KeyUp(SDLKey key);
		bool KeyDown(SDLKey key);
	
		int GetMouseX();
		int GetMouseY();
	
		bool GetMouseButton(int iButton);
		
		void Pause(); //AIS** Sits waiting for the user to press a key
	
	private:		
		bool myfSelfUpdate;
		SDL_Event myEvent;
		
		//AIS** (Variables for advanced GetKey() (the one with the most param)
			void SetDefaults();			//Sets variables to their defaults
			
			//vars
				int	   myiInvalidKey;	//Holds the key code for an invalid key
				int	   myiLastKey;		//Holds the last SDL key inputted from advanced GetKey
				int	   myiRepeatKey;	//Holds a key that may be repeated
				bool   myfRepeat;		//True when keys may repeat
				ASFC_Timer myoTime;			//Holds mills passed since the keyboard was open for input
				ASFC_Timer myoRepeatTime;	//Holds the mills passed since the last key was inputted
};

#endif

//end of keyinput.h
	
