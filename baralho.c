#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralho.h"

int topo = TOTAL_CARTAS;

const Carta USADA = { (Valor)-1, (Naipe)-1 };

// Verifica se a carta foi usada
int carta_foi_usada(Carta carta) {
    return carta.valor == USADA.valor && carta.naipe == USADA.naipe;
}

void inicializar_baralho(Carta* baralho) {
    int i = 0;
    for (int v = 0; v < 10; v++) {
        for (int n = 0; n < 4; n++) {
            baralho[i].valor = (Valor)v;
            baralho[i].naipe = (Naipe)n;
            i++;
        }
    }
}

void embaralhar(Carta* baralho, int tamanho) {
    srand(time(NULL));
    for (int i = 0; i < tamanho - 1; i++) {
        int j = i + rand() % (tamanho - i);
        Carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }
}

void imprimir_valor(Valor v) {
    char* nomes_valor[] = {"4", "5", "6", "7", "Q", "J", "K", "A", "2", "3"};
    printf("%s", nomes_valor[v]);
}

void imprimir_carta(Carta c) {
    char* simbolos_naipe[] = {"♦", "♠", "♥", "♣"};
    imprimir_valor(c.valor);
    printf("%s", simbolos_naipe[c.naipe]);
}

Carta virar_carta(Carta* baralho) {
    return baralho[(topo--)];
}

Valor definir_manilha(Carta carta_virada) {
    if (carta_virada.valor == TRES) 
        return QUATRO; // Manilha é o Quatro
    
    return carta_virada.valor + 1;
}
