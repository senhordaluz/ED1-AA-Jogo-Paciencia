#ifndef PILHA_NAIPE_H_INCLUDED
#define PILHA_NAIPE_H_INCLUDED

#include "pilha.h"
#include "carta.h"

typedef struct pilhas_naipe Pilhas_Naipe;
static struct pilhas_naipe {
    int naipes[4];
    PPilha pilha[4];

    // Adiciona nova carta
    int (*push) (Pilhas_Naipe* self, int pilha_id, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilhas_Naipe* self, int naipe);
    // Verifica se as pilhas de naipe estao cheias
    int (*cheia) (Pilhas_Naipe* self);
    // Limpa pilha
    void (*limpa) (Pilhas_Naipe* self);
};

Pilhas_Naipe* cria_pilhas_naipe(void);
void free_pilhas_naipe(Pilhas_Naipe* pilhas_naipe);
static int isNaipeAlocado(Pilhas_Naipe* pilhas_naipe);
static int isNaipeAlocado_outraPilha(Pilhas_Naipe* pilhas_naipe, int pilha_id);
static int pilhas_naipe_push(Pilhas_Naipe* pilhas_naipe, int naipe, Carta* carta);
static Carta* pilhas_naipe_pop(Pilhas_Naipe* pilhas_naipe, int naipe);
static int pilhas_naipe_movimentacao_valida(Pilha* pilha_destino, Carta* carta);
static int pilhas_naipe_movimentacao_valida_naipe(Carta* carta_topo, Carta* nova_carta);
static int pilhas_naipe_movimentacao_valida_valor(Carta* carta_topo, Carta* nova_carta);
static int pilhas_naipe_limpa(Pilhas_Naipe* pilhas_naipe);
static int pilhas_naipe_cheias(Pilhas_Naipe* pilhas_naipe);

Pilhas_Naipe* cria_pilhas_naipe(void) {
    Pilhas_Naipe* pilhas_naipe = (Pilhas_Naipe*)malloc(sizeof(Pilhas_Naipe));

    if (!pilhas_naipe) {
        printf("Erro: Nao foi possivel alocar memoria para as pilhas de naipe!\nO programa sera encerrado!\n");
        exit(1);
    }

    int i;
    for (i = 0; i < 4; i++) {
        pilhas_naipe->naipes[i] = 4;
        pilhas_naipe->pilha[i] = cria_pilha_generica(13);
    }

    pilhas_naipe->push = pilhas_naipe_push;
    pilhas_naipe->pop = pilhas_naipe_pop;
    pilhas_naipe->cheia = pilhas_naipe_cheias;
    pilhas_naipe->limpa = pilhas_naipe_limpa;

    return pilhas_naipe;
}

void free_pilhas_naipe(Pilhas_Naipe* pilhas_naipe) {
    int i;
    for (i = 0; i < 4; i++) {
        free_pilha(pilhas_naipe->pilha[i]);
    }
    free(pilhas_naipe);
}

static int isNaipeAlocado(Pilhas_Naipe* pilhas_naipe) {
    int i;
    for (i = 0; i < 4; i++) {
        if ( pilhas_naipe->naipes[i] != 4 )
            return 1;
    }
    return 0;
}

static int isNaipeAlocado_outraPilha(Pilhas_Naipe* pilhas_naipe, int pilha_id) {
    int i;
    for (i = 0; i < 4; i++) {
        if ( i == pilha_id )
            continue;
        if ( pilhas_naipe->naipes[i] != 4 )
            return 1;
    }
    return 0;
}

static int pilhas_naipe_push(Pilhas_Naipe* pilhas_naipe, int pilha_id, Carta* carta) {
    // Verifica se o id enviado e valido
    if (pilha_id >= 4) {
        printf("id de pilha invalido!\n");
        return 0;
    }

    // Verifica se o naipe ja foi alocado em outra pilha
    if ( isNaipeAlocado_outraPilha(pilhas_naipe, pilha_id) ) {
        printf("Movimento invalido!\n");
        return 0;
    }

    Pilha* pilha = pilhas_naipe->pilha[pilha_id];

    // Verifica se a movimentacao e valida
    if ( !pilhas_naipe_movimentacao_valida(pilha, carta) ) {
        printf("Movimento invalido!\n");
        return 0;
    }

    // Caso a movimentacao seja valida e a pilha esteja vazia, salva qual naipe esta pilha pertencera
    if ( isPilhaVazia(pilha) ) {
        int naipe = carta->getNaipe(carta);
        pilhas_naipe->naipes[pilha_id] = naipe;
    }

    // Realiza o push
    return pilha->push(pilha, carta);
}

static Carta* pilhas_naipe_pop(Pilhas_Naipe* pilhas_naipe, int naipe) {
    if (naipe >= 4) {
        printf("Pilha vazia ou ID inválido!\n");
        return NULL;
    }
    Pilha* pilha = pilhas_naipe->pilha[pilhas_naipe->naipes[naipe]];
    return pilha->pop(pilha);
}

static int pilhas_naipe_movimentacao_valida(Pilha* pilha_destino, Carta* carta) {
    // Caso a pilha esteja vazia, a primeira carta deve ser o As
    if ( isPilhaVazia(pilha_destino) ) {
        if ( carta->valor == 'A' || carta->valor == 'a' )
            return 1;
        else
            return 0;
    }
    
    // Caso contratio, verifica sequencia ascendente
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
        case 'P': case 'p':
            if (nova_carta->naipe == 'P' || nova_carta->naipe == 'p')
                return 1;
            return 0;
        case 'C': case 'c':
            if (nova_carta->naipe == 'C' || nova_carta->naipe == 'c')
                return 1;
            return 0;
        case 'O': case 'o':
            if (nova_carta->naipe == 'O' || nova_carta->naipe == 'o')
                return 1;
            return 0;
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

static int pilhas_naipe_limpa(Pilhas_Naipe* pilhas_naipe) {
    int i;
    for (i = 0; i < 4; i++) {
        Pilha* pilha = pilhas_naipe->pilha[i];
        pilha->limpa(pilha);
    }
}

static int pilhas_naipe_cheias(Pilhas_Naipe* pilhas_naipe) {
    int i;
    for (i = 0; i < 4; i++) {
        Pilha* pilha = pilhas_naipe->pilha[i];
        if (!isPilhaCheia(pilha))
            return 0;
    }
    return 1;
}
#endif // PILHA_NAIPE_H_INCLUDED
