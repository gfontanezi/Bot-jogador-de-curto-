#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../baralho.h"
#include "../mao.h"

static int meu_id = 0;
static int total_jogadores = 0;
static int num_cartas = 0;
static Carta minha_mao[6];

static Valor manilha_rodada;


static int get_rank_carta(Carta c)
{
    // cartas usadas com valor -1.
    if (c.valor == -1)
    {
        return -1;
    }
    // Verifica se a carta é uma manilha.
    if (c.valor == manilha_rodada)
    {
        // Poder da manilha = 100 + poder do naipe para desempate.
        // Ordem: Ouros(0) < Copas(1) < Espadas(2) < Paus(3)
        return 100 + (int)c.naipe;
    }
    // Se for uma carta normal, o poder é o seu valor.
    return (int)c.valor;
}

void iniciar_aleatorio2(int id, int total)
{
    meu_id = id;
    total_jogadores = total;
}

void nova_rodada_aleatorio2(int rodada, Carta carta_virada, int n_cartas, Carta *mao)
{
    num_cartas = n_cartas;
    for (int i = 0; i < n_cartas; i++)
    {
        minha_mao[i] = mao[i];
    }
    // A ordem é circular, então depois do 3 vem o 4.
    if (carta_virada.valor == TRES) {
        manilha_rodada = QUATRO;
    } else {
        // Para todas as outras cartas, a manilha é o valor seguinte.
        manilha_rodada = (Valor)(carta_virada.valor + 1);
    }
}


int apostar_aleatorio2(const int *apostas){
    int aposta = 0;
    for (int i = 0; i < num_cartas; i++) {
        if (minha_mao[i].valor == manilha_rodada) {
            aposta++;
        }
    }
    return aposta;
}


int jogar_aleatorio2(const Carta *mesa, int num_na_mesa)
{
    int idx_a_jogar = -1;

    // CASO 1: Sou o primeiro a jogar.
    if (num_na_mesa == 0)
    {
        // Joga a carta mais fraca para não gastar cartas boas.
        int rank_pior_carta = 200; // Valor inicial alto
        for (int i = 0; i < num_cartas; i++)
        {
            if (minha_mao[i].valor == -1) continue;
            int rank_atual = get_rank_carta(minha_mao[i]);
            if (rank_atual < rank_pior_carta)
            {
                rank_pior_carta = rank_atual;
                idx_a_jogar = i;
            }
        }
    }
    // CASO 2: Não sou o primeiro, preciso reagir.
    else
    {
        // 1. Encontrar a carta mais forte na mesa.
        int rank_vencedor_mesa = -1;
        for (int i = 0; i < num_na_mesa; i++)
        {
            int rank_atual_mesa = get_rank_carta(mesa[i]);
            if (rank_atual_mesa > rank_vencedor_mesa)
            {
                rank_vencedor_mesa = rank_atual_mesa;
            }
        }

        // 2. Tentar vencer com a carta mais fraca possível ("vencer barato").
        int indice_menor_vencedora = -1;
        int rank_menor_vencedora = 200;
        for (int i = 0; i < num_cartas; i++)
        {
            if (minha_mao[i].valor == -1) continue;
            int rank_minha_carta = get_rank_carta(minha_mao[i]);
            if (rank_minha_carta > rank_vencedor_mesa && rank_minha_carta < rank_menor_vencedora)
            {
                rank_menor_vencedora = rank_minha_carta;
                indice_menor_vencedora = i;
            }
        }

        if (indice_menor_vencedora != -1)
        {
            idx_a_jogar = indice_menor_vencedora;
        }
        // 3. Não posso vencer, então jogo a pior carta ("perder barato").
        else
        {
            int rank_pior_carta = 200;
            for (int i = 0; i < num_cartas; i++)
            {
                if (minha_mao[i].valor == -1) continue;
                int rank_minha_carta = get_rank_carta(minha_mao[i]);
                if (rank_minha_carta < rank_pior_carta)
                {
                    rank_pior_carta = rank_minha_carta;
                    idx_a_jogar = i;
                }
            }
        }
    }

    minha_mao[idx_a_jogar] = (Carta){-1, -1}; // Marca a carta como usada (usando sua sintaxe)
    return idx_a_jogar;
}

const char *nome_aleatorio2()
{
    return "aleatorio2";
}