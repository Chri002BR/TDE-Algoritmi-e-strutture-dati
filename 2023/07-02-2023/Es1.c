#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float calcolo(int **M, int i, int j, int r, int c);
void f(int **M, int r, int c);
void stampaMat(int **M, int r, int c);
void stampaMatFloat(float **M, int r, int c);

float calcolo(int **M, int i, int j, int r, int c){

	int sum=0;
	int count =0;
	float result =0;

	for(int k=-1; k<2; k++){

		if(j+k<0 || j+k >= r)	// Se j+k sforano i limiti "delle righe" saltare all'iterazione successiva
			continue;


		if((i-1>=0 && i-1<c)  )
			{sum+=M[i-1][j+k]; count++;}

		if((i>=0 && i<c) )
			{sum+=M[i][j+k]; count++;}

		if((i+1>=0 && i+1<c) )
			{sum+=M[i+1][j+k]; count++;}
	}

	result = (float)sum/count;
	return result;
}


void f(int **M, int r, int c){

	// Matrice allocata all'interno della funzione ???????
	float **Mat;
	Mat = (float **)malloc(r*sizeof(float*));
	for(int i=0; i<r; i++)
		Mat[i]=(float *)malloc(c*sizeof(float));




	for(int i=0; i<c; i++){
		for(int j=0; j<r; j++){
			Mat[i][j] = calcolo(M, i, j, r, c);
		}

	}

	stampaMatFloat(Mat, r, c);

}


void stampaMat(int **M, int r, int c){
	printf(" -------- Stampa matrice: -------- \n");
	for(int i=0; i<c; i++){
		for(int j=0; j<r; j++){
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
}

void stampaMatFloat(float **M, int r, int c){
	printf(" -------- Stampa matrice: -------- \n");
	for(int i=0; i<c; i++){
		for(int j=0; j<r; j++){
			printf("%.2f ", M[i][j]);
		}
		printf("\n");
	}
}



int main(){

	// da fare con malloc
	int valori[3][3] = {
    {1, 2, 1},
    {2, 0, 2},
    {1, 2, 1}
};
	int r=3;	// righe
	int c=3;	// colonne

	int **M = malloc(r*sizeof(int *));
	for(int i=0; i<r; i++) 
		M[i] = malloc(c*sizeof(int));

	for(int i=0; i<c; i++){
		for(int j=0; j<r; j++){
			M[i][j] = valori[i][j];
		}
	}


	stampaMat(M, r, c);
	
	f(M, r, c);
	
	

	return 0;
}




