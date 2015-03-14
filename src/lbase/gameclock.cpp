/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			gameclock.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "gameclock.h" 
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LL_GameClock
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LL_GameClock::LL_GameClock()
	:	myfClockOn(true),
 		myiHour(6),
		myiMinute(30),
		myiTick(0),
		myiTicksPerMinute(100),
		myiDay(5),
		myiMonth(2),
		myiYear(85)
{	//Load images
		myimgSun.LoadImage	(LL_GameClock__SUN);
		myimgMoon1.LoadImage(LL_GameClock__MOON1);
}
//---------------------------------------------------------------------------------------------- [File I/O]-
void LL_GameClock::SaveRecordingInfo(ofstream &oFile)
{	//%Clock On%
		oFile << myfClockOn << " ";
	//%Hour% %Minute% %Tick% %TicksPerMinute%
		oFile << myiHour   << " "
  			  << myiMinute << " "
       		  << myiTick   << " "
              << myiTicksPerMinute << " ";
	//%Day% %Month% %Year%
		oFile << myiDay << " " << myiMonth << " " << myiYear << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_GameClock::LoadRecordingInfo(ifstream &oFile, string sGraphicsDir)
{	//%Clock On%
		oFile >> myfClockOn;
	//%Hour% %Minute% %Tick% %TicksPerMinute%
		oFile >> myiHour >> myiMinute >> myiTick >> myiTicksPerMinute;
	//%Day% %Month% %Year%
		oFile >> myiDay >> myiMonth >> myiYear;
}
//------------------------------------------------------------------------------------------------ [Time] -
void LL_GameClock::AddTicks(int iTicks)
{	//!!! Add code to handle date!

	//Add the ticks
		myiTick += iTicks;

	//Make sure we have no overlapping times
		while(myiTick >= myiTicksPerMinute)
		{	myiMinute++;
			myiTick -= myiTicksPerMinute;
		}
		while(myiMinute >= MINUTES_PER_HOUR)
		{	myiHour++;
			myiMinute -= MINUTES_PER_HOUR;
		}
		
	//Make sure we haven't progressed into the next day\month\year
		while(myiHour >= HOURS_PER_DAY)
		{	myiDay++;
  			myiHour -= HOURS_PER_DAY;
		}
		while(myiDay >= DAYS_PER_MONTH)
		{	myiMonth++;
			myiDay -= DAYS_PER_MONTH;
		}
		while(myiMonth >= MONTHS_PER_YEAR)
		{	myiYear++;
			myiMonth -= MONTHS_PER_YEAR;
		}
}
//-------------------------------------------------------------------------------------------- [Drawing] -
void LL_GameClock::Draw()
{	//If the clock's off don't draw
		if(!myfClockOn)
		{	return;
		}
	//Sun if up
		if(SunUp())
		{	myimgSun.BlitTo(*mypoScreen, SunElementX() + CELESTIALVIEW_X, PLAYFIELD_Y - SunElementY()-11);
		}
	//Moon if up
		if(MoonUp())
		{	myimgMoon1.BlitTo(	*mypoScreen, MoonElementX() + CELESTIALVIEW_X,
								PLAYFIELD_Y - MoonElementY()-11);
		}
}
//P------------------------------------------------------------------------------------------- [Drawing] -P
bool LL_GameClock::SunUp()
{	//The sun is up on the interval [0, 18]
		if(myiHour >= 0 && myiHour < 18)
			return true;
		return false;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_GameClock::SunElementX()
{	/* Equation: 34(x-6)
	*/
	
	//Vars
		double dTime;
	
	//First figure out the time as a double value:
		dTime = myiHour + double(myiMinute) / 60;
		
	//Return the formlula
		return(int(34 * (dTime-6)));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_GameClock::SunElementY()
{	/* 	Where the Element Y Equation comes from:
		abs(46sin((PI/24)x)
	*/
	
	//Vars
		double dTime;
	
	//First figure out the time as a double value:
		dTime = myiHour + double(myiMinute)/60;
		
	//Figure out which twelve of the clock dTime is in
		dTime -= 6;
		
	//Now put this in the formula and return
		return(int(33 * sin(.2617993878 * dTime)));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
bool LL_GameClock::MoonUp()
{	//The moon is up on the interval [18, 24)U[0,6]
		if((myiHour >= 18 && myiHour < 24) || (myiHour >= 0 && myiHour <= 6))
			return true;
		return false;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_GameClock::MoonElementX()
{	//Vars
		double dTime;

	//First figure out the time as a double value:
		dTime = myiHour + double(myiMinute) / 60;
		
	//Now translate dTime to equal which 12/th of the clock it will occupy
		if(myiHour  >= 18) dTime -= 18;
		else			   dTime += 6;
		
	//Return the formlula
		return(int(34 * dTime));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
int LL_GameClock::MoonElementY()
{	//Vars
		double dTime;

	//First figure out the time as a double value:
		dTime = myiHour + double(myiMinute) / 60;
		
	//Now translate dTime to equal which 12/th of the clock it will occupy
		if(myiHour  >= 18) dTime -= 18;
		else			   dTime += 6;
		
	//Now enter it in the sine wave formula
		return(int(33 * sin(.2617993878 * dTime)));
}
