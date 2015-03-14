//Associated header
	#include "animation.h"
	
//--------------------------------------------------------- [Constuctors] -
ASFC_Animation::ASFC_Animation(int subImageWidth, int subImageHeight,
			int imageBufferWidth, int imageBufferHeight)
	:
		_subImageWidth(subImageWidth),
		_subImageHeight(subImageHeight),
		_numImages(0),
		_images(32, COLOR_BLUE, -1, -1, subImageWidth, subImageHeight)
{
	if((subImageWidth > imageBufferWidth ||
		subImageHeight > imageBufferHeight ) &&
		(imageBufferWidth != -1 && imageBufferHeight != -1))
	{
		cerr << "ASFC_Animation err: Invalid image buffer size.\n";
		cerr << "  potential for future seg fault.\n";
	}
		
}
//------------------------------------------------------------- [Loading] -
int ASFC_Animation::Load(string file)
{
	//Vars
		ASFC_Animation_Element newAnimation;

	//Recall where this animation starts
		newAnimation.element = _numImages;
	//Load the animation into the image buffer
		_numImages = _images.Load(file);
	//Recall other stats on the animation
		newAnimation.numImages = _numImages - newAnimation.element;
	//Save our animation information
		_elements.push_back(newAnimation);
	//Return the element number of this animation
		return(_elements.size() - 1);
}
//------------------------------------------------------------- [Drawing] -
void ASFC_Animation::Draw(ASFC_Screen &screen, int x, int y, int animation)
{
	//Draw this animation
		_images.Draw(
			screen, x, y,
			_elements[animation].element + _elements[animation].currentFrame);
	//Turn on the animated flag
		_elements[animation].animated = true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Animation::Update()
{
	//Loop through all animations, turning off their animated flags
	//- and - moving 1 frame down
		for(int i = 0; i < _elements.size(); i++)
		{
			//Set animated
				_elements[i].animated = false;
			//Update the current frame
				_elements[i].currentFrame++;
				if(_elements[i].currentFrame >= _elements[i].numImages)
				{
					_elements[i].currentFrame = 0;
				}
		}
}
