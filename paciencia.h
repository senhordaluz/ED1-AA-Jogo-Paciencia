#ifndef PACIENCIA_H_INCLUDED
#define PACIENCIA_H_INCLUDED

#include "carta.h"
#include "pilha.h"
#include "pilha_estoque.h"
#include "pilha_naipe.h"
#include "pilha_descarte.h"
#include "pilha_fileira.h"

#define PILHA_ESTOQUE   0
#define PILHA_FILEIRA   1
#define PILHA_DESCARTE  2
#define PILHA_NAIPE     3

typedef struct paciencia Paciencia;
static struct paciencia {
    Pilha* pilha_estoque;
    Pilhas_Fileira* pilhas_fileira;
    Pilhas_Naipe* pilhas_naipe;
    Pilha* pilha_descarte;

    // Funcoes
    void (*reiniciar) (Paciencia* self);
    void (*finaliza) (Paciencia* self, int* estado_de_jogo);
};

Paciencia* inicializa_jogo_paciencia(void);
void free_paciencia(Paciencia* paciencia);
static void paciencia_finaliza(Paciencia* paciencia, int* estado_de_jogo);
static void paciencia_reiniciar(Paciencia* paciencia);
static int isFimDeJogo(Paciencia* paciencia);

static int paciencia_movimento1(Paciencia* paciencia, int tipo_pilha, int pilha_id);
static int paciencia_movimento2(Paciencia* paciencia, int fileira_id, int pilha_naipe_id);

Paciencia* inicializa_jogo_paciencia(void) {
    Paciencia* paciencia = (Paciencia*)malloc(sizeof(Paciencia));

    if (!paciencia) {
        printf("Erro: Nao foi possivel alocar memoria inicializar o jogo!\nO programa sera encerrado!\n");
        exit(1);
    }

    // Inicializa pilhas
    Pilha* pilha_estoque = cria_pilha_estoque();
    Pilhas_Fileira* pilhas_fileira = cria_pilhas_fileira(pilha_estoque);
    Pilhas_Naipe* pilhas_naipe = cria_pilhas_naipe();
    Pilha* pilha_descarte = cria_pilha_descarte();

    // Relaciona pilhas inicializadas a estrutura paciencia
    paciencia->pilha_estoque = pilha_estoque;
    paciencia->pilhas_fileira = pilhas_fileira;
    paciencia->pilhas_naipe = pilhas_naipe;
    paciencia->pilha_descarte = pilha_descarte;

    // Funcoes
    paciencia->finaliza = paciencia_finaliza;

    return paciencia;
}

void free_paciencia(Paciencia* paciencia) {
    free_pilha(paciencia->pilha_estoque);
    free_pilhas_fileira(paciencia->pilhas_fileira);
    free_pilhas_naipe(paciencia->pilhas_naipe);
    free_pilha(paciencia->pilha_descarte);

    free(paciencia);
}

static void paciencia_finaliza(Paciencia* paciencia, int* estado_de_jogo) {
    *estado_de_jogo = 0;
    free_paciencia(paciencia);
}

static void paciencia_reiniciar(Paciencia* paciencia) {
    // Reinicializa pilhas
    Pilha* pilha_estoque = paciencia->pilha_estoque;
    Pilhas_Fileira* pilhas_fileira = paciencia->pilhas_fileira;
    Pilhas_Naipe* pilhas_naipe = paciencia->pilhas_naipe;
    Pilha* pilha_descarte = paciencia->pilha_descarte;

    pilha_estoque->limpa(pilha_estoque);
    pilhas_fileira->limpa(pilhas_fileira, pilha_estoque);
    pilhas_naipe->limpa(pilhas_naipe);
    pilha_descarte->limpa(pilha_descarte);
}

static int isFimDeJogo(Paciencia* paciencia) {
    Pilha* pilha_estoque = paciencia->pilha_estoque;
    Pilhas_Fileira* pilhas_fileira = paciencia->pilhas_fileira;
    Pilhas_Naipe* pilhas_naipe = paciencia->pilhas_naipe;
    Pilha* pilha_descarte = paciencia->pilha_descarte;

    if (
            isPilhaVazia(pilha_estoque) &&
            pilhas_fileira->isVazia(pilhas_fileira) &&
            pilhas_naipe->cheia(pilhas_naipe) &&
            isPilhaVazia(pilha_descarte)
        ) {
        return 1;
    }
    return 0;
}

/**
 * Movimento 1:
 *  "Retirar cartas da pilha de estoque, uma por vez, e empilha-las nas pilhas de naipe, fileira ou descarte"
 */
static int paciencia_movimento1(Paciencia* paciencia, int tipo_pilha, int pilha_id) {
    /**
     * Casos de Erro
     */

    // Tipo de pilha invalido
    if ( tipo_pilha >= 4 ) {
        printf("Tipo de pilha invalido!\n");
        return 0;
    }

    // Tenta mover para propria pilha de estoque
    if ( tipo_pilha == PILHA_ESTOQUE ) {
        printf("Tipo de pilha invalido!\n");
        return 0;
    }

    // Variveis utilizadas
    Pilha* pilha_estoque = paciencia->pilha_estoque;
    Carta* carta = pilha_estoque->pop(pilha_estoque);

    // Verifica se a pilha estava vazia
    if (!carta) {
        printf("Pilha Vazia!\n");
        return 0;
    }

    /**
     * Casos de Sucesso
     */
    
    // Pilha de Descarte
    if ( tipo_pilha == PILHA_DESCARTE ) {
        Pilha* pilha_descarte = paciencia->pilha_descarte;
        int sucesso = pilha_descarte->push(pilha_descarte, carta);
        if (!sucesso) {
            pilha_estoque->push(pilha_estoque, carta);
            return 0;
        }
        return 1;
    }

    // Pilha Fileira
    if ( tipo_pilha == PILHA_FILEIRA ) {
        Pilhas_Fileira* pilhas_fileira = paciencia->pilhas_fileira;
        int sucesso = pilhas_fileira->push(pilhas_fileira, pilha_id, carta);
        if (!sucesso) {
            pilha_estoque->push(pilha_estoque, carta);
            return 0;
        }
        return 1;
    }

    // Pilha de Naipe
    if ( tipo_pilha == PILHA_NAIPE ) {
        Pilhas_Naipe* pilhas_naipe = paciencia->pilhas_naipe;
        int sucesso = pilhas_naipe->push(pilhas_naipe, pilha_id, carta);
        if (!sucesso) {
            pilha_estoque->push(pilha_estoque, carta);
            return 0;
        }
        return 1;
    }
}

/**
 * Movimento 2:
 *  "Retirar 1 carta virada para cima no topo de uma pilha de fileira e empilha-la em uma pilha de naipes."
 */
static int paciencia_movimento2(Paciencia* paciencia, int fileira_id, int pilha_naipe_id) {
    Pilhas_Fileira* pilhas_fileira = paciencia->pilhas_fileira;
    Pilhas_Naipe* pilhas_naipe = paciencia->pilhas_naipe;

    Carta* carta = pilhas_fileira->pop(pilhas_fileira, fileira_id);
    if (!carta) {
        printf("Pilha Vazia!\n");
        return 0;
    }

    int sucesso = pilhas_naipe->push(pilhas_naipe, pilha_naipe_id, carta);
    if (!sucesso) {
        pilhas_fileira->retorna(pilhas_fileira, fileira_id, carta);
        return 0;
    }
    return 1;
}

#endif // PACIENCIA_H_INCLUDED
