#include <conio.h>
#include <iostream>
#include <fstream>
#include "snake.h"
#include "food.h"
#include "common.h"

using namespace std;
int largura, altura;
char dificuldade;
Snake snake;
Food comida;

void alterarDificuldade()
{
    bool manter = true;
    while (manter)
    {
        char dif;
        cout << "Deseja jogar no:\n";
        cout << "1 - fácil\n";
        cout << "2 - difícil\n";
        cin >> dif;
        if (dif == '1')
        {
            dificuldade = 'f';
            largura = 75;
            altura = 25;
            system("cls");
            manter = false;
            snake.setVelocidade(15);
        }
        else if (dif == '2')
        {
            dificuldade = 'd';
            largura = 45;
            altura = 25;
            system("cls");
            manter = false;
            snake.setVelocidade(55);
            
        }
        else
        {
            system("cls");
            cout << "Valor inválido. Digite novamente.\n";
        }
    }
    snake.criarCobra();
    comida.gerarComida(largura);
    system("cls");
}

string getNameJogador()
{
    system("cls");
    string nomeJogador;

    cout << "Informe seu nick: ";
    cin >> nomeJogador;
    return nomeJogador;
}

void salvarJogada(string nome, int pontos)
{
    ifstream arquivoLeitura("basePontuacao.txt");
    ofstream arquivoEscrita("tempPontuacao.txt");

    bool nickEncontrado = false;
    bool nickAtualizado = false;

    string linha;
    while (getline(arquivoLeitura, linha))
    {
        size_t pos = linha.find("Nome: " + nome);
        if (pos != string::npos)
        {
            nickEncontrado = true;
            size_t pontosPos = linha.find("Pontos: ");
            if (pontosPos != string::npos)
            {
                int pontosExistente = stoi(linha.substr(pontosPos + 8));
                if (pontos > pontosExistente)
                {
                    arquivoEscrita << "Nome: " << nome << ", Pontos: " << pontos << "\n";
                    nickAtualizado = true;
                }
                else
                {
                    arquivoEscrita << linha << "\n";
                }
            }
            else
            {
                arquivoEscrita << linha << "\n";
            }
        }
        else
        {
            arquivoEscrita << linha << "\n";
        }
    }

    arquivoLeitura.close();

    if (!nickEncontrado)
    {
        arquivoEscrita << "Nome: " << nome << ", Pontos: " << pontos << "\n";
    }

    arquivoEscrita.close();

    remove("basePontuacao.txt");
    rename("tempPontuacao.txt", "basePontuacao.txt");
}

void renderCampo()
{
    system("cls");
    for (int x = 0; x <= largura; x++)
    {
        Common::goToxy(x, 0);
        cout << static_cast<CHAR>(219);

        Common::goToxy(x, altura);
        cout << static_cast<CHAR>(219);
    }

    for (int y = 0; y <= altura; ++y)
    {
        Common::goToxy(0, y);
        cout << static_cast<CHAR>(219);

        Common::goToxy(largura, y);
        cout << static_cast<CHAR>(219);
    }
}

void renderFood()
{
    COORD comidaPos = comida.getPos();

    Common::goToxy(comidaPos.X, comidaPos.Y);
    cout << '@';
}

void renderSnake()
{
    vector<COORD> snakePos = snake.getPos();
    int snakeSize = snake.getTamanho();

    Common::goToxy(snakePos[0].X, snakePos[0].Y);
    cout << 'O';

    if (snakeSize > 1)
    {
        Common::goToxy(snakePos[1].X, snakePos[1].Y);
        cout << 'o';
    }
}

void renderPontuacao(int pontos)
{
    Common::goToxy(0, altura + 2);
    cout << "Pontos: ";
    cout << pontos;
}

bool detectCollision()
{
    vector<COORD> snakePos = snake.getPos();

    if (snakePos.at(0).X == 0 || snakePos.at(0).X == largura)
        return true;
    if (snakePos.at(0).Y == 0 || snakePos.at(0).Y == altura)
        return true;
    for (int i = 1; i < snakePos.size(); ++i)
    {
        if (snakePos[0].X == snakePos[i].X && snakePos[0].Y == snakePos[i].Y)
            return true;
    }

    return false;
}

void playGame()
{
    bool crescer = false;
    int pontos = 0;
    string nomeJogador = getNameJogador();
    alterarDificuldade();
    renderCampo();
    Common::goToxy(22, altura + 2);
    cout << "Devs: Gabriel Ferreira \\ Guilherme Henrique \\ Luan Pozzobon";
    while (!detectCollision())
    {
        renderPontuacao(pontos);
        renderFood();
        renderSnake();

        if (kbhit())
        {
            switch (tolower(getch()))
            {
            case 'w':
                snake.mudarDirecao('c');
                break;
            case 'a':
                snake.mudarDirecao('e');
                break;
            case 's':
                snake.mudarDirecao('b');
                break;
            case 'd':
                snake.mudarDirecao('d');
                break;
            }
        }

        if (snake.comer(comida.getPos()))
        {
            comida.gerarComida(largura);
            snake.crescer();

            if (dificuldade == 'f')
            {
                pontos += 5;
            }
            else
            {
                pontos += 10;
            }
            crescer = true;
        }

        Sleep(100 - snake.getVelocidade());
        snake.moverCobra(crescer);
        crescer = false;
    }
    if (detectCollision() == true)
    {
        Common::goToxy(largura / 2 - 5, altura / 2);
        cout << "GAME OVER!";
    }
    else
    {
        if (snake.getTamanho() == altura * largura)
        {
            Common::goToxy(largura / 2 - 5, altura / 2);
            cout << "VOCÊ GANHOU, PARABÉNS!";
        }
    }
    salvarJogada(nomeJogador, pontos);
    Common::goToxy(largura + 2, altura + 2);
}

void showHighscores()
{
    system("cls");
    ifstream arquivoLeitura("basePontuacao.txt");
    if (arquivoLeitura.is_open())
    {
        string linha;
        while (getline(arquivoLeitura, linha))
        {
            cout << linha << endl;
        }
        arquivoLeitura.close();
    }
    else
    {
        cout << "Não houve jogos." << endl;
    }
    cout << "\n";
}

int main()
{
    system("cls");
    int opcao;
    cout << "Bem vindo ao Snake em C++. Escolha sua dificuldade para iniciar e bom jogo!" << endl;

    do
    {
        cout << "Menu:" << endl;
        cout << "1. Iniciar novo jogo" << endl;
        cout << "2. HighScores" << endl;
        cout << "3. Sair do jogo" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            system("cls");
            playGame();
            cout << '\n';
            break;
        case 2:
            system("cls");
            showHighscores();
            break;
        case 3:
            system("cls");
            cout << "\nObrigado por jogar!\n";
            Sleep(5);
            opcao = 123;
            break;
        default:
            system("cls");
            cout << "Opcao invalida. Tente novamente." << endl;
            break;
        }
        cout << endl;
    } while (opcao != 123);

    return 0;
}
