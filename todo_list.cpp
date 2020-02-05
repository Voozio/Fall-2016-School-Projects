//Todo.cpp - A To-do List Program
//Justin Voo - 10/17/16
//CISP 400

//Pre-processors
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

//Standard library for syntax convenience
using namespace std;

//Class dealing with the date of a task
class Date
{
    private:
        string date;

    public:
        string insertDate(string task);
};

//Function to insert a date to a task
string Date::insertDate(string task)
{
    string date;

    cout << "\nEnter the task date (Ex: ##/##/##): ";
    getline(cin, date);
    task += "  (" + date + ")";
    return task;
}

//Class containing important variables and all functions
class Program
{
    private:
        vector<string> list;
        vector<string> complete;
        bool quit = false;

    public:
        void greeting();
        void open();
        void menu();
        void inputTasks();
        void displayTasks();
        void completeTask();
        void incompleteTask();
        void removeTask();
        bool determineQuit();
        void saveAndQuit();
};

//Greeting function to welcome the user
//Option to open a pre-existing file
void Program::greeting()
{
    string decision;

    cout << "Welcome to your personal To-do List!\n";
    cout << "It is recommended to use a pre-existing file only if this program has already been used to create a to-do list.\n";
    cout << "To use a pre-existing to-do list, enter '0': ";
    getline(cin, decision);
    if (decision == "0")
    {
        open();
        cout << "\nA pre-exisitng file was used...\n";
    }
    else
    {
        cout << "\nA pre-existing file was not used...\n";
    }
}

//Function used to open a file and store its contents in vectors
void Program::open()
{
    string line;
    int temp;
    bool flag = false;
    ifstream filestream("ToDoList.txt");

    //Loops while not EOF (End of File)
    while (!filestream.eof())
    {
        getline(filestream, line);
        if (line == "x")
        {
            complete.push_back(line);
            flag = true;
        }
        else if (line == "o")
        {
            complete.push_back(line);
            flag = true;
        }
        else if (line != "")
        {
            list.push_back(line);
        }
    }
    temp = list.size();
    if (!flag)
    {
        for (int x = 0; x < temp; x++)
        {
            complete.push_back("o");
        }
    }
    filestream.close();
}

//Function used to display a menu with an array of options
void Program::menu()
{
    string decision;
    bool flag = true;

    cout << "\n----------------------------";
    cout << "\n            Menu\n";
    cout << "----------------------------\n";
    cout << "-Add a new task............1\n";
    cout << "-Display all tasks.........2\n";
    cout << "-Mark a task as complete...3\n";
    cout << "-Mark a task as incomplete.4\n";
    cout << "-Remove task...............5\n";
    cout << "-Save and quit.............6\n\n";
    while (flag)
    {
        cout << "-Choice: ";
        getline(cin, decision);
        if (decision == "1")
        {
            cout << "\nTo stop entering new tasks, leave the task name blank.\n";
            inputTasks();
            flag = false;
        }
        else if (decision == "2")
        {
            displayTasks();
            flag = false;
        }
        else if (decision == "3")
        {
            completeTask();
            flag = false;
        }
        else if (decision == "4")
        {
            incompleteTask();
            flag = false;
        }
        else if (decision == "5")
        {
            removeTask();
            flag = false;
        }
        else if (decision == "6")
        {
            quit = true;
            flag = false;
        }
        else
        {
            cout << "\nThat is not an option. Please try again.\n\n";
        }
    }
}

//Function used to continuously input tasks until a blank task is entered
void Program::inputTasks()
{
    string task;
    string decision;
    Date date;

    cout << "\nEnter a task name: ";
    getline(cin, task);
    if (task != "")
    {
        task = date.insertDate(task);
        list.push_back(task);
        cout << "\nTo mark this task as complete, enter '0': ";
        getline(cin, decision);
        if (decision == "0")
        {
            complete.push_back("x");
        }
        else
        {
            complete.push_back("o");
        }
        //Bonus - Recursion
        inputTasks();
    }
    else
    {
        cout << "\nNo task entered...\n";
    }
}

//Function used to display all tasks in the current task list
//Bonus - Display completed items seperately
void Program::displayTasks()
{
    int counter = 0;

    //Checks to see if there are any tasks in the list
    if (list.size() > (unsigned)0)
    {
        cout << "\n\n----------------------------\n";
        cout << " Incomplete Tasks\n";
        cout << "----------------------------\n";
        for (int x = 0; (unsigned)x < list.size(); x++)
        {
            if (complete[x] == "o")
            {
                cout << "-" << list[x] << endl;
                counter++;
            }

        }
        if (counter == 0)
        {
            cout << "There are no incomplete tasks...\n";
        }
        counter = 0;
        cout << "\n----------------------------\n";
        cout << " Completed Tasks\n";
        cout << "----------------------------\n";
        for (int x = 0; (unsigned)x < list.size(); x++)
        {
            if (complete[x] == "x")
            {
                cout << "-" << list[x] << endl;
                counter++;
            }
        }
        if (counter == 0)
        {
            cout << "There are no completed tasks...\n";
        }
    }
    else
    {
        cout << "\nYour current task list is empty...\n";
    }
}


//Bonus - Function - Items marked as complete using a parallel vector
//X's represent complete items while O's represent incomplete items
void Program::completeTask()
{
    string decision;
    int final_decision;
    int inc_num = 0;
    int counter = 0;
    bool flag = true;
    vector<string> temp;

    //Checks to see if there are any incomplete tasks in the current task list
    for (int x = 0; (unsigned)x < complete.size(); x++)
    {
        if (complete[x] == "o")
        {
            inc_num++;
        }
    }
    if (inc_num != 0)
    {
        cout << "\n\n----------------------------\n";
        cout << " Incomplete Tasks\n";
        cout << "----------------------------\n";
        for (int x = 0; (unsigned)x < list.size(); x++)
        {
            if (complete[x] == "o")
            {
                cout << counter + 1 << ". " << list[x] << endl;
                temp.push_back(list[x]);
                counter++;
            }
        }
        cout << "\nWhich task would you like to mark as complete?\n";
        cout << "Using the list above, select a number: ";
        while (flag)
        {
            getline(cin, decision);
            //Converts a string to an int
            final_decision = atoi(decision.c_str());
            if (final_decision > 0 && final_decision <= counter)
            {
                //Iterates through current task list to find matching task
                for (int x = 0; (unsigned)x < list.size(); x++)
                {
                    if (temp[final_decision-1] == list[x])
                    {
                        complete[x] = "x";
                    }
                }
                flag = false;
                cout << "\nTask successfully marked as complete...\n";
            }
            else
            {
                cout << "\nThat is not an option. Please try again: ";
            }
        }
    }
    else
    {
        cout << "\n\nThere are no incomplete tasks...\n";
    }
}

//Function used to mark tasks as incomplete if already completed
void Program::incompleteTask()
{
    string decision;
    int final_decision;
    int comp_num = 0;
    int counter = 0;
    bool flag = true;
    vector<string> temp;

    //Checks to see if there are any complete tasks in the current task list
    for (int x = 0; (unsigned)x < complete.size(); x++)
    {
        if (complete[x] == "x")
        {
            comp_num++;
        }
    }
    if (comp_num != 0)
    {
        cout << "\n\n----------------------------\n";
        cout << " Completed Tasks\n";
        cout << "----------------------------\n";
        for (int x = 0; (unsigned)x < list.size(); x++)
        {
            if (complete[x] == "x")
            {
                cout << counter + 1 << ". " << list[x] << endl;
                temp.push_back(list[x]);
                counter++;
            }
        }
        cout << "\nWhich task would you like to mark as incomplete?\n";
        cout << "Using the list above, select a number: ";
        while (flag)
        {
            getline(cin, decision);
            //Converts a string to an int
            final_decision = atoi(decision.c_str());
            if (final_decision > 0 && final_decision <= counter)
            {
                //Iterates through current task list to find matching task
                for (int x = 0; (unsigned)x < list.size(); x++)
                {
                    if (list[x] == temp[final_decision-1])
                    {
                        complete[x] = "o";                  
                    }
                }
                flag = false;
                cout << "\nTask successfully marked as incomplete...\n";
            }
            else
            {
                cout << "\nThat is not an option. Please try again: ";
            }
        }
    }
    else
    {
        cout << "\n\nThere are no completed tasks...\n";
    }
}

//Function used to remove tasks from the current task list
void Program::removeTask()
{
    string decision;
    int final_decision;
    int counter = 0;
    //Second counter used to count the number of total completed tasks
    int counter_2 = 0;
    bool flag = true;
    vector<string> temp;

    //Checks to see if there are any tasks in the current task list
    if (list.size() > (unsigned)0)
    {
        cout << "\n\n----------------------------\n";
        cout << " Incomplete Tasks\n";
        cout << "----------------------------\n";
        for (int x = 0; (unsigned)x < list.size(); x++)
        {
            if (complete[x] == "o")
            {
                counter++;
                cout << counter << ". " << list[x] << endl;
                temp.push_back(list[x]);
            }
        }
        if (counter == 0)
        {
            cout << "There are no incomplete tasks...\n";
        }
        cout << "\n----------------------------\n";
        cout << " Completed Tasks\n";
        cout << "----------------------------\n";
        for (int x = 0; (unsigned)x < list.size(); x++)
        {
            if (complete[x] == "x")
            {
                counter++;
                cout << counter << ". " << list[x] << endl;
                temp.push_back(list[x]);
                counter_2++;
            }
        }
        if (counter_2 == 0)
        {
            cout << "There are no completed tasks...\n";
        }
        cout << "\nWhich task would you like to remove?\n";
        cout << "Using the list above, select a number: ";
        while (flag)
        {
            getline(cin, decision);
            //Converts string to an int
            final_decision = atoi(decision.c_str());
            if (final_decision > 0 && (unsigned)final_decision <= list.size())
            {
                //Iterates through current task list to find matching task
                for (int x = 0; (unsigned)x < list.size(); x++)
                {
                    if (list[x] == temp[final_decision-1])
                    {
                        list.erase(list.begin() + x);
                        complete.erase(complete.begin() + x);               
                    }
                }
                cout << "\nTask successfully removed...\n";
                flag = false;
            }
            else
            {
                cout << "\nThat is not an option. Please try again: ";
            }
        }
    }
    else
    {
        cout << "\nYour current task list is empty...\n";
    }
}

//Function used to determine whether to quit
//Function needed to access private noQuit variable
bool Program::determineQuit()
{
    if (quit)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Function used to save current task list to a .txt file
//The task list is first copied and then the completed/incomplete list second
//Requires #include <iterator> to iterate through the stream
void Program::saveAndQuit()
{
    ofstream filestream("ToDoList.txt");
    copy(list.begin(), list.end(), ostream_iterator<string>(filestream, "\n"));
    copy(complete.begin(), complete.end(), ostream_iterator<string>(filestream, "\n"));
    filestream.close();
}

//Main function used to run the program
int main()
{
    Program todo;

    todo.greeting();
    while (!todo.determineQuit())
    {
        todo.menu();
    }
    todo.saveAndQuit();
}

