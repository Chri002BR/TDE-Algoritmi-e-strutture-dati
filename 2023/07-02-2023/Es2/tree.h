typedef struct node{
    int info;               // valore del nodo
    int num_children;       // Numero figli
    struct node **children; // vettore con i puntatori ai figli
}Node;