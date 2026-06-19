#ifndef ARV_B_H
#define ARV_B_H

typedef struct BNodo {
    int     *chaves;
    struct BNodo **filhos;
    int      n;
    int      folha;
} BNodo;

typedef struct BArvore {
    BNodo *raiz;
    int    t;     /* grau minimo (ordem) */
} BArvore;

BArvore *b_criar    (int t);
void     b_inserir  (BArvore *bt, int chave);
void     b_remover  (BArvore *bt, int chave);
BNodo   *b_buscar   (BArvore *bt, BNodo *x, int chave);
void     b_imprimir (BNodo *x, int nivel);
void     b_destruir (BArvore *bt);

#endif /* ARV_B_H */
