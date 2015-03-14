/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			shader.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "shader.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LRUN_Shader
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LRUN_Shader::LRUN_Shader()
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
//Load shade patterns
void LRUN_Shader::LoadShades(string sFile)
{		ifstream oFile(sFile.c_str(), ios::binary);
		string 	sFileType;
		int	   	iVersionNumber;
		int		iNumShades;
		char	c;
	
	//~.shade 0~		File type and version number
		oFile >> sFileType;
  		oFile >> iVersionNumber;
  	
    //If we have a valid version	
		if(ValidVersionNum("LRUN_Shader::Load 000, Invalid file type or version", sFileType,
			iVersionNumber))
		{	//%Width%, %Height%, %CenterX%, %CenterY%, %Num o Shades%
				oFile >> myiWidth;
    			oFile >> myiHeight;
       			oFile >> myiCenterX;
          		oFile >> myiCenterY;
          		oFile >> iNumShades;
      			lShades.Resize(iNumShades);
			
			//Loop for # of shades
				for(int i = 0; i < iNumShades; i++)
				{	//Size this shade
						lShades[i].Resize(myiWidth, myiHeight);
    
    				//Loop for height and width
						for(int iY = 0; iY < myiHeight; iY++)
							for(int iX = 0; iX < myiWidth; iX++)
							{	//Read in a char
									oFile >> c;
									
								//If its X shade true else false
									if(c == 'X' || c == 'x')
										lShades[i][iX][iY] = true;
									else
										lShades[i][iX][iY] = false;
							}
				}
		}
}		
//---------------------------------------------------------------------------------------------- [Shade] -
//Put the qualities of shade pattern iPattern on matrix oMatrix with the true\false condition fStyle
void LRUN_Shader::Shade(ASFC_Matrix<bool> &oMatrix, C_i3(iFromX, iFromY, iPattern), const bool fStyle)
{	//Vars
		int iMatX, iMatY;

	//Loop through all the elements on this shade pattern
		for(int iY = 0; iY < myiHeight; iY++)
	  	{	for(int iX = 0; iX < myiWidth; iX++)
	  		{	//If this is a shade region on the pattern
	  				if(lShades[iPattern][iX][iY])
	  				{	//Determine the real X, Y to place on the matrix
       						iMatX = iX - myiCenterX + iFromX;
       						iMatY = iY - myiCenterY + iFromY;
       						
        				//Shade here (if legal)
	  						if(iMatX >= 0 && iMatY >= 0 && iMatX < myiWidth && iMatY < myiHeight)
	  						{	oMatrix[iMatX][iMatY] = fStyle;
	  						}
	  				}
	  		}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LRUN_Shader::GrabLight(C_i4(iTopLeftX, iTopLeftY, iPlayerX, iPlayerY), LL_TerrainMap& oMap, 
							ASFC_Matrix<bool> &lLight, bool AddTorchLight)
{

	//Const
		const int EXTRA_CHECK = 20;	//How many tiles (in each direction) to check for off screen light on
	//Vars
		int iCenterX, iCenterY;
		int tiHour;
		
	//Size the return matrix (figure out the center coods for this matrix)
		lLight.Resize(PLAYFIELD_TILEWIDTH, PLAYFIELD_TILEHEIGHT);
		iCenterX = iPlayerX - iTopLeftX;
		iCenterY = iPlayerY - iTopLeftY;

	//Set all true for the default vals in the matrix
		for(int iY = 0; iY < lLight.Height(); iY++)
			for(int iX = 0; iX < lLight.Width(); iX++)
				lLight[iX][iY] = false;
				
	//Shade for the current time
		tiHour = mypoGameClock->Hour();
			 if(tiHour >= 9 && tiHour <= 15)		Shade(lLight, iCenterX, iCenterY, SHADE_DAY_1, true);
		else if(tiHour == 8 || tiHour == 16)		Shade(lLight, iCenterX, iCenterY, SHADE_DAY_2, true);
		else if(tiHour == 7 || tiHour == 17)		Shade(lLight, iCenterX, iCenterY, SHADE_DAY_3, true);
		else if(tiHour == 6 || tiHour == 18)		Shade(lLight, iCenterX, iCenterY, SHADE_DAY_4, true);
		else if(tiHour == 5 || tiHour == 19)		Shade(lLight, iCenterX, iCenterY, SHADE_DAY_5, true);
		else if(tiHour == 4 || tiHour == 20)		Shade(lLight, iCenterX, iCenterY, SHADE_DAY_6, true);
		else if(tiHour == 3 || tiHour == 21)		Shade(lLight, iCenterX, iCenterY, SHADE_DAY_7, true);
		else										Shade(lLight, iCenterX, iCenterY, SHADE_DAY_8, true);
		
	//Add torch light
		if(AddTorchLight)
		{	Shade(lLight, iCenterX, iCenterY, SHADE_TORCH, true);
		}

	//Now search for torches and lighthouses
		for(int iY = 0 - EXTRA_CHECK; iY < lLight.Height() + EXTRA_CHECK; iY++)
			for(int iX = 0 - EXTRA_CHECK; iX < lLight.Width()+ EXTRA_CHECK; iX++)
			{	//If tis a legal tile
					if(	iTopLeftX+iX >= 0 && iTopLeftX+iX < oMap.Width() & iTopLeftY+iY >= 0 &&
						iTopLeftY+iY < oMap.Height())
					{	//If there's a lighthouse here
	 					if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iY).LightEffect() == LIGHTEFFECT_LIGHTHOUSE)
 						{		 if(myiLighthouseFrame == 0)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_1, true);
	 						else if(myiLighthouseFrame == 1)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_2, true);
	 						else if(myiLighthouseFrame == 2)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_3, true);
	 						else if(myiLighthouseFrame == 3)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_4, true);
	 						else if(myiLighthouseFrame == 4)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_5, true);
	 						else if(myiLighthouseFrame == 5)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_6, true);
		 					else if(myiLighthouseFrame == 6)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_7, true);
		 					else if(myiLighthouseFrame == 7)	Shade(lLight, iX, iY, SHADE_LIGHTHOUSE_8, true);
 						}
 						//If theres some kindof torch here do the propa' shadin'
						else if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iY).LightEffect() == LIGHTEFFECT_ILLUMINATE)
 							Shade(lLight, iX, iY, SHADE_ILLUMINATE, true);
 						else if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iY).LightEffect() == LIGHTEFFECT_SMALL_TORCH)
 							Shade(lLight, iX, iY, SHADE_TORCH_SMALL, true);
						else if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iY).LightEffect() == LIGHTEFFECT_TORCH)
							Shade(lLight, iX, iY, SHADE_TORCH, true);
					}
			}
		
	//Now figure out the lighting effects from iX, iY
		//Check left of iX, iY
			for(int iX = iCenterX-1; iX > 0; iX--)
			{	//If there's a blocked terrain here shade to the west		
 					if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iCenterY).LightEffect() == LIGHTEFFECT_BLOCK)
 						Shade(lLight, iX, iCenterY, SHADE_WEST, false);
			}
		//Check right of iX, iY
			for(int iX = iCenterX+1; iX < lLight.Width(); iX++)
			{	//If there's a blocked terrain here shade to the east
 					if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iCenterY).LightEffect() == LIGHTEFFECT_BLOCK)
						Shade(lLight, iX, iCenterY, SHADE_EAST, false);
			}
		//Check above iX, iY
			for(int iY = iCenterY-1; iY > 0; iY--)
			{	for(int iX = 0; iX < lLight.Width(); iX++)
				{	//If there's a blocked terrain here    
	    				if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iY).LightEffect() == LIGHTEFFECT_BLOCK)
	 					{	//If its north-west
	 							if(iX < iCenterX)
	 								Shade(lLight, iX, iY, SHADE_NORTH_WEST, false);
							//If its straight north
								else if(iX == iCenterX)
									Shade(lLight, iX, iY, SHADE_NORTH, false);
							//If its north east
								else
									Shade(lLight, iX, iY, SHADE_NORTH_EAST, false);
						}
				}
			}
		//Check above iX, iY
			for(int iY = iCenterY+1; iY < lLight.Height(); iY++)
			{	for(int iX = 0; iX < lLight.Width(); iX++)
				{	//If there's a blocked terrain here
	    				if(oMap.GetTerrain(iTopLeftX+iX, iTopLeftY+iY).LightEffect() == LIGHTEFFECT_BLOCK)
	 					{	//If its south-west
	 							if(iX < iCenterX)
	 								Shade(lLight, iX, iY, SHADE_SOUTH_WEST, false);
							//If its straight south
								else if(iX == iCenterX)
									Shade(lLight, iX, iY, SHADE_SOUTH, false);
							//If its south east
								else
									Shade(lLight, iX, iY, SHADE_SOUTH_EAST, false);
						}
				}
			}
						
	//Increment our lighthouse frame counter
		if(++myiLighthouseFrame > LIGHTHOUSE_FRAMES)
			myiLighthouseFrame = 0;
}
//P---------------------------------------------------------------------------------------- [Debugging] -P
//Makes sure iVersionNumber is the correct version number for a .shade file, if it is return true
bool LRUN_Shader::ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum))
{	//Const
		const string REQUIRED_FILE_TYPE 		= ".shade";	//Holds the required file type
		const int	 REQUIRED_VERSION_NUMBER	= 0;		//Holds the required version number
		
	//If invalid
		if(sFileType != REQUIRED_FILE_TYPE || iVersionNum != REQUIRED_VERSION_NUMBER)
		{	cout << sErrorCode << endl;
			cout << "--[File Type]-->               "  << sFileType   				<< endl;
			cout << "--[Required File Type]-->      "  << REQUIRED_FILE_TYPE   		<< endl;
			cout << "--[Version Number]-->          "  << iVersionNum   			<< endl;
			cout << "--[Required Version Number]--> "  << REQUIRED_VERSION_NUMBER   << endl;
			return false;
		}
		else
			return true;
}
