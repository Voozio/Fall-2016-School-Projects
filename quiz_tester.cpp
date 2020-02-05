//quiz_tester.cpp - A quiz tester program.
//Justin Voo - 8/27/16
//CISP 400

//Pre-processors
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iterator>

using namespace std;

//Function prototypes
void greeting();
vector<string> open();
vector<int> quiz(vector<string> list);
string findAnswer(vector<string> list, int question);
string answerConverter(string answer);
vector<string> displayScore(int correct, int incorrect);
void save(vector<string> list);

//This Quiz object stores the quiz questions, answers, and score
class Quiz
{
    public:
        vector<string> list;
        int correct;
        int incorrect;
        vector<int> runningScore;
        vector<string> finalScore;
};

int main()
{
    //A Quiz object is instantiated
    Quiz quiz1;

    greeting();
    //open() fills the list with questions and answers from a .txt file
    quiz1.list = open();
    //quiz() uses list to run
    quiz1.runningScore = quiz(quiz1.list);
    quiz1.correct = quiz1.runningScore[0];
    quiz1.incorrect = quiz1.runningScore[1];
    //The score is displayed after the quiz is taken
    quiz1.finalScore = displayScore(quiz1.correct, quiz1.incorrect);
    //Bonus - The performance is saved into a file
    save(quiz1.finalScore);

    return 0;
}

//A function to greet the user and give a description of the program
void greeting()
{
    cout << "Welcome! This program will quiz you with multiple choice questions.\n";
    cout << "For each question, please enter the letter corresponding the answer you select.\n";
    cout << "Example: If you choose the first answer to Question 1, you will type 'A' or 'a'.\n\n";
}

//A function that allows the questions to be opened from a file
//Each line from the file is read and put into a single slot in the vector
vector<string> open()
{
    vector<string> list;
    string line;
    ifstream filestream("questions.txt");
    bool flag = false;

    while (flag == false)
    {
        getline(filestream, line);
        if (line == "")
        {
            flag = true;
        }
        else
        {
            //Every new .txt line is placed onto a new line in the vector
            list.push_back(line);
        }
    }
    filestream.close();
    return list;
}

//The function that runs the actual quiz
vector<int> quiz(vector<string> list, int correct, int incorrect)
{
    bool retake = true;
    int decision;

    //Bonus - Allows the user wants to retake the quiz
    while (retake == true)
    {
        //The flag variable for while loops
        bool temp = false;
        bool flag = false;
        //The int variables to hold ints
        int random;
        int current = 0;
        //Each question takes up 6 lines in the .txt file
        int max = (list.size() / 6);
        int questionNumber;
        int vectorLine = 0;
        //Score numbers are instatiated
        vector<int> score(2);
        score[0] = 0;
        score[1] = 0;
        string answer = "";
        string realAnswer;
        //Srand time is set to NULL to make rand() more random
        srand(time(NULL));
        //QuestionsUsed keep a list of the question numbers
        //It will be used to make sure there are no repeat questions displayed
        vector<int> questionsUsed;
        //The questionsUsed vector is given a size of max
        questionsUsed.push_back(max);
        //Numbers are placed inside of questionsUsed from 1 to max in chronological order
        for (int x = 0; x < max; x++)
        {
            questionsUsed[x] = x + 1;
        }
        //This is the main quiz loop that displays the quiz
        while (current < max)
        {
            //This loop creates random numbers to choose quiz questions
            //A different question is chosen each time
            while (flag == false)
            {
                random = rand()%max + 1;
                for (int x = 0; x < max; x++)
                {
                    if (random == questionsUsed[x])
                    {
                        questionsUsed[x] = -1;
                        flag = true;
                    }
                }
            }
            //The current questionNumber is set the the new random number
            questionNumber = random;
            //The answer for the current question is found
            realAnswer = findAnswer(list, questionNumber);
            //The current question and all the possible answers are displayed
            cout << "Question " << questionNumber << endl;
            vectorLine = (questionNumber * 6) - 6;
            for (int x = 0; x < 5; x++)
            {
                cout << list[vectorLine] << endl;
                vectorLine++;
            }
            //A request for user input is shown
            cout << "Selection: ";
            getline(cin, answer);
            //An error check that makes sure all input is valid
            while (temp == false)
            {
                if (answer != "a" && answer != "A" && answer != "b" && answer != "B" && answer != "c" && answer != "C" && answer != "d" && answer != "D")
                {
                    cout << "\nYour answer is invalid.\n\nSelection: ";
                    getline(cin, answer);
                }
                else
                {
                    temp = true;
                }
            }
            //A function that changes the user input to lowercase
            answer = answerConverter(answer);
            if (answer == realAnswer)
            {
                cout << "You are correct! Hoorah!\n\n";
                score[1] += 1;
            }
            else
            {
                cout << "That's incorrect. Nice try buddy...\n\n";
                score[1] += 1;
            }
            //Current keeps track of how many questions have been shown
            current++;
            temp = false;
            flag = false;
        }
        cout << "Would you like to retake the quiz? Type 0 to retake and anything else to quit: " << endl;
        cin >> decision;
        if (decision != 0)
        {
            retake = false;
            return score;
        }
        else
        {
            cout << "\n\n\n";
        }
    }
}

//This function finds the answer to a certain question
string findAnswer(vector<string> list, int question)
{
    int counter = (question * 6) - 1;
    string answer = "";
    
    if (list[counter] == "1")
    {
        answer = "a";
    }
    else if (list[counter] == "2")
    {
        answer = "b";
    }
    else if (list[counter] == "3")
    {
        answer = "c";
    }
    else
    {
        answer = "d";
    }
    return answer;
}

//This function converts the user input to lowercase
string answerConverter(string answer)
{
    if (answer == "A")
    {
        answer = "a";
    }
    else if (answer == "B")
    {
        answer = "b";
    }
    else if (answer == "C")
    {
        answer = "c";
    }
    else if (answer == "D")
    {
        answer = "d";
    }
    return answer;
}

//This function displays the number of correct and incorrect answers
//as well as the percentage score
vector<string> displayScore(int correct, int incorrect)
{
    vector<string> list;
    list.push_back(to_string(correct));
    list.push_back(to_string(incorrect));
    double total = correct + incorrect;
    total = (double)correct/total;
    total *= 100;
    list.push_back(to_string(total));
    cout << "\nCorrect: " << correct << "\nIncorrect: " << incorrect;
    cout << "\nScore: " << total << "%" << endl << endl;

    return list;
}

//This function saves the user's score into a .txt file
void save(vector<string> list)
{
    ofstream filestream("QuizScore.txt");
    copy(list.begin(), list.end(), ostream_iterator<string>(filestream, "\n"));
    filestream.close();
}


