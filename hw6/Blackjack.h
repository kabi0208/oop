#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iomanip>

using namespace std;

class Card{ // store the card
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

class Game{ // play Blackjack game
    private:
        int players; // the total players which join the game
        // exactly one dealer
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