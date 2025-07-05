#ifndef ALEATORIO1_H
#define ALEATORIO1_H

#include "../baralho.h"

const char* nome_aleatorio1();
void iniciar_aleatorio1(const int meu_id, const int total_jogadores);
void nova_rodada_aleatorio1(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao);
int apostar_aleatorio1(const int* apostas);
int jogar_aleatorio1(const Carta* mesa, const int num_na_mesa, const int vitorias);

#endif // ALEATORIO1_H