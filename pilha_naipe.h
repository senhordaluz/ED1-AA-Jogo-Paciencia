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
static int pilhas_naipe_movimentacao_valida(Pilha* pilha_destino, Carta* carta);
static int pilhas_naipe_movimentacao_valida_naipe(Carta* carta_topo, Carta* nova_carta);
static int pilhas_naipe_movimentacao_valida_valor(Carta* carta_topo, Carta* nova_carta);

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

    Pilha* pilha = pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]];

    if ( !isPilhaVazia && pilhas_naipe_movimentacao_valida(pilha, carta) ) {
        printf("Naipe invalido!\n");
        return;
    }

    pilha->push(pilha, carta);
}

static Carta* _pilhas_naipe_pop(Pilhas_Naipe* pilhas_naipe, int naipe) {
    if (naipe >= 4) {
        printf("Pilha vazia ou ID inválido!\n");
        return NULL;
    }
    Pilha* pilha = pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]];
    return pilha->pop(pilha);
}

static int pilhas_naipe_movimentacao_valida(Pilha* pilha_destino, Carta* carta) {
    Carta* carta_topo = pilha_destino->cartas[pilha_destino->topo];
    if (pilhas_naipe_movimentacao_valida_naipe(carta_topo, carta))
        return pilhas_naipe_movimentacao_valida_valor(carta_topo, carta);
    return 0;
}

static int pilhas_naipe_movimentacao_valida_naipe(Carta* carta_topo, Carta* nova_carta) {
    switch (carta_topo->naipe) {
        case 'E': case 'e':
            if (nova_carta->naipe == 'E' || nova_carta->naipe == 'e')
                return 1;
            return 0;
            break;
        case 'P': case 'p':
            if (nova_carta->naipe == 'P' || nova_carta->naipe == 'p')
                return 1;
            return 0;
            break;
        case 'C': case 'c':
            if (nova_carta->naipe == 'C' || nova_carta->naipe == 'c')
                return 1;
            return 0;
            break;
        case 'O': case 'o':
            if (nova_carta->naipe == 'O' || nova_carta->naipe == 'o')
                return 1;
            return 0;
            break;
    }
}

static int pilhas_naipe_movimentacao_valida_valor(Carta* carta_topo, Carta* nova_carta) {
    switch (carta_topo->valor) {
        case 'K': case 'k':
            return 0;
            break;
        case 'Q': case 'q':
            if (nova_carta->valor == 'K' || nova_carta->valor == 'k')
                return 1;
            return 0;
            break;
        case 'J': case 'j':
            if (nova_carta->valor == 'Q' || nova_carta->valor == 'q')
                return 1;
            return 0;
            break;
        case '9':
            if (nova_carta->valor == 'J' || nova_carta->valor == 'j')
                return 1;
            return 0;
            break;
        case '8':
            if (nova_carta->valor == '9')
                return 1;
            return 0;
            break;
        case '7':
            if (nova_carta->valor == '8')
                return 1;
            return 0;
            break;
        case '6':
            if (nova_carta->valor == '7')
                return 1;
            return 0;
            break;
        case '5':
            if (nova_carta->valor == '6')
                return 1;
            return 0;
            break;
        case '4':
            if (nova_carta->valor == '5')
                return 1;
            return 0;
            break;
        case '3':
            if (nova_carta->valor == '4')
                return 1;
            return 0;
            break;
        case '2':
            if (nova_carta->valor == '3')
                return 1;
            return 0;
            break;
        case '1':
            if (nova_carta->valor == '2')
                return 1;
            return 0;
            break;
        case 'A': case 'a':
            if (nova_carta->valor == '1')
                return 1;
            return 0;
            break;
    }
}
#endif // PILHA_NAIPE_H_INCLUDED
