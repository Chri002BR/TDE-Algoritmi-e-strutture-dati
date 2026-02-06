#ifndef TREE_H
#define TREE_H

/* 
 * Definizione del tipo T come ADT di prima classe.
 * I dettagli implementativi (struct tree e struct node) sono nascosti nel modulo .c.
 */
typedef struct tree *T;

/* 
 * Funzione wrapper che conta la lunghezza del cammino più lungo 
 * contenente solo valori positivi o nulli.
 */
int f(T t);

#endif /* TREE_H */
