/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			legalmovesmap.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A legal moves map is a 3d 100 x 100 x 4 array that describes legal movements
*/
#ifndef LL_LEGALMOVESMAP_H_
#define LL_LEGALMOVESMAP_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_LegalMovesMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_LegalMovesMap
{	public:
	//Const
		#define LL_LegalMovesMap__WIDTH    100
		#define LL_LegalMovesMap__HEIGHT   100
		#define LL_LegalMovesMap__NUM_DIRS 4

	//- [Constuctors] -
 		LL_LegalMovesMap();
	//- [Legal] -
		bool LegalNorth(int iX, int iY);
		bool LegalSouth(int iX, int iY);
		bool LegalWest (int iX, int iY);
		bool LegalEast (int iX, int iY);
		bool SetLegalNorth(int iX, int iY, bool fTo);
		bool SetLegalSouth(int iX, int iY, bool fTo);
		bool SetLegalWest (int iX, int iY, bool fTo);
		bool SetLegalEast (int iX, int iY, bool fTo);
 	private:
 	//Vars
 		bool mylMap[LL_LegalMovesMap__WIDTH][LL_LegalMovesMap__HEIGHT][LL_LegalMovesMap__NUM_DIRS];
};

#endif
