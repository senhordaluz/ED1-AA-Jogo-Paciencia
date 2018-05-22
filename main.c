#include <stdio.h>
#include <stdlib.h>

#include "carta.h"
#include "pilha.h"
#include "pilha_estoque.h"
#include "pilha_naipe.h"
#include "pilha_descarte.h"
#include "pilha_fileira.h"

int main()
{
    Carta* carta = nova_carta("AC");
    carta->print(carta);
    free_carta(carta);

    Pilha* pilha_estoque = cria_pilha_estoque();
    imprimePilha(pilha_estoque);
    printf("NOVA PILHA\n");
    pilha_estoque->limpa(pilha_estoque);
    imprimePilha(pilha_estoque);
    free_pilha(pilha_estoque);

    printf("Hello world!\n");
    return 0;
}
