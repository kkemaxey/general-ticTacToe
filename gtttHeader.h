#ifndef GTTTHEADER_H
#define GTTTHEADER_H
using namespace std;

class Player
{
    private:
        string first, last;
        char piece;
        int wins, losses, draws;

    public:
        Player();
        ~Player();
        void getName(int);
        void setPiece(char);
        void setStats(int, int, int);
        int totalGames();
        static void printStats(Player*, int);

        friend class Board;
};

class Board
{
    private:
        static const int MAX_ROW = 10;
        static const int MAX_COL = 15;
        char board[MAX_ROW][MAX_COL];
        int row = 0;
        int col = 0;

    public:
        Board();
        ~Board();
        bool isFull();
        void printBoard();
        void getDimensions();
        void placePiece(Player);
        bool checkWin(Player);
};

Player* setup(int&);
bool retry();
bool isValidName(string);
bool isValidInput(string);
string format(string);
string substring(string, int, int);
bool isAlpha(char);
bool isDigit(char);
char toLower(char);
char toUpper(char);

#endif