typedef struct no_avl
{
    struct no_avl *pai;
    struct no_avl *esquerda;
    struct no_avl *direita;
    int altura;
    int valor;
} NoAvl;

typedef struct arvore_avl
{
    struct no_avl *raiz;
} ArvoreAvl;

ArvoreAvl* cria_arvore_avl();

NoAvl *adiciona_na_arvore_avl(ArvoreAvl * arvore, int valor);

NoAvl* remove_na_arvore_avl(ArvoreAvl * arvore, int valor);

void print_arvore_avl(ArvoreAvl* arvore);