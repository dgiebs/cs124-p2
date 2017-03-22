#include <iostream>
#include <time.h>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

using namespace std;

int* conventional(int*, int*);

int main( int argc, char *argv[])
{

}

int* conventional(int* a, int* b, n){
	int [pow(n, 2)] value;

	for (i = 0; i < pow(n, 2); i += n){
		for (j = 0; j < n; j++){
			tmp = 0
			for (k = 0; k < n; k++ ){// second matrix iteration
				tmp += a[i + k] * b[k*n + j];
			}
			value [i + j] = tmp
		}
	}
}

int* strassens