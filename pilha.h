#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "carta.h"

typedef struct pilha Pilha;
typedef struct pilha* PPilha;
static struct pilha {
    // Topo de pilha
    int topo;
    // Vetor de cartas
    PCarta cartas[52];

    // Adiciona nova carta
    void (*push) (Pilha* self, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilha* self);
    // Limpa pilha
    void (*limpa) (Pilha* self);
};

Pilha* cria_pilha_standart(void);
void free_pilha(Pilha* pilha);
void _pilha_push(Pilha* pilha, Carta* carta);
Carta* _pilha_pop(Pilha* pilha);
void _pilha_limpa(Pilha* pilha);
void imprimePilha(Pilha* pilha);
int isPilhaVazia(Pilha* pilha);
int isPilhaCheia(Pilha* pilha);

Pilha* cria_pilha_standart(void) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));

    if (!pilha) {
        printf("Erro: Nao foi possivel alocar memoria para a pilha standart!\nO programa sera encerrado!\n");
        exit(1);
    }

    pilha->topo = 52;

    pilha->push = _pilha_push;
    pilha->pop = _pilha_pop;
    pilha->limpa = _pilha_limpa;

    return pilha;
}

void free_pilha(Pilha* pilha) {
    _pilha_limpa(pilha);
    free(pilha);
}

void _pilha_push(Pilha* pilha, Carta* carta) {
    if (!isPilhaCheia(pilha)) {
        if (isPilhaVazia(pilha))
            pilha->topo = 0;
        else
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

void _pilha_limpa(Pilha* pilha) {
    if ( !isPilhaVazia(pilha) ) {
        int i;
        for (i = 0; i < pilha->topo; i++) {
            Carta* carta = pilha->pop(pilha);
            free_carta(carta);
        }
    }
}

void imprimePilha(Pilha* pilha) {
    pilha->cartas[pilha->topo]->print(pilha->cartas[pilha->topo]);
    if ( !isPilhaVazia(pilha) ) {
        int i;
        for (i = 0; i < pilha->topo; i++) {
            pilha->cartas[i]->print(pilha->cartas[i]);
        }
    }
}

int isPilhaVazia(Pilha* pilha) {
    if (pilha->topo == 52)
        return 1;
    return 0;
}

int isPilhaCheia(Pilha* pilha) {
    if (pilha->topo == 51)
        return 1;
    return 0;
}

#endif // PILHA_H_INCLUDED
