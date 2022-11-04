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

void quickselect(int* A, int p, int q, int goal, int* count, int* result);
int ranpar(int* A,int p,int q, int* count){
	int r=(p-1);
	int randix = rand()%(q-p) + p;
	if (q-p > 3){
		printf("q-p is %i, creating sub\n", q-p);
		int subA[3], randixvec[3], subresult;
		for (int subAi = 0; subAi < 3; subAi++){
			randixvec[subAi] = rand()%(q-p)+p;
		        subA[subAi] = A[randixvec[subAi]];	
		}
		printf("Subarray is: ");
		print(subA, 0, 3);
		printf("With original indexes: "); print(randixvec, 0, 3);
		quickselect(subA, 0, 2, floor(3/2), count, &subresult);
		//randix = subresult;
		int sub2;
		for (int subAi =0; subAi <3; subAi++){
			if (subA[subresult] == A[randixvec[subAi]])
				sub2 = randixvec[subAi];
		}
		printf("subresult is: %i, element %i, original position is: %i\n", subresult, subA[subresult],sub2);
		randix = sub2;
	}
	printf("randix is: %i \n", randix);
	swap(A, randix, q);
	int pivot = A[q];
	printf("Pivot is %i\n", pivot);
	for (int e=p; e<q; e++){
		*count = *count+1;
		if (A[e] <= pivot){
			r++;
			swap(A, r, e);
		}
	}
	swap(A, r+1, q); // pivot in its position
	print(A, p, q+1); 
	return (r+1);
}

void quickselect(int* A, int p, int q, int goal, int* count, int* result){
	if (p<q){
		int r =ranpar(A, p, q, count);
		if (r > goal)
			quickselect(A, p, r-1, goal, count, result);
		else if (r < goal)
			quickselect(A, r+1, q, goal, count, result);
		else if (r ==goal){
			printf("%i-th element (%i) found\n", goal, A[r]);
			*result = r;
		}
	}
}

int main(int argc, char* argv[]){
	clock_t t;
    	t = clock();
	int IN = atoi(argv[1]);
	int A[IN],i;
	int result;
	srand ( time(NULL) ); // seed for random generator
	for(i=0;i<IN;i++)
     		A[i]=rand()%IN;
	printf("Original array: ");
	print(A, 0, IN);
	int goal = atoi(argv[2]);
	int count=0;	
	quickselect(A, 0, sizeof(A)/sizeof(A[0])-1, goal, &count, &result);
	printf("From main, %i-th element is %i\n", result, A[result]);
	t = clock() - t;
    	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	//printf("time taken: %f\n", time_taken);
	//FILE *fp;
	//const char *filename = "out/quickselect.txt";
	//char buffer[1024];
	//snprintf(buffer, sizeof(buffer), "out/quickselect%i.txt", goal);
        //fp = fopen (buffer, "a+"); // file pointer
        //fprintf(fp, "%i %i %i %f\n", IN, goal, count, time_taken);
        //fclose (fp);
	return 0;	
}
