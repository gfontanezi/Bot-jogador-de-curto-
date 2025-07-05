#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aleatorio1.h"
#include "../baralho.h"

// Variáveis globais para armazenar o estado do jogador
static int id;
static int num_jogadores;
static Carta mao[6];
static int num_cartas;

const char* nome_aleatorio1() {
    return "Aleatório 1";
}

void iniciar_aleatorio1(const int meu_id, const int total_jogadores) {
    id = meu_id;
    num_jogadores = total_jogadores;
    srand(time(NULL) + id); // Semente diferente para cada jogador
}

void nova_rodada_aleatorio1(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao) {
    num_cartas = n_cartas;
    for (int i = 0; i < n_cartas; i++) {
        mao[i] = minha_mao[i];
    }
}

int apostar_aleatorio1(const int* apostas) {
    // Aposta aleatória entre 0 e num_cartas
    return rand() % (num_cartas + 1);
}

int jogar_aleatorio1(const Carta* mesa, const int num_na_mesa, const int vitorias) {
    while (1) {
        // Sorteia um índice aleatório entre 0 e num_cartas - 1
        int idx = rand() % num_cartas;

        // Verifica se a carta é válida
        if (!carta_foi_usada(mao[idx])) {
            mao[idx] = USADA; // Marca a carta como usada
            return idx;       // Retorna o índice da carta válida
        }
    }
}