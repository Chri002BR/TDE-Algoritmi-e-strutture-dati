#include "tree.h"
#include <stdlib.h>
#include <stddef.h>


// Sia per il quasi-ADT che per la definizione di del puntatore T (che punta a questa struttura)
struct Node{
    int value;
    int n_children;
    struct Node **children; /* Vettore di puntatori a nodo */
}node;


// ADT 1 classe
struct tree{
    struct Node *root;
};



/* Funzione helper privata per calcolare il massimo tra due interi */
static int max(int a, int b){
    return (a > b) ? a : b;
}

/* Funzione ricorsiva che conta il cammino più lungo con solo valori >= 0 */
static int recursive_visit(struct Node *n){
    int i;
    int max_child_length = 0;
    int current_child_length;

    /* Caso base: nodo nullo */
    if(n == NULL)
        return 0;

    /* Se il valore è negativo, il cammino si interrompe */
    if(n->value < 0)
        return 0;

    /* Il valore è >= 0, quindi questo nodo conta */
    /* Se è una foglia, ritorna 1 */
    if(n->n_children == 0)
        return 1;

    /* Altrimenti, trova il massimo tra i cammini dei figli */
    for(i = 0; i < n->n_children; i++){
        current_child_length = recursive_visit(n->children[i]);
        max_child_length = max(max_child_length, current_child_length);
    }

    /* Ritorna 1 (questo nodo) + il massimo cammino tra i figli */
    return 1 + max_child_length;
}

T createTree(int value){
    T albero = malloc(sizeof(struct tree));
    struct Node *nodo = malloc(sizeof(struct Node));
    nodo->value = value;
    nodo->n_children = 0;
    nodo->children = NULL;
    albero->root = nodo;

    return albero;
}

/* Funzione helper privata per aggiungere figlio a un nodo specifico */
static void addChildToNode(struct Node *parent, struct Node *child){
    /* Espandi il vettore children con realloc */
    parent->children = realloc(parent->children, (parent->n_children + 1) * sizeof(struct Node*));
    parent->children[parent->n_children] = child;
    parent->n_children++;
}

/* Funzione helper privata per cercare nodo con un dato valore (DFS) */
static struct Node* findNode(struct Node *n, int value){
    int i;
    struct Node *result;

    if(n == NULL)
        return NULL;

    if(n->value == value)
        return n;

    /* Cerca ricorsivamente nei figli */
    for(i = 0; i < n->n_children; i++){
        result = findNode(n->children[i], value);
        if(result != NULL)
            return result;
    }

    return NULL;
}

/* Aggiunge un figlio al nodo che ha valore parent_value */
void addChild(T albero, int parent_value, int child_value){
    struct Node *parent;
    struct Node *newChild;

    if(albero == NULL || albero->root == NULL)
        return;

    /* Trova il nodo padre */
    parent = findNode(albero->root, parent_value);
    if(parent == NULL)
        return;

    /* Crea il nuovo nodo figlio */
    newChild = malloc(sizeof(struct Node));
    newChild->value = child_value;
    newChild->n_children = 0;
    newChild->children = NULL;

    /* Aggiungi il figlio */
    addChildToNode(parent, newChild);
}


int f(T t){
    /* Controllo se l'albero o la root sono nulli */
    if(t == NULL || t->root == NULL)
        return 0;

    /* Chiama la funzione ricorsiva sulla radice */
    return recursive_visit(t->root);
}



