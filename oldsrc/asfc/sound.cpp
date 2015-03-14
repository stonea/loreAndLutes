/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
	
	File:	sound.cpp	[Class Sound]
    By:		Andy Stone
    Desc:	This file includes the code of the ASFC_Sound object
*/

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "sound.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												ASFC_Sound Data
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//----------------------------------------------------------------------------------------- [Initlization] -
ASFC_Sound::~ASFC_Sound()
{
/*	Mix_CloseAudio();
*/
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Sound::Init()
{	
/*
    myfMusicPlaying = false;
	myfSoundOff = false;
	iAudioRate = 22050;
	iAudioFormat = AUDIO_S16SYS;
	iAudioChannels = 2;
	iAudioBuffers = 4096;
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(iAudioRate, iAudioFormat, iAudioChannels, iAudioBuffers);
	mysCurrentFile = "";
*/
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Sound::LoadMusic(string sMusicFile)
{
/*	if(myfSoundOff)
		return;

	if(!FileExist(sMusicFile))
	{	myfMusicLoaded = false;
		return;
	}

	if(mysCurrentFile == sMusicFile)
	{	myfMusicLoaded = false;
		return;
	}
	else
		mysCurrentFile = sMusicFile;
	if(myfMusicPlaying)
		StopMusic();
	myfMusicLoaded = true;
	poMusic = Mix_LoadMUS(sMusicFile.c_str());
*/
}
//---------------------------------------------------------------------------------------------- [Playing] -
void ASFC_Sound::PlayMusic()
{
/*	if(myfSoundOff)
		return;

	myfMusicPlaying = true;
	if(myfMusicLoaded)
		Mix_PlayMusic(poMusic, -1);
*/
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Sound::StopMusic()
{
/*	if(myfSoundOff)
		return;

	myfMusicPlaying = false;
	mysCurrentFile = "";
	Mix_HaltMusic();
	Mix_FreeMusic(poMusic);
*/
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Sound::TurnSoundOff()
{
/*	Mix_HaltMusic();
	Mix_FreeMusic(poMusic);
	myfSoundOff = true;
*/
}
