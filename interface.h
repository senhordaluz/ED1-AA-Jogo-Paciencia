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

#define VERSAO  "VERSAO - 1.0.0"

// Telas
#define TELA_INICIO     0
#define TELA_JOGO       1
#define TELA_CREDITOS   2
#define SAIR            4

// Opcoes internas do jogo
#define ESCOLHA_MOVIMENTO   0
#define MOVIMENTO_1         1
#define MOVIMENTO_2         2
#define MOVIMENTO_3         3
#define MOVIMENTO_1_NAIPE       4
#define MOVIMENTO_1_FILEIRA     5
#define MOVIMENTO_1_DESCARTE    6
#define PROXIMA_ESCOLHA         99
#define MOVIMENTO_SUCESSO       100
#define MOVIMENTO_FALHA         101

// Constantes internas
#define LARGURA             200
#define BUFFER_SIZE         5000
#define SCREEN_BUFFER_SIZE  400000

// ***********************************************************************************************************

void Interface_Mostra_Tela(Paciencia* paciencia);

static void _interface_mostra_tela_principal(Paciencia* paciencia);
static void _interface_mostra_tela_jogo(Paciencia* paciencia);

static void _interface_monta_cabecalho(void);
static int _interface_monta_baralho_em_tela(Paciencia* paciencia);
static void _interface_monta_baralho_preenche_vazios(char* string, int tamanho);

static void _interface_limpa_tela(void);
static void _interface_adiciona_linha_vazia(char* tela);
static void _interface_monta_linha_separacao(char* tela);
static void _interface_limpa_buffer(char* buffer);
static void _interface_adiciona_linha(char* tela, char* linha);
static void _interface_preenche_lados(char* linha, char* texto);

static void _interface_tela_principal_opcoes(Paciencia* paciencia);
static void _interface_tela_jogo_opcoes(Paciencia* paciencia, int* escolha_movimento);
static void _interface_tela_jogo_opcoes_lista(Paciencia* paciencia, int* escolha_movimento);
static void _interface_tela_jogo_opcoes_movimento1(Paciencia* paciencia, int* escolha_movimento);
static void _interface_tela_jogo_opcoes_movimento1_naipe(Paciencia* paciencia, int* escolha_movimento);
static void _interface_tela_jogo_opcoes_movimento1_fileira(Paciencia* paciencia, int* escolha_movimento);
static void _interface_tela_jogo_opcoes_movimento1_descarte(Paciencia* paciencia, int* escolha_movimento);
static void _interface_tela_jogo_opcoes_movimento2(Paciencia* paciencia, int* escolha_movimento);
static void _interface_tela_jogo_opcoes_movimento3(Paciencia* paciencia, int* escolha_movimento);

static int _interface_controle_entrada_opcoes(int opcoes_validas);
static int _interface_controle_pressione_enter_para_continuar(int sucesso);

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

    _interface_monta_cabecalho();

    // Exibe opcoes
    _interface_tela_principal_opcoes(paciencia);
}

// Tela de jogo
static void _interface_mostra_tela_jogo(Paciencia* paciencia) {

    int escolha_movimento = ESCOLHA_MOVIMENTO;
    do {
        _interface_limpa_tela();

        _interface_monta_cabecalho();

        // Mostra cartas
        _interface_monta_baralho_em_tela(paciencia);

        // Exibe opcoes
        _interface_tela_jogo_opcoes(paciencia, &escolha_movimento);
    } while (escolha_movimento != PROXIMA_ESCOLHA);
}

// ***********************************************************************************************************

/**
 * Modulos de tela
 */

// Cabecalho
static void _interface_monta_cabecalho(void) {
    char tela[SCREEN_BUFFER_SIZE] = "";
    char linha[BUFFER_SIZE] = "";

    // Prepara cabecalho
    _interface_monta_linha_separacao(tela);

    _interface_adiciona_linha_vazia(tela);
    _interface_adiciona_linha_vazia(tela);

    _interface_preenche_lados(linha, "PACIENCIA");
    _interface_adiciona_linha(tela, linha);

    _interface_adiciona_linha_vazia(tela);
    _interface_preenche_lados(linha, VERSAO);
    _interface_adiciona_linha(tela, linha);

    _interface_adiciona_linha_vazia(tela);
    _interface_adiciona_linha_vazia(tela);

    _interface_monta_linha_separacao(tela);

    // Preenche tela
    puts(tela);
}

// Monta baralho com todas a pilhas em tela
static int _interface_monta_baralho_em_tela(Paciencia* paciencia) {
    char tela[SCREEN_BUFFER_SIZE] = "";
    char linha[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE] = "";

    // Pilhas
    Pilha* pilha_estoque = paciencia->pilha_estoque;
    Pilhas_Fileira* pilhas_fileira = paciencia->pilhas_fileira;
    Pilhas_Naipe* pilhas_naipe = paciencia->pilhas_naipe;
    Pilha* pilha_descarte = paciencia->pilha_descarte;

    // Cabecalho
    _interface_adiciona_linha_vazia(tela);

    _interface_preenche_lados(linha, "|                        |                        |                        |                        |                        |                        |");
    _interface_adiciona_linha(tela, linha);

    _interface_preenche_lados(linha, "|        Estoque         |        Descarte        |    Pilha de Naipe 1    |    Pilha de Naipe 2    |    Pilha de Naipe 3    |    Pilha de Naipe 4    |");
    _interface_adiciona_linha(tela, linha);

    _interface_preenche_lados(linha, "|                        |                        |                        |                        |                        |                        |");
    _interface_adiciona_linha(tela, linha);

    // Pilha Estoque
    pilha_estoque->toString(pilha_estoque, buffer);
    strcpy(linha, "|");
    _interface_monta_baralho_preenche_vazios(buffer, 24);
    strcat(linha, buffer);
    strcat(linha, "|");

    // Pilha Descarte
    pilha_descarte->toString(pilha_descarte, buffer);
    _interface_monta_baralho_preenche_vazios(buffer, 24);
    strcat(linha, buffer);
    strcat(linha, "|");

    // Pilhas de Naipe
    int i;
    for (i = 0; i < 4; i++) {
        Pilha* pilha_naipe = pilhas_naipe->pilha[i];
        pilha_naipe->toString(pilha_naipe, buffer);
        _interface_monta_baralho_preenche_vazios(buffer, 24);
        strcat(linha, buffer);
        strcat(linha, "|");
    }

    strcpy(buffer, linha);
    _interface_preenche_lados(linha, buffer);
    _interface_adiciona_linha(tela, linha);

    _interface_preenche_lados(linha, "|                        |                        |                        |                        |                        |                        |");
    _interface_adiciona_linha(tela, linha);

    // Pilhas de Fileira
    _interface_adiciona_linha_vazia(tela);
    _interface_preenche_lados(linha, "PILHAS FILEIRA");
    _interface_adiciona_linha(tela, linha);

    _interface_preenche_lados(linha, "|                          |                          |                          |                          |                          |                          |                          |");
    _interface_adiciona_linha(tela, linha);

    _interface_preenche_lados(linha, "|        FILEIRA 1         |        FILEIRA 2         |        FILEIRA 3         |        FILEIRA 4         |        FILEIRA 5         |        FILEIRA 6         |        FILEIRA 7         |");
    _interface_adiciona_linha(tela, linha);

    _interface_preenche_lados(linha, "|                          |                          |                          |                          |                          |                          |                          |");
    _interface_adiciona_linha(tela, linha);

    // "|     [0]: Rei de ouro     |"
    // "|   [1]: Valete de ouro  |"

    // Monta fileiras
    int maior_pilha_id = pilhas_fileira->maiorPilhaID(pilhas_fileira);
    int maior_topo_de_pilha = pilhas_fileira->pilha[maior_pilha_id]->topo;
    for (i = 0; i <= maior_topo_de_pilha; i++) {
        int j;
        for ( j = 0; j < 7; j++) {
            if ( j == 0 )
                strcpy(linha, "|");

            pilhas_fileira->toString(pilhas_fileira, buffer, j, i);
            _interface_monta_baralho_preenche_vazios(buffer, 24);
            strcat(linha, buffer);
            strcat(linha, "|");
        }
        strcpy(buffer, linha);
        _interface_preenche_lados(linha, buffer);
        _interface_adiciona_linha(tela, linha);
    }

    _interface_preenche_lados(linha, "|                          |                          |                          |                          |                          |                          |                          |");
    _interface_adiciona_linha(tela, linha);

    // Preenche tela
    puts(tela);
}

static void _interface_monta_baralho_preenche_vazios(char* string, int tamanho) {
    char buffer[BUFFER_SIZE] = "";
    int sobra = tamanho - strlen(string);

    int i;
    if (sobra % 2) {
        for (i = 0; i <= sobra/2; i++)
            strcat(buffer, " ");
        strcat(buffer, string);
        for (i = 0; i < sobra/2; i++)
            strcat(buffer, " ");
    } else {
        for (i = 0; i <= sobra/2; i++)
            strcat(buffer, " ");
        strcat(buffer, string);
        for (i = 0; i <= sobra/2; i++)
            strcat(buffer, " ");
    }
    strcpy(string, buffer);
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

static void _interface_adiciona_linha_vazia(char* tela) {
    _interface_adiciona_linha(tela, "");
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

    _interface_adiciona_linha(tela, " Selecione uma opcao: ");
    _interface_adiciona_linha(tela, " [1]: Iniciar novo jogo");
    _interface_adiciona_linha(tela, " [2]: Creditos");
    _interface_adiciona_linha(tela, " [3]: Sair");

    _interface_adiciona_linha_vazia(tela);

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

// Controle das telas de opcoes do jogo
static void _interface_tela_jogo_opcoes(Paciencia* paciencia, int* escolha_movimento) {
    switch (*escolha_movimento) {
        case ESCOLHA_MOVIMENTO:
            return _interface_tela_jogo_opcoes_lista(paciencia, escolha_movimento);
        case MOVIMENTO_1:
            return _interface_tela_jogo_opcoes_movimento1(paciencia, escolha_movimento);
        case MOVIMENTO_1_NAIPE:
            return _interface_tela_jogo_opcoes_movimento1_naipe(paciencia, escolha_movimento);
        case MOVIMENTO_1_FILEIRA:
            return _interface_tela_jogo_opcoes_movimento1_fileira(paciencia, escolha_movimento);
        case MOVIMENTO_1_DESCARTE:
            return _interface_tela_jogo_opcoes_movimento1_descarte(paciencia, escolha_movimento);

        case MOVIMENTO_2:
            return _interface_tela_jogo_opcoes_movimento2(paciencia, escolha_movimento);
        case MOVIMENTO_3:
            return _interface_tela_jogo_opcoes_movimento3(paciencia, escolha_movimento);

        case MOVIMENTO_SUCESSO:
            if ( _interface_controle_pressione_enter_para_continuar(1) )
                *escolha_movimento = ESCOLHA_MOVIMENTO;
            return;
        case MOVIMENTO_FALHA:
            if ( _interface_controle_pressione_enter_para_continuar(0) )
                *escolha_movimento = ESCOLHA_MOVIMENTO;
            return;
    }
}

// Lista opcoes da tela de jogo
static void _interface_tela_jogo_opcoes_lista(Paciencia* paciencia, int* escolha_movimento) {
    char tela[SCREEN_BUFFER_SIZE] = "";

    _interface_adiciona_linha(tela, " Selecione uma opcao: ");
    _interface_adiciona_linha(tela, " [1]: Retirar carta da pilha de estoque");
    _interface_adiciona_linha(tela, " [2]: Retirar carta de uma pilha fileira e mover ate uma das pilhas de naipe");
    _interface_adiciona_linha(tela, " [3]: Mover carta(s) de uma fileira para outra");
    _interface_adiciona_linha(tela, " [4]: Voltar ao menu principal");
    _interface_adiciona_linha(tela, " [5]: Sair do jogo");

    _interface_adiciona_linha_vazia(tela);

    // Exibe tela
    puts(tela);

    int opcao_escolhida = _interface_controle_entrada_opcoes(5);

    switch (opcao_escolhida) {
        case 1: // Vai para opcoes da pilha de estoque
            *escolha_movimento = MOVIMENTO_1;
            break;
        case 2: // Vai para opcoes da pilha de naipe
            *escolha_movimento = MOVIMENTO_2;
            break;
        case 3: // Vai para opcoes de mover pilha fileira
            *escolha_movimento = MOVIMENTO_3;
            break;
        case 4: // Voltar ao menu principal
            *escolha_movimento = PROXIMA_ESCOLHA;
            paciencia->tela_atual = TELA_INICIO;
            break;
        case 5: // Sair do jogo
            *escolha_movimento = PROXIMA_ESCOLHA;
            paciencia->tela_atual = SAIR;
            break;
    }
}

// Controle de opcoes do movimento 1:
// Retirar cartas da pilha de estoque, uma por vez, e empilha-las nas pilhas de naipe, fileira ou descarte
static void _interface_tela_jogo_opcoes_movimento1(Paciencia* paciencia, int* escolha_movimento) {
    char tela[SCREEN_BUFFER_SIZE] = "";

    _interface_adiciona_linha(tela, " Voce escolheu ");
    _interface_adiciona_linha(tela, " Retirar um carta da pilha de estoque ");
    _interface_adiciona_linha_vazia(tela);
    _interface_adiciona_linha(tela, " Selecione uma opcao: ");
    _interface_adiciona_linha(tela, " [1]: Colocar carta na pilha de naipe");
    _interface_adiciona_linha(tela, " [2]: Colocar carta numa pilha fileira");
    _interface_adiciona_linha(tela, " [3]: Colocar carta na pilha de descarte");
    _interface_adiciona_linha(tela, " [4]: Voltar");

    _interface_adiciona_linha_vazia(tela);

    // Exibe tela
    puts(tela);

    int opcao_escolhida = _interface_controle_entrada_opcoes(4);

    switch (opcao_escolhida) {
        case 1: // Colocar carta na pilha de naipe
            *escolha_movimento = MOVIMENTO_1_NAIPE;
            break;
        case 2: // Colocar carta numa pilha fileira
            *escolha_movimento = MOVIMENTO_1_FILEIRA;
            break;
        case 3: // Colocar carta na pilha de descarte
            *escolha_movimento = MOVIMENTO_1_DESCARTE;
            break;
        case 4: // Volta para opcoes da pilha de estoque
            *escolha_movimento = ESCOLHA_MOVIMENTO;
            break;
    }
}

// Controle de opcoes do movimento 1 para pilhas de naipe:
// Retirar uma carta da pilha de estoque e empilha numa das pilhas de naipe
static void _interface_tela_jogo_opcoes_movimento1_naipe(Paciencia* paciencia, int* escolha_movimento) {
    char tela[SCREEN_BUFFER_SIZE] = "";

    _interface_adiciona_linha(tela, " Voce escolheu ");
    _interface_adiciona_linha(tela, " Retirar um carta da pilha de estoque e move-la para a pilha de naipes ");
    _interface_adiciona_linha_vazia(tela);
    _interface_adiciona_linha(tela, " Selecione uma pilha de naipe: ");
    _interface_adiciona_linha(tela, " [1]: Pilha de Naipe 1");
    _interface_adiciona_linha(tela, " [2]: Pilha de Naipe 2");
    _interface_adiciona_linha(tela, " [3]: Pilha de Naipe 3");
    _interface_adiciona_linha(tela, " [4]: Pilha de Naipe 4");
    _interface_adiciona_linha(tela, " [5]: Voltar");

    _interface_adiciona_linha_vazia(tela);

    // Exibe tela
    puts(tela);

    int opcao_escolhida = _interface_controle_entrada_opcoes(5);

    int sucesso;
    switch (opcao_escolhida) {
        case 1: // Colocar carta na pilha de naipe
            *escolha_movimento = PROXIMA_ESCOLHA;
            sucesso = paciencia->movimento1(paciencia, PILHA_NAIPE, 0);
            break;
        case 2: // Colocar carta numa pilha fileira
            *escolha_movimento = PROXIMA_ESCOLHA;
            sucesso = paciencia->movimento1(paciencia, PILHA_NAIPE, 1);
            break;
        case 3: // Colocar carta na pilha de descarte
            *escolha_movimento = PROXIMA_ESCOLHA;
            sucesso = paciencia->movimento1(paciencia, PILHA_NAIPE, 2);
            break;
        case 4: // Volta para opcoes da pilha de estoque
            *escolha_movimento = PROXIMA_ESCOLHA;
            sucesso = paciencia->movimento1(paciencia, PILHA_NAIPE, 3);
            break;
        case 5: // Volta para opcoes da pilha de estoque
            *escolha_movimento = MOVIMENTO_1;
            return;
    }
    if (sucesso)
        *escolha_movimento = MOVIMENTO_SUCESSO;
    else
        *escolha_movimento = MOVIMENTO_FALHA;
}

// Controle de opcoes do movimento 1 para pilhas de naipe:
// Retirar uma carta da pilha de estoque e empilha numa das pilhas de fileira
static void _interface_tela_jogo_opcoes_movimento1_fileira(Paciencia* paciencia, int* escolha_movimento) {

}

// Controle de opcoes do movimento 1 para pilhas de naipe:
// Retirar uma carta da pilha de estoque e empilha na pilha de descarte
static void _interface_tela_jogo_opcoes_movimento1_descarte(Paciencia* paciencia, int* escolha_movimento) {

}

static void _interface_tela_jogo_opcoes_movimento2(Paciencia* paciencia, int* escolha_movimento) {

}

static void _interface_tela_jogo_opcoes_movimento3(Paciencia* paciencia, int* escolha_movimento) {

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

static int _interface_controle_pressione_enter_para_continuar(int sucesso) {
    if (sucesso)
        puts(" Movimento bem sucedido ");
    else
        puts(" Nao foi possivel executar o movimento ");
    printf(" Pressione enter para continuar...");
    char enter;
    int result = 0;
    while( enter != '\n' ) {
        enter = getchar();
    }
    // while( getchar() != '\n' );
    // char enter = getchar();
    if ( enter == '\n' )
        return 1;
    else
        return 0;
}

// ***********************************************************************************************************


#endif // INTERFACE_H_INCLUDED
