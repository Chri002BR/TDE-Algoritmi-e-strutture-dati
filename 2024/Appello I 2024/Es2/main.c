#include <stdio.h>
#include <stdlib.h>

/* --- DEFINIZIONE STRUTTURE DATI (ADT) --- */

typedef struct node *link;

struct node {
    int val;
    link l;
    link r;
};

struct binary_search_tree {
    link root;
};
typedef struct binary_search_tree *BST;

/* --- FUNZIONI DI SUPPORTO (GIA' PRONTE) --- */

link newNode(int val, link l, link r) {
    link x = malloc(sizeof(struct node));
    x->val = val;
    x->l = l;
    x->r = r;
    return x;
}

BST BSTinit() {
    BST b = malloc(sizeof(struct binary_search_tree));
    b->root = NULL;
    return b;
}

// Inserimento semplice BST
link insertR(link h, int val) {
    if (h == NULL) return newNode(val, NULL, NULL);
    if (val < h->val)
        h->l = insertR(h->l, val);
    else
        h->r = insertR(h->r, val);
    return h;
}

void BSTinsert(BST b, int val) {
    b->root = insertR(b->root, val);
}

// Stampa In-Order per verifica (dovrebbe stampare ordinato)
void visit(link h) {
    if (h == NULL) return;
    visit(h->l);
    printf("%d ", h->val);
    visit(h->r);
}

/* --- TO DO: IMPLEMENTA LE FUNZIONI QUI SOTTO --- */

// Suggerimento: ti serviranno funzioni ausiliarie (statiche)
// 1. Una per contare i nodi (int count(link h))
// 2. Una per calcolare l'altezza (int height(link h))
// 3. Una per inserire nel vettore i nodi di un livello specifico (void getLevel(link h, int level, link *arr, int *pos))

/* Scrivi qui le tue funzioni ausiliarie... */

int calcHeight(link h){

    if(h==NULL){
        return 0;
    }

    int countLx = calcHeight(h->l);
    int countRx = calcHeight(h->r);
    if(countLx > countRx)
        return countLx+1;
    return countRx+1;
}


void countNode(link h, int *result){

    if(h==NULL){
        return ;
    }

    countNode(h->l, result);
    countNode(h->r, result);
    (*result)++;
    return;

}


void insertNodeLevel(link node, int h, link *vett, int *index){

    if(h==0){
        vett[*index] = node;
        (*index)++;
        return;
    }

    insertNodeLevel(node->l, h-1, vett, index);
    insertNodeLevel(node->r, h-1, vett, index);
    return;
}



/* Funzione Principale richiesta */
link *BSTlevelizedNodes(BST b, int *n) {
    // 1. Conta i nodi totali
    // 2. Alloca il vettore di puntatori (link *arr = malloc...)
    // 3. Calcola l'altezza dell'albero
    // 4. Cicla per ogni livello i da 0 a altezza:
    //      Chiama la funzione che riempie il vettore con i nodi del livello i
    // 5. Aggiorna *n con il numero totale
    // 6. Ritorna il vettore

    /* SCRIVI QUI IL CODICE */
    
    int height;

    countNode(b->root, n);
    height=calcHeight(b->root);

    link *vett=malloc(sizeof(link)*(*n));
    int index=0;
    for(int i=0; i<height; i++){
        insertNodeLevel(b->root, i, vett, &index);
    }
    return vett; // Rimuovi e ritorna il vettore
}

/* --- MAIN DI TEST --- */

int main() {
    /* Creiamo questo albero:
            10
           /  \
          5    15
         / \   / \
        2   8 12  20
    
    Livello 0: 10
    Livello 1: 5, 15
    Livello 2: 2, 8, 12, 20
    
    Risultato atteso array: [10, 5, 15, 2, 8, 12, 20]
    */

    BST b = BSTinit();
    BSTinsert(b, 10);
    BSTinsert(b, 5);
    BSTinsert(b, 15);
    BSTinsert(b, 2);
    BSTinsert(b, 8);
    BSTinsert(b, 12);
    BSTinsert(b, 20);

    printf("Albero (Visita In-Order per controllo): ");
    visit(b->root);
    printf("\n");

    int n = 0;
    // Chiamata alla tua funzione
    link *vettore = BSTlevelizedNodes(b, &n);

    printf("\n--- Risultato Vettore Levelized ---\n");
    printf("Numero nodi trovati: %d\n", n);
    printf("Vettore: ");
    if (vettore != NULL) {
        for(int i = 0; i < n; i++) {
            // Stampiamo il valore puntato dal puntatore nel vettore
            printf("%d ", vettore[i]->val);
        }
        printf("\n");
        free(vettore); // Pulizia
    } else {
        printf("Errore: Vettore NULL\n");
    }
    
    // Verifica Output atteso
    printf("\nOutput Atteso:\n10 5 15 2 8 12 20\n");

    return 0;
}