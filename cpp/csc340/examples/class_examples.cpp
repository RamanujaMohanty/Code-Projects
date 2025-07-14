#include <iostream>
using namespace std;

class Circle
{
public: // Access Specifier
    Circle();
    Circle(double);
    double get_area;
    double get_rad;
    void set_rad;

private:
    double radius;
};

int main()
{
    Circle circ_1;
}
