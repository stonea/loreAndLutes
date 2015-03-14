/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			filechooser.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: Displays a directory listing and allows the user to choose a file. This class uses
				 PhysFS to poll for directory information.
*/
#ifndef LEDIT_FILECHOOSER_H_
#define LEDIT_FILECHOOSER_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//PhysFS (for directory management functions, e.g. enumerate files)
	#include <physfs.h>
//Parent
	#include "editor.h"
//Dependencies
	#include <asfc/utils.h>
	#include <SDL/SDL.h>
//Aggregates
	#include <vector>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_FileChooser : public LEDIT_Editor
{	public:
	//- [Construction] -
		LEDIT_FileChooser();
		~LEDIT_FileChooser();
		MEMVAR_SETGET(SetFileManager, FileManager, LL_FileManager*, mypoFileManager);
	//- [File Choosing] -
		string 	GrabFile(C_s2(sDirectory, sFileType));

	protected:
	//P- [File Choosing] -P
		bool HandleKeys();
		void HandleMouse(int* piKey);
		void EnumerateFiles();
		void DrawFiles();
		string FileName(string sFile, C_i(iMaxChars));
		string DirBack(C_s(sDir));

	//Vars
	 	string mysDirectory; 
 		string mysSubDirectory;	//Directorys down from the original mysDirectory
    	string mysFileType;
       	string mysNotes;
	    vector<LL_FileManager::LL_FileInfo> myloFiles;
		int myiSelected;
		int myiDirsDown;
		ASFC_Input myoInput;
		ASFC_Timer myoTimer;
		LL_FileManager* mypoFileManager;

	//Const
		static const int NO_LINK	= -1;
		static const int COL1_X		= 0;	//Where the first columns of files in a GrabFile() list is
		static const int COL2_X		= 26;	//Where the second columns of files in a GrabFile() list is
		static const int NUMCOLS	= 2;	//The # of columns in a GrabFile() list
		static const int DELAY		= 100;	//Time that must pass between cursor movements in GrabFile()
		static const int NO_SELECTION = -1;	//No item selected

		//Keys
			static const SDLKey KEY_PREVFILE 	= SDLK_LEFT;
			static const SDLKey KEY_NEXTFILE 	= SDLK_RIGHT;
			static const SDLKey KEY_PREVROW		= SDLK_UP;
			static const SDLKey KEY_NEXTROW		= SDLK_DOWN;
			static const SDLKey KEY_PAGEUP		= SDLK_PAGEUP;
			static const SDLKey KEY_PAGEDOWN	= SDLK_PAGEDOWN;
			static const SDLKey KEY_CHOOSE		= SDLK_RETURN;
			static const SDLKey KEY_CHOOSE2		= SDLK_SPACE;
			static const SDLKey KEY_CANCEL		= SDLK_ESCAPE;
};

#endif
