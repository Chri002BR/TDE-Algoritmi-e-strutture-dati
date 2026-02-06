#include <stdio.h>
#include <stdlib.h>

void confrontoCitta(int **mat, int N, int **compatibili){

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(mat[i][j]>0)
                compatibili[i][j]=1;
            else
                compatibili[i][j]=0;
        }
    }

}


void solve(int indice, int **compatibili, int N, int min_group, int *bestSol){
    
}

int minGroup(int **compatibili, int N, int min_group){
    // TODO: Implementare la funzione ricorsiva
    // Deve trovare il minimo numero di gruppi di città
    // dove le città sono mutualmente raggiungibili con al massimo 1 città intermedia

    int gruppi[N][N];
    int sizeGrous[N];
    for(int k = 0; k < N; k++) sizeGrous[k] = 0;

    int bestSol=N;
    solve(0, compatibili, N, N, &bestSol);


}

int main() {
    int N;

    printf("Inserisci il numero di città: ");
    scanf("%d", &N);

    // Allocazione matrice distanze N x N
    int **mat = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        mat[i] = (int *)malloc(N * sizeof(int));
    }

    // Lettura matrice distanze
    printf("Inserisci la matrice delle distanze (%d x %d):\n", N, N);
    printf("(0 indica assenza di connessione diretta)\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // Allocazione matrice compatibili N x N
    int **compatibili = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        compatibili[i] = (int *)malloc(N * sizeof(int));
    }

    // Chiamata funzione per determinare compatibilità
    confrontoCitta(mat, N, compatibili);

    // Stampa matrice compatibili (opzionale, per debug)
    printf("\nMatrice compatibili:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", compatibili[i][j]);
        }
        printf("\n");
    }

    // Chiamata funzione ricorsiva per trovare numero minimo di gruppi
    int risultato = minGroup(compatibili, N, N); // N è il valore iniziale massimo di gruppi

    printf("\nNumero minimo di gruppi: %d\n", risultato);

    // Deallocazione memoria
    for (int i = 0; i < N; i++) {
        free(mat[i]);
        free(compatibili[i]);
    }
    free(mat);
    free(compatibili);

    return 0;
}
