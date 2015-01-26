#ifndef GFX_HPP_INCLUDED
    #define GFX_HPP_INCLUDED

    unsigned long SDL_GetPixel(SDL_Surface *surface, int x, int y);
    void SDL_PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel);
    unsigned long Color(unsigned char R,unsigned char V,unsigned char B,unsigned char A);
    void Line(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur);
    void HorizLine(SDL_Surface* surf,int x1,int y1, int x2,unsigned long couleur);
    void VertLine(SDL_Surface* surf,int x1,int y1, int y2,unsigned long couleur);
    void Box(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur);
    void Bar(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur);
    void Circle(SDL_Surface* surf,int x1,int y1, int radius,unsigned long couleur);
    void Disc(SDL_Surface* surf,int x1,int y1, int radius,unsigned long couleur);

#endif // GFX_HPP_INCLUDED
