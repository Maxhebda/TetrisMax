#include "shape.h"

const unsigned short int counterShape3x3 = 6;
const unsigned short int counterShape4x4 = 1;
const unsigned short int tableShape3x3percent[counterShape3x3]={100,100,100,100,100,100};
const unsigned short int tableShape4x4percent[counterShape4x4]={100};
const unsigned short int tableShape3x3[counterShape3x3*9]=
{    0,0,0,
     0,1,0,
     0,0,0,

     0,1,0,
     1,1,1,
     0,0,0,

     1,1,0,
     0,1,1,
     0,0,0,

     0,1,1,
     1,1,0,
     0,0,0,

     0,0,1,
     1,1,1,
     0,0,0,

     1,0,0,
     1,1,1,
     0,0,0};
const unsigned short int tableShape4x4[counterShape3x3*16]=
{   0,0,0,0,
    1,1,1,1,
    0,0,0,0,
    0,0,0,0};

Shape::Shape()
{
    srand(time(NULL));
    direction = true;
}

void Shape::newShape()
{
    bool isNotEndRandom=true;
    unsigned short int randomCounter;
    shape.clear();

    while (isNotEndRandom)
    {
        randomCounter = rand()%(counterShape3x3+counterShape4x4);
        if (randomCounter<counterShape3x3)
        {           //small shapes 3x3
            if (rand()%100<tableShape3x3percent[randomCounter])
            {
                isNotEndRandom=false;
            }
        }
        else
        {           //big shapes 4x4
            if (rand()%100<tableShape4x4percent[randomCounter-counterShape3x3])
            {
                isNotEndRandom=false;
            }
        }
    }
    if (randomCounter<counterShape3x3)
    {
        lengthRow = 3;
        for (short int i=0; i<9 ; i++)
        {
            shape.push_back(tableShape3x3[i+9*randomCounter]);
        }
    }
    else
    {
        lengthRow = 4;
        for (short int i=0; i<16 ; i++)
        {
            shape.push_back(tableShape4x4[i+16*(randomCounter-counterShape3x3)]);
        }
    }
    // new first shape position
    yPosition=0;
    xPosition=(10-((shape.size()==9)?3:4)) / 2;          // (10 - 3) / 2
}

QVector <unsigned short int> Shape::getShape()
{
    return shape;
}

void Shape::rotateShape()   // 90 degree rotation / turn left
{
    unsigned short int row = shape.size()==9?3:4;
    QVector <unsigned short int> shapeTemp;
    // copy shape
    for (unsigned short int y=0; y<row ; y++)
    {
        for (unsigned short int x=0; x<row ; x++)
        {
            shapeTemp.push_back(shape[row*y+x]);
        }
    }

    if (direction)
    {
        // rotate shape right direction
        for (unsigned short int y=0; y<row ; y++)
        {
            for (unsigned short int x=0; x<row ; x++)
            {
                shape[row*x + y]=shapeTemp[row * (row-1-y) + x];
            }
        }
    }
    else
    {
        // rotate shape left direction
        for (unsigned short int y=0; y<row ; y++)
        {
            for (unsigned short int x=0; x<row ; x++)
            {
                shape[row*x+y]=shapeTemp[row * y + row-1-x];
            }
        }
    }
}

unsigned short int Shape::row()
{
    return lengthRow;
}

unsigned short int Shape::getShapeCell(unsigned short int y, unsigned short int x)
{
    return shape[row() * y + x];
}

unsigned short int Shape::x()
{
    return xPosition;
}

unsigned short int Shape::y()
{
    return  yPosition;
}
