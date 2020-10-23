#include <iostream>

class Rectangle {
    int width, height;
public:
    // method declarations
    void set_values(int, int);
    int area();
};


int main() {

    Rectangle rectangle;

    rectangle.set_values(2, 3);
    std::cout << "area = " << rectangle.area() << std::endl;

    return EXIT_SUCCESS;
}


// method definitions
void Rectangle::set_values(int x, int y) {
    width = x;
    height = y;
}

int Rectangle::area() {
    return width * height;
}