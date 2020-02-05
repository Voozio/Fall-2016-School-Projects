//blackjack.cpp - A simple game of blackjack
//Justin Voo - 10/31/16
//CISP 400


//Pre-processors
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>


//Standard library call
using namespace std;


//Function prototypes used to foreshadow upcoming functions
string greeting();
string getCardName(int current_card);
void displayCards(vector<string> card_list);


//Four instances of this class will be made to create the deck
class Deck
{
        private:
                vector<int> deck;
        public:
                Deck();
                int drawCard(int random);
                int getSize();
};


//Deck class constructor
Deck::Deck()
{
        for(int x = 0; x < 10; x++)
        {
                deck.push_back(x + 1);
        }
        for(int x = 0; x < 3; x++)
        {
                deck.push_back(10);
        }
}


//A card is drawn and that card is removed the from the list of existing cards
int Deck::drawCard(int random)
{
        int card;


        card = deck[random];
        deck.erase(deck.begin() + random);
        return card;
}


//A function that returns the size of a current card set
int Deck::getSize()
{
        return (signed)deck.size();
}


//Bonus - Recursion
class Game
{
        private:
                //Four class instances
                Deck spades;
                Deck hearts;
                Deck clubs;
                Deck diamonds;
        public:
                int hit();
};


int Game::hit()
{
        int current_card;
        int random;
        srand(time(NULL));
        random = rand()%4;
        if(random == 0)
        {
                random = rand()%spades.getSize();
                current_card = spades.drawCard(random);
        }
        else if(random == 1)
        {
                random = rand()%hearts.getSize();
                current_card = hearts.drawCard(random);
        }
        else if(random == 2)
        {
                random = rand()%clubs.getSize();
                current_card = clubs.drawCard(random);
        }
        else if(random == 3)
        {
                random = rand()%diamonds.getSize();
                current_card = diamonds.drawCard(random);
        }
        return current_card;
}


int main()
{
        //Game class for "hitting" (getting another card)
        Game game;
        //Temporary card variables
        int current_card;
        int current_card_2;
        //These vectors hold all the cards that have been drawn
        vector<string> player_cards;
        vector<string> comp_cards;
        //Cummulative totals
        int player_total;
        int comp_total;
        //Input variables
        string decision;
        string wager_decision;
        int wager;
        bool flag;
        bool high_ace_player = false;
        bool high_ace_comp = false;
        bool bust = false;
        string comp_cheat;


        //Bonus - Incorporate wagering
        wager_decision = greeting();
        if(wager_decision == "0")
        {
                cout << "\nEnter a wager amount: $";
                cin >> wager;
                while (cin.fail() || wager <= 0)
                {
                        cin.clear();
                        cin.ignore(100,'\n');
                        cout << "\nYour input is invalid. Please select a valid number: ";
                        cin >> wager;
                }
                cin.ignore();
        }
        
        //Bonus - Computer cheat mode
        cout << "\nTo enable computer cheat mode, enter \"0\": ";
        getline(cin, comp_cheat);


        //Player's first turn
        current_card = game.hit();
        player_cards.push_back(getCardName(current_card));
        current_card_2 = game.hit();
        player_cards.push_back(getCardName(current_card_2));
        player_total = current_card + current_card_2;


        //Bonus - Automatically uses high ace if the total doesn't bust
        if(current_card == 1 || current_card_2 == 1)
        {
                if(player_total <= 11)
                {
                        high_ace_player = true;
                        player_total += 10;
                }
        }
        displayCards(player_cards);
        cout << "\nYour total is " << player_total << ".\n";
        if(player_total == 21)
        {
                cout << "BLACKJACK!\n";
        }
        
        //Computer's first turn
        current_card = game.hit();
        comp_cards.push_back(getCardName(current_card));
        current_card_2 = game.hit();
        comp_cards.push_back(getCardName(current_card_2));


        //Assigns computer's cards if cheat mode is active
        if(comp_cheat == "0")
        {
                current_card = 10;
                current_card_2 = 11;
                comp_cards[0] = "10";
                comp_cards[1] = "Ace (1 or 11)";
        }
        comp_total = current_card + current_card_2;
        //Automatically uses high ace if the total doesn't bust
        if(current_card == 1 || current_card_2 == 1)
        {
                if(comp_total <= 11)
                {
                        comp_total += 10;
                        high_ace_comp = true;
                }
        }
        cout << "\nThe dealer has a " << comp_cards[0] << " showing, and a hidden card.\n";
        cout << "His total is hidden too.\n\n";
        if(player_total == 21)
        {
                cout << "You already have blackjack so you must stay.\n\n";
        }
        //Player's turn continued
        while(decision != "stay" && player_total < 21)
        {
                flag = true;
                while(flag)
                {
                        cout << "Would you like to \"hit\" or \"stay\"? ";
                        getline(cin, decision);
                        if(decision == "hit")
                        {
                                current_card = game.hit();
                                player_cards.push_back(getCardName(current_card));
                                player_total += current_card;
                                //Automatically uses high ace if the total doesn't bust
                                if(current_card == 1 || current_card_2 == 1)
                                {
                                        if(player_total <= 11)
                                        {
                                                player_total += 10;
                                                high_ace_player = true;
                                        }
                                }
                                displayCards(player_cards);
                                if(player_total > 21)
                                {
                                        if(high_ace_player)
                                        {
                                                cout << "\nYour Ace(11) is changed to a (1)\n";
                                                player_total -= 10;
                                                high_ace_player = false;
                                        }
                                }
                                cout << "\nYour total is " << player_total;
                                if(player_total > 21)
                                {
                                        cout << " ~ You busted.\n\n";
                                        bust = true;
                                }
                                else
                                {
                                        cout << ".\n\n";
                                }
                                flag = false;
                        }
                        else if(decision == "stay")
                        {
                                flag = false;
                        }
                        else
                        {
                                cout << "Invalid input...\n";
                        }
                }
        }
        //Checks to see if the player has bust
        //Computer's turn continued
        if(!bust)
        {
                cout << "\nNow for the dealer's turn.\nHis hidden card was a " << comp_cards[1] << ".\n";
                cout << "His total was " << comp_total << ".\n\n";
                while(comp_total <= 17)
                {
                        cout << "Dealer chooses to hit.\n";
                        current_card = game.hit();
                        comp_cards.push_back(getCardName(current_card));
                        cout << "He draws a " << current_card;
                        comp_total += current_card;
                        //Automatically uses high ace if the total doesn't bust
                        if(current_card == 1 || current_card_2 == 1)
                        {
                                if(comp_total <= 11)
                                {
                                        comp_total += 10;
                                        high_ace_comp = true;
                                }
                        }
                        if(comp_total > 21)
                        {
                                if(high_ace_comp)
                                {
                                        comp_total -= 10;
                                        cout << "\nHis Ace(11) is changed to (1);\n";
                                        high_ace_comp = false;
                                }
                                else
                                {
                                        cout << " ~ he busted.\n";
                                }
                        }
                        else
                        {
                                cout << ".\n";
                        }
                        cout << "His total is " << comp_total << ".\n\n";
                }
        }
        //Outcome possibilities - win, tie, loss
        if(player_total > comp_total)
        {
                if(!bust)
                {
                        cout << "YOU WIN!\n";
                        if(wager_decision == "0")
                        {
                                cout << "You've doubled your money.\n";
                                cout << "You now have a total of $" << wager*2 << ".\n";
                        }
                }
                else
                {
                        cout << "The dealer wins :(\n";
                        if(wager_decision == "0")
                        {
                                cout << "You lost the wager.\n";
                        }
                }
        }
        else if(player_total == comp_total)
        {
                cout << "It's a tie ._.\n";
                if(wager_decision == "0")
                {
                        cout << "You get your money back.\n";
                }
        }
        else if(comp_total > player_total)
        {
                if(comp_total <= 21)
                {
                        cout << "The dealer wins :(\n";
                        if(wager_decision == "0")
                        {
                                cout << "You lost the wager.\n";
                        }
                }
                else
                {
                        cout << "YOU WIN!\n";
                        if(wager_decision == "0")
                        {
                                cout << "You've doubled your money.\n";
                                cout << "You now have a total of $" << wager*2 << ".\n";
                        }
                }
        }
}


//Greeting function that also accepts a decision for a wager
string greeting()
{
        string decision;


        cout << "Welcome to the ultimate blackjack program!\n";
        cout << "Would you like to make a wager? To accept, enter \"0\": ";
        getline(cin, decision);
        return decision;
}


//A function that returns a card name
string getCardName(int current_card)
{
        string card;


        if (current_card == 1)
        {
                card = "Ace (1 or 11)";
                return card;
        }
        else if (current_card == 11)
        {
                card = "Jack (10)";
                return card;
        }
        else if (current_card == 12)
        {
                card = "Queen (10)";
                return card;
        }
        else if (current_card == 13)
        {
                card = "King (10)";
                return card;
        }
        else
        {
                //An int is turned into a string
                card = to_string(current_card);
                return card;
        }
}


//A function that displays all of the player's current cards
void displayCards(vector<string> card_list)
{
        cout << "\nYour current cards: ";
        for(int x = 0; (unsigned)x < card_list.size(); x++)
        {
                cout << card_list[x];
                if ((unsigned)x < card_list.size()-1)
                {
                        cout << ", ";
                }
        }
        cout << ".";
}
