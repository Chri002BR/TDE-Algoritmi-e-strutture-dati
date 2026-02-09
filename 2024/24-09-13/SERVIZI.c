#include <stdlib.h>
#include "SERVIZI.h"

struct servizi_t {
    int *assegnazioni; // assegnazioni[i] = indice della sede che serve la città i
    int N;
    float media;
};

SERVIZI SERVIZIinit(int N) {
    SERVIZI s = malloc(sizeof(struct servizi_t));
    s->N = N;
    s->assegnazioni = malloc(N * sizeof(int));
    for(int i=0; i<N; i++) s->assegnazioni[i] = -1; // -1 = non assegnato
    s->media = 0.0;
    return s;
}

void SERVIZIassign(SERVIZI s, int citta, int sede) {
    s->assegnazioni[citta] = sede;
}

int SERVIZIcount(SERVIZI s, int sedeIndex) {
    int count = 0;
    for (int i=0; i<s->N; i++) {
        // Se la città i è assegnata a sedeIndex
        if (s->assegnazioni[i] == sedeIndex) {
            count++;
        }
    }
    return count;
}

void SERVIZIsetMedia(SERVIZI s, float media) { s->media = media; }
float SERVIZIgetMedia(SERVIZI s) { return s->media; }

void SERVIZIfree(SERVIZI s) {
    free(s->assegnazioni);
    free(s);
}