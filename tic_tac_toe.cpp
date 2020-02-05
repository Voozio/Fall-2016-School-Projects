//TicTacToe.cpp - A game of Tic Tac Toe against a computer
//Justin Voo - 9/26/16
//CISP 400

//Pre-processors
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

//Standard library
using namespace std;

//Prototypes used to foreshadow upcoming functions
int greeting();
void outputWinner(int flag_result);

//The class behind the game
class TicTacToe
{
    private:
        vector<string> board;
        vector<int> usedSpaces;

    public:
        TicTacToe();
        void displayBoard();
        string chooseMarker();
        void playerTurn(string player_marker);
        void compTurn(string comp_marker);
        int getUsedSpacesSize();
        int determineWinner(string marker, int condition);
        bool reset();
} ;

//The TicTacToe constructor function
//The game board is created
TicTacToe::TicTacToe()
{
    for (int x = 0; x < 9; x++)
    {
        board.push_back(" ");
    }
}

//This functions displays the current game board
void TicTacToe::displayBoard()
{
    cout << "\nCurrent Board:\n";
    for (int x = 0; (unsigned)x < board.size(); x++)
    {
        cout << " " << board[x] << " | " << board[x+1] << " | " << board[x+2];
        if (x < 6)
        {
            cout << "\n-----------\n";
        }
        x += 2;
    }
}

//This function allows the player to choose his/her marker
string TicTacToe::chooseMarker()
{
    string marker = "";
    bool flag = true;

    cout << "Would you like to use an 'X' or an 'O' as your marker?\n";
    while (flag)
    {
        cout << "Enter an 'X' or an 'O' or '0' to quit: ";
        getline(cin, marker);
        if (marker == "X" || marker == "x")
        {
            return "X";
            flag = true;
        }
        else if (marker == "O" || marker == "o")
        {
            return "O";
            flag = true;
        }
        else
        {
            cout << "Your input is invalid.\n\n";
        }
    }
}

//This function allows the user to take his/her turn
void TicTacToe::playerTurn(string player_marker)
{
    int choice;
    int counter = 0;
    bool flag = true;
    cout << "\nIt is your turn. Select a space or '0' to quit: ";
    cin >> choice;
    //Will keep looping until user input is valid
    while (flag)
    {
        //Checks to see if input is an integer
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(100,'\n');
            cout << "\nYour input is invalid. Please select a space number: ";
            cin >> choice;
        }
        //Checks to see if input is within the Tic Tac Toe space range
        if (choice < 0 || choice > 9)
        {
            cin.clear();
            cout << "\nThat is not a valid space number. Please select a number between 1-9: ";
            cin >> choice;
        }
        else
        {
            //Counts how many numbers in usedSpaces that are not = to user input
            for (int x = 0; (unsigned)x < usedSpaces.size(); x++)
            {
                if (usedSpaces[x] != choice)
                {
                    counter++;
                }
            }
            //Determines if user inputs an untaken space
            if (counter == usedSpaces.size())
            {
                cin.clear();
                usedSpaces.push_back(choice);
                board[choice-1] = player_marker;
                flag = false;
            }
            //resets cin/counter and starts over
            else
            {
                cin.clear();
                counter = 0;
                cout << "\nThat space has already been taken. Please select a different one: ";
                cin >> choice;
            }
        }
    }
}

//This function decides the computer's move

void TicTacToe::compTurn(string comp_marker)
{
    bool flag = true;
    srand(time(NULL));
    int random;
    int counter = 0;

    while (flag)
    {
        random = rand()%9;
        for (int x = 0; (unsigned)x < usedSpaces.size(); x++)
        {
            if (usedSpaces[x] != (random+1))
            {
                counter++;
            }
        }
        if (counter > 10)
        {
            flag = false;;
        }
        if (counter == usedSpaces.size())
        {
            usedSpaces.push_back(random+1);
            board[random] = comp_marker;
            flag = false;
        }
        else
        {
            counter = 0;
        }
    }
}

int TicTacToe::getUsedSpacesSize()
{
    return (int)usedSpaces.size();
}

//This function determines if a winner or tie is present
int TicTacToe::determineWinner(string marker, int condition)
{
    if (board[0] == marker && board[1] == marker && board[2] == marker)
    {
        return condition;
    }
    else if (board[3] == marker && board[4] == marker && board[5] == marker)
    {
        return condition;
    }
    else if (board[6] == marker && board[7] == marker && board[8] == marker)
    {
        return condition;
    }
    else if (board[0] == marker && board[3] == marker && board[6] == marker)
    {
        return condition;
    }
    else if (board[1] == marker && board[4] == marker && board[7] == marker)
    {
        return condition;
    }
    else if (board[2] == marker && board[5] == marker && board[8] == marker)
    {
        return condition;
    }
    else if (board[0] == marker && board[4] == marker && board[8] == marker)
    {
        return condition;
    }
    else if (board[2] == marker && board[4] == marker && board[6] == marker)
    {
        return condition;
    }
    else
    {
        return -1;
    }
}

bool TicTacToe::reset()
{
    cin.ignore();
    string answer = "0";

    cout << "\nWould you like to play again?\n";
    cout << "Enter '0' for yes and anything else for no: ";
    getline(cin, answer);
    if (answer == "0")
    {
        board.clear();
        board.resize(9);
        for (int x = 0; x < 9; x++)
        {
            board[x] = " ";
        }
        usedSpaces.clear();
        usedSpaces.resize(0);
        cout << string(100, '\n');
        return true;
    }
    else
    {
        return false;
    }
}

//Bonus - Option to quit is given in functions chooseMarker() and playerTurn()
int main()
{
    TicTacToe Game;
    int first_move;
    int flag_result = -1;
    string player_marker;
    string comp_marker;
    bool playAgain = true;

    while (playAgain)
    {
        first_move = greeting();
        //Bonus - Player gets to choose which marker he prefers (X or O)
        player_marker = Game.chooseMarker();
        if (player_marker == "O")
        {
            comp_marker = "X";
        }
        else
        {
            comp_marker = "O";
        }
        if (first_move != 0)
        {
            Game.compTurn(comp_marker);
        }
        while (flag_result == -1)
        {
            Game.displayBoard();
            if (Game.getUsedSpacesSize() != 9)
            {
                Game.playerTurn(player_marker);
                flag_result = Game.determineWinner(player_marker, 0);
            }
            if (flag_result == -1 && Game.getUsedSpacesSize() != 9)
            {
                Game.compTurn(comp_marker);
                flag_result = Game.determineWinner(comp_marker, 1);
            }
            if (Game.getUsedSpacesSize() == 9)
            {
                flag_result = Game.determineWinner(player_marker, 0);
                if (flag_result == -1)
                {
                    flag_result = Game.determineWinner(comp_marker, 1);
                }
                if (flag_result != 0 && flag_result != 1)
                {
                    flag_result = 2;
                }
            }
        }
        Game.displayBoard();
        outputWinner(flag_result);
        //Bonus - Option to play again
        playAgain = Game.reset();
        if (playAgain == true)
        {
            flag_result = -1;
        }
    }

    return 0;
}

//This function greets the user and explains the rules of the game
int greeting()
{
    vector<int> example(9);
    srand(time(NULL));
    int random = rand()%2;

    cout << "\n\nWelcome to TicTacToe! You will be facing a computer.\n";
    cout << "Here are the space numbers:\n\n";
    for (int x = 0; (unsigned)x < example.size(); x++)
    {
        example[x] = x + 1;
        example[x+1] = x + 2;
        example[x+2] = x + 3;
        cout << " " << example[x] << " | " << example[x+1] << " | " << example[x+2];
        if (x < 6)
        {
            cout << "\n-----------\n";
        }
        x += 2;
    }
    cout << "\n\nWhen it is your turn, you will select a space to place your marker in.";
    if (random == 0)
    {
        cout << "\n\nBy random selection, you will go first.\n\n";
    }
    else
    {
        cout << "\n\nBy random selection, the computer will go first.\n\n";
    }

    return random;
}

//This function uses the flag_result variable to output the winner
void outputWinner(int flag_result)
{
    if (flag_result == 0)
    {
        cout << "\n\nYou won!\n";
    }
    else if (flag_result == 1)
    {
        cout << "\n\nYou lose :(\n";
    }
    else
    {
        cout << "\n\nIt's a tie!\n";
    }
}


