#include "scorescell.h"

ScoresCell::ScoresCell(QString value)
{
    srand(time(NULL));
    xSpeed = rand()%40+20;
    if (rand()%2==0)
    {
        xSpeed*=-1;                 // x = 20..60 or -20..-60   left||right
    }
    ySpeed = rand()%40-60;          // y = -21..-60             only up
    gravitation = (rand()%16+6)/3;  // g = 2..7
    step = 0;
    lengthOfLife = rand()%11+10;    // l = 10..20
    this->value = value;
}

void ScoresCell::setX(double x)
{
    this->x = x;
}

void ScoresCell::setY(double y)
{
    this->y = y;
}

unsigned short int ScoresCell::getX()
{
    return static_cast<unsigned short int>(x);
}

unsigned short int ScoresCell::getY()
{
    return  static_cast<unsigned short int>(y);
}

bool ScoresCell::itsDead()
{
    if (step>=lengthOfLife)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ScoresCell::go()
{
    step++;
    x=x+xSpeed;
    y=y+ySpeed;
    ySpeed = ySpeed + gravitation;
}

QString ScoresCell::getValue()
{
    return value;
}
