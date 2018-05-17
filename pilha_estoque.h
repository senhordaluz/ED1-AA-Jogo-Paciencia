#ifndef PILHA_ESTOQUE_H_INCLUDED
#define PILHA_ESTOQUE_H_INCLUDED

#include "pilha.h"
#include "carta.h"

Pilha* cria_pilha_estoque(void) {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));

    if (!pilha) {
        printf("Erro: Nao foi possivel alocar memoria para a pilha de estoque!\nO programa sera encerrado!\n");
        exit(1);
    }

    pilha->topo = -1;
    pilha->cartas = malloc(52 * sizeof(Carta*));

    pilha->push = _pilha_push;
    pilha->pop = _pilha_pop;
    pilha->limpa = _pilha_limpa;
    pilha->free = free_pilha;
}

#endif // PILHA_ESTOQUE_H_INCLUDED
