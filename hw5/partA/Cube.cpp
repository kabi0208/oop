#include "Cube.h"
#include <iostream>

using namespace std;

Cube::Cube(){ // constructer without parameter
    x = 0, y = 0, z = 0;
}

Cube::Cube(double xi, double yi, double zi){ // constructer with parameter
    x = xi, y = yi, z = zi;
}

double Cube::get_x() const{ return x; } // get the value of x
double Cube::get_y() const{ return y; } // get the value of y
double Cube::get_z() const{ return z; } // get the value of z

bool Cube::operator!=(const Cube &goal) const{ // test if the volume isn't equal 
    if((-0.00001 < x * y * z - goal.x * goal.y * goal.z) && (0.00001 > x * y * z - goal.x * goal.y * goal.z))
        return false;
    return true;
} 

double operator/(const Cube &a, const Cube &b){ // division
    if((b.x + b.y + b.z) == 0)
        cout << "(warning!!the denominator is 0.) ";
    return (a.x + a.y + a.z) / (b.x + b.y + b.z);
}