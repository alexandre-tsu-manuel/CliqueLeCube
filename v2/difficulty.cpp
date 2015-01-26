#include "difficulty.hpp"

void Difficulty::set(int lvl)
{
    switch(lvl)
    {
        case 1:
            this->min = 100;
            this->max = 140;
            this->time = 45;
            this->pxPerSec = 1;
            return;
        case 2:
            this->min = 70;
            this->max = 110;
            this->time = 30;
            this->pxPerSec = 2;
            return;
        case 3:
            this->min = 40;
            this->max = 70;
            this->time = 15;
            this->pxPerSec = 4;
            return;
        case 4:
            this->min = 40;
            this->max = 70;
            this->time = 10;
            this->pxPerSec = 8;
            return;
        default:
            this->set(1);
    }
}

void Difficulty::setFreePlay(bool freePlay) {this->freePlay = freePlay;}
int Difficulty::getMin() {return this->min;}
int Difficulty::getMax() {return this->max;}
int Difficulty::getTime() {return this->time;}
int Difficulty::getPxPerSec() {return this->pxPerSec;}
bool Difficulty::isFreePlay() {return this->freePlay;}
