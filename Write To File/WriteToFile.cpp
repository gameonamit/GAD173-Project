// basic file operations
#include <iostream>
#include <fstream>

using namespace std;

int main() {

	int x, y;
	x = 99;
	y = 101;

	// declare
	ofstream myfile;

	// open
	myfile.open("example.txt");

	// write to file
	myfile << x << "\t" << y;

	// close
	myfile.close();

	return 0;
}