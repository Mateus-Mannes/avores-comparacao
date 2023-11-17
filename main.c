#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL/arvore_avl.h"

#define QTD_PARAMETROS 200

int remover_valor_aleatorio(int * valores, int * qtdValoresDisponiveis);

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
        printf("Indice: %d\n", indice);
        int valor = valores[indice];

        // reduzindo a lista de valores possíveis
        valores[indice] = valores[qtdValoresDisponiveis - 1];
        qtdValoresDisponiveis--;

        printf("%d Adicionando %d\n", i, valor);
        adiciona_na_arvore_avl(avl, valor);
        print_arvore_avl(avl);
        printf("\n -----------------------\n");
    }

    // reiniciando vetor de valores
    for (i = 1; i <= QTD_PARAMETROS; i++) valores[i - 1] = i;
    qtdValoresDisponiveis = QTD_PARAMETROS;    

    for(i = 0; i < QTD_PARAMETROS; i++) {

        // pegando um valor aleatório para remover
        int indice = rand() % qtdValoresDisponiveis;
        printf("Indice: %d\n", indice);
        int valor = valores[indice];

        // reduzindo a lista de valores possíveis
        valores[indice] = valores[qtdValoresDisponiveis - 1];
        qtdValoresDisponiveis--;

        printf("%d removendo %d\n", i, valor);
        remove_na_arvore_avl(avl, valor);
        print_arvore_avl(avl);
        printf("\n -----------------------\n");
    }
}