#ifndef TREE_H
#define TREE_H

/* 
 * Definizione del tipo T come "quasi ADT" (struttura visibile).
 * Il tipo T è un puntatore al nodo, ma la struttura del nodo è esposta.
 */

typedef struct node {
    int value;              // Valore intero contenuto nel nodo
    int num_children;       // Numero di figli
    struct node **children; // Vettore di puntatori a nodo (figli)
} Node;

typedef Node *T;

/* 
 * Funzione wrapper che conta la lunghezza del cammino più lungo 
 * contenente solo valori positivi o nulli.
 */
int f(T t);

#endif /* TREE_H */
