#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simples2.h"

static int id;
static int num_jogadores;
static Carta mao[6];
static int num_cartas;
static int aposta = 0;
static Valor manilha_atual;

extern int comparar_cartas(Carta a, Carta b, Valor manilha);

const char* nome_simples2() {
    return "Simples 2";
}

void iniciar_simples2(const int meu_id, const int total_jogadores) {
    id = meu_id;
    num_jogadores = total_jogadores;
}

void nova_rodada_simples2(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao) {
    num_cartas = n_cartas;
    manilha_atual = (carta_virada.valor + 1) % 10;
    for (int i = 0; i < n_cartas; i++) {
        mao[i] = minha_mao[i];
    }
}

int apostar_simples2(const int* apostas) {
    // Apostar a quantidade de cartas maiores ou iguais a Ás
    int aposta = 0;
    for (int i = 0; i < num_cartas; i++)
        if (mao[i].valor >= AS || mao[i].valor == manilha_atual) 
            aposta++;

    return aposta;
}

// Retorna o índice da menor carta que ganha de todas as cartas na mesa
int menor_carta_que_ganha(const Carta* mesa, int num_na_mesa) {
    int idx = -1;
    for (int i = 0; i < num_cartas; i++) {
        if (mao[i].valor < 0) continue;
        int ganha = 1;
        for (int j = 0; j < num_na_mesa; j++) {
            if (comparar_cartas(mao[i], mesa[j], manilha_atual) <= 0) {
                ganha = 0;
                break;
            }
        }
        if (ganha && (idx == -1 || comparar_cartas(mao[i], mao[idx], manilha_atual) < 0)) {
            idx = i;
        }
    }
    return idx;
}

// Retorna o índice da maior carta que perde para todas as cartas na mesa
int maior_carta_que_perde(const Carta* mesa, int num_na_mesa) {
    int idx = -1;
    for (int i = 0; i < num_cartas; i++) {
        if (mao[i].valor < 0) continue;
        int perde = 1;
        for (int j = 0; j < num_na_mesa; j++) {
            if (comparar_cartas(mao[i], mesa[j], manilha_atual) >= 0) {
                perde = 0;
                break;
            }
        }
        if (perde && (idx == -1 || comparar_cartas(mao[i], mao[idx], manilha_atual) > 0)) {
            idx = i;
        }
    }
    return idx;
}

// Se não encontrar carta adequada, joga a menor disponível
int menor_disponivel() {
    int idx = -1;
    for (int i = 0; i < num_cartas; i++) {
        if (mao[i].valor >= 0 && (idx == -1 || comparar_cartas(mao[i], mao[idx], manilha_atual) < 0)) {
            idx = i;
        }
    }
    return idx;
}
