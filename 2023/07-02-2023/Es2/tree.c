#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* ============================================================================
 * ADT DI PRIMA CLASSE - TIPO OPACO
 * ============================================================================
 * La definizione completa della struttura TreeCDT è NASCOSTA all'utente.
 * Appare solo in questo file .c, NON nell'header.
 * L'utente può usare il tipo T (puntatore a TreeCDT) ma non può accedere
 * direttamente ai campi interni (es. non può scrivere t->root).
 * Questo garantisce l'incapsulamento: l'implementazione interna può cambiare
 * senza modificare il codice cliente.
 */
struct TreeCDT {
    Node* root; // puntatore alla radice dell'albero
};

/* ----------------------------------------------------------------------------
 * FUNZIONI PUBBLICHE DELL'ADT DI PRIMA CLASSE
 * ----------------------------------------------------------------------------
 * Queste funzioni costituiscono l'interfaccia pubblica dell'ADT.
 * Sono le UNICHE operazioni che l'utente può usare per manipolare un oggetto T.
 */

// Crea un albero vuoto (ADT di prima classe)
T createEmpty() {
    T t = (T)malloc(sizeof(struct TreeCDT));
    t->root = NULL;
    return t;
}

// Crea un albero con un singolo nodo (ADT di prima classe)
T createNode(int value) {
    T t = (T)malloc(sizeof(struct TreeCDT));
    // Qui si crea anche un nodo (quasi ADT) ma è nascosto all'utente
    t->root = (Node*)malloc(sizeof(Node));
    t->root->value = value;
    t->root->children = NULL;
    t->root->num_children = 0;
    return t;
}

// Aggiunge un figlio a un nodo (ADT di prima classe)
// Internamente manipola i campi del quasi ADT Node
void addChild(T parent, T child) {
    if (parent == NULL || parent->root == NULL || child == NULL) return;
    
    /* QUASI ADT - Accesso diretto ai campi di Node
     * Qui possiamo accedere direttamente a p->num_children e p->children
     * perché Node è un quasi ADT (struttura visibile in tree.h).
     * Questo è permesso SOLO all'interno del modulo tree.c
     */
    Node* p = parent->root;
    p->num_children++;
    p->children = (Node**)realloc(p->children, p->num_children * sizeof(Node*));
    p->children[p->num_children - 1] = child->root;
}

// Distrugge un albero (ADT di prima classe)
void destroyTree(T t) {
    if (t == NULL) return;
    // TODO: Implementare ricorsivamente la distruzione di tutti i nodi
    free(t);
}

/* ============================================================================
 * FUNZIONI PRIVATE/AUSILIARIE
 * ============================================================================
 * Queste funzioni sono dichiarate 'static' quindi visibili SOLO in questo file.
 * Non fanno parte dell'interfaccia pubblica dell'ADT.
 */

/* Funzione ricorsiva ausiliaria - lavora sul QUASI ADT Node
 * Questa funzione accede direttamente ai campi di Node (value, children, num_children)
 * perché Node è un quasi ADT con struttura visibile.
 * È dichiarata static perché è un dettaglio implementativo, non parte dell'interfaccia.
 */
static int f_ric(Node* n) {
    if (n == NULL) return 0;
    
    // QUASI ADT: accesso diretto a n->value
    if (n->value < 0) return 0;
    
    // Trova il massimo tra tutti i figli
    int max = 0;
    // QUASI ADT: accesso diretto a n->num_children e n->children
    for (int i = 0; i < n->num_children; i++) {
        int child_len = f_ric(n->children[i]);
        if (child_len > max) max = child_len;
    }
    
    // Aggiungi 1 per il nodo corrente (valore >= 0)
    return 1 + max;
}

/* ----------------------------------------------------------------------------
 * FUNZIONE WRAPPER - PARTE DELL'INTERFACCIA PUBBLICA DELL'ADT
 * ----------------------------------------------------------------------------
 * Questa è la funzione richiesta dall'esercizio.
 * È pubblica (non static) e lavora sul tipo ADT di prima classe T.
 * Internamente chiama la funzione ausiliaria f_ric che lavora sul quasi ADT Node.
 */
int f(T t) {
    if (t == NULL || t->root == NULL) return 0;
    // Delega il lavoro alla funzione ricorsiva che lavora sui nodi
    return f_ric(t->root);
}

/* ============================================================================
 * RIEPILOGO:
 * ============================================================================
 * ADT DI PRIMA CLASSE (T):
 * - struct TreeCDT definita SOLO in .c (opaca)
 * - Funzioni pubbliche: createEmpty, createNode, addChild, destroyTree, f
 * - L'utente NON può accedere a t->root
 * 
 * QUASI ADT (Node):
 * - struct Node definita in tree.h (visibile)
 * - Usata internamente dalle funzioni dell'ADT
 * - I suoi campi (value, children, num_children) sono accessibili
 *   SOLO all'interno del modulo tree.c
 * - La funzione ricorsiva f_ric lavora direttamente su Node
 */