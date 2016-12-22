//Alexzander Avila
//Hangman

#include <iostream>
#include <iomanip>
#include <cstring>
#include <unistd.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "parts.h"

bool isguessed(char, char *);
bool testchoice(char, char *);
bool testifdone(char *);

bool guessed = false;
char words[5][20];
char *complete;
int main()
{
    srand(time(NULL));
    int misses = 0;
    char choice;
    char *guesses = new char[26];
    char *word = new char[20];
    int cap = 0;
    string str;
    string dum;
    int num;
    int linecount = 0;
    ifstream fin;
    ifstream lines;
    int count = 0;
    system("clear");
 
    lines.open("words.txt");
    while(getline(lines, dum))
    {
        linecount++;
    }
    lines.close();
    fin.open("words.txt");   

    num = rand() % linecount;
    num += 1;

    while(count != num)
    {
        getline(fin, str);
        strcpy(word, str.c_str());
        count++;
    }
    complete = new char[strlen(word)];
    for(int i = 0; i < strlen(word); i++)
        complete[i] = '-';
    do
    {

        guessed = false;

        //display the phase the user is on
        if(misses == 0)
            displaySetup();
        else if(misses == 1)
            displayHead();
        else if(misses == 2)
            displayBody();
        else if(misses == 3)
            displayLarm();
        else if(misses == 4)
            displayRarm();
        else if(misses == 5)
            displayLleg();

        //display the users current guesses
        cout << "Current Guesses:" << endl;
        for(int i = 0; i < strlen(guesses); i++)
        {
            cout << guesses[i];
            if(i != (strlen(guesses)-1))
                cout << ", ";
        } 
        cout << endl;

        //display the word being guessed
        for(int i = 0; i < strlen(complete); i++)
        {
            cout << complete[i];
        }
        if(testifdone(complete))
        {
            displayWin();
            return 1;
        }

        //prompt the user for a guess
        cout << endl;
        do
        {
            if(guessed)
                cout << "You've already guessed that letter!" << endl;
            cout << "Guess a letter: ";
            cin >> choice;

        }while(isguessed(choice, guesses));
            guesses[cap] = choice;
            cap++;
        if(!testchoice(choice, word))
            misses++;


        system("clear");
        usleep(10000);
    }while(misses < 6);
    if(misses == 6)
    {
        displayAll();
        cout << endl << "The word was: " << word << endl;
        displayEnd();
    }
    fin.close();
    return 0;
}


bool isguessed(char choice, char *guesses)
{
    for(int i = 0; i < strlen(guesses); i++)
    {
        if(choice == guesses[i])
        {
            guessed = true;
            return true;
        }
    }
    return false;
}

bool testchoice(char choice, char *word)
{
    bool appeared = false;
    for(int i = 0; i < strlen(word); i++)
    {
        if(word[i] == choice)
        {
            appeared = true;
            complete[i] = choice;
        }
    }
    if(appeared)
        return true;
    else
        return false;
}

bool testifdone(char *complete)
{
    for(int i = 0; i < strlen(complete); i++)
    {
        if(complete[i] == '-')
            return false;
    }
    return true;
}
