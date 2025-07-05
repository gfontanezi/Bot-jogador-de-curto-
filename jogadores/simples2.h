#ifndef SIMPLES2_H
#define SIMPLES2_H

#include "../baralho.h"

const char* nome_simples2();
void iniciar_simples2(const int meu_id, const int total_jogadores);
void nova_rodada_simples2(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao);
int apostar_simples2(const int* apostas);
int jogar_simples2(const Carta* mesa, const int num_na_mesa, const int vitorias);

#endif // SIMPLES2_H
