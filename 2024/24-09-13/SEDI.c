#include <stdlib.h>
#include "SEDI.h"

struct sedi_t {
    int *s;       // Vettore flag: 1 = è sede, 0 = non è sede
    int nums;     // Numero corrente di sedi (contatore)
    int N;        // Numero totale città
    DISTMATR d;   // Riferimento alla matrice distanze
};

SEDI SEDIinit(int N, DISTMATR d) {
    SEDI newS = malloc(sizeof(struct sedi_t));
    newS->N = N;
    newS->nums = 0;
    newS->d = d;
    newS->s = calloc(N, sizeof(int)); // calloc inizializza a 0
    return newS;
}

void SEDIadd(SEDI s, int indice) {
    if (s->s[indice] == 0) {
        s->s[indice] = 1;
        s->nums++;
    }
}

void SEDIremove(SEDI s, int indice) {
    if (s->s[indice] == 1) {
        s->s[indice] = 0;
        s->nums--;
    }
}

int SEDIisSede(SEDI s, int indice) {
    return s->s[indice];
}

int SEDIgetN(SEDI s) { return s->N; }
int SEDIgetNumS(SEDI s) { return s->nums; }
DISTMATR SEDIgetD(SEDI s) { return s->d; }

void SEDIfree(SEDI s) {
    free(s->s);
    free(s);
}