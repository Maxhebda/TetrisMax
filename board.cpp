#include "board.h"

Board::Board()
{
    clearBoard();
}

void Board::clearBoard()
{
    for (unsigned short int y=0; y<20 ; y++)
    {
        for (unsigned short int x=0; x<10 ; x++)
        {
            board[y][x]=0;
        }
    }
}

unsigned short int Board::getBoard(unsigned short y, unsigned short x)
{
    return board[y][x];
}

void Board::setBoard(unsigned short y, unsigned short x, unsigned short s)
{
    board[y][x] = s;
}
