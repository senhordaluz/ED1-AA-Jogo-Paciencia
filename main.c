#include <stdio.h>
#include <stdlib.h>

#include "paciencia.h"

int main()
{
    Paciencia* paciencia = inicializa_jogo_paciencia();

    imprimePilhasFileira(paciencia->pilhas_fileira);
    imprimePilha(paciencia->pilha_estoque);

    free_paciencia(paciencia);

    printf("Hello world!\n");
    return 0;
}
