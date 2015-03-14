#ifndef ASFC_UTILS_H_
#define ASFC_UTILS_H_

//Dependencies
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <stdio.h>
	#include <math.h>
	using namespace std;

//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
/*MEMVAR_SET: This macro creates a function that sets variable C, of type B, with a function called A
	Example: If you had an int called iValue you could do this:
				MEMVAR_SET(SetValue, int, iValue);
	
	Result:
		void A(B zSetTo) 
		{	C = zSetTo
		}
		
	Result of Example:
		void SetValue(int zSetTo)
		{	iValue = zSetTo;
		}
		
	It save typing!
*/
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
#define MEMVAR_SET(A, B, C) \
	void A(B zSetTo) \
	{ \
		C = zSetTo; \
	}
//..................................................................................................................
/*MEMVAR_GET: This macro creates a function that returns variable C, of type B, with a function called A
	Example: If you had an int called iValue you could do this:
				MEMVAR_GET(GetValue, int, iValue);
	
	Result:
		B A() 
		{	return(C)
		}
		
	Result of Example:
		int GetValue()
		{	return(iValue);
		}	
*/
#define MEMVAR_GET(A, B, C)\
	B A()\
	{\
		return(C);\
	}\
//..................................................................................................................
/*MEMVAR_SETGET: This macro creates a function simply calls MEMVAR_SET(A, C, D); and thne
			   	 MEMVAR_GET(B, C, D);
	
	Result:
		MEMVAR_SET(A, C, D);
		MEMVAR_GET(B, C, D);
*/
#define MEMVAR_SETGET(A, B, C, D) \
	void A(C zSetTo) \
	{ \
		D = zSetTo; \
	} \
 \
	C B() \
	{ \
		return(D); \
	}
//..................................................................................................................
/*MEMVAR_LINK: This macro creates a MEMVAR_SET and MEMVAR_GET functions that overload eachother
	
	Result:
		MEMVAR_SET(A, B, C);
		MEMVAR_GET(A, B, C);
*/
#define MEMVAR_LINK(A, B, C)	void A(B zSetTo) {C = zSetTo;} B A() {return(C);}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
/*	Color constants


	These color constants are just a shorthand way of writing common RGB values.
*/

//Primary, Secondary, and grays (in the compu-spectrum)
#define COLOR_RED				0xff, 0x00, 0x00
#define COLOR_GREEN				0x00, 0xff, 0x00
#define COLOR_BLUE				0x00, 0x00, 0xff
#define COLOR_YELLOW			0xff, 0xff, 0x00
#define COLOR_PURPLE			0xff, 0x00, 0xff
#define COLOR_CYAN				0x00, 0xff, 0xff
#define COLOR_GRAY				0x7f, 0x7f, 0x7f

#define COLOR_LIGHT_RED			0xff, 0x7f, 0x7f
#define COLOR_LIGHT_GREEN		0x7f, 0xff, 0x7f
#define COLOR_LIGHT_BLUE		0x7f, 0x7f, 0xff
#define COLOR_LIGHT_YELLOW		0xff, 0xff, 0x7f
#define COLOR_LIGHT_PURPLE		0xff, 0x7f, 0xff
#define COLOR_LIGHT_CYAN		0x7f, 0xff, 0xff
#define COLOR_LIGHT_GRAY		0xbf, 0xbf, 0xbf

#define COLOR_DARK_RED			0x7f, 0x00, 0x00
#define COLOR_DARK_GREEN		0x00, 0x7f, 0x00
#define COLOR_DARK_BLUE			0x00, 0x00, 0x7f
#define COLOR_DARK_YELLOW		0x7f, 0x7f, 0x00
#define COLOR_DARK_PURPLE		0x7f, 0x00, 0x7f
#define COLOR_DARK_CYAN			0x00, 0x7f, 0x7f
#define COLOR_DARK_GRAY			0x3f, 0x3f, 0x3f

#define COLOR_GRAY_0			0x00, 0x00, 0x00
#define COLOR_GRAY_1			0x10, 0x10, 0x10
#define COLOR_GRAY_2			0x20, 0x20, 0x20
#define COLOR_GRAY_3			0x30, 0x30, 0x30
#define COLOR_GRAY_4			0x40, 0x40, 0x40
#define COLOR_GRAY_5			0x50, 0x50, 0x50
#define COLOR_GRAY_6			0x60, 0x60, 0x60
#define COLOR_GRAY_7			0x70, 0x70, 0x70
#define COLOR_GRAY_8			0x80, 0x80, 0x80
#define COLOR_GRAY_9			0x90, 0x90, 0x90
#define COLOR_GRAY_A			0xa0, 0xa0, 0xa0
#define COLOR_GRAY_B			0xb0, 0xb0, 0xb0
#define COLOR_GRAY_C			0xc0, 0xc0, 0xc0
#define COLOR_GRAY_D			0xd0, 0xd0, 0xd0
#define COLOR_GRAY_E			0xe0, 0xe0, 0xe0
#define COLOR_GRAY_F			0xf0, 0xf0, 0xf0

#define COLOR_BLACK				0x00, 0x00, 0x00
#define COLOR_WHITE				0xff, 0xff, 0xff

//Oranges & Browns
#define COLOR_ORANGE			0xff, 0x80, 0x00
#define COLOR_LIGHT_ORANGE		0xff, 0xbf, 0x80
#define COLOR_DARK_ORANGE		0xbf, 0x5f, 0x00

#define COLOR_BROWN				0xa5, 0x7b, 0x48
#define COLOR_LIGHT_BROWN		0xa5, 0x93, 0x7c
#define COLOR_DARK_BROWN		0x59, 0x45, 0x2c

//..................................................................................................................
/*	Direction constants

	These constants associate direction with a numerical value
*/
enum ASFC_DIRECTION
{	DIR_NORTH		=	0,
	DIR_NORTH_WEST,
	DIR_NORTH_EAST,
       
	DIR_SOUTH,
	DIR_SOUTH_WEST,
	DIR_SOUTH_EAST,
       
	DIR_WEST,
	DIR_EAST,
       
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
       
	DIR_X_POS,
	DIR_X_NEG,
	DIR_Y_POS,
	DIR_Y_NEG,
	DIR_Z_POS,
	DIR_Z_NEG,
       
	DIR_QUAD_1,
	DIR_QUAD_2,
	DIR_QUAD_3,
	DIR_QUAD_4,
       
	DIR_CLOCKWISE,
	DIR_COUNTER_CLOCKWISE,
       
	DIR_WITH,
	DIR_AGAINST,
       
	DIR_DOWNSTREAM,
	DIR_UPSTREAM,

	DIR_IDLE
};


//..................................................................................................................
/*	True\False constants

	These constants hold bool values.
*/

#define YES			true
#define NO			false

#define AFFIRMATIVE	true
#define NEGATIVE	false

#define ON			true
#define OFF			false

#define GO			true
#define STOP		false

//..................................................................................................................
//Angular Constants
const 	double	ANGLE_0  			= 0.0;
const	double	ANGLE_PIovr6		= 0.5235987756;
const	double	ANGLE_PIover4		= 0.7853981634;
const	double	ANGLE_PIover3		= 1.047197551;
const	double	ANGLE_PIover2		= 1.570796327;
const	double	ANGLE_2PIover3		= 2.094395102;
const	double	ANGLE_3PIover4		= 2.35619449;
const	double	ANGLE_5PIover6		= 2.617993878;
const	double	ANGLE_PI			= 3.141592654;
const	double	ANGLE_7PIover6		= 5.497787144;
const	double	ANGLE_5PIover4		= 3.926990817;
const	double	ANGLE_4PIover3		= 4.188790205;
const	double	ANGLE_3PIover2		= 4.71238898;
const	double	ANGLE_5PIover3		= 5.235987756;
const	double	ANGLE_7PIover4		= 5.497787144;
const	double	ANGLE_11PIover6		= 5.759586532;
const	double	ANGLE_2PI			= 6.283185307;
//..................................................................................................................
/*	Returns

	These constants hold common return values that functions may use
*/
enum ASFC_RETURN
{	RETURN_GOOD   = 0,
	RETURN_BAD    = -1,
	RETURN_DEBUG  = 10
};
//..................................................................................................................
/*	UnTypeable Characters

	These constants hold some important characters that can't usually be typed easily. NOTICE:
	these chars are for ANSI fonts!
*/
const char CH_ENDL					= '\n';
const char CH_TAB					= '\t';
const char CH_BELL					= '\a';
const char CH_SPACE					= ' ';
const char CH_CENTS					= '¢';
const char CH_POUNDS				= '£';
const char CH_YEN					= '¥';
const char CH_COPYRIGHT				= '©';
const char CH_RIGHTSRESERVED		= '®';
const char CH_DEGREES				= '°';
const char CH_PLUSORMINUS			= '±';
const char CH_SQUARED				= '²';
const char CH_CUBED					= '³';
const char CH_PARAGRAPH				= '¶';
const char CH_DOT					= '·';
const char CH_1OVER4				= '¼';
const char CH_1OVER2				= '½';
const char CH_3OVER4				= '¾';
const char CH_INVERSEQUESTION		= '¿';
const char CH_DIVIDE				= '÷';
//..................................................................................................................
//Prototypes of various helper functions (String manipulation mostly)
string UpperString(string s);				//Returns s in all caps
string LowerString(string s);				//Returns s in all lowers
string Val(double d);			  			//Converts a value to a string
double Val(string s);		 	  			//Converts a string to a value
string Rot(int iChars, string s); 			//Rotates all the chars iChars down in a string
void SToStr(string s, char* str); 			//Converts a C++ string to an C string
void RangeCheck(int i, int iMin, int iMax, string sFunction, string sVar, int iErrCode);	//Range checks variable i (inclusive min & max)
string Qoute(string s);						//Returns string s surrounded with qoutes
string ReadString(ifstream &oFile); 		//Reads in a string surrounded by double qoutes (or any other set of characters) from a ifstream
bool FileExist(string sFile);				//Returns true if sFile is a valid file
int PollRandom(int max);					//Generates a number from [0, max)

#endif
