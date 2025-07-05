#ifndef ALEATORIO2_H
#define ALEATORIO2_H

#include "../baralho.h"

const char* nome_aleatorio2();
void iniciar_aleatorio2(const int meu_id, const int total_jogadores);
void nova_rodada_aleatorio2(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao);
int apostar_aleatorio2(const int* apostas);
int jogar_aleatorio2(const Carta* mesa, const int num_na_mesa, const int vitorias);

#endif // ALEATORIO2_H