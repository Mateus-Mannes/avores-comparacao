enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
  struct no* pai;
  struct no* esquerda;
  struct no* direita;
  Cor cor;
  int valor;
} No;

typedef struct arvore {
  struct no* raiz;
  struct no* nulo; 
} RedBlack;

int contagem_insercao_rb = 0;
int contagem_remocao_rb = 0;

RedBlack* cria_arvore_rb();
No* adiciona_na_arvore_rb(RedBlack* arvore, int valor);
void remove_na_arvore_rb(RedBlack* arvore, int valor);
int get_contagem_insercao_rb();
int get_contagem_remocao_rb();