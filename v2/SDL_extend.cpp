#include <SDL/SDL.h>

extern SDL_Surface *screen;

SDL_Color rgbToColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r,g,b};
    return color;
}

void advancedBlit(SDL_Surface* src, SDL_Rect* coordonnes)
{
    SDL_SetClipRect(src, coordonnes);
    SDL_BlitSurface(src, NULL, screen, coordonnes);
    SDL_SetClipRect(screen, NULL);
}
