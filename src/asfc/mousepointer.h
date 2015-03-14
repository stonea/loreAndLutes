#ifndef ASFC_MOUSEPOINTER_H_
#define ASFC_MOUSEPOINTER_H_

//Dependencies
	#include <SDL.h>
	#include <string>
	#include <fstream>
	using namespace std;

class ASFC_MousePointer
{
	public:
	//- [Construction] -
		ASFC_MousePointer();
	//- [Loading\Setting] -
		void Load(string sFile);
		void Set();

	protected:
		//Const
			const static int NUM_ROWS = 32;
			const static int NUM_COLS = 32;
		//Vars
			char  _image[NUM_COLS][NUM_ROWS];
			int	  _hotX, _hotY;
};

#endif
