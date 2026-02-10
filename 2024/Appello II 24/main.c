#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NR 5 // Numero Righe
#define NC 20 // Numero Colonne

// 1. DEFINIZIONE STRUTTURE DATI
// Struttura per memorizzare una singola coordinata
typedef struct {
    int r;
    int c;
} Posizione;

// Struttura per memorizzare una parola trovata e la lista delle sue posizioni
typedef struct {
    char *parola;           // Puntatore alla parola (dall'elenco originale o copia)
    Posizione *posizioni;   // Vettore dinamico delle posizioni
    int num_posizioni;      // Numero di volte che la parola appare
} ParolaTrovata;

// 2. PROTOTIPO DELLA FUNZIONE (DA IMPLEMENTARE)
// Nota: Passiamo un puntatore a puntatore per 'risultato' per poter allocare il vettore dinamico
void paroleTrovate(char testo[NR][NC], char **elenco, int np, ParolaTrovata **risultato, int *num_trovate);

// funzione aggiuntiva (controlla se la parola è contenuta nell'elenco)
int verificaParola(char **elenco, char *parola, int np);

int verificaInResult(ParolaTrovata **risultato, char *parola, int  num_trovate);

// 3. MAIN DI TEST
int main() {
    // A. Setup dei dati di input
    char testo[NR][NC] = {
        "ciao.mondo.prova...",
        "testo.di.prova.abc.",
        "..ciao..ancora.....",
        "nessuna.parola.qui.",
        "fine.del.testo....."
    };

    // Creiamo un elenco di parole da cercare
    int np = 3;
    char *elenco[] = {"ciao", "prova", "nonpresente"};

    // Variabili per ottenere l'output
    ParolaTrovata *vettore_risultati = NULL;
    int dim_risultati = 0;

    // B. Chiamata alla tua funzione
    printf("--- Inizio Ricerca ---\n");
    paroleTrovate(testo, elenco, np, &vettore_risultati, &dim_risultati);

    // C. Verifica e Stampa dei risultati
    printf("\n--- Risultati ---\n");
    printf("Parole distinte trovate: %d\n", dim_risultati);
    
    for (int i = 0; i < dim_risultati; i++) {
        printf("Parola: '%s' (trovata %d volte):\n", 
               vettore_risultati[i].parola, 
               vettore_risultati[i].num_posizioni);
        
        for (int j = 0; j < vettore_risultati[i].num_posizioni; j++) {
            printf("\t -> Riga: %d, Colonna: %d\n", 
                   vettore_risultati[i].posizioni[j].r, 
                   vettore_risultati[i].posizioni[j].c);
        }
        // Pulizia memoria interna (opzionale per test rapido, ma buona prassi)
        free(vettore_risultati[i].posizioni);
    }

    // Pulizia vettore principale
    if(vettore_risultati) free(vettore_risultati);

    // D. Stampa del Risultato Atteso (Hardcoded) per verifica
    printf("\n--- Risultati Attesi (VERIFICA) ---\n");
    printf("Se il tuo codice funziona, dovresti vedere esattamente:\n");
    printf("1. Parola 'ciao'        -> Trovata in (0, 0) e (2, 2)\n");
    printf("2. Parola 'prova'       -> Trovata in (0, 11) e (1, 9)\n");
    printf("3. Parola 'nonpresente' -> Non deve apparire (o count 0)\n");
    printf("---------------------------------------\n");

    return 0;
}

// ---------------------------------------------------------
// SPAZIO PER IL TUO CODICE
// ---------------------------------------------------------

void paroleTrovate(char testo[NR][NC], char **elenco, int np, ParolaTrovata **risultato, int *num_trovate) {
    /* ISTRUZIONI:
       1. Scansiona la matrice 'testo' per individuare le parole (delimitate da !isalpha).
       2. Per ogni parola individuata nel testo, controlla se è presente in 'elenco'.
       3. Se presente, aggiorna la struttura dati dinamica '*risultato'.
          - Se è la prima volta che trovi quella parola dell'elenco, aggiungi un nuovo elemento a 'risultato'.
          - Se l'hai già trovata, aggiorna solo la lista delle posizioni di quell'elemento.
       4. Alla fine, aggiorna '*num_trovate' con la dimensione del vettore risultato.
    */

    *risultato = NULL;
    *num_trovate = 0;
    
    *risultato = malloc(sizeof(ParolaTrovata)*np);
    for(int i=0; i<np; i++){
        (*risultato)[i].posizioni = malloc(sizeof(Posizione));
        (*risultato)[i].parola = malloc(sizeof(char)*NC);
    }

    char parola[NC];
    int index, indiceRisultato, indiceMaxRis=0;

    for(int i=0; i<NR; i++){
        index=0;
        for(int j=0; j<NC; j++){
            if(isalpha(testo[i][j])){   // lettera
                parola[index]=testo[i][j];
                index++;
            }else{      // non lettera (delimito e controllo se la parola formata è nell'elenco)
                parola[index]='\0'; // termino la parola
                if(verificaParola(elenco, parola, np)){ // se la parola viene trovata come corrispondenza
                    if((indiceRisultato = verificaInResult(risultato, parola, *num_trovate))!=-1){   // se la parola viene trovata come corrispondenza 
                        (*risultato)[indiceRisultato].num_posizioni++;
                            // aggiungere una posizione...
                        (*risultato)[indiceRisultato].posizioni = realloc((*risultato)[indiceRisultato].posizioni, sizeof(Posizione)*(*risultato)[indiceRisultato].num_posizioni); 
                        (*risultato)[indiceRisultato].posizioni[(*risultato)[indiceRisultato].num_posizioni-1].r = i;
                        (*risultato)[indiceRisultato].posizioni[(*risultato)[indiceRisultato].num_posizioni-1].c = j-index;

                    }else{  // se la parola non è un occorrenza (parola nuova da aggiungere a result)
                    (*num_trovate)++;
                        (*risultato)[indiceMaxRis].num_posizioni=1;
                        strcpy((*risultato)[indiceMaxRis].parola, parola);
                        (*risultato)[indiceMaxRis].posizioni[0].r = i;
                        (*risultato)[indiceMaxRis].posizioni[0].c = j-index;
                    }
                }
                index=0;
            }   
        }

    }
    
}


// Ritorna 1 se trova una corrispondenza
int verificaParola(char **elenco, char *parola, int np){

    for(int i=0; i<np; i++){
        if(strcmp(elenco[i], parola)==0)
            return 1;
    }
    return 0;
}

int verificaInResult(ParolaTrovata **risultato, char *parola, int  num_trovate){

    for(int i=0; i<num_trovate; i++){
        if(strcmp((*risultato)[i].parola, parola)==0)
            return i;
    }
    return -1;
}
