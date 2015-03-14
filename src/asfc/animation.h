#ifndef ASFC_ANIMATION_H_
#define ASFC_ANIMATION_H_

//Dependencies
	#include <SDL.h>
	#include <SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "utils.h"
	#include "screen.h"
//Aggregates
	#include "image.h"
	#include <vector>
	using namespace std;
	
class ASFC_Animation
{
	public:
	//- [Constuctors] -
 		ASFC_Animation(int subImageWidth, int subImageHeight,
			int imageBufferWidth = -1, int imageBufferHeight = -1);
	//- [Loading] -
		int Load(string file);
	//- [Drawing] -
		MEMVAR_GET(NumElements, int, _elements.size());
		void Draw(ASFC_Screen &screen, int x, int y, int animation);
		void Update();
 	
 	protected:
	//Type
		struct ASFC_Animation_Element
		{
			ASFC_Animation_Element()
			{
				currentFrame = 0;
				animated = true;
			}
		
			int element, numImages, currentFrame;
			bool animated;
		};
	
 	//Vars
		ASFC_Image _images;	
		vector<ASFC_Animation_Element> _elements;
		int _subImageWidth, _subImageHeight, _numImages;
};

//Now ending animation.h
	#endif
