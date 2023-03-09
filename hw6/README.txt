1. 姓名：陳品希

2. 學號：409410024

3. e-mail：ivychen20020208@gmail.com

4. 完成的作業項目
    我的遊戲整個是寫在一個叫做Game的class裡面，在main裡面只要創一個Game class的物件即可進行遊戲。
    以上我都已經做好了，要玩遊戲的話只要make再執行執行檔hw6.exe(./hw6.exe)就可以玩了。
    遊戲準備：
        a.  Welcome to the Blackjack game, how many players should be creat?
            這邊問的是參與遊戲的總共有幾人，這邊的人數包含dealer, human, meek, random players。
            "4人會使用一副牌大於4人小於8人會使用兩副牌，以此類推"
        b.  About the kinds of players:
            There would be exactly one dealer, there're __ players need to be decided.
            How many human players?
            How many meek computer players?
            How many random computer players?
            這邊會依序詢問各種類的人是幾個(dealer已經自動決定好是一個，並告知剩下幾個player要被決定)
            若選擇後的總數跟一開始決定的總人數不相符，會需要重新選擇各種類的人是幾個:
                the total number of players is not currect, please decide again...
                About the kinds of players:
                There would be exactly one dealer, there're __ players need to be decided.
        c.  the __'s name of human is:
            若為Human player則會需要幫player取名。
            若為Meek或Random就會自動生成名字(例:Meek1,Meek2)，Dealer因為只有一個所以就直接叫Dealer
        d.  ___, how much would be your starting bankroll?
            因為似乎沒有特別規定meek跟random的bankroll規則，故除了dealer，所有players的bankroll都要手動輸入。
            然後我規定bankroll必須大於1
        e.  The standings so far:
            ------------------------------
            Jack bankroll is $100
            Meek1 bankroll is $100
            Random1 bankroll is $100
            Dealer bankroll is $10000
            決定完之後就會出現類似上面的範例，輸出目前所有player的bankroll
    遊戲開始:
        a.  ___, how much would you like to bet?
            若為human就會讓他選擇bet多少，然後會印出目前所有人bet的金額
            關於random，pdf檔上的規定He randomly bets some amount between $1 and half of his bankroll each round.
            但規定bet必需大於等於1，故若random的bankroll小於1，我就會直接讓他bet 1
        b.  The initial starting cards are:
            -----------------------------------------
            Jack's current hand:[??][8S]
            Meek1's current hand:[??][JS]
            Random1's current hand:[??][2D]
            Dealer's current hand:[??][KD]
            印出大家的初始卡牌
        c.  Jack's turn:
            ----------------
            Jack's current hand:[QD][8S](18 points)
            point的部分若手牌中有A則會以最有利的情況輸出point
            也就是說若A視為11不會爆牌，則視為11。若會爆牌，則視為1
        d.  Would you like to draw another card (Y or N):
            可以決定是否繼續加牌，這邊若輸入是y或Y我就判定他要加，其他就判定不要。
            若當前手牌點數為21點，因沒有特別規定，我仍會讓player可以選擇繼續加牌。
            若加完後爆牌會印出 "Jack busted at 31!" 類似這樣的訊息。
            除了Human其他都是電腦自動選擇，輸出比照作業pdf上提供的輸出範例
        e.  印出遊戲結果及計算後的bankroll，這邊也比照作業pdf上提供的輸出範例
            遊戲輸贏的判定我參考了教授在討論區貼的網址:https://zh.m.wikipedia.org/zh-tw/%E4%BA%8C%E5%8D%81%E4%B8%80%E9%BB%9E
            規則如下:
                莊家在取得17點之前必須要牌，因規則不同會有軟17點或硬17點才停牌的具體區分。且莊家如果拿牌五張而沒有爆牌則視為莊家勝利。
                每位玩家的目的是要取得最接近21點數的牌來擊敗莊家，但同時要避免爆牌。要注意的是，若玩家爆牌在先即為輸，就算隨後莊家爆牌也是如此。
                若玩家和莊家擁有同樣點數，這樣的狀態稱為「push」，玩家和莊家皆不算輸贏。
                每位玩者和莊家之間的遊戲都是獨立的，因此在同一局內，莊家有可能會輸給某些玩家，但也同時擊敗另一些玩家。
            但對於規則中push的情況，我參考作業pdf第6頁:All ties打成平局 go to the dealer.
            若為push，我會判定為dealer贏
    遊戲結束:
        Another round? (Y or N):
        詢問是否繼續下一輪，若輸入是y或Y我就判定他要，其他就判定不要。
        若開啟下一輪，則會從遊戲準備的e.繼續
    以上若有沒有特別說明的地方，則都與作業pdf規定相同

    關於我的code:
        Card主要處理Card相關問題，像是發牌、確認剩幾張牌之類的
        class Card{
            private:
                int eachcardnum; // the quantity of each different card when the table been rebuild (how many decks)
                int currentcardnum; // store how many cards left
                int cardtable[52]; // store the current quantity of each different card
            public:
                Card(int); // build the initial table
                int getcurrentcardnum(); // get value of currentcardnum
                int GiveCard(); // when called, return one card number. (give player one card)
                void RebuildCard(int players); // if the currentcardnum is less than 5 * quantity of player, refresh the cardtable
        };
        每個玩家都是一個Player，存取player的相關資訊，決定player的行為，及計算手牌分數
        class Player{ // store player's name, a starting bankroll, and some strategy
            private:
                string name; // player's name
                int type; // used to judge the player's type. Dealer:0 Human:1 Meek:2 Random:3
            public:
                int handcard[22]; // the cards that player get in that round
                int point; // the current total point of all cards player get
                long long int bankroll; // player's current bankroll
                long long int bet; // how much player bet in this round
                int cardnum; // the current quantity of cards that player get
                int wingame; // count player wins how much rounds in a row. if lose, change to 0. if busted, change to -1. The initial value is -1
                Player(string playername,int startbankroll, int playertype); // build the initial name, a starting bankroll, and some strategy of player
                string getname(); // get player's name
                void PlayerBankroll(); // decide bankroll of player
                void PlayerBet(); // decide bet of player
                char PlayerChoose(); // decide if player want another card
                int CountPoint(); // count the current total point of all cards player get
        };
        Game負責執行整個遊戲
        class Game{ // play Blackjack game
            private:
                int players; // the total players which join the game
                int human; // the quantity of human players
                int meek; // the quantity of meek players
                int random; // the quantity of random players
            public:
                string CardValue(int cardnumber); // change the card number to rank and suit
                void GameStart(); // use when the game start
                void BuildHuman(Player **p); // build the initial name, a starting bankroll, and some strategy of human
                bool Playing(Card *cards, Player **p); // play for one round (if something went wrong => return true)
                void BetCycle(Player **p, int player, bool win); // use bet to change the bankroll if win or lose
                void WhoWin(Player **p); // judge if the player win
                Game(); // play the whole game
        };

5. Bouns內容
    防呆:
        a.  若卡牌數不夠
            作業要求是"如果牌庫總量低於玩家數 * 5 ，則需將牌回收並重新洗牌"，
            雖然很極端，但也有可能有平均每個玩家抽超過五張牌的情況。在這種極端加上極端的情況下，會有剩餘牌不夠抽的可能
            故我會判斷若剩餘可抽的牌為0，印出"There's no more card, restart the game..."，這場的輸贏就通通不計算，直接重開一場。
        b.  玩家數量不能為負
            不管是一開始輸入的總玩家數還是各種類玩家數都必須大於等於0，而總玩家數必須大於1，因為只有Dealer一個人沒辦法玩遊戲。
    遊戲化:
        我在code內加入一些sleep()跟system("clear")
        sleep():可以讓輸出慢慢跑出來，不要一次全都跑出來，增強遊戲體驗，順便營造一種computer player也有在思考的感覺
        system("clear"):我是設定每玩完1輪就清空螢幕，讓資訊不要看起來那麼雜亂。
        
6. Reference
    https://zh.m.wikipedia.org/zh-tw/%E4%BA%8C%E5%8D%81%E4%B8%80%E9%BB%9E
    https://wellbay.cc/thread-1926538.htm
    https://www.delftstack.com/zh-tw/howto/cpp/char-to-string-cpp/

7.補充
    我的執行檔叫hw6.exe
    若執行中有些微停頓為正常現象，我只是想讓他能讓人更有遊戲體驗，詳細可以看bonus內容說明



