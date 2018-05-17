#include <stdio.h>
#include <stdlib.h>

#include "carta.h"
#include "pilha_estoque.h"

int main()
{
    Carta* carta = nova_carta("AC");
    carta->print(carta);
    free_carta(carta);

    Pilha* pilha_estoque = cria_pilha_estoque();
    pilha_estoque->free(pilha_estoque);

    printf("Hello world!\n");
    return 0;
}
