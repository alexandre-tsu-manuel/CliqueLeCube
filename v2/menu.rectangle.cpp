#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include "SDL_extend.hpp"
#include "menu.rectangle.hpp"

extern SDL_Surface *screen, *layer;

int angle = 0;
int rotateAngle = 0;

Uint32 moveRectangle(Uint32 interval, void* nothing)
{
    SDL_Surface *rectangle, *rotatedRectangle;
    SDL_Rect pos;

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 48, 48, 48));
    SDL_BlitSurface(layer, NULL, screen, NULL);

    angle = angle >= 360 ? 1 : angle + 1;
    rotateAngle = rotateAngle <= 0 ? 355 : rotateAngle - 5;

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
    color(rectangle, 255, 77, 77);
    pos = trajectoireCirculaire(300, angle);

    rotatedRectangle = rotozoomSurface(rectangle, rotateAngle, 1.0, 10);
    pos.x += (screen->w - rotatedRectangle->w) / 2;
    pos.y += (screen->h - rotatedRectangle->h) / 2;
    delColor(rotatedRectangle, 0, 0, 0);
    advancedBlit(rotatedRectangle, &pos);

    SDL_FreeSurface(rotatedRectangle);
    SDL_FreeSurface(rectangle);

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
    color(rectangle, 77, 255, 77);
    pos = trajectoireCirculaire(300, (angle + 180) % 360);

    rotatedRectangle = rotozoomSurface(rectangle, rotateAngle, 1.0, 10);
    pos.x += (screen->w - rotatedRectangle->w) / 2;
    pos.y += (screen->h - rotatedRectangle->h) / 2;
    delColor(rotatedRectangle, 0, 0, 0);
    advancedBlit(rotatedRectangle, &pos);

    SDL_FreeSurface(rotatedRectangle);
    SDL_FreeSurface(rectangle);

    SDL_Flip(screen);

    return interval;
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

void testTrajectoire()
{
    SDL_Rect milieu;
    milieu.x = screen->w/2;
    milieu.y = screen->h/2;
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
