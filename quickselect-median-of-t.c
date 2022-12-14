#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void swap(int* A, int i, int j){
	int aux = A[i];
	A[i]=A[j];
	A[j]=aux;
}
void print(int* A, int p, int q){
	for (int idx=p; idx<q; idx++)
		printf("%i ", A[idx]); // as pointer
	printf("\n\n");
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int median(int* A, int sz){
	int med;
	qsort(A, sz, sizeof(int), cmpfunc);
	int idx = floor((sz)/2);
	med = A[idx];
	return med;
}
int ranpar(int* A,int p,int q, int* count, int M){
	int r=(p-1);
	int randix = rand()%(q-p+1)+p;
	if (q-p > M){
		int subA[M], randixvec[M], subresult;
		for (int subAi = 0; subAi <M; subAi++){
			randixvec[subAi]=rand()%(q-p+1)+p;
		        subA[subAi] = A[randixvec[subAi]];	
		}
		subresult = median(subA,M);
		int sub2;
		for (int subAi =0; subAi <M; subAi++){
			if (subresult == A[randixvec[subAi]])
				sub2 = randixvec[subAi];
		}
		randix = sub2;
	}
	swap(A, randix, q);
	int pivot = A[q];
	for (int e=p; e<q; e++){
		*count = *count+1;
		if (A[e] <= pivot){
			r++;
			swap(A, r, e);
		}
	}
	swap(A, r+1, q); // pivot in its position
	return (r+1);
}

void quickselect(int* A, int p, int q, int goal, int* count, int M){
	if (p<q){
		int r =ranpar(A, p, q, count, M);
		if (r > goal)
			quickselect(A, p, r-1, goal, count, M);
		else if (r < goal)
			quickselect(A, r+1, q, goal, count, M); 

		else if (r ==goal){
			printf("%i-th element (%i) found\n", goal, A[r]);
		}
	}
}

int main(int argc, char* argv[]){
	clock_t t;
    	t = clock();
	int IN = atoi(argv[1]);
	int M = 2*atoi(argv[3])+1;
	int A[IN],i;
	srand ( time(NULL) ); // seed for random generator
	for(i=0;i<IN;i++)
     		A[i]=rand()%IN;
	int goal = atoi(argv[2]);
	printf("This is median-of-%i. Looking for %i-th element\n", M, goal);
	int count=0;
	quickselect(A, 0, sizeof(A)/sizeof(A[0])-1, goal, &count, M);	
	t = clock() - t;
    	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("time taken: %f\n", time_taken);
	FILE *fp;
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "out/quickselect-median-of/quickselect-median-of-%i-%i.txt", M, goal);
        fp = fopen (buffer, "a+"); // file pointer
        fprintf(fp, "%i %i %i %f\n", IN, goal, count, time_taken);
        fclose (fp);
	return 0;	
}
