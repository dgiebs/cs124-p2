#include <iostream>
#include <time.h>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <vector>

using namespace std;

int* conventional(int*, int*, int);
int* strassens(int*, int*, int);
int* add_sub(int*, int*, int, bool);

int main(){
	int a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	int b[16] = {3, 5, 2, 4, 7, 8, 4, 1, 9, 3, 5, 2, 8, 3, 5, 16};
	int *ao = a;
	int *bo = b;
	int n = 4;

	int* x = strassens(ao, bo, n);
	for (int i = 0; i < (int)pow(n, 2); i++){
		printf("%i ", x[i]);
		if (i % 4 == 3){
			printf("\n");
		}
	}
}


int* conventional(int* a, int* b, int n){

	int* value =  new int[(int)pow(n, 2)];

	for (int i = 0; i < pow(n, 2); i += n){
		for (int j = 0; j < n; j++){
			int tmp = 0;
			for (int k = 0; k < n; k++){// second matrix iteration
				tmp += a[i + k] * b[k*n + j];
			}
			value [i + j] = tmp;
		}
	}
	return value;
}

int* strassens(int* a, int* b, int n){

	int* value =  new int[(int)pow(n, 2)];

	if (n == 1){
		value[0] = a[0]*b[0];
		printf("%i %i %i \n", a[0], b[0], value[0]);
		return value;
	}
	else{
		int new_n = n/2;
		int* submatrices_a[4*(int)pow(new_n, 2)];
		int* submatrices_b[4*(int)pow(new_n, 2)];
		for (int i = 0; i < 4; i++){
			submatrices_a[i*(int)pow(new_n, 2)] = new int[(int)pow(new_n, 2)];
			submatrices_b[i*(int)pow(new_n, 2)] = new int[(int)pow(new_n, 2)];
		}

		for (int i = 0; i < 4; i++){
			for (int j = 0; j < new_n; j++){
				for (int k = 0; k < new_n; k++){
					printf("a: %i \n", a[n*j + k + i*new_n]);
					//printf("b: %i \n", b[n*j + k + i*new_n]);
					submatrices_a[i*(int)pow(new_n, 2)][j+k] = a[n*j + k + i*new_n];
					submatrices_b[i*(int)pow(new_n, 2)][j+k] = b[n*j + k + i*new_n];
				}
			}
		}
			printf("A \n");
			for (int i = 0; i < (int)pow(n, 2); i++){
				printf("%i ", submatrices_a[i*(int)pow(new_n, 2)][0]);
				if (i % 2 == 1){
					printf("\n");
				}
			}
			printf("B\n");
			for (int i = 0; i < (int)pow(n, 2); i++){
				printf("%i ", submatrices_a[i*(int)pow(new_n, 2)][0]);
				if (i % 2 == 1){
					printf("\n");
				}
			}
			printf("\n");

		int* p1 = strassens(submatrices_a[0], add_sub(submatrices_b[1], submatrices_b[3], new_n, false), new_n);
		int* p2 = strassens(add_sub(submatrices_a[0], submatrices_a[1], new_n, true), submatrices_b[3], new_n);
		int* p3 = strassens(add_sub(submatrices_a[2], submatrices_a[3], new_n, true), submatrices_b[0], new_n);
		int* p4 = strassens(submatrices_a[3], add_sub(submatrices_b[2], submatrices_b[0], new_n, false), new_n);
		int* p5 = strassens(add_sub(submatrices_a[0], submatrices_a[3], new_n, true), add_sub(submatrices_b[0], submatrices_b[3], new_n, true), new_n);
		int* p6 = strassens(add_sub(submatrices_a[1], submatrices_a[3], new_n, false), add_sub(submatrices_b[2], submatrices_b[3], new_n, true), new_n);
		int* p7 = strassens(add_sub(submatrices_a[0], submatrices_a[2], new_n, false), add_sub(submatrices_b[0], submatrices_b[1], new_n, true), new_n);

		int* quads[4];
		for (int i = 0; i < 4; i++){
			quads[i] = new int[(int)pow(new_n, 2)];
		}

		quads[0] = add_sub(add_sub(p5, p6, new_n, true), add_sub(p4, p2, new_n, false), new_n, true);
		quads[1] = add_sub(p1, p2, new_n, true);
		quads[2] = add_sub(p3, p4, new_n, true);
		quads[3] = add_sub(add_sub(p1, p7, new_n, false), add_sub(p5, p3, new_n, false), new_n, true);

		for (int i = 0; i < 4; i++){
			for (int j = 0; j < new_n; j++){
				for (int k = 0; k < new_n; k++){
					value[n*j + k + i*new_n] = quads[i][j+k];
				}
			}
		}
		return value;
	}
}

int* add_sub(int* a, int* b, int n, bool add){

	int* value =  new int[(int)pow(n, 2)];

	if (add == true){
		for (int i = 0; i < (int)pow(n, 2); i++){
			value[i] = a[i] + b[i];
		}
	}
	else{
		for (int i = 0; i < (int)pow(n, 2); i++){
			value[i] = a[i] - b[i];
		}
	}
	return value;
}