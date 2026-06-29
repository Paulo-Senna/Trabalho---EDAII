#include <stdio.h>
#include <stdlib.h>
#include "../include/rubro_negra.h"
#include "../include/arvores.h"

RBTree *rb_criar() {
    RBTree *t = (RBTree *)malloc(sizeof(RBTree));
    t->nil = (RBNode *)malloc(sizeof(RBNode));
    t->nil->cor = PRETO;
    t->nil->esq = t->nil->dir = t->nil->pai = t->nil;
    t->raiz = t->nil;
    return t;
}

static void rotacionar_esq(RBTree *t, RBNode *x) {
    contador_ops++; // rotacao
    RBNode *y = x->dir;
    x->dir = y->esq;
    if (y->esq != t->nil) y->esq->pai = x;
    y->pai = x->pai;
    if      (x->pai == t->nil)   t->raiz     = y;
    else if (x == x->pai->esq)   x->pai->esq = y;
    else                          x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

static void rotacionar_dir(RBTree *t, RBNode *x) {
    contador_ops++; // rotacao
    RBNode *y = x->esq;
    x->esq    = y->dir;
    if (y->dir != t->nil) y->dir->pai = x;
    y->pai = x->pai;
    if      (x->pai == t->nil)   t->raiz     = y;
    else if (x == x->pai->dir)   x->pai->dir = y;
    else                          x->pai->esq = y;
    y->dir = x;
    x->pai = y;
}

static void inserir_fixup(RBTree *t, RBNode *z) {
    while (z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            RBNode *y = z->pai->pai->dir;
            if (y->cor == VERMELHO) {
                z->pai->cor      = PRETO;
                y->cor           = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) { z = z->pai; rotacionar_esq(t, z); }
                z->pai->cor      = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_dir(t, z->pai->pai);
            }
        } else {
            RBNode *y = z->pai->pai->esq;
            if (y->cor == VERMELHO) {
                z->pai->cor      = PRETO;
                y->cor           = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) { z = z->pai; rotacionar_dir(t, z); }
                z->pai->cor      = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_esq(t, z->pai->pai);
            }
        }
    }
    t->raiz->cor = PRETO;
}

void rb_inserir(RBTree *t, int chave) {
    RBNode *z  = (RBNode *)malloc(sizeof(RBNode));
    z->chave = chave;
    z->cor = VERMELHO;
    z->esq = z->dir = z->pai = t->nil;

    RBNode *y = t->nil;
    RBNode *x = t->raiz;
    while (x != t->nil) {
        contador_ops++; // comparacao
        y = x;
        x = (z->chave < x->chave) ? x->esq : x->dir;
    }
    z->pai = y;
    if      (y == t->nil)         t->raiz  = z;
    else if (z->chave < y->chave) y->esq   = z;
    else                          y->dir    = z;

    inserir_fixup(t, z);
}

static void transplant(RBTree *t, RBNode *u, RBNode *v) {
    if      (u->pai == t->nil)   t->raiz     = v;
    else if (u == u->pai->esq)   u->pai->esq = v;
    else                          u->pai->dir  = v;
    v->pai = u->pai;
}

static RBNode *minimo(RBTree *t, RBNode *x) {
    while (x->esq != t->nil) x = x->esq;
    return x;
}

static void remover_fixup(RBTree *t, RBNode *x) {
    while (x != t->raiz && x->cor == PRETO) {
        if (x == x->pai->esq) {
            RBNode *w = x->pai->dir;
            if (w->cor == VERMELHO) {
                w->cor      = PRETO;
                x->pai->cor = VERMELHO;
                rotacionar_esq(t, x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
                w->cor = VERMELHO; x = x->pai;
            } else {
                if (w->dir->cor == PRETO) {
                    w->esq->cor = PRETO; w->cor = VERMELHO;
                    rotacionar_dir(t, w); w = x->pai->dir;
                }
                w->cor = x->pai->cor; x->pai->cor = PRETO;
                w->dir->cor = PRETO; rotacionar_esq(t, x->pai);
                x = t->raiz;
            }
        } else {
            RBNode *w = x->pai->esq;
            if (w->cor == VERMELHO) {
                w->cor      = PRETO;
                x->pai->cor = VERMELHO;
                rotacionar_dir(t, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
                w->cor = VERMELHO; x = x->pai;
            } else {
                if (w->esq->cor == PRETO) {
                    w->dir->cor = PRETO; w->cor = VERMELHO;
                    rotacionar_esq(t, w); w = x->pai->esq;
                }
                w->cor = x->pai->cor; x->pai->cor = PRETO;
                w->esq->cor = PRETO; rotacionar_dir(t, x->pai);
                x = t->raiz;
            }
        }
    }
    x->cor = PRETO;
}

void rb_remover(RBTree *t, int chave) {
    RBNode *z = t->raiz;
    while (z != t->nil) {
        contador_ops++; // comparacao
        if      (chave == z->chave) break;
        else if (chave < z->chave)  z = z->esq;
        else                        z = z->dir;
    }
    if (z == t->nil) return;

    RBNode *y = z;
    RBNode *x;
    int y_cor_orig = y->cor;

    if (z->esq == t->nil) {
        x = z->dir; transplant(t, z, z->dir);
    } else if (z->dir == t->nil) {
        x = z->esq; transplant(t, z, z->esq);
    } else {
        y = minimo(t, z->dir);
        y_cor_orig = y->cor;
        x = y->dir;
        if (y->pai == z) {
            x->pai = y;
        } else {
            transplant(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplant(t, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }
    free(z);
    if (y_cor_orig == PRETO) remover_fixup(t, x);
}

RBNode *rb_buscar(RBTree *t, int chave) {
    RBNode *x = t->raiz;
    while (x != t->nil) {
        if (chave == x->chave) return x;
        else if (chave < x->chave)  x = x->esq;
        else x = x->dir;
    }
    return NULL;
}

void rb_imprimir(RBTree *t, RBNode *x, int nivel) {
    if (x == t->nil) return;
    rb_imprimir(t, x->dir, nivel + 1);
    printf("\n");
    for (int i = 0; i < nivel; i++) printf("\t");
    printf("%d(%c)", x->chave, x->cor == VERMELHO ? 'V' : 'P');
    rb_imprimir(t, x->esq, nivel + 1);
}

static void liberar_nos(RBTree *t, RBNode *x) {
    if (x == t->nil) return;
    liberar_nos(t, x->esq);
    liberar_nos(t, x->dir);
    free(x);
}

void rb_destruir(RBTree *t) {
    liberar_nos(t, t->raiz);
    free(t->nil);
    free(t);
}
