/************************
Blackjack
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
struct Card {
    string valueName;
    string suit;
    int value;
};



string printCardLong(Card card);
string printCardShort(Card card);
void playBlackjack(int &ovrMoney);
void Game(int &ovrMoney, vector<Card> decVeck, int &vecIndex);
void errorHandle2(int &choice, int lowerBound, int upperBound);



// shuffles a deck of cards, or multiple decks at once 
void shuffleDeck(vector<Card> &deckVec) {
    random_device rd;
    mt19937 rng(rd()); // Mersenne Twister
    shuffle(deckVec.begin(), deckVec.end(), rng);
}



// if its user's first turn, they have option to double down
void turnNumber(int dbl) {
    if (dbl == 1) {
        cout << endl;
        cout << "Would you like to hit, stand or double?" << endl;
        cout << "Press 'H' to hit" << endl;
        cout << "Press 'S' to stand" << endl;
        cout << "Press 'D' to double" << endl;
    }
    else {
        cout << endl;
        cout << "Would you like to hit or stand?" << endl;
        cout << "Press 'H' to hit" << endl;
        cout << "Press 'S' to stand" << endl;
    }
}



// deals with user input in regards to in game descions (hit, stand, double)
void hitOrStand(int &descision, int dbl, int &ovrMoney, int betChoice) {
    while (1)
    {
        cout << "Your Choice --> ";
        string userChoice;
        cin >> userChoice;
        if ((dbl == 1) && (userChoice[0] == 'D') && (userChoice.size() == 1)) {
            descision = 3;
            break;

        }
        if ((userChoice[0] == 'H') && (userChoice.size() == 1)) {
            descision = 1;
            break;
        }
        else if ((userChoice[0] == 'S') && (userChoice.size() == 1)) {
            descision = 2;
            break;
        }
        else
        {
            cout << "Invalid Input, Try again: ";
            continue;
        }
    }
}



// if user want's to keep playing with same shoot (same decks), they can quickly play another hand
void prePostGame(int &ovrMoney, vector<Card> deckVec, int &vecIndex) {
    int game = 2; // blackjack
    cout << endl;
    if (vecIndex > 120) {
        cout << "You're almost out of cards and it is time for a new shoot" << endl;
        cout << "You are being taken to the home menu, you may return with a newly shuffled deck" << endl;
        postGameOptions(ovrMoney, game);
    }
    cout << "Press R to quick-play again with same shoot" << endl;
    cout << "Press M to see post-game menu, you may return with a newly shuffled deck" << endl;
    while(1) {
        cout << "Your Choice --> ";
        string userChoice;
        cin >> userChoice;
        if ((userChoice[0] == 'R') && (userChoice.size() == 1)) {
            cout << endl;
            Game(ovrMoney, deckVec, vecIndex);
        }
        else if ((userChoice[0] == 'M') && (userChoice.size() == 1)) {
            postGameOptions(ovrMoney, game);
        }
        else {
            cout << "Invalid Input, Try again: ";
        }
    }
}



// handles the users bet, in regard to the Casino's maximum
void errorHandle2(int &choice, int lowerBound, int upperBound) {
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



// decifers if dealer or player has blackjack
bool hasBlackjack(Card card1, Card card2) { 
    if (card1.valueName == "Ace") {
        if (card2.value == 10) {
            return true;
        }
    }
    if (card1.value == 10) {
        if (card2.valueName == "Ace") {
            return true;
        }
    }
    return false; // no blackjack 
}



// if dealer has blackjack, game is prematurely ended here
void checkDealerBlackjack (Card dealerCard1, Card dealerCard2, bool playerBJ, int &ovrMoney, int betChoice, vector<Card> deckVec, int &vecIndex) {
    if ((dealerCard1.valueName == "Ace") || (dealerCard1.value == 10)) {
        cout << "Checking for blackjack..." << endl;
        cout << "...";
        if (hasBlackjack(dealerCard1, dealerCard2) == true) {
            if (playerBJ == false) {
                cout << "The dealer's second card is " << printCardLong(dealerCard2) << " and has Blackjack!" << endl;
                cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
                prePostGame(ovrMoney, deckVec, vecIndex);
            }
            if (playerBJ == true) {
                ovrMoney += betChoice;
                cout << "The dealer's second card is " << printCardLong(dealerCard2) << " and has Blackjack!" << endl;
                cout << "This is a push and you keep your money, your balance now stands at $" << ovrMoney << endl;
                prePostGame(ovrMoney, deckVec, vecIndex);
            }
        }
        else {
            cout << "No one's home!" << endl;
        }
    }
}



// prints the details of a given card in english
string printCardLong(Card card) {
    return "(" + card.valueName + "-" + card.suit + ")";
}



// prints the details of a given card in character/numerical format
string printCardShort(Card card) {
    return string(1, card.valueName[0]) + string(1, card.suit[0]);
}



// displays the rules of the game to the user
void displayBlackjackMenu() {
    cout << "Hello! Welcome to Blackjack!" << endl;
    cout << "Rules below: " << endl;
    cout << "             Your aim is to get closer to 21 than the dealer, without exceeding it" << endl;
    cout << "             On any value of your inital cards you may 'hit' or 'stand'" << endl;
    cout << "             After standing, the dealer reveals their second card and hits until they reach 17+" << endl;
    cout << "             The dealer will stand on a soft 17" << endl;
    cout << "             In this casino, we do not allow splitting or offer insurance" << endl;
    cout << "             The game will be played with 3 decks" << endl;
    cout << "             Finally, Blackjack pays 3:2 (rounded down if bet was an odd number)" << endl << endl;
}



// reads file, decks are filled into vector
void readFile(vector<Card> &deckVec) {
    ifstream inFS;
    inFS.open("deckOfCards.txt");
    if (!inFS.is_open()) {
        cout << "file not read";
        exit(0);
    }
    string line;
    while (getline(inFS, line)) {
        Card card;
        stringstream ss(line);
        string value;
        string suit;
        ss >> value >> suit;
        card.valueName = value;
        card.suit = suit;
        if (value == "Ace") {
            card.value = 11;
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
            card.value = 10;
        }
        else if (value == "Jack") {
            card.value = 10;
        }
        else if (value == "Queen") {
            card.value = 10;
        }
        else if (value == "King") {
            card.value = 10;
        }
        else {
            card.value = 0;
            cout << "Error, could not assign numerical alue to the card" << endl;
        }
        deckVec.push_back(card);
    }
    inFS.close();
}



// carries out each step of the game as it is played
void Game(int &ovrMoney, vector<Card> deckVec, int &vecIndex) {
    cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
    int betChoice = 0;
    errorHandle2(betChoice, 1, 2000);
    cout << endl;
    ovrMoney -= betChoice;
    cout << "...Dealing..." << endl << endl;
    Card playerCard1 = deckVec[++vecIndex];
    Card dealerCard1 = deckVec[++vecIndex];
    Card playerCard2 = deckVec[++vecIndex];
    Card dealerCard2 = deckVec[++vecIndex];
    vector<Card> playerHandVec;
    vector<Card> dealerHandVec;
    playerHandVec.push_back(playerCard1);
    playerHandVec.push_back(playerCard2);
    playerHandVec.push_back(dealerCard1);
    playerHandVec.push_back(dealerCard2);
    cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
    cout << "You hold:                    " << printCardLong(playerCard1) << "  and  " << printCardLong(playerCard2);
    bool playerBJ = false;
    if (hasBlackjack(playerCard1, playerCard2) == true) {
        playerBJ = true;
        cout << "  -  Blackjack!";
    }
    cout << endl << endl;
    cout << "The dealer is showing:       " << printCardLong(dealerCard1) << endl;
    cout << " -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  " << endl;
    checkDealerBlackjack(dealerCard1, dealerCard2, playerBJ, ovrMoney, betChoice, deckVec, vecIndex);

    // Blackjack! 3:2 winnings
    if (playerBJ == true) { 
        ovrMoney += betChoice;
        ovrMoney += betChoice * 1.5;
        int winning = betChoice * 1.5;
        cout << "Congratuations! You have won $" << winning << " and your balance now stands at $" << ovrMoney << endl;
        prePostGame(ovrMoney, deckVec, vecIndex);
    }

    // loop for player playing the game
    int descision = 0;
    int dbl = 0;
    int playerAce = 0;
    int dealerAce = 0;
    int playerValue = playerCard1.value + playerCard2.value;
    int dealerValue = dealerCard1.value + dealerCard2.value; // figure aces here ig idfk 
    if (playerCard1.value == 11) {
        playerAce++;
    }
    if (playerCard2.value == 11) {
        playerAce++;
    }
    if (dealerCard1.value == 11) {
        dealerAce++;
    }
    if (dealerCard2.value == 11) {
        dealerAce++;
    }
    // deals with pocket aces
    if ((playerCard1.value == 11) && (playerCard2.value == 11)) {
        playerValue -= 10;
        playerAce--;
    }
    if ((dealerCard1.value == 11) && (dealerCard2.value == 11)) {
        dealerValue -= 10;
        dealerAce--;
    }

    while(1) {
        if (playerValue == 21) {
            cout << " ...nice!";
            break;
        }
        descision = 0;
        dbl++;
        turnNumber(dbl);
        hitOrStand(descision, dbl, ovrMoney, betChoice);
        if ((descision == 1) || (descision == 3)) { // Hit (3 is double)
            Card playerCard = deckVec[++vecIndex];
            playerHandVec.push_back(playerCard);
            playerValue += playerCard.value;
            if (playerCard.value == 11) {
                playerAce++;
            }
            if ((playerAce != 0) && (playerValue > 21)) {
                playerValue -= 10;
                playerAce--;
            }
            cout << endl;
            cout << "Your next card is " << printCardLong(playerCard) << " - hand value: " << playerValue << endl;
            if ((playerAce == 0) && (playerValue > 21)) {
                // double the money spent and potential winnings
                if (descision == 3) {
                    ovrMoney -= betChoice;
                    betChoice += betChoice;
                }
                cout << endl;
                cout << "Too many!" << endl;
                cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
                prePostGame(ovrMoney, deckVec, vecIndex);
                break;
            }
            // double the money spent and potential winnings
            if (descision == 3) {
                ovrMoney -= betChoice;
                betChoice += betChoice;
                break;
            }
        }
        if (descision == 2) { // Stand
            break;
        }
    }




    // loop dealers hand 
    cout << endl;
    cout << "Press any key to continously reveal the dealers card's until a value 17 or higher is achieved" << endl;
    while(1) {
        string userChoice;
        cin >> userChoice;
        break;
    }
    cout << "The dealers second card is: " << printCardLong(dealerCard2) << " - hand value: " << dealerValue << endl;
    while (dealerValue < 17) {
        Card dealerCard = deckVec[++vecIndex];
        dealerHandVec.push_back(dealerCard);
        dealerValue += dealerCard.value;
        if (dealerCard.value == 11) {
            dealerAce++;
        }
        if ((dealerAce != 0) && (dealerValue > 21)) { // or 17+ cuz dealer will stand there (MIGHT ALREADY BE GOOD)
            dealerValue -= 10;
            dealerAce--;
        }
        while(1) {
            string userChoice;
            cin >> userChoice;
            break;
        }
        cout << "The dealer's next card is: " << printCardLong(dealerCard) <<  " - hand value: " << dealerValue << endl;
    }



    cout << endl;
    cout << "The dealer's hand has the value of " << dealerValue << endl;
    if (dealerValue > 21) {
        cout << "Bust!" << endl;
        ovrMoney += betChoice;
        ovrMoney += betChoice;
        cout << "Congratuations! You have won $" << betChoice << " and your balance now stands at $" << ovrMoney << endl;
        prePostGame(ovrMoney, deckVec, vecIndex);
    }
    cout << "The player's hand has the value of " << playerValue << endl << endl;
    // push, money back
    if (dealerValue == playerValue) {
        ovrMoney += betChoice;
        cout << "This is a push and you keep your money, your balance now stands at $" << ovrMoney << endl;
        prePostGame(ovrMoney, deckVec, vecIndex);
    }
    // L
    else if (dealerValue > playerValue) {
        cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        prePostGame(ovrMoney, deckVec, vecIndex);
    }
    // W (make sure this is actually facts)
    else {
        ovrMoney += betChoice;
        ovrMoney += betChoice;
        cout << "Congratuations! You have won $" << betChoice << " and your balance now stands at $" << ovrMoney << endl;
        prePostGame(ovrMoney, deckVec, vecIndex);
    }
    
    prePostGame(ovrMoney, deckVec, vecIndex);

}



//overall starting point for the game
void playBlackjack(int &ovrMoney) {
    int vecIndex = -1;
    vector<Card> deckVec;
    displayBlackjackMenu();
    // populates the pool of card pulls to 3 decks effectively 
    readFile(deckVec);
    readFile(deckVec);
    readFile(deckVec);
    shuffleDeck(deckVec);
    Game(ovrMoney, deckVec, vecIndex);
}