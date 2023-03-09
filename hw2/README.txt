1. 姓名：陳品希

2. 學號：409410024

3. e-mail：ivychen20020208@gmail.com

4. 完成的作業項目
	1.撰寫 Credit card number validation
        I. 下列function成功運作
            1.bool isvalid (const string& cardNumber)
                測試是否符合投影片內的規則，是的話return true
            2.int sumofDoubleEvenPlace (const string& cardNumber)
                return 計算過的even place數字加總
            3.int getDigit (int number)
                把各位數字加起來，return 處理過的number
            4.int sumOfOddPlace (const string& cardNumber)
                return odd place數字加總
            5.bool startsWith (const string& cardNumber, const string& substr)
                根據討論區上的"作業二function bool startsWith 問題"，我改成：
                int startsWith (const string& cardNumber)
                若為已知的四種信用卡其中一種，就return 他的第一個數字
                若不是，則return 7(之所以return 7，是因為我在main函式以string陣列儲存要印出的信用卡種類，這樣比較方便轉換)
            以下為我自己新增的：
            6.bool iscard (const string& cardNumber)
				測試是否符合credit card的標準(是否為 13 - 16 digits，是否都是數字)
				若都符合則return true
            7.struct timespec computeTime(const struct timespec start,const struct timespec end)
				計算生成fake number的時間：
				將在main function內得到的開始及結束時間傳入(const struct timespec)，計算後所得時長存在timming傳回去(struct timespec)
			8.string fakeOne (const string& brand)
				return 生成的號碼，這個function在後面會詳細說明
		II.當輸入特定字串時 (例："004") 生成指定要求
            1.生成要求的合法信用卡號碼
				我使用function生成號碼：
				string fakeOne (const string& brand)
				這個在教授的ppt內有，但似乎不在作業要求內。
				原版是string& fakeOne (const string& brand)，我稍微修改成如上function。
				我在function內判斷brand並產生適當的開頭數字，其他的數字以random產生，
				呼叫sumofDoubleEvenPlace及sumOfOddPlace的結果加總對10取餘數，存在remainder
				若其值不為零，修改最後一位數字來讓總和符合標準。配合do while迴圈檢查來避免意外情況(雖然我是覺得不會有意外啦)
            2.使用timer計算生成時間
				我使用clock_gettime測量生成號碼的時間，並配合下列副函式進行換算
				struct timespec computeTime(const struct timespec start,const struct timespec end)
				而根據討論區的範例輸出，我讓記算出的時間以整數型態輸出
		III.讀檔
			根據教授的ppt："Read the name of the data file from the command line in argv[1]."
			我使用argv讀取檔案名稱，後來在討論區看到有固定檔名為input.txt，
			但我想我這樣寫應該也符合要求，故沒有多做更改。
		IV.關於偵錯等部分
			1.若argv[1]沒有東西(沒給檔名)
				輸出 "there's no argv[1], which means name of data file haven't be given..." 並結束程式
			2.若txt檔無法開啟(當前資料夾內沒有此檔案或其他原因)
				輸出 "Failed to open file." 並結束程式
			3.若輸入號碼不符合credit card要求(between 13 and 16 digits)
				程式會判斷string長度與是否都是數字，不符合的話輸出 "this isn't a credit card number (not 13 ~ 16 numbers.)"
				並繼續讀取下一行
			4.若某行沒有任何東西
				程式會自動忽略那行而繼續看下一行(不會輸出任何東西)
			5.若號碼開頭不是提供四種的其中一種
				程式會當他是Unknown card
				若合法：a valid Unknown card #
				若不合法：an invalid Unknown card #

5. Bouns內容(助教會依Bonus內容酌量給分)
	1.使用非講義的方法，生成合法的信用卡號碼
		string fakeOne (const string& brand)
		我在function內判斷brand並產生適當的開頭數字，其他的數字以random產生，
		呼叫sumofDoubleEvenPlace及sumOfOddPlace的結果加總對10取餘數，存在remainder
		若其值不為零，修改最後一位數字來讓總和符合標準。配合do while迴圈檢查來避免意外情況(雖然我是覺得不會有意外啦)
			補充：因為計算後的數字總和只要能被10整除即為合法，故可知只要動到一個數字即可讓號碼合法
			我選擇修改最後一位(由右數來第一位)，即可避免判斷其為奇位數或偶位數。
	2.整體 coding style

6. Reference
	讀檔：https://shengyu7697.github.io/cpp-read-text-file/
	argc/argv：https://blog.gtwang.org/programming/c-cpp-tutorial-argc-argv-read-command-line-arguments/
	生成亂數：https://edisonx.pixnet.net/blog/post/91314418
	測量時間：https://blog.gtwang.org/programming/measure-the-execution-time-in-c-language/2/