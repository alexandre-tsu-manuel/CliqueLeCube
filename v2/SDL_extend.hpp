#ifndef HPP_SDL_EXTEND
    #define HPP_SDL_EXTEND

    #define color(x,r,g,b) SDL_FillRect(x, NULL, SDL_MapRGB(x->format, r, g, b))
    #define delColor(x, r, g, b) SDL_SetColorKey(x, SDL_SRCCOLORKEY, SDL_MapRGB(x->format, r, g, b));

    SDL_Color rgbToColor(Uint8 r, Uint8 g, Uint8 b);
    void advancedBlit(SDL_Surface* src, SDL_Rect* coordonnes);

#endif
