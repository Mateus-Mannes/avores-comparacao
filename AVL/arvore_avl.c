#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

// metodos privados
NoAvl * novo_no(int valor);
int fator_balanceamento(NoAvl *no);
int altura(NoAvl *no);
int max(int a, int b);
NoAvl *rse(NoAvl *no, ArvoreAvl * arvore);
NoAvl *rsd(NoAvl *no, ArvoreAvl * arvore);
NoAvl* rde(NoAvl* no, ArvoreAvl * arvore);
NoAvl* rdd(NoAvl* no, ArvoreAvl * arvore);

unsigned long int get_contagem_insercao_avl() {
    return contagem_insercao_avl;
}

unsigned long int get_contagem_remocao_avl() {
    return contagem_remocao_avl;
}


ArvoreAvl* cria_arvore_avl() {
    ArvoreAvl* arvore = (ArvoreAvl*) malloc(sizeof(ArvoreAvl));
    arvore->raiz = NULL;
    return arvore;
}

NoAvl *adiciona_na_arvore_avl_recursivo(ArvoreAvl * arvore, NoAvl * no , int valor) {
    
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    if (no == NULL) {
        no = novo_no(valor);
        contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
        if(arvore->raiz == NULL) arvore->raiz = no;
        return no;
    } 
  
    if (valor < no->valor) {
        contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
        no->esquerda  = adiciona_na_arvore_avl_recursivo(arvore, no->esquerda, valor); 
        no->esquerda->pai = no;
    }
    else if (valor > no->valor) {
        contagem_insercao_avl += 2; // CONTAGEM COMPARAÇÃO INSERÇÃO
        no->direita = adiciona_na_arvore_avl_recursivo(arvore, no->direita, valor);
        no->direita->pai = no;
    }
    else {
        contagem_insercao_avl += 2; // CONTAGEM COMPARAÇÃO INSERÇÃO
        return no;
    }
  
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita)); 
  
    int fb = fator_balanceamento(no);
  
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    if (fb > 1 && valor < no->esquerda->valor) 
        return rsd(no, arvore); 

    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    if (fb < -1 && valor > no->direita->valor) 
        return rse(no, arvore); 
  
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    if (fb > 1 && valor > no->esquerda->valor) 
        return rdd(no, arvore);
    
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    if (fb < -1 && valor < no->direita->valor) 
        return rde(no, arvore);
  
    return no; 
}

NoAvl *adiciona_na_arvore_avl(ArvoreAvl * arvore, int valor) { 
    contagem_insercao_avl = 0;
    return adiciona_na_arvore_avl_recursivo(arvore, arvore->raiz, valor);
}

NoAvl * minValueNode(NoAvl* no) 
{ 
    NoAvl* current = no; 
 
    while (current->esquerda != NULL) {
        contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
        current = current->esquerda;
    } 
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO

    return current; 
} 

NoAvl* remove_na_arvore_avl_recursivo(ArvoreAvl * arvore , NoAvl* no, int valor) 
{ 
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if (no == NULL) 
        return no; 
 
    if ( valor < no->valor ) {
        contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
        no->esquerda = remove_na_arvore_avl_recursivo(arvore, no->esquerda, valor);
    }  
    else if( valor > no->valor ) {
        contagem_remocao_avl += 2; // CONTAGEM COMPARAÇÃO REMOÇÃO
        no->direita = remove_na_arvore_avl_recursivo(arvore, no->direita, valor);    
    }
    else
    { 
        contagem_remocao_avl += 2; // CONTAGEM COMPARAÇÃO REMOÇÃO

        contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
        if( (no->esquerda == NULL) ||
            (no->direita == NULL) ) 
        { 
            contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
            NoAvl *noDeletar = no->esquerda ? 
                         no->esquerda : 
                         no->direita; 

            contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
            if (noDeletar == NULL) 
            { 
                noDeletar = no; 
                no = NULL; 
            } 
            else 
            {
                NoAvl * temp = no;
                no = noDeletar;
                noDeletar = temp;
            }

            contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
            if(noDeletar == arvore->raiz) arvore->raiz = no;
            free(noDeletar); 
        } 
        else
        { 
            NoAvl* temp = minValueNode(no->direita); 
 
            no->valor = temp->valor; 
 
            no->direita = remove_na_arvore_avl_recursivo(arvore, no->direita, temp->valor); 
        } 
    } 
  
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if (no == NULL) return no; 
  
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita)); 
 
    int fb = fator_balanceamento(no); 
 
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if (fb > 1 && fator_balanceamento(no->esquerda) >= 0) 
        return rsd(no, arvore); 
 
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if (fb > 1 && fator_balanceamento(no->esquerda) < 0) 
        return rdd(no, arvore); 
 
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if (fb < -1 && fator_balanceamento(no->direita) <= 0) 
        return rse(no, arvore); 
 
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if (fb < -1 && fator_balanceamento(no->direita) > 0) 
        return rde(no, arvore);
 
    return no; 
}

NoAvl* remove_na_arvore_avl(ArvoreAvl * arvore, int valor) 
{
    contagem_remocao_avl = 0;
    return remove_na_arvore_avl_recursivo(arvore, arvore->raiz, valor);
}

NoAvl * novo_no(int valor) 
{ 
    NoAvl *no = (NoAvl*)malloc(sizeof(NoAvl));
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor; 
    no->altura = 1; // intancia um novo no como folha
    return no;
}

int fator_balanceamento(NoAvl *no)
{
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    if (no == NULL) 
        return 0; 
    return altura(no->esquerda) - altura(no->direita); 
}

int altura(NoAvl *no)
{
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    if(no == NULL) return 0;
    return no->altura;
}

int max(int a, int b) 
{ 
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    return (a > b)? a : b; 
} 

NoAvl *rse(NoAvl *no, ArvoreAvl * arvore)
{
    NoAvl *pai = no->pai;
    NoAvl *direita = no->direita;

    no->direita = direita->esquerda;
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if(no->direita != NULL) no->direita->pai = no;

    no->pai = direita;
    direita->esquerda = no;
    direita->pai = pai;

    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if(arvore->raiz == no) arvore->raiz = direita;

    no->altura = max(altura(no->esquerda), 
                    altura(no->direita)) + 1; 
    direita->altura = max(altura(direita->esquerda), 
                    altura(direita->direita)) + 1; 

    return direita;
}

NoAvl *rsd(NoAvl *no, ArvoreAvl * arvore)
{
    NoAvl *pai = no->pai;
    NoAvl *esquerda = no->esquerda;

    no->esquerda = esquerda->direita;
    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if(no->esquerda != NULL) no->esquerda->pai = no;

    no->pai = esquerda;
    esquerda->direita = no;
    esquerda->pai = pai;

    contagem_insercao_avl++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    contagem_remocao_avl++; // CONTAGEM COMPARAÇÃO REMOÇÃO
    if(arvore->raiz == no) arvore->raiz = esquerda;

    no->altura = max(altura(no->esquerda), 
                    altura(no->direita)) + 1; 
    esquerda->altura = max(altura(esquerda->esquerda), 
                    altura(esquerda->direita)) + 1;

    return esquerda;
}

NoAvl* rde(NoAvl* no, ArvoreAvl * arvore) {
    no->direita = rsd(no->direita, arvore);
    return rse(no, arvore);
}


NoAvl* rdd(NoAvl* no, ArvoreAvl * arvore) {
    no->esquerda = rse(no->esquerda, arvore);
    return rsd(no, arvore);
}

void print_arvore_avl_recursivo(NoAvl* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += 10;
 
    // Process right child first
    print_arvore_avl_recursivo(root->direita, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%.0d\n", root->valor);
 
    // Process left child
    print_arvore_avl_recursivo(root->esquerda, space);
}
 
void print_arvore_avl(ArvoreAvl* arvore)
{
    print_arvore_avl_recursivo(arvore->raiz, 0);
}