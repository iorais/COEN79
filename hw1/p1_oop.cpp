#include <iostream>
#include <math.h>

class circle {
    private:
        float radius;
    
    public:
        circle(float radius) { this->radius = radius; }
        float getRadius() {return radius; }
        float area() { return 3.14 * pow(radius, 2); }
};

int main() {
    circle myCircle(1);

    std::cout   << myCircle.getRadius() << std::endl
                << myCircle.area()      << std::endl;
    
    return 0;
}