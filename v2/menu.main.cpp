#include <SDL/SDL.h>
#include "music.hpp"
#include "SDL_extend.hpp"
#include "difficulty.hpp"
#include "menu.button.hpp"
#include "menu.rectangle.hpp"
#include "menu.main.hpp"

extern SDL_Surface *screen, *layer;

void menu()
{
    SDL_Event event;
    Difficulty *difficulty;
    SDL_TimerID timer;
    Button *buttons[4];

    buttons[0] = new Button(screen->w/2, screen->h/2 - 120, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Jouer");
    buttons[1] = new Button(screen->w/2, screen->h/2 - 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Quitter");
    buttons[2] = new Button(screen->w/2, screen->h/2, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Difficulté");
    buttons[3] = new Button(screen->w/2, screen->h/2 + 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Jeu libre");

    difficulty.set(2);

    playMusic("Menu");

    SDL_FillRect(layer, NULL, 1);
    delColor(layer, 0, 0, 1);

    timer = SDL_AddTimer(20, moveRectangle, NULL);

    while (1)
    {
        displayMenu(buttons);
        SDL_WaitEvent(&event);
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(buttons[0]->isHover()) // Jouer
            {
                difficulty.setFreePlay(false);
                SDL_RemoveTimer(timer);
                //jouer(difficulty);
                playMusic("Menu");
                timer = SDL_AddTimer(10, moveRectangle, NULL);
            }
            else if(buttons[1]->isHover()) // Quitter
                return;
            else if(buttons[2]->isHover()) // Difficulté
            {
                setDifficulty(difficulty);
                SDL_FillRect(layer, NULL, 1);
                delColor(layer, 0, 0, 1);
            }
            else if(buttons[3]->isHover()) // Jeu libre
            {
                difficulty.setFreePlay(true);
                SDL_RemoveTimer(timer);
                //jouer(difficulty);
                timer = SDL_AddTimer(10, moveRectangle, NULL);
                playMusic("Menu");
            }
        }
    }
}

void setDifficulty(Difficulty* difficulty)
{
    Button *buttons[4];
    SDL_Event event;
    Difficulty choice;

    buttons[0] = new Button(screen->w/2, screen->h/2 - 120, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Facile");
    buttons[1] = new Button(screen->w/2, screen->h/2 - 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Moyen");
    buttons[2] = new Button(screen->w/2, screen->h/2, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Difficile");
    buttons[3] = new Button(screen->w/2, screen->h/2 + 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Hardcore");

    SDL_FillRect(layer, NULL, 1);
    delColor(layer, 0, 0, 1);

    while (1)
    {
        displayMenu(buttons);
        SDL_WaitEvent(&event);
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            for (i = 0 ; i < 4 ; i++)
            {
                if (buttons[i]->isHover())
                {
                    difficulty->set(i + 1);
                    return;
                }
            }
        }
    }
}

void displayMenu(Button *buttons[])
{
    for (int i = 0 ; i < 4 ; i++)
        buttons[i]->display();
}
