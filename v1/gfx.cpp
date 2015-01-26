#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fmod.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>

#include "tout.hpp"

extern SDL_Surface *ecran;

unsigned long SDL_GetPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    unsigned char *p = (unsigned char*)surface->pixels + y * surface->pitch + x * bpp;
    if (bpp==4)
        return *(unsigned long *)p;
    return 0;
}

void SDL_PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel)
{
    int bpp = surface->format->BytesPerPixel;
    unsigned char *p = (unsigned char *)surface->pixels + y * surface->pitch + x * bpp;
    if (bpp==4)
        *(unsigned long*)p = pixel;
}

unsigned long Color(unsigned char R,unsigned char V,unsigned char B,unsigned char A)
{
    return 65536*R + 256*V + B + 16777216 * A;
}

void Line(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur)  // Bresenham : ligne quelconque
{
  int x,y;
  int Dx,Dy;
  int xincr,yincr;
  int erreur;
  int i;

  Dx = abs(x2-x1);
  Dy = abs(y2-y1);
  if(x1<x2)
    xincr = 1;
  else
    xincr = -1;
  if(y1<y2)
    yincr = 1;
  else
    yincr = -1;

  x = x1;
  y = y1;
  if(Dx>Dy)
    {
      erreur = Dx/2;
      for(i=0;i<Dx;i++)
        {
          x += xincr;
          erreur += Dy;
          if(erreur>Dx)
            {
              erreur -= Dx;
              y += yincr;
            }
        SDL_PutPixel(surf,x, y,couleur);
        }
    }
  else
    {
      erreur = Dy/2;
      for(i=0;i<Dy;i++)
        {
          y += yincr;
          erreur += Dx;
          if(erreur>Dy)
            {
              erreur -= Dy;
              x += xincr;
            }
        SDL_PutPixel(surf,x, y,couleur);
        }
    }
}

void HorizLine(SDL_Surface* surf,int x1,int y1, int x2,unsigned long couleur)  // a noter que Line gere ça aussi
{
    int i;
    for(i=x1;i<=x2;i++)
        SDL_PutPixel(surf,i,y1,couleur);
}

void VertLine(SDL_Surface* surf,int x1,int y1, int y2,unsigned long couleur)  // a noter que Line gere ça aussi
{
    int i;
    for(i=y1;i<=y2;i++)
        SDL_PutPixel(surf,x1,i,couleur);
}

void Box(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur)
{
    HorizLine(surf,x1,y1,x2,couleur);
    HorizLine(surf,x1,y2,x2,couleur);
    VertLine(surf,x1,y1,y2,couleur);
    VertLine(surf,x2,y1,y2,couleur);
}

void Bar(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur)
{
    int i,j;
    for(i=x1;i<=x2;i++)
        for(j=y1;j<=y2;j++)
            SDL_PutPixel(surf,i,j,couleur);
}


void Circle(SDL_Surface* surf,int x1,int y1, int radius,unsigned long couleur)
{
    // inspiré de http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/bresenham.html
    int d,x,y,x2m1,max;
    y=radius;
    d= -radius;
    x2m1= -1;
    max = (int)(radius/sqrt(2.0));
    for(x=0;x<=max;x++)
    {
        x2m1 += 2;
        d+= x2m1;
        if (d>=0)
        {
            y--;
            d -= (y<<1);
        }
        SDL_PutPixel(surf,x1+x,y1+y,couleur);
        SDL_PutPixel(surf,x1-x,y1+y,couleur);
        SDL_PutPixel(surf,x1+x,y1-y,couleur);
        SDL_PutPixel(surf,x1-x,y1-y,couleur);
        SDL_PutPixel(surf,x1+y,y1+x,couleur);
        SDL_PutPixel(surf,x1-y,y1+x,couleur);
        SDL_PutPixel(surf,x1+y,y1-x,couleur);
        SDL_PutPixel(surf,x1-y,y1-x,couleur);
    }

}

void Disc(SDL_Surface* surf,int x1,int y1, int radius,unsigned long couleur)
{
    int x,y,d,stepd,max;
    y=radius;
    d= -radius;
    stepd= -1;
    max = (int)(radius/sqrt(2.0));
    for(x=0;x<=max;x++)
    {
        stepd += 2;
        d+= stepd;
        if (d>=0)
        {
            y--;
            d -= (y<<1);  /* Must do this AFTER y-- */
        }
        HorizLine(surf,x1-x,y1+y,x1+x,couleur);
        HorizLine(surf,x1-x,y1-y,x1+x,couleur);
        HorizLine(surf,x1-y,y1+x,x1+y,couleur);
        HorizLine(surf,x1-y,y1-x,x1+y,couleur);
    }

}
void gradient(SDL_Surface* ecran,SDL_Rect position, SDL_Color startColor, SDL_Color endColor, int direction) // direction : 1 -> haut 2 -> droite 3 -> bas 4 -> gauche
{
    int pasR,pasG,pasB; // pasR signifie pas à pas rouge
    SDL_Color couleur = startColor;
    int i;
    pasR = (int)round((startColor.r - endColor.r) / position.h);
    pasG = (int)round((startColor.g - endColor.g) / position.h);
    pasB = (int)round((startColor.b - endColor.b) / position.h);
    for(i = 0;i < position.h ;i++)
    {
        couleur.r = startColor.r + pasR * ( i - position.h);
        couleur.g = startColor.g + pasG * ( i - position.h);
        couleur.b = startColor.b + pasB * ( i - position.h);
        Line(ecran,position.x,position.y + position.h - i,position.x + position.w,position.y + position.h - i, Color(couleur.r,couleur.g,couleur.b , 1));
    }
}
