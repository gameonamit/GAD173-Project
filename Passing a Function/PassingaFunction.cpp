#include <iostream>

using namespace std;

// function prototypes
void func(void (*f)(int));

void print(int x);


int main()
{
	func(print);
}


// function definition
void print(int x) 
{
	cout << x << endl;
}

// function definition
void func(void (*f)(int)) 
{
	for (int ctr = 0; ctr < 5; ctr++) 
	{
		(*f)(ctr);
	}
}