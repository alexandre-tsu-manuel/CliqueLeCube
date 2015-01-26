#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fmod.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>
#include "bouton.hpp"
#include "fonctions.hpp"
#include "jouer.hpp"

extern SDL_Surface *ecran, *layer;

void menu()
{
    SDL_Event event;
    Difficulty difficulty;
    SDL_TimerID timer;
    Button *buttons[4];

    buttons[0] = new Button(ecran->w/2, ecran->h/2 - 120, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Jouer");
    buttons[1] = new Button(ecran->w/2, ecran->h/2 - 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Quitter");
    buttons[2] = new Button(ecran->w/2, ecran->h/2, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "DIfficulté");
    buttons[3] = new Button(ecran->w/2, ecran->h/2 + 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Jeu libre");

    difficulty.min = 70;
    difficulty.max = 110;
    difficulty.temps = 30;
    difficulty.pxPerS = 2;

    jouerMusique("Menu");

    SDL_FillRect(layer, NULL, 1);
    delColor(layer, 0, 0, 1);

    timer = SDL_AddTimer(20, moveRectangle, NULL);

    while (1)
    {
        displayMenu(buttons);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if(buttons[0]->isHover()) // Jouer
                {
                    difficulty.freePlay = false;
                    SDL_RemoveTimer(timer);
                    jouer(difficulty);
                    jouerMusique("Menu");
                    timer = SDL_AddTimer(10, moveRectangle, NULL);
                }
                else if(buttons[1]->isHover()) // Quitter
                    return;
                else if(buttons[2]->isHover()) // Difficulté
                {
                    SDL_FillRect(layer, NULL, 1);
                    delColor(layer, 0, 0, 1);
                    difficulty = setOption();
                    SDL_FillRect(layer, NULL, 1);
                    delColor(layer, 0, 0, 1);
                }
                else if(buttons[3]->isHover()) // Jeu libre
                {
                    difficulty.freePlay = true;
                    SDL_RemoveTimer(timer);
                    jouer(difficulty);
                    timer = SDL_AddTimer(10, moveRectangle, NULL);
                    jouerMusique("Menu");
                }
                break;
        }
    }
}

Difficulty setOption()
{
    Button *buttons[4];
    SDL_Event event;
    Difficulty choice;

    buttons[0] = new Button(ecran->w/2, ecran->h/2 - 120, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Facile");
    buttons[1] = new Button(ecran->w/2, ecran->h/2 - 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Moyen");
    buttons[2] = new Button(ecran->w/2, ecran->h/2, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "DIfficile");
    buttons[3] = new Button(ecran->w/2, ecran->h/2 + 60, rgbToColor(207, 207, 207), rgbToColor(0, 0, 0), rgbToColor(125, 124, 124), "Hardcore");

    while (1)
    {
        displayMenu(buttons);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if(buttons[0]->isHover())
                {
                    choice.min = 100;
                    choice.max = 140;
                    choice.temps = 45;
                    choice.pxPerS = 1;
                    return choice;
                }
                else if(buttons[1]->isHover())
                {
                    choice.min = 70;
                    choice.max = 110;
                    choice.temps = 30;
                    choice.pxPerS = 2;
                    return choice;
                }
                else if(buttons[2]->isHover())
                {
                    choice.min = 40;
                    choice.max = 70;
                    choice.temps = 15;
                    choice.pxPerS = 4;
                    return choice;
                }
                else if(buttons[3]->isHover())
                {
                    choice.min = 40;
                    choice.max = 70;
                    choice.temps = 10;
                    choice.pxPerS = 8;
                    return choice;
                }
                break;
        }
    }
}

void jouer(Difficulty difficulty)
{
    srand(time(NULL));
    jouerMusique("Jouer");

    int actualColorR = rand() % 255, actualColorV = rand() % 255,actualColorB = rand() % 255;
    int continuer = 1;
    int sizex = rand () % (difficulty.max - difficulty.min + 1) + difficulty.min;
    int sizey = rand () % (difficulty.max - difficulty.min + 1) + difficulty.min;
    int tempsRestant, tempsTotal;
    int score = 0;
    int oldTicks;
    tempsTotal = SDL_GetTicks() + difficulty.temps*1000;
    bool directionHaut = 0, directionDroite = 1;

    SDL_Surface *rectangle = NULL;
    SDL_Rect positionRectangle;
    SDL_Event event;
    SDL_Color couleurBlanche = {255,255,255,0};

    positionRectangle.x = rand() % ecran->w - sizex;
    positionRectangle.y = rand() % ecran->h - sizey;

    TTF_Font *policeMini = TTF_OpenFont("game_over.ttf", 50);

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, sizex, sizey, 32, 0, 0, 0, 0);

    color(rectangle, actualColorR, actualColorV, actualColorB);

    while (continuer)
    {
        SDL_PollEvent(&event);
        SDL_Delay(10);
        if(difficulty.freePlay == false)
            tempsRestant = (tempsTotal - SDL_GetTicks())/100;
        else
            tempsRestant = 1000;

        color(ecran,tempsRestant*100/(tempsTotal/100),tempsRestant*100/(tempsTotal/100),tempsRestant*100/(tempsTotal/100));

        switch(event.type)
        {
        case SDL_MOUSEMOTION:
            if(checkZone(event.motion.x, event.motion.y, positionRectangle,sizex,sizey))
            {
                color(rectangle, (int)actualColorR + ((255 - actualColorR)/6)*5, (int)actualColorV + ((255 - actualColorV)/6)*5, (int)actualColorB + ((255 - actualColorB)/6)*5);
            }
            else
            {
                color(rectangle, actualColorR, actualColorV, actualColorB);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(checkZone(event.button.x, event.button.y, positionRectangle,sizex,sizey))
            {
                SDL_FreeSurface(rectangle);
                score++;
                actualColorR = rand () % (255 - 30 + 1) + 30;
                actualColorV = rand () % (255 - 30 + 1) + 30;
                actualColorB = rand () % (255 - 30 + 1) + 30;

                sizex = rand () % (difficulty.max - difficulty.min + 1) + difficulty.min;
                sizey = rand () % (difficulty.max - difficulty.min + 1) + difficulty.min;

                positionRectangle.x = rand() % ecran->w - sizex;
                positionRectangle.y = rand() % ecran->h - sizey;

                rectangle = SDL_CreateRGBSurface(SDL_SWSURFACE, sizex, sizey, 32, 0, 0, 0, 0);
                color(rectangle, actualColorR, actualColorV, actualColorB);
                SDL_BlitSurface(rectangle,NULL, ecran, &positionRectangle);
                SDL_WarpMouse(event.button.x,event.button.y+1);

                directionDroite = rand() % 2;
                directionHaut = rand() %2;
            }
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                tempsRestant = 0;
            break;
        case SDL_QUIT:
            continuer = 0;
            break;
        }


        if(positionRectangle.x + sizex >= ecran->w)
            directionDroite = 0;
        if(positionRectangle.x <= 0)
            directionDroite = 1;
        if(positionRectangle.y + sizey >= ecran->h)
            directionHaut = 1;
        if(positionRectangle.y <= 0)
            directionHaut = 0;

        if(directionDroite)
            positionRectangle.x = positionRectangle.x + difficulty.pxPerS;
        if(directionHaut)
            positionRectangle.y = positionRectangle.y - difficulty.pxPerS;
        if(!directionDroite)
            positionRectangle.x = positionRectangle.x - difficulty.pxPerS;
        if(!directionHaut)
            positionRectangle.y = positionRectangle.y + difficulty.pxPerS;

        SDL_BlitSurface(rectangle,NULL, ecran, &positionRectangle);
        if(!difficulty.freePlay)
            write(couleurBlanche,10,50,false, "Temps restant : %d.%d s", tempsRestant/10,tempsRestant - tempsRestant/10*10);
        write(couleurBlanche,10,10,false, "Score : %d", score);

        afficherFps(SDL_GetTicks(),oldTicks);
        oldTicks = SDL_GetTicks();
        SDL_Flip(ecran);
        if(tempsRestant == 0)
        {
            write(couleurBlanche,(ecran->w/2)-30,(ecran->h/2)-20,false, "Score : %d", score);
            SDL_Flip(ecran);
            pause();
            continuer = 0;
        }
    }

    SDL_FreeSurface(rectangle);
    TTF_CloseFont(policeMini);
}
