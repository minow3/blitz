#include <iostream>
#include <conio.h> // Required for windows to catch user input
using namespace std;

void Play() {
    cout << "Play" << endl;
    // takes user name
    // at the end writes name and score to leaderboard

}

void Rules() {
    cout << "Rules" << endl;

    // describe rules of the game
    // and small description how to play
}

void Leaderboard() {
    cout << "Leaderboard" << endl;

    // opens leaderboard.txt file
    // reads only first 5 or 10 records
}

void computerBrains() {
    // create computer brains
}

void cardDeck() {
    // create card deck
}



int main() {

    char choice;

    while(true) {
        cout << "Let's play Blitz" << endl;
        cout << " " << endl;
        cout << " 1 - Play" << endl;
        cout << " 2 - Rules" << endl;
        cout << " 3 - Leaderboard" << endl;
        cout << " 4 - Exit" << endl;
        cout << " " << endl;

        choice = _getch(); //take user input

        switch(choice) {
            case '1':
                Play();
                break;
            case '2':
                Rules();
                break;
            case '3':
                Leaderboard();
                break;
            case '4':
                return 0;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }

    return 0;
}