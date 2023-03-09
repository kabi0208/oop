1. 姓名：陳品希

2. 學號：409410024

3. e-mail：ivychen20020208@gmail.com

4. 完成的作業項目

    Part A : 
        1.Define a non-member function that overloads the operator "/" 
            物件A中的XYZ總和 / 物件B的XYZ總和
        2.Define a member function that overload the operator "!="
            The volume of A cube != The volume of B cube

    Part B : 實作一個具有自己運算模式的物件 Time
        1.A Time object will store a quantity of time, in terms of days, hours, minutes, and second.
            Format : days~hh:mm:ss
            ex.10~18:30:58
            補充:這邊的hour, minute, day 有限制要是兩位整數，但day似乎沒有特別規定，故day我沒有特別限制輸出的是幾位整數
        2.Constructors: 
            I.Should have a default constructor
            II.Allows automatic type conversions from “int” to “Time”
            III. No negative time, should represent as "0" if negative.
        3.Basic operators need to be overloaded 
            arithmetic operator : +,-,++,--
            comparison operator : < , > , <= , >= , == , !=
            I/O operator : >>, <<

5. Bouns內容
    Part A : 
        1.取得pivate的值
            我有像作業四一樣做了以下function：
            double Cube::get_x() const{ return x; } // get the value of x
            double Cube::get_y() const{ return y; } // get the value of y
            double Cube::get_z() const{ return z; } // get the value of z
            方便別人取得value
        2.印出錯誤訊息
            double operator/(const Cube &a, const Cube &b)
            在此function中，若相除的分母為零，會輸出以下錯誤訊息：
            "(warning!!the denominator is 0.) "
            
    Part B : 
        1.取得pivate的值
            我有像作業四一樣做了以下function：
            int get_day() const; // get the value of day
            int get_hour() const; // get the value of hour
            int get_minute() const; // get the value of minute
            int get_second() const; // get the value of second
            方便別人取得value
        2.印出錯誤訊息
            I. Time::Time(int s)
                若parameter小於0，輸出錯誤訊息："The parameter is less than 0, default the Time object to represent 0."
            II. Time::Time(int d, int h, int m, int s)
                若任一parameter小於0，輸出錯誤訊息："At least one parameter is less than 0, default the Time object to represent 0."
            III. istream & operator>>(istream & cin, Time& goal)
                若任一input value小於0，輸出錯誤訊息："At least one input value is less than 0, default the Time object to represent 0."
            IV. Time operator-(const Time &a, const Time &b)
                若第一個Time小於第二個，輸出錯誤訊息："(The first quantity of time is less than the second, set Time as 0) "
            VI. Time& Time::operator--()
                Time Time::operator--(int)
                若Time原本就是0，輸出錯誤訊息："(the Time object is already at 0, then decrement does not change it) "
        3.operator+
            我也處理了 1 + t 的情況(1是數字、t是Time)
    

6. Reference
	https://reurl.cc/A7Ke1j
    https://www.796t.com/content/1548262469.html
    https://blog.xuite.net/hgsfhevil/wretch/132240622
    https://www.section.io/engineering-education/getting-started-with-operator-overloading-in-c++/
    https://www.runoob.com/w3cnote/cpp-func-setw.html
    老師overload的ppt

7.補充
    因為好像沒有規定，
    所以我 Part A 的執行檔叫hw5A.exe，Part B的執行檔叫hw5B.exe
    然後附在資料夾內的執行檔都是用我自己寫的main.cpp一起編譯的

