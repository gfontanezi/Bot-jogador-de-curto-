#ifndef BARALHO_H
#define BARALHO_H

#include "carta.h"

#define TOTAL_CARTAS 40

int carta_foi_usada(Carta carta);
void inicializar_baralho(Carta* baralho);
void embaralhar(Carta* baralho, int tamanho);
void imprimir_valor(Valor v);
void imprimir_carta(Carta c);
Carta virar_carta(Carta* baralho);
Valor definir_manilha(Carta carta_virada);

#endif
