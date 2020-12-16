// overloaded functions
#include <iostream>
using namespace std;

// a function that accept two ints and returns an int
int sum(int a, int b)
{
	return a + b;
}

float sum(float a, float b)
{
	return a + b;
}

// a function that accepts two doubles and returns a double
double sum(double a, double b)
{
	return a + b;
}


//template <class T>
//T add(T x, T y)
//{
//	return x + y;
//}

template <class T, class U>
T add(T x, U y)
{
	return x + y;
}


int main()
{
	// invoke overloaded functions
	cout << sum(10, 20) << endl;
	cout << sum(3.142f, 2.71f) << endl;
	cout << sum(1.0, 1.5) << endl;

	// invoke template function explicitly with different parameter types
	cout << add<int>(1, 2) << endl;
	cout << add<float>(2.1f, 3.1f) << endl;
	cout << add<double>(1.5, 2.5) << endl;

	// invoke template function implicitly with different parameter types
	cout << add(1, 2) << endl;
	cout << add(4.5f, 5.5f) << endl;
	cout << add(1.5, 2.5) << endl;

	cin.get();
	return 0;
}