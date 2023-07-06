#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <string>
#include <Windows.h>

class Snake
{
private:
    std::vector<COORD> pos;
    int tamanho;
    int velocidade;
    char direcao;

public:
    Snake();
    void mudarDirecao(char direcao);
    void criarCobra();
    void unrenderSnake(bool);
    void moverCobra(bool);
    std::vector<COORD> getPos();
    int getTamanho();
    int getVelocidade();
    void setVelocidade(int velocidade);
    bool comer(COORD posicaoComida);
    void crescer();
};

#endif
