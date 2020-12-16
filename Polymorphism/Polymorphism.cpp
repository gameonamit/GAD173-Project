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

	virtual int area() 
	{
		return 0;
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

	//Pointers
	Polygon* p;

	p = &rectangle;
	p-> set_values(8, 10);
	cout << p->area() << endl;

	p = &triangle;
	p->set_values(8, 10);
	cout << p->area() << endl;
	return 0;
}