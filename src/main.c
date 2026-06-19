#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

/* Definicao do contador global usado por avl.c, rubro_negra.c e arv_b.c */
long long contador_ops = 0;

#define MAX_N       10000
#define PASSO       100
#define AMOSTRAS    10

/* Chaves aleatorias: [amostra][indice] */
static int chaves[AMOSTRAS][MAX_N];

static void gerar_chaves(void) {
    srand(42);
    for (int s = 0; s < AMOSTRAS; s++)
        for (int i = 0; i < MAX_N; i++)
            chaves[s][i] = rand();
}

/* ----- medicao AVL ----- */

static double medir_avl_insercao(int amostra, int n) {
    nodoAVL *raiz = NULL;
    long long total = 0;
    for (int i = 0; i < n; i++) {
        contador_ops = 0;
        raiz = insereAVL(chaves[amostra][i], raiz);
        total += contador_ops;
    }
    /* libera a arvore */
    for (int i = 0; i < n; i++) raiz = removeAVL(raiz, chaves[amostra][i]);
    return (double)total / n;
}

static double medir_avl_remocao(int amostra, int n) {
    nodoAVL *raiz = NULL;
    for (int i = 0; i < n; i++) raiz = insereAVL(chaves[amostra][i], raiz);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        contador_ops = 0;
        raiz = removeAVL(raiz, chaves[amostra][i]);
        total += contador_ops;
    }
    return (double)total / n;
}

/* ----- medicao Rubro-Negra ----- */

static double medir_rb_insercao(int amostra, int n) {
    RBTree *rb = rb_criar();
    long long total = 0;
    for (int i = 0; i < n; i++) {
        contador_ops = 0;
        rb_inserir(rb, chaves[amostra][i]);
        total += contador_ops;
    }
    rb_destruir(rb);
    return (double)total / n;
}

static double medir_rb_remocao(int amostra, int n) {
    RBTree *rb = rb_criar();
    for (int i = 0; i < n; i++) rb_inserir(rb, chaves[amostra][i]);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        contador_ops = 0;
        rb_remover(rb, chaves[amostra][i]);
        total += contador_ops;
    }
    rb_destruir(rb);
    return (double)total / n;
}

/* ----- medicao Arvore B ----- */

static double medir_b_insercao(int amostra, int n, int t) {
    BArvore *bt = b_criar(t);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        contador_ops = 0;
        b_inserir(bt, chaves[amostra][i]);
        total += contador_ops;
    }
    b_destruir(bt);
    return (double)total / n;
}

static double medir_b_remocao(int amostra, int n, int t) {
    BArvore *bt = b_criar(t);
    for (int i = 0; i < n; i++) b_inserir(bt, chaves[amostra][i]);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        contador_ops = 0;
        b_remover(bt, chaves[amostra][i]);
        total += contador_ops;
    }
    b_destruir(bt);
    return (double)total / n;
}

/* ----- loop principal ----- */

int main(void) {
    gerar_chaves();

    FILE *fins = fopen("resultado_insercao.csv", "w");
    FILE *frem = fopen("resultado_remocao.csv",  "w");
    if (!fins || !frem) { perror("fopen"); return 1; }

    fprintf(fins, "n,AVL,RB,B1,B5,B10\n");
    fprintf(frem, "n,AVL,RB,B1,B5,B10\n");

    int ordens_b[] = {1, 5, 10};

    for (int n = PASSO; n <= MAX_N; n += PASSO) {

        double soma_ins[5] = {0};
        double soma_rem[5] = {0};

        for (int s = 0; s < AMOSTRAS; s++) {
            soma_ins[0] += medir_avl_insercao(s, n);
            soma_ins[1] += medir_rb_insercao (s, n);
            soma_ins[2] += medir_b_insercao  (s, n, ordens_b[0]);
            soma_ins[3] += medir_b_insercao  (s, n, ordens_b[1]);
            soma_ins[4] += medir_b_insercao  (s, n, ordens_b[2]);

            soma_rem[0] += medir_avl_remocao(s, n);
            soma_rem[1] += medir_rb_remocao (s, n);
            soma_rem[2] += medir_b_remocao  (s, n, ordens_b[0]);
            soma_rem[3] += medir_b_remocao  (s, n, ordens_b[1]);
            soma_rem[4] += medir_b_remocao  (s, n, ordens_b[2]);
        }

        fprintf(fins, "%d,%.4f,%.4f,%.4f,%.4f,%.4f\n", n,
                soma_ins[0]/AMOSTRAS, soma_ins[1]/AMOSTRAS,
                soma_ins[2]/AMOSTRAS, soma_ins[3]/AMOSTRAS, soma_ins[4]/AMOSTRAS);

        fprintf(frem, "%d,%.4f,%.4f,%.4f,%.4f,%.4f\n", n,
                soma_rem[0]/AMOSTRAS, soma_rem[1]/AMOSTRAS,
                soma_rem[2]/AMOSTRAS, soma_rem[3]/AMOSTRAS, soma_rem[4]/AMOSTRAS);

        if (n % 1000 == 0) { printf("n = %d\n", n); fflush(stdout); }
    }

    fclose(fins);
    fclose(frem);
    printf("Concluido. Gerados: resultado_insercao.csv  resultado_remocao.csv\n");
    return 0;
}
