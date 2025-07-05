#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simples.h"

//-----------------------------------------------------//
//                                                     //
//      JOGADOR "OMEGA" - ESTRATÉGIA TIE-AWARE         //
//      (Implementado em simples.c)                    //
//                                                     //
//-----------------------------------------------------//


// --- Estado do Jogador ---
static int id_simples;
static int num_jogadores_simples;
static int num_cartas_simples;
static Carta mao_simples[6];
static int aposta_feita_simples;
static Valor manilha_atual_simples;

// Memória Perfeita: rastreia todas as 40 cartas.
static int cartas_vistas[40];

extern int comparar_cartas(Carta a, Carta b, Valor manilha);

// --- Funções Auxiliares (com Consciência de Risco) ---

// Retorna o número de cartas de um dado valor que ainda não foram vistas.
static int contar_nao_vistas_de_valor(Valor v) {
    if (v < 0 || v > 9) return 0;
    int count = 0;
    for (int naipe = 0; naipe < 4; naipe++) {
        if (cartas_vistas[v * 4 + naipe] == 0) {
            count++;
        }
    }
    return count;
}

static int achar_menor_que_ganha_seguro(const Carta* mesa, int num_na_mesa) {
    int idx = -1;
    float melhor_score = -1.0; // Score: maior é melhor

    for (int i=0; i < num_cartas_simples; i++) {
        if (mao_simples[i].valor < 0) continue;
        
        int ganha = 1;
        for (int j = 0; j < num_na_mesa; j++) {
            if (comparar_cartas(mao_simples[i], mesa[j], manilha_atual_simples) <= 0) {
                ganha = 0;
                break;
            }
        }

        if (ganha) {
            float score = 100.0 - (float)mao_simples[i].valor; // Prioriza a carta mais fraca que ganha
            if (mao_simples[i].valor != manilha_atual_simples && contar_nao_vistas_de_valor(mao_simples[i].valor) == 0) {
                score += 50.0; // Bônus enorme por uma vitória garantida (sem risco de empate)
            }
            if (score > melhor_score) {
                melhor_score = score;
                idx = i;
            }
        }
    }
    return idx;
}

static int achar_maior_que_perde(const Carta* mesa, int num_na_mesa) {
    int idx = -1;
    if (num_na_mesa == 0) return -1;
    Carta carta_vencedora = mesa[0];
    for (int i = 1; i < num_na_mesa; i++) if (comparar_cartas(mesa[i], carta_vencedora, manilha_atual_simples) > 0) carta_vencedora = mesa[i];

    for (int i=0; i<num_cartas_simples; i++) {
        if (mao_simples[i].valor < 0) continue;
        if (comparar_cartas(mao_simples[i], carta_vencedora, manilha_atual_simples) < 0) {
            if (idx == -1 || comparar_cartas(mao_simples[i], mao_simples[idx], manilha_atual_simples) > 0) idx = i;
        }
    }
    return idx;
}

static int achar_menor_da_mao() {
    int idx = -1;
    for (int i=0; i<num_cartas_simples; i++) if (mao_simples[i].valor >= 0 && (idx == -1 || comparar_cartas(mao_simples[i], mao_simples[idx], manilha_atual_simples) < 0)) idx=i;
    return idx;
}


// --- Funções da Interface ---
const char* nome_simples() { return "Omega"; }

void iniciar_simples(const int meu_id, const int total_jogadores) {
    id_simples = meu_id;
    num_jogadores_simples = total_jogadores;
}

void nova_rodada_simples(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao) {
    num_cartas_simples = n_cartas;
    manilha_atual_simples = (carta_virada.valor + 1) % 10;
    
    memset(cartas_vistas, 0, sizeof(cartas_vistas));
    for (int i=0; i<n_cartas; i++) {
        mao_simples[i] = minha_mao[i];
        cartas_vistas[minha_mao[i].valor * 4 + minha_mao[i].naipe] = 1;
    }
    cartas_vistas[carta_virada.valor * 4 + carta_virada.naipe] = 1;
}

int apostar_simples(const int* apostas) {
    float vitorias_estimadas = 0.0;
    for (int i=0; i<num_cartas_simples; i++) {
        float valor_base = 0.0;
        Carta c = mao_simples[i];

        if (c.valor == manilha_atual_simples) valor_base = 1.0;
        else if (c.valor == TRES) valor_base = 0.85;
        else if (c.valor == DOIS) valor_base = 0.75;
        else if (c.valor == AS) valor_base = 0.6;
        else if (c.valor == REI) valor_base = 0.3;

        // Ajusta o valor baseado no risco de empate
        if (c.valor != manilha_atual_simples && valor_base > 0) {
            if (contar_nao_vistas_de_valor(c.valor) > 0) {
                valor_base *= 0.6; // Reduz o valor se houver risco de empate
            }
        }
        vitorias_estimadas += valor_base;
    }
    int aposta = (int)(vitorias_estimadas + 0.5);
    aposta_feita_simples = (aposta > num_cartas_simples) ? num_cartas_simples : aposta;
    return aposta_feita_simples;
}

int jogar_simples(const Carta* mesa, const int num_na_mesa, const int vitorias) {
    // Atualiza a memória com as cartas da mesa
    for(int i = 0; i < num_na_mesa; i++) cartas_vistas[mesa[i].valor * 4 + mesa[i].naipe] = 1;

    int idx_a_jogar = -1;

    if (vitorias < aposta_feita_simples) {
        // MODO OFENSIVO: Tenta ganhar com a jogada mais segura
        idx_a_jogar = achar_menor_que_ganha_seguro(mesa, num_na_mesa);
        if (idx_a_jogar == -1) {
             // Fallback: se não pode ganhar, joga o menor lixo
             idx_a_jogar = achar_menor_da_mao();
        }
    } else {
        // MODO DEFENSIVO: Tenta perder, descartando o maior valor possível
        idx_a_jogar = achar_maior_que_perde(mesa, num_na_mesa);
        if (idx_a_jogar == -1) {
            // Fallback: se é forçado a ganhar, minimiza o dano jogando a vitória mais barata
            idx_a_jogar = achar_menor_que_ganha_seguro(mesa, num_na_mesa);
             // Se mesmo assim não achar (mesa vazia), joga a menor carta
             if (idx_a_jogar == -1) {
                 idx_a_jogar = achar_menor_da_mao();
             }
        }
    }
    
    // Atualiza a memória com a carta que será jogada
    cartas_vistas[mao_simples[idx_a_jogar].valor * 4 + mao_simples[idx_a_jogar].naipe] = 1;
    mao_simples[idx_a_jogar].valor = -1;
    return idx_a_jogar;
}