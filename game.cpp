#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <ctime>

using namespace std;

// Function to generate card deck
vector<string> createDeck() {
    vector<string> cards = {
        "AC", "AD", "AH", "AS",
        "KC", "KD", "KH", "KS",
        "QC", "QD", "QH", "QS",
        "JC", "JD", "JH", "JS",
        "10C", "10D", "10H", "10S",
        "9C", "9D", "9H", "9S",
        "8C", "8D", "8H", "8S",
        "7C", "7D", "7H", "7S",
        "6C", "6D", "6H", "6S",
        "5C", "5D", "5H", "5S",
        "4C", "4D", "4H", "4S",
        "3C", "3D", "3H", "3S",
        "2C", "2D", "2H", "2S"
    };
    random_device rd;
    mt19937 g(rd());
    shuffle(cards.begin(), cards.end(), g);
    return cards;
}

// Get card value (simplified for now)
int getCardValue(const string& card) {
    if (card.substr(0, 2) == "10") return 10;
    char rank = card[0];
    if (rank == 'A') return 11;
    if (rank == 'K' || rank == 'Q' || rank == 'J') return 10;
    return rank - '0';
}

// Get hand cards score
int getHandScore(const vector<string>& hand) {
    int score = 0;
    for (const auto& card : hand) {
        score += getCardValue(card);
    }
    return score;
}

// Swap card function
void swapCard(vector<string>& hand, string& tableCard, const string& newCard, int index) {
    tableCard = hand[index];
    hand[index] = newCard;
}

// Player's turn
bool playerTurn(vector<string>& hand, string& tableCard, vector<string>& deck) {
    cout << "\nYour hand: ";
    for (int i = 0; i < 3; ++i) cout << "[" << i + 1 << "] " << hand[i] << "  ";
    cout << "\nTable card: " << tableCard << endl;

    cout << "Draw from (1) Deck or (2) Table? ";
    int choice;
    cin >> choice;

    string drawnCard;
    if (choice == 1 && !deck.empty()) {
        drawnCard = deck.back();
        deck.pop_back();
    } else if (choice == 2) {
        drawnCard = tableCard;
    } else {
        cout << "Invalid choice or empty deck. Skipping turn.\n";
        return false;
    }

    cout << "You drew: " << drawnCard << endl;
    cout << "Which card to replace (1-3)? or 0 to keep your hand: ";
    int replace;
    cin >> replace;

    if (replace >= 1 && replace <= 3) {
        swapCard(hand, tableCard, drawnCard, replace - 1);
    } else {
        // If kept hand, discard the drawn card to table
        tableCard = drawnCard;
    }

    int score = getHandScore(hand);
    cout << "Your current score: " << score << endl;

    if (score == 31) {
        cout << "You hit 31! You win instantly!\n";
        return true;
    }

    cout << "Do you want to knock? (y/n): ";
    char knock;
    cin >> knock;
    return (knock == 'y' || knock == 'Y');
}

// Computer's turn (simple logic)
bool computerTurn(vector<string>& hand, string& tableCard, vector<string>& deck) {
    int minIndex = 0;
    int minVal = getCardValue(hand[0]);
    for (int i = 1; i < 3; ++i) {
        if (getCardValue(hand[i]) < minVal) {
            minVal = getCardValue(hand[i]);
            minIndex = i;
        }
    }

    string drawnCard;
    if (!deck.empty()) {
        drawnCard = deck.back();
        deck.pop_back();
    } else {
        drawnCard = tableCard;
    }

    if (getCardValue(drawnCard) > minVal) {
        swapCard(hand, tableCard, drawnCard, minIndex);
    } else {
        tableCard = drawnCard;
    }

    int score = getHandScore(hand);
    cout << "Computer's turn. Score: " << score << endl;
    return (score >= 27); // Knock if 27+
}

// Game function
void Play() {
    string username;
    cout << "Enter your username: ";
    cin >> username;

    vector<string> deck = createDeck();
    vector<string> playerHand, computerHand;
    string tableCard;

    // Deal 3 cards to each
    for (int i = 0; i < 3; ++i) {
        computerHand.push_back(deck.back());
        deck.pop_back();
        playerHand.push_back(deck.back());
        deck.pop_back();
    }
    tableCard = deck.back();
    deck.pop_back();

    bool gameOver = false;
    bool playerKnocked = false;
    bool computerKnocked = false;

    while (!gameOver) {
        // Refill deck from table if deck is empty
        if (deck.empty()) {
            deck.push_back(tableCard);
            random_shuffle(deck.begin(), deck.end());
        }

        computerKnocked = computerTurn(computerHand, tableCard, deck);
        if (getHandScore(computerHand) == 31) {
            cout << "Computer hit 31! Computer wins!\n";
            return;
        }
        if (computerKnocked) {
            cout << "Computer knocks! You get one last turn.\n";
            playerKnocked = playerTurn(playerHand, tableCard, deck);
            gameOver = true;
        }

        if (!gameOver) {
            playerKnocked = playerTurn(playerHand, tableCard, deck);
            if (getHandScore(playerHand) == 31) {
                cout << username << " hit 31! You win instantly!\n";
                return;
            }
            if (playerKnocked) {
                cout << username << " knocked! Computer gets one last turn.\n";
                computerKnocked = computerTurn(computerHand, tableCard, deck);
                gameOver = true;
            }
        }
    }

    int playerScore = getHandScore(playerHand);
    int computerScore = getHandScore(computerHand);

    cout << "\nFinal Scores:\n";
    cout << username << ": " << playerScore << endl;
    cout << "Computer: " << computerScore << endl;

    if (playerScore > computerScore)
        cout << username << " wins!\n";
    else if (computerScore > playerScore)
        cout << "Computer wins!\n";
    else
        cout << "It's a tie!\n";

    ofstream out("leaderboard.txt", ios::app);
    if (out) {
        out << username << " - " << playerScore << " points\n";
        out.close();
    }
}

void Rules() {
    cout << "\n--- Game Rules ---\n";
    cout << "1. Goal is to reach 31 points with 3 cards.\n";
    cout << "2. You can draw from the deck or the table.\n";
    cout << "3. You can knock on your turn if you feel confident.\n";
    cout << "4. If someone gets 31, they win immediately.\n";
    cout << "5. After a knock, the other player gets one last turn.\n\n";
}

void Leaderboard() {
    ifstream in("leaderboard.txt");
    cout << "\n--- Leaderboard ---\n";
    if (!in) {
        cout << "No scores recorded yet.\n";
        return;
    }
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
    cout << endl;
}

int main() {
    char choice;
    while (true) {
        cout << "\nLet's play Blitz\n";
        cout << "1 - Play\n2 - Rules\n3 - Leaderboard\n4 - Exit\n> ";
        cin >> choice;

        switch (choice) {
            case '1': Play(); break;
            case '2': Rules(); break;
            case '3': Leaderboard(); break;
            case '4': return 0;
            default: cout << "Invalid choice.\n";
        }
    }
    return 0;
}
