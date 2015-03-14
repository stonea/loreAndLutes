//Protected under the GNU General Public License read and see copying.txt for details
#ifndef ASFC_SCREEN_H_
#define ASFC_SCREEN_H_

#include "surface.h"
//Dependencies
	#include "utils.h"

class ASFC_Screen : public ASFC_Surface {
	public:
		ASFC_Screen();
		ASFC_Screen(int width, int height, int bpp, bool fullscreen = false);
		~ASFC_Screen();
		
		int Init(int width, int height, int bpp, bool fullscreen = false);
		void Update();
};

#endif	
		
