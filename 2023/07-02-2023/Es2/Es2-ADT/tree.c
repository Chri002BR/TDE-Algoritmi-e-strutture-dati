#include <stdlib.h>
#include "tree.h"

/*
 * Definizione della struttura del nodo (interna al modulo).
 * Ogni nodo tiene traccia dei figli mediante un vettore di puntatori a nodo
 * e il numero di figli.
 */
typedef struct node {
    int value;              // Valore intero contenuto nel nodo
    int num_children;       // Numero di figli
    struct node **children; // Vettore di puntatori a nodo (figli)
} Node;

/*
 * Definizione della struttura dell'albero (ADT di prima classe).
 * Contiene solo il puntatore alla radice.
 */
struct tree {
    Node *root;
};

/*
 * Prototipo della funzione ricorsiva (statica, visibile solo in questo modulo).
 */
static int f_recursive(Node *n);

/*
 * Implementazione della funzione wrapper.
 */
int f(T t) {
    if (t == NULL || t->root == NULL) {
        return 0;
    }
    return f_recursive(t->root);
}

/*
 * Funzione ricorsiva.
 * (Scheletro da implementare secondo la logica dell'esercizio)
 */
static int f_recursive(Node *n) {
    // Implementazione logica
    // Se n->value < 0, il cammino si interrompe o non conta.
    // Altrimenti si calcola 1 + max(cammino valido dei figli)
    return 0; 
}
