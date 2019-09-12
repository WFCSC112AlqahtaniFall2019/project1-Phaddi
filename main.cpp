#include <iostream>
#include <vector>

using namespace std;
int row = 3;
int col = 3;
int userguess;
int space = 0; //how we show which square is which to the user
int location1; //first location of boat
int location2; //second location of boat
int guessnum = 0;
int guesscor = 0;
//declare and initialize 2D vectors (vector of vector)
vector <int> vec(col, 0);
vector <vector<int>> matrix(row, vec);
vector <int> guesses;
vector <char> key;

//interface
bool guessTwicePass(int userGuess, vector<int> guesses);
void printBoard();
bool beenGuessed(int num, vector<int> guesses);

int main()
{
    cout << "Welcome to Battleship! There are two enemy ships hiding in this grid, type in numbers to try to find and sink them!" << endl;
    //print the vector
    printBoard();

    //Secret locations decided
    bool set = false;
    srand(time(0));
    while(!set)
    {
        location1 = rand() % (row*col) + 1;
        location2 = rand() % (row*col) + 1;
        if(location1 != location2)
        {
            set = true;
        } else
        {
            set = false;
        }
    }
    //making the key
    for(int i = 1; i <= row * col; i++)
    {
        if(i == location1 || i == location2)
        {
            key.push_back('X');
        }
        else
        {
            key.push_back('O');
        }
    }

    //game starts
    while(guesscor < 2) {
        cout << "Guess a location 1-" << row * col << ":" << endl;
        cin >> userguess;
        if(userguess >= 1 && userguess <= row*col) {
            if (guessTwicePass(userguess, guesses) == true) {
                if (userguess == location1 || userguess == location2) {
                    cout << "HIT!" << endl;
                    guessnum++;
                    guesscor++;
                } else {
                    cout << "Miss" << endl;
                    guessnum++;
                }
                guesses.push_back(userguess);
                printBoard();
            } else {
                cout << "Sorry, you guessed that already." << endl;
                guessnum++;
            }
        } else{
            cout << "Guess in the provided range." << endl;
            guessnum++;
        }
    }

    //game over you win in _ guesses message

    cout << endl;
    cout << "Game Over! You won in " << guessnum << " guesses!" << endl;
    cout << "FINAL BOARD:" << endl;
    printBoard();

    return 0;
}

//double checks that the same input hasn't already been guessed
bool guessTwicePass(int userGuess, vector<int> guesses) {
    bool pass = true;
    int guess = userGuess;
    if(guesses.size() < 1)
    {
        return true;
    }
    for(int i = 0; i <= guesses.size()-1; i++) {
        if (guess == guesses.at(i)) {
            return false;
        }
    }
    return true;
}

//prints the board
void printBoard()
{
    space = 0; //resets the space count
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.size(); j++)
        {
            space++;
            if(beenGuessed(space, guesses)) {
                    cout << "[" << key.at(space-1) << "]";
            } else {
                cout << "[" << space << "]";
            }
        }
        cout << endl;
    }
}

//checks to see if the input has been guessed
bool beenGuessed(int num, vector<int> guesses)
{
    if(guesses.size() < 1)
    {
        return false;
    }
    for(int i = 0; i < guesses.size(); i++)
    {
        if(num == guesses.at(i))
        {
            return true;
        }
    }
    return false;
}