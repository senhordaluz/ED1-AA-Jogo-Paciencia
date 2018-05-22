#ifndef PILHA_DESCARTE_H_INCLUDED
#define PILHA_DESCARTE_H_INCLUDED

#include "pilha.h"
#include "carta.h"

Pilha* cria_pilha_descarte(void) {
    return cria_pilha_generica(52);
}

#endif // PILHA_DESCARTE_H_INCLUDED
