/************************
Baccarat
************************/

#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <random>
#include <set>
#include <vector>
#include <sstream>
#include <cstdlib> 
#include <ctime>
using namespace std;

// data type with propertization for a single card within a deck
struct BaccaratCard {
    string valueName;
    string suit;
    int value;
};


void Game2(int &ovrMoney, vector<BaccaratCard> deckVec, int vecIndex);



void displayBaccaratMenu() {
    cout << "Hello! Welcome to Baccarat!" << endl;
    cout << "Rules below: " << endl;
    cout << "             Your aim is to bet on the outcome/winner of the game" << endl;
    cout << "             The player will be dealt two cards along with the banker" << endl;
    cout << "             First one to get closest to 9 wins" << endl;
    cout << "             However, if either goes over 9, score is subtracted by 10" << endl;
    cout << "             If the players hand is 5 or less, they will be dealt a third card" << endl;
    cout << "             The banker drawing a third card depends on the player" << endl;
    cout << "             Please see the following link for more information on this if you please" << endl;
    cout << "             https://www.onlinecasinos.co.uk/game-guides/baccarat/rules-for-baccarat-banker.htm" << endl;
    cout << "             Betitng on the Player or the Banker pays 1:1" << endl;
    cout << "             betting on tie pays 8:1" << endl;
    cout << "             Imporant note is that Face cards value at 0, and Aces value at 1" << endl;
    cout << "             Happy playing!" << endl << endl;
}


// prints the details of a given card in english
string printCardLong2(BaccaratCard card) {
    return "(" + card.valueName + "-" + card.suit + ")";
}



// handles the users bet, in regard to the Casino's maximum
void errorHandle3(int &choice, int lowerBound, int upperBound) {
    while (1) {
        cout << "Your Choice --> $";
        int userChoice;
        cin >> userChoice;
        if (cin.fail() || userChoice < lowerBound || userChoice > upperBound) {
            cout << "Invalid Input, Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else {
            choice = userChoice;
            break;
        }
    }
}



// shuffles a deck of cards, or multiple decks at once 
void shuffleDeck2(vector<BaccaratCard> &deckVec) {
    random_device rd;
    mt19937 rng(rd()); // Mersenne Twister
    shuffle(deckVec.begin(), deckVec.end(), rng);
}



// reads file, decks are filled into vector
void readFile2(vector<BaccaratCard> &deckVec) {
    ifstream inFS;
    inFS.open("deckOfCards.txt");
    if (!inFS.is_open()) {
        cout << "file not read";
        exit(0);
    }
    string line;
    while (getline(inFS, line)) {
        BaccaratCard card;
        stringstream ss(line);
        string value;
        string suit;
        ss >> value >> suit;
        card.valueName = value;
        card.suit = suit;
        if (value == "Ace") {
            card.value = 1;
        }
        else if (value == "2") {
            card.value = 2;
        }
        else if (value == "3") {
            card.value = 3;
        }
        else if (value == "4") {
            card.value = 4;
        }
        else if (value == "5") {
            card.value = 5;
        }
        else if (value == "6") {
            card.value = 6;
        }
        else if (value == "7") {
            card.value = 7;
        }
        else if (value == "8") {
            card.value = 8;
        }
        else if (value == "9") {
            card.value = 9;
        }
        else if (value == "10") {
            card.value = 0;
        }
        else if (value == "Jack") {
            card.value = 0;
        }
        else if (value == "Queen") {
            card.value = 0;
        }
        else if (value == "King") {
            card.value = 0;
        }
        else {
            card.value = 0;
            cout << "Error, could not assign numerical alue to the card" << endl;
        }
        deckVec.push_back(card);
    }
    inFS.close();
}



// calculates the points for a hand at any given state of the game
int handTotal(vector<BaccaratCard> hand) {
        int total = 0;
        for (int i = 0; i < hand.size(); i++ ) {
            total += hand.at(i).value;
        }
        // 10 - 19
        if (total >= 10 && total <= 19) { // 10-10=0, 11-10=1, 12-10=2, etc.
            total -= 10;
        }
        // 20+
        if (total >= 20) {
            total -= 20;
        }
        return total;
}



// evaluates if the player needs to draw a third card or not 
bool evaluatePlayerDraw(vector<BaccaratCard> hand) {
    if (handTotal(hand) <= 5) {
            return true; // have to draw 1 more
    }
    else if (handTotal(hand) == 6 || handTotal(hand) == 7) {
        return false; // dont draw 1 more
    }
    else {
        return false; // dont draw 1 more
    }
}



// outputs the winner of the game based on score 
string whoWon(vector<BaccaratCard> hand1, vector<BaccaratCard> hand2) {
        if (handTotal(hand1) > handTotal(hand2)) {
            return "Player";
        }
        // second hand (banker) is greater WINNER
        else if (handTotal(hand1) < handTotal(hand2)) {
            return "Banker";
        }
        // if reach here, the hands are equal
        else {
            return "Draw";
        }
}



// evaluates if the banker needs to draw a third card, based on the players third card value 
bool evaluateBankerDraw(vector<BaccaratCard> hand, BaccaratCard playerCard) { // playerCard = players third 
    if (hand.size() == 3) { // already has 3 cards
        return false;
    }
    if (handTotal(hand) <= 2) {
        return true; // draw
    }
    // 3 4 5 or 6
    if (handTotal(hand) >= 3 && handTotal(hand) <= 6) {
        // banker 6, player third is 6 or 7
        if (handTotal(hand) == 6) {
            if (playerCard.value == 7) {
                return true; // draw
            }
            else {
                return false; // dont draw
            }
        }
        // banker 5, player third is [4,7] or did NOT draw third
        if (handTotal(hand) == 5) {
            if (playerCard.value >= 4 && playerCard.value <= 7) {
                return true; // draw
            }
            else {
                return false; // dont draw
            }
        }
        // banker 4, player third is [2,7] or did NOT draw third
        if (handTotal(hand) == 4) {
            if (playerCard.value >= 2 && playerCard.value <= 7) {
                return true; // draw
            }
            else {
                return false; // dont draw
            }
        }
        if (handTotal(hand) == 3) {
            if (playerCard.value == 8) {
                return false; // dont draw
            }
            else {
                return true; // draw
            }
        }
    }
    return false; // dont draw, bankers hand >= 7
}



// if user want's to keep playing with same shoe (same decks), they can quickly play another hand
void prePostGame2(int &ovrMoney, vector<BaccaratCard> deckVec, int &vecIndex) {
    int game = 4; // baccarat
    cout << endl;
    if (vecIndex > 120) {
        cout << "You're almost out of cards and it is time for a new shoe" << endl;
        cout << "You are being taken to the home menu, you may return with a newly shuffled deck" << endl;
        postGameOptions(ovrMoney, game);
    }
    cout << "Press R to quick-play again with same shoe" << endl;
    cout << "Press M to see post-game menu, you may return with a newly shuffled deck" << endl;
    while(1) {
        cout << "Your Choice --> ";
        string userChoice;
        cin >> userChoice;
        if ((userChoice[0] == 'R') && (userChoice.size() == 1)) {
            cout << endl;
            Game2(ovrMoney, deckVec, vecIndex);
        }
        else if ((userChoice[0] == 'M') && (userChoice.size() == 1)) {
            postGameOptions(ovrMoney, game);
        }
        else {
            cout << "Invalid Input, Try again: ";
        }
    }
}




// plays the game (Baccarat)
void Game2(int &ovrMoney, vector<BaccaratCard> deckVec, int vecIndex) {
    cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
    int betChoice = 0;
    int decision; 
    errorHandle3(betChoice, 1, 2000);
    cout << endl;
    ovrMoney -= betChoice;
    cout << "Enter who you would like to bet on" << endl;
    cout << "Press P for Player" << endl;
    cout << "Press B for Banker" << endl;
    cout << "Press D for the outcome to the game to be draw" << endl;
    while (1)
    {
        cout << "Your Choice --> ";
        string userChoice;
        cin >> userChoice;
        if ((userChoice[0] == 'P') && (userChoice.size() == 1)) {
            decision = 1; // bet on the player 
            break;

        }
        if ((userChoice[0] == 'B') && (userChoice.size() == 1)) {
            decision = 2; // bet on the banker 
            break;
        }
        else if ((userChoice[0] == 'D') && (userChoice.size() == 1)) {
            decision = 3; // bet on a draw
            break;
        }
        else
        {
            cout << "Invalid Input, Try again: ";
            continue;
        }
    }
    cout << "...Dealing..." << endl << endl;
    BaccaratCard playerCard1 = deckVec[++vecIndex];
    BaccaratCard playerCard2 = deckVec[++vecIndex];
    BaccaratCard bankerCard1 = deckVec[++vecIndex];
    BaccaratCard bankerCard2 = deckVec[++vecIndex];
    vector<BaccaratCard> playerHandVec;
    vector<BaccaratCard> bankerHandVec;
    playerHandVec.push_back(playerCard1);
    playerHandVec.push_back(playerCard2);
    bankerHandVec.push_back(bankerCard1);
    bankerHandVec.push_back(bankerCard2);
    cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
    cout << "The Player holds:                    " << printCardLong2(playerCard1) << "  and  " << printCardLong2(playerCard2) << endl;
    cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
    cout << "The Banker holds:                    " << printCardLong2(bankerCard1) << "  and  " << printCardLong2(bankerCard2) << endl;
    cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
    cout << endl;
    cout << "The Player's hand has a value of " << handTotal(playerHandVec) << endl;
    cout << "The Banker's hand has a value of " << handTotal(bankerHandVec) << endl;
    cout << "Press any key to continue" << endl;
    while(1) {
        string userChoice;
        cin >> userChoice;
        break;
    }


    bool naturalWin = false; 
    // natural win logic
    if (handTotal(playerHandVec) == 8 || handTotal(playerHandVec) == 9 || handTotal(bankerHandVec) == 8 || handTotal(bankerHandVec) == 9)  {
        naturalWin = true; 
    }

    // draw third logic 
    if (naturalWin == false) {
        BaccaratCard playerCard3;
        BaccaratCard bankerCard3;
        bool playerDraw = evaluatePlayerDraw(playerHandVec);
        bool playerDidDraw = false;
        bool bankerDidDraw = false;
        if (playerDraw) {
            playerCard3 = deckVec[++vecIndex];
            playerHandVec.push_back(playerCard3);
            playerDidDraw = true; 
        }
        if (playerDidDraw) { // player drew a third card
            if (evaluateBankerDraw(bankerHandVec, playerCard3)) {
                bankerCard3 = deckVec[++vecIndex];
                bankerHandVec.push_back(bankerCard3);
                bankerDidDraw = true;
            }
        }
        else { // player did not draw a third card 
        // if bank 5 or less, draw 3rd 
            if (handTotal(bankerHandVec) <= 5) {
                bankerCard3 = deckVec[++vecIndex];
                bankerHandVec.push_back(bankerCard3);
                bankerDidDraw = true; 
            }
        }

        if (playerDidDraw) {
            cout << endl << "The Player must draw a third card" << endl;
            cout << "Press any key to continue" << endl;
            while(1) {
                string userChoice;
                cin >> userChoice;
                break;
            }
            cout << "...Dealing..." << endl << endl;
            cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
            cout << "The Player now holds:                    " << printCardLong2(playerCard1) << ",  " << printCardLong2(playerCard2);
            cout << "  and  " << printCardLong2(playerCard3) << endl;
            cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl << endl;
            cout << "The Player's hand has a value of " << handTotal(playerHandVec) << endl;
            cout << "Press any key to continue" << endl;
            while(1) {
                string userChoice;
                cin >> userChoice;
                break;
            }
        }
        if (bankerDidDraw) {
            cout << endl << "The Banker must draw a third card" << endl;
            cout << "Press any key to continue" << endl;
            while(1) {
                string userChoice;
                cin >> userChoice;
                break;
            }
            cout << "...Dealing..." << endl << endl;
            cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
            cout << "The Banker now holds:                    " << printCardLong2(bankerCard1) << ",  " << printCardLong2(bankerCard2);
            cout << "  and  " << printCardLong2(bankerCard3) << endl;
            cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl << endl;
            cout << "The Bankers's hand has a value of " << handTotal(bankerHandVec) << endl;
        }
    }


    cout << endl << "The outcome of the game was:" << endl;
    cout << "Player: " << handTotal(playerHandVec) << endl;
    cout << "Banker: " << handTotal(bankerHandVec) << endl << endl;
    cout << "Therefore... ";
    if (whoWon(playerHandVec, bankerHandVec) == "Player") {
        cout << "Player won" << endl;
        if (decision == 1) {
            ovrMoney += betChoice;
            ovrMoney += betChoice;
            int winning = betChoice; 
            cout << "You bet on the Player" << endl;
            cout << "Congratuations! You have won $" << winning << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "You did not bet on the Player" << endl;
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        prePostGame2(ovrMoney, deckVec, vecIndex);
    }
    if (whoWon(playerHandVec, bankerHandVec) == "Banker") {
        cout << "Banker won" << endl;
        if (decision == 2) {
            ovrMoney += betChoice;
            ovrMoney += betChoice;
            int winning = betChoice; 
            cout << "You bet on the Banker" << endl;
            cout << "Congratuations! You have won $" << winning << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "You did not bet on the Banker" << endl;
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        prePostGame2(ovrMoney, deckVec, vecIndex);
    }
    if (whoWon(playerHandVec, bankerHandVec) == "Draw") {
        cout << "Resulted in a draw" << endl;
        if (decision == 3) {
            ovrMoney += betChoice;
            ovrMoney += betChoice * 8;
            int winning = betChoice; 
            cout << "You bet on a draw" << endl;
            cout << "Congratuations! You have won $" << winning << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "You did not bet on a draw" << endl;
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        prePostGame2(ovrMoney, deckVec, vecIndex);
    }

}



//overall starting point for the game
void playBaccarat(int &ovrMoney) {
    int vecIndex = -1;
    vector<BaccaratCard> deckVec;
    cout << endl;
    displayBaccaratMenu();
    // populates the pool of card pulls to 3 decks effectively 
    readFile2(deckVec);
    readFile2(deckVec);
    readFile2(deckVec);
    shuffleDeck2(deckVec);
    Game2(ovrMoney, deckVec, vecIndex);
}
