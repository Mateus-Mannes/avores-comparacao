#include "BTree.h"

unsigned long int contagem_insercao_b = 0;
unsigned long int contagem_remocao_b = 0;

// Criar nó
No_B *cria_no(ArvoreB *arvore) {
  int max = arvore->ordem * 2;
  No_B *no = malloc(sizeof(No_B));

  no->pai = NULL;

  no->chaves = malloc(sizeof(int) * (max + 1));
  no->filhos = malloc(sizeof(No_B) * (max + 2));
  no->total = 0;

  for (int i = 0; i < max + 2; i++) {
    contagem_insercao_b++; // CONTAGEM INSERÇÃO
    
    no->filhos[i] = NULL;
  }
  contagem_insercao_b++; // CONTAGEM INSERÇÃO

  return no;
}

ArvoreB *cria_arvore_b(int ordem) {
  ArvoreB *a = malloc(sizeof(ArvoreB));
  a->ordem = ordem;
  a->raiz = cria_no(a);

  return a;
}

// Pesquisa binária
int pesquisa_binaria(No_B *no, int chave) {
  int inicio = 0, fim = no->total - 1, meio;

  while (inicio <= fim) {
    contagem_insercao_b++; // CONTAGEM INSERÇÃO
    contagem_remocao_b++; // CONTAGEM REMOÇÃO

    meio = (inicio + fim) / 2;

    if (no->chaves[meio] == chave) {
      contagem_insercao_b++; // CONTAGEM INSERÇÃO
      contagem_remocao_b++; // CONTAGEM REMOÇÃO

      return meio;
    } else if (no->chaves[meio] > chave) {
      contagem_insercao_b += 2; // CONTAGEM INSERÇÃO
      contagem_remocao_b += 2; // CONTAGEM REMOÇÃO
      
      fim = meio - 1;
    } else {
      contagem_insercao_b += 2; // CONTAGEM INSERÇÃO
      contagem_remocao_b += 2; // CONTAGEM REMOÇÃO

      inicio = meio + 1;
    }
  }
  contagem_insercao_b++; // CONTAGEM INSERÇÃO
  contagem_remocao_b++; // CONTAGEM REMOÇÃO
  
  return inicio;
}

No_B *localiza_no(ArvoreB *arvore, int chave) {
  No_B *no = arvore->raiz;
  
  while (no != NULL) {
    contagem_insercao_b++; // CONTAGEM INSERÇÃO
    contagem_remocao_b++; // CONTAGEM REMOÇÃO
    
    int i = pesquisa_binaria(no, chave);

    contagem_insercao_b++; // CONTAGEM INSERÇÃO
    contagem_remocao_b++; // CONTAGEM REMOÇÃO
    if (no->filhos[i] == NULL) {
      return no;
    } else {
      no = no->filhos[i];
    }
  }
  contagem_insercao_b++; // CONTAGEM INSERÇÃO
  contagem_remocao_b++; // CONTAGEM REMOÇÃO

  return NULL;
}

void adiciona_chave_no(No_B *no, No_B *novo, int chave) {
  int i = pesquisa_binaria(no, chave);

  for (int j = no->total - 1; j >= i; j--) {
    contagem_insercao_b++; // CONTAGEM INSERÇÃO
    
    no->chaves[j + 1] = no->chaves[j];
    no->filhos[j + 2] = no->filhos[j + 1];
  }
  contagem_insercao_b++; // CONTAGEM INSERÇÃO

  no->chaves[i] = chave;
  no->filhos[i + 1] = novo;

  no->total++;
}

int transbordo(ArvoreB *arvore, No_B *no) {
  contagem_insercao_b++; // CONTAGEM INSERÇÃO
  
  return no->total > arvore->ordem * 2;
}

No_B *divide_no(ArvoreB *arvore, No_B *no) {
  int meio = no->total / 2;
  No_B *novo = cria_no(arvore);
  novo->pai = no->pai;

  for (int i = meio + 1; i < no->total; i++) {
    contagem_insercao_b++; // CONTAGEM INSERÇÃO

    novo->filhos[novo->total] = no->filhos[i];
    novo->chaves[novo->total] = no->chaves[i];

    contagem_insercao_b++; // CONTAGEM INSERÇÃO
    if (novo->filhos[novo->total] != NULL) {
      novo->filhos[novo->total]->pai = novo;
    }

    novo->total++;
  }
  contagem_insercao_b++; // CONTAGEM INSERÇÃO

  novo->filhos[novo->total] = no->filhos[no->total];
  
  contagem_insercao_b++; // CONTAGEM INSERÇÃO
  if (novo->filhos[novo->total] != NULL) {
    novo->filhos[novo->total]->pai = novo;
  }
  
  no->total = meio;
  
  return novo;
}

void adiciona_chave_b_recursivo(ArvoreB *arvore, No_B *no, No_B *novo, int chave) {
  adiciona_chave_no(no, novo, chave);

  contagem_insercao_b++; // CONTAGEM INSERÇÃO
  if (transbordo(arvore, no)) {
    int promovido = no->chaves[arvore->ordem];
    No_B *novo = divide_no(arvore, no);

    contagem_insercao_b++; // CONTAGEM INSERÇÃO
    if (no->pai == NULL) {
      No_B *pai = cria_no(arvore);
      pai->filhos[0] = no;
      adiciona_chave_no(pai, novo, promovido);

      no->pai = pai;
      novo->pai = pai;
      arvore->raiz = pai;
    } else {
      adiciona_chave_b_recursivo(arvore, no->pai, novo, promovido);
    }
  }
}

// Adicionar chave em árvore B
void adiciona_chave_b(ArvoreB *arvore, int chave) {
  contagem_insercao_b = 0;

  No_B *no = localiza_no(arvore, chave);

  adiciona_chave_b_recursivo(arvore, no, NULL, chave);
}

void remove_chave_recursivo(ArvoreB *arvore, No_B *no, int chave) {
  int index = pesquisa_binaria(no, chave);

  contagem_remocao_b++; // CONTAGEM REMOÇÃO
  if (index < no->total && no->chaves[index] == chave) {
    // Caso 1: A chave está no nó folha
    
    contagem_remocao_b++; // CONTAGEM REMOÇÃO
    if (no->filhos[0] == NULL) {

      for (int i = index; i < no->total - 1; i++) {
        contagem_remocao_b++; // CONTAGEM REMOÇÃO
        no->chaves[i] = no->chaves[i + 1];
      }
      contagem_remocao_b++; // CONTAGEM REMOÇÃO
      
      no->total--;
    } else {
      int index = pesquisa_binaria(no, chave);

      // Encontrar o predecessor (maior valor menor que a chave) na subárvore esquerda
      No_B *predecessor = no->filhos[index];
      
      while (predecessor->filhos[predecessor->total] != NULL) {
        contagem_remocao_b++; // CONTAGEM REMOÇÃO

        predecessor = predecessor->filhos[predecessor->total];
      }
      contagem_remocao_b++; // CONTAGEM REMOÇÃO
      
      int predecessorChave = predecessor->chaves[predecessor->total - 1];

      // Trocar a chave do nó interno com o predecessor
      no->chaves[index] = predecessorChave;

      // Recursivamente remover o predecessor da subárvore esquerda
      remove_chave_recursivo(arvore, predecessor, predecessorChave);
    }
  } else {
    int index = pesquisa_binaria(no, chave);
    No_B *filho = no->filhos[index];

    // Verificar se o filho tem chaves suficientes para realizar a remoção

    contagem_remocao_b++; // CONTAGEM REMOÇÃO
    if (filho != NULL && filho->total > arvore->ordem) {
      // Chamar recursivamente a função de remoção no nó filho
      remove_chave_recursivo(arvore, filho, chave);
    } else {

      if (index < no->total && no->filhos[index + 1] != NULL && no->filhos[index + 1]->total > arvore->ordem) {
        contagem_remocao_b++; // CONTAGEM REMOÇÃO

        No_B *irmaoDireita = no->filhos[index + 1];

        // Mover uma chave do nó pai para o nó filho
        filho->chaves[filho->total] = no->chaves[index];
        filho->total++;

        // Transferir todas as chaves e filhos do irmão à direita para o nó filho
        for (int i = 0; i < irmaoDireita->total; i++) {
          contagem_remocao_b++; // CONTAGEM REMOÇÃO

          filho->chaves[filho->total] = irmaoDireita->chaves[i];
          filho->filhos[filho->total] = irmaoDireita->filhos[i];

          contagem_remocao_b++; // CONTAGEM REMOÇÃO
          if (filho->filhos[filho->total] != NULL) {
            filho->filhos[filho->total]->pai = filho;
          }
          
          filho->total++;
        }
        contagem_remocao_b++; // CONTAGEM REMOÇÃO

        // Atualizar o nó pai removendo a chave e o ponteiro para o irmão à direita
        for (int i = index; i < no->total - 1; i++) {
          contagem_remocao_b++; // CONTAGEM REMOÇÃO

          no->chaves[i] = no->chaves[i + 1];
          no->filhos[i + 1] = no->filhos[i + 2];
        }
        contagem_remocao_b++; // CONTAGEM REMOÇÃO

        no->total--;

        // Libere o irmão à direita
        free(irmaoDireita);
      } else if (index > 0 && no->filhos[index - 1] != NULL && no->filhos[index - 1]->total > arvore->ordem) {
        contagem_remocao_b += 2; // CONTAGEM REMOÇÃO

        No_B *irmaoEsquerda = no->filhos[index - 1];

        // Mover uma chave do nó pai para o nó filho
        filho->chaves[0] = no->chaves[index - 1];
        filho->total++;

        // Transferir todas as chaves e filhos do irmão à esquerda para o nó filho
        for (int i = 0; i < irmaoEsquerda->total; i++) {
          contagem_remocao_b++; // CONTAGEM REMOÇÃO

          filho->chaves[filho->total] = irmaoEsquerda->chaves[i];
          filho->filhos[filho->total] = irmaoEsquerda->filhos[i];

          contagem_remocao_b++; // CONTAGEM REMOÇÃO
          if (filho->filhos[filho->total] != NULL) {
            filho->filhos[filho->total]->pai = filho;
          }
          
          filho->total++;
        }
        contagem_remocao_b++; // CONTAGEM REMOÇÃO

        // Atualizar o nó pai removendo a chave e o ponteiro para o irmão à esquerda
        for (int i = index - 1; i < no->total - 1; i++) {
          contagem_remocao_b++; // CONTAGEM REMOÇÃO
          no->chaves[i] = no->chaves[i + 1];
          no->filhos[i + 1] = no->filhos[i + 2];
        }
        contagem_remocao_b++; // CONTAGEM REMOÇÃO

        no->total--;

        // Libere o irmão à esquerda
        free(irmaoEsquerda);
      } else {
        contagem_remocao_b += 2; // CONTAGEM REMOÇÃO

        No_B *irmaoDireita = no->filhos[index + 1];

        // Mover uma chave do nó pai para o nó filho
        contagem_remocao_b++; // CONTAGEM REMOÇÃO
        if (filho != NULL) {
          filho->chaves[filho->total] = no->chaves[index];
          filho->total++;

          // Transferir todas as chaves e filhos do irmão à direita para o nó filho
          for (int i = 0; i < irmaoDireita->total; i++) {
            contagem_remocao_b++; // CONTAGEM REMOÇÃO

            filho->chaves[filho->total] = irmaoDireita->chaves[i];
            filho->filhos[filho->total] = irmaoDireita->filhos[i];

            contagem_remocao_b++; // CONTAGEM REMOÇÃO
            if (filho->filhos[filho->total] != NULL) {
              filho->filhos[filho->total]->pai = filho;
            }
            
            filho->total++;
          }
          contagem_remocao_b++; // CONTAGEM REMOÇÃO

          // Atualizar o nó pai removendo a chave e o ponteiro para o irmão à direita
          for (int i = index; i < no->total - 1; i++) {
            contagem_remocao_b++; // CONTAGEM REMOÇÃO
            no->chaves[i] = no->chaves[i + 1];
            no->filhos[i + 1] = no->filhos[i + 2];
          }
          contagem_remocao_b++; // CONTAGEM REMOÇÃO

          no->total--;

          // Libere o irmão à direita
          free(irmaoDireita); 
        }
      }
    }
  }
}

void remove_chave_b(ArvoreB *arvore, int chave) {
  contagem_remocao_b = 0;

  No_B *no = localiza_no(arvore, chave);
  
  remove_chave_recursivo(arvore, no, chave);
}

// Percorrer a árvore
void printar_arvore_b(No_B *no) {
  if (no != NULL) {
    for (int i = 0; i < no->total; i++) {
      printar_arvore_b(no->filhos[i]);

      printf("%d ", no->chaves[i]);
    }

    printar_arvore_b(no->filhos[no->total]);
  }
}

// Contagem inserção
unsigned long int get_contagem_insercao_b() {
  return contagem_insercao_b;
}

// Contagem remoção
unsigned long int get_contagem_remocao_b() {
  return contagem_remocao_b;
}