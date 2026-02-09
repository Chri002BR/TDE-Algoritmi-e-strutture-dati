#include <stdio.h>

// Definizione del tipo opaco
typedef struct elenco_t *ELENCO;

// Costruttore: alloca la struttura vuota
ELENCO ELENCOinit(int N);

// Caricamento: legge i nomi dal file e li salva
// (Il file deve essere già aperto e posizionato sui nomi)
ELENCO ELENCOfile(FILE *f, int N);

// Getter: restituisce il numero di città
int ELENCOgetN(ELENCO e);

// Getter extra (utile per stampare): restituisce il nome dato l'indice
char ELENCOgetNome(ELENCO e, int indice);

// Distruttore: libera la memoria
void ELENCOfree(ELENCO e);