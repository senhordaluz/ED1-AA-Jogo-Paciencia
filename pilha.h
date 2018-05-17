#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "carta.h"

typedef struct pilha Pilha;
static struct pilha {
    // Topo de pilha
    int topo;
    // Vetor de cartas
    Carta* cartas[52];

    // Adiciona nova carta
    void (*push) (Pilha* self, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilha* self);
    // Limpa pilha
    void (*limpa) (Pilha* self);
    // Libera pilha da memoria
    void (*free) (Pilha* self);
};

void free_pilha(Pilha* pilha);
void _pilha_push(Pilha* pilha, Carta* carta);
Carta* _pilha_pop(Pilha* pilha);
int isPilhaVazia(Pilha* pilha);
int isPilhaCheia(Pilha* pilha);

void free_pilha(Pilha* pilha) {
    if (isPilhaVazia(pilha)) {
        int i;
        for (i = 0; i <= pilha->qtd_cartas; i++) {
            Carta* carta = pilha->pop(pilha);
            free_carta(carta);
        }
    }
    free_pilha(pilha);
}

void _pilha_push(Pilha* pilha, Carta* carta) {
    if (!isPilhaCheia(pilha)) {
        pilha->topo++;
        pilha->cartas[pilha->topo] = carta;
        return;
    }
    printf("Pilha cheia!\n");
    return;
}

Carta* _pilha_pop(Pilha* pilha) {
    if (!isPilhaVazia(pilha)) {
        Carta* carta = pilha->cartas[pilha->topo];
        pilha->cartas[pilha->topo] = NULL;
        pilha->topo--;
        return carta;
    }
    printf("Pilha vazia!\n");
    return NULL;
}

int isPilhaVazia(Pilha* pilha) {
    if (pilha->topo == -1)
        return 1;
    return 0;
}

int isPilhaCheia(Pilha* pilha) {
    if (pilha->topo == 51)
        return 1;
    return 0;
}

#endif // PILHA_H_INCLUDED
