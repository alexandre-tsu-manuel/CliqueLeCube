#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <time.h>
#include <fmod.h>
#include <SDL/SDL_rotozoom.h>
#include <pthread.h>
#include "tout.hpp"

FMOD_SYSTEM *systeme;
FMOD_SOUND *musique;
FMOD_CHANNEL *channel;

extern SDL_Surface *ecran, *layer;
extern TTF_Font *policeMini;
extern TTF_Font *policeMaxi;

int angle = 0;
int rotateAngle = 0;

void jouerMusique(const char* chaine)
{
    FMOD_Channel_Stop(channel);
    if(!strcmp(chaine, "Jouer"))
        FMOD_System_CreateSound(systeme, "Jouer.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    else if (!strcmp(chaine, "Menu"))
        FMOD_System_CreateSound(systeme, "Menu.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, musique, 0, &channel);
    FMOD_Sound_SetLoopCount(musique, - 1);
    FMOD_Channel_SetVolume(channel,1);
}

void pause()
{
    SDL_Event event;

    while (SDL_WaitEvent(&event))
        if (event.type == SDL_KEYDOWN)
            break;
}

void delColor(SDL_Surface *picture, int r, int v, int b)
{
    SDL_SetColorKey(picture, SDL_SRCCOLORKEY, SDL_MapRGB(picture->format, r, v, b));
}

void advancedBlit(SDL_Surface* src, SDL_Rect* coordonnes)
{
    SDL_SetClipRect(src, coordonnes);
    SDL_BlitSurface(src, NULL, ecran, coordonnes);
    SDL_SetClipRect(ecran, NULL);
}

void testTrajectoire()
{
    SDL_Rect milieu;
    milieu.x = ecran->w/2;
    milieu.y = ecran->h/2;
    SDL_Rect positionPoint[360];
    SDL_Surface* point[360];
    for(int i = 0;i<= 360;i+=1)
    {
        point[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,2,2,32,0,0,0,0);
        color(point[i], 150,150,150);
        positionPoint[i] = trajectoireCirculaire(300,i);
        positionPoint[i].x +=milieu.x;
        positionPoint[i].y +=milieu.y;
        advancedBlit(point[i],&positionPoint[i]);
        SDL_FreeSurface(point[i]);
    }
}

Uint32 moveRectangle(Uint32 interval, void* nothing)
{
    SDL_Surface *rectangle, *rotatedRectangle;
    SDL_Rect pos;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 48, 48, 48));
    SDL_BlitSurface(layer, NULL, ecran, NULL);

    angle = angle >= 360 ? 1 : angle + 1;
    rotateAngle = rotateAngle <= 0 ? 355 : rotateAngle - 5;

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
    color(rectangle, 255, 77, 77);
    pos = trajectoireCirculaire(300, angle);

    rotatedRectangle = rotozoomSurface(rectangle, rotateAngle, 1.0, 10);
    pos.x += (ecran->w - rotatedRectangle->w) / 2;
    pos.y += (ecran->h - rotatedRectangle->h) / 2;
    delColor(rotatedRectangle, 0, 0, 0);
    advancedBlit(rotatedRectangle, &pos);

    SDL_FreeSurface(rotatedRectangle);
    SDL_FreeSurface(rectangle);

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
    color(rectangle, 77, 255, 77);
    pos = trajectoireCirculaire(300, (angle + 180) % 360);

    rotatedRectangle = rotozoomSurface(rectangle, rotateAngle, 1.0, 10);
    pos.x += (ecran->w - rotatedRectangle->w) / 2;
    pos.y += (ecran->h - rotatedRectangle->h) / 2;
    delColor(rotatedRectangle, 0, 0, 0);
    advancedBlit(rotatedRectangle, &pos);

    SDL_FreeSurface(rotatedRectangle);
    SDL_FreeSurface(rectangle);

    SDL_Flip(ecran);

    return interval;
}

void displayMenu(Button *buttons[])
{
    for (int i = 0 ; i < 4 ; i++)
        buttons[i]->display();
}

SDL_Rect write(SDL_Color couleur, int x, int y, bool big, const char* text, ...)
{
    SDL_Surface* texte;
    SDL_Rect info;
    char buffer[500];
    SDL_Rect position;
    va_list args;
    va_start(args,text);
    vsprintf(buffer,text,args);
    va_end(args);
    if (big)
        texte = TTF_RenderText_Blended(policeMaxi, buffer, couleur);
    else
        texte = TTF_RenderText_Blended(policeMini, buffer, couleur);
    position.x = x;
    position.y = y;
    info.x = x;
    info.y = y;
    info.h = texte->h;
    info.w = texte->w;

    advancedBlit(texte, &position);
    SDL_FreeSurface(texte);

    return info;
}

SDL_Color rgbToColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r,g,b};
    return color;
}


void initFMOD()
{
    FMOD_System_Create(&systeme);
    FMOD_System_Init(systeme, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_Sound_SetLoopCount(musique, -1);
}

SDL_Rect trajectoireCirculaire(double rayon, double angle)
{
    SDL_Rect position;
    double x = sin(angle*(M_PI/180))*rayon;
    double y = cos(angle*(M_PI/180))*rayon;
    position.x = (int)x;
    position.y = (int)y;
    return position;
}

void afficherFps(int actualTicks, int oldTicks)
{
    int fps = 1000/(actualTicks - oldTicks);
    write(rgbToColor(255,255,255),ecran->w - 50,10, false, "%d",fps);
}

int checkZone(int x,int y,SDL_Rect pos,int w,int h)
{
    return (x >= pos.x && y >= pos.y && x <= pos.x + w && y <= pos.y + h);
}
