#ifndef HPP_DIFFICULTY
    #define HPP_DIFFICULTY

    class Difficulty
    {
        private:
            int min, max;
            int time;
            int pxPerSec;
            bool freePlay;
        public:
            void set(int lvl);
            void setFreePlay(bool freePlay);
            int getMin();
            int getMax();
            int getTime();
            int getPxPerSec();
            bool isFreePlay();
    } Difficulty;

#endif
