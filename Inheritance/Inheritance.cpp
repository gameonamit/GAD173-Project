#include <iostream>
using namespace std;

class Polygon {
protected:
	int width, height;
public:
	void set_values(int a, int b)
	{
		width = a; height = b;
	}

	int GetWidth() 
	{
		return width;
	}

	int GetHeight()
	{
		return height;
	}
};

class Triangle : public Polygon {
public:
	int area() 
	{
		return width * height / 2;
	}
};

class Rectangle : public Polygon 
{
public:
	int area() 
	{
		return width * height;
	}
};

int main() 
{
	Rectangle rectangle;
	Triangle triangle;

	rectangle.set_values(8, 10);
	triangle.set_values(8, 10);

	cout << rectangle.area() << endl;
	cout << triangle.area() << endl;
}