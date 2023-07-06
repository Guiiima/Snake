#include "food.h"
#include <random>

Food::Food() {}

void Food::gerarComida(int largura) {

    std::mt19937 mt(time(nullptr));
    std::uniform_int_distribution<short> randX(1, largura - 1);
    std::uniform_int_distribution<short> randY(1, 24);

    pos.X = randX(mt);
    pos.Y = randY(mt);

}

COORD Food::getPos() {
    return pos;
}