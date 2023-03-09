// This program computes the average of a set of non-negative integers (0 ~ 100). When input is -1, compute average and display. 
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip> 
using namespace std;

int check_int(string grade_str) { // if grade is float => return -1, integer => return 0
    if(grade_str.length() < 1)
        return -1;
    for(int i = 0; i < grade_str.length(); i++){ 
        if(i== 0 && grade_str[0] == 45 && grade_str.length() > 1) // test if it's -1 (ascii '-' => 45)
            continue;
        if(48 > grade_str[i] || 57 < grade_str[i]) //ascii '0' ~ '9' => 48 ~ 57
                return -1;
    }
    return 0;
}

int main() {
    while(cout << endl << "New program start..." << endl, 1) {
        cout << "You can only input integer between 0 to 100, if you want to end and compute average, please input -1" << endl;
        int number = 0; // The number of scores read.
        int sum = 0; // The summation of all the scores read.
        char grade_str[50]; // Holds each individual score as it is read from the keyboard.
        int grade; // change grade_str to integer
        float average; // Holds the computed average.
        int illegal = 0; // count if there is illegal input

        while(cout << "Please input your score (If there's not another score, please input -1) : ", cin >> grade_str, 1) { // Loop as long as the input was illegal or -1.
            if(check_int(grade_str) != 0){ //check if input is integer
                cout << "illegal input, ending the program..." << endl;
                illegal++;
                break;
            }
            grade = atoi(grade_str); // change grade_str to integer and store in grade
            if(grade < -1 || grade > 100){ // check if input is -1 ~ 100
                cout << "illegal input, ending the program..." << endl;
                illegal++;
                break;
            }
            if(grade == -1) // if grade is -1 => end the loop
                break;
            sum += grade; 
            number++; 
        }

        // check if grade has been input
        if(number == 0 && illegal == 0)
            cout << "You haven't entered any grade..." << endl;

        // When done reading scores, compute average and display.
        if(illegal == 0 && number != 0){// if there is illegal input or there's no grade to compute => don't computing average
            average = (float)sum/number;
            cout << "Your average score is : " << fixed << setprecision(2) << fixed << average << endl;
        }
        
        // ask if want to start new program
        char order; // if it's 'y' => start new program, 'n' or others => end
        cout << "Do you want to start new program? (y/n) : ";
        cin >> order;
        if(order == 'y')
            continue;
        break;
    }
    // When done, exit the program.
    return 0;
}