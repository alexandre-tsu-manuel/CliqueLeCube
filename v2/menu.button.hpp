#ifndef HPP_MENU_BUTTON
    #define HPP_MENU_BUTTON

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

#endif
