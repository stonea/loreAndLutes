//Associated Header
	#include "timer.h"

//----------------------------------------------------------- [Resetting] -
void ASFC_Timer::Reset()
{
	_ticks = SDL_GetTicks();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Timer::Delay(long lMilliseconds)
{
	//Loop until that ellapsed time has been met
		while(SDL_GetTicks() - _ticks < lMilliseconds)
		{
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool ASFC_Timer::Ellapsed(long lMilliseconds)
{
	//Return true if that's passed
		return(SDL_GetTicks() - _ticks > lMilliseconds);	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
long ASFC_Timer::Ellapsed()
{
	//Return the number of mills ellapsed
		return(SDL_GetTicks() - _ticks);
}
