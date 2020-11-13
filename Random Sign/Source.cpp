#include <iostream>
#include <time.h>

using namespace std;

int main() {

	srand(time(NULL));

	int sign;

	while (getchar()) {
		sign = 2 * (rand() % 2) - 1;
		cout << "sign = " << sign << endl;
	}

	return EXIT_SUCCESS;
}
