#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL/arvore_avl.h"

#define QTD_PARAMETROS 10

int main() {

    ArvoreAvl * avl = cria_arvore_avl();

    // iniciando a semente do rand
    srand(time(NULL));

    // setando um vetor com os valores aleatórios distintos
    int valores[QTD_PARAMETROS];
    int i;
    for (i = 0; i < QTD_PARAMETROS; i++) {
        int posicaoVetor = 0;
        int valor = rand();
        while (posicaoVetor <= i) {
            if (valores[posicaoVetor] == valor) {
                valor = rand();
                posicaoVetor = 0;
            } 
            else {
                posicaoVetor++;
            }
        }
        valores[i] = valor;
    }

    FILE *fpt;

    fpt = fopen("amostras.csv", "w+");
    fprintf(fpt,"Nome Arvore, Nome operacao, Quantidade Parametros, Valor, Custo Operacao, Custo Total\n");

    int count_operacoes_total = 0;
    for(i = 0; i < QTD_PARAMETROS; i++) {
        adiciona_na_arvore_avl(avl, valores[i]);
        printf("Inserindo %d\n", valores[i]);
        printf("Operações: %d\n", get_contagem_insercao_avl());
        count_operacoes_total += get_contagem_insercao_avl();
        fprintf(fpt,"AVL, Insercao, %d, %d, %d, %d\n", i, valores[i], get_contagem_insercao_avl(), count_operacoes_total);
        print_arvore_avl(avl);
    }

    count_operacoes_total = 0;
    for(i = 0; i < QTD_PARAMETROS; i++) {
        remove_na_arvore_avl(avl, valores[i]);
        printf("Removendo %d\n", valores[i]);
        printf("Operações: %d\n", get_contagem_remocao_avl());
        count_operacoes_total += get_contagem_remocao_avl();
        fprintf(fpt,"AVL, Remocao, %d, %d, %d, %d\n", i, valores[i], get_contagem_remocao_avl(), count_operacoes_total);
        print_arvore_avl(avl);
    }

    fclose(fpt);
    free(avl);
}