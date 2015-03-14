/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			gameclock.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LL_GAMECLOCK_H_
#define LL_GAMECLOCK_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include <asfc/surface.h>
//Realizes
	#include <lbase/guimetrics.h>
	#include <asfc/screen.h>
//Dependencies
	#include <math.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_GameClock
{	public:
	//- [Construction] -
		LL_GameClock();
	//- [File I/O]-
		void SaveRecordingInfo(ofstream &oFile);
		bool LoadRecordingInfo(ifstream &oFile, string sGraphicsDir);
	//- [Time] -
		MEMVAR_SETGET(SetClockOn,			ClockOn,bool, myfClockOn)
		MEMVAR_SETGET(SetHour, 				Hour, 	int, myiHour);
		MEMVAR_SETGET(SetMinute,			Minute,	int, myiMinute);
		MEMVAR_SETGET(SetTick,				Tick,	int, myiTick);
		MEMVAR_SETGET(SetTicksPerMinute,	TicksPerMinute,	int, myiTicksPerMinute);
		void AddTicks(int iTicks);
	//- [Date] -
		MEMVAR_SETGET(SetDay, 			Day, 	int, myiDay);
		MEMVAR_SETGET(SetMonth,			Month,	int, myiMonth);
		MEMVAR_SETGET(SetYear,			Year,	int, myiYear);
	//- [Drawing] -
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, mypoScreen);
		void Draw();
		
	protected:
	//P- [Drawing] -P
		bool SunUp();
		int SunElementX();		
		int SunElementY();
		bool MoonUp();
		int MoonElementX();
		int MoonElementY();
	
	//Vars
		bool myfClockOn;
		int myiHour,
			myiMinute,
			myiTick,
			myiTicksPerMinute;
		int myiDay,
			myiMonth,
			myiYear;
		ASFC_Screen* mypoScreen;
		ASFC_Surface myimgSun,
					 myimgMoon1,
					 myimgMoon2,
					 myimgMoon3,
					 myimgMoon4,
					 myimgMoon5,
					 myimgMoon6,
					 myimgMoon7,
					 myimgMoon8;

	//Const
		const static int MINUTES_PER_HOUR = 60;
		const static int HOURS_PER_DAY	  = 24;
		const static int DAYS_PER_MONTH	  = 30;
		const static int MONTHS_PER_YEAR  = 12;
		#define LL_GameClock__SUN 	"./data/clock/sun.bmp"
		#define LL_GameClock__MOON1 "./data/clock/moon1.bmp"
		#define LL_GameClock__MOON2 "./data/clock/moon2.bmp"
		#define LL_GameClock__MOON3 "./data/clock/moon3.bmp"
		#define LL_GameClock__MOON4 "./data/clock/moon4.bmp"
		#define LL_GameClock__MOON5 "./data/clock/moon5.bmp"
		#define LL_GameClock__MOON6 "./data/clock/moon6.bmp"
		#define LL_GameClock__MOON7 "./data/clock/moon7.bmp"
		#define LL_GameClock__MOON8 "./data/clock/moon8.bmp"
};

#endif
