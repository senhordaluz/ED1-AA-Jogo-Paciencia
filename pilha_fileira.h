#ifndef PILHA_FILEIRA_H_INCLUDED
#define PILHA_FILEIRA_H_INCLUDED

#include "pilha.h"
#include "carta.h"

typedef struct pilhas_fileira Pilhas_Fileira;
static struct pilhas_fileira {
    int carta_virada[7];
    PPilha pilha[7];

    // Adiciona nova carta
    int (*push) (Pilhas_Fileira* self, int fileira_id, Carta* carta);
    // Retorna carta para pilha apos movimentacao falha
    int (*retorna) (Pilhas_Fileira* self, int fileira_id, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilhas_Fileira* self, int fileira_id);
    // Move cartas viradas de uma fileira para outra
    int (*move) (Pilhas_Fileira* self, int fileira_origem, int fileira_destino, int posicao_carta);
    // Limpa pilha
    void (*limpa) (Pilhas_Fileira* self, Pilha* pilha_estoque);
    // Verifica se as pilhas estao vazias
    int (*isVazia) (Pilhas_Fileira* self);
};

Pilhas_Fileira* cria_pilhas_fileira(Pilha* pilha_estoque);
static void preenche_pilhas_fileira(Pilhas_Fileira* pilhas_fileira, Pilha* pilha_estoque);
static void reordena_topo(Pilhas_Fileira* pilhas_fileira, int fileira_id);
static int pilha_fileira_movimentacao_valida(Pilha* pilha_destino, Carta* carta);
static int pilha_fileira_movimentacao_valida_naipe(Carta* carta_topo, Carta* nova_carta);
static int pilha_fileira_movimentacao_valida_valor(Carta* carta_topo, Carta* nova_carta);
static int pilhas_fileira_move(Pilhas_Fileira* pilhas_fileira, int fileira_origem, int fileira_destino, int posicao_carta);
static int pilhas_fileira_push(Pilhas_Fileira* pilhas_fileira, int fileira_id, Carta* carta);
static int pilhas_fileira_return(Pilhas_Fileira* pilhas_fileira, int fileira_id, Carta* carta);
static Carta* pilhas_fileira_pop(Pilhas_Fileira* pilhas_fileira, int fileira_id);
static void pilhas_fileira_limpa(Pilhas_Fileira* pilhas_fileira, Pilha* pilha_estoque);
void pilhas_fileira_imprime_fileira(Pilhas_Fileira* pilhas_fileira, int fileira_id);
void imprimePilhasFileira(Pilhas_Fileira* pilhas_fileira);
static int pilhas_fileira_isVazia(Pilhas_Fileira* pilhas_fileira);

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
    }

    preenche_pilhas_fileira(pilhas_fileira, pilha_estoque);

    pilhas_fileira->push = pilhas_fileira_push;
    pilhas_fileira->retorna = pilhas_fileira_return;
    pilhas_fileira->pop = pilhas_fileira_pop;
    pilhas_fileira->move = pilhas_fileira_move;
    pilhas_fileira->limpa = pilhas_fileira_limpa;
    pilhas_fileira->isVazia = pilhas_fileira_isVazia;

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
    Pilha* pilha;
    // Fileira 1
    pilha = pilhas_fileira->pilha[0];
    pilha->push(pilhas_fileira->pilha[0], pilha_estoque->pop(pilha_estoque));
    pilhas_fileira->carta_virada[0] = 0;

    // Fileira 2
    pilha = pilhas_fileira->pilha[1];
    for (i = 0; i < 2; i++) {
        pilha->push(pilha, pilha_estoque->pop(pilha_estoque));
    }
    pilhas_fileira->carta_virada[1] = 1;

    // Fileira 3
    pilha = pilhas_fileira->pilha[2];
    for (i = 0; i < 3; i++) {
        pilha->push(pilha, pilha_estoque->pop(pilha_estoque));
    }
    pilhas_fileira->carta_virada[2] = 2;

    // Fileira 4
    pilha = pilhas_fileira->pilha[3];
    for (i = 0; i < 4; i++) {
        pilha->push(pilha, pilha_estoque->pop(pilha_estoque));
    }
    pilhas_fileira->carta_virada[3] = 3;

    // Fileira 5
    pilha = pilhas_fileira->pilha[4];
    for (i = 0; i < 5; i++) {
        pilha->push(pilha, pilha_estoque->pop(pilha_estoque));
    }
    pilhas_fileira->carta_virada[4] = 4;

    // Fileira 6
    pilha = pilhas_fileira->pilha[5];
    for (i = 0; i < 6; i++) {
        pilha->push(pilha, pilha_estoque->pop(pilha_estoque));
    }
    pilhas_fileira->carta_virada[5] = 5;

    // Fileira 7
    pilha = pilhas_fileira->pilha[6];
    for (i = 0; i < 7; i++) {
        pilha->push(pilha, pilha_estoque->pop(pilha_estoque));
    }
    pilhas_fileira->carta_virada[6] = 6;
}

static void reordena_topo(Pilhas_Fileira* pilhas_fileira, int fileira_id) {
    Pilha* pilha = pilhas_fileira->pilha[fileira_id];
    if (pilhas_fileira->carta_virada[fileira_id] > pilha->topo) {
        pilhas_fileira->carta_virada[fileira_id] = pilha->topo;
    }
}

static int pilha_fileira_movimentacao_valida(Pilha* pilha_destino, Carta* carta) {
    Carta* carta_topo = pilha_destino->cartas[pilha_destino->topo];
    if (pilha_fileira_movimentacao_valida_naipe(carta_topo, carta))
        return pilha_fileira_movimentacao_valida_valor(carta_topo, carta);
    return 0;
}

static int pilha_fileira_movimentacao_valida_naipe(Carta* carta_topo, Carta* nova_carta) {
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

static int pilha_fileira_movimentacao_valida_valor(Carta* carta_topo, Carta* nova_carta) {
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

static int pilhas_fileira_move(Pilhas_Fileira* pilhas_fileira, int fileira_origem, int fileira_destino, int posicao_carta) {
    if ( posicao_carta < pilhas_fileira->carta_virada[fileira_origem] ) {
        printf("Posicao invalida!\n");
        return 0;
    }

    Pilha* pilha_origem = pilhas_fileira->pilha[fileira_origem];
    Pilha* pilha_destino = pilhas_fileira->pilha[fileira_destino];

    {
        Carta* carta_topo = pilha_origem->cartas[posicao_carta];
        if ( !pilha_fileira_movimentacao_valida(pilha_destino, carta_topo) ) {
            printf("Movimento invalido!\n");
            return 0;
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
    reordena_topo(pilhas_fileira, fileira_origem);

    // Coloca cartas movidas na fileira de destino
    for (i = 0; i < total; i++) {
        Carta* carta = pilha_auxiliar->pop(pilha_auxiliar);
        pilha_destino->push(pilha_destino, carta);
    }

    free_pilha(pilha_auxiliar);

    return 1;
}

static int pilhas_fileira_push(Pilhas_Fileira* pilhas_fileira, int fileira_id, Carta* carta) {
    Pilha* pilha_destino = pilhas_fileira->pilha[fileira_id];

    if ( !pilha_fileira_movimentacao_valida(pilha_destino, carta) ) {
        printf("Movimento invalido!\n");
        return 0;
    }

    return pilha_destino->push(pilha_destino, carta);
}

static int pilhas_fileira_return(Pilhas_Fileira* pilhas_fileira, int fileira_id, Carta* carta) {
    Pilha* pilha_destino = pilhas_fileira->pilha[fileira_id];

    return pilha_destino->push(pilha_destino, carta);
}

static Carta* pilhas_fileira_pop(Pilhas_Fileira* pilhas_fileira, int fileira_id) {
    Pilha* pilha = pilhas_fileira->pilha[fileira_id];
    Carta* carta = pilha->pop(pilha);

    reordena_topo(pilhas_fileira, fileira_id);

    return carta;
}

static void pilhas_fileira_limpa(Pilhas_Fileira* pilhas_fileira, Pilha* pilha_estoque) {
    int i;
    for (i = 0; i < 7; i++) {
        Pilha* pilha = pilhas_fileira->pilha[i];
        pilha->limpa(pilha);
    }
    preenche_pilhas_fileira(pilhas_fileira, pilha_estoque);
}

void pilhas_fileira_imprime_fileira(Pilhas_Fileira* pilhas_fileira, int fileira_id) {
    if (fileira_id >= 7) {
        printf("Fileira inválida!\n");
        return;
    }

    Pilha* pilha = pilhas_fileira->pilha[fileira_id];

    int i;
    int carta_virada = pilhas_fileira->carta_virada[fileira_id];
    for (i = carta_virada; i <= pilha->topo; i++) {
        Carta* carta = pilha->cartas[i];
        carta->print(carta);
    }
}

void imprimePilhasFileira(Pilhas_Fileira* pilhas_fileira) {
    int i;
    for (i = 0; i < 7; i++) {
        printf("Fileira %d!\n", i+1);
        pilhas_fileira_imprime_fileira(pilhas_fileira, i);
    }
}

static int pilhas_fileira_isVazia(Pilhas_Fileira* pilhas_fileira) {
    int i;
    for (i = 0; i < 7; i++) {
        Pilha* pilha = pilhas_fileira->pilha[i];
        if ( !isPilhaVazia(pilha) )
            return 0;
    }
    return 1;
}

#endif // PILHA_FILEIRA_H_INCLUDED
