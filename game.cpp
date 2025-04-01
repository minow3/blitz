#include <iostream>

using namespace std;

void Play() {
    cout << "Play" << endl;
    
// takes user name
  string Username;
  cout << "Enter your username:  ";
  cin>>Username; 
  cout << "Your username is: " << Username << endl;


    // at the end writes name and score to leaderboard

}

void Rules() {
    cout << "Rules" << endl;

    // describe rules of the game
    
    cout << "1. (GAMEPLAY.)" << endl; 
    cout << "2. Players take turns drawing 1 card from deck." << endl; 
    cout << "3. You may also swap a card (Max of three cards.)" << endl; 
    cout << "4. A player can knock end of round when they believe they have the highest hand." << endl; 
    cout << "5. Everyone gets one last turn after a knock." << endl; 
    cout << "6. If a player has 31 they must say immedietly and the round ends."  << endl; 
    
}

void Leaderboard() {
    cout << "Leaderboard" << endl;

    // opens leaderboard.txt file
    // reads only first 5 or 10 records
    // use <fstream> ?????
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

         cin>>choice; 

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
