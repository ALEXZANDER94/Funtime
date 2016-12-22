#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
#include <cstdlib>
using namespace std;
#include "interface.h"
#include "User.h"

#define PLAY 1
#define RULES 2
#define EXIT 0

#define HIT 'h'
#define STAY 's'
#define SPLIT 'd'
#define FORFEIT 'q'

void Begin(User &, User &, vector<int> &);
void clear(vector<int> &);
void computerTurn(User, User &, vector<int> &);
void WhoWon(User &, User &, vector<int> &);
void Phase(User &, User &, vector<int> &);
void endPhase(User, User &, vector<int> &);
char *findWinner(User &, User &, vector<int> &);


int main()
{
    User usr;
    User comp;
    srand(time(NULL));
    vector<int> deck;
    for(int i = 1; i < 5; i++)
    {
        for(int j = 1; j < 14; j++)
        {
            deck.insert(deck.end(), j);
        }
    }

    int choice;

    system("clear");
    displayWelcome();
    do
    {

        displayMenu();
        cin >> choice;
        switch(choice)
        {
            case PLAY:
                system("clear");
                deckShuffle1(deck);
                usleep(350000);
                system("clear");
                deckShuffle2(deck);
                usleep(350000);
                system("clear");
                deckShuffle3(deck);
                usleep(350000);
                Begin(usr, comp, deck);
                usr.CompleteClear();
                comp.clear();
                clear(deck);
                break;
            case RULES:
                system("clear");
                displayWelcome();
                displayRules();
                break;
            case EXIT:
                system("clear");
                cout << "Thanks for playing!" << endl;
                break;
            default:
                cout << "Enter a valid choice please." << endl;
                break;
        }
    }while(choice != 0);

    return 0;
}

void Begin(User &usr, User &comp, vector<int> &deck)
{
    usr.Userdraw(deck);
    comp.Userdraw(deck);
    Phase(usr, comp, deck);
}

void Phase(User &usr, User &comp, vector<int> &deck)
{
    User sp;
    char choice;
    system("clear");
    do
    {
        usr.displayBoard(usr,comp);
        cout << endl;
        if(usr.getTotal(0) > 21)
        {
            if(usr.testifOver())
            {
                if(usr.Spl())
                {
                    Phase(usr.getSplit(), comp, deck);
                    endPhase(usr, comp, deck);
                    return;
                }
                else
                {
                    cout << "You bust at " << usr.getTotal(0) << endl;
                    WhoWon(usr, comp, deck);
                    return;
                }
            }
        }

        if(usr.previous())
        {
            cout << "Hand Total: " << usr.getPrev().getTotal(0);
            cout << setfill(' ') << setw(10) << " ";
        }
        cout << "Hand Total: " << usr.getTotal(0);
        if(usr.aceProp() && usr.getTotal(1) <= 21)
        {
            cout << " or " << usr.getTotal(1);
        }
        if(usr.splitProp())
        {
            if(!usr.aceProp())
                cout << setfill(' ') << setw(10) << " ";
            else
                cout << setfill(' ') << setw(10) << " ";
            cout << "Hand Total: " << usr.getSplit().getTotal(0);
        }
        cout << endl;
        cout << endl;
        displayGameUI();
        cin >> choice;
        switch(choice)
        {
            case HIT:
                system("clear");
                usr.draw(deck);
                break;
            case STAY:
                if(!usr.Spl() && usr.previous())
                    return;
                break;
            case SPLIT:
                system("clear");
                if(usr.canSplit())
                {
                    usr.establishSplit(sp);
                }
                else
                    cout << "Split requires two of the same card!" << endl; 
                break;
            case FORFEIT:
                system("clear");
                cout << "That was a great game!" << endl;
                usr.clear();
                comp.clear();
                clear(deck);
                return;
                break;
            default:
                system("clear");
                cout << "Enter a valid choice!" << endl;
                break;
        }
    }while(choice != 's');
    if(usr.Spl())
    {
        usr.CalcTotals();
        Phase(usr.getSplit(), comp, deck);
        endPhase(usr, comp, deck);
    }
    else
    {
        if(usr.getTotal(1) > usr.getTotal(0) && usr.getTotal(1) <= 21)
            usr.resetTotal();
        endPhase(usr, comp, deck);
    }
}

void endPhase(User usr, User &comp, vector<int> &deck)
{
    system("clear");
    computerTurn(usr, comp, deck);
    WhoWon(usr, comp, deck);

}
void computerTurn(User usr, User &comp, vector<int> &deck)
{
    bool ai = true;
    do
    {
        system("clear");
        comp.displayBoard(usr, comp);
        cout << "Hand Total: " << usr.getTotal(0);
        if(usr.Spl())
        {
            cout << setfill(' ') << setw(10) << " ";
            cout << "Next Hand Total: " << usr.getSplit().getTotal(0);
        }
        cout << endl;
        usleep(1000000);
        cout << endl;
        if(!usr.Spl())
        {
            if(comp.testifOver() || comp.getTotal(0) >= usr.getTotal(0))
            {
                ai = false;
            }
            if(comp.canSplit())
            {
            }
            if((comp.getTotal(0) < usr.getTotal(0)) && usr.getTotal(0) <= 21) 
            {
                system("clear");
                comp.draw(deck);              
            }
        }
        else
        {
            if(comp.testifOver() || (comp.getTotal(0) >= usr.getTotal(0) && comp.getTotal(0) >= usr.getSplit().getTotal(0)))
            {
                ai = false;
            }
            if(comp.canSplit())
            {
            }
            if(((comp.getTotal(0) < usr.getTotal(0)) || comp.getTotal(0) < usr.getSplit().getTotal(0)) && usr.getTotal(0) <=21)
            {
                system("clear");
                comp.draw(deck);
            }
        }
    }while(ai);
}

void clear(vector<int> &deck)
{
    deck.clear();

    for(int i = 1; i < 5; i++)
    {
        for(int j = 1; j < 14; j++)
        {
            deck.insert(deck.end(), j);
        }
    }
}
void WhoWon(User &usr, User &comp, vector<int> &deck)
{
    char *choices;
    choices = new char[5];
    choices = findWinner(usr, comp, deck);
    int win_count = 0;
    int draw_count = 0;
    for(int i = 0; i < 5; i++)
    {
        if(choices[i] == 'W')
        {
            win_count++;
        }
        else if(choices[i] == 'D')
        {
            draw_count++;
        }
    }
    if(win_count > 0)
        displayWin();
    else if(draw_count > 0)
        displayDraw();
    else
        displayGO();
    cout << "That was a great game!" << endl;
    usr.CompleteClear();
    comp.clear();
    clear(deck);
}

char *findWinner(User &usr, User &comp, vector<int> &deck)
{
    char *w;
    int i = 0;
    User *tmp = &usr;
    w = new char[5];
    do
    {
        if(tmp->getTotal(0) > 21 || (comp.getTotal(0) > tmp->getTotal(0) && comp.getTotal(0) <= 21))
        {
            w[i] = 'L';
            i++;
        }
        else if(comp.getTotal(0) < tmp->getTotal(0) || comp.getTotal(0) > 21)
        {
            w[i] = 'W';
            i++;
        }
        else if(comp.getTotal(0) == tmp->getTotal(0))
        {
            w[i] = 'D';
            i++;
        }
        tmp = &tmp->getSplit();

    }while(tmp);
    return(w);
}
