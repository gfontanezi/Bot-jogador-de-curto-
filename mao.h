#ifndef MAO_H
#define MAO_H

#include "carta.h"

typedef struct {
    int jogador_id;
    Carta carta;
} Jogada;

int comparar_cartas(Carta a, Carta b, Valor manilha);
int resolver_mao(Jogada* jogadas, int num_jogadores, Valor manilha);
// retorna o índice do vencedor ou -1 se houve empate entre não-manilhas

#endif
