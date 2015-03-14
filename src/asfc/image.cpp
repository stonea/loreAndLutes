//Associated header
	#include "image.h"
	
//-------------------------------------------------------- [Construction] -
ASFC_Image::ASFC_Image(int imgBpp, int transR, int transG,
	int transB,int bufW, int bufH, int subImgW, int subImgH)
	: 
	  _numImages(0),
	  _width(bufW),
	  _height(bufH),
	  _subWidth(subImgW),
	  _subHeight(subImgH),
	  _bpp(imgBpp),
	  _texture(NULL),
	  _transR(transR),
	  _transG(transG),
	  _transB(transB)
{
	//Vars
		double closestPower;
	
	//!!! ADD SUPPORT TO ALLOW THE SIZE TO BE SET UPON THE FIRST IMG LOAD !!!
	//!!! free the texture memory !!!	
	//Create the surface if we have a definite size
		if(_bpp != -1 && _width != -1 && _height != 1)
		{
			//Insure a legal buffer size
				CalculateLegalGLSize();
			//Create the surface
				_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, _width, _height+1,
					_bpp, 0, 0, 0, 0);
			//Create the texture
				_texture = (void *)malloc(_width * _height * 4);
				glGenTextures(1, &_textureID);
		}
}
//------------------------------------------------------------- [Loading] -
int ASFC_Image::Load(string file)
{
	//Load the next element
		return Load(file, -1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int ASFC_Image::Load(string file, int element)
{
	//Vars
		SDL_Surface *imgSurface, *dstSurface;
		SDL_Rect srcRect, dstRect;
		int row, col, subImages;
		int drawElement, subElement;
		int surfaceNum;
	//Load the image onto a temporary surface
		imgSurface = IMG_Load(file.c_str());
	//Create the surface if it hasn't already been created
		if(_width == -1 || _height == -1 || _bpp == -1)
		{
			//Set the image statistics
				_width  = imgSurface->w;
				_height = imgSurface->h;
				_bpp = imgSurface->format->BitsPerPixel;
			//Calculate a legal GL size
				CalculateLegalGLSize();
			//Create the surface
				_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, _width, _height,
					_bpp, 0, 0, 0, 0);		
			//Create the texture
				_texture = (void *)malloc(_width * _height * 4);
				glGenTextures(1, &_textureID);
		}
	//Set the subwidth\height if it hasn't already been set
		if(_subWidth == -1 || _subHeight == -1)
		{
			_subWidth  = imgSurface->w;
			_subHeight = imgSurface->h;
			CalculateLegalGLSize();
		}
	//Determine how many sub images are in the image file (only load 1 image if a specifc element
	//was chosen.
		subImages = imgSurface->w / _subWidth;
		if(element != -1)
			subImages = 1;
	//Loop through every sub image
		element == -1 ? drawElement = _numImages : drawElement = element;
		for(int i = 0; i < subImages; i++)
		{
			//Figure out what surface this image should be set to
				dstSurface = _surface;
				surfaceNum = -1;
				if(drawElement >= _imagesPerSurface)
				{
					//Figure out what extra surface in the vector this image maps to
						surfaceNum = SurfaceNumForElement(drawElement);
					//Loop until this extra surface exists
						while(_additionalSurfaces.size() <= surfaceNum)
						{
							//Add another extra surface
								_additionalSurfaces.resize(_additionalSurfaces.size() + 1);
								_additionalSurfaces[_additionalSurfaces.size() - 1] =
									SDL_CreateRGBSurface(SDL_SWSURFACE, _width, _height+1,
									_bpp, 0, 0, 0, 0);
							//Add another extra texture
								_additionalTextureIDs.resize(_additionalTextureIDs.size() + 1);
								_additionalTextures.resize(_additionalTextures.size() + 1);
								_additionalTextures[_additionalTextures.size() - 1] =
									(void *)malloc(_width * _height * 4);
								glGenTextures(1,
									&_additionalTextureIDs[_additionalTextureIDs.size() - 1]);
						}
					dstSurface = _additionalSurfaces[surfaceNum];
				}
			//Figure out which element in the surface we're dealing with
				if(surfaceNum >= 0)
					subElement = drawElement - _imagesPerSurface * (surfaceNum + 1);
				else
					subElement = drawElement;
			//Figure out where to plot this new image in the surface
				//Determine this image's row\col position within the larger buffer
					row = subElement / _elementsPerRow;
					col = subElement % _elementsPerRow;
				//Create the source rectangle
					srcRect.x = _subWidth * i;
					srcRect.y = 0;
					srcRect.w = _subWidth;
					srcRect.h = _subHeight;
				//Create the destination rectangle
					dstRect.x = col * _subWidth;
					dstRect.y = row * _subHeight;
					dstRect.w = _subWidth;
					dstRect.h = _subHeight;
			//Copy the image onto the surface
				SDL_BlitSurface(imgSurface, &srcRect, dstSurface, &dstRect);
			//Conver the surface to the current texture
				ConvertSurfaceToTexture(surfaceNum);
			//If we added an image remember so
				if(element == -1)
					_numImages++;
				drawElement++;
		}
	//Delete the temporary image surface
		SDL_FreeSurface(imgSurface);
	//Return the number of rectangles
		return _numImages;	
}
//------------------------------------------------------------- [Drawing] -
void ASFC_Image::Draw(ASFC_Screen &screen, int x, int y, int element)
{
	//Vars
		int row, col;
		float texSubW, texSubH;
		float aX, aY, bX, bY, cX, cY, dX, dY;
		int surfaceNum, textureID;
	//Figure out which surface this element lies in, and the associated
	//texture ID
		surfaceNum = SurfaceNumForElement(element);
		if(surfaceNum == -1)
			textureID = _textureID;
		else
		{
			textureID = _additionalTextureIDs[surfaceNum];
			element -= _imagesPerSurface * (surfaceNum + 1);
		}
	//Determine the pixel location in the surface where this image is		
		row  = element / _elementsPerRow;
		col  = element % _elementsPerRow;
		texSubW = (float)_subWidth  / (float)_width;
		texSubH = (float)_subHeight / (float)_height;
		aX = texSubW * col;
		aY = 1.0 - texSubH * row;
		bX = aX + texSubW;
		bY = aY;
		cX = aX;
		cY = aY - texSubH;
		dX = bX;
		dY = cY;
		
		if(element == -1)
		{
			aX = 0;
			aY = 1;
			bX = 1;
			bY = 1;
			cX = 0;
			cY = 0;
			dX = 1;
			dY = 0;
		}
	//Draw this objects texture
    	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBegin(GL_QUADS);
			//Set the default color
				glColor4f(1.0, 1.0, 1.0, 1.0);
			//Top left
				glTexCoord2f(aX, aY);
				glVertex2f(x, y);
			//Top right
				glTexCoord2f(bX, bY);
				if(element != -1)
					glVertex2f(x + _subWidth, y);
				else
					glVertex2f(x + _width, y);
			//Bottom right
				glTexCoord2f(dX, dY);
				if(element != -1)
					glVertex2f(x + _subWidth, y + _subHeight);
				else
					glVertex2f(x + _width, y + _height);
			//Bottom left
				glTexCoord2f(cX, cY);
				if(element != -1)
					glVertex2f(x, y + _subHeight);
				else
					glVertex2f(x, y + _height);
		glEnd();
}
//P----------------------------------------------------------- [Loading] -P
void ASFC_Image::CalculateLegalGLSize()
{
	//Vars
		float closestPower;

	//Convert the width & height values to be legal GL size
	//Legal GL size has width & height values that are powers of 2
	//For example: 16 x 16, 32, 64, 128, 512 are all legal GL sizes
	//while 15 x 15 3 x 9, 32 x 65 are not
		closestPower = log((double)_width) / log(2.0);
		if(int(closestPower) != closestPower)
			closestPower = int(closestPower) + 1;
		_width = (int)pow(2, closestPower);

		closestPower = log((double)_height) / log(2.0);
		if(int(closestPower) != closestPower)
			closestPower = int(closestPower) + 1;
		_height = (int)pow(2, closestPower);
	//Insure that the texture is a square
		if(_width > _height)
			_height = _width;
		if(_height > _width);
			_width = _height;
	//Figure out the number of sub images that span across one row in the surface
		_elementsPerRow = int((float)_width / (float)_subWidth);
		_imagesPerSurface = _elementsPerRow *
			int(float(_height) / float(_subHeight));
		if(_imagesPerSurface <= 0)
		{
			cerr << "Error in ASFC_Image: Surface isn't large enough to hold image\n";
			cerr << "\tPotential for seg fault.\n";
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int ASFC_Image::ConvertSurfaceToTexture(int surfaceNum)
{
	//Vars
		int bpp;
		Uint8 *srcPxl, *dstPxl;
		Uint32 fullPxl;
		SDL_Surface* surface;
		GLuint textureID;
		void *texture;
		
	//Grab the number of bytes per pixel
		bpp = _bpp / 8;
	//Grab a pointer to the surface, texture, and textureID that needs to be dealt with
		surface   = SurfaceForSurfaceNum(surfaceNum);
		textureID = TextureIDForSurfaceNum(surfaceNum);
		texture   = TextureForSurfaceNum(surfaceNum);		
	//Grab the start of the texture data
		dstPxl = (Uint8 *)texture;
	//Copy the bytes in the SDL surface to the openGL texture
		SDL_LockSurface(surface);
		//!! THIS SHOULD BE >= , BUT IT SEG FAULTS IF I DO THAT? WHY? WHO KNOWS? !!!
		for(int i = _height-1; i >= 0; i--)
		{
			for(int j = 0; j < _width; j++)
			{
				//Grab the source pixel
					srcPxl = (Uint8 *)surface->pixels + i * surface->pitch + j * bpp;
				//Convert this source pixel into a full 32 bit pixel
					if(bpp == 1)
					{
						fullPxl = *srcPxl;
					}
					else if(bpp == 2)
					{
						fullPxl = *(Uint16 *)srcPxl;
					}
					else if(bpp == 3)
					{
						if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
						{
							fullPxl = srcPxl[0] << 16 | srcPxl[1] << 8 | srcPxl[2];
						}
						else
						{
							fullPxl = srcPxl[0] | srcPxl[1] << 8 | srcPxl[2] << 16;
						}
					}
					else if(bpp == 4)
					{
						fullPxl = *(Uint32 *)srcPxl;
					}
					else
					{
						cerr << "Can not convert SDL Surface to OpenGL Texture. Invalid image ";
						cerr << "bpp of " << bpp << endl;
						exit(1);
					}
				//Put the pixel onto the texture
					SDL_GetRGBA(fullPxl, surface->format, &(dstPxl[0]), &(dstPxl[1]),
						&(dstPxl[2]), &(dstPxl[3]));
				//If we have a transparent pixel set the alpha to 0.
					if(dstPxl[0] == _transR && dstPxl[1] == _transG && dstPxl[2] == _transB)
					{
						dstPxl[3] = 0;
					}
					//cerr << j << " " << i << endl;
					//screen.DrawPixel(j, i, dstPxl[0], dstPxl[1], dstPxl[2]);
						
					dstPxl += 4;
			}
		}
		SDL_UnlockSurface(surface);
	//Now generate this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, _width, _height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, (unsigned int*)texture);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int ASFC_Image::SurfaceNumForElement(int element)
{
	return (element / _imagesPerSurface) - 1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
SDL_Surface* ASFC_Image::SurfaceForSurfaceNum(int surfaceNum)
{
	if(surfaceNum < 0)
		return _surface;
	else
		return(_additionalSurfaces[surfaceNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
GLuint ASFC_Image::TextureIDForSurfaceNum(int surfaceNum)
{
	if(surfaceNum < 0)
		return _textureID;
	else
		return(_additionalTextureIDs[surfaceNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void *ASFC_Image::TextureForSurfaceNum(int surfaceNum)
{
	if(surfaceNum < 0)
		return _texture;
	else
		return(_additionalTextures[surfaceNum]);
}
