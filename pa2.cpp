#include <iostream>
#include <time.h>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

using namespace std;

#define STR_BASE 8

int* conventional(int*, int*, int);
int* strassens(int*, int*, int);
pair<int*, int> matrixify(char* infile);

int main( int argc, char *argv[])
{
	if (argc != 4){
		printf("Incorrect number of parameters\n");
		return 0;
	}

	int dimension = atoi(argv[2]);
	inputfile = argv[3];
}

// convert file to matrix w d = 2^k
pair<int*, int> matrixfiy(char* inputfile){
	ifstream infile(inputfile);
	string str;
	while (getline(infile, str)){
		// fill in matrix
	}
}

int* conventional(int* a, int* b, n){
	int [n**2] value;

	for (i = 0; i < n**2; i += n){
		for (j = 0; j < n; j++){
			tmp = 0
			for (k = 0; k < n; k++ ){// second matrix iteration
				for (l = 0; l < n^2; l += n){
					tmp += a[i + j] * b[k + l];
				}
			}
			value [i + j] = tmp
		}
	}
}

int* strassens(int* a, int* b, n){

}