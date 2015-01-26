#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fmod.h>
#include <time.h>
#include "music.hpp"
#include "menu.main.hpp"
//#include "bouton.hpp"
//#include "fonctions.hpp"
//#include "jouer.hpp"

// TODO (Cesar#1#): Faire les Highscores
// TODO (Cesar#2#): Cube piege
// TODO (Cesar#3#): Cube Bonus
// TODO (Cesar#4#): Optimiser

SDL_Surface *screen, *layer;
TTF_Font *policeMini;
TTF_Font *policeMaxi;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    putenv("SDL_VIDEO_WINDOW_POS=center");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    TTF_Init();
    initFMOD();

    screen = SDL_SetVideoMode(info->current_w, info->current_h, info->vfmt->BitsPerPixel, SDL_HWSURFACE | SDL_NOFRAME | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Clique le cube !", NULL);
    layer = SDL_CreateRGBSurface(SDL_HWSURFACE, screen->w, screen->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
    policeMini = TTF_OpenFont("Minecraftia.ttf", 20);
    policeMaxi = TTF_OpenFont("Minecraftia.ttf", 35);

    menu();

    TTF_CloseFont(policeMini);
    TTF_CloseFont(policeMaxi);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
