#ifndef PILHA_DESCARTE_H_INCLUDED
#define PILHA_DESCARTE_H_INCLUDED

#include "pilha.h"
#include "carta.h"

Pilha* cria_pilha_descarte(void) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));

    if (!pilha) {
        printf("Erro: Nao foi possivel alocar memoria para a pilha de descarte!\nO programa sera encerrado!\n");
        exit(1);
    }

    pilha->topo = 52;

    pilha->push = _pilha_push;
    pilha->pop = _pilha_pop;
    pilha->limpa = _pilha_limpa;

    return pilha;
}

#endif // PILHA_DESCARTE_H_INCLUDED
