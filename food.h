#ifndef FOOD_H
#define FOOD_H
#include <Windows.h>
#include <cstdlib>
#include <ctime>


class Food {
    private:
    COORD pos;

    public:
        Food();
        void gerarComida(int);
        COORD getPos();
};

#endif