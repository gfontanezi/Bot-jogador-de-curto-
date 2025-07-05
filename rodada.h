#ifndef RODADA_H
#define RODADA_H

#include "carta.h"

typedef struct {
    int numero;
    int num_jogadores;
    int cartas_por_jogador;
    int jogador_inicial;

    Carta carta_virada;
    Valor manilha;

    Carta maos[5][6];
    int cartas_restantes[5];
    int apostas[5];
    int vitorias[5];
    int pontos_acumulados;
} Rodada;

void iniciar_rodada(Rodada* r, int numero, int num_jogadores, int jogador_inicial, Carta* baralho);
void imprimir_maos(const Rodada* r);
void atualizar_jogador_inicial(Rodada* r, int vencedor);

#endif