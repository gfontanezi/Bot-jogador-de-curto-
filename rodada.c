#include <stdio.h>
#include <string.h>
#include "rodada.h"
#include "baralho.h"

void distribuir_cartas(Rodada* r, int num_jogadores, Carta* baralho, int* idx) {
    for (int j = 0; j < num_jogadores; j++) {
        for (int c = 0; c < r->cartas_por_jogador; c++) {
            r->maos[j][c] = baralho[(*idx)++];
        }
    }
}

void iniciar_rodada(Rodada* r, int numero, int num_jogadores, int jogador_inicial, Carta* baralho) {
    r->numero = numero;
    r->num_jogadores = num_jogadores;
    r->cartas_por_jogador = numero + 1; // rodada 0 tem 2 cartas, rodada 4 tem 5 etc
    r->jogador_inicial = jogador_inicial;
    r->pontos_acumulados = 0;

    embaralhar(baralho, TOTAL_CARTAS);

    int idx = 0;
    distribuir_cartas(r, num_jogadores, baralho, &idx);

    for (int j = 0; j < num_jogadores; j++) {
        r->cartas_restantes[j] = r->cartas_por_jogador;
        r->apostas[j] = 0;     
        r->vitorias[j] = 0;
    }

    r->carta_virada = baralho[idx++];
    r->manilha = definir_manilha(r->carta_virada);
}

// Atualiza o jogador inicial com base no vencedor da mão
void atualizar_jogador_inicial(Rodada* r, int vencedor) {
    if (vencedor != -1) { // Se não houve empate
        r->jogador_inicial = vencedor;
    }
}

void imprimir_maos(const Rodada* r) {
    for (int j = 0; j < r->num_jogadores; j++) {
        printf("Jogador %d: ", j);
        for (int c = 0; c < r->cartas_restantes[j]; c++) {
            imprimir_carta(r->maos[j][c]);
            printf(" ");
        }
        printf("\n");
    }
}