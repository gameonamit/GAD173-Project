#include <iostream>
#include <time.h>

using namespace std;

int main() {

	srand(time(NULL));

	int sign;

	int xSpeed;
	int ySpeed;

	while (getchar()) {

		// generate a random sign: -1 or +1
		sign = 2 * (rand() % 2) - 1;


		// generate a random direction
		xSpeed = sign * (rand() % 100 + 500);
		ySpeed = -(rand() % 100 + 500);

		cout << "xSpeed: " << xSpeed << " ySpeed: " << ySpeed << endl;
	}

	return EXIT_SUCCESS;
}
