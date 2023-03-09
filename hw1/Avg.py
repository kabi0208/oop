# This program computes the average of a set of non-negative integers (0 ~ 100). When input is -1, compute average and display.
def check_int(grade_str):# if grade is float => return -1, integer => return 0
    if len(grade_str) < 1: 
        return -1
    for i in range (0,len(grade_str)): 
        if i == 0 and ord(grade_str[0]) == 45 and len(grade_str) > 1: # test if it's -1 (ascii '-' => 45)
                continue
        if 48 > ord(grade_str[i]) or 57 < ord(grade_str[i]): #ascii '0' ~ '9' => 48 ~ 57
                return -1
    return 0

while True:
    print("\nNew program start...")
    print("You can only input integer between 0 to 100, if you want to end and compute average, please input -1")
    number = 0 # The number of scores read.
    total = 0 # The summation of all the scores read.
    average = 0.0 # Holds the computed average.
    illegal = 0 # count if there is illegal input
    while True:
        print("Please input your score (If there's not another score, please input -1) : ", end = '') # Loop as long as the input was illegal or -1.
        grade_str = input() 
        if check_int(grade_str) != 0: #check if input is integer
            print("illegal input, ending the program...")
            illegal += 1
            break
        grade = int(grade_str) # change grade_str to integer and store in grade
        if grade < -1 or grade > 100: # check if input is -1 ~ 100
            print("illegal input, ending the program...")
            illegal += 1
            break
        if grade == -1: #if grade is -1 => end the loop
            break
        total += grade
        number += 1

    #check if grade has been input
    if number == 0 and illegal == 0:
        print("You haven't entered any grade...")
        
    # When done reading scores, compute average and display.
    if illegal == 0 and number != 0: # if there is illegal input or there's no grade to compute => don't computing average
        average = float(total/number)
        # wrong : average = round(average,2) # it would output %.1f if there's only one input
        print("Your average score is :", '%.2f'%average)
        
    # ask if want to start new program
    print("Do you want to start new program? (y/n) : ", end = '')
    order = input() # if it's 'y' => start new program, 'n' or others => end
    if order == 'y':
        continue
    break
        