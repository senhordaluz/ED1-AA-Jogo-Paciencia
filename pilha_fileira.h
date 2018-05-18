#ifndef PILHA_FILEIRA_H_INCLUDED
#define PILHA_FILEIRA_H_INCLUDED

#include "pilha.h"
#include "carta.h"

typedef struct pilhas_fileira Pilhas_Fileira;
static struct pilhas_fileira {
    int carta_virada[7];
    PPilha pilha[7];

    // Adiciona nova carta
    void (*push) (Pilhas_Fileira* self, int fileira, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilhas_Fileira* self, int fileira);
    // Move cartas viradas de uma fileira para outra
    void (*move) (Pilhas_Fileira* self, int fileira_origem, int fileira_destino, int posicao_carta);
    // Limpa pilha
    void (*limpa) (Pilhas_Fileira* self);
};

Pilhas_Fileira* cria_pilhas_fileira(Pilha* pilha_estoque);
static void preenche_pilhas_fileira(Pilhas_Fileira* pilhas_fileira, Pilha* pilha_estoque);

Pilhas_Fileira* cria_pilhas_fileira(Pilha* pilha_estoque) {
    if (pilha_estoque->topo != 51) {
        printf("Pilha Estoque invalida!\n");
        return NULL;
    }

    Pilhas_Fileira* pilhas_fileira = (Pilhas_Fileira*)malloc(sizeof(Pilhas_Fileira));

    if (!pilhas_fileira) {
        printf("Erro: Nao foi possivel alocar memoria para as pilhas de fileira!\nO programa sera encerrado!\n");
        exit(1);
    }

    int i;
    for (i = 0; i < 7; i++) {
        pilhas_fileira->pilha[i] = cria_pilha_standart();
        pilhas_fileira->carta_virada[i] = i+1;
    }

    preenche_pilhas_fileira(pilhas_fileira, pilha_estoque);

    return pilhas_fileira;
}

static void preenche_pilhas_fileira(Pilhas_Fileira* pilhas_fileira, Pilha* pilha_estoque) {
    int i;
    // Fileira 1
    pilhas_fileira->pilha[0]->push(pilhas_fileira->pilha[0], pilha_estoque->pop(pilha_estoque));
    // Fileira 2
    for (i = 0; i < 2; i++) {
        pilhas_fileira->pilha[1]->push(pilhas_fileira->pilha[1], pilha_estoque->pop(pilha_estoque));
    }
    // Fileira 3
    for (i = 0; i < 3; i++) {
        pilhas_fileira->pilha[2]->push(pilhas_fileira->pilha[2], pilha_estoque->pop(pilha_estoque));
    }
    // Fileira 4
    for (i = 0; i < 4; i++) {
        pilhas_fileira->pilha[3]->push(pilhas_fileira->pilha[3], pilha_estoque->pop(pilha_estoque));
    }
    // Fileira 5
    for (i = 0; i < 5; i++) {
        pilhas_fileira->pilha[4]->push(pilhas_fileira->pilha[4], pilha_estoque->pop(pilha_estoque));
    }
    // Fileira 6
    for (i = 0; i < 6; i++) {
        pilhas_fileira->pilha[5]->push(pilhas_fileira->pilha[5], pilha_estoque->pop(pilha_estoque));
    }
    // Fileira 7
    for (i = 0; i < 7; i++) {
        pilhas_fileira->pilha[6]->push(pilhas_fileira->pilha[6], pilha_estoque->pop(pilha_estoque));
    }
}

#endif // PILHA_FILEIRA_H_INCLUDED
