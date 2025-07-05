#ifndef CARTA_H
#define CARTA_H

typedef enum {
    OUROS = 0,
    ESPADAS,
    COPAS,
    PAUS
} Naipe;

typedef enum {
    QUATRO = 0, CINCO, SEIS, SETE, 
    DAMA, VALETE, REI, AS, DOIS, TRES
} Valor;

typedef struct {
    Valor valor;
    Naipe naipe;
} Carta;

extern const Carta USADA;

#endif
