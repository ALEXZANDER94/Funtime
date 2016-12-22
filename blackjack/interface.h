const void displayWelcome()
{
    cout << endl;
    cout << "\033[1;33;40m"
         << "          ____        ____  ____              ____        " << endl
         << "|      | |     |     |     |    | |\\      /| |           " << endl
         << "|  /\\  | |__   |     |     |    | | \\    / | |__        " << endl
         << "| /  \\ | |     |     |     |    | |  \\  /  | |          " << endl
         << "|/    \\| |____ |____ |____ |____| |   \\/   | |____      " << endl
         << "\033[0m";
    cout << endl;
}
const void displayGO()
{
    cout << endl;
    cout << "\033[1;31;40m"
         << " _____                     ____      ____            ____   ___             " << endl
         << "|          /\\    |      | |         |    | \\      / |      |   \\         " << endl
         << "|  ___    /__\\   |\\    /| |__       |    |  \\    /  |__    |___/         " << endl
         << "|     |  /    \\  | \\  / | |         |    |   \\  /   |      |   \\        " << endl
         << "|_____| /      \\ |  \\/  | |____     |____|    \\/    |____  |    \\       " << endl
         << "\033[0m";
    cout << endl;
}

const void displayWin()
{
    cout << endl;
    cout << "\033[1;34;40m"
         << "       _____                 ____  __    _     " << endl
         << "|    |   |   |\\    | |\\   | |     |  \\  | | " << endl
         << "| /\\ |   |   |  \\  | | \\  | |__   |__/  |_| " << endl
         << "|/  \\|   |   |   \\ | |  \\ | |     |  \\   _ " << endl 
         << "|    | __|__ |    \\| |   \\| |____ |   \\ |_| " << endl
         << "\033[0m";
    cout << endl;    
}
const void displayDraw()
{
    cout << endl;
    cout << "\033[1;29;40m"
         << " ___    __                               " << endl
         << "|   \\  |  \\     /\\    |    |          " << endl
         << "|    | |__/    /__\\   | /\\ |          " << endl
         << "|    | |  \\   /    \\  |/  \\|   _  _  _ " << endl
         << "|___/  |   \\ /      \\ |    |  |_||_||_|" << endl
         << "\033[0m";
    cout << endl;
}
void displayMenu()
{
    cout << "Would you like to:" << endl
         << "1. PLAY" << endl
         << "2. RULES" << endl
         << "0. EXIT" << endl;
}

void displayGameUI()
{
    cout << "Would you like to:" << endl
         << "h. HIT" << endl
         << "s. STAY" << endl
         << "d. SPLIT" << endl
         << "q. FORFEIT" << endl;
}
void displayRules()
{
    cout << "The rules of the game are simple." << endl
         << "-User always goes first." << endl
         << "-During your turn, enter 'h' to hit." << endl
         << "-If you wish to end your turn, enter 's' to stay." << endl
         << "-If you have two of the same card, enter 'd' to split." << endl
         << "-Get as close as you can to 21 without going over." << endl
         << "-Just like the original BlackJack, Aces count for both 1's and 11's. " << endl;
    cout << endl;
}

void deckShuffle1(vector<int> &deck)
{

    cout << "Shuffling the deck." << endl;
    random_shuffle(deck.begin(), deck.end());
}

void deckShuffle2(vector<int> &deck)
{

    cout << "Shuffling the deck.." << endl;
    random_shuffle(deck.begin(), deck.end());
}

void deckShuffle3(vector<int> &deck)
{

    cout << "Shuffling the deck..." << endl;
    random_shuffle(deck.begin(), deck.end());
}
