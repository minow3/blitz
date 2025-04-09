#include <iostream>

using namespace std;


//Shuffle deck
void shuffleDeck(vector<string>& deck) {
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

// Function to deal three cards per player per round
void dealCards(vector<string>& deck) {
    int player = 1;  // Track player number

    while (deck.size() >= 6) {  // Each round needs 6 cards (3 per player)
        cout << "Round starts:" << endl;

        for (int i = 0; i < 2; ++i) {  // Loop for 2 players
            cout << "Player " << (i + 1) << " gets: ";
            for (int j = 0; j < 3; ++j) {  
                cout << deck.back() << " ";  // Deal from the back of the deck
                deck.pop_back();  // Remove the card from the deck
            }
            cout << endl;
        }
        cout << "Remaining cards in deck: " << deck.size() << endl;
        cout << "-----------------------------" << endl;
    }

    // If any cards are left but not enough for another round
    if (!deck.empty()) {
        cout << "Final remaining cards (less than 6): ";
        for (const auto& card : deck) {
            cout << card << " ";
        }
        cout << endl;
        deck.clear();  // Empty the deck
    }

    cout << "Game over! No more cards left in the deck." << endl;
}

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

     vector<string> cards = {
        "AC", "AD", "AH", "AS", "KC", "KD", "KH", "KS",
        "QC", "QD", "QH", "QS", "JC", "JD", "JH", "JS",
        "10C", "10D", "10H", "10S", "9C", "9D", "9H", "9S",
        "8C", "8D", "8H", "8S", "7C", "7D", "7H", "7S",
        "6C", "6D", "6H", "6S", "5C", "5D", "5H", "5S",
        "4C", "4D", "4H", "4S", "3C", "3D", "3H", "3S",
        "2C", "2D", "2H", "2S"
    };

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
                //Shuffle cards
                shuffleDeck(cards);
                //deal cards
                dealCards(cards);
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
