#include <iostream>
#include <time.h>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <vector>
#include <fstream>

using namespace std;

#define STR_BASE 90

vector<vector<int>>* conventional(vector<vector<int>>*, vector<vector<int>>*);
vector<vector<int>>* strassens(vector<vector<int>>*, vector<vector<int>>*);
vector<vector<int>>* add_sub(vector<vector<int>>*, vector<vector<int>>*, bool);
tuple<vector<vector<int>>*, vector<vector<int>>*> matrixify(char*, int);
int nextPower2(int);

int main(int argc, char *argv[])
{
	if (argc != 4){
		printf("Incorrect number of parameters\n");
		return 0;
	}

	int n = atoi(argv[2]);
	char* inpt = argv[3];

	tuple<vector<vector<int>>*, vector<vector<int>>*> padded = matrixify(inpt, n);
	vector<vector<int>>* a = get<0>(padded);
	vector<vector<int>>* b = get<1>(padded);
	vector<vector<int>> &ar = *a;
	vector<vector<int>> &br = *b;

    clock_t begin = clock();
    vector<vector<int>>* strassen = strassens(a, b);
	clock_t end = clock();
	double timing = (double)(end - begin) / CLOCKS_PER_SEC;

	for (int i = 0; i < n; i++){
		printf("%i\n", strassen->at(i)[i]);
	}

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
tuple<vector<vector<int>>*, vector<vector<int>>*> matrixify(char* inpt, int n){
	ifstream infile(inpt);
	string str;
	int i = 0;
	int j = 0;

	// pad matrix w 0's up to next power of 2
	int new_n = nextPower2(n);
	vector<vector<int>>* a = new vector<vector<int>> (new_n, vector<int> (new_n, 0));
	vector<vector<int>>* b = new vector<vector<int>> (new_n, vector<int> (new_n, 0));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			infile >> str;
			a->at(i)[j] = atoi(str.c_str());
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			infile >> str;
			b->at(i)[j] = atoi(str.c_str());
		}
	}

	return make_tuple(a, b);
}

vector<vector<int>>* conventional(vector<vector<int>>* a, vector<vector<int>>* b){

	int n = (int)a->size();
	vector<vector<int>>* result = new vector<vector<int>> (n, vector<int> (n));

	for (int i = 0; i < n; i ++){
		for (int j = 0; j < n; j++){
			result->at(i)[j] = 0;
			for (int k = 0; k < n; k++){
				result->at(i)[j] += a->at(i)[k]*b->at(k)[j];
			}
		}
	}
	return result;
}

vector<vector<int>>* strassens(vector<vector<int>>* a, vector<vector<int>>* b){

	int n = (int)a->size();
	vector<vector<int>>* result = new vector<vector<int>> (n, vector<int> (n));

	if (n <= STR_BASE){
		result = conventional(a, b);
		return result;
	}
	else{

		// arrange submatrices
		int new_n = n/2;
		vector<vector<vector<int>>>* sub_a = new vector<vector<vector<int>>> (4, vector<vector<int>> (new_n, vector<int> (new_n)));
		vector<vector<vector<int>>>* sub_b = new vector<vector<vector<int>>> (4, vector<vector<int>> (new_n, vector<int> (new_n)));

		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++){
				for (int k = 0; k < new_n; k++){
					for (int l = 0; l < new_n; l++){
						sub_a->at(i+2*j)[k][l] = a->at(j*new_n+k)[i*new_n+l];
						sub_b->at(i+2*j)[k][l] = b->at(j*new_n+k)[i*new_n+l];
					}
				}
			}
		}

		// calculate componenets of strassens
		vector<vector<int>>* p1 = strassens(&sub_a->at(0), add_sub(&sub_b->at(1), &sub_b->at(3), false));
		vector<vector<int>>* p2 = strassens(add_sub(&sub_a->at(0), &sub_a->at(1), true), &sub_b->at(3));
		vector<vector<int>>* p3 = strassens(add_sub(&sub_a->at(2), &sub_a->at(3), true), &sub_b->at(0));
		vector<vector<int>>* p4 = strassens(&sub_a->at(3), add_sub(&sub_b->at(2), &sub_b->at(0), false));
		vector<vector<int>>* p5 = strassens(add_sub(&sub_a->at(0), &sub_a->at(3), true), add_sub(&sub_b->at(0), &sub_b->at(3), true));
		vector<vector<int>>* p6 = strassens(add_sub(&sub_a->at(1), &sub_a->at(3), false), add_sub(&sub_b->at(2), &sub_b->at(3), true));
		vector<vector<int>>* p7 = strassens(add_sub(&sub_a->at(0), &sub_a->at(2), false), add_sub(&sub_b->at(0), &sub_b->at(1), true));

		vector<vector<vector<int>>>* quads = new vector<vector<vector<int>>> (4, vector<vector<int>> (new_n, vector<int> (new_n)));
		vector<vector<int>>* quad0 = add_sub(add_sub(p5, p6, true), add_sub(p4, p2, false), true);
		vector<vector<int>>* quad1 = add_sub(p1, p2, true);
		vector<vector<int>>* quad2 = add_sub(p3, p4, true);
		vector<vector<int>>* quad3 = add_sub(add_sub(p1, p7, false), add_sub(p5, p3, false), true);

		//rerrange 4 matrices into the result, return value
		quads->at(0) = *quad0;
		quads->at(1) = *quad1;
		quads->at(2) = *quad2;
		quads->at(3) = *quad3;

		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++){
				for (int k = 0; k < new_n; k++){
					for (int l = 0; l < new_n; l++){
						result->at(j*new_n+k)[i*new_n+l] = quads->at(i+2*j)[k][l];
					}
				}
			}
		}
		delete quads;
		delete sub_a;
		delete sub_b;

		return result;
	}
}

//add or subtract matrices
vector<vector<int>>* add_sub(vector<vector<int>>* a, vector<vector<int>>* b, bool add){

	int n = (int)a->size();
	vector<vector<int>>* result = new vector<vector<int>> (n, vector<int> (n));

	if (add == true){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				result->at(i)[j] = a->at(i)[j] + b->at(i)[j];
			}
		}
	}
	else{
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				result->at(i)[j] = a->at(i)[j] - b->at(i)[j];
			}
		}
	}
	return result;
}