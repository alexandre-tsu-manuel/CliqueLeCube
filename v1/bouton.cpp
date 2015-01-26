#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "bouton.hpp"

extern TTF_Font *policeMaxi;
extern SDL_Surface *layer;

Button::Button(int x, int y, SDL_Color foregrnd, SDL_Color foregrndHover, SDL_Color backgrnd, const char* text)
{
    SDL_Surface *textSurf;
    SDL_Rect pos;

    pos.x = 10;
    pos.y = 0;

    textSurf = TTF_RenderText_Blended(policeMaxi, text, foregrnd);
    this->pos.h = textSurf->h;
    this->pos.w = textSurf->w;
    this->normal = SDL_CreateRGBSurface(SDL_HWSURFACE, textSurf->w + pos.x * 2, textSurf->h + pos.y * 2, 32, 0, 0, 0, 0);
    SDL_FillRect(this->normal, NULL, SDL_MapRGB(this->normal->format, backgrnd.r, backgrnd.g, backgrnd.b));
    SDL_BlitSurface(textSurf, NULL, this->normal, &pos);
    SDL_FreeSurface(textSurf);

    textSurf = TTF_RenderText_Shaded(policeMaxi, text, foregrndHover, backgrnd);
    this->hover = SDL_CreateRGBSurface(SDL_HWSURFACE, textSurf->w + pos.x * 2, textSurf->h + pos.y * 2, 32, 0, 0, 0, 0);
    SDL_FillRect(this->hover, NULL, SDL_MapRGB(this->hover->format, backgrnd.r, backgrnd.g, backgrnd.b));
    SDL_BlitSurface(textSurf, NULL, this->hover, &pos);
    SDL_FreeSurface(textSurf);

    this->pos.x = x - this->pos.w / 2;
    this->pos.y = y - this->pos.h / 2;
}

void Button::free()
{
    SDL_FreeSurface(normal);
    SDL_FreeSurface(hover);
}

bool Button::isHover()
{
    int x, y;

    SDL_GetMouseState(&x, &y);
    return (x >= this->pos.x && y >= this->pos.y && x <= this->pos.x + this->pos.w && y <= this->pos.y + this->pos.h);
}

void Button::display()
{
    if (this->isHover())
        SDL_BlitSurface(this->hover, NULL, layer, &this->pos);
    else
        SDL_BlitSurface(this->normal, NULL, layer, &this->pos);
}
