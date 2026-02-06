#ifndef TREE_H
#define TREE_H

/* * 1. QUASI-ADT (Nodo)
 * La struttura è definita interamente nel .h.
 * L'utente PUÒ accedere direttamente a t->root->info o t->root->children.
 * Richiesto dalla traccia: "vettore di puntatori a nodo e il numero di figli".
 */
typedef struct node {
    int value;                 // Valore del nodo
    int num_children;         // Numero di figli
    struct node **children;   // Vettore dinamico di puntatori ai figli
} Node;

/* * 2. ADT DI PRIMA CLASSE (Albero T)
 * Qui dichiariamo solo che T è un puntatore a "qualcosa" chiamato struct TreeCDT.
 * Non definiamo i campi qui. L'utente vede solo il puntatore opaco.
 */
typedef struct TreeCDT *T;


// Funzioni per l'ADT
T createEmpty();
T createNode(int value);
void addChild(T parent, T child);
void destroyTree(T t);

// Funzione richiesta
int f(T t);



#endif