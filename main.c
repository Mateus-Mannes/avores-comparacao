#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL/arvore_avl.h"

#define QTD_PARAMETROS 200

int main() {

    ArvoreAvl * avl = cria_arvore_avl();

    // setando um vetor com valores de 1 a `QTD_PARAMETROS`
    int valores[QTD_PARAMETROS] = { 0 };
    int i;
    for (i = 1; i <= QTD_PARAMETROS; i++) valores[i - 1] = i;

    // iniciando a semente do rand e a quantidade de valores disponíveis
    srand(time(NULL));
    int qtdValoresDisponiveis = QTD_PARAMETROS;

    for(i = 0; i < QTD_PARAMETROS; i++) {
        // pegando um valor aleatório para inserir
        int indice = rand() % qtdValoresDisponiveis;
        int valor = valores[indice];

        // reduzindo a lista de valores possíveis
        valores[indice] = valores[qtdValoresDisponiveis - 1];
        qtdValoresDisponiveis--;

        adiciona_na_arvore_avl(avl, valor);
    }

    // reiniciando vetor de valores
    for (i = 1; i <= QTD_PARAMETROS; i++) valores[i - 1] = i;
    qtdValoresDisponiveis = QTD_PARAMETROS;    

    for(i = 0; i < QTD_PARAMETROS; i++) {
        // pegando um valor aleatório para remover
        int indice = rand() % qtdValoresDisponiveis;
        int valor = valores[indice];

        // reduzindo a lista de valores possíveis
        valores[indice] = valores[qtdValoresDisponiveis - 1];
        qtdValoresDisponiveis--;

        remove_na_arvore_avl(avl, valor);
    }

    free(avl);
}