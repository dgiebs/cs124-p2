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
int nextPower2(int);

pair<int*, int> matrixify(char* infile, int dimension);

int main( int argc, char *argv[])
{
	if (argc != 4){
		printf("Incorrect number of parameters\n");
		return 0;
	}

	int dimension = atoi(argv[2]);
	inputfile = argv[3];
}

// from http://www.geeksforgeeks.org/smallest-power-of-2-greater-than-or-equal-to-n/
int nextPower2(int n){
	int count = 0;
	// !(n&(n-1)) is T iff n is a power of 2 bc powers of 2 take the form '1 0^k' and 1 less than that is '1^(k-1)'
	if (n && !(n&(n-1))){
		return n;
	}

	while (n != 0){
		n >>= 1;
		count += 1;
	}
	return 1 << count;
}

// convert file to matrix w d = 2^k
pair<int*, int> matrixfiy(char* inputfile, int dimension){
	ifstream infile(inputfile);
	string str;
	int col_counter = 0;
	int row_counter = 0;

	int padded_dimension = nextPower2(dimension);

	int inmatrixA [padded_dimension][padded_dimension] = {0};
	int inmatrixB [padded_dimension][padded_dimension] = {0};
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