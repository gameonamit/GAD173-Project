#include <iostream>
#include "Rectangle.h"
#include "Triangle.h"

using namespace std;

int main() {
    // Rectangle
    Rectangle rectangle;

    rectangle.set_values(2, 3);
    std::cout << "area = " << rectangle.area() << std::endl;


    // Triangle
    Triangle triangle;

    triangle.set_values(2, 3);
    std::cout << "area = " << triangle.area() << std::endl;

    return EXIT_SUCCESS;
}