#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H

#define VERMELHO 1
#define PRETO    0

typedef struct RBNode {
    int chave;
    int cor;
    struct RBNode *esq, *dir, *pai;
} RBNode;

typedef struct RBTree {
    RBNode *raiz;
    RBNode *nil;  /* sentinela */
} RBTree;

RBTree *rb_criar   (void);
void    rb_inserir  (RBTree *t, int chave);
void    rb_remover  (RBTree *t, int chave);
RBNode *rb_buscar   (RBTree *t, int chave);
void    rb_imprimir (RBTree *t, RBNode *x, int nivel);
void    rb_destruir (RBTree *t);

#endif /* RUBRO_NEGRA_H */
