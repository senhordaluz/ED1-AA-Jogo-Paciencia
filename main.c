#include <stdio.h>
#include <stdlib.h>

#include "paciencia.h"

int main()
{
    Paciencia* paciencia = inicializa_jogo_paciencia();

    imprimePilhasFileira(paciencia->pilhas_fileira);
    imprimePilha(paciencia->pilha_estoque);

    int* jogoRodando = 1;

    int count = 0;

    while (jogoRodando) {
        count++;
        printf("FOI: %d\n", count);

        // Testando movimento 1
        printf("Pilha Descarte:\n");
        paciencia_movimento1(paciencia, PILHA_DESCARTE, 0);
        imprimePilha(paciencia->pilha_descarte);

        printf("Pilha Naipe:\n");
        paciencia_movimento1(paciencia, PILHA_NAIPE, 1);
        imprimePilha(paciencia->pilhas_naipe->pilha[1]);

        printf("Pilha Fileira:\n");
        paciencia_movimento1(paciencia, PILHA_FILEIRA, 1);
        imprimePilha(paciencia->pilhas_fileira->pilha[1]);

        paciencia->finaliza(paciencia, &jogoRodando);
    }

    printf("Hello world!\n");
    return 0;
}
