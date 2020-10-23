#include "Triangle.h"

// method definitions
void Triangle::set_values(int x, int y) {
    width = x;
    height = y;
}

int Triangle::area() {
    return width * height;
}