#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "carta.h"

typedef struct pilha Pilha;
static struct pilha {
    Carta** cartas;

    // Adiciona nova carta
    void (*push) (Pilha* self, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilha* self);
    // Limpa pilha
    void (*limpa) (Pilha* self);
}

#endif // PILHA_H_INCLUDED
