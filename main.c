#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "paciencia.h"

int main()
{

    int jogoRodando = 1;

    Paciencia* paciencia = inicializa_paciencia(&jogoRodando);

    int count = 0;

    while (jogoRodando) {
        count++;

        Interface_Mostra_Tela(paciencia);

        printf("FIM de LOOP: %d\n", count);
        printf("Jogo Rodando: %d\n", jogoRodando);
    }

    printf("Hello world!\n");
    return 0;
}
