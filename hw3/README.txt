1. 姓名：陳品希

2. 學號：409410024

3. e-mail：ivychen20020208@gmail.com

4. 完成的作業項目
    請撰寫一個用來換算美金銅板的程式
    I.使用OOP物件導向的寫法來寫 (此處請參考作業投影片中的 Minimum class requirements )
        1. At least one constructor that takes a double representing a dollars and cents value.
        2. A member function to extract the dollars value and the cents value of the input and save them as integers. This function should be called from the constructor.
        3. A member function to compute and save q, d, n, and p. This function should be called from the constructor.
            Notice that this function must be computed q, d, n, and pin that order, 
            and that the maximum possible value must be computed for each from what currently remains after the predecessor is computed (q has no predecessor).
        4. Constant members that do the following (make all of these implicitly inlined).
            a. Return the dollar value.
            b. Return q, d, n, and p as separate members.
            c. A display function to display the equivalent values of q, d, n, and p as computed by step 3 above. Notice that this function displays all values.

    II.將輸入的美金換算成由 quarters25分硬幣，dimes10分，nickels5分，和 pennies1分 的組合

    III.輸出以最大面額為基準

5. Bouns內容
    1. 整體 coding style 與 作業完整度
    2. 防呆機制的處理
        a. 判斷 argv[1] 是否存在，若不存在，會輸出 "You haven't input anything. (There's no argv[1])" 並結束程式
        b. 判斷 argv[1] 內容是否合法 (x.y1y2) 
            I.判斷string長度是否小於4 (像是0就判斷為不合法)
            II.判斷string內的倒數第三個digit是否為'.'
            III.判斷string內其他digit是否都是數字
            => 若判斷結果為不合法，輸出 "your input is not valid.(not x.y1y2)" 並結束程式
            補充：0.00程式會判斷其為合法

6. Reference
	class:http://kaiching.org/pydoing/cpp-guide/unit-10-class.html
    lround:https://www.delftstack.com/zh-tw/howto/cpp/how-to-round-a-double-to-an-int-in-cpp/
