#ifndef INPUT_H_
#define INPUT_H_

//Dependencies
	#include <SDL/SDL.h>
//Aggregates
	#include "timer.h"

class ASFC_Input
{
	public:
	//Type
		enum MOUSEBUTTON
		{
			MOUSE_LEFT = 1,
			MOUSE_MIDDLE,
			MOUSE_RIGHT
		};
	
	//- [Construction] -
		ASFC_Input();
	//- [Key Handeling] -
		SDLKey GetKey();
		int GetKey(int keyDelay, int repeatRate);
		SDLMod GetMod();
		bool KeyUp(SDLKey key);
		bool KeyDown(SDLKey key);
	//- [Mouse Handeling] -	
		int GetMouseX();
		int GetMouseY();
		bool GetMouseButton(int iButton);
		void Pause();
	//- [Updating] -
		void Update();
	
	private:
	//Const
		const static int KEY_INVALID = -1;
	
		SDL_Event _event;
		
		//AIS** (Variables for advanced GetKey() (the one with the most param)
			void SetDefaults();
			
			//vars
				int	   _repeatKey;
				bool   _repeat;
				ASFC_Timer _time;
				ASFC_Timer _repeatTime;
};

#endif

//end of keyinput.h
	
