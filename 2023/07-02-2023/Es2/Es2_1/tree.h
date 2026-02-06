

/* ADT di prima classe - solo tipo opaco T visibile */
typedef struct tree *T;

/* Funzione wrapper richiesta dalla consegna */
int f(T t);

/* Funzioni di utilità per costruire l'albero */
T createTree(int value);
void addChild(T albero, int parent_value, int child_value);
