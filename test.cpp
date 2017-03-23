#include <iostream>
#include <time.h>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <vector>

using namespace std;

vector<vector<int>> conventional(vector<vector<int>>, vector<vector<int>>);
vector<vector<int>> strassens(vector<vector<int>>, vector<vector<int>>);
vector<vector<int>> add_sub(vector<vector<int>>, vector<vector<int>>, bool);

int main(){
	vector<vector<int>> a = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12}, {13, 14, 15, 16}};
	vector<vector<int>> b = {{3, 5, 2, 4},{7, 8, 4, 1}, {9, 3, 5, 2}, {8, 3, 5, 16}};

	int n = (int)a.size();

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

	vector<vector<int>> convent = conventional(a, b);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i ", convent[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	vector<vector<int>> strassen = strassens(a, b);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%i ", strassen[i][j]);
		}
		printf("\n");
	}
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