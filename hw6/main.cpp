#include "Blackjack.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iomanip>

using namespace std;

int main(){
    Game *p = new Game(); // play Blackjack game
    delete p;
    return 0;
}