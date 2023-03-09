// This program computes the average of a set of non-negative integers (0 ~ 100). When input is -1, compute average and display. 
import java.io.*;
import java.util.Scanner;

class function{
    static int check_int(String grade_str) { // if grade is float => return -1, integer => return 0
        if(grade_str.length() < 1)
            return -1;
        for(int i = 0; i < grade_str.length(); i++) { 
            if(i == 0 && grade_str.charAt(0) == 45 && grade_str.length() > 1) // test if it's -1 (ascii '-' => 45)
                continue;
            if(48 > grade_str.charAt(i) || 57 < grade_str.charAt(i)) //ascii '0' ~ '9' => 48 ~ 57
                    return -1;
        }
        return 0;
    }
}

public class Avg{
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        while(true) {
            System.out.println("\nNew program start...");
            System.out.println("You can only input integer between 0 to 100, if you want to end and compute average, please input -1");
            int number = 0; // The number of scores read.
            int sum = 0; // The summation of all the scores read.
            String grade_str = new String(); // Holds each individual score as it is read from the keyboard.
            int grade; // change grade_str to integer
            float average; // Holds the computed average.
            int illegal = 0; // count if there is illegal input
            while(true) {
                System.out.print("Please input your score (If there's not another score, please input -1) : ");
                grade_str = input.nextLine();
                if(function.check_int(grade_str) != 0) { //check if input is integer
                    System.out.println("illegal input, ending the program...");
                    illegal++;
                    break;
                }
                grade = Integer.parseInt(grade_str); // change grade_str to integer and store in grade
                if(grade < -1 || grade > 100){ // check if input is -1 ~ 100
                    System.out.println("illegal input, ending the program...");
                    illegal++;
                    break;
                }
                if(grade == -1) // if grade is -1 => end the loop
                    break;
                sum += grade; 
                number ++;
            }

            // check if grade has been input
            if(number == 0 && illegal == 0)
                System.out.println("You haven't entered any grade...");
                
            // When done reading scores, compute average and display.
            if(illegal == 0 && number != 0) {// if there is illegal input or there's no grade to compute => don't computing average
                average = (float)sum/number;
                System.out.printf("Your average score is : %.2f%n", average);
            }
            
            // ask if want to start new program 
            System.out.print("Do you want to start new program? (y/n) : ");
            String order_str = input.nextLine(); // if it's 'y' => start new program, 'n' or others => end
            char order_char = order_str.charAt(0);
            if(order_char == 'y' && order_str.length() == 1)
                continue;
            break;
        }
    }
}       