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
#define TELA_CREDITOS   2
#define SAIR            4

// Constantes internas
#define LARGURA             150
#define BUFFER_SIZE         5000
#define SCREEN_BUFFER_SIZE  400000

// ***********************************************************************************************************

void Interface_Mostra_Tela(Paciencia* paciencia);

static void _interface_mostra_tela_principal(Paciencia* paciencia);
static void _interface_mostra_tela_jogo(Paciencia* paciencia);

static void _interface_limpa_tela(void);
static void _interface_monta_linha_vazia(char* tela);
static void _interface_monta_linha_separacao(char* tela);
static void _interface_limpa_buffer(char* buffer);
static void _interface_adiciona_linha(char* tela, char* linha);
static void _interface_preenche_lados(char* linha, char* texto);

static void _interface_tela_principal_opcoes(Paciencia* paciencia);

static int _interface_controle_entrada_opcoes(int opcoes_validas);

// ***********************************************************************************************************

void Interface_Mostra_Tela(Paciencia* paciencia) {
    switch (paciencia->tela_atual) {
        case TELA_INICIO:
            return _interface_mostra_tela_principal(paciencia);
        case TELA_JOGO:
            return _interface_mostra_tela_jogo(paciencia);
        case TELA_CREDITOS: // Redireciona para tela principal para testes
            return _interface_mostra_tela_principal(paciencia);
        case SAIR:
            return paciencia->finaliza(paciencia);
    }
}

// ***********************************************************************************************************

/**
 * Montagem de telas
 */

// Tela Principal
static void _interface_mostra_tela_principal(Paciencia* paciencia) {
    _interface_limpa_tela();

    char tela[SCREEN_BUFFER_SIZE] = "";
    char linha[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE] = "";

    // Prepara cabecalho
    _interface_monta_linha_separacao(tela);
    
    _interface_monta_linha_vazia(tela);
    _interface_monta_linha_vazia(tela);

    _interface_limpa_buffer(linha);
    _interface_limpa_buffer(buffer);

    _interface_preenche_lados(linha, "PACIENCIA");
    _interface_adiciona_linha(tela, linha);

    _interface_monta_linha_vazia(tela);
    _interface_monta_linha_vazia(tela);

    // Footer
    _interface_monta_linha_separacao(tela);

    // Preenche tela
    puts(tela);

    // Exibe opcoes
    _interface_tela_principal_opcoes(paciencia);
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
    puts("");
}

static void _interface_monta_linha_vazia(char* tela) {
    char buffer[BUFFER_SIZE] = "";
    int i;
    for (i = 0; i < LARGURA; i++)
        strcat(buffer, " ");
    _interface_adiciona_linha(tela, buffer);
}

static void _interface_monta_linha_separacao(char* tela) {
    char buffer[BUFFER_SIZE] = "";
    int i;
    for (i = 0; i < LARGURA; i++)
        strcat(buffer, "-");
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
    strcpy(linha, "");
    
    char buffer[BUFFER_SIZE] = "";
    int tamanho_texto = strlen(texto);
    int espaco_sobrando = LARGURA/2 - tamanho_texto/2;

    int i;

    // Monta espaco vazio
    for (i = 0; i <= espaco_sobrando; i++) {
        strcat(buffer, " ");
    }

    strcat(buffer, texto);
    
    strcpy(linha, buffer);
}

// ***********************************************************************************************************

/**
 * Funcoes auxiliares de controle de opcoes
 */

// Lista opcoes da tela principal
static void _interface_tela_principal_opcoes(Paciencia* paciencia) {
    char tela[SCREEN_BUFFER_SIZE] = "";
    char linha[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE] = "";

    _interface_adiciona_linha(tela, " Selecione uma opcao: ");
    _interface_adiciona_linha(tela, " [1]: Iniciar novo jogo");
    _interface_adiciona_linha(tela, " [2]: Creditos");
    _interface_adiciona_linha(tela, " [3]: Sair");

    _interface_monta_linha_vazia(tela);

    // Exibe tela
    puts(tela);

    int opcao_escolhida = _interface_controle_entrada_opcoes(3);

    switch (opcao_escolhida) {
        case 1: // Inicial novo jogo
            paciencia->tela_atual = TELA_JOGO;
            break;
        case 2: // Creditos
            paciencia->tela_atual = TELA_CREDITOS;
            break;
        case 3: // Sair
            paciencia->tela_atual = SAIR;
            break;
    }

}

// ***********************************************************************************************************

/**
 * Funcoes auxiliares de controle de entrada de dados
 */

static int _interface_controle_entrada_opcoes(int opcoes_validas) {
    printf(": ");

    int opcao_escolhida;
    int result = 0;

    do {
        result = scanf("%d", &opcao_escolhida);

        if (opcao_escolhida <= 0 || opcao_escolhida > opcoes_validas)
            result = 0;

        if (!result)
            printf("\nOpcao Incorreta!\nTente novamente\n : ");
    } while (!result);
    return opcao_escolhida;
}

// ***********************************************************************************************************


#endif // INTERFACE_H_INCLUDED
