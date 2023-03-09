#include<iostream>
using namespace std;

class Cube {
    friend double operator/(const Cube&, const Cube&); // division
    private:
        double x, y, z;
    public:
        Cube(); // constructer without parameter
        Cube(double, double, double); // constructer with parameter
        double get_x() const; // get the value of x
        double get_y() const; // get the value of y
        double get_z() const; // get the value of z
        bool operator!=(const Cube&) const; // test if the volume isn't equal 
        
};

double operator/(const Cube&, const Cube&); // division


