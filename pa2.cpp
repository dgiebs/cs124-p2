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

#define STR_BASE 8

vector<vector<int>> conventional(vector<vector<int>>, vector<vector<int>>);
vector<vector<int>> strassens(vector<vector<int>>, vector<vector<int>>);
vector<vector<int>> add_sub(vector<vector<int>>, vector<vector<int>>, bool);
tuple<vector<vector<int>>, vector<vector<int>>> matrixify(char*, int);
int nextPower2(int);

int main( int argc, char *argv[])
{
	if (argc != 4){
		printf("Incorrect number of parameters\n");
		return 0;
	}

	int n = atoi(argv[2]);
	char* inpt = argv[3];

	tuple<vector<vector<int>>, vector<vector<int>>> padded = matrixify(inpt, n);
	vector<vector<int>> a = get<0>(padded);
	vector<vector<int>> b = get<1>(padded);

	//assumed that there are two 2d vectors a and b from here on out

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i ", b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
    
    clock_t begin = clock();
    vector<vector<int>> convent = conventional(a, b);
	clock_t end = clock();
	double timing = (double)(end - begin) / CLOCKS_PER_SEC;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i ", convent[i][j]);
		}
		printf("\n");
	}
	printf("timing: %f \n", timing);

    begin = clock();
    vector<vector<int>> strassen = strassens(a, b);
	end = clock();
	timing = (double)(end - begin) / CLOCKS_PER_SEC;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i ", strassen[i][j]);
		}
		printf("\n");
	}
	printf("timing: %f \n", timing);

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
tuple<vector<vector<int>>, vector<vector<int>>> matrixify(char* inpt, int n){
	ifstream infile(inpt);
	string str;
	int i = 0;
	int j = 0;

	// pad matrix w 0's up to next power of 2
	int new_n = nextPower2(n);
	vector<vector<int>> a (new_n, vector<int> (new_n, 0));
	vector<vector<int>> b (new_n, vector<int> (new_n, 0));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			infile >> str;
			a[i][j] = stoi(str);
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			infile >> str;
			b[i][j] = stoi(str);
		}
	}

	return make_tuple(a, b);
}

vector<vector<int>> conventional(vector<vector<int>> a, vector<vector<int>> b){
	
	int n = (int)a.size();
	vector<vector<int>> result (n, vector<int> (n, 0));

	for (int i = 0; i < n; i ++){
		for (int j = 0; j < n; j++){
			for (int k = 0; k < n; k++){
				result[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	return result;
}

vector<vector<int>> strassens(vector<vector<int>> a, vector<vector<int>> b){
	
	int n = (int)a.size();
	vector<vector<int>> result (n, vector<int> (n, 0));

	if (n == 1){
		result[0][0] = a[0][0]*b[0][0];
		return result;
	}
	else{
		int new_n = n/2;
		vector<vector<vector<int>>> sub_a (4, vector<vector<int>> (new_n, vector<int> (new_n, 0)));
		vector<vector<vector<int>>> sub_b (4, vector<vector<int>> (new_n, vector<int> (new_n, 0)));

		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++){
				for (int k = 0; k < new_n; k++){
					for (int l = 0; l < new_n; l++){
						sub_a[i+2*j][k][l] = a[j*new_n+k][i*new_n+l];
						sub_b[i+2*j][k][l] = b[j*new_n+k][i*new_n+l];
					}
				}
			}
		}

		vector<vector<int>> p1 = strassens(sub_a[0], add_sub(sub_b[1], sub_b[3], false));
		vector<vector<int>> p2 = strassens(add_sub(sub_a[0], sub_a[1], true), sub_b[3]);
		vector<vector<int>> p3 = strassens(add_sub(sub_a[2], sub_a[3], true), sub_b[0]);
		vector<vector<int>> p4 = strassens(sub_a[3], add_sub(sub_b[2], sub_b[0], false));
		vector<vector<int>> p5 = strassens(add_sub(sub_a[0], sub_a[3], true), add_sub(sub_b[0], sub_b[3], true));
		vector<vector<int>> p6 = strassens(add_sub(sub_a[1], sub_a[3], false), add_sub(sub_b[2], sub_b[3], true));
		vector<vector<int>> p7 = strassens(add_sub(sub_a[0], sub_a[2], false), add_sub(sub_b[0], sub_b[1], true));

		vector<vector<vector<int>>> quads (4, vector<vector<int>> (new_n, vector<int> (new_n, 0)));

		quads[0] = add_sub(add_sub(p5, p6, true), add_sub(p4, p2, false), true);
		quads[1] = add_sub(p1, p2, true);
		quads[2] = add_sub(p3, p4, true);
		quads[3] = add_sub(add_sub(p1, p7, false), add_sub(p5, p3, false), true);

		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++){
				for (int k = 0; k < new_n; k++){
					for (int l = 0; l < new_n; l++){
						result[j*new_n+k][i*new_n+l] = quads[i+2*j][k][l];
					}
				}
			}
		}

		return result;
	}
}

vector<vector<int>> add_sub(vector<vector<int>> a, vector<vector<int>> b, bool add){
	
	int n = (int)a.size();
	vector<vector<int>> result (n, vector<int> (n, 0));

	if (add == true){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				result[i][j] = a[i][j] + b[i][j];
			}
		}
	}
	else{
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				result[i][j] = a[i][j] - b[i][j];
			}
		}
	}
	return result;
}