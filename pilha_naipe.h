#ifndef PILHA_NAIPE_H_INCLUDED
#define PILHA_NAIPE_H_INCLUDED

#include "pilha.h"
#include "carta.h"

#define ESPADA  0
#define COPAS   1
#define PAUS    2
#define OURO    3

typedef struct pilhas_naipe Pilhas_Naipe;
static struct pilhas_naipe {
    int naipes[4];
    PPilha pilha[4];

    // Adiciona nova carta
    void (*push) (Pilhas_Naipe* self, int naipe, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilhas_Naipe* self, int naipe);
    // Limpa pilha
    void (*limpa) (Pilhas_Naipe* self);
};

Pilhas_Naipe* cria_pilhas_naipe(void);
void free_pilhas_naipe(Pilhas_Naipe* pilhas_naipe);
static int isNaipeAlocado(Pilhas_Naipe* pilhas_naipe, int naipe);
static void _pilhas_naipe_push(Pilhas_Naipe* pilhas_naipe, int naipe, Carta* carta);
static Carta* _pilhas_naipe_pop(Pilhas_Naipe* pilhas_naipe, int naipe);

Pilhas_Naipe* cria_pilhas_naipe(void) {
    Pilhas_Naipe* pilhas_naipe = (Pilhas_Naipe*)malloc(sizeof(Pilhas_Naipe));

    if (!pilhas_naipe) {
        printf("Erro: Nao foi possivel alocar memoria para as pilhas de naipe!\nO programa sera encerrado!\n");
        exit(1);
    }

    int i;
    for (i = 0; i < 4; i++) {
        pilhas_naipe->naipes[i] = 4;
        pilhas_naipe->pilha[i] = cria_pilha_generica(52);
    }

    pilhas_naipe->push = _pilhas_naipe_push;
    pilhas_naipe->pop = _pilhas_naipe_pop;

    return pilhas_naipe;
}

void free_pilhas_naipe(Pilhas_Naipe* pilhas_naipe) {
    int i;
    for (i = 0; i < 4; i++) {
        free_pilha(pilhas_naipe->pilha[i]);
    }
    free(pilhas_naipe);
}

static int isNaipeAlocado(Pilhas_Naipe* pilhas_naipe, int naipe) {
    if (pilhas_naipe->naipes[naipe] < 4)
        return 1;
    return 0;
}

static void _pilhas_naipe_push(Pilhas_Naipe* pilhas_naipe, int naipe, Carta* carta) {
    if (naipe >= 4) {
        printf("Id de pilha invalido!\n");
        return;
    }

    int isPilhaVazia = 0;

    if (!isNaipeAlocado(pilhas_naipe, naipe)) {
        int i;
        int naipes_alocados = 0;
        for (i = 0; i < 4; i++) {
            if (pilhas_naipe->naipes[i] != 4)
                naipes_alocados++;
        }
        switch (naipes_alocados) {
            case 0:
                pilhas_naipe->naipes[naipe] = 0;
                break;
            case 1:
                pilhas_naipe->naipes[naipe] = 1;
                break;
            case 2:
                pilhas_naipe->naipes[naipe] = 2;
                break;
            case 3:
                pilhas_naipe->naipes[naipe] = 3;
                break;
        }
        isPilhaVazia = 1;
    }

    if (isPilhaVazia) {
        int topo = pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]]->topo;
        Carta* carta_topo = pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]]->cartas[topo];
        if (carta->naipe != carta_topo->naipe) {
            printf("Naipe invalido!\n");
            return;
        }
    }

    pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]]->push(pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]],carta);
}

static Carta* _pilhas_naipe_pop(Pilhas_Naipe* pilhas_naipe, int naipe) {
    if (naipe >= 4) {
        printf("Id de pilha invalido!\n");
        return NULL;
    }
    return pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]]->pop(pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]]);
}

#endif // PILHA_NAIPE_H_INCLUDED
