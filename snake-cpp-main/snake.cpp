#include "snake.h"
#include "common.h"

Snake::Snake() {}

void Snake::criarCobra(){
    this->pos.clear();
    this->pos.push_back({12, 17});
    tamanho = 1;
    direcao = 'd';
}

void Snake::mudarDirecao(char direcao)
{
    if(this->direcao == 'c' && direcao == 'b') return;
    if(this->direcao == 'b' && direcao == 'c') return;
    if(this->direcao == 'd' && direcao == 'e') return;
    if(this->direcao == 'e' && direcao == 'd') return;
    this->direcao = direcao;
}

void Snake::unrenderSnake(bool crescer){
    Common::goToxy(pos.at(0).X, pos.at(0).Y);
    std::cout << ' ';
    if(!crescer){
        Common::goToxy(pos.at(tamanho - 1).X, pos.at(tamanho - 1).Y);
        std::cout << ' ';
    }
}

void Snake::moverCobra(bool crescer)
{
    unrenderSnake(crescer);
    for(int i = tamanho - 1; i > 0; --i){
        pos[i] = pos[i - 1];
    }
    switch (direcao)
    {
    case 'c':
        pos[0].Y--;
        break;
    case 'b':
        pos[0].Y++;
        break;
    case 'd':
        pos[0].X++;
        break;
    case 'e':
        pos[0].X--;
        break;
    default:
        break;
    }
}

std::vector<COORD> Snake::getPos() {
    return pos;
}

int Snake::getTamanho(){
    return tamanho;
}

int Snake::getVelocidade(){
    return velocidade;
}

void Snake::setVelocidade(int vel){
    velocidade = vel;
}

bool Snake::comer(COORD posicaoComida) {
    if(posicaoComida.X == pos.at(0).X && posicaoComida.Y == pos.at(0).Y) return true;
    else return false;
}

void Snake::crescer() {   
    pos.push_back(pos[tamanho]);

    switch(direcao){
        case 'c':
            pos[tamanho].Y++;
            break;
        case 'b':
            pos[tamanho].Y--;
            break;
        case 'e':
            pos[tamanho].X++;
            break;
        case 'd':
            pos[tamanho].X--;
            break;
    }
    tamanho++;
}
