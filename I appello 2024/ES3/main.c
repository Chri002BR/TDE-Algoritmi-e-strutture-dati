#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* --- FUNZIONI DI SUPPORTO (GIA' PRONTE) --- */

// Ritorna 1 se il carattere è una vocale, 0 altrimenti
int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Verifica se due parole possono essere concatenate secondo la regola
// Regola: Se w1 finisce con vocale, w2 NON può iniziare con vocale (quindi deve essere consonante)
//         Se w1 finisce con consonante, w2 NON può iniziare con consonante (quindi deve essere vocale)
// Ritorna 1 se OK, 0 se VIETATO
int checkConstraint(char *w1, char *w2) {
    if (w1 == NULL) return 1; // Se w1 è NULL, vuol dire che w2 è la prima parola della lista: va sempre bene.
    
    int len1 = strlen(w1);
    char lastChar = w1[len1 - 1]; // Ultimo carattere della prima parola
    char firstChar = w2[0];       // Primo carattere della seconda parola
    
    int v1 = isVowel(lastChar);
    int v2 = isVowel(firstChar);

    // Se entrambi sono vocali (1, 1) -> VIETATO
    // Se entrambi sono consonanti (0, 0) -> VIETATO
    // Devono essere diversi (1, 0) oppure (0, 1)
    if (v1 == v2) 
        return 0; // Vietato
    
    return 1; // Ok
}

/* --- TO DO: IMPLEMENTA QUESTA PARTE --- */

/* * Suggerimento per l'implementazione:
 * 1. Ti serve una funzione ricorsiva ausiliaria (wrapper).
 * 2. Ti serve un vettore 'visited' (o mark) per sapere quali parole hai già usato.
 * 3. Ti serve mantenere due stringhe: 
 * - 'currentString': quella che stai costruendo passo passo nella ricorsione.
 * - 'bestString': la migliore trovata finora (più lunga).
 * * Logica ricorsiva:
 * - Per ogni parola nel dizionario:
 * - Se non è usata E rispetta il vincolo con l'ultima parola inserita:
 * - Segnala come usata.
 * - Aggiungi alla concatenazione corrente.
 * - Ricorsione.
 * - Backtrack (togli dalla concatenazione, segna come non usata).
 */

void solve(char **words, int n, int *visited, char *currentStr, char *bestStr, char *lastWord) {
    // 1. Controlla se la stringa corrente è la migliore trovata finora
    //    Se strlen(currentStr) > strlen(bestStr), copia current in best.

    // 2. Ciclo su tutte le parole disponibili
    //    if (!visited[i] && checkConstraint(lastWord, words[i])) {
    //        ... ricorsione ...
    //    }

    /* SCRIVI QUI IL TUO CODICE */
    
}


void *bestConcat_r(char **words, int n, char *string, char *stringBest, int *mark){
    // controlla best   
    if(strlen(stringBest) < strlen(string))
        strcpy(stringBest, string);

    for(int i=0; i<n; i++){

        if(mark[i]==0 && checkConstraint(string, words[i])){
            
            mark[i] = 1;

            int lenStr=strlen(string);
            int lenWord = strlen(words[i]);

            for(int j=0; j<lenWord; j++){
                string[lenStr + j] = words[i][j];
            }
            string[lenStr + lenWord]='\0';

            bestConcat_r(words, n, string, stringBest, mark);

            // elimino la parola da string
            string[lenStr]='\0';
            mark[i]=0;




        }
    }    

}

char *bestConcat(char **words, int n) {
    // 1. Alloca le strutture necessarie (visited, bestString, currentString)
    //    Nota: La lunghezza massima possibile è la somma di tutte le lunghezze + 1 per terminatore.
    // 2. Chiama la funzione ricorsiva.
    // 3. Libera memoria temporanea e ritorna la bestString.

    /* SCRIVI QUI IL TUO CODICE */
    
    int Nchar=0;
    for(int i=0; i<n; i++){
        Nchar += strlen(words[i]);
    }

    int *mark=calloc(sizeof(int), n);            // per indicare quali elementi ho già preso
    char *string=malloc(sizeof(char)*Nchar+1);  // aggiungo uno per '\n'
    char *stringBest=malloc(sizeof(char)*Nchar+1);  // aggiungo uno per '\n'

    
    bestConcat_r(words, n, string, stringBest, mark);


    return stringBest; // Rimuovi e ritorna la stringa allocata
}

/* --- MAIN DI TEST --- */

int main() {
    /* Esempio:
     * Parole: "era", "finito", "gatto", "albero"
     *
     * Analisi Vincoli:
     * - "era" (finisce 'a' -> V). Next deve iniziare per C.
     * - "finito" (finisce 'o' -> V). Next deve iniziare per C.
     * - "gatto" (finisce 'o' -> V). Next deve iniziare per C.
     * - "albero" (finisce 'o' -> V). Next deve iniziare per C.
     * * Percorsi possibili:
     * 1. era (V) -> finito (C..V) -> gatto (C..V) -> STOP (albero inizia per V, vietato dopo gatto che finisce V)
     * Lunghezza: 3 + 6 + 5 = 14 ("erafinitogatto")
     * * 2. albero (V) -> finito (C..V) -> gatto (C..V) -> STOP
     * Lunghezza: 6 + 6 + 5 = 17 ("alberofinitogatto")
     * * 3. gatto (V) -> finito (C..V) -> era (V..V) -> NO! (era inizia V, finito finisce V)
     */

    char *words[] = {
        "era",      // 3 chars, ends V
        "finito",   // 6 chars, starts C, ends V
        "gatto",    // 5 chars, starts C, ends V
        "albero"    // 6 chars, starts V, ends V
    };
    int n = 4;

    printf("--- Inizio Ricerca ---\n");
    char *result = bestConcat(words, n);

    if (result != NULL) {
        printf("Miglior stringa: %s\n", result);
        printf("Lunghezza: %lu\n", strlen(result));
        free(result);
    } else {
        printf("Nessuna combinazione trovata.\n");
    }

    printf("\nAtteso:\nStringa: alberofinitogatto (o varianti stesso ordine)\nLunghezza: 17\n");

    return 0;
}