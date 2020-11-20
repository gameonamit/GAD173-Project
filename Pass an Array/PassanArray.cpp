#include<iostream>
using namespace std;

const int N = 5;

// pass by reference
void my_function(int* x, int P) {

	for (int i = 0; i < P; ++i) {
		*(x + i) = i;
	}
}

int main() {

	int x[N] = { 10, 20, 30, 40, 50 };

	cout << "before method call\n";

	for (int i = 0; i < N; ++i) {
		cout << *(x + i) << endl;
	}

	my_function(x, N);

	cout << "after method call\n";

	for (int i = 0; i < N; ++i) {
		cout << *(x + i) << endl;
	}
}