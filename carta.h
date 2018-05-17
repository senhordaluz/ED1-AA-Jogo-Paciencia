#ifndef CARTA_H_INCLUDED
#define CARTA_H_INCLUDED

typedef struct carta Carta;
typedef struct carta* PCarta;
static struct carta {
    char valor;
    char naipe;

    void (*print) (Carta* self);
    void (*change) (Carta* carta, char* valor);
};

Carta* nova_carta(char* valor);
void free_carta(Carta* carta);
static void _print(Carta* self);
static void _troca(Carta* carta, char* valor);
static int _isValorValido(char* valor);

Carta* nova_carta(char* valor) {
    if ( _isValorValido(valor) ) {
        Carta* carta = (Carta*) malloc(sizeof(Carta));

        carta->valor = valor[0];
        carta->naipe = valor[1];

        carta->print = _print;
        carta->change = _troca;

        if (!carta) {
            printf("Erro: Nao foi possivel alocar memoria para a Carta!\nO programa sera encerrado!\n");
            exit(1);
        }

        return carta;
    }
    printf("Valor invalido!\n");
    return NULL;
}

void free_carta(Carta* carta) {
    free(carta);
}

static void _print(Carta* self) {
    int ch = 0;
    char *valor, *naipe;
    switch (self->valor) {
        case 'A':
        case 'a':
            valor = "As";
            break;
        case 'J':
        case 'j':
            valor = "Valete";
            break;
        case 'K':
        case 'k':
            valor = "Rei";
            break;
        case 'Q':
        case 'q':
            valor = "Dama";
            break;
        default:
            ch = 1;
            valor = self->valor;
            break;
    }
    switch (self->naipe) {
        case 'E':
        case 'e':
            naipe = "espada";
            break;
        case 'C':
        case 'c':
            naipe = "copas";
            break;
        case 'P':
        case 'p':
            naipe = "copas";
            break;
        case 'O':
        case 'o':
            naipe = "ouro";
            break;
    }
    if (ch)
        printf("%c de %s\n", valor, naipe);
    else
        printf("%s de %s\n", valor, naipe);
}

static void _troca(Carta* carta, char valor[2]) {
    if ( _isValorValido(valor) ) {
        carta->valor = valor[0];
        carta->naipe = valor[1];
        return;
    }
    printf("Valor invalido\n");
}

static int _isValorValido(char* valor) {
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

#endif // CARTA_H_INCLUDED
