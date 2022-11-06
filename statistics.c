#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void statistics(float data[], int sz, float *mean, float *sd){
	float sum = 0.0, SD = 0.0;
    	int i;
    	for (i = 0; i < sz; ++i) {
        	sum += data[i];
    	}
    	*mean = sum / sz;
    	for (i = 0; i < sz; ++i) {
        	SD += pow(data[i] - *mean, 2);
    	}
	*sd = sqrt(SD/sz); 
}

int readmatrix(size_t rows, size_t cols, float (*a)[cols], const char* filename)
{

    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL)
        return 0;

    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
            fscanf(pf, "%f", a[i] + j);
    }


    fclose (pf);
    return 1;
}

int main(int argc, char* argv[]){
	int cols = atoi(argv[3]); // num of rows
	int rows = atoi(argv[2]);
	int j = atoi(argv[4]);
	char* filename = argv[1];
	float matrix[rows][cols];
	int alpha = j/20000;
    	readmatrix(rows, cols, matrix, filename);
	float C[rows];
	float T[rows];
	if (cols == 4){
	for (int r=0; r<rows; r++){
		C[r]=matrix[r][2]; // comparisons
		T[r] = matrix[r][3]; //time
	}
	}
	if (cols ==2){
		for (int r=0; r<rows; r++){
                 C[r]=matrix[r][0]; // comparisons
                 T[r] = matrix[r][1]; //time
         }
	}
	float meanC, sdC, meanT, sdT;
	statistics(C, rows, &meanC, &sdC);
	statistics(T, rows, &meanT, &sdT);

	FILE *fp;
	const char *file2 = "out/STATS.txt";
	fp = fopen(file2, "a+");
	if (cols == 4){
	fprintf(fp, "%i %f %f %f %f\n", alpha, meanC, sdC, meanT, sdT);}
	if (cols==2){
		fprintf(fp, "%i %f %f %f %f\n", j, meanC, sdC, meanT, sdT);}
	fclose(fp);	
	return 0;
}
