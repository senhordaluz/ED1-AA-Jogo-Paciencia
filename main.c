#include <stdio.h>
#include <stdlib.h>

#include "carta.h"

int main()
{
    Carta* carta = nova_carta("AC");
    carta->print(carta);
    free_carta(carta);

    printf("Hello world!\n");
    return 0;
}
