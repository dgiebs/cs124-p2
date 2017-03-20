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
	int [n**2] value;

	for (i = 0; i < n^2; i += n){
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