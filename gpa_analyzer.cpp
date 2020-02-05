//GPAAna.cpp - A program that accepts a list of scores and calculates the average score.
//Justin Voo - 9/12/16
//CISP 400

//Pre-processors
#include <iostream>
#include <string>

//Access to the standard library
using namespace std;

//Function prototypes used to foreshadow upcoming functions
void greeting(); 
bool exitPrompt(bool exit);

//The class behind it all
//This holds all necessary functions and variables dealing with user scores
class scoreTransformer
{
    public:
        //An initial size is initialized to prevent error
        int size = 0;
        //The array is dynamically allocated using a double pointer
        double* scores = new double[size];
        //The actual size is kept track of based on how many scores the user inputs
        int realSize = 0;

        //The function is resized when the user wants to input more scores
        double* resize(scoreTransformer userScores);
        //A score is inputed into the dynamic array
        double* input(scoreTransformer userScores);
        //The average score is calculated
        void calcAverage(scoreTransformer userScores);
        void sort(scoreTransformer userScores);
};

int main()
{
    //Object declaration
    scoreTransformer userScores;
    bool exit = false;

    greeting();
    //Loop runs until user decides to stop entering scores
    while (exit == false)
    {
        //The array is resized every iteration to make sure there is enough space for user input
        userScores.scores = userScores.resize(userScores);
        userScores.scores = userScores.input(userScores);
        exit = exitPrompt(exit);
        //One is added to realSize for every score that the user inputs
        userScores.realSize += 1;
    }
    userScores.calcAverage(userScores);
    userScores.sort(userScores);

    delete[] userScores.scores;
    return 0;
}

//A function used to greet the user
void greeting()
{
  cout << "Welcome to the GPA Analyzer. This program will sort your scores and calculate the average.\n";
}

//This function allows the user to input a single score.
double* scoreTransformer::input(scoreTransformer userScores)
{
    string userInput;
    //A value is given to inputNum to prevent error
    double inputNum = -1;
    bool valid = false;

    while (valid == false)
    { 
        //Prompts for input
        cout << "\nPlease enter in grade #"<< userScores.realSize + 1 <<" (letters only): ";
        cin >> userInput;
        //Input validation
        if (userInput == "A" || userInput == "a")
        { 
           inputNum = 4;
        }
        else if (userInput == "B" || userInput == "b")
        {
            inputNum = 3;
        }
        else if (userInput == "C" || userInput == "c")
        {
            inputNum = 2;
        }
        else if (userInput == "D" || userInput == "d")
        {
            inputNum = 1;
        }
        else if (userInput == "F" || userInput == "f")
        {
            inputNum = 0;
        }
        if (inputNum != 0 && inputNum != 1 && inputNum != 2 && inputNum != 3 && inputNum != 4)
        {
            cout << "\nYour input is invalid.\n";
            valid = false;
        }
        else
        {
            valid = true;
        }
    }
    //The score (inputNum) is placed into the next empty slot of an array
    *(userScores.scores + userScores.realSize) = inputNum;
    //Bonus - A list of the entered GPA values to allow the user to keep track of what was entered
    cout << "\nCurrent GPA values inputed:\n";
    for (int x=0; x <= realSize; x++)
    {
        cout << *(userScores.scores+x);
        if (x < realSize)
        {
            cout << ", ";
        }
    }

    return scores;
}

//This function resizes the dynamic array in the class
double* scoreTransformer::resize(scoreTransformer userScores)
{
   double* temp = new double[size + 1];

   for(int x = 0; x < size; x++)
   {
        *(temp + x) = *(scores + x);
   }
   //One is added to the size to prevent memory issues
   size++;
   scores = temp;

   return temp;
}

//This functions prompts for scores to be entered no more
bool exitPrompt(bool exit)
{
    string userInput;
    bool exitPromptLoop = false;
    
    cout << "\n\nWould you like to continue entering grades (Y/N)?: ";
    cin >> userInput;
    //Input validation
    while (exitPromptLoop == false)
    {   
        if(userInput== "N" || userInput == "n")
        {   
            exit = true;
            exitPromptLoop = true;
        }
        else if(userInput == "Y" || userInput== "y")
        {
            exit = false;
            exitPromptLoop = true;
        }
        else
        {
            cout << "Your input is invalid. Please enter in Y or N: ";
            cin >> userInput;
        }
    }

    return exit;
}

//This function adds up all the scores and calculates the average
void scoreTransformer::calcAverage(scoreTransformer userScores)
{
    double gpa;

    for (int x = 0; x <= realSize; x++)
    {
        gpa += *(userScores.scores + x);
    }
    gpa /= realSize;
    if (gpa >= 4)
    {
        cout << "\nYour average grade is an A with an actual GPA of " << gpa << ".\n";
    }
    if (gpa < 4 and gpa >= 3)
    {
        cout << "\nYour average grade is a B with an actual GPA of " << gpa << ".\n";
    } 
    if (gpa < 3 and gpa >= 2)
    {
        cout << "\nYour average grade is a C with an actual GPA of " << gpa << ".\n";
    }
    if (gpa < 2 and gpa >= 1)
    {
        cout << "\nYour average grade is a D with an actual GPA of " << gpa << ".\n";
    }
    if (gpa < 1)
    {
        cout << "\nYour average grade is an F with an actual GPA of " << gpa << ".\n";
    }
}

//Bonus - This function uses bubble sort to sort all the user's GPA scores
void scoreTransformer::sort(scoreTransformer userScores)
{
    //A flag variable
    bool flag;
    //A temporary dynamic array is created
    int* sortedList = new int[realSize];
    
    for (int x = 0; x < realSize; x++)
    {
        *(sortedList + x) = *(scores + x);
    }
    //Condition must be put at the end of the loop for value checking to be full
    //Else, certain parts of the array will be sorted
    do
    {
        flag = false;
        for (int s = 0; s < realSize - 1; s++)
        {
            if (*(sortedList + s) > *(sortedList + (s+1)))
            {
                int temp = *(sortedList + s);
                *(sortedList + s) = *(sortedList + (s+1));
                *(sortedList + (s+1)) = temp;
                flag = true;
            }
        }
    } while (flag);
    cout << "Your individual GPA scores sorted in ascending order are: ";
    for (int x = 0; x < realSize; x++)
    {
        cout << *(sortedList + x);
        if (x < realSize - 1)
        {
            cout << ", ";
        }
    }
    cout << ".\n";
}
