#include "common.h"
#include <string.h>
using namespace std;
void loadSounds();
static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;
void initSounds()
{
	memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);
	music = NULL;
	loadSounds();
}
void loadMusic(const char *filename)
{	
	Mix_VolumeMusic(128);
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}
void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}
void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}
void loadSounds()
{
	sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("res/laser1.wav");
	sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("res/laser4.wav");
	sounds[SND_PLAYER_DIE] = Mix_LoadWAV("res/DeathFlash.flac");
	sounds[SND_ALIEN_DIE] = Mix_LoadWAV("res/10 Guage Shotgun-SoundBible.com-74120584.ogg");
	sounds[SND_POINTS] = Mix_LoadWAV("res/342749__rhodesmas__notification-01.ogg");
	sounds[SND_MENU] = Mix_LoadWAV("res/vgmenuselect.wav");
	sounds[SND_BUTTON]= Mix_LoadWAV("res/keypress-001.wav");
}