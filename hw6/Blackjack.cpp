#include "Blackjack.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iomanip>

using namespace std;

Card::Card(int cardnumber){ // build the initial table
    eachcardnum = cardnumber;
    currentcardnum = eachcardnum  * 52;
    for(int i = 0; i < 52; i++){
        cardtable[i] = eachcardnum; // cardtable store the current quantity of each different card
    }
}

int Card::getcurrentcardnum(){ // get value of currentcardnum
    return currentcardnum;
}

int Card::GiveCard(){ // when called, return one card number. (give player one card)
    if(currentcardnum == 0) // if there's no more card left, return -1;
        return -1;
    int givencard = rand() % currentcardnum; // givencard: decide to give the card bigger than (the value of givencard) cards.
    int i = 0, state = 0; // state count the current card is bigger than (the value of state) cards.
    while(i < 52 * eachcardnum){
        if(cardtable[i%52] == 0){ // there's no more this kind of card.
            state--;
        }
        if(state == givencard && cardtable[i%52] != 0){ // find the card that decided to give
            currentcardnum--;
            cardtable[i%52]--;
            return i%52;
        }
        i++;
        state++;
    }
    return -1;
}

void Card::RebuildCard(int players){ // if the currentcardnum is less than 5 * quantity of player, refresh the cardtable
    if(currentcardnum >= players * 5)
        return;
    currentcardnum = eachcardnum * 52;
    for(int i = 0; i < 52; i++){
        cardtable[i] = eachcardnum;
    }
}

Player::Player(string playername,int startbankroll, int playertype){ // build the initial name, a starting bankroll, and some strategy of player
    name = playername;
    bet = 0;
    bankroll = startbankroll;
    type = playertype;
    point = 0;
    cardnum = 0;
    wingame = -1;
    for(int i = 0; i < 22; i++){
        handcard[i] = 0;
    }
}

string Player::getname(){ // get player's name
    return name;
}

void Player::PlayerBankroll(){ // decide bankroll of player
    do{
        cout << name << ", how much would be your starting bankroll? ";
        cin >> bankroll;
        if(bankroll < 1)
            cout << "I think if you want to play, you need to pay some money, please input more than 0." << endl;
    }while(bankroll < 1);
}

void Player::PlayerBet(){ // decide bet of player
    if(type == 0){ // Dealer
        return;
    }
    else if(type == 1){ // Human
        do{
            cout << name << ", how much would you like to bet? ";
            cin >> bet;
            if(bet < 1)
                cout << "The minimum bet is $1 at our table, please bet again..." << endl;
        }while(bet < 1);
    }
    else if(type == 2){ // Meek
        if(wingame >= 3){
            bet *= 2;
            wingame = 0;
        }
        else if(wingame == -1){
            bet = 2;
            wingame = 0;
        }
    }
    else if(type == 3){ // Random
        if(bankroll <= 1)
            bet = 1;
        else
            bet = (rand() % (bankroll / 2 - 1)) + 1;
    }
}

char Player::PlayerChoose(){ // decide if player want another card
    char choose = 'N';

    if(type == 0){ // Dealer
        if(point <= 16)
            choose = 'Y';
    }
    else if(type == 1){ // Human
        cout << "Would you like to draw another card (Y or N): ";
        cin >> choose;
    }
    else if(type == 2){ // Meek
        if(point % 2 == 0)
            choose = 'Y';
        for(int i = 0; i < cardnum; i++){
            if(handcard[i] == 24)
                choose = 'Y';
        }
    }
    else if(type == 3){ // Random
        if(point <= 9)
            choose = 'Y';
        else if(point <= 12){
            if(rand() % 10 < 8)
                choose = 'Y';
        }
        else if(point <= 15){
            if(rand() % 10 < 7)
                choose = 'Y';
        }
        else if(point <= 18){
            if(rand() % 10 < 5)
                choose = 'Y';
        }
    }
    return choose;
}

int Player::CountPoint(){ // count the current total point of all cards player get
    point = 0;
    int ace = 0;
    for(int i = 0; i < cardnum; i++){ // search handcard and change point 
        if(handcard[i] / 4 + 1 > 10) // if is J - k
            point += 10;
        else if(handcard[i] / 4 + 1 == 1){ // if is A
            point += 1;
            ace++;
        }
        else
            point += handcard[i] / 4 + 1;
    }
    for(int i = 0; i < ace; i++){ // decide if A could be 11 point
        if(point + 10 < 22)
            point += 10;
    }
    return point;
}

string Game::CardValue(int cardnumber){ // change the card number to rank and suit
    string rank = to_string(cardnumber / 4 + 1);
    if(cardnumber / 4 + 1 == 1)
        rank = "A";
    if(cardnumber / 4 + 1 == 11)
        rank = "J";
    if(cardnumber / 4 + 1 == 12)
        rank = "Q";
    if(cardnumber / 4 + 1 == 13)
        rank = "K";
    
    if(cardnumber % 4 == 0) // Clubs, Diamonds, Hearts, Spades
        rank.push_back('C');
    if(cardnumber % 4 == 1)
        rank.push_back('D');
    if(cardnumber % 4 == 2)
        rank.push_back('H');
    if(cardnumber % 4 == 3)
        rank.push_back('S');
    return rank;
}

void Game::GameStart(){ // use when the game start
    do{ // input quantity of players
        cout << "Welcome to the Blackjack game, how many players should be creat?" << endl;
        cin >> players;
        if(players == 1)
            cout << "If there's only dealer, he/she will be lonely, please input more than one..." << endl;
        else if(players < 1)
            cout << "If there's no player, what do you want to play for?" << endl;
    }while(players < 2);

    do{ // input quantity of each kind of players
        cout << "About the kinds of players:" << endl;
        cout << "There would be exactly one dealer, there're " << players -1 << " players need to be decided." << endl;
        
        do{
            cout << "How many human players?" << endl;
            cin >> human;
            if(human < 0)
                cout << "human player can not be less than zero, please try again." << endl;
        }while(human < 0);

        do{
            cout << "How many meek computer players?" << endl;
            cin >> meek;
            if(meek < 0)
                cout << "meek computer player can not be less than zero, please try again." << endl;
        }while(meek < 0);

        do{
            cout << "How many random computer players?" << endl;
            cin >> random;
            if(random < 0)
                cout << "random computer player can not be less than zero, please try again." << endl;
        }while(random < 0);

        if((human + meek + random + 1) != players)
            cout << "the total number of players is not currect, please decide again..." << endl;
    }while((human + meek + random + 1) != players);

}

void Game::BuildHuman(Player **p){ // build the initial name, a starting bankroll, and some strategy of human
    int startbankroll;
    string playername;
    for(int i = 0; i < human; i++){
        cout << "the " << i + 1 << "'s name of human is:" << endl;
        cin >> playername;
        do{
            cout << playername << ", how much would be your starting bankroll? ";
            cin >> startbankroll;
            if(startbankroll < 1)
                cout << "I think if you want to play, you need to pay some money, please input more than 0." << endl;
        }while(startbankroll < 1);
        p[i] = new Player(playername, startbankroll, 1);
    }
}

bool Game::Playing(Card *cards, Player **p){ // play for one round(if something went wrong => return true)
    sleep(2);
    // players bet
    cout << "Okay, time for betting!" << '\n' << "-----------------------------------------" << endl;
    for(int i = 0; i < players - 1; i++){
        p[i] -> PlayerBet();
        cout << p[i] -> getname() << " bets $" << p[i] -> bet << endl;
        sleep(1);
    }
    sleep(1);
    // the initial hand card (two card)
    cout << '\n' << "The initial starting cards are:" << '\n' << "-----------------------------------------" << endl;
    sleep(1);
    for(int i = 0; i < players; i++){
        p[i] -> handcard[0] = cards -> GiveCard();
        p[i] -> handcard[1] = cards -> GiveCard();
        p[i] -> cardnum += 2;
        cout << p[i] -> getname() << "'s current hand:[??][" << CardValue(p[i] -> handcard[1]) << "]" << endl; 
        sleep(1);
    }
    cout << endl;

    // players play
    char choose;
    for(int i = 0; i < players; i++){
        sleep(1);
        cout << p[i] -> getname() << "'s turn:" << '\n' << "----------------" << endl;
        choose = 'Y';
        sleep(1);
        while(choose == 'Y' || choose == 'y'){
            if(p[i] -> CountPoint() > 21){ // check if busted
                cout << p[i] -> getname() << " busted at " << p[i] -> point << "!" << endl;
                break;
            }
            cout << p[i] -> getname() <<  "'s current hand:";
            for(int j = 0; j < p[i] -> cardnum; j++){
                cout << "[" << CardValue(p[i] -> handcard[j]) << "]";
            }
            cout << "(" << p[i] -> CountPoint() << " points)" << endl;
            choose = p[i] -> PlayerChoose(); // player choose
            if(choose != 'Y' && choose != 'y'){
                cout << p[i] -> getname() << " chooses to stay." << endl;
                break;
            }
            // give player one card
            p[i] -> handcard[p[i] -> cardnum] = cards -> GiveCard();
            p[i] -> cardnum++;

            cout << p[i] -> getname() << " chooses to draw." << endl;
            if(p[i] -> handcard[(p[i] -> cardnum) - 1] < 0){ // check if there's any card left in card table
                return 1;
            }
            sleep(1);
        }
        cout << endl;
        sleep(1);
    }
    return 0;
}

void Game::BetCycle(Player **p, int player, bool win){ // use bet to change the bankroll if win or lose
    int i = player;
    if(win == 1){ // player win
        p[i] -> wingame++;
        p[i] -> bankroll += p[i] -> bet;
        p[players - 1] -> bankroll -= p[i] -> bet;
        sleep(1);
        cout << "Yowzah! " << p[i] -> getname() << " wins $" << p[i] -> bet << endl;
    }
    else{ // dealer win
        if(p[i] -> point > 21)
            p[i] -> wingame = -1;
        else
            p[i] -> wingame = 0;
        p[i] -> bankroll -= p[i] -> bet;
        p[players - 1] -> bankroll += p[i] -> bet;
        sleep(1);
        cout << "Ouch! " << p[i] -> getname() << " loses $" << p[i] -> bet << endl;
    }
}

void Game::WhoWin(Player **p){ // judge if the player win
    cout << "Let's see how it turned out:" << '\n' << "---------------------------------------" << endl;
    sleep(2);
    for(int i = 0; i < players - 1; i++){
        if(p[players - 1] -> cardnum >= 5 && p[players - 1] -> point <= 21) // dealer have more than five card without busted
            BetCycle(p, i, 0);
        else if(p[i] -> point > 21) // player busted
            BetCycle(p, i, 0);
        else if(p[players - 1] -> point > 21) // dealer busted
            BetCycle(p, i, 1);
        else if(p[i] -> point <= p[players - 1] -> point) // player's point less than or equal to dealer's
            BetCycle(p, i, 0);
        else if(p[i] -> point > p[players - 1] -> point) // player's point more than dealer's
            BetCycle(p, i, 1);
    }
    sleep(1);
    cout << '\n' << "The standings so far:" << '\n' << "------------------------------" << endl;
    for(int i = 0; i < players; i++){
        cout << p[i] -> getname() << " $" << p[i] -> bankroll << endl;
    }
}

Game::Game(){ // play the whole game
    srand(time(NULL));
    GameStart();
    Card *cards = new Card((players / 4 + 1));
    Player *p[players];
    BuildHuman(p); // build human
    string playername;
    for(int i = 0; i < meek; i++){ // build meek
        playername = "Meek" + to_string(i + 1);
        p[human + i] = new Player(playername, 0, 2);
    }
    for(int i = 0; i < random; i++){ // build random
        playername = "Random" + to_string(i + 1);
        p[human + meek + i] = new Player(playername, 0, 3);
    }
    for(int i = 0; i < meek + random; i++){ // build bankroll of players
        p[human + i] -> PlayerBankroll();
    }
    p[players - 1] = new Player("Dealer", 10000, 0); // build dealer
    char choose = 'Y';
    system("clear");
    while(choose == 'Y' || choose == 'y'){ // play game
        cards -> RebuildCard(players);
        sleep(1);
        cout << '\n'  << "The standings so far:" << '\n' << "------------------------------" << endl;
        sleep(2);
        for(int i = 0; i < players; i++){
            p[i] -> cardnum = 0;
            p[i] -> point = 0;
            cout << p[i] -> getname() << " bankroll is $" << p[i] -> bankroll << endl;
        }
        sleep(2);
        cout << '\n' << "Game start!" << '\n' << endl;
        if(Playing(cards, p) > 0){ // play and check if there's no more card and this round of game end
            sleep(1);
            cout << "There's no more card, restart the game..." << endl;
            continue;
        }
        sleep(1);
        WhoWin(p); // check who win and refresh bankroll
        cout << "Another round? (Y or N):";
        cin >> choose;
        system("clear");
    }
}