#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL/arvore_avl.h"
#include "RedBlack/RedBlack.h"

#define QTD_PARAMETROS 10000
#define QTD_AMOSTRAS 100

void gerar_valores_aleatorios(int * valores);

void executar_operacoes(
    char * nomeArvore,
    void * arvore,
    char * nomeOperacao,
    void * (*operacao)(void *, int),
    int * valores,
    int (*get_contagem)(),
    int numero_amostra,
    FILE *arquivo
);

int main() {

    // iniciando a semente do rand
    srand(time(NULL));

    // criando o arquivo de amostras
    FILE *arquivo;
    arquivo = fopen("amostras.csv", "w+");
    fprintf(arquivo,"Nome Arvore, Nome operacao, Amostra, Quantidade Parametros, Valor, Custo Operacao, Custo Total\n");

    int i = 0;
    for (int i; i < QTD_AMOSTRAS; i++)
    {
        // setando um vetor com os valores aleatórios distintos
        int valores[QTD_PARAMETROS];
        gerar_valores_aleatorios(valores);

        // executando testes arvore AVL
        ArvoreAvl * avl = cria_arvore_avl();
        executar_operacoes("AVL", avl, "Insercao", adiciona_na_arvore_avl, valores, get_contagem_insercao_avl, i+1, arquivo);
        executar_operacoes("AVL", avl, "Remocao", remove_na_arvore_avl, valores, get_contagem_remocao_avl, i+1, arquivo);
        free(avl);

        // executando testes arvore RedBlack
        RedBlack * rb = cria_arvore_rb();
        executar_operacoes("RedBlack", rb, "Insercao", adiciona_na_arvore_rb, valores, get_contagem_insercao_rb, i+1, arquivo);
        executar_operacoes("RedBlack", rb, "Remocao", remove_na_arvore_rb, valores, get_contagem_remocao_rb, i+1, arquivo);
        free(rb);


        // executando testes arvore B
        // ArvoreB * ab1 = cria_arvore_b();
        // executar_operacoes("Arvore B ordem 1", ab1, "Insercao", adiciona_na_arvore_b, valores, get_contagem_insercao_b, arquivo);
        // executar_operacoes("Arvore B ordem 1", ab1, "Remocao", remove_na_arvore_b, valores, get_contagem_remocao_b, arquivo);
        // free(ab1);
        // ArvoreB * ab2 = cria_arvore_b();
        // executar_operacoes("Arvore B ordem 5", ab2, "Insercao", adiciona_na_arvore_b, valores, get_contagem_insercao_b, arquivo);
        // executar_operacoes("Arvore B ordem 5", ab2, "Remocao", remove_na_arvore_b, valores, get_contagem_remocao_b, arquivo);
        // free(ab2);
        // ArvoreB * ab3 = cria_arvore_b();
        // executar_operacoes("Arvore B ordem 10", ab3, "Insercao", adiciona_na_arvore_b, valores, get_contagem_insercao_b, arquivo);
        // executar_operacoes("Arvore B ordem 10", ab3, "Remocao", remove_na_arvore_b, valores, get_contagem_remocao_b, arquivo);
        // free(ab3);   
    }

    fclose(arquivo);
}

void gerar_valores_aleatorios(int * valores) {
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
}

void executar_operacoes(
    char * nomeArvore,
    void * arvore,
    char * nomeOperacao,
    void * (*operacao)(void *, int),
    int * valores,
    int (*get_contagem)(),
    int numero_amostra,
    FILE *arquivo
) 
{
    int count_operacoes_total = 0;
    int i = 0;
    for(i = 0; i < QTD_PARAMETROS; i++) {
        operacao(arvore, valores[i]);
        count_operacoes_total += get_contagem();
        fprintf(arquivo,"%s, %s, %d, %d, %d, %d, %d\n", nomeArvore, nomeOperacao, numero_amostra, i, valores[i], get_contagem(), count_operacoes_total);
    }
}