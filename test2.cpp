#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define DIM 1024

// writes 2d^2 matrix entries to file for testing
int main(){
	ofstream outfile;
	outfile.open("test_data.txt");
	srand((unsigned)time(NULL));
	int range = 2 * (int) pow(DIM, 2);
	for (int i = 0; i < range; i++){
		outfile << (rand() % 3) - 1 << "\n";
	}
	outfile.close();
	return 0;
}

