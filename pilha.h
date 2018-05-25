#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "carta.h"

typedef struct pilha Pilha;
typedef struct pilha* PPilha;
struct pilha {
    // Topo de pilha
    int topo;
    // Vetor de cartas
    PCarta* cartas;
    // Total de cartas
    int tamanho;

    // Adiciona nova carta retorna 1: sucesso 0: erro
    int (*push) (Pilha* self, Carta* carta);
    // Retira carta da pilha e retorna valor
    Carta* (*pop) (Pilha* self);
    // Limpa pilha
    void (*limpa) (Pilha* self);
    // Monta string da pilha
    void (*toString) (Pilha* self, char* string);
};

Pilha* cria_pilha_generica(int tamanho);
void free_pilha(Pilha* pilha);
static int pilha_push(Pilha* pilha, Carta* carta);
static Carta* pilha_pop(Pilha* pilha);
void pilha_limpa(Pilha* pilha);
void imprimePilha(Pilha* pilha);
int isPilhaVazia(Pilha* pilha);
int isPilhaCheia(Pilha* pilha);
static void pilha_toString(Pilha* pilha, char* string);

Pilha* cria_pilha_generica(int tamanho) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));

    if (!pilha) {
        printf("Erro: Nao foi possivel alocar memoria para a pilha de %d cartas!\nO programa sera encerrado!\n", tamanho);
        exit(1);
    }

    pilha->topo = tamanho;
    pilha->tamanho = tamanho;
    pilha->cartas = malloc(tamanho * sizeof(Carta));

    pilha->push = pilha_push;
    pilha->pop = pilha_pop;
    pilha->limpa = pilha_limpa;
    pilha->toString = pilha_toString;

    return pilha;
}

void free_pilha(Pilha* pilha) {
    pilha_limpa(pilha);
    free(pilha);
}

static int pilha_push(Pilha* pilha, Carta* carta) {
    if (!isPilhaCheia(pilha)) {
        if (isPilhaVazia(pilha))
            pilha->topo = 0;
        else
            pilha->topo++;
        pilha->cartas[pilha->topo] = carta;
        return 1;
    }
    printf("Pilha cheia!\n");
    return 0;
}

static Carta* pilha_pop(Pilha* pilha) {
    if (!isPilhaVazia(pilha)) {
        Carta* carta = pilha->cartas[pilha->topo];
        pilha->cartas[pilha->topo] = NULL;
        pilha->topo--;
        return carta;
    }
    printf("Pilha vazia!\n");
    return NULL;
}

void pilha_limpa(Pilha* pilha) {
    if ( !isPilhaVazia(pilha) ) {
        int i;
        for (i = 0; i <= pilha->topo; i++) {
            Carta* carta = pilha->pop(pilha);
            free_carta(carta);
        }
        pilha->topo = pilha->tamanho;
    }
}

void imprimePilha(Pilha* pilha) {
    char string[600];
    pilha->toString(pilha, string);
    printf("%s", string);
    return;
}

int isPilhaVazia(Pilha* pilha) {
    if (pilha->topo == pilha->tamanho)
        return 1;
    return 0;
}

int isPilhaCheia(Pilha* pilha) {
    if (pilha->topo == pilha->tamanho-1)
        return 1;
    return 0;
}

static void pilha_toString(Pilha* pilha, char* string) {
    strcpy(string, "");
    if ( !isPilhaVazia(pilha) ) {
        int i;
        char cartaString[20];
        for (i = 0; i <= pilha->topo; i++) {
            Carta* carta = pilha->cartas[i];
            carta->toString(carta, cartaString);
            strcat(cartaString, "\n");
            strcat(string, cartaString);
        }
    }
}

#endif // PILHA_H_INCLUDED
