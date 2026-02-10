#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- DEFINIZIONE STRUTTURE DATI (ADT) --- */

typedef struct {
    char name[16];
    int val;
} Item;

typedef struct node *link;
struct node {
    Item item;
    link next;
};

struct slist_t {
    link head;
};
typedef struct slist_t *SLIST;

/* --- FUNZIONI DI SUPPORTO (GIA' PRONTE) --- */

// Crea un nuovo nodo
link newNode(char *name, int val, link next) {
    link x = malloc(sizeof(struct node));
    strcpy(x->item.name, name);
    x->item.val = val;
    x->next = next;
    return x;
}

// Inizializza una lista vuota
SLIST SLISTinit() {
    SLIST s = malloc(sizeof(struct slist_t));
    s->head = NULL;
    return s;
}

// Inserimento ordinato (per preparare i dati di test corretti)
void SLISTaddOrdered(SLIST s, char *name, int val) {
    link x = newNode(name, val, NULL);
    if (s->head == NULL || strcmp(name, s->head->item.name) < 0) {
        x->next = s->head;
        s->head = x;
    } else {
        link t = s->head;
        while (t->next != NULL && strcmp(t->next->item.name, name) <= 0) {
            t = t->next;
        }
        x->next = t->next;
        t->next = x;
    }
}

// Stampa la lista
void SLISTprint(SLIST s) {
    if (s == NULL) return;
    link t = s->head;
    while (t != NULL) {
        printf("(\"%s\", %d) -> ", t->item.name, t->item.val);
        t = t->next;
    }
    printf("NULL\n");
}

/* --- TO DO: IMPLEMENTA QUESTA FUNZIONE --- */

SLIST SLISTmerge(SLIST a, SLIST b) {
    // Suggerimento:
    // 1. Crea la lista risultato (SLIST result = SLISTinit())
    // 2. Usa tre puntatori: t1 (per a), t2 (per b), tail (per result)
    // 3. Cicla finché t1 o t2 non sono NULL
    // 4. Trova il nome "minimo" tra t1 e t2
    // 5. Somma i valori di tutti i nodi in t1 con quel nome
    // 6. Somma i valori di tutti i nodi in t2 con quel nome
    // 7. Aggiungi il nuovo nodo in coda a result
    
    /* --- SCRIVI QUI IL TUO CODICE --- */
    
    SLIST result = SLISTinit();
    link ta, tb, tail;
    ta=a->head;
    tb=b->head;
    tail=NULL;

    while(ta!=NULL || tb!=NULL){
        char *name;
        int sum=0;
        int cmp;
        if(ta==NULL){
            name = tb->item.name;
        }
        else if(tb==NULL){
            name = ta->item.name;
        }else{
            cmp = strcmp(ta->item.name, tb->item.name);
            if(cmp<=0)
                name=ta->item.name;
            else
                name=tb->item.name;
        }

        // fino quando a non è NULL e il nome è uguale a name
        while(ta != 0 && strcmp(ta->item.name, name) == 0){
            sum += ta->item.val;
            ta=ta->next;
        }

        while(tb != 0 && strcmp(tb->item.name, name) == 0){
            sum += tb->item.val;
            tb=tb->next;
        }


        link nuovoNodo = newNode(name, sum, NULL);

        if(tail==NULL){
            result->head=nuovoNodo;
            tail = result->head;
        }else{
            tail->next=nuovoNodo;
            tail = tail->next;
        }
    }
    return result; // Rimuovi questo e ritorna la lista corretta
}

/* --- MAIN DI TEST --- */

int main() {
    // 1. Creazione Lista A
    // Dati: ("roma", 7), ("torino", 4), ("zagabria", 5)
    // Nota: La funzione addOrdered li mette già in ordine alfabetico se li inserisci a caso,
    // ma qui li inseriamo per simulare l'input.
    SLIST a = SLISTinit();
    SLISTaddOrdered(a, "roma", 7);
    SLISTaddOrdered(a, "torino", 4);
    SLISTaddOrdered(a, "zagabria", 5);

    printf("Lista A (Input):\n");
    SLISTprint(a);

    // 2. Creazione Lista B
    // Dati: ("roma", 3), ("torino", 3), ("torino", 2), ("venezia", 10)
    SLIST b = SLISTinit();
    SLISTaddOrdered(b, "roma", 3);
    SLISTaddOrdered(b, "torino", 3);
    SLISTaddOrdered(b, "torino", 2);
    SLISTaddOrdered(b, "venezia", 10);

    printf("\nLista B (Input):\n");
    SLISTprint(b);

    // 3. Esecuzione Merge
    printf("\n--- Esecuzione Merge ---\n");
    SLIST res = SLISTmerge(a, b);

    // 4. Verifica Risultato
    printf("\nRisultato Ottenuto:\n");
    SLISTprint(res);

    printf("\nRisultato Atteso:\n");
    printf("(\"roma\", 10) -> (\"torino\", 9) -> (\"venezia\", 10) -> (\"zagabria\", 5) -> NULL\n");

    return 0;
}