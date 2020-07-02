#ifndef BOARD_H
#define BOARD_H

#include <QVector>

class Board
{
public:
    Board();
    void clearBoard();
    unsigned short int getBoard(unsigned short int y, unsigned short int x);
    void setBoard(unsigned short int y, unsigned short int x, unsigned short int s);

private:
    unsigned short int board[20][10];   // 0 - empty, 1 - stone, 2 - sand
};

#endif // BOARD_H
