#ifndef USER_H
#define USER_H
class User
{
    private:
        int *hand;
        int hand_count;
        int *hand_total;

        bool ace;

        User *split;
        User *prev;

    public:

        User()
        {
            hand = new int[10];
            hand_count = 0;
            hand_total = new int[1];
            hand_total[0] = 0; 
            hand_total[1] = 0;
            split = NULL;
            prev = NULL;
            ace = false;
        }

        void establishSplit(User &sp)
        {
            int index = getsplitIndex();
            User *tmp = this;
            while(tmp->split)
                tmp = tmp->split;
            tmp->split = &sp;
            sp.prev = tmp;
            sp.hand[0] = hand[index];

            if(hand[index] == 1)
            {
                sp.ace = true;
                hand_total[0] -= 1;
                hand_total[1] -= 11;
                sp.hand_total[0] += 1;
                sp.hand_total[1] += 11;
            }
            else
            {
                if(hand[index] > 10)
                {
                    hand_total[0] -= 10;
                    hand_total[1] -= 10;
                    sp.hand_total[0] += 10;
                    sp.hand_total[1] += 10;
                }
                else
                {
                    hand_total[0] -= sp.hand[0];
                    hand_total[1] -= sp.hand[0];
                    sp.hand_total[0] += sp.hand[0];
                    sp.hand_total[1] += sp.hand[0];
                }
            }
            sp.hand_count++;
            hand[index] = '\0';
            hand_count--;
        }

        void Userdraw(vector<int> &deck)
        {
            this->draw(deck);
            this->draw(deck);
            cout << endl;
        }

        void resetTotal()
        {
            hand_total[0] = hand_total[1];   
        }
        void CalcTotals()
        {
            User *tmp = this;
            do
            {
                if(tmp->hand_total[1] > tmp->hand_total[0] && tmp->hand_total[1] <= 21)
                    tmp->hand_total[0] = tmp->hand_total[1];
                tmp = tmp->split;
            }while(tmp);
        }
        int getTotal(int index)
        {
            return(hand_total[index]);
        }

        void clear()
        {
            for(int i = 0; i < this->hand_count; i++)
                this->hand[i] = '\0';
            this->hand_count = 0;
            this->hand_total[0] = 0;
            this->hand_total[1] = 0;
            //this->prev = NULL;
            //this->split = NULL;
            this->ace = false;
        }
        void CompleteClear()
        {
            User *tmp = this;
            do
            {
                for(int i = 0; i < tmp->hand_count; i++)
                    tmp->hand[i] = '\0';
                tmp->hand_count = 0;
                tmp->hand_total[0] = 0;
                tmp->hand_total[1] = 0;
                tmp->ace = false;
                tmp = tmp->split;
                if(tmp)
                    tmp->prev->split = NULL;
            }while(tmp);
        }
        void draw(vector<int> &deck)
        {
            hand[hand_count] = deck.back();
            if(hand[hand_count] > 10)
            {
                hand_total[0] += 10;
                hand_total[1] += 10;
            }
            else
            {
                if(hand[hand_count] == 1)
                {
                    this->ace = true;
                    hand_total[0] += 1;
                    hand_total[1] += 11;
                }
                else
                {
                    hand_total[0] += hand[hand_count];
                    hand_total[1] += hand[hand_count];
                }       
            }
            deck.pop_back();
            hand_count++;
        }

        User getPrev()
        {
            User dum = *prev;
            return(dum);
        }
        User& getSplit()
        {
            User &dum = *split;
            return(dum);
        }
        bool aceProp()
        {
            return(this->ace);
        }

        bool previous()
        {
            if(this->prev != NULL)
                return true;
            else
                return false;
        }
        bool Spl()
        {
            if(this->split != NULL)
                return true;
            else
                return false;
        }

        void displayHand()
        {
            for(int i = 0; i < this->hand_count; i++)
            {
                if(hand[i] != '\0')
                {
                    cout << "[";
                    if(this->hand[i] == 11)
                        cout << "J";
                    else if(this->hand[i] == 12)
                        cout << "Q";
                    else if(this->hand[i] == 13)
                        cout << "K";
                    else if(this->hand[i] == 1)
                        cout << "A";
                    else
                        cout << this->hand[i];
                    cout << "] ";
                }
            }
        }

        bool testifOver()
        {
            if(!this->ace)
            {
                if(hand_total[0] > 21)
                    return true;

            }
            if(hand_total[0] > 21)
                return true;
            else if(hand_total[1] > 21)
                this->ace = false;
            return false;
        }
        void displayBoard(User usr, User comp)
        {
            User *tmp = &usr;
            //Dealer's Hand
            cout << "Dealer's Hand: " << endl;
            comp.displayHand();
            cout << "\nDealer Total: " << comp.getTotal(0);
            cout << endl << endl << endl;

            //User's Hand(s)
            cout << "Your Hands: " << endl;
            while(tmp->prev)
            {
                tmp = tmp->prev;
            }
            do
            {
                tmp->displayHand();
                if(tmp->ace)
                {
                    if(tmp->hand_total[0] < 10)
                        cout << setfill(' ') << setw(1 + (4 * (7 - tmp->hand_count))) << " ";
                    if(tmp->hand_total[0] >= 10)
                        cout << setfill(' ') << setw(2 + (4 * (7 - tmp->hand_count))) << " ";
                }
                else
                {
                    if(tmp->hand_total[0] < 10)
                        cout << setfill(' ') << setw(3 + (4 * (5-tmp->hand_count))) << " ";
                    else if(tmp->hand_total[1] >= 10)
                        cout << setfill(' ') << setw(4 + (4 * (5-tmp->hand_count))) << " ";
                }
                tmp = tmp->split;
            }while(tmp);
            cout << endl;
        }

        int getsplitIndex()
        {
            for(int i = 0; i < hand_count; i++)
            {
                for(int j = i+1; j < hand_count; j++)
                {
                    if(hand[i] == hand[j])
                        return j;
                }
            }

        }

        int getCount()
        {
            return(this->hand_count);
        }
        bool splitProp()
        {
            if(split != NULL)
                return true;
            else
                return false;
        }
        bool canSplit()
        {
            for(int i = 0; i < hand_count; i++)
            {
                for(int j = i+1; j < hand_count; j++)
                {
                    if(hand[i] == hand[j])
                        return true;
                }
            }
            return false;
        }

        User& operator =(const User& usr)
        {
            for(int i = 0; i < usr.hand_count; i++)
            {
                this->hand[i] = usr.hand[i];
            }
            this->hand_total[0] = usr.hand_total[0];
            this->hand_total[1] = usr.hand_total[1];
            this->ace = usr.ace;
            this->split = usr.split;
            this->prev = usr.prev;
            this->hand_count = usr.hand_count;
            return(*this);
        }
};
#endif
