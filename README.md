# Funtime
Just some games made with C++


FUNTIME

These two directories are the challenges I had given myself whilst a student at California State University - Bakersfield.
They are made completely in C++ and, I believe, show my experience with algorithm analysis, slight AI implementation, Object
Oriented Programming, and I/O manipulation. The directories themselves are self explanatory, the Hangman directory contains
files that, when executed, begin a game of hangman; the Blackjack directory contains files that, when executed, begin a game
Blackjack.


PREREQUISITES - Hangman & Blackjack

There are no prerequisites for installing this project.


INSTALLING - Hangman & Blackjack

To install, clone the project onto your desktop, or wherever you wish to have it stored. 


RUNTIME - Hangman

The Hangman game was fairly simple to implement. I had come up with the idea to create it when I had discovered the C++
method 'system("clear")'. The source code begins by selectint a random number, this number is used to grab the word from
a separate file containing all of the possible words for the game. Once a word is selected, then the game begins and the User 
is prompted to enter a letter. Just as we enjoyed the game as children, the executable shows the User a string of hyphens 
equal to the number of characters in the word to be guessed. The User is then prompted to enter a letter and, if they are
correct, the letter is shown in the string. 


RUNTIME - BLACKJACK

The Blackjack game was quite difficult to implement. At the time, it was a rather extensive challenge of my knowledge of 
C++ and Object-Oriented Programming. The executable starts by prompting the User to enter a choice: 1, 2, or 3. 
Upon beginning the game, an array ("deck") is created and instantiated with values 1 through 13 via 'for' loop; this
is done 4 times (52 cards in a deck). Then the array is "shuffled" 3 times before beginning to simulate an sense of randomness.
The User goes first and can decide "hit" or "stay". After the User has decided to stay, then the Dealer has a chance. The AI
is simple, "as long as the User has a higher hand than me, I will keep requesting more cards". A much more interesting 
feature of the source code is the ability to Split. If the User has two of the same card, they may split their hand into two
separate hands for an extra chance to win.


AUTHOR

Alexzander Avila - Initial work - B.S. in Computer Science
