#include <stdio.h>
#include <stdlib.h>

#include "paciencia.h"

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
    Pilhas_Fileira* pilhas_fileira = cria_pilhas_fileira(pilha_estoque);
    Pilhas_Naipe* pilhas_naipe = cria_pilhas_naipe();
    Pilha* pilha_descarte = cria_pilha_descarte();

    imprimePilhasFileira(pilhas_fileira);
    imprimePilha(pilha_estoque);

    free_pilha(pilha_estoque);
    free_pilhas_fileira(pilhas_fileira);
    free_pilhas_naipe(pilhas_naipe);
    free_pilha(pilha_descarte);

    printf("Hello world!\n");
    return 0;
}
