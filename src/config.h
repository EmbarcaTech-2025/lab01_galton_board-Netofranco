#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdint.h>

//Definições utilizadas no programa para o Display
#define SCREEN_WIDTH 128                //Largura do Display em Pixels
#define SCREEN_HEIGHT 64                //Comprimento do Display em Pixels
#define SIMULATION_HEIGHT 54            //Comprimento reservado pra area de simulação em Pixels
#define HISTOGRAM_HEIGHT 10             //Compimento reservado para area do Histograma em Pixels

//Definições utilizadas no programa para Simulação da Galton Board
#define BALL_RADIUS 2                   //Raio das bolas em Pixels
#define PEG_RADIUS 1                    //Raio dos Pinos em Pixels
#define NUM_PEG_ROWS 7                  //Numero de Linha dos Pinos
#define NUM_BINS (NUM_PEG_ROWS + 1)     //Numero de Compartimentos (sempre numero de linhas + 1)
#define MAX_BALLS 8                     //Numero máximo de Bolas Simultaneas

//Estrutura para representação de uma bolinha
typedef struct {
    float x, y;                         //Define posição dos eixos
    float vx, vy;                       //Define velocidade nos eixos
    bool active;                        //Define status da bolinha (ativo ou inativo)
    int bin;                            //Registo em qual compartimento a bolinha caiu
    int prev_x, prev_y;                 //Armazena posicinamento prévio nos eixos (para efeito de simulação)
} Ball;

//Estrutura para representação de um Obstaculo
typedef struct {
    float x, y;                         //Define posição nos eixo
} Peg;

#endif // CONFIG_H