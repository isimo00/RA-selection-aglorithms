#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void print(int* A, int n){
	for (int e=0; e<n; e++)
		printf("%i ", A[e]);
	printf("\n \n");
}

void swap(int* A, int i, int j){
	int aux = A[i];
	A[i]=A[j];
	A[j]=aux;
}

int ranpar(int*A, int p, int q, int* count){
	int pivot = A[q];
	int i = (p-1);
	for (int j=p; j<q; j++){
		*count = *count+1;
		if (A[j] <= pivot){
			i++;
			swap(A, i, j);
		}
	}
	swap(A, i+1, q);
	return (i+1);
}

void quicksort(int* A, int p, int q, int* count){
	if (p<q){
		int r= ranpar(A, p, q, count);
		quicksort(A, p, r-1, count);
		quicksort(A, r+1, q, count);
	}
}

int main(int argc, char* argv[]){
	clock_t t;
    	t = clock();
	int IN = atoi(argv[1]); // char to int
	int S[IN],i;
	srand ( time(NULL) ); // seed for random generator
	for(i=0;i<IN;i++)
     		S[i]=rand()%IN;
	int n = ceil(pow(IN, 3./4));

	int R[n];
	int ranidx;	
	for (int i=0; i<n; i++){
		ranidx = rand()%IN;
		R[i]=S[ranidx];
	}
	int count=0;

	quicksort(R,0, n, &count);

	int id = floor(0.5*n-sqrt(IN));
	int iu = floor(0.5*n+sqrt(IN));
	int d= R[id];
	int u=R[iu];
	int *C= malloc(4*n*sizeof(int));
	int j =0;
	int ld=0;
	int lu=0;
	bool error = false;
	for (int i=0; i<IN; i++){
		if (S[i] >= d && S[i] <= u){
			C[j]=S[i];
			j++;
			if (j > 4*n*sizeof(int)){
				error =true;
				printf("Algorithm failed, E3. Aborting. \n");
				abort();	
			}
		}
		else if (S[i] < d)
		        ld++;
		else if (S[i] > u)
			lu++;

		if (ld >= ceil(IN/2) || lu>=ceil(IN/2))
			error = true;	

	}

	quicksort(C, 0, j-1, &count); 
	int fin = floor(IN/2)-ld+1;
	printf("Total elements: %i, Median: %i\nError: %d\n", IN, C[fin], error);
	t = clock() - t;
    	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	FILE *fp;
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "out/floydrivest/floydrivest%i.txt", IN);
	fp = fopen(buffer, "a+");
	fprintf(fp, "%i %d\n", count, error); 
	//fprintf(fp, "%i %f\n", count, time_taken);
       	fclose(fp);	
	printf("time taken: %f\n", time_taken);
	return C[fin];
}
