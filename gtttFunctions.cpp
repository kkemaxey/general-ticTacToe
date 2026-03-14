#include <iostream>
#include <string>
#include <iomanip>
#include "gtttHeader.h"
using namespace std;

//-----------------------------------
// Fills the board with empty pieces
//-----------------------------------

Board::Board()
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            board[i][j] = ' ';
        }
    }
}


//--------------------------------------
// This clears the board once it's done
//--------------------------------------

Board::~Board()
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            board[i][j] = ' ';
        }
    }
}


//----------------------------------
// This checks if the board is full
//----------------------------------

bool Board::isFull()
{ // this can be O(1) if i just pass the amount of moves and make sure it's not equal to row*col
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This creates strings to hold the repeating lines, those being the number of rows and the lines inbetween, and prints them when needed along with the rest of the board
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Board::printBoard()
{
    char rowChar = 'A';

    string line = "   ";
    string colNum = "    ";

    for (int i = 0; i < col; i++)
    {
        line += "--- ";
        
        if (i + 1 < 10)
        {
            colNum += to_string(i + 1);
            colNum += "   "; 
        }
        else
        {
            colNum += to_string(i + 1);
            colNum += "  "; 
        }
    }

    cout << endl << colNum;
    for (int i = 0; i < row; i++)
    {
        cout << endl << line << endl;
        cout << rowChar << " | ";
        for (int j = 0; j < col; j++)
        {
            cout << board[i][j] << " | ";
        }
        cout << rowChar;
        rowChar++;
    }
    cout << endl << line << endl << colNum << endl << endl;
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Uses to do-while loops to error check the user inputs. If the input is valid, the input will be saved and used to display the board.
//--------------------------------------------------------------------------------------------------------------------------------------

void Board::getDimensions()
{
    string input;
    cout << endl << "Please enter the dimension of the board." << endl << endl;

    do
    {
        cout << "Enter the number rows    -> ";
        getline (cin, input);

        if (!isValidInput(input) || stoi(input) > MAX_ROW || stoi(input) < 4)
        {
            cout << "Please enter a valid input. ";
        }
        else
        {
            row = stoi(input);
        }
    } while (row == 0);

    do
    {
        cout << endl << "Enter the number columns -> ";
        getline (cin, input);

        if (!isValidInput(input) || stoi(input) > MAX_COL || stoi(input) < 4)
        {
            cout << "Please enter a valid input. " << endl;
        }
        else
        {
            col = stoi(input);
        }
    } while (col == 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This first parses the input into the expected format then checks if that format is followed. Then it checks if the board has room for the piece and finally inserts it
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Board::placePiece(Player player)
{
    string userInput;
    bool set = false;

    while (!set)
    {
        cout << player.first << ", where would you like to place your piece? -> ";
        getline(cin, userInput);

        //Parsing
        char tempChar = userInput[0];
        string tempString;
        for (int i = 1; i < userInput.length(); i++)
        {
            tempString += userInput[i];
        }

        //Error Checking
        if (!isValidInput(tempString) || !isAlpha(tempChar))
        {
            cout << "Please enter a valid input. " << endl;
            continue;
        }

        int userCol = stoi(tempString) - 1;
        int userRow = toLower(tempChar) - 97;

        if (userCol >= col || userCol < 0 || userRow >= row)
        {
            cout << "Please enter a valid input. " << endl;
        }

        //Setting the piece
        else if (board[userRow][userCol] != ' ')
        {
            cout << "That spot is full." << endl;
            cout << "Please enter a valid input." << endl;
        }
        else if (isFull())
        {
            cout << "The board is full!" << endl;
            return;
        }
        else
        {
            board[userRow][userCol] = player.piece;
            set = true;
        }
    }
}


//---------------------------------------------------------------------------------------------------------------
// This will first search for a player's piece in the board then check any winning configurations for that piece
//---------------------------------------------------------------------------------------------------------------

bool Board::checkWin(Player player)
{ //instead of checking the whole board you can just check all wining configurations from where the user inserted their piece
    bool hasWon = false;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (board[i][j] == toLower(player.piece))
            {
                if (j + 2 < col && 
                    board[i][j+1] == toLower(player.piece) && 
                    board[i][j+2] == toLower(player.piece))
                {
                    board[i][j] -= 32;
                    board[i][j+1] -= 32;
                    board[i][j+2] -= 32;
                    hasWon = true;
                }
                if (i + 2 < row && 
                    board[i+1][j] == toLower(player.piece) && 
                    board[i+2][j] == toLower(player.piece))
                {
                    board[i][j] -= 32;
                    board[i+1][j] -= 32;
                    board[i+2][j] -= 32;
                    hasWon = true;
                }

                if (i + 2 < row && j + 2 < col && 
                    board[i+1][j+1] == toLower(player.piece) && 
                    board[i+2][j+2] == toLower(player.piece))
                {
                    board[i][j] -= 32;
                    board[i+1][j+1] -= 32;
                    board[i+2][j+2] -= 32;
                    hasWon = true;
                }
                
                if (i + 2 < row && j - 2 >= 0 && 
                    board[i+1][j-1] == toLower(player.piece) && 
                    board[i+2][j-2] == toLower(player.piece))
                {
                    board[i][j] -= 32;
                    board[i+1][j-1] -= 32;
                    board[i+2][j-2] -= 32;
                    hasWon = true;
                }
            }
        }
    }

    if (hasWon)
    {
        cout << "Congratulations " << player.first << "! You win!!" << endl;
    }
    printBoard();
    return hasWon;
}

//----------------------------------------------------
// Initializes everything to zero except for the piece
//----------------------------------------------------

Player::Player()
{
    first = last = "";
    wins = losses = draws = 0;
}


//------------------------------
// This is a standard destructor
//------------------------------

Player::~Player()
{
    first = last = "";
    wins = losses = draws = 0;
}


//------------------------------------------------------------------------------------------------------------
// This function makes use of the isValidName and substring function to validate a player's name and set them
//------------------------------------------------------------------------------------------------------------

void Player::getName(int playerNum)
{
    bool finished = false;

    do
    {
        string nameCheck;
        cout << "Player " << playerNum << ", Please enter your name -> ";
        getline(cin, nameCheck);

        int space = 0;
        while (nameCheck[space] != ' ')
        {
            space++;
        }

        string tempFirst, tempLast;
        tempFirst = substring(nameCheck, 0, space);
        tempLast = substring(nameCheck, space + 1, nameCheck.length());

        if (isValidName(tempFirst) && isValidName(tempLast))
        {
            first = format(tempFirst);
            last = format(tempLast);
            finished = true;
        }
        else
        {
            cout << "Please enter a valid name." << endl;
        }
    } while (!finished);

    cout << "Hello, " << first << "." << endl;
}


//------------------------------------------------
// This just sets the players' pieces respectfully
//------------------------------------------------

void Player::setPiece(char p)
{
    piece = p;
}


//------------------------------------
// This updates the stats of a player
//------------------------------------

void Player::setStats(int w, int l, int d)
{
    wins += w;
    losses += l;
    draws += d;
}


//----------------------------------------------------------
// This adds all the stats to keep track of the total games
//----------------------------------------------------------

int Player::totalGames()
{
    return (wins + losses + draws);
}


//---------------------------------------------------------------------
// This prints out each players' stats according to the specifications
//---------------------------------------------------------------------

void Player::printStats(Player* arr, int numP)
{
    string line = " ------ ------ ------ ";

    static int length = 0;
    cout << "Total game(s) played = " << arr[0].totalGames() << endl << endl;
    
    for (int i = 0; i < numP; i++)
    {
        if ((arr[i].first.length() + arr[i].last.length()) + 1 > length)
        {
            length = arr[i].first.length() + arr[i].last.length() + 1;
        }
    }
    
    int lineIndent = length + line.length() + 1;
    
    cout << right << setw(lineIndent) << line << endl;
    cout << right << setw(lineIndent) << "|  WIN | LOSS | DRAW |" << endl;
    cout << right << setw(lineIndent) << line << endl;

    for (int i = 0; i < numP; i++)
    {
        string full = arr[i].first + " " + arr[i].last; 
        cout << right << setw(length) << full;
        cout << " | " << right << setw(4) << arr[i].wins;
        cout << " | " << right << setw(4) << arr[i].losses;
        cout << " | " << right << setw(4) << arr[i].draws << " |" << endl;
        cout << setw(lineIndent) << line << endl;
    }
}


//---------------------------------------------------------------------------------------------------------------------------------
// This takes in the amount of players that the user wants, then dynamically allocates an array of players and assigns their pieces
//---------------------------------------------------------------------------------------------------------------------------------

Player* setup(int &numP)
{
    string input = "0";

    while (stoi(input) > 7 || stoi(input) < 3)
    {
        cout << "How many players? Pick a number between 3 & 7 -> ";
        getline(cin, input);

        if (!isValidInput(input) || stoi(input) > 7 || stoi(input) < 3)
        {
            cout << "Please enter a valid input." << endl;
            input = "0";
        }
    }

    numP = stoi(input);

    Player* arr = new Player[numP];

    for (int i = 0; i < numP; i++)
    {
        arr[i].getName(i + 1); // prompt player for name
        arr[i].setPiece('z' - i); // assign piece
    }

    return arr;
}


//---------------------------------------------------
// This determines if the user wants to retry or not
//---------------------------------------------------

bool retry()
{
    string userInput;
    cout << "Would you like to play again? Y/N -> ";
    getline(cin, userInput);

    while ((userInput[0] != 'Y') && (userInput[0] != 'N') || userInput.length() != 1)
    {
        cout << "Please insert a valid input (Y or N)-> ";
        getline(cin, userInput);
    }

    if (userInput[0] == 'Y')
    {
        return true;
    }
    else
    {
        cout << "Thanks for playing!" << endl;
        return false;
    }
}


//-----------------------------------------------------------------------------------------------------------------
// This function test for the most common combination of characters to a valid name and returns true if it's valid
//-----------------------------------------------------------------------------------------------------------------

bool isValidName(string str)
{
    if (str[0] == '\'' || str[0] == '-' || str.length() == 0)
    {
        return false;
    }

    for (int i = 0; i < str.length(); i++)
    {
        if (isAlpha(str[i]) || ((str[i] == '\'') || (str[i] == '-') && isAlpha(str[i+1])))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}


//-------------------------------------------------------------------------------------------------------
// This function loops through a given string an ensures that it's ready for any string to int conversion
//-------------------------------------------------------------------------------------------------------

bool isValidInput(string str)
{
    if (str.empty())
    {
        return false;
    }

    for (int i = 0; i < str.length(); i++)
    {
        if (!isDigit(str[i]))
        {
            return false;
        }
    }
    return true;
}


//------------------------------------------------------------------------------------
// This formats any name so that the first letter is uppercase and the rest are lower
//------------------------------------------------------------------------------------

string format(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = toLower(str[i]);

        if(str[i] == '-')
        {
            str[i+1] = toUpper(str[i+1]);
            i++;
        }
    }

    str[0] = toUpper(str[0]);
    return str;
}


//------------------------------------------------------------------------------------------------
// This creates a substring if given the start position and end position of the desired substring
//------------------------------------------------------------------------------------------------

string substring(string str, int start, int end)
{
    string str2;

    for (int i = start; i < end; i++)
    {
        if (str[i] == '\'' || str[i] == '-')
        {
            str2 += str[i];
        }
        else
        {
            str[i] = toLower(str[i]);
            str2 += str[i];
        }
    }

    return str2;
}


//------------------------------------------------------------------------
// This returns true if the character is an uppercase or lowercase letter
//------------------------------------------------------------------------

bool isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


//-----------------------------------------------
// This returns true if the character is a digit
//-----------------------------------------------

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

//------------------------------------------------------------
// This returns the capitalized letter if the input is valid
//------------------------------------------------------------

char toUpper(char c)
{
    return c & ~32;
}


//----------------------------------------------------------
// This returns the lowercased letter if the input is valid
//----------------------------------------------------------

char toLower(char c)
{
    return c | 32;
}