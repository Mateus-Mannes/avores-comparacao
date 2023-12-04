#include <stdlib.h>
#include <stdio.h>
#include "RedBlack.h"

int vazia(RedBlack* arvore);
No* criarNo(RedBlack* arvore, No* pai, int valor);
No* adicionarNo(RedBlack* arvore, No* no, int valor);
No* localizar(RedBlack* arvore, int valor);
void balancear(RedBlack* arvore, No* no);
void rotacionarEsquerda(RedBlack* arvore, No* no, unsigned long int* contagem);
void rotacionarDireita(RedBlack* arvore, No* no, unsigned long int* contagem);
No* sucessor(RedBlack* arvore, No* no);
void balancearRemocao(RedBlack* arvore, No* no);
void remove_na_arvore_rb_recursivo(RedBlack* arvore, int valor);
No* adiciona_na_arvore_rb_recursivo(RedBlack* arvore, int valor);

unsigned long int contagem_insercao_rb;
unsigned long int contagem_remocao_rb;

unsigned long int get_contagem_insercao_rb() {
  return contagem_insercao_rb;
}

unsigned long int get_contagem_remocao_rb() {
  return contagem_remocao_rb;
}

No* adiciona_na_arvore_rb(RedBlack* arvore, int valor){
  contagem_insercao_rb = 0;
  return adiciona_na_arvore_rb_recursivo(arvore, valor);
}
void remove_na_arvore_rb(RedBlack* arvore, int valor){
  contagem_remocao_rb = 0;
  return remove_na_arvore_rb_recursivo(arvore, valor);
}

RedBlack* cria_arvore_rb() {
  RedBlack *arvore = malloc(sizeof(RedBlack));
  arvore->nulo = NULL;
  arvore->raiz = NULL;

  arvore->nulo = criarNo(arvore, NULL, 0);
  arvore->nulo->cor = Preto;

  return arvore;
}

int vazia(RedBlack* arvore) {
  return arvore->raiz == NULL;
}

No* criarNo(RedBlack* arvore, No* pai, int valor) {
  No* no = malloc(sizeof(No));

  no->pai = pai;    
  no->valor = valor;
  no->direita = arvore->nulo;
  no->esquerda = arvore->nulo;

  return no;
}

No* adicionarNo(RedBlack* arvore, No* no, int valor) {
  contagem_insercao_rb++;
  if (valor > no->valor) {
    contagem_insercao_rb++;
    if (no->direita == arvore->nulo) {
      no->direita = criarNo(arvore, no, valor);     
      no->direita->cor = Vermelho;       
      
      return no->direita;
    } else {
      return adicionarNo(arvore, no->direita, valor);
    }
  } else {
    contagem_insercao_rb++;
    if (no->esquerda == arvore->nulo) {
      no->esquerda = criarNo(arvore, no, valor);
      no->esquerda->cor = Vermelho;
      
      return no->esquerda;
    } else {
      return adicionarNo(arvore, no->esquerda, valor);
    }
  }
}

No* adiciona_na_arvore_rb_recursivo(RedBlack* arvore, int valor) {
  contagem_insercao_rb++;
  if (vazia(arvore)) {
    arvore->raiz = criarNo(arvore, arvore->nulo, valor);
    arvore->raiz->cor = Preto;
      
    return arvore->raiz;
  } else {
    No* no = adicionarNo(arvore, arvore->raiz, valor);
    balancear(arvore, no);
    
    return no;
  }
}

No* localizar(RedBlack* arvore, int valor) {
  contagem_remocao_rb++;
  if (!vazia(arvore)) {
    No* no = arvore->raiz;

    while (no != arvore->nulo) {
      contagem_remocao_rb+=2;
      if (no->valor == valor) {
        return no;
      } else {
        no = valor < no->valor ? no->esquerda : no->direita;
      }
    }
    contagem_remocao_rb++;
  }

  return NULL;
}

void balancear(RedBlack* arvore, No* no) {
  while (no->pai->cor == Vermelho) {
    contagem_insercao_rb+=2;
    if (no->pai == no->pai->pai->esquerda) {
      No *tio = no->pai->pai->direita;
      
      contagem_insercao_rb++;
      if (tio->cor == Vermelho) {
        tio->cor = Preto; //Caso 1
        no->pai->cor = Preto; 

        no->pai->pai->cor = Vermelho; //Caso 1
        no = no->pai->pai; //Caso 1
      } else {
        contagem_insercao_rb++;
        if (no == no->pai->direita) {
          no = no->pai; //Caso 2
          rotacionarEsquerda(arvore, no, &contagem_insercao_rb); //Caso 2
        } else {
          no->pai->cor = Preto; 
          no->pai->pai->cor = Vermelho; //Caso 3
          rotacionarDireita(arvore, no->pai->pai, &contagem_insercao_rb); //Caso 3
        }
      }
    } else {
      No *tio = no->pai->pai->esquerda;
      
      contagem_insercao_rb++;
      if (tio->cor == Vermelho) {
        tio->cor = Preto; //Caso 1
        no->pai->cor = Preto; 

        no->pai->pai->cor = Vermelho; //Caso 1
        no = no->pai->pai; //Caso 1
      } else {
        contagem_insercao_rb++;
        if (no == no->pai->esquerda) {
          no = no->pai; //Caso 2
          rotacionarDireita(arvore, no, &contagem_insercao_rb); //Caso 2
        } else {
          no->pai->cor = Preto; 
          no->pai->pai->cor = Vermelho; //Caso 3
          rotacionarEsquerda(arvore, no->pai->pai, &contagem_insercao_rb); //Caso 3
        }
      }
    }
  }
  contagem_insercao_rb++;
  arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerda(RedBlack* arvore, No* no, unsigned long int* contagem) {
  No* direita = no->direita;
  no->direita = direita->esquerda; 

  contagem++;
  if (direita->esquerda != arvore->nulo) {
    direita->esquerda->pai = no;
  }

  direita->pai = no->pai;
  
  if (no->pai == arvore->nulo) {
    contagem++;
    arvore->raiz = direita;
  } else if (no == no->pai->esquerda) {
    contagem+=2;
    no->pai->esquerda = direita;
  } else {
    contagem+=2;
    no->pai->direita = direita;
  }

  direita->esquerda = no;
  no->pai = direita;
}

void rotacionarDireita(RedBlack* arvore, No* no, unsigned long int* contagem) {
  No* esquerda = no->esquerda;
  no->esquerda = esquerda->direita;
  
  contagem++;
  if (esquerda->direita != arvore->nulo) {
    esquerda->direita->pai = no;
  }
  
  esquerda->pai = no->pai;
  
  if (no->pai == arvore->nulo) {
    contagem++;
    arvore->raiz = esquerda;
  } else if (no == no->pai->esquerda) {
    contagem+=2;
    no->pai->esquerda = esquerda;
  } else {
    contagem+=2;
    no->pai->direita = esquerda;
  }
  
  esquerda->direita = no;
  no->pai = esquerda;
}

void remove_na_arvore_rb_recursivo(RedBlack* arvore, int valor) {
  No* no = localizar(arvore, valor);
  
  contagem_remocao_rb++;
  if (no != NULL) {
    No* substituto;

    // Caso 1: Nó a ser removido tem zero ou um filho
    contagem_remocao_rb++;
    if (no->esquerda == arvore->nulo || no->direita == arvore->nulo) {
      substituto = no;
    } else {
      // Caso 2: Nó a ser removido tem dois filhos
      substituto = sucessor(arvore, no);
    }

    No* filhoSubstituto;
    contagem_remocao_rb++;
    if (substituto->esquerda != arvore->nulo) {
      filhoSubstituto = substituto->esquerda;
    } else {
      filhoSubstituto = substituto->direita;
    }

    filhoSubstituto->pai = substituto->pai;

    if (substituto->pai == arvore->nulo) {
      contagem_remocao_rb++;
      arvore->raiz = filhoSubstituto;
    } else if (substituto == substituto->pai->esquerda) {
      contagem_remocao_rb+=2;
      substituto->pai->esquerda = filhoSubstituto;
    } else {
      contagem_remocao_rb+=2;
      substituto->pai->direita = filhoSubstituto;
    }

    contagem_remocao_rb++;
    if (substituto != no) {
      no->valor = substituto->valor;
    }

    contagem_remocao_rb++;
    if (substituto->cor == Preto) {
      balancearRemocao(arvore, filhoSubstituto);
    }

    free(substituto);
  }
}

No* sucessor(RedBlack* arvore, No* no) {
  no = no->direita;

  while (no->esquerda != arvore->nulo) {
    contagem_remocao_rb++;
    no = no->esquerda;
  }
  contagem_remocao_rb++;

  return no;
}

void balancearRemocao(RedBlack* arvore, No* no) {
  while (no != arvore->raiz && no->cor == Preto) {
    contagem_remocao_rb+=2;
    if (no == no->pai->esquerda) {
      No* irmao = no->pai->direita;

      contagem_remocao_rb++;
      if (irmao->cor == Vermelho) {
        irmao->cor = Preto;  // Caso 1
        no->pai->cor = Vermelho; // Caso 1
        rotacionarEsquerda(arvore, no->pai, &contagem_remocao_rb); // Caso 1
        irmao = no->pai->direita; // Caso 1
      }

      contagem_remocao_rb++;
      if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
        irmao->cor = Vermelho; // Caso 2
        no = no->pai; // Caso 2
      } else {
        contagem_remocao_rb++;
        if (irmao->direita->cor == Preto) {
          irmao->esquerda->cor = Preto; // Caso 3
          irmao->cor = Vermelho; // Caso 3
          rotacionarDireita(arvore, irmao, &contagem_remocao_rb); // Caso 3
          irmao = no->pai->direita; // Caso 3
        }

        irmao->cor = no->pai->cor; // Caso 4
        no->pai->cor = Preto; // Caso 4
        irmao->direita->cor = Preto; // Caso 4
        rotacionarEsquerda(arvore, no->pai, &contagem_remocao_rb); // Caso 4
        no = arvore->raiz; // Caso 4
      }
    } else {
      No* irmao = no->pai->esquerda;

      contagem_remocao_rb++;
      if (irmao->cor == Vermelho) {
        irmao->cor = Preto;  // Caso 1
        no->pai->cor = Vermelho; // Caso 1
        rotacionarDireita(arvore, no->pai, &contagem_remocao_rb); // Caso 1
        irmao = no->pai->esquerda; // Caso 1
      }

      contagem_remocao_rb++;
      if (irmao->direita->cor == Preto && irmao->esquerda->cor == Preto) {
        irmao->cor = Vermelho; // Caso 2
        no = no->pai; // Caso 2
      } else {
        contagem_remocao_rb++;
        if (irmao->esquerda->cor == Preto) {
        irmao->direita->cor = Preto; // Caso 3
        irmao->cor = Vermelho; // Caso 3
        rotacionarEsquerda(arvore, irmao, &contagem_remocao_rb); // Caso 3
        irmao = no->pai->esquerda; // Caso 3
        }

        irmao->cor = no->pai->cor; // Caso 4
        no->pai->cor = Preto; // Caso 4
        irmao->esquerda->cor = Preto; // Caso 4
        rotacionarDireita(arvore, no->pai, &contagem_remocao_rb); // Caso 4
        no = arvore->raiz; // Caso 4
      }
    }
  }

  no->cor = Preto;
}
