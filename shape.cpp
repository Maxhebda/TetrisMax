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
}

void Shape::clearShape()
{
    shape.clear();
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
        for (short int i=0; i<9 ; i++)
        {
            shape.push_back(tableShape3x3[i+9*randomCounter]);
        }
    }
    else
    {
        for (short int i=0; i<16 ; i++)
        {
            shape.push_back(tableShape4x4[i+16*(randomCounter-counterShape3x3)]);
        }
    }
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
    shape.clear();
    // rotate shape
    for (unsigned short int y=0; y<row ; y++)
    {
        for (unsigned short int x=0; x<row ; x++)
        {
            shape.push_back(shapeTemp[row * x + row-1-y]);
        }
    }
}
