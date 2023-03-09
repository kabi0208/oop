// change dollars and cents (x.y1y2 from argv[1]) to quarter, dime, nickel, and pennie then display.
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

class Coins {
    public:
        Coins(double money) {
            input = money; // put argv[1](double type) to input
            storeCoins(); // extract the dollar value and the cent value
            computeCoins();
        }
        void storeCoins() { // extract the dollars value and the cents value of the input and save them as integers.
            dollar = int(input);
            cent = int(lround((input - dollar) * 100));
        }
        void computeCoins() { // compute and save q, d, n, and p. 
            quarter = dollar * 4 + cent / 25;
            dime = (cent % 25) / 10;
            nickel = ((cent % 25) % 10) / 5;
            pennie = cent % 5;
        }
        inline const int getDollarValue() { return dollar;} // return the dollar value
        inline const int getQuarter() { return quarter;} // return q
        inline const int getDime() { return dime;} // return d
        inline const int getNickel() { return nickel;} // return n
        inline const int getPennie() { return pennie;} // return p
        
        inline const void output() { // A display function to display the equivalent values of q, d, n, and p as computed by step 3 above.
            cout << "$" << setprecision(2) << fixed << dollar + 0.01 * cent << " = ";
            cout << quarter << " quarters, " << dime << " dimes, " << nickel << " nickels, " << pennie << " pennies" << endl; 
            return;
        }

    private:
        double input; // x.y1y2 from argv[1]
        int dollar;
        int cent;
        int quarter; // 25 cents
        int dime; // 10 cents
        int nickel; // 5 cents
        int pennie; // 1 cents
};

bool isvaild (const string input) { // check if it's vaild (x.y1y2)
    if (input.length() < 4) // check if string length is enough (e.g. 0 => invaild)
        return false;
    for (int i = input.length() - 1; i >= 0; i--) { // check if this string is composed by only number and the third last digit is '.'
        if (i == input.length() - 3) { // if the third last digit isn't '.' => return false
            if (input[i] != '.')
                return false;
        }
        else if (48 > input[i] || 57 < input[i]) // ascii '0' ~ '9' => 48 ~ 57
            return false;
    }
    return true;
}

int main (int argc, char *argv[]) {
    if (argc < 2) { // check if there's argv[1] => if not than return 0
        cout << "You haven't input anything. (There's no argv[1])" << endl;
        return 0;
    }
    if (isvaild(argv[1]) == false) { // check if the input is vaild => if not than return 0
        cout << "your input is not valid.(not x.y1y2)" << endl;
        return 0;
    }
    Coins mycoin(atof(argv[1])); // compute argv[1](dollars and cents) to quarter, dime, nickel, and pennie then store
    mycoin.output(); // output as requirement
    
    return 0;
}
