#ifndef PILHA_FILEIRA_H_INCLUDED
#define PILHA_FILEIRA_H_INCLUDED

#include "pilha.h"
#include "carta.h"

typedef struct pilhas_fileira Pilhas_Fileira;
static struct pilhas_fileira {
    int carta_virada[7];
    PPilha pilha[7];

    // Adiciona nova carta
    void (*push) (Pilhas_Fileira* self, int fileira_id, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilhas_Fileira* self, int fileira_id);
    // Move cartas viradas de uma fileira para outra
    void (*move) (Pilhas_Fileira* self, int fileira_origem, int fileira_destino, int posicao_carta);
    // Limpa pilha
    void (*limpa) (Pilhas_Fileira* self);
};

Pilhas_Fileira* cria_pilhas_fileira(Pilha* pilha_estoque);
static void preenche_pilhas_fileira(Pilhas_Fileira* pilhas_fileira, Pilha* pilha_estoque);
static int movimentacao_valida(Pilha* pilha_destino, Carta* carta);
static int _movimentacao_valida_naipe(Carta* carta_topo, Carta* nova_carta);
static int _movimentacao_valida_valor(Carta* carta_topo, Carta* nova_carta);
static void move(Pilhas_Fileira* pilhas_fileira, int fileira_origem, int fileira_destino, int posicao_carta);

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
        pilhas_fileira->pilha[i] = cria_pilha_generica(52);
        pilhas_fileira->carta_virada[i] = i+1;
    }

    preenche_pilhas_fileira(pilhas_fileira, pilha_estoque);

    pilhas_fileira->move = move;

    return pilhas_fileira;
}

void free_pilhas_fileira(Pilhas_Fileira* pilhas_fileira) {
    int i;
    for (i = 0; i < 7; i++) {
        free_pilha(pilhas_fileira->pilha[i]);
    }
    free(pilhas_fileira);
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

static int movimentacao_valida(Pilha* pilha_destino, Carta* carta) {
    Carta* carta_topo = pilha_destino->cartas[pilha_destino->topo];
    if (_movimentacao_valida_naipe(carta_topo, carta))
        return _movimentacao_valida_valor(carta_topo, carta);
    return 0;
}

static int _movimentacao_valida_naipe(Carta* carta_topo, Carta* nova_carta) {
    switch (carta_topo->naipe) {
        case 'E': case 'e':
        case 'P': case 'p':
            switch (nova_carta->naipe) {
                case 'C': case 'c':
                case 'O': case 'o':
                    return 1;
                    break;
                default:
                    return 0;
                    break;
            }
            break;
        case 'C': case 'c':
        case 'O': case 'o':
            switch (nova_carta->naipe) {
                case 'E': case 'e':
                case 'P': case 'p':
                    return 1;
                    break;
                default:
                    return 0;
                    break;
            }
            break;
    }
}

static int _movimentacao_valida_valor(Carta* carta_topo, Carta* nova_carta) {
    switch (carta_topo->valor) {
        case 'K': case 'k':
            if (nova_carta->valor == 'Q' || nova_carta->valor == 'q')
                return 1;
            return 0;
            break;
        case 'Q': case 'q':
            if (nova_carta->valor == 'J' || nova_carta->valor == 'j')
                return 1;
            return 0;
            break;
        case 'J': case 'j':
            if (nova_carta->valor == '9')
                return 1;
            return 0;
            break;
        case '9':
            if (nova_carta->valor == '9')
                return 1;
            return 0;
            break;
        case '8':
            if (nova_carta->valor == '7')
                return 1;
            return 0;
            break;
        case '7':
            if (nova_carta->valor == '6')
                return 1;
            return 0;
            break;
        case '6':
            if (nova_carta->valor == '5')
                return 1;
            return 0;
            break;
        case '5':
            if (nova_carta->valor == '4')
                return 1;
            return 0;
            break;
        case '4':
            if (nova_carta->valor == '3')
                return 1;
            return 0;
            break;
        case '3':
            if (nova_carta->valor == '2')
                return 1;
            return 0;
            break;
        case '2':
            if (nova_carta->valor == '1')
                return 1;
            return 0;
            break;
        case '1':
            if (nova_carta->valor == 'A' || nova_carta->valor == 'a')
                return 1;
            return 0;
            break;
        case 'A': case 'a':
            return 0;
            break;
    }
}

static void move(Pilhas_Fileira* pilhas_fileira, int fileira_origem, int fileira_destino, int posicao_carta) {
    if ( posicao_carta < pilhas_fileira->carta_virada[fileira_origem] ) {
        printf("Posicao invalida!\n");
        return;
    }

    Pilha* pilha_origem = pilhas_fileira->pilha[fileira_origem];
    Pilha* pilha_destino = pilhas_fileira->pilha[fileira_destino];

    {
        Carta* carta_topo = pilha_origem->cartas[posicao_carta];
        if ( !movimentacao_valida(pilha_destino, carta_topo) ) {
            printf("Movimentacao invalida!\n");
            return;
        }
    }

    Pilha* pilha_auxiliar = cria_pilha_generica(52);

    int i;
    int total = pilha_origem->topo - posicao_carta;

    // Cria pilha auxiliar com cartas para mover
    for (i = 0; i < total; i++) {
        Carta* carta = pilha_origem->pop(pilha_origem);
        pilha_auxiliar->push(pilha_auxiliar, carta);
    }

    // Acerta posição da carta virada
    if (pilhas_fileira->carta_virada[fileira_origem] > pilha_origem->topo) {
        pilhas_fileira->carta_virada[fileira_origem] = pilha_origem->topo;
    }

    // Coloca cartas movidas na fileira de destino
    for (i = 0; i < total; i++) {
        Carta* carta = pilha_auxiliar->pop(pilha_auxiliar);
        pilha_destino->push(pilha_destino, carta);
    }

    free_pilha(pilha_auxiliar);
}

#endif // PILHA_FILEIRA_H_INCLUDED
