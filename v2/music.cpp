#include <stdlib.h>
#include <fmod.h>
#include <string.h>

FMOD_SYSTEM *FMODSystem;
FMOD_SOUND *music;
FMOD_CHANNEL *channel;

void initFMOD()
{
    FMOD_System_Create(&FMODSystem);
    FMOD_System_Init(FMODSystem, 2, FMOD_INIT_NORMAL, NULL);
}

void playMusic(const char* name)
{
    char *completeName = (char*) calloc(strlen(name) + 5, sizeof(char)); //Size for name + .mp3\0

    strcpy(completeName, name);
    strcat(completeName, ".mp3");
    FMOD_Channel_Stop(channel);
    FMOD_System_CreateSound(FMODSystem, completeName, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &music);
    FMOD_System_PlaySound(FMODSystem, FMOD_CHANNEL_FREE, music, 0, &channel);
    FMOD_Sound_SetLoopCount(music, - 1);
    FMOD_Channel_SetVolume(channel, 0.4);
}
