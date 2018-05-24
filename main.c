#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paciencia.h"

int main()
{

    Paciencia* paciencia = inicializa_jogo_paciencia();

    int* jogoRodando = 1;

    int count = 0;

    while (jogoRodando) {
        count++;
        printf("INICIO DE LOOP: %d\n", count);

        printf("Too String das Pilhas Fileiras: \n");
        char string[5000];
        paciencia->pilhas_fileira->toString(paciencia->pilhas_fileira, string);
        printf("%s", string);

        // printf("Too String das Pilhas Fileiras De Novo: \n");
        // paciencia->pilhas_fileira->toString(paciencia->pilhas_fileira, string);
        // printf("%s", string);

        // pilha_estoque_mostra_topo(paciencia->pilha_estoque);

        // // Testando movimento 1
        // printf("Testando movimento 1:\n");
        // printf("Pilha Descarte:\n");
        // printf("Sucesso - Movimento 1: %d\n", paciencia_movimento1(paciencia, PILHA_DESCARTE, 0));
        // imprimePilha(paciencia->pilha_descarte);

        // printf("Pilha Naipe:\n");
        // printf("Sucesso - Movimento 1: %d\n", paciencia_movimento1(paciencia, PILHA_NAIPE, 1));
        // imprimePilha(paciencia->pilhas_naipe->pilha[1]);

        // printf("Pilha Fileira:\n");
        // printf("Sucesso - Movimento 1: %d\n", paciencia_movimento1(paciencia, PILHA_FILEIRA, 1));
        // imprimePilha(paciencia->pilhas_fileira->pilha[1]);

        // // Testando movimento 2
        // printf("Testando movimento 2:\n");
        // printf("Sucesso Movimento 2: %d\n", paciencia_movimento2(paciencia, 3, 2));
        // printf("Pilha Naipe:\n");
        // imprimePilha(paciencia->pilhas_naipe->pilha[2]);
        // printf("Pilha Fileira:\n");
        // imprimePilha(paciencia->pilhas_fileira->pilha[3]);

        // // Testando movimento 3
        // printf("Testando movimento 3:\n");
        // printf("Sucesso movimento 3: %d\n", paciencia_movimento3(paciencia, 2, 3, 1));
        // imprimePilhasFileira(paciencia->pilhas_fileira);

        paciencia->finaliza(paciencia, &jogoRodando);
        printf("FIM de LOOP: %d\n", count);
        printf("Jogo Rodando: %d\n", jogoRodando);
    }

    // char string[20];
    // Carta* carta = nova_carta("AP");
    // carta->toString(carta, string);
    // printf("Carta to string: %s\n", string);
    // free_carta(carta);

    // carta = nova_carta("1C");
    // carta->toString(carta, string);
    // printf("Carta to string: %s\n", string);
    // free_carta(carta);

    printf("Hello world!\n");
    return 0;
}
