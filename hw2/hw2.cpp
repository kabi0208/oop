//Credit card number validation
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

struct timespec computeTime (const struct timespec start, const struct timespec end) { // compute cost time (tv_nsec => nanosecond, tv_sec => second)
    struct timespec timming;
    timming.tv_sec = end.tv_sec - start.tv_sec;
    timming.tv_nsec = end.tv_nsec - start.tv_nsec;
    if (end.tv_nsec < start.tv_nsec) { // check if nanosecond of the end is lower than start. 
        timming.tv_sec -= 1;
        timming.tv_nsec += 1000000000;
    }
    return timming;
}

int startsWith (const string& cardNumber) { // return the first number if this is one of the four given card types, else return 7
    if (3 < int(cardNumber[0]) - 48 && int(cardNumber[0]) - 48 < 7) // check if start with 4, 5, or 6
        return int(cardNumber[0]) - 48;
    else if (int(cardNumber[0]) - 48 == 3 && int(cardNumber[1]) - 48 == 7) // check if start with 37
        return 3;
    else
        return 7;
    return 0;
}

int getDigit (int number) { // return this number if it is a single digit, otherwise, return the sum of the two digits (this function is for the even place number from right to left)
    if (number / 10 != 0) //check if there're two digits
        return (number % 10) + (number / 10);
    return number;
}

int sumofDoubleEvenPlace (const string& cardNumber) { // Get the result of all even place number after calculation
    int sum = 0;
    for (int i = cardNumber.length() - 2; i >= 0; i -= 2){
        sum += getDigit((int(cardNumber[i]) - 48) * 2);
    }
    return sum;
}

int sumOfOddPlace (const string& cardNumber) { // Return sum of odd-place digits in the card number
    int sum = 0;
    for (int i = cardNumber.length() - 1; i >= 0; i -= 2){
        sum += (int(cardNumber[i]) - 48);
    }
    return sum;
}

int check_int(string grade_str){ // if grade is float => return -1, integer => return 0
    if(grade_str.length() < 1)
        return -1;
    
    return 0;
}

bool iscard (const string& cardNumber) { //check if it's compute by 13-16 numbers
    for(int i = 0; i < cardNumber.length(); i++){ // check if this string is composed by only number
        if(48 > cardNumber[i] || 57 < cardNumber[i]) //ascii '0' ~ '9' => 48 ~ 57
            return false;
    }
    if (cardNumber.length() < 13 || cardNumber.length() > 16) // check if card number is between 13 ~ 16 digits
        return false;
    else 
        return true;
    return false;
}

bool isvalid (const string& cardNumber) { // Return true if the card number is valid
    if ((sumofDoubleEvenPlace(cardNumber) + sumOfOddPlace(cardNumber)) % 10 == 0) // check if is valid
        return true;
    else
        return false;
    return false;
}

string fakeOne (const string& brand) { // Return a valid credit card number for the given brand : "004", "005", "006", "0037"
    char card[32] = {0};
    card[0] = brand[2];
    if (brand == "0037")
        card[1] = brand[3];
    else  // if (brand == "004" || brand == "005" || brand == "006")
        card[1] = rand() % 10 + 48;
    int remainder = 0; // the remainder of sum % 10, sum = sumofDoubleEvenPlace(card) + sumOfOddPlace(card);
    do {
        int cardlength = 13 + rand() % 4; // let cardlength between 13 ~ 16
        for (int i = 2; i < cardlength; i++) { // compose card number of the third place to the last place with random
            card [i] = char(rand() % 10 + 48);
        }
        card [cardlength] = '\0'; // add '\0' at the last place
        
        remainder = (sumofDoubleEvenPlace(card) + sumOfOddPlace(card)) % 10;
        if (remainder != 0){ //if card number is valid, change the last place number of card to let it be valid
            if (int(card[cardlength - 1]) - 48 >= remainder ) 
                card[cardlength - 1] -= remainder;
            else
                card[cardlength - 1] += (10 - remainder);
        }
    }
    while(isvalid(card) != true); // check if is valid
    return card;
}

int main(int argc, char *argv[]) {
    struct timespec time_start, time_end, timming; // to compute the start and end time of compose a fake card number (clock_gettime)

    unsigned seed = (unsigned)time(NULL); // get sequentially
    srand(seed); // let sequentially be the seed of random

    if (argc <= 1) { // check if there's argv[1]
        cout << "there's no argv[1], which means name of data file haven't be given..." << endl;
        return 0;
    }

    string card_name[8] = {"American Express card #", "Visa card #", "MasterCard card #", "Discover card #", "Unknown card #"};

    // get data from txt and store in number
    ifstream input;
    char number[256] = {0};
    input.open(argv[1]);
    if (!input.is_open()) {
        cout << "Failed to open file." << endl;
    } 
    else {
        while (!input.eof()) {
            clock_gettime (CLOCK_MONOTONIC, &time_start); // start to measure time 
            input.getline (number, sizeof(number));
            string str_number = string(number);
            if (str_number.length() < 1) // check if there's no digit
                continue;
            else if (str_number == "004" || str_number == "005" || str_number == "006" || str_number == "0037"){ // if it is one of the four given brand
                string fakeNumber = fakeOne(number); // compose fake card number
                clock_gettime(CLOCK_MONOTONIC, &time_end); // end measuring time 
                timming = computeTime(time_start, time_end);
                cout << "Generated a valid " << card_name[number[2] - 48 - 3] << ": " << fakeNumber << "; ";
                cout << "Timing: " << (int)(timming.tv_sec * 1000000 + ((double)timming.tv_nsec / 1000.0))  << " microseconds" << endl;
                continue;
            }
            else if (iscard(str_number) == false){ // check if it's a credit card. 
                cout << "this isn't a credit card number (not 13 ~ 16 numbers.)" << endl;
                continue;
            }
            else if (isvalid(str_number) == true) {
                cout << str_number << ": a valid ";
            }
            else if (isvalid(str_number) != true) {
                cout << str_number << ": an invalid ";
            }
            else {
                cout << "I don't know what happened..." << endl;
                continue;
            }
            cout << card_name[startsWith(str_number) - 3] << endl;
        }
        input.close();
    }
    return 0;
}