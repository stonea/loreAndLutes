#ifndef ASFC_IMAGE_H_
#define ASFC_IMAGE_H_

//Aggregates
	#include <vector>
	using namespace std;

//Dependencies
	#include <SDL.h>
	#include <SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "utils.h"
	#include "screen.h"
	
class ASFC_Image
{
	public:
	//- [Construction] -
		ASFC_Image(int imgBpp = -1, int transR = -1, int transG = -1,
			int transB = -1, int bufW = -1, int bufH = -1,
			int subImgW = -1, int subImgH = -1);
		MEMVAR_GET(SubWidth, int, _subWidth);
		MEMVAR_GET(SubHeight, int, _subHeight);
	//- [Loading] -
		int Load(string file);
		int Load(string file, int element);
	//- [Drawing] -
		void Draw(ASFC_Screen &screen, int x, int y, int element = 0);
		
	protected:
	//P- [Loading] -P
		void CalculateLegalGLSize();
		int ConvertSurfaceToTexture(int surfaceNum);
		int SurfaceNumForElement(int element);
		SDL_Surface* SurfaceForSurfaceNum(int surfaceNum);
		GLuint TextureIDForSurfaceNum(int surfaceNum);
		void *TextureForSurfaceNum(int surfaceNum);
	
	//Vars
		int _numImages;
		int _width, _height, _bpp, _subWidth, _subHeight, _elementsPerRow;
		int _imagesPerSurface;
		SDL_Surface *_surface;
		void *_texture;
		GLuint _textureID;
		vector<void *> _additionalTextures;
		vector<GLuint> _additionalTextureIDs;
		vector<SDL_Surface*> _additionalSurfaces;
		int _transR, _transG, _transB;
};

#endif
