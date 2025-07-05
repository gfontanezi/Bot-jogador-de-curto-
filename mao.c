#include "mao.h"

// retorna negativo se a < b, 0 se iguais, positivo se a > b
int comparar_cartas(Carta a, Carta b, Valor manilha) {
    if(a.valor == manilha) {
        if(b.valor == manilha)
            return (a.naipe - b.naipe);
        return 1; // a é manilha, b não é
    }
    if(b.valor == manilha) {
        return -1; // b é manilha, a não é
    }
    return (a.valor - b.valor); // comparação normal de valores
}

// retorna o índice da jogada vencedora, ou -1 em caso de empate entre não-manilhas
int resolver_mao(Jogada* jogadas, int num_jogadores, Valor manilha) {
    int vencedor = 0;
    int empate = 0;

    for (int i = 1; i < num_jogadores; i++) {
        int comp = comparar_cartas(jogadas[i].carta, jogadas[vencedor].carta, manilha);
        if (comp > 0) {
            vencedor = i;
            empate = 0;
        } else if (comp == 0) {
            empate = 1;
        }
    }

    return empate ? -1 : vencedor;
}
