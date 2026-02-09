#include <stdio.h>

typedef struct distmatr_t *DISTMATR;

DISTMATR DISTMATRinit(int N);
DISTMATR DISTMATRfile(FILE *f, int N); // Legge la matrice dal file

int DISTMATRgetVal(DISTMATR d, int i, int j); // Restituisce distanza tra i e j
int DISTMATRgetN(DISTMATR d); // Utile per sapere la dimensione
void DISTMATRfree(DISTMATR d);




