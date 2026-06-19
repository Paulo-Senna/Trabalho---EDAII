#ifndef AVL_H
#define AVL_H

typedef struct nodoAVL {
    int info;
    struct nodoAVL *esq;
    struct nodoAVL *dir;
    int alt;
} nodoAVL;

int      altura      (nodoAVL *sub);
nodoAVL *insereAVL   (int info, nodoAVL *arv);
nodoAVL *removeAVL   (nodoAVL *raiz, int x);
nodoAVL *buscaAVL    (nodoAVL *raiz, int x);
void     imprimirAVL (nodoAVL *raiz, int nivel);

#endif /* AVL_H */
