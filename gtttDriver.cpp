#include <iostream>
#include <string>
#include <iomanip>
#include "gtttHeader.h"
using namespace std;

//---------------------------------------------------------------------------------------
// This function covers the game logic and handles situations for wins, losses, and draws  
//---------------------------------------------------------------------------------------

int main()
{
    int numP = 0;
    Player* players = setup(numP);
    Board gameBoard;
    bool restart;

    int turn = 0;
    do
    {
        gameBoard.getDimensions();
        gameBoard.printBoard();
        
        while (!gameBoard.isFull())
        {
            gameBoard.placePiece(players[turn % numP]);
    
            if (gameBoard.checkWin(players[turn % numP]))
            {
                turn += 1;
                break;
            }
            turn += 1;
        }

        if (gameBoard.isFull())
        {
            cout << "That's a draw!" << endl;
            for (int i = 0; i < numP; i++)
            {
                players[i].setStats(0, 0, 1);
            }
        }
        else
        {
            for (int i = 0; i < numP; i++)
            {
                if (turn % numP == i)
                {
                    players[i].setStats(1, 0, 0);
                }
                else
                {
                    players[i].setStats(0, 1, 0);
                }
            }
        }

        Player::printStats(players, numP);
        restart = retry();
        gameBoard.~Board();
    } while (restart);

    return 0;
}