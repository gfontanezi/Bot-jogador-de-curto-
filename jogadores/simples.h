#ifndef SIMPLES_H
#define SIMPLES_H

#include "../baralho.h"

const char* nome_simples();
void iniciar_simples(const int meu_id, const int total_jogadores);
void nova_rodada_simples(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao);
int apostar_simples(const int* apostas);
int jogar_simples(const Carta* mesa, const int num_na_mesa, const int vitorias);

#endif // SIMPLES_H
