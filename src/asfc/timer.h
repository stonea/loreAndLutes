#ifndef ASFC_TIMER_H_
#define ASFC_TIMER_H_

//Dependencies
	#include <SDL.h>


class ASFC_Timer
{	public:
	//- [Resetting] -
		void Reset();
	//- [Time Handeling]
		void Delay(long mills);
		bool Ellapsed(long mills);
		long Ellapsed();
	
	private:
	//var	
		long _ticks;
};

#endif
