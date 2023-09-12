#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include "roulette.h"
#include "blackjack.h"
using namespace std;


// displays the main menu
void displayMenu() {
    cout << "Hello! Welcome to the Virtual Casino!" << endl;
    cout << "Press '1' to play BlackJack" << endl;
    cout << "Press '2' to play Roulette" << endl;
    cout << "Press 'Q' to quit" << endl;
}



// functionality for the main menu, allows user to choose which game to play
void mainMenu(int &ovrMoney) {
    displayMenu();
    while (1)
    {
        cout << "Your Choice --> ";
        string userChoice;
        cin >> userChoice;
        if ((userChoice[0] == '1') && (userChoice.size() == 1)) {
            playBlackjack(ovrMoney);
            break;
        }
        else if ((userChoice[0] == '2') && (userChoice.size() == 1)) {
            playRoulette(ovrMoney);
            break;
        }
        else if ((userChoice[0] == 'Q') && (userChoice.size() == 1)) {
            cout << endl << "Thanks for playing!" << endl;
            cout << "...Exiting..." << endl;
            exit(0);
        }
        else {
            cout << "Invalid Input, Try again: ";
            continue;
        }
    }
}



// menu for after game completion, provides further options for the user
void postGameOptions(int &ovrMoney, int game) { // 1 Roulette, 2 Blackjack
    cout << endl;
    cout << "Thank you for playing!" << endl;
    cout << "Press 'R' to play again" << endl;
    cout << "Press 'M' to change game (return to the main menu)" << endl;
    cout << "Press 'Q' to quit" << endl;
    while(1) {
        cout << "Your Choice --> ";
        string userChoice;
        cin >> userChoice;
        if ((userChoice[0] == 'R') && (userChoice.size() == 1)) {
            if (game == 1) {
                playRoulette(ovrMoney);
            }
            if (game == 2) {
                playBlackjack(ovrMoney);
            }
        }
        else if ((userChoice[0] == 'M') && (userChoice.size() == 1)) {
            cout << endl;
            mainMenu(ovrMoney);
        }
        else if ((userChoice[0] == 'Q') && (userChoice.size() == 1)) {
            cout << endl << "Thanks for playing!" << endl;
            cout << "...Exiting..." << endl;
            exit(0);
        }
        else {
            cout << "Invalid Input, Try again: ";
        }
    }
}



int main() {
    srand(time(0));
    int ovrMoney = 0;
    mainMenu(ovrMoney);
    return 0;
}

