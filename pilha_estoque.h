#ifndef PILHA_ESTOQUE_H_INCLUDED
#define PILHA_ESTOQUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pilha.h"
#include "carta.h"

Pilha* cria_pilha_estoque(void);
static void cria_baralho_ordenado(Pilha* pilha);
static void embaralhar(Pilha* pilha);
static void pilha_estoque_limpa(Pilha* pilha);

Pilha* cria_pilha_estoque(void) {
    // Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));

    // if (!pilha) {
    //     printf("Erro: Nao foi possivel alocar memoria para a pilha de estoque!\nO programa sera encerrado!\n");
    //     exit(1);
    // }

    // pilha->topo = 52;
    // pilha->tamanho = 52;
    // pilha->cartas = (Pilha*)malloc(52 * sizeof(Pilha));

    // pilha->push = _pilha_push;
    // pilha->pop = _pilha_pop;

    Pilha* pilha = cria_pilha_generica(52);

    pilha->limpa = pilha_estoque_limpa;

    // cria_baralho_ordenado(pilha);
    // embaralhar(pilha);

    return pilha;
}

static void cria_baralho_ordenado(Pilha* pilha) {
    // Espada
    pilha->push(pilha,nova_carta("AE"));
    pilha->push(pilha,nova_carta("1E"));
    pilha->push(pilha,nova_carta("2E"));
    pilha->push(pilha,nova_carta("3E"));
    pilha->push(pilha,nova_carta("4E"));
    pilha->push(pilha,nova_carta("5E"));
    pilha->push(pilha,nova_carta("6E"));
    pilha->push(pilha,nova_carta("7E"));
    pilha->push(pilha,nova_carta("8E"));
    pilha->push(pilha,nova_carta("9E"));
    pilha->push(pilha,nova_carta("JE"));
    pilha->push(pilha,nova_carta("QE"));
    pilha->push(pilha,nova_carta("KE"));

    // Copas
    pilha->push(pilha,nova_carta("AC"));
    pilha->push(pilha,nova_carta("1C"));
    pilha->push(pilha,nova_carta("2C"));
    pilha->push(pilha,nova_carta("3C"));
    pilha->push(pilha,nova_carta("4C"));
    pilha->push(pilha,nova_carta("5C"));
    pilha->push(pilha,nova_carta("6C"));
    pilha->push(pilha,nova_carta("7C"));
    pilha->push(pilha,nova_carta("8C"));
    pilha->push(pilha,nova_carta("9C"));
    pilha->push(pilha,nova_carta("JC"));
    pilha->push(pilha,nova_carta("QC"));
    pilha->push(pilha,nova_carta("KC"));

    // Paus
    pilha->push(pilha,nova_carta("AP"));
    pilha->push(pilha,nova_carta("1P"));
    pilha->push(pilha,nova_carta("2P"));
    pilha->push(pilha,nova_carta("3P"));
    pilha->push(pilha,nova_carta("4P"));
    pilha->push(pilha,nova_carta("5P"));
    pilha->push(pilha,nova_carta("6P"));
    pilha->push(pilha,nova_carta("7P"));
    pilha->push(pilha,nova_carta("8P"));
    pilha->push(pilha,nova_carta("9P"));
    pilha->push(pilha,nova_carta("JP"));
    pilha->push(pilha,nova_carta("QP"));
    pilha->push(pilha,nova_carta("KP"));

    // Ouro
    pilha->push(pilha,nova_carta("AO"));
    pilha->push(pilha,nova_carta("1O"));
    pilha->push(pilha,nova_carta("2O"));
    pilha->push(pilha,nova_carta("3O"));
    pilha->push(pilha,nova_carta("4O"));
    pilha->push(pilha,nova_carta("5O"));
    pilha->push(pilha,nova_carta("6O"));
    pilha->push(pilha,nova_carta("7O"));
    pilha->push(pilha,nova_carta("8O"));
    pilha->push(pilha,nova_carta("9O"));
    pilha->push(pilha,nova_carta("JO"));
    pilha->push(pilha,nova_carta("QO"));
    pilha->push(pilha,nova_carta("KO"));
}

static void embaralhar(Pilha* pilha) {
    size_t n = 52;
    // PCarta array[52] = pilha->cartas;
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          Carta* t = pilha->cartas[j];
          pilha->cartas[j] = pilha->cartas[i];
          pilha->cartas[i] = t;
        }
    }
}

static void pilha_estoque_limpa(Pilha* pilha) {
    pilha_limpa(pilha);
    cria_baralho_ordenado(pilha);
    embaralhar(pilha);
}

static void pilha_estoque_mostra_topo(Pilha* pilha) {
    Carta* carta = pilha->cartas[pilha->topo];
    carta->print(carta);
}

#endif // PILHA_ESTOQUE_H_INCLUDED
