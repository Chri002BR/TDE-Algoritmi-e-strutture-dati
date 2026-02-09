#include <stdio.h>
#include "ELENCO.h"
#include "DISTMATR.h"
#include "SEDI.h"
#include "SERVIZI.h"

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (fin == NULL) return 1;

    int N;
    fscanf(fin, "%d", &N);

    // 1. Carico Elenco Città
    ELENCO elenco = ELENCOfile(fin, N);

    // 2. Carico Matrice Distanze
    DISTMATR distanze = DISTMATRfile(fin, N);

    // 3. Inizializzo struttura vuota per le Sedi (il problema richiederà di riempirla)
    SEDI sedi = SEDIinit(N, distanze);

    // ... qui andrà la logica del problema (calcolo combinazioni, etc.) ...
    
    // Pulizia finale
    ELENCOfree(elenco);
    DISTMATRfree(distanze);
    SEDIfree(sedi);
    fclose(fin);
    return 0;
}



int checkSedi(DISTMATR d, int MAXD, int MINS, SEDI sol){
    int N=DISTMATRgetN(d);

    for(int i=0; i<N; i++){
        if(SEDIisSede(sol, i))
            continue;
        
        for(int j=0; j<N; j++){
            if(DISTMATRgetVal(d, i, j) <= MAXD)
                break;
        }
        
    }
    



    return 1;
}



