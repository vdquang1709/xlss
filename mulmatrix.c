#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void tran(double *A, double *B, int n) {
    int i,j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            B[j*n+i] = A[i*n+j];
        }
    }
}

void mmT(double *A, double *B, double *C, int n) 
{   
    int i, j, k;
    double *B2;
    B2 = (double*)malloc(sizeof(double)*n*n);
    tran(B,B2, n);
    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) {
            double dot  = 0;
            for (k = 0; k < n; k++) {
                dot += A[i*n+k]*B2[j*n+k];
            } 
            C[i*n+j ] = dot;
        }
    }
    free(B2);
}

void mmT_omp(double *A, double *B, double *C, int n, int threads) 
{   
    double *B2;
    B2 = (double*)malloc(sizeof(double)*n*n);
    tran(B,B2, n);
    #pragma omp parallel num_threads(threads)
    {
        int i, j, k;
        #pragma omp for
        for (i = 0; i < n; i++) { 
            for (j = 0; j < n; j++) {
                double dot  = 0;
                for (k = 0; k < n; k++) {
                    dot += A[i*n+k]*B2[j*n+k];
                } 
                C[i*n+j ] = dot;
            }
        }

    }
    free(B2);
}

int main(int argc, char *argv[]) {
    int i, n;
    double *A, *B, *C, dtime_seq, dtime_par;

	if (argc == 2)
		n=atoi(argv[1]);
	else
		n=2000;

	printf("Size: %dx%d \n",n,n);

    A = (double*)malloc(sizeof(double)*n*n);
    B = (double*)malloc(sizeof(double)*n*n);
    C = (double*)malloc(sizeof(double)*n*n);
    
    for(i=0; i<n*n; i++) {
        A[i] = 10; 
        B[i] = 0.25;
    }

    dtime_seq = omp_get_wtime();
    mmT(A,B,C, n);
    dtime_seq = omp_get_wtime() - dtime_seq;
    printf("Thoi gian thuc thi tuan tu: %f s\n\n", dtime_seq);
    
    dtime_par = omp_get_wtime();
    mmT_omp(A,B,C, n,2);
    dtime_par = omp_get_wtime() - dtime_par;
    printf("Thoi gian thuc thi song song voi %d threads: %f s\n", 2, dtime_par);
    printf("Speedup : %f\n", dtime_seq/dtime_par);
    printf("Efficiency: %f\n\n", (dtime_seq/dtime_par)/2);

    dtime_par = omp_get_wtime();
    mmT_omp(A,B,C, n,4);
    dtime_par = omp_get_wtime() - dtime_par;
    printf("Thoi gian thuc thi song song voi %d threads: %f s\n", 4, dtime_par);
    printf("Speedup : %f\n", dtime_seq/dtime_par);
    printf("Efficiency: %f\n\n", (dtime_seq/dtime_par)/4);

    dtime_par = omp_get_wtime();
    mmT_omp(A,B,C, n,6);
    dtime_par = omp_get_wtime() - dtime_par;
    printf("Thoi gian thuc thi song song voi %d threads: %f s\n", 6, dtime_par);
    printf("Speedup : %f\n", dtime_seq/dtime_par);
    printf("Efficiency: %f\n\n", (dtime_seq/dtime_par)/6);

    dtime_par = omp_get_wtime();
    mmT_omp(A,B,C, n,8);
    dtime_par = omp_get_wtime() - dtime_par;
    printf("Thoi gian thuc thi song song voi %d threads: %f s\n", 8, dtime_par);
    printf("Speedup : %f\n", dtime_seq/dtime_par);
    printf("Efficiency: %f\n\n", (dtime_seq/dtime_par)/8);

    dtime_par = omp_get_wtime();
    mmT_omp(A,B,C, n, 10);
    dtime_par = omp_get_wtime() - dtime_par;
    printf("Thoi gian thuc thi song song voi %d threads: %f s\n", 10, dtime_par);
    printf("Speedup : %f\n", dtime_seq/dtime_par);
    printf("Efficiency: %f\n\n", (dtime_seq/dtime_par)/10);

    return 0;

}
