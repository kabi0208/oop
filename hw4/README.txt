1. 姓名：陳品希

2. 學號：409410024

3. e-mail：ivychen20020208@gmail.com

4. 完成的作業項目
    撰寫一個用建立迷宮的程式
        撰寫一個 Grid class 包含以下function (請勿擅自合併 或 取代function功能) 任何function 有誤 一個扣20分

        class Grid {
        public: // public static class constants, for direction indicators
        static const int NORTH = 0;
        static const int WEST = 1;
        static const int SOUTH = 2;
        static const int EAST = 3;

        // public member functions
        Grid(); // build 1 x 1 grid with mover in only square, facing east
        Grid(int r, int c); // build grid with r rows, c cols, // blocks around edge with random exit and random mover position and direction
        Grid(int r, int c, int mr, int mc, int d); // build empty grid with r rows, c cols, and mover at row mr, col mc, and facing direction d
        bool Move(int s); // move forward s spaces, if possible
        void TogglePath(); // toggle whether or not moved path is shown
        void TurnLeft(); // turn the mover to the left

        void PutDown(); // put down an item at the mover's position
        bool PutDown(int r, int c); // put down an item at (r, c), if possible
        bool PickUp(); // pick up item at current position
        bool PlaceBlock(int r, int c); // put a block at (r, c), if possible
        void Grow(int gr, int gc); // grow the grid by gr rows, gc columns
        void Display() const; // display the grid on screen

        // Accessors
        bool FrontIsClear() const; // check to see if space in front of mover is clear
        bool RightIsClear() const; // check to see if space to right of mover is clear
        int GetRow() const; // return row of the mover
        int GetCol() const; // return column of the mover

        int GetNumRows() const; // return number of rows in the grid
        int GetNumCols() const; // return number of columns in the grid

        private則自己設計

5. Bouns內容
    1. 建立有圍牆和出口的迷宮
        這個部分因為好像沒有看到有特別規定圍牆是外擴還是內縮
        例：
        3X3 外擴
        # # # # #
        # > . . .
        # . . . #
        # . . . #
        # # # # #
        3X3 內縮
        # # #
        # > .
        # # #
        雖然在討論區上看到有人問，但好像沒有明確回覆，所以我就照圍牆外擴來做了
    2. 進行Grow時，有處理右邊和下面的出口位置
        我是直接讓出口平移到新的grid的邊界
        若出口在右邊
        # # #
        # > .
        # # #
        會變成這樣
        # # # # #
        # > . . .
        # . . . #
        # . . . #
        # # # # #

        若出口在下面
        # # #
        # > #
        # . #
        會變成這樣
        # # # # #
        # > . . #
        # . . . #
        # . . . #
        # . # # #
    3. 讓出口一直存在
        我在討論區看到driver 在placeblock的時候把出口堵住的問題
        我的解決方法是在placeblock的時候判斷，若放了這個block會導致沒有出口，
        那就不讓他放，return false
    4.印出錯誤訊息
        作業要求的function中 若 type 為 bool，執行失敗不會印出任何錯誤訊息
        (像是bool PlaceBlock(int r, int c) 若r, c 超出範圍則return false之類的情況)
        因為我覺得可以在main判斷回傳是否為true就好。
        而以下function若執行不成功或我有修改傳入的值，會印出一些訊息提醒他：
        a.三個 constructor 程式都會印出："Constructing a _x_ Stack..."，提醒使用者(因為當r, c不在範圍內時，會修改值讓形成的grid在指定範圍大小)
            Grid(int r, int c, int mr, int mc, int d);
                這個function我會額外多判斷d是否合法(0~3)，若不合法則幫他設定為3(EAST)，
                並印出訊息："The direction you set is invaild, help you set as EAST"
        b.void Grow(int gr, int gc);
            若 gr 或 gc <=0 ，印出："Grow means bigger, so your input should be bigger than 0"，不改變grid大小
            而執行成功會印出："Grow stack to a _x_ Stack..."
    5. coding style

6. Reference
	標頭檔：http://kaiching.org/pydoing/cpp-guide/unit-13-header.html

7.補充
    因為好像沒有規定要叫什麼，所以我的執行檔叫hw4.exe
    然後附在資料夾內的執行檔是用ftp上的main.cpp一起編譯的