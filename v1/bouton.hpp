#ifndef BOUTON_HPP_INCLUDED
    #define BOUTON_HPP_INCLUDED

    class Button
    {
        private:
            SDL_Rect pos;
            SDL_Surface *normal, *hover;
        public:
            Button(int x, int y, SDL_Color foregrnd, SDL_Color foregrndHover, SDL_Color backgrnd, const char* text);
            void free();
            bool isHover();
            void display();
    };

#endif // BOUTON_HPP_INCLUDED
