#ifndef CARTA_H_INCLUDED
#define CARTA_H_INCLUDED

#include <string.h>

#define ESPADA  0
#define COPAS   1
#define PAUS    2
#define OURO    3

typedef struct carta Carta;
typedef struct carta* PCarta;
struct carta {
    char valor;
    char naipe;

    // Imprime a carta no console
    void (*print) (Carta* self);
    // Altera valor da carta
    void (*change) (Carta* self, char* valor);
    // Retorna enum com naipe
    int (*getNaipe) (Carta* self);
    // Retorna string
    void (*toString) (Carta* self, char* string);
};

Carta* nova_carta(char* valor);
void free_carta(Carta* carta);
static void carta_print(Carta* self);
static void carta_troca(Carta* carta, char* valor);
static int carta_isValorValido(char* valor);
static int carta_getNaipe(Carta* carta);
static void carta_toString(Carta* carta, char* string);

Carta* nova_carta(char* valor) {
    if ( carta_isValorValido(valor) ) {
        Carta* carta = (Carta*) malloc(sizeof(Carta));

        if (!carta) {
            printf("Erro: Nao foi possivel alocar memoria para a Carta!\nO programa sera encerrado!\n");
            exit(1);
        }

        carta->valor = valor[0];
        carta->naipe = valor[1];

        carta->print = carta_print;
        carta->change = carta_troca;
        carta->getNaipe = carta_getNaipe;
        carta->toString = carta_toString;

        return carta;
    }
    printf("Valor invalido!\n");
    return NULL;
}

void free_carta(Carta* carta) {
    free(carta);
}

static void carta_print(Carta* carta) {
    char string[20];
    carta->toString(carta, string);
    puts(string);
}

static void carta_troca(Carta* carta, char valor[2]) {
    if ( carta_isValorValido(valor) ) {
        carta->valor = valor[0];
        carta->naipe = valor[1];
        return;
    }
    printf("Valor invalido\n");
}

static int carta_isValorValido(char* valor) {
    int valor_valido = 0;
    int naipe_valido = 0;

    switch (valor[0]) {
        case 'A':
        case 'a':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'J':
        case 'j':
        case 'Q':
        case 'q':
        case 'K':
        case 'k':
            valor_valido = 1;
            break;
    }

    switch (valor[1]) {
        case 'E':
        case 'e':
        case 'C':
        case 'c':
        case 'P':
        case 'p':
        case 'O':
        case 'o':
            naipe_valido = 1;
            break;
    }

    if (valor_valido && naipe_valido)
        return 1;
    return 0;
}

static int carta_getNaipe(Carta* carta) {
    switch (carta->naipe) {
        case 'E':
        case 'e':
            return ESPADA;
        case 'C':
        case 'c':
            return COPAS;
        case 'P':
        case 'p':
            return PAUS;
        case 'O':
        case 'o':
            return OURO;
    }
    return NULL;
}

static void carta_toString(Carta* carta, char* string) {
    strcpy(string, "");
    switch (carta->valor) {
        case 'A':
        case 'a':
            strcat(string, "As");
            break;
        case 'J':
        case 'j':
            strcat(string, "Valete");
            break;
        case 'K':
        case 'k':
            strcat(string, "Rei");
            break;
        case 'Q':
        case 'q':
            strcat(string, "Dama");
            break;
        case '1':
            strcat(string, "1");
            break;
        case '2':
            strcat(string, "2");
            break;
        case '3':
            strcat(string, "3");
            break;
        case '4':
            strcat(string, "4");
            break;
        case '5':
            strcat(string, "5");
            break;
        case '6':
            strcat(string, "6");
            break;
        case '7':
            strcat(string, "7");
            break;
        case '8':
            strcat(string, "8");
            break;
        case '9':
            strcat(string, "9");
            break;
    }
    switch (carta->naipe) {
        case 'E':
        case 'e':
            strcat(string, " de espada");
            break;
        case 'C':
        case 'c':
            strcat(string, " de copas");
            break;
        case 'P':
        case 'p':
            strcat(string, " de paus");
            break;
        case 'O':
        case 'o':
            strcat(string, " de ouro");
            break;
    }
}

#endif // CARTA_H_INCLUDED
