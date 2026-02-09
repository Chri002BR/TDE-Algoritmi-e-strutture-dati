#include <stdlib.h>
#include "DISTMATR.h"

struct distmatr_t {
    int **m; // Matrice quadrata
    int N;
};

DISTMATR DISTMATRinit(int N) {
    DISTMATR d = malloc(sizeof(struct distmatr_t));
    d->N = N;
    d->m = malloc(N * sizeof(int*));
    for (int i=0; i<N; i++) {
        d->m[i] = malloc(N * sizeof(int));
    }
    return d;
}

DISTMATR DISTMATRfile(FILE *f, int N) {
    DISTMATR d = DISTMATRinit(N);
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            fscanf(f, "%d", &d->m[i][j]);
        }
    }
    return d;
}

int DISTMATRgetVal(DISTMATR d, int i, int j) {
    return d->m[i][j];
}

int DISTMATRgetN(DISTMATR d) {
    return d->N;
}

void DISTMATRfree(DISTMATR d) {
    for (int i=0; i < d->N; i++) free(d->m[i]);
    free(d->m);
    free(d);
}