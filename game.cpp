// Team: Blitz
// Members: Tomas, Micheal, William, Archie
// Function: Recreating card game known by the name blitz or 31
// Goals: 1. Game has to be playable. 2. Player can select multiple opponents. 3.Include some advance features
// Advance features:
//  1. Using mt19937 (Mersenne Twister) random generator for his speed and high quality output.
//  2. Create executable file of this game, so saving time for compiling and runing in terminal
//  3. Using pre-increment ++i (increments before assigning)
//  4. Inside function parameters used const to prevent modifications inside and used & sign for pointing into original location in memory, avoiding copying


// ##### LIBRARIES #####
#include <iostream> //Handles input/output
#include <vector> //Creates dinamic arrays
#include <random> //Lets to use random numbers
#include <algorithm> //Algorithmic functions
#include <map> // for the container to store multi value pairs, in some languages known as dictionary
#include <fstream> //File handling, lets read and write

using namespace std;

// ##### DECK OF CARDS #####
vector<string> createDeck()
{   
    // raw deck
    vector<string> cards = {
        "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC", "AC",
        "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD", "AD",
        "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH", "AH",
        "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS", "AS",
    };

    // Randomizing and shuffle deck
    random_device rd;
    mt19937 random(rd()); // Mersenne Twister
    shuffle(cards.begin(), cards.end(), random); //shuffle deck using mt19937
    return cards;
}

// ##### DEALING CARDS #####
vector<string> dealCards(vector<string>& deck, int numCards)
{
    // loops trough deck, and removes if card dealt
    vector<string> hand;
    for (int i = 0; i < numCards; ++i) // increments first then assigns
    {
        hand.push_back(deck.back());
        deck.pop_back();  // Remove the card from the deck
    }
    return hand;
}

// ##### SUITS #####
// Separate suits from cards, further calculation points for hand holding cards
char getSuit(const string& card)
{
    return card.back();
}

// ##### POINTS CALCULATION #####
// Separates strings to determent worth of the cards
int getCardValue(const string& card)
{
    if (card.substr(0, 2) == "10") //working with card has double digit
    {
        return 10;
    }

    char rank = card[0]; // Takes single character to determent values of named cards

    if (rank == 'A') // Gives 11 points for aces
    {
        return 11;
    }
    if (rank == 'K' || rank == 'Q' || rank == 'J') // King, Queen, Jack gets 10 points
    {
        return 10;
    }

    return rank - '0'; // for numeric cards to return number
}

// ##### CALCULATION POINTS ON THE HAND #####
// this function calculates points from cards which are at the hand
// Takes in account that calculation uses only same suits
int getHandScore(const vector<string>& hand)
{
    map<char, int> totalSuit; // total score for each suit
    for (const string& card : hand) //loop cards trough hand
    {
        totalSuit[getSuit(card)] += getCardValue(card); //extracts suit and adds value to totalSuit
    }

    int maxScore = 0;

    for (const auto& [suit, score] : totalSuit) // loop trough map
    {
        maxScore = max(maxScore, score); // keeps maximum score
    }
    return maxScore; //returns best score
}

// ##### SWAP CARD #####
// Swap card from the hand for one from deck or from the table and updates table card that was removed
void swapCard(vector<string>& hand, string& tableCard, string drawnCard, int index)
{
    tableCard = hand[index]; // card from hand goes to table
    hand[index] = drawnCard; // drawn card (table, deck) goes to hand
}

// ##### PLAYER TURN #####
// Controls player turn, player can swap cards from deck or table, shows score and lets knock
bool playerTurn(vector<string>& hand, string& tableCard, vector<string>& deck)
{
    //Prints cards are at hand
    cout << "\n\tYour hand: ";
    for (int i = 0; i < 3; ++i)
    {
        cout << "[" << i + 1 << "] " << hand[i] << "  ";
    }

    // Show current score BEFORE making a move
    int currentScore = getHandScore(hand);
    cout << "\n\tCurrent score: " << currentScore; // current score

    cout << "\n\tTable card: " << tableCard << endl; // Shows last card on table

    // Player move to take card from deck or table
    cout << "\tDraw from (1) Deck or (2) Table? ";
    int choice;
    cin >> choice;

    // Player takes card from deck
    string drawnCard;
    if (choice == 1 && !deck.empty()) // if deck is not empty
    {
        drawnCard = deck.back(); //top card
        deck.pop_back(); //removes card
    }

    // Player takes card from table
    else if (choice == 2)
    {
        drawnCard = tableCard; //table card
    }
    else
    {
        cout << "\tInvalid choice or empty deck. Skipping turn.\n";
        return false;
    }

    // Displays card player took
    cout << "\tYou drew: " << drawnCard << endl;

    // Selecting card to replace
    cout << "\tWhich card to replace (1-3)? or 0 to keep your hand: ";
    int replace;
    cin >> replace;

    if (replace >= 1 && replace <= 3)
    {
        swapCard(hand, tableCard, drawnCard, replace - 1); //swaps card
    }
    else
    {
        tableCard = drawnCard; // card becomes table card
    }

    // Show current score
    int score = getHandScore(hand);
    cout << "\tYour current score: " << score << endl;

    // Check if player hit 31
    if (score == 31)
    {
        cout << "\tYou hit 31! You win instantly!\n";
        return true;
    }

    // Check if player wants to knock
    cout << "\tDo you want to knock? (y/n): ";
    char knock;
    cin >> knock;
    return (knock == 'y' || knock == 'Y');
}

// ##### COMPUTER TURN #####
// Simulates computer turn (Opponent), acts like player, knocking score starts from 27
bool computerTurn(vector<string>& hand, string& tableCard, vector<string>& deck)
{
    int minIndex = 0;
    int minVal = getCardValue(hand[0]); //Stores min value card

    // Find the card with the lowest value
    for (int i = 1; i < 3; ++i)
    {
        if (getCardValue(hand[i]) < minVal)
        {
            minVal = getCardValue(hand[i]); 
            minIndex = i;
        }
    }
    
    // Computer draws card from deck
    string drawnCard;
    if (!deck.empty()) //if not empty
    {
        drawnCard = deck.back(); //takes top card
        deck.pop_back(); //removes
    }

    // Computer draws card from table
    else
    {
        drawnCard = tableCard; //table card goes into hand
    }

    // Swaps card if value is higher then min value card on hand
    if (getCardValue(drawnCard) > minVal)
    {
        swapCard(hand, tableCard, drawnCard, minIndex); //swaping
    }

    // Computers puts card to table if value worst
    else
    {
        tableCard = drawnCard; // card goes to table
    }

    //Saves computer score
    int score = getHandScore(hand);

    // Tells player computer turn is done
    cout << "\tOpponent turn done...\n" << endl;
    return (score >= 27);
}

// ##### PLAY #####
// Hole action happens here, starting with user name, then prompting select count of opponents
// Initiating deck, player and computer hands, giving turns to player and computer
// Calculating final scores and giving option to play again
void Play()
{
    string player;
    int opponents = 0;

    cout << "\n\t=== Blitz ===\n\n";
    cout << "\tWhat's your name?\n";
    cout << "\tEnter: ";
    cin >> player; // Asking for name

    // Creates small loop provide count of opponents
    do
    {
        cout << "\n\tGame can be played with 1-3 opponents.\n";
        cout << "\tSelect number of opponents: ";
        cin >> opponents;

        if (opponents < 1 || opponents > 3)
        {
            cout << "\n\tPlease enter a valid number between 1 and 3.\n";
        }

    } while (opponents < 1 || opponents > 3); //loop continues until number 1, 2, 3 not selected

    bool playAgain = false; // Controling loop (repeat point)

    // Main game loop
    do {
        vector<string> deck = createDeck(); // creating deck
        vector<string> playerHand; // player hand
        vector<vector<string>> computerHands(opponents); // multiple opponents
        string tableCard;

        // Deal 3 cards to player and computer cards
        for (int i = 0; i < 3; ++i)
        {
            playerHand.push_back(deck.back()); //takes cards from back of the deck
            deck.pop_back(); //removes the cards from deck

            for (int j = 0; j < opponents; ++j) //gives 3 cards to each computer
            {
                computerHands[j].push_back(deck.back()); // takes from back of the deck
                deck.pop_back(); //removes the cards from deck
            }
        }

        // Sets the top card as the table first card
        tableCard = deck.back(); //takes from deck
        deck.pop_back(); // and removes from deck

        // Tracks game evolvement
        bool gameOver = false; // Checks for game over
        bool playerKnocked = false; // Checks if player knocked
        vector<bool> computerKnocked(opponents, false); // Checks if any computer knocked

        // Loop for continuity, if deck is empty takes all remaining cards from table, shuffles
        while (!gameOver)
        {
            if (deck.empty())
            {
                deck.push_back(tableCard); //Pushes table card to deck
                random_device rd;
                mt19937 random(rd());
                shuffle(deck.begin(), deck.end(), random); //shuffles deck using mt19937
            }

            // Computer turns
            for (int i = 0; i < opponents; ++i) // each computer takes turn
            {
                computerKnocked[i] = computerTurn(computerHands[i], tableCard, deck);

                if (getHandScore(computerHands[i]) == 31) // if computer hits 31
                {
                    cout << "\tOpponent " << (i + 1) << " hit 31! They win!\n";
                    ofstream out("leaderboard.txt", ios::app); // write to leaderboard
                    out << player << " - LOSS\n"; // player loses
                    out.close();
                    return;
                }

                // Computer knocks if score are bigger then 26 gives one last turn for the player
                if (computerKnocked[i])
                {
                    cout << "\tOpponent " << (i + 1) << " knocks! You get one last turn.\n";
                    playerKnocked = playerTurn(playerHand, tableCard, deck); // player turn
                    gameOver = true; // Close the game
                    break;
                }
            }

            // Player turn
            if (!gameOver) // If game continues
            {
                playerKnocked = playerTurn(playerHand, tableCard, deck); // player turn

                if (getHandScore(playerHand) == 31)
                {
                    cout << player << " hit 31! You win instantly!\n";
                    ofstream out("leaderboard.txt", ios::app);
                    out << player << " - WIN\n";
                    out.close();
                    return;
                }

                if (playerKnocked)
                {
                    cout << player << " knocked! Opponents get one last turn.\n";

                    for (int i = 0; i < opponents; ++i)
                    {
                        computerKnocked[i] = computerTurn(computerHands[i], tableCard, deck);
                    }
                    gameOver = true;
                }
            }
        }

        // Final Scoring
        int playerScore = getHandScore(playerHand);
        vector<int> compScores(opponents);
        int maxScore = playerScore;
        int winner = -1; // -1 for player, 0+ for computer[i]

        for (int i = 0; i < opponents; ++i) {
            compScores[i] = getHandScore(computerHands[i]);
            if (compScores[i] > maxScore) {
                maxScore = compScores[i];
                winner = i;
            }
        }

        cout << "\n\tFinal Scores:\n";
        cout << player << ": " << playerScore << endl;
        for (int i = 0; i < opponents; ++i) {
            cout << "\tOpponent " << (i + 1) << ": " << compScores[i] << endl;
        }

        if (winner == -1) {
            cout << player << " wins!\n";
            ofstream out("leaderboard.txt", ios::app);
            out << player << " - WIN\n";
            out.close();
        } else {
            cout << "\tOpponent " << (winner + 1) << " wins!\n";
            ofstream out("leaderboard.txt", ios::app);
            out << player << " - LOSS\n";
            out.close();
        }

        cout << "\n\tDo you want to play again? (y/n): ";
        char again;
        cin >> again;
        playAgain = (again == 'y' || again == 'Y');

    } while (playAgain);
}

// ##### RULES #####
void Rules()
{
    cout << " " << endl;
    cout << "\t=== Game Rules ===" << endl;
    cout << " " << endl;
    cout << "\t1. Goal is to reach 31 points" << endl;
    cout << "\t2. Hand can hold only 3 cards" << endl;
    cout << "\t3. Points are calculate only with cards has same suits" << endl;
    cout << "\t4. You can change one card from the deck or the table" << endl;
    cout << "\t5. You can knock on your turn if you feel confident" << endl;
    cout << "\t6. After a knock, the other players gets one last turn" << endl;
    cout << "\t7. If highest score held by few players winner become last knocker" << endl;
    cout << " " << endl;
}

// ##### LEADERBOARD ######
void Leaderboard()
{
    cout << "\n\t=== Leaderboard ===\n\n";
    ifstream in("leaderboard.txt"); // reads file
    if (in) {
        string line; 
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    } else {
        cout << "\tNo leaderboard found yet.\n";
    }
}


// ##### MENU #####
int main()
{
    char choice;
    do
    {
        // Main Menu
        cout << "\n\t=== Let's play Blitz ===\n\n";
        cout << "\t1. Play\n";
        cout << "\t2. Rules\n";
        cout << "\t3. Leaderboard\n";
        cout << "\t4. Exit\n";
        cout << "\n\tEnter: ";
        cin >> choice;
        
        switch(choice) // Selects menu
        {
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
                cout << "\n\tThank you for playing!!!\n";
                break;
            default:
                cout << "\n\tPlease enter only available choice!\n";
        }

    } while(choice != '4'); // exits the loop on 4
    
    return 0;
}