#include <stdlib.h>
#include "tree.h"

/*
 * Prototipo della funzione ricorsiva (statica).
 * In questo caso calcola la lunghezza del cammino continua di positivi
 * che inizia PARTENDO dal nodo 'n'.
 * Aggiorna tramite side-effect (puntatore) il massimo globale trovato.
 */
static int longest_path_starting_here(Node *n, int *global_max);

/*
 * Implementazione della funzione wrapper.
 */
int f(T t) {
    if (t == NULL) {
        return 0;
    }
    
    int max_len = 0;
    longest_path_starting_here(t, &max_len);
    return max_len;
}

/*
 * Funzione ricorsiva.
 * Ritorna: la lunghezza del cammino valido (nodi >= 0) che inizia in 'n' e scende.
 * Side-effect: aggiorna *global_max se trova un cammino locale o nei sottoalberi più lungo.
 */
static int longest_path_starting_here(Node *n, int *global_max) {
    if (n == NULL) {
        return 0;
    }

    int current_path_len = 0; // Se il nodo è negativo, il cammino che parte qui è 0.
    
    // Iteriamo sui figli per processarli (necessario per esplorare tutto l'albero per il global_max)
    int max_child_path = 0;
    for (int i = 0; i < n->num_children; i++) {
        int child_res = longest_path_starting_here(n->children[i], global_max);
        if (child_res > max_child_path) {
            max_child_path = child_res;
        }
    }

    if (n->value >= 0) {
        current_path_len = 1 + max_child_path;
    } else {
        current_path_len = 0; 
    }

    // Aggiorniamo il massimo globale
    if (current_path_len > *global_max) {
        *global_max = current_path_len;
    }
    
    return current_path_len;
}
