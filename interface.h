#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#ifdef __unix__
#elif defined(_WIN32) || defined(WIN32) 
#define OS_Windows
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paciencia.h"
#include "carta.h"

// Telas
#define TELA_INICIO     0
#define TELA_JOGO       1

// Constantes internas
#define LARGURA             200
#define BUFFER_SIZE         5000
#define SCREEN_BUFFER_SIZE  400000

// ***********************************************************************************************************

void Interface_Mostra_Tela(Paciencia* paciencia, int tela);

static void _interface_mostra_tela_principal(void);
static void _interface_mostra_tela_jogo(Paciencia* paciencia);

static void _interface_limpa_tela(void);
static void _interface_monta_linha_vazia(char* tela);
static void _interface_limpa_buffer(char* buffer);
static void _interface_adiciona_linha(char* tela, char* linha);

// ***********************************************************************************************************

void Interface_Mostra_Tela(Paciencia* paciencia, int tela) {
    switch (tela) {
        case TELA_INICIO:
            return _interface_mostra_tela_principal();
        case TELA_JOGO:
            return _interface_mostra_tela_jogo(paciencia);
    }    

}

// ***********************************************************************************************************

/**
 * Montagem de telas
 */

// Tela Principal
static void _interface_mostra_tela_principal(void) {
    _interface_limpa_tela();

    char tela[SCREEN_BUFFER_SIZE] = "";
    char linha[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE] = "";

    // Prepara cabecalho
    _interface_monta_linha_vazia(tela);
    _interface_monta_linha_vazia(tela);

    _interface_limpa_buffer(linha);
    _interface_limpa_buffer(buffer);

    strcat(linha, "PACIENCIA");

    puts(tela);
}

// Tela de jogo
static void _interface_mostra_tela_jogo(Paciencia* paciencia) {
    _interface_limpa_tela();

    char tela[SCREEN_BUFFER_SIZE] = "";
    char linha[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE] = "";

    // Prepara cabecalho
    _interface_monta_linha_vazia(tela);
    _interface_limpa_buffer(linha);
    _interface_limpa_buffer(buffer);
}

// ***********************************************************************************************************

/**
 * Funcoes auxiliares internas
 */

static void _interface_limpa_tela(void) {
    #ifdef OS_Windows
    /* Windows code */
    system("cls");
    #else
    /* GNU/Linux code */
    system("clear");
    #endif 
}

static void _interface_monta_linha_vazia(char* tela) {
    char buffer[BUFFER_SIZE] = "";
    int i;
    for (i = 0; i < LARGURA; i++)
        strcat(buffer, " ");
    _interface_adiciona_linha(tela, buffer);
}

static void _interface_limpa_buffer(char* buffer) {
    strcpy(buffer, "");
}

static void _interface_adiciona_linha(char* tela, char* linha) {
    strcat(tela, linha);
    strcat(tela, "\n");
}

static void _interface_preenche_lados(char* linha, char* texto) {
    int tamanho_texto = strlen(texto);
    int espaco_sobrando = LARGURA - tamanho_texto;

    int i;
    
}


#endif // INTERFACE_H_INCLUDED
