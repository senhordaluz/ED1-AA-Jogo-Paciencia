#ifndef PACIENCIA_H_INCLUDED
#define PACIENCIA_H_INCLUDED

#include "carta.h"
#include "pilha.h"
#include "pilha_estoque.h"
#include "pilha_naipe.h"
#include "pilha_descarte.h"
#include "pilha_fileira.h"

typedef struct paciencia Paciencia;
static struct paciencia {
    Pilha* pilha_estoque;
    Pilhas_Fileira* pilhas_fileira;
    Pilhas_Naipe* pilhas_naipe;
    Pilha* pilha_descarte;
};

Paciencia* inicializa_jogo_paciencia(void);
void free_paciencia(Paciencia* paciencia);

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

    return paciencia;
}

void free_paciencia(Paciencia* paciencia) {
    free_pilha(paciencia->pilha_estoque);
    free_pilhas_fileira(paciencia->pilhas_fileira);
    free_pilhas_naipe(paciencia->pilhas_naipe);
    free_pilha(paciencia->pilha_descarte);

    free(paciencia);
}

#endif // PACIENCIA_H_INCLUDED
