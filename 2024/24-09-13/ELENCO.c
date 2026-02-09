#include <stdlib.h>
#include <string.h>
#include "ELENCO.h"

struct elenco_t {
    char *nomi; // Matrice di stringhe allocata dinamicamente
    int N;       // Numero di città
};

ELENCO ELENCOinit(int N) {
    ELENCO e = malloc(sizeof(struct elenco_t));
    e->N = N;
    e->nomi = malloc(N * sizeof(char*));
    for (int i=0; i<N; i++) {
        e->nomi[i] = malloc(sizeof(char)); //[cite_start]// Assumiamo max 30 char come da testo [cite: 358]
    }
    return e;
}

ELENCO ELENCOfile(FILE *f, int N) {
    ELENCO e = ELENCOinit(N);
    for (int i=0; i<N; i++) {
        fscanf(f, "%c", e->nomi[i]);
    }
    return e;
}

int ELENCOgetN(ELENCO e) {
    return e->N;
}

char ELENCOgetNome(ELENCO e, int indice) {
    if (indice < 0 || indice >= e->N) return '\0';
    return e->nomi[indice];
}

void ELENCOfree(ELENCO e) {
    if (e == NULL) return;
    free(e->nomi);
    free(e->nomi);
    free(e);
}