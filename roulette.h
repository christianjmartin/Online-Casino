/*********************
Roulette
*********************/

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
using namespace std;



void postGameOptions(int &ovrMoney, int game);



// handles user character input, and any possible errors from it
void errorCharHandle(char &choice, char target) {
    while (1) {
        char userChoice;
        cin >> userChoice;

        // Check if the input operation fails or if it is not equal to the target
        if (cin.fail() || userChoice != target) {
            cout << "Invalid Input. Try again: ";

            // Clear the error state of cin and ignore the incorrect input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Input is valid
        choice = userChoice;
        cout << endl;
        break;
    }
}



// handles numerical user input in a needed range
void errorHandle(int &choice, int lowerBound, int upperBound, string specific) {
    while (1) {
        if (specific == "$") { 
            cout << "Your Choice --> $";
        }
        else if (specific == "") {
            cout << "";
        }
        else {
            cout << "Your Choice " << specific <<  "--> ";
        }
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



// given any given number, decifers what color it is on the spinner
void findColor(int num, set<int> redSet, set<int> blackSet, set<int> greenSet, string& color) {
    if (redSet.count(num) == 1) {
        color = "Red";
    }
    else if (blackSet.count(num) == 1) {
        color = "Black";
    }
    else if (greenSet.count(num) == 1) {
        color = "Green";
    }
    else {
        color = "ERROR NUM DOES NOT EXIST";
    }
}



// displays 10 different betting categories
void displayOptions() {
    cout << "Hello! Welcome to Roulette!" << endl;
    cout << "The goal is simple, pick a bet from the options listed below, and spin when you are ready!" << endl << endl;
    cout << "OPTION 1: pick a single number" << endl; // done
    cout << "OPTION 2: pick two numbers" << endl; // done
    cout << "OPTION 3: pick three numbers" << endl; // done 
    cout << "OPTION 4: pick four numbers" << endl; // done
    cout << "OPTION 5: pick six numbers" << endl; // done
    cout << "OPTION 6: pick a column (12 numbers)" << endl;
    cout << "OPTION 7: pick the odds" << endl;
    cout << "OPTION 8: pick the evens" << endl,
    cout << "OPTION 9: pick red" << endl;
    cout << "OPTION 10: pick black" << endl;
}



// reads file, numbers are filled into sets based on color
void readFile(set<int> &redNumbers, set<int> &greenNumbers, set<int> &blackNumbers, set<int> &allNumbers) {
    ifstream inFS;
    inFS.open("Roulette.txt");
    if (!inFS.is_open()) {
        cout << "file not read";
        exit(0);
    }
    string line;
    while (getline(inFS, line)) {
        stringstream ss(line);
        string color;
        int number;
        ss >> color >> number;
        allNumbers.insert(number);
        if (color == "Red") {
            redNumbers.insert(number);
        } 
        if (color == "Green") {
            greenNumbers.insert(number);
        }
        else if (color == "Black") {
            blackNumbers.insert(number);
        }
    }
    inFS.close();
    // cout << "red: ";
    // for (int i : redNumbers) {
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << "black: ";
    // for (int i : blackNumbers) {
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << "green: ";
    // for (int i : greenNumbers) {
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << "all nums: ";
    // for (int i : allNumbers) {
    //     cout << i << " ";
    // }
}



// carries out each step of the game as it is played
void playRoulette(int &ovrMoney) { 
    set<int> redNumbers;
    set<int> blackNumbers;
    set<int> greenNumbers;
    set<int> allNumbers;
    string empty = "";
    int game = 1; // roulette
    int choice = 0;
    displayOptions();
    string s = "(1-10)";
    errorHandle(choice, 1, 10, s);
    cout << endl;
    readFile(redNumbers, greenNumbers, blackNumbers, allNumbers);

    if (choice == 1) {  // betting on a single number
        cout << "Enter a single number to bet on" << endl;
        int numChoice = 0;
        string s2 = "(0-36)";
        errorHandle(numChoice, 0, 36, s2);
        // bet and spin
        cout << endl;
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s3 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s3);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar;
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if (winningNum == numChoice) {
            ovrMoney += betChoice;
            ovrMoney += betChoice * 35;
            cout << "Congratuations! You have won $" << betChoice * 35 << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }

    else if (choice == 2) {  // betting on two numbers
        cout << "Enter two unique numbers to bet on" << endl;
        int numChoice[2];
        for (int i = 0; i < 2; ++i) {
            cout << "Number " << (i + 1) << " (0-36) --> ";
            errorHandle(numChoice[i], 0, 36, empty);
            // Check for duplicate numbers
            for (int j = 0; j < i; ++j) {
                if (numChoice[j] == numChoice[i]) {
                    cout << "You've entered a duplicate number. Please enter a unique number" << endl;
                    --i; 
                    break;
                }
            }
        }
        // bet and spin
        cout << endl;
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s4 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s4);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar = '\0';
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if ((winningNum == numChoice[0]) || (winningNum == numChoice[1])) {
            ovrMoney += betChoice;
            ovrMoney += betChoice * 17;
            cout << "Congratulations! You have won $" << betChoice * 17 << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }

    else if (choice == 3) {  // betting on three numbers
        cout << "Enter three unqiue numbers to bet on" << endl;
        int numChoice[3];
        for (int i = 0; i < 3; ++i) {
            cout << "Number " << (i + 1) << " (0-36) --> ";
            errorHandle(numChoice[i], 0, 36, empty);
            // Check for duplicate numbers
            for (int j = 0; j < i; ++j) {
                if (numChoice[j] == numChoice[i]) {
                    cout << "You've entered a duplicate number. Please enter a unique number" << endl;
                    --i; 
                    break;
                }
            }
        }
        // bet and spin
        cout << endl;
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s5 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s5);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar = '\0';
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if ((winningNum == numChoice[0]) || (winningNum == numChoice[1]) || (winningNum == numChoice[2])) {
            ovrMoney += betChoice;
            ovrMoney += betChoice * 11;  
            cout << "Congratulations! You have won $" << betChoice * 11 << " and your balance now stands at $" << ovrMoney << endl;
        } 
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }

    else if (choice == 4) {  // betting on four numbers
        cout << "Enter four unique numbers to bet on" << endl;
        int numChoice[4];
        for (int i = 0; i < 4; ++i) {
            cout << "Number " << (i + 1) << " (0-36) --> ";
            errorHandle(numChoice[i], 0, 36, empty);
            // Check for duplicate numbers
            for (int j = 0; j < i; ++j) {
                if (numChoice[j] == numChoice[i]) {
                    cout << "You've entered a duplicate number. Please enter a unique number" << endl;
                    --i; 
                    break;
                }
            }
        }
        // bet and spin
        cout << endl;
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s6 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s6);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar = '\0';
        errorCharHandle(userChar, 'S');
        //results
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if ((winningNum == numChoice[0]) || (winningNum == numChoice[1]) || 
            (winningNum == numChoice[2]) || (winningNum == numChoice[3])) {
            ovrMoney += betChoice;
            ovrMoney += betChoice * 8;
            cout << "Congratulations! You have won $" << betChoice * 8 << " and your balance now stands at $" << ovrMoney << endl;
        } 
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }

    else if (choice == 5) {  // betting on six numbers
        cout << "Enter six unique numbers to bet on" << endl;
        int numChoice[6];
        for (int i = 0; i < 6; ++i) {
            cout << "Number " << (i + 1) << " (0-36) --> ";
            errorHandle(numChoice[i], 0, 36, empty);
            // Check for duplicate numbers
            for (int j = 0; j < i; ++j) {
                if (numChoice[j] == numChoice[i]) {
                    cout << "You've entered a duplicate number. Please enter a unique number" << endl;
                    --i; 
                    break;
                }
            }
        }
        // bet and spin
        cout << endl;
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s7 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s7);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar = '\0';
        errorCharHandle(userChar, 'S');
        // results
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if ((winningNum == numChoice[0]) || (winningNum == numChoice[1]) || (winningNum == numChoice[2]) || 
            (winningNum == numChoice[3]) || (winningNum == numChoice[4]) || (winningNum == numChoice[5])) {
            ovrMoney += betChoice;
            ovrMoney += betChoice * 5;
            cout << "Congratulations! You have won $" << betChoice * 2 << " and your balance now stands at $" << ovrMoney << endl;
        } 
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }

    else if (choice == 6) { // 2 to 1
        cout << "Which column would you like to choose?" << endl;
        cout << "1: (1-12)" << endl;
        cout << "2: (13-24)" << endl;
        cout << "3: (25-36)" << endl;
        string s8 = "(1-3)"; 
        int colChoice = 0;
        errorHandle(colChoice, 1, 3, s8);
        // bet and spin
        cout << endl;
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s9 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s9);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar;
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if (((colChoice == 1) && (winningNum >= 1) && (winningNum <= 12)) || 
            ((colChoice == 2) && (winningNum >= 13) && (winningNum <= 24)) ||
            ((colChoice == 3) && (winningNum >= 25) && (winningNum <= 36))) {
                ovrMoney += betChoice;
                ovrMoney += betChoice * 2;
                cout << "Congratuations! You have won $" << betChoice * 2 << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }


    else if (choice == 7) { // 1 to 1 
        cout << "You are betting odd numbers" << endl;
        // bet and spin
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s10 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s10);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar;
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if (winningNum % 2 != 0) {
            ovrMoney += betChoice;
            ovrMoney += betChoice;
            cout << "Congratuations! You have won $" << betChoice << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }

    else if (choice == 8) {
        cout << "You are betting even numbers" << endl;
        // bet and spin
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s11 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s11);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar;
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if (winningNum % 2 == 0) {
            ovrMoney += betChoice;
            ovrMoney += betChoice;
            cout << "Congratuations! You have won $" << betChoice << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);
    }

    else if (choice == 9) {
        cout << "You are betting on red" << endl;
        // bet and spin
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s12 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s12);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar;
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if (color == "Red") {
            ovrMoney += betChoice;
            ovrMoney += betChoice;
            cout << "Congratuations! You have won $" << betChoice << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);

    }

    else if (choice == 10) {
        cout << "You are betting on black" << endl;
        // bet and spin
        cout << "Enter the amount you would like to bet (Max bet: $2000)" << endl;
        string s13 = "$";
        int betChoice = 0;
        errorHandle(betChoice, 1, 2000, s13);
        cout << endl;
        ovrMoney -= betChoice;
        cout << "When you are ready, press 'S' to spin: ";
        char userChar;
        errorCharHandle(userChar, 'S');
        // results 
        int winningNum = rand() % 37;
        string color = "";
        findColor(winningNum, redNumbers, blackNumbers, greenNumbers, color); 
        cout << "The ball has landed on: " << color << " " << winningNum << endl;
        if (color == "Black") {
            ovrMoney += betChoice;
            ovrMoney += betChoice;
            cout << "Congratuations! You have won $" << betChoice << " and your balance now stands at $" << ovrMoney << endl;
        }
        else {
            cout << "The odds were not in your favor this time, your balance now stands at $" << ovrMoney << endl;
        }
        postGameOptions(ovrMoney, game);

    }
}