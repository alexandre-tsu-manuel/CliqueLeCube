#ifndef FONCTIONS_HPP_INCLUDED
    #define FONCTIONS_HPP_INCLUDED

    typedef struct Difficulty
    {
        int min, max;
        int temps;
        int pxPerS;
        bool freePlay;
    } Difficulty;

    #define color(X,R,G,B) SDL_FillRect(X, NULL, SDL_MapRGB(X->format, R, G, B));
    #define xyToRect(x, y) (SDL_Rect){(Sint16)x, (Sint16)y, 0, 0}

    void jouerMusique(const char* chaine);
    void pause();
    void delColor(SDL_Surface *image, int r, int v, int b);
    void advancedBlit(SDL_Surface* src, SDL_Rect* coordonnes);
    void testTrajectoire();
    Uint32 moveRectangle(Uint32 interval, void* nothing);
    void displayMenu(Button *buttons[]);
    SDL_Rect write(SDL_Color couleur, int x, int y, bool big, const char* text, ...);
    SDL_Color rgbToColor(Uint8 r, Uint8 g, Uint8 b);

    void initFMOD();
    SDL_Rect trajectoireCirculaire(double rayon, double angle);
    void afficherFps(int actualTicks, int oldTicks);
    int checkZone(int x,int y,SDL_Rect pos,int w,int h);

#endif
