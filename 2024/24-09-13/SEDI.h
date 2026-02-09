#include "DISTMATR.h"

typedef struct sedi_t *SEDI;

// Inizializza l'insieme vuoto, collegandolo alla matrice distanze
SEDI SEDIinit(int N, DISTMATR d);

// Aggiunge la città 'indice' all'insieme delle sedi
void SEDIadd(SEDI s, int indice);

// Rimuove (backtracking)
void SEDIremove(SEDI s, int indice);

// Controlla se 'indice' è una sede (restituisce 1 o 0)
int SEDIisSede(SEDI s, int indice);

// Getters
int SEDIgetN(SEDI s);
int SEDIgetNumS(SEDI s); // Quante sedi sono state scelte finora?
DISTMATR SEDIgetD(SEDI s);

void SEDIfree(SEDI s);
