#include <iostream>
#include <time.h>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define STR_BASE 8

int* conventional(int*, int*, int);
int* strassens(int*, int*, int);
int* matrix_add_sub(int*, int*, int, bool);
int nextPower2(int);

tuple<int*, int*, int> matrixify(char* infile, int dimension);

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
tuple<int*, int*, int> matrixfiy(char* inputfile, int dimension){
	ifstream infile(inputfile);
	string str;
	int col_counter = 0;
	int row_counter = 0;

	// pad matrix w 0's up to next power of 2
	int padded_dimension = nextPower2(dimension);
	int inmatrixA [padded_dimension][padded_dimension] = {0};
	int inmatrixB [padded_dimension][padded_dimension] = {0};
	while (getline(infile, str)){
		// fill in matrices
		if (row_counter < dimension){
			inmatrixA[row_counter][col_counter] = stoi(str);
		} else {
			inmatrixB[row_counter - dimension][col_counter] = stoi(str);
		}

		row_counter++;
		col_counter++;
		// reset col to 0 when dimension reached
		if (col_counter >= dimension){
			col_counter = 0;
		}
	}

	return make_tuple(inmatrixA, inmatrixB, padded_dimension);
}

int* conventional(tuple<int*, int*, int> inpt){
	int n = get<2>(inpt);
	int *a = get<0>(inpt);
	int *b = get<1>(inpt);

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

int* strassens(int* a, int* b, n){

}