/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			shader.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: The shader plots areas in a matrix false based on information it gets from a terrain
				 map about light interactions.
*/
#ifndef LRUN_SHADER_H_
#define LRUN_SHADER_H_
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include <asfc/linkedlist.h>
	#include <asfc/matrix.h>
//Realizes
	#include <lbase/gameclock.h>
//Dependencies
	#include <fstream>
	#include <asfc/utils.h>
	#include <lbase/terrainmap.h>
	using namespace std;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//A LRUN_Shade describes a type of shading efffect that should be preformed
enum LRUN_SHADE
{	SHADE_NORTH				= 0,
	SHADE_NORTH_EAST,
	SHADE_EAST,
	SHADE_SOUTH_EAST,
	SHADE_SOUTH,
	SHADE_SOUTH_WEST,
	SHADE_WEST,
	SHADE_NORTH_WEST,
	SHADE_LIGHTHOUSE_1,
	SHADE_LIGHTHOUSE_2,
	SHADE_LIGHTHOUSE_3,
	SHADE_LIGHTHOUSE_4,
	SHADE_LIGHTHOUSE_5,
	SHADE_LIGHTHOUSE_6,
	SHADE_LIGHTHOUSE_7,
	SHADE_LIGHTHOUSE_8,
	SHADE_TORCH_SMALL,
	SHADE_TORCH,
	SHADE_DAY_1,
	SHADE_DAY_2,
	SHADE_DAY_3,
	SHADE_DAY_4,
	SHADE_DAY_5,
	SHADE_DAY_6,
	SHADE_DAY_7,
	SHADE_DAY_8,
	SHADE_ILLUMINATE
};
	

class LRUN_Shader
{	public:
	//Const
		static const int LIGHTHOUSE_FRAMES = 8;
	
	//- [Construction] -
		LRUN_Shader();
		MEMVAR_SETGET(SetClock, Clock, LL_GameClock*, mypoGameClock);
	//- [File I/O] -
		void LoadShades(string sFile);
	//- [Testing\Debugging] -
		void DrawShade(C_i(iShade));	//Outputs shade pattern #iShade to the console		
	//- [Shade] -
		void Shade(ASFC_Matrix<bool> &oMatrix, C_i3(iFromX, iFromY, iPattern), const bool fStyle);
		void GrabLight(C_i4(iTopLeftX, iTopLeftY, iPlayerX, iPlayerY), LL_TerrainMap& oMap, 
				       ASFC_Matrix<bool> &lLight, bool AddTorchLight);
 	
 	private:
 	//P- [Debugging] -P
 		bool ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum));
 		
 	//Vars 	
 		ASFC_LinkedList<ASFC_Matrix<bool> > lShades;
 		int myiWidth, myiHeight, myiCenterX, myiCenterY;
 		int myiLighthouseFrame;
 		LL_GameClock* mypoGameClock;
};

#endif
