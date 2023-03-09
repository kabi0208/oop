#include "Cube.h"
#include <iostream>

using namespace std;

int main() {
    Cube a(1.0, 1.0, 1.0);
    Cube b(1.0, 1.0, 1.0);

    if(a != b)
        cout << "they are not same." << endl;
    else
        cout << "they are same. " << endl;
    
    cout << "division:" << a/b << endl;

    Cube c(2.0, 2.0, 2.0);
    Cube d(1.0, 2.0, 1.0);
    Cube e;

    if(c != d)
        cout << "they are not same." << endl;
    else
        cout << "they are same. " << endl;
    
    cout << "division:" << c/d << endl;

    if(c != e)
        cout << "they are not same." << endl;
    else
        cout << "they are same. " << endl;

    cout << "division:" << c/e << endl;
    
    return 0;
}