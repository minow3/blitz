//Name: Tomas Bendaravicius
//Date: 03/04/2025
//Function: create multiple functions for deck of cards to shuffle and deal

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Function to shuffle the deck
void shuffleDeck(vector<string>& deck) {
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

// Function to deal three cards
void dealCards(const vector<string>& deck) {
    cout << "Dealt cards: " << deck[0] << ", " << deck[1] << ", " << deck[2] << endl;
}

int main() {
    vector<string> cards = {
        "AC", "AD", "AH", "AS", "KC", "KD", "KH", "KS",
        "QC", "QD", "QH", "QS", "JC", "JD", "JH", "JS",
        "10C", "10D", "10H", "10S", "9C", "9D", "9H", "9S",
        "8C", "8D", "8H", "8S", "7C", "7D", "7H", "7S",
        "6C", "6D", "6H", "6S", "5C", "5D", "5H", "5S",
        "4C", "4D", "4H", "4S", "3C", "3D", "3H", "3S",
        "2C", "2D", "2H", "2S"
    };

    shuffleDeck(cards);
    dealCards(cards);

    return 0;
}